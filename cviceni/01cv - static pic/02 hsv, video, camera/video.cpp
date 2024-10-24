// icp.cpp 
// Author: JJ

// C++ 
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdexcept>
#include <ctime>

cv::VideoCapture capture;

//=====================================================================================================

enum Keys {
    KEY_ESC = 27,
    KEY_ENTER = 13,
    KEY_SPACE = 32,
    KEY_UP = 2490368,
    KEY_DOWN = 2621440,
    KEY_LEFT = 2424832,
    KEY_RIGHT = 2555904
} my_key_t;

static void init(void)
{
    capture = cv::VideoCapture("video.mkv");

    if (!capture.isOpened())
    {
        std::cerr << "no camera" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Camera " <<
            ": width=" << capture.get(cv::CAP_PROP_FRAME_WIDTH) <<
            ", height=" << capture.get(cv::CAP_PROP_FRAME_HEIGHT) <<
            std::endl;
    }
}

/*
Find the center of white area in the image.
*/
void find_center(cv::Mat& img, cv::Point& center)
{
    cv::Moments m = cv::moments(img, true);
    center.x = m.m10 / m.m00;
    center.y = m.m01 / m.m00;
}

int main(int argc, char * argv[]) {
    cv::Mat frame, scene, eroded, dilated;
    double h_low = 150.0;
    double s_low = 128.0;
    double v_low = 128.0;
    double h_hi = 255.0;
    double s_hi = 255.0;
    double v_hi = 255.0;

    init();

    // Create a structuring element for dilation and erosion
    int erosion_size = 2;
    int dilation_size = 3;

    cv::Mat dilation_element = cv::getStructuringElement(cv::MORPH_RECT,
                                        cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                        cv::Point(dilation_size, dilation_size));

    cv::Mat erosion_element = cv::getStructuringElement(cv::MORPH_RECT,
                                                cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
                                                cv::Point(erosion_size, erosion_size));

    // green color
    cv::Scalar green = cv::Scalar(0, 255, 0);
    int thickness = 2;
    int rectangle_x_size = 15;
    int rectangle_y_size = 20;

    while (1) {
        capture.read(frame);
        if (frame.empty()) {
            std::cerr << "Cam disconnected?" << std::endl;
            break;
        }


        // analyze the image
        cv::Mat scene_hsv, scene_threshold;

        cv::cvtColor(frame, scene_hsv, cv::COLOR_BGR2HSV);

        cv::Scalar lower_threshold = cv::Scalar(h_low, s_low, v_low);
        cv::Scalar upper_threshold = cv::Scalar(h_hi, s_hi, v_hi);
        cv::inRange(scene_hsv, lower_threshold, upper_threshold, scene_threshold);
        //cv::imshow("threshold", scene_threshold);

        // Apply erosion
        cv::erode(scene_threshold, eroded, erosion_element);

        // Apply dilation
        cv::dilate(eroded, dilated, dilation_element);

        // find center
        cv::Point center;
        find_center(dilated, center);
        std::cout << "Center absolute: " << center << '\n';
        // add rectangle
        cv::Point left_top(center.x - rectangle_x_size, center.y - rectangle_y_size);
        cv::Point right_bottom(center.x + rectangle_x_size, center.y + rectangle_y_size);
        cv::rectangle(frame, left_top, right_bottom, green, thickness);

        // Display the resulting frame
        cv::imshow("grabbed", frame);
        cv::imshow("threshold", dilated);

        if (cv::waitKey(1) == KEY_ESC) {
            break;
        }
        
        // wait 1s
        int wait_time = 500;
        if (cv::waitKey(wait_time) == KEY_RIGHT) {
            continue;
        }
    }

    if (capture.isOpened())
        capture.release();

    exit(EXIT_SUCCESS);
}

