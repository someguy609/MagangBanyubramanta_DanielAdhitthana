#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "interfaces/msg/motion.hpp"

using std::placeholders::_1;

#define MOVEMENT_SPEED_DIFF 0.01
#define MIN_MOVEMENT_SPEED 0.2
#define MAX_MOVEMENT_SPEED 1
#define MIN_YAW_SPEED 5
#define MAX_YAW_SPEED 50
#define MIN_DEPTH_SPEED 5
#define MAX_DEPTH_SPEED 20
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
		movement_speed += (msg.buttons[LB] && movement_speed < MAX_MOVEMENT_SPEED) - (msg.buttons[RB] && movement_speed > MIN_MOVEMENT_SPEED);
		yaw_speed += (msg.buttons[X] && yaw_speed < MAX_YAW_SPEED) - (msg.buttons[B] && yaw_speed > MIN_YAW_SPEED);
		depth_speed += (msg.buttons[Y] && depth_speed < MAX_DEPTH_SPEED) - (msg.buttons[A] && depth_speed > MIN_DEPTH_SPEED);

		yaw += ((msg.axes[LR_RIGHT] < 0) - (msg.axes[LR_RIGHT] > 0)) * yaw_speed;
		yaw += (yaw > 180 ? -360 : yaw < -180 ? 360
											  : 0);

		depth += ((msg.axes[UD_RIGHT] < 0) - (msg.axes[UD_RIGHT] > 0)) * depth_speed;
		depth = MIN(MAX(depth, 0), 100);

		auto data = interfaces::msg::Motion();
		data.x_cmd = msg.axes[LR_LEFT] * -MAX_VALUE * movement_speed;
		data.y_cmd = msg.axes[UD_LEFT] * MAX_VALUE * movement_speed;
		data.yaw = yaw;
		data.depth = depth;

		publisher_->publish(data);
	}

	rclcpp::Publisher<interfaces::msg::Motion>::SharedPtr publisher_;
	rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscriber_;
	int yaw = 0, depth = 0, yaw_speed = MIN_YAW_SPEED, depth_speed = MIN_DEPTH_SPEED;
	double movement_speed = 1;
};

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<Controller>());
	rclcpp::shutdown();
	return 0;
}