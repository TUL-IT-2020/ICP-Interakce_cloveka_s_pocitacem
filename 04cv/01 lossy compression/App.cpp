#include <iostream>
#include <opencv2/opencv.hpp>
#include <numeric>

#include "App.h"


App::App()
{
    // default constructor
    // nothing to do here (so far...)
    std::cout << "Constructed...\n";
}

bool App::init()
{
    try {
        capture = cv::VideoCapture(0, cv::CAP_ANY);
        if (!capture.isOpened())
            throw std::runtime_error("Can not open camera :(");

        std::cout << "Cam opened successfully.\n";

    }
    catch (std::exception const& e) {
        std::cerr << "Init failed : " << e.what() << std::endl;
        throw;
    }
    std::cout << "Initialized...\n";
    return true;
}

std::vector<uchar> App::lossy_bw_limit(cv::Mat& input_img, size_t size_limit)
{
    std::string suff(".jpg"); // target format
    if (!cv::haveImageWriter(suff))
        throw std::runtime_error("Can not compress to format:" + suff);

    std::vector<uchar> bytes;
    std::vector<int> compression_params;

    // prepare parameters for JPEG compressor
    // we use only quality, but other parameters are available (progressive, optimization...)
    std::vector<int> compression_params_template;
    compression_params_template.push_back(cv::IMWRITE_JPEG_QUALITY); 

    std::cout << '[';

    //try step-by-step to decrease quality by 5%, until it fits into limit
    for (auto i = 100; i > 0; i -= 5) {
        compression_params = compression_params_template; // reset parameters
        compression_params.push_back(i);                  // set desired quality
        std::cout << i << ',';

        // try to encode
        cv::imencode(suff, input_img, bytes, compression_params);

        // check the size limit
        if (bytes.size() <= size_limit)
            break; // ok, done 
    }
    std::cout << "]\n";

    return bytes;
}

int App::run(void)
{
    cv::Mat frame;
    std::vector<uchar> bytes;
    float target_coefficient = 0.5f; // used as size-ratio, or quality-coefficient
    try {
        while (capture.isOpened())
        {
            capture >> frame;

            if (frame.empty()) {
                std::cerr << "device closed (or video at the end)" << '\n';
                capture.release();
                break;
            }

            // encode image with bandwidth limit
            auto size_uncompressed = frame.elemSize() * frame.total();
            auto size_compressed_limit = size_uncompressed * target_coefficient;

            //
            // Encode single image with limitation by bandwidth
            //
            bytes = lossy_bw_limit(frame, size_compressed_limit); // returns JPG compressed stream for single image
            

            //
            // TASK 1: Replace function lossy_bw_limit() - limitation by bandwith - with limitation by quality.
            //         Implement the function:
            // bytes = lossy_quality_limit(frame, target_coefficient);
            // 
            //         Use PSNR (Peak Signal to Noise Ratio)
            //         or  SSIM (Structural Similarity) 
            // (from https://docs.opencv.org/2.4/doc/tutorials/highgui/video-input-psnr-ssim/video-input-psnr-ssim.html#image-similarity-psnr-and-ssim ) 
            //         to estimate quality of the compressed image.
            //


            // display compression ratio
            auto size_compreessed = bytes.size();
            std::cout << "Size: uncompressed = " << size_uncompressed << ", compressed = " << size_compreessed << ", = " << size_compreessed / (size_uncompressed / 100.0) << " % \n";

            //
            // decode compressed data
            //  
            cv::Mat decoded_frame = cv::imdecode(bytes, cv::IMREAD_ANYCOLOR);

            cv::namedWindow("original");
            cv::imshow("original", frame);

            cv::namedWindow("decoded");
            cv::imshow("decoded", decoded_frame);

            // key handling
            int c = cv::pollKey();
            switch (c) {
            case 27:
                return EXIT_SUCCESS;
                break;
            case 'q':
                target_coefficient *= 2;
                break;
            case 'a':
                target_coefficient /= 2;
                break;
            default:
                break;
            }

            target_coefficient = std::clamp(target_coefficient, 0.01f, 1.0f);
            std::cout << "Target coeff: " << target_coefficient*100.0f << " %\n";
        }
    }
    catch (std::exception const& e) {
        std::cerr << "App failed : " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Finished OK...\n";
    return EXIT_SUCCESS;
}

App::~App()
{
    // clean-up
    cv::destroyAllWindows();
    std::cout << "Bye...\n";
}
