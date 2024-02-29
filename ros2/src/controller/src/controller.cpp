#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "interfaces/msg/motion.hpp"

using std::placeholders::_1;

#define SPEED 5
#define MAX_VALUE 500
#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)

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
		publisher_ = this->create_publisher<interfaces::msg::Motion>("motion_command", 10);
		subscriber_ = this->create_subscription<sensor_msgs::msg::Joy>(
			"joy", 10, std::bind(&Controller::topic_callback, this, _1));
	}

private:
	void topic_callback(const sensor_msgs::msg::Joy &msg)
	{
		yaw += ((msg.axes[LR_RIGHT] < 0) - (msg.axes[LR_RIGHT] > 0) * SPEED);
		yaw += (yaw > 180 ? -360 : yaw < -180 ? 360
											  : 0);

		depth += ((msg.axes[UD_RIGHT] < 0) - (msg.axes[UD_RIGHT] > 0) * SPEED);
		depth = MIN(MAX(depth, 0), 100);

		auto data = interfaces::msg::Motion();
		data.x_cmd = msg.axes[LR_LEFT] * -MAX_VALUE;
		data.y_cmd = msg.axes[UD_LEFT] * MAX_VALUE;
		data.yaw = yaw;
		data.depth = depth;

		publisher_->publish(data);
	}
	rclcpp::Publisher<interfaces::msg::Motion>::SharedPtr publisher_;
	rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscriber_;
	int yaw = 0, depth = 0;
	int left = 0;
};

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<Controller>());
	rclcpp::shutdown();
	return 0;
}