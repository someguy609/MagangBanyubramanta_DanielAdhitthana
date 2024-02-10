#include <algorithm>
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"
#include "camera/msg/object.hpp"

#define RED 0
#define YELLOW 30
#define BLUE 120
#define HUE_THRESHOLD 20
#define MIN_SATURATION 50
#define MIN_VALUE 50

#define DEBUG

using namespace std::chrono_literals;
using std::placeholders::_1;

class Camera : public rclcpp::Node
{
public:
    Camera() : Node("camera")
    {
        timer_ = this->create_wall_timer(500ms, std::bind(&Camera::topic_callback, this));
        publisher_ = this->create_publisher<camera::msg::Object>("detected_object", 10);
        cap_ = cv::VideoCapture(0);

        if (!cap_.isOpened())
            RCLCPP_ERROR(this->get_logger(), "Failed to open video capture");
    }

    ~Camera()
    {
        cap_.release();
        cv::destroyAllWindows();
    }

private:
    void topic_callback()
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

        // denoising ???

        // cv::Mat opening,
        //     opening_kernel = cv::getStructuringElement(cv::MORPH_RECT,
        //                                                cv::Size(5, 5),
        //                                                cv::Point(2, 2));
        // cv::morphologyEx(frame, opening, cv::MORPH_OPEN);

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
        cv::inRange(hsv_frame, cv::Scalar(RED - HUE_THRESHOLD, MIN_SATURATION, MIN_VALUE), cv::Scalar(RED + HUE_THRESHOLD, 255, 255), red);
        cv::inRange(hsv_frame, cv::Scalar(YELLOW - HUE_THRESHOLD, MIN_SATURATION, MIN_VALUE), cv::Scalar(YELLOW + HUE_THRESHOLD, 255, 255), yellow);
        cv::inRange(hsv_frame, cv::Scalar(BLUE - HUE_THRESHOLD, MIN_SATURATION, MIN_VALUE), cv::Scalar(BLUE + HUE_THRESHOLD, 255, 255), blue);

        auto message = camera::msg::Object();
        message.red = cv::countNonZero(red) > 0;
        message.yellow = cv::countNonZero(yellow) > 0;
        message.blue = cv::countNonZero(blue) > 0;

        publisher_->publish(message);
    }

    rclcpp::Publisher<camera::msg::Object>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    cv::VideoCapture cap_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Camera>());
    rclcpp::shutdown();
    return 0;
}