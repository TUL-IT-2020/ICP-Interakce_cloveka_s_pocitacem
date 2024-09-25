// icp.cpp 
// author: JJ

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
    unsigned char compute_threshold(cv::Vec3b pixel);

    void draw_cross_normalized(cv::Mat& img, cv::Point2f center_relative, int size);
    void draw_cross(cv::Mat& img, int x, int y, int size);

    ~App(); //default destructor, called on app instance destruction
private:
    // no private variables, so far...
};

App::App()
{
    // default constructor
    // nothing to do here (so far...)
}

bool App::init()
{
    try {
        // all initialization code
        //...

        // some init
        // if (not_success)
        //  throw std::exception("something went bad");
    }
    catch (std::exception const& e) {
        std::cerr << "Init failed : " << e.what() << std::endl;
        throw;
    }
    
    return true;
}

unsigned char App::compute_threshold(cv::Vec3b pixel)
{
    // compute temp grayscale value (convert from colors to Y)
    unsigned char Y = 0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0];
    return Y;
}

int App::run(void)
{
    try {
        // read image
        cv::Mat frame = cv::imread("resources/lightbulb.jpg");  //can be JPG,PNG,GIF,TIFF,...

        if (frame.empty())
            throw std::runtime_error("Empty file? Wrong path?");

        //start timer
        auto start = std::chrono::steady_clock::now();

        // create copy of the frame
        cv::Mat frame2;
        frame.copyTo(frame2);

        // convert to grayscale, create threshold, sum white pixels
        // compute centroid of white pixels (average X,Y coordinate of all white pixels)
        int white_pixel_count = 0;
        cv::Point2f center;
        cv::Point2f center_normalized;

        for (int y = 0; y < frame.rows; y++) //y
        {
            for (int x = 0; x < frame.cols; x++) //x
            {
                // load source pixel
                cv::Vec3b pixel = frame.at<cv::Vec3b>(y, x);

                // compute temp grayscale value (convert from colors to Y)
                unsigned char Y = compute_threshold(pixel);
                //frame2.at<cv::Vec3b>(y, x) = cv::Vec3b(Y, Y, Y);

                // FIND THRESHOLD (value 0..255)
                if (Y < 240 ) {
                    // set output pixel black
                    frame2.at<cv::Vec3b>(y, x) = cv::Vec3b(0, 0, 0);
                }
                else {
                    // set output pixel white
                    frame2.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 255, 255);

                    //update centroid
                    white_pixel_count++;
                    center.x += x;
                    center.y += y;
                }

            }
        }

        // compute centroid
        center.x /= white_pixel_count;
        center.y /= white_pixel_count;

        // normalize centroid
        center_normalized.x = center.x / frame.cols;
        center_normalized.y = center.y / frame.rows;

        std::cout << "Center absolute: " << center << '\n';
        std::cout << "Center normalized: " << center_normalized << '\n';

        // how long the computation took?
        auto end = std::chrono::steady_clock::now();

        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Elapsed time: " << elapsed_seconds.count() << "sec" << std::endl;

        // highlight the center of object
        draw_cross(frame, center.x, center.y, 25);
        draw_cross_normalized(frame2, center_normalized, 25);

        // show me the result
        cv::namedWindow("frame");
        cv::imshow("frame", frame);

        cv::namedWindow("frame2");
        cv::imshow("frame2", frame2);

        // keep application open until ESC is pressed
        while (true)
        {
            int key = cv::pollKey(); // poll OS events (key press, mouse move, ...)
            if (key == 27) // test for ESC key
                break;
        }

    }
    catch (std::exception const& e) {
        std::cerr << "App failed : " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

App::~App()
{
    // clean-up
    cv::destroyAllWindows();
    std::cout << "Bye...\n";
}

// define our application
App app;

// MAIN program function
int main()
{
    if (app.init())
        return app.run();
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

