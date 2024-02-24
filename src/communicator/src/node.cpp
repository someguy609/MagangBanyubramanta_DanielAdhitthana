#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <asio.hpp>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

class Communicator : public rclcpp::Node
{
public:
    Communicator() : Node("communicator")
    {
        timer_ = this->create_wall_timer(
            500ms, std::bind(&Communicator::timer_callback, this));
    }

private:
    void timer_callback()
    {
    }

    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Communicator>());
    rclcpp::shutdown();
    return 0;
}