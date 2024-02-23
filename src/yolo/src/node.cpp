#include <chrono>
#include <functional>
#include <memory>
#include <map>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "opencv2/opencv.hpp"
#include "interfaces/msg/gate.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

#define INPUT_WIDTH 640
#define INPUT_HEIGHT 640
#define DIMENSIONS 85
#define ROWS 25200
#define SCORE_THRESH 0.2
#define CONF_THRESH 0.1
#define NMS_THRESH 0.4
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
		timer_ = this->create_wall_timer(100ms, std::bind(&YOLO::timer_callback, this));
		publisher_ = this->create_publisher<interfaces::msg::Gate>("detected_object", 10);
		cap_ = cv::VideoCapture(0);

		if (!cap_.isOpened())
		{
			RCLCPP_ERROR(this->get_logger(), "Failed to open camera");
			return;
		}

		net_ = cv::dnn::readNet("src/yolo/src/best.onnx");
	}

	~YOLO()
	{
		cap_.release();
		cv::destroyAllWindows();
	}

private:
	void preprocess(cv::Mat &frame)
	{

		cv::resize(frame, frame, cv::Size(INPUT_WIDTH, INPUT_HEIGHT));

		cv::Mat blob;
		cv::dnn::blobFromImage(frame, blob, 1. / 255., cv::Size(INPUT_WIDTH, INPUT_HEIGHT), cv::Scalar(), true, false, CV_32FC1);
		net_.setInput(blob);
	}

	void postprocess(cv::Mat &frame)
	{
		std::vector<cv::Mat> detections;
		net_.forward(detections, net_.getUnconnectedOutLayersNames());

		// float x_fact = frame.cols / INPUT_WIDTH,
		// 	  y_fact = frame.rows / INPUT_HEIGHT;
		std::vector<float> confidences, x, y, w, h;
		std::vector<cv::Rect> boxes;

		cv::Mat results = detections[0];

		for (int i = 0; i < results.size[1]; i++)
		{
			float *detection = results.ptr<float>(0, i);
			float conf = detection[4];

			if (conf < CONF_THRESH)
				continue;

			float *class_scores = detection + 5;
			cv::Mat scores(1, results.size[2] - 5, CV_32FC1, class_scores);
			cv::Point class_id;
			double max_score;
			cv::minMaxLoc(scores, 0, &max_score, 0, &class_id);

			if (max_score < SCORE_THRESH)
				continue;

			float x_ = detection[0],
				  y_ = detection[1],
				  w_ = detection[2],
				  h_ = detection[3];

			confidences.push_back(conf);
			x.push_back(x_);
			y.push_back(y_);
			w.push_back(w_);
			h.push_back(h_);
			boxes.push_back(cv::Rect(x_ - (w_ / 2.), y_ - (h_ / 2.), w_, h_));
		}

		std::vector<int> indices;
		cv::dnn::NMSBoxes(boxes, confidences, SCORE_THRESH, NMS_THRESH, indices);

#ifdef DEBUG
		RCLCPP_INFO(this->get_logger(), "Detected %ld objects", indices.size());
#endif

		for (long unsigned int i = 0; i < indices.size(); i++)
		{
			int idx = indices[i];
			auto message = interfaces::msg::Gate();

			message.x = x[idx];
			message.y = y[idx];
			message.w = w[idx];
			message.h = h[idx];

			publisher_->publish(message);

#ifdef DEBUG
			cv::rectangle(frame, boxes[idx], cv::Scalar(0, 0, 255));
#endif
		}
	}

	void timer_callback()
	{
		cv::Mat frame;

		if (!cap_.read(frame))
		{
			RCLCPP_ERROR(this->get_logger(), "Failed to read frame");
			return;
		}

		preprocess(frame);
		postprocess(frame);

#ifdef DEBUG
		cv::imshow("frame", frame);
#endif

		cv::waitKey(1);
	}

	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Publisher<interfaces::msg::Gate>::SharedPtr publisher_;
	cv::VideoCapture cap_;
	cv::dnn::Net net_;
	const std::vector<std::string> class_names = {"mouse"};
};

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<YOLO>());
	rclcpp::shutdown();
	return 0;
}