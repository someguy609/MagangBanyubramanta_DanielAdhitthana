#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <asio.hpp>
#include <cstdint>

#include "rclcpp/rclcpp.hpp"
#include "interfaces/msg/motion.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

#define PORT "/dev/ttyACM0"

class Communicator : public rclcpp::Node
{
public:
	Communicator() : Node("communicator"), port_(asio::serial_port(io_, PORT))
	{
		port_.set_option(asio::serial_port_base::baud_rate(115200));
		port_.set_option(asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::software));
		port_.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::none));
		port_.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));
		port_.set_option(asio::serial_port_base::character_size(8));

		subscriber_ = this->create_subscription<interfaces::msg::Motion>("motion_command", 10, std::bind(&Communicator::topic_callback, this, _1));
	}

private:
	void encode(uint8_t *dest, uint8_t idx, int val)
	{
		int sign = val < 0;
		val *= sign ? -1 : 1;
		dest[0] |= (val >> 8) + sign * 2 << (2 * idx);
		dest[idx + 1] = val & 0xFF;
	}

	void topic_callback(const interfaces::msg::Motion &message)
	{
		uint8_t buff[5];

		encode(buff, 0, message.x_cmd);
		encode(buff, 1, message.y_cmd);
		encode(buff, 2, message.yaw);
		encode(buff, 3, message.depth);

		RCLCPP_INFO(this->get_logger(), "Sending motion commands");
		asio::write(port_, asio::buffer(buff));
	}

	rclcpp::Subscription<interfaces::msg::Motion>::SharedPtr subscriber_;
	asio::io_service io_;
	asio::serial_port port_;
};

int main(int argc, char *argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<Communicator>());
	rclcpp::shutdown();
	return 0;
}