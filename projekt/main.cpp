// main.cpp 
// By Pytel

// C++ 
#include <iostream>
#include <stdexcept>
#include <numeric>
#include <random>
#include <thread>

// OpenCV 
#include <opencv2/opencv.hpp>

// load clasifier
class App {
public:
	App();
	~App();

	// public methods
	int init(void);
	int run(void);

	// static methods
	cv::Point2f find_face(cv::Mat & frame);
	void draw_cross_relative(cv::Mat& img, cv::Point2f center_relative, int size);

private:
    cv::VideoCapture capture;
    cv::CascadeClassifier face_cascade; // Face cascade classifier
};
//-----------------------------------------------------------------------

App::App() {
	// Initialize the face cascade classifier with the appropriate file
	std::string face_cascade_name = "resources/haarcascade_frontalface_default.xml";
    if (!face_cascade.load(face_cascade_name)) {
        std::cerr << "Error loading face cascade\n";
        exit(EXIT_FAILURE);
    }
}

int App::init(void){
    //open capture device
    //open first available camera
#ifdef _WIN32
    // Windows
    capture = cv::VideoCapture(cv::CAP_DSHOW);
#elif __linux__
    // Linux
    capture = cv::VideoCapture(0, cv::CAP_V4L2);
#else
    // Other OS (macOS, etc.)
    capture = cv::VideoCapture(0);
#endif
    
    //open video file
    //capture = cv::VideoCapture("video.mkv");

    if (!capture.isOpened()) { 
        std::cerr << "no source?" << std::endl;
        return false;
    } else {
        std::cout << "Source: " << 
            ": width=" << capture.get(cv::CAP_PROP_FRAME_WIDTH) <<
            ", height=" << capture.get(cv::CAP_PROP_FRAME_HEIGHT) << '\n';
    }
    return true;
}

int App::run() {

	cv::Mat frame; // for captured frame 
	do {
		capture.read(frame);
		if (frame.empty())
		{
			std::cerr << "Cam disconnected? End of video?" << std::endl;
			return -1;
		}

		// find face
        cv::Point2f center = find_face(frame); 

		//display result
		cv::Mat scene_cross;
		frame.copyTo(scene_cross);
        draw_cross_relative(scene_cross, center, 30); // use "center" coordinates to draw the result
		cv::imshow("scene", scene_cross);
		
	} while (cv::pollKey() != 27); //message loop untill ESC

	return EXIT_SUCCESS;
}

cv::Point2f App::find_face(cv::Mat & frame)
{
    cv::Point2f center(0.0f, 0.0f); // for result

	cv::Mat scene_grey;
	cv::cvtColor(frame, scene_grey, cv::COLOR_BGR2GRAY);

	std::vector<cv::Rect> faces;
	face_cascade.detectMultiScale(scene_grey, faces);
        
	if (faces.size() > 0) {
		center.x = (faces[0].x + faces[0].width / 2.0f) / frame.cols;
		center.y = (faces[0].y + faces[0].height / 2.0f) / frame.rows;
	}

	std::cout << "found normalized center: " << center << std::endl;

    return center;
}

void App::draw_cross_relative(cv::Mat& img, cv::Point2f center_relative, int size)
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

App::~App()
{
    // clean-up
    cv::destroyAllWindows();
    std::cout << "Bye...\n";

    if (capture.isOpened()) {
        capture.release();
    }
}

//=====================================================================================================

// define our application
App app;

// MAIN program function
int main()
{
    if (app.init()) {
		return app.run();
	} else {
		return EXIT_FAILURE;
	}
}