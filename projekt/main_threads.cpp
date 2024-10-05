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
	cv::Point2f find_face(cv::Mat & frame);
	void draw_cross_relative(cv::Mat& img, cv::Point2f center_relative, int size);

	// thread functions
	void camera_processing_thread();
	void UI_thread();

private:
    cv::VideoCapture capture;
    cv::CascadeClassifier face_cascade; // Face cascade classifier

	// thread controll variables
	std::mutex mtx;
	bool user_exit = false;
	bool cam_disconnected = false;
	bool process_images = true;

	// thread shared variables
	bool new_coordinates = false;
	cv::Point2f center = cv::Point2f(0.0f, 0.0f);
	cv::Mat frame;
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

App::~App()
{
    // clean-up
    cv::destroyAllWindows();
    std::cout << "Bye...\n";

    if (capture.isOpened()) {
        capture.release();
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
    return center;      
}

void App::draw_cross_relative(cv::Mat& img, const cv::Point2f center_relative, const int size)
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

void App::UI_thread() {
	cv::Point2f center_local;
	cv::Mat frame_local;
	// wait for first frame
	while (!new_coordinates) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	do {
		// get global variables
		{
			std::lock_guard<std::mutex> lock(mtx);
			if (new_coordinates) {
				center_local = center;
				frame.copyTo(frame_local);
				new_coordinates = false;
				
				std::cout << "found normalized center: " << center << std::endl;
			}
		}

		//display result
		cv::Mat scene_cross;
		frame_local.copyTo(scene_cross);
        draw_cross_relative(scene_cross, center, 30);
		cv::imshow("scene", scene_cross);
		
	} while (cv::pollKey() != 27 || cam_disconnected); //message loop untill ESC
	user_exit = true;
	process_images = false;
}

void App::camera_processing_thread() {
	cv::Mat frame_local;
	cv::Point2f center_local;
	do {
		capture.read(frame_local);
		if (frame_local.empty())
		{
			cam_disconnected = true;
			break;
		}

		// find face
        center_local = find_face(frame_local);

		// update global variables
		{
			std::lock_guard<std::mutex> lock(mtx);
			frame_local.copyTo(frame);	// TODO: use shared pointer (swap)
			center = center_local;
			new_coordinates = true;
		}
	} while (process_images);
}

int App::run() {
	// start camera processing thread
	std::thread camera_thread(std::bind(&App::camera_processing_thread, this));

	// UI handling
	UI_thread();
	
	if (cam_disconnected) {
		std::cerr << "Camera disconnected\n";
		return EXIT_FAILURE;
	}

	if (user_exit) {
		std::cout << "User exit\n";
		return EXIT_SUCCESS;
	}

	camera_thread.join();

	return EXIT_SUCCESS;
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