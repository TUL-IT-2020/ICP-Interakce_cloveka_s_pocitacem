// icp.cpp 
// Author: JJ

// C++ 
#include <iostream>
#include <chrono>
#include <stack>
#include <random>
#include <numeric>

// OpenCV 
#include <opencv2\opencv.hpp>


void draw_cross_relative(cv::Mat& img, const cv::Point2f center_relative, const int size)
{
	cv::Point p;
	p.x = center_relative.x * img.cols;
	p.y = center_relative.y * img.rows;

	cv::Point p1 = cv::Point(p.x - size / 2, p.y);
	cv::Point p2 = cv::Point(p.x + size / 2, p.y);
	cv::Point p3 = cv::Point(p.x, p.y - size / 2);
	cv::Point p4 = cv::Point(p.x, p.y + size / 2);

	cv::line(img, p1, p2, CV_RGB(255, 0, 0), 3);
	cv::line(img, p3, p4, CV_RGB(255, 0, 0), 3);
}

cv::Point2f centroid_nonzero(cv::Mat& scene, cv::Scalar& lower_threshold, cv::Scalar& upper_threshold)
{
	cv::Mat scene_hsv;
	cv::cvtColor(scene, scene_hsv, cv::COLOR_BGR2HSV);

	cv::Mat scene_threshold;
	cv::inRange(scene_hsv, lower_threshold, upper_threshold, scene_threshold);

	cv::namedWindow("scene_threshold", 0);
	cv::imshow("scene_threshold", scene_threshold);

	std::vector<cv::Point> whitePixels;
	cv::findNonZero(scene_threshold, whitePixels);
	int whiteCnt = whitePixels.size();

	cv::Point whiteAccum = std::accumulate(whitePixels.begin(), whitePixels.end(), cv::Point(0.0, 0.0));

	cv::Point2f centroid_relative(0.0f, 0.0f);
	if (whiteCnt > 0)
	{
		cv::Point centroid = { whiteAccum.x / whiteCnt, whiteAccum.y / whiteCnt };
		centroid_relative = { static_cast<float>(centroid.x) / scene.cols, static_cast<float>(centroid.y) / scene.rows };
	}

	return centroid_relative;
}
//---------------------------------------------------------------------
// MAIN
//---------------------------------------------------------------------
int main(int argc, char* argv[])
{
	// load image
//	cv::Mat scene = cv::imread("resources/lightbulb.jpg"); //can be JPG,PNG,GIF,TIFF,...
	//cv::Mat scene = cv::imread("resources/sunset.webp"); //can be JPG,PNG,GIF,TIFF,...
	cv::Mat scene = cv::imread("resources/hsv-map.png"); //can be JPG,PNG,GIF,TIFF,...

	if (scene.empty())
	{
		std::cerr << "not found" << std::endl;
		exit(EXIT_FAILURE);
	}


	cv::namedWindow("scene", 0);
	cv::imshow("scene", scene);

	int hm = 0, sm = 0, vm = 0, hx = 179, sx = 255, vx = 255;
	cv::createTrackbar("HMin", "scene", &hm, 179);
	cv::createTrackbar("SMin", "scene", &sm, 255);
	cv::createTrackbar("VMin", "scene", &vm, 255);
	cv::createTrackbar("HMax", "scene", &hx, 179);
	cv::createTrackbar("SMax", "scene", &sx, 255);
	cv::createTrackbar("VMax", "scene", &vx, 255);

	cv::Scalar lower_threshold;
	cv::Scalar upper_threshold;
	do {
		// Get current positions of trackbars
		// HSV ranges between (0-179, 0-255, 0-255).
		lower_threshold = cv::Scalar(
			cv::getTrackbarPos("HMin", "scene"),
			cv::getTrackbarPos("SMin", "scene"),
			cv::getTrackbarPos("VMin", "scene"));

		upper_threshold = cv::Scalar(
			cv::getTrackbarPos("HMax", "scene"),
			cv::getTrackbarPos("SMax", "scene"),
			cv::getTrackbarPos("VMax", "scene"));

		// compute centroid 
		auto start = std::chrono::system_clock::now();
		auto centroid = centroid_nonzero(scene, lower_threshold, upper_threshold);
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::cout << "elapsed time: " << elapsed_seconds.count() << " sec" << std::endl;
		std::cout << "found relative: " << centroid << std::endl;

		//display result
		cv::Mat scene_cross;
		scene.copyTo(scene_cross);
		draw_cross_relative(scene_cross, centroid, 30);
		cv::imshow("scene", scene_cross);

		
	} while (cv::waitKey(1) != 27); //message loop with 1ms delay untill ESC

	exit(EXIT_SUCCESS);
}
