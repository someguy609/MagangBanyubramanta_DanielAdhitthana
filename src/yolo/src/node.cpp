#include <chrono>
#include <functional>
#include <memory>
#include <map>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "cv_bridge/cv_bridge.h"
#include "sensor_msgs/msg/image.hpp"
#include "opencv2/opencv.hpp"
#include "interfaces/msg/gate.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

#define INPUT_WIDTH 640
#define INPUT_HEIGHT 640
#define DEBUG

struct Detection
{
	int cls;
	float x, y, w, h, conf;
};

class YOLO : public rclcpp::Node
{
public:
	YOLO() : Node("YOLO")
	{
		publisher_ = this->create_publisher<interfaces::msg::Gate>("detected_object", 10);
		cap_ = this->create_subscription<sensor_msgs::msg::Image>("capture", 10, std::bind(&YOLO::topic_callback, this, _1));

		net_ = cv::dnn::readNet("src/yolo/src/best.onnx");

#ifdef DEBUG
		cv::namedWindow("values");
		cv::createTrackbar("score", "values", &score_thresh, 100);
		cv::createTrackbar("conf", "values", &conf_thresh, 100);
		cv::createTrackbar("nms", "values", &nms_thresh, 100);
#endif
	}

	~YOLO()
	{
		cv::destroyAllWindows();
	}

private:
	void preprocess(cv::Mat &frame)
	{
		x_fact = float(frame.cols) / float(INPUT_WIDTH);
		y_fact = float(frame.rows) / float(INPUT_HEIGHT);

		cv::resize(frame, frame, cv::Size(INPUT_WIDTH, INPUT_HEIGHT));

		cv::Mat blob;
		cv::dnn::blobFromImage(frame, blob, 1. / 255., cv::Size(INPUT_WIDTH, INPUT_HEIGHT), cv::Scalar(), true, false, CV_32FC1);
		net_.setInput(blob);
	}

	void postprocess(cv::Mat &frame)
	{
		std::vector<cv::Mat> results;
		net_.forward(results, net_.getUnconnectedOutLayersNames());

		std::vector<float> confidences;
		std::vector<cv::Rect> boxes;
		std::vector<Detection> detections;

		cv::Mat data = results[0];

		for (int i = 0; i < data.size[1]; i++)
		{
			float *detection = data.ptr<float>(0, i);
			float conf = detection[4];

			if (conf < conf_thresh / 100.)
				continue;

			float *class_scores = detection + 5;
			cv::Mat scores(1, data.size[2] - 5, CV_32FC1, class_scores);
			cv::Point class_id;
			double max_score;
			cv::minMaxLoc(scores, 0, &max_score, 0, &class_id);

			if (max_score < score_thresh / 100.)
				continue;

			Detection d;
			d.cls = class_id.x;
			d.conf = conf;
			d.x = detection[0] * x_fact,
			d.y = detection[1] * y_fact,
			d.w = detection[2] * x_fact,
			d.h = detection[3] * y_fact;

			detections.push_back(d);
			confidences.push_back(conf);
			boxes.push_back(cv::Rect(d.x - (d.w / 2.), d.y - (d.h / 2.), d.w, d.h));
		}

		std::vector<int> indices;
		cv::dnn::NMSBoxes(boxes, confidences, score_thresh / 100., nms_thresh / 100., indices);

#ifdef DEBUG
		RCLCPP_INFO(this->get_logger(), "Detected %ld objects", indices.size());
#endif

		for (long unsigned int i = 0; i < indices.size(); i++)
		{
			int idx = indices[i];
			auto message = interfaces::msg::Gate();

			message.x = detections[idx].x;
			message.y = detections[idx].y;
			message.w = detections[idx].w;
			message.h = detections[idx].h;

			publisher_->publish(message);

#ifdef DEBUG
			std::string label = class_names[detections[idx].cls];

			cv::Point2i top_left = boxes[idx].tl();
			int base_line;
			cv::Size label_size = cv::getTextSize(label, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &base_line);

			cv::rectangle(frame, boxes[idx], cv::Scalar(0, 0, 255));
			cv::rectangle(frame, top_left, cv::Point(label_size.width, top_left.y + base_line), cv::Scalar(0, 0, 255), -1);
			cv::putText(frame, label, top_left, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255));
			cv::resize(frame, frame, cv::Size(0, 0), x_fact, y_fact);
#endif
		}
	}

	void topic_callback(const sensor_msgs::msg::Image &sensor_img)
	{
		cv_bridge::CvImagePtr cv_img = cv_bridge::toCvCopy(sensor_img);
		cv::Mat frame = cv_img->image;

		if (frame.empty())
		{
			RCLCPP_ERROR(this->get_logger(), "Failed to read frame");
			return;
		}

		preprocess(frame);
		postprocess(frame);

#ifdef DEBUG
		cv::imshow("frame", frame);
		cv::waitKey(1);
#endif
	}

	rclcpp::Publisher<interfaces::msg::Gate>::SharedPtr publisher_;
	rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr cap_;
	cv::dnn::Net net_;
	int score_thresh = 20, conf_thresh = 40, nms_thresh = 40;
	float x_fact, y_fact;
	const std::vector<std::string> class_names = {"mouse"};
};

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<YOLO>());
	rclcpp::shutdown();
	return 0;
}