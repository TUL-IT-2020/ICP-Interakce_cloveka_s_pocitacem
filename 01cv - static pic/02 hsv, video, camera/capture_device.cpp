// icp.cpp 
// Author: JJ

class App {
    ...
private:
    ...
    cv::VideoCapture capture;  // global variable, move to app class, protected
}

//=====================================================================================================

void App::init(void)
{
    //open first available camera
    capture = cv::VideoCapture(cv::CAP_DSHOW);
    
    //open video file
    //capture = cv::VideoCapture("video.mkv");

    if (!capture.isOpened())
    { 
        std::cerr << "no source?" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "Source: " << 
            ": width=" << capture.get(cv::CAP_PROP_FRAME_WIDTH) <<
            ", height=" << capture.get(cv::CAP_PROP_FRAME_HEIGHT) << '\n';
    }
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
        draw_cross_relative(scene_cross, center, 30);
        cv::imshow("scene", scene_cross);
                

        if (cv::waitKey(1) == 27)
            break;
    }

    return EXIT_SUCCESS;
}

App::~App()
{
    // clean-up
    cv::destroyAllWindows();
    std::cout << "Bye...\n";

    if (capture.isOpened())
        capture.release();
}


