#pragma once
#include <vector>
#include <opencv2/opencv.hpp>

class App {
public:
    App();

    bool init(void);
    
    std::vector<uchar> lossy_bw_limit(cv::Mat& input_img, std::size_t size_limit);
    
    int run(void);

    ~App();
private:
    cv::VideoCapture capture;
};

