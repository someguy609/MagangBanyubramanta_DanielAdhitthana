#include <algorithm>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"
#include "interfaces/msg/object.hpp"

#define DEBUG

using namespace std::chrono_literals;
using std::placeholders::_1;

class Camera : public rclcpp::Node
{
public:
    Camera() : Node("camera")
    {
        timer_ = this->create_wall_timer(500ms, std::bind(&Camera::timer_callback, this));
        publisher_ = this->create_publisher<interfaces::msg::Object>("detected_object", 10);
        cap_ = cv::VideoCapture(0);

// #ifdef DEBUG
//         cv::namedWindow("values");
//         cv::createTrackbar("hue thresh", "values", &hue_thresh, 90);
//         cv::createTrackbar("min sat", "values", &min_sat, 255);
//         cv::createTrackbar("min val", "values", &min_val, 255);
//         cv::createTrackbar("min area", "values", &min_area, 10000);
//         cv::createTrackbar("red hue", "values", &red_hue, 179);
//         cv::createTrackbar("yellow hue", "values", &yellow_hue, 179);
//         cv::createTrackbar("blue hue", "values", &blue_hue, 179);
// #endif

        if (!cap_.isOpened())
            RCLCPP_ERROR(this->get_logger(), "Failed to open video capture");
    }

    ~Camera()
    {
        cap_.release();
        cv::destroyAllWindows();
    }

private:

    void morph(cv::Mat &frame) 
    {
        cv::morphologyEx(frame, frame, cv::MORPH_OPEN, kernel);
        cv::morphologyEx(frame, frame, cv::MORPH_CLOSE, kernel);
    }

    void timer_callback()
    {
        cv::Mat frame;

        if (!cap_.read(frame))
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to read frame");
            return;
        }

#ifdef DEBUG
        cv::imshow("frame", frame);
#endif

        cv::Mat hsv_frame;
        cv::cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);

        if (hsv_frame.empty())
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to convert frame to HSV");
            return;
        }

#ifdef DEBUG
        cv::imshow("hsv_frame", hsv_frame);
#endif

        cv::Mat red, yellow, blue;
        cv::inRange(hsv_frame, cv::Scalar(red_hue - hue_thresh, min_sat, min_val), cv::Scalar(red_hue + hue_thresh, 255, 255), red);
        cv::inRange(hsv_frame, cv::Scalar(yellow_hue - hue_thresh, min_sat, min_val), cv::Scalar(yellow_hue + hue_thresh, 255, 255), yellow);
        cv::inRange(hsv_frame, cv::Scalar(blue_hue - hue_thresh, min_sat, min_val), cv::Scalar(blue_hue + hue_thresh, 255, 255), blue);

        this->morph(red);
        this->morph(yellow);
        this->morph(blue);

#ifdef DEBUG
        cv::imshow("red", red);
        cv::imshow("yellow", yellow);
        cv::imshow("blue", blue);
#endif

        cv::Moments red_moments = cv::moments(red),
                    yellow_moments = cv::moments(yellow),
                    blue_moments = cv::moments(blue);

        auto message = interfaces::msg::Object();
        message.red = red_moments.m00 > min_area;
        message.yellow = yellow_moments.m00 > min_area;
        message.blue = blue_moments.m00 > min_area;

        publisher_->publish(message);
    }

    rclcpp::Publisher<interfaces::msg::Object>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    cv::VideoCapture cap_;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    int red_hue = 0, yellow_hue = 30, blue_hue = 120,
        hue_thresh = 50, min_sat = 50, min_val = 50, min_area = 100;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Camera>());
    rclcpp::shutdown();
    return 0;
}