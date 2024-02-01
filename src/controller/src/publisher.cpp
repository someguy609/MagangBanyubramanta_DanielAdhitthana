#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"

class Controller : public rclcpp::Node
{
public:
    Controller() : Node("controller")
    {
        publisher_ = this->create_publisher<sensor_msgs::msg::Joy>("topic", 10);
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(500),
            std::bind(&Controller::timer_callback, this));
    }

private:
    void timer_callback()
    {
        auto message = sensor_msgs::msg::Joy();
        publisher_->publish(message);
        RCLCPP_INFO(this->get_logger(), "e");
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<sensor_msgs::msg::Joy>::SharedPtr publisher_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Controller>());
    rclcpp::shutdown();
    return 0;
}