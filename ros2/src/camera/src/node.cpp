#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"
#include "std_msgs/msg/header.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "interfaces/msg/object.hpp"

#define DEBUG

using namespace std::chrono_literals;
using std::placeholders::_1;

class Camera : public rclcpp::Node
{
public:
    Camera() : Node("camera")
    {
        timer_ = this->create_wall_timer(10ms, std::bind(&Camera::timer_callback, this));
        object_publisher_ = this->create_publisher<interfaces::msg::Object>("detected_object", 10);
        img_publisher_ = this->create_publisher<sensor_msgs::msg::Image>("capture", 10);
        cap_ = cv::VideoCapture(0);

#ifdef DEBUG
        cv::namedWindow("values");
        cv::createTrackbar("hue thresh", "values", &hue_thresh, 90);
        cv::createTrackbar("sat thresh", "values", &sat_thresh, 255);
        cv::createTrackbar("val thresh", "values", &val_thresh, 255);
        cv::createTrackbar("min area", "values", &min_area, 10000);
        cv::createTrackbar("red hue", "values", &red_hue, 179);
        cv::createTrackbar("red sat", "values", &red_sat, 255);
        cv::createTrackbar("red val", "values", &red_val, 255);
        cv::createTrackbar("yellow hue", "values", &yellow_hue, 179);
        cv::createTrackbar("yellow sat", "values", &yellow_sat, 255);
        cv::createTrackbar("yellow val", "values", &yellow_val, 255);
        cv::createTrackbar("blue hue", "values", &blue_hue, 179);
        cv::createTrackbar("blue sat", "values", &blue_sat, 255);
        cv::createTrackbar("blue val", "values", &blue_val, 255);
#endif
    }

    ~Camera()
    {
        cap_.release();
        cv::destroyAllWindows();
    }

private:
    void publish_img(const cv::Mat &frame)
    {
        auto message = cv_bridge::CvImage();
        message.header = std_msgs::msg::Header();
        message.header.frame_id = std::to_string(frame_id++);
        message.header.stamp = now();
        message.encoding = "bgr8";
        message.image = frame;

        img_publisher_->publish(*message.toImageMsg());
    }

    void morph(cv::Mat &frame)
    {
        cv::morphologyEx(frame, frame, cv::MORPH_OPEN, kernel);
        cv::morphologyEx(frame, frame, cv::MORPH_CLOSE, kernel);
    }

    cv::Point find_center(cv::Mat &binary, cv::Mat &original, cv::Scalar color = cv::Scalar(255, 255, 255))
    {
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::Point center_point;
        findContours(binary, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        for (size_t i = 0; i < contours.size(); i++)
        {
            if (cv::contourArea(contours[i]) < min_area)
                continue;

            cv::Rect bbox = boundingRect(contours[i]);
            center_point.x = bbox.x + bbox.width / 2;
            center_point.y = bbox.y + bbox.height / 2;

#ifdef DEBUG
            cv::rectangle(original, bbox, color);
#endif
        }

        return center_point;
    }

    void embed_msg(cv::Mat &frame, cv::Mat &original, const int color)
    {
        int red = color == interfaces::msg::Object::RED;
        int yellow = color == interfaces::msg::Object::YELLOW;
        int blue = color == interfaces::msg::Object::BLUE;
        cv::Point center = find_center(frame, original, 255 * cv::Scalar(blue, yellow, red || yellow));

        auto message = interfaces::msg::Object();
        message.type = color;
        message.x = center.x;
        message.y = center.y;

        object_publisher_->publish(message);
    }

    void timer_callback()
    {
        if (!cap_.isOpened())
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to open video capture");
            return;
        }

        cv::Mat frame;

        if (!cap_.read(frame))
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to read frame");
            return;
        }

        publish_img(frame);

        cv::Mat hsv_frame;
        cv::cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);

        if (hsv_frame.empty())
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to convert frame to HSV");
            return;
        }

        cv::Mat red_lower, red_upper, red, yellow, blue;
        cv::inRange(hsv_frame, cv::Scalar(red_hue - hue_thresh, red_sat, red_val), cv::Scalar(red_hue + hue_thresh, 255, 255), red_lower);
        cv::inRange(hsv_frame, cv::Scalar(180 - red_hue - hue_thresh, red_sat, red_val), cv::Scalar(180 - red_hue + hue_thresh, 255, 255), red_upper);
        cv::inRange(hsv_frame, cv::Scalar(yellow_hue - hue_thresh, yellow_sat, yellow_val), cv::Scalar(yellow_hue + hue_thresh, 255, 255), yellow);
        cv::inRange(hsv_frame, cv::Scalar(blue_hue - hue_thresh, blue_sat, blue_val), cv::Scalar(blue_hue + hue_thresh, 255, 255), blue);

        cv::bitwise_or(red_lower, red_upper, red);

        this->morph(red);
        this->morph(yellow);
        this->morph(blue);

        this->embed_msg(red, frame, interfaces::msg::Object::RED);
        this->embed_msg(yellow, frame, interfaces::msg::Object::YELLOW);
        this->embed_msg(blue, frame, interfaces::msg::Object::BLUE);

#ifdef DEBUG
        cv::imshow("red", red);
        cv::imshow("yellow", yellow);
        cv::imshow("blue", blue);
        cv::imshow("frame", frame);
#endif

        cv::waitKey(1);
    }

    rclcpp::Publisher<interfaces::msg::Object>::SharedPtr object_publisher_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr img_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    cv::VideoCapture cap_;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    int red_hue = 0, yellow_hue = 30, blue_hue = 120, hue_thresh = 10,
        red_sat = 150, yellow_sat = 150, blue_sat = 150, sat_thresh = 10,
        red_val = 50, yellow_val = 50, blue_val = 50, val_thresh = 10,
        min_area = 10000;
    unsigned long long int frame_id = 0;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Camera>());
    rclcpp::shutdown();
    return 0;
}