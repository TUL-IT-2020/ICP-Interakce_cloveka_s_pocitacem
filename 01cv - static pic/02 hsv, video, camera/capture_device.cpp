// icp.cpp 
// Author: JJ

#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdexcept>
#include <chrono>

// our application class 
class App {
public:
    App(); // default constructor, called on app instance definition
    
    // public methods
    bool init(void);
    int run(void);
    
    void draw_cross_relative(cv::Mat& img, const cv::Point2f center_relative, const int size);
    void draw_cross_normalized(cv::Mat& img, cv::Point2f center_relative, int size);
    void draw_cross(cv::Mat& img, int x, int y, int size);
    
    ~App(); //default destructor, called on app instance destruction
private:

    cv::VideoCapture capture;  // global variable, move to app class, protected
};

//=====================================================================================================

App::App()
{
    // default constructor
    // nothing to do here (so far...)
}

bool App::init(void)
{
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

int App::run(void)
{
    cv::Mat frame, scene;

    while (1)
    {
        capture.read(frame);
        if (frame.empty())
        {
            std::cerr << "Cam disconnected? End of file?\n";
            break;
        }

        // show grabbed frame
        cv::imshow("grabbed", frame);

        // WARNING: image MUST NOT be modified. If you want to draw into image,
        // do your own COPY!

        // analyze the image...
        // center = find_object(frame);

        // make a copy and draw center
        cv::Mat scene_cross;
        frame.copyTo(scene_cross);
        //draw_cross_relative(scene_cross, center, 30);
        cv::imshow("scene", scene_cross);
                

        if (cv::waitKey(1) == 27)
            break;
    }

    return EXIT_SUCCESS;
}

void App::draw_cross(cv::Mat& img, int x, int y, int size)
{
    cv::Point p1(x - size / 2, y);
    cv::Point p2(x + size / 2, y);
    cv::Point p3(x, y - size / 2);
    cv::Point p4(x, y + size / 2);

    cv::line(img, p1, p2, CV_RGB(255, 0, 0), 3);
    cv::line(img, p3, p4, CV_RGB(255, 0, 0), 3);
}

void App::draw_cross_normalized(cv::Mat& img, cv::Point2f center_normalized, int size)
{
    center_normalized.x = std::clamp(center_normalized.x, 0.0f, 1.0f);
    center_normalized.y = std::clamp(center_normalized.y, 0.0f, 1.0f);
    size = std::clamp(size, 1, std::min(img.cols, img.rows));

    cv::Point2f center_absolute(center_normalized.x * img.cols, center_normalized.y * img.rows);

    cv::Point2f p1(center_absolute.x - size / 2, center_absolute.y);
    cv::Point2f p2(center_absolute.x + size / 2, center_absolute.y);
    cv::Point2f p3(center_absolute.x, center_absolute.y - size / 2);
    cv::Point2f p4(center_absolute.x, center_absolute.y + size / 2);

    cv::line(img, p1, p2, CV_RGB(255, 0, 0), 3);
    cv::line(img, p3, p4, CV_RGB(255, 0, 0), 3);
}

App::~App()
{
    if (capture.isOpened())
        capture.release();

    // clean-up
    cv::destroyAllWindows();
    std::cout << "Bye...\n";
}

//=====================================================================================================

// define our application
App app;

// MAIN program function
int main()
{
    if (app.init())
        return app.run();
    else
        return EXIT_FAILURE;
}
