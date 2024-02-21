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
        timer_ = this->create_wall_timer(10ms, std::bind(&Camera::timer_callback, this));
        publisher_ = this->create_publisher<interfaces::msg::Object>("detected_object", 10);
        cap_ = cv::VideoCapture(0);

#ifdef DEBUG
        cv::namedWindow("values");
        cv::createTrackbar("hue thresh", "values", &hue_thresh, 90);
        cv::createTrackbar("min sat", "values", &min_sat, 255);
        cv::createTrackbar("min val", "values", &min_val, 255);
        cv::createTrackbar("min area", "values", &min_area, 10000);
        cv::createTrackbar("red hue", "values", &red_hue, 179);
        cv::createTrackbar("yellow hue", "values", &yellow_hue, 179);
        cv::createTrackbar("blue hue", "values", &blue_hue, 179);
#endif

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

    void embed_msg(cv::Moments &moment, const int color)
    {
        if (moment.m00 < min_area)
            return;

        auto message = interfaces::msg::Object();
        message.color = color;
        message.x = moment.m10 / moment.m00 - cap_.get(cv::CAP_PROP_FRAME_WIDTH) / 2;
        message.y = moment.m01 / moment.m00 - cap_.get(cv::CAP_PROP_FRAME_HEIGHT) / 2;
        message.angle = 2 * float(message.x) / float(cap_.get(cv::CAP_PROP_FRAME_WIDTH));

        publisher_->publish(message);
    }

    void timer_callback()
    {
        cv::Mat frame;

        if (!cap_.read(frame))
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to read frame");
            return;
        }

        cv::Mat hsv_frame;
        cv::cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);

        if (hsv_frame.empty())
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to convert frame to HSV");
            return;
        }

        cv::Mat red_lower, red_upper, red, yellow, blue;
        cv::inRange(hsv_frame, cv::Scalar(red_hue - hue_thresh, min_sat, min_val), cv::Scalar(red_hue + hue_thresh, 255, 255), red_lower);
        cv::inRange(hsv_frame, cv::Scalar(180 - red_hue - hue_thresh, min_sat, min_val), cv::Scalar(180 - red_hue + hue_thresh, 255, 255), red_upper);
        cv::inRange(hsv_frame, cv::Scalar(yellow_hue - hue_thresh, min_sat, min_val), cv::Scalar(yellow_hue + hue_thresh, 255, 255), yellow);
        cv::inRange(hsv_frame, cv::Scalar(blue_hue - hue_thresh, min_sat, min_val), cv::Scalar(blue_hue + hue_thresh, 255, 255), blue);

        cv::bitwise_or(red_lower, red_upper, red);

        this->morph(red);
        this->morph(yellow);
        this->morph(blue);

        cv::Moments red_moments = cv::moments(red),
                    yellow_moments = cv::moments(yellow),
                    blue_moments = cv::moments(blue);

        this->embed_msg(red_moments, interfaces::msg::Object::RED);
        this->embed_msg(yellow_moments, interfaces::msg::Object::YELLOW);
        this->embed_msg(blue_moments, interfaces::msg::Object::BLUE);

#ifdef DEBUG
        cv::imshow("red", red);
        cv::imshow("yellow", yellow);
        cv::imshow("blue", blue);
#endif

        cv::waitKey(1);
    }

    rclcpp::Publisher<interfaces::msg::Object>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    cv::VideoCapture cap_;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    int red_hue = 0, yellow_hue = 30, blue_hue = 120,
        hue_thresh = 10, min_sat = 150, min_val = 50, min_area = 10000;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Camera>());
    rclcpp::shutdown();
    return 0;
}