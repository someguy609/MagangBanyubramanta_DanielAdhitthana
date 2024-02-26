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
	void encode(uint8_t *dest, int value)
	{
		int neg = value < 0;
		value *= neg ? -1 : 1;
		dest[0] = (value >> 8) + neg * 2;
		dest[1] = value & 0xFF;
	}

	int decode(uint8_t *src)
	{
		int top = src[0];
		int bottom = src[1];

		int neg = top > 1;
		top -= neg * 2;

		int value = ((top & 0x7F) << 8) | bottom;
		if (neg)
			value *= -1;

		return value;
	}

	void topic_callback(const interfaces::msg::Motion &message)
	{
		uint8_t buff[8];

		encode(buff, message.x_cmd);
		encode(buff + 2, message.y_cmd);
		encode(buff + 4, message.yaw);
		encode(buff + 6, message.depth);

		RCLCPP_INFO(this->get_logger(), "Sending \"%s\"", buff);
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