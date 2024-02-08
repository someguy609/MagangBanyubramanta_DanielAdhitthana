#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "controller/msg/motion.hpp"

using std::placeholders::_1;

#define MAX_VALUE 500

/**
 * Wired Linux XBox Controller
 * http://wiki.ros.org/joy
 */

enum Buttons
{
	A,
	B,
	X,
	Y,
	LB,
	RB,
	BACK,
	START,
	POWER,
	LEFT_STICK,
	RIGHT_STICK
};

enum Axes
{
	LR_LEFT,
	UD_LEFT,
	LT,
	LR_RIGHT,
	UD_RIGHT,
	RT,
	LR_CROSS,
	UD_CROSS
};

class Controller : public rclcpp::Node
{
public:
	Controller() : Node("controller")
	{
		publisher_ = this->create_publisher<controller::msg::Motion>("motion_command", 10);
		subscriber_ = this->create_subscription<sensor_msgs::msg::Joy>(
			"joy", 10, std::bind(&Controller::topic_callback, this, _1));
	}

private:
	void topic_callback(const sensor_msgs::msg::Joy &msg)
	{
		auto data = controller::msg::Motion();
		data.x_cmd = msg.axes[LR_LEFT] * MAX_VALUE;
		data.y_cmd = msg.axes[UD_LEFT] * MAX_VALUE;
		data.yaw = msg.axes[LR_RIGHT] * MAX_VALUE;
		data.depth = msg.axes[UD_RIGHT] * MAX_VALUE;

		publisher_->publish(data);
		RCLCPP_INFO(this->get_logger(), "Published motion commands");
	}
	rclcpp::Publisher<controller::msg::Motion>::SharedPtr publisher_;
	rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscriber_;
};

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<Controller>());
	rclcpp::shutdown();
	return 0;
}