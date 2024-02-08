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
#define YELLOW 60
#define BLUE 230
#define HUE_THRESHOLD 50
#define MIN_SATURATION 50
#define MIN_VALUE 50

using namespace std::chrono_literals;
using std::placeholders::_1;

class Camera : public rclcpp::Node
{
public:
    Camera() : Node("camera")
    {
        publisher_ = this->create_publisher<camera::msg::Object>("detected_object", 10);
        cap_ = cv::VideoCapture(0);

        if (!cap_.isOpened())
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to open video capture");
            return;
        }

        while (cap_.isOpened())
        {
            cv::Mat frame;

            if (!cap_.read(frame))
            {
                RCLCPP_ERROR(this->get_logger(), "Failed to read frame");
                break;
            }

            cv::Mat hsv_frame;
            cv::cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);

            if (hsv_frame.empty())
            {
                RCLCPP_ERROR(this->get_logger(), "Failed to convert frame to HSV");
                break;
            }

            cv::Mat red, yellow, blue;
            cv::inRange(hsv_frame, cv::Scalar(std::max(0, RED - HUE_THRESHOLD), MIN_SATURATION, MIN_VALUE), cv::Scalar(std::min(255, RED + HUE_THRESHOLD), 255, 255), red);
            cv::inRange(hsv_frame, cv::Scalar(std::max(0, YELLOW - HUE_THRESHOLD), MIN_SATURATION, MIN_VALUE), cv::Scalar(std::min(255, YELLOW + HUE_THRESHOLD), 255, 255), yellow);
            cv::inRange(hsv_frame, cv::Scalar(std::max(0, BLUE - HUE_THRESHOLD), MIN_SATURATION, MIN_VALUE), cv::Scalar(std::min(255, BLUE + HUE_THRESHOLD), 255, 255), blue);

            auto message = camera::msg::Object();
            message.red = !red.empty();
            message.yellow = !yellow.empty();
            message.blue = !blue.empty();

            publisher_->publish(message);

            int key = cv::waitKey(0);
            if (key == 'q')
            {
                RCLCPP_INFO(this->get_logger(), "Understandable, have a nice day :)");
                break;
            }
        }

        cap_.release();
        cv::destroyAllWindows();
    }

private:
    rclcpp::Publisher<camera::msg::Object>::SharedPtr publisher_;
    cv::VideoCapture cap_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Camera>());
    rclcpp::shutdown();
    return 0;
}