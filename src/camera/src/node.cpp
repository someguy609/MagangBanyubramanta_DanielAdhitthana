#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"
#include "camera/msg/object.hpp"

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
                return;
            }

            // deteksi disini

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
    // rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Camera>());
    rclcpp::shutdown();
    return 0;
}