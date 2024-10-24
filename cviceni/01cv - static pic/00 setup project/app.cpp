// icp.cpp 
// author: JJ

#include <iostream>
#include <opencv2/opencv.hpp>

class App {
public:
    App();

    bool init(void);
    int run(void);

    ~App();
private:
};

App::App()
{
    // default constructor
    // nothing to do here (so far...)
    std::cout << "Constructed...\n";
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
    std::cout << "Initialized...\n";
    return true;
}

int App::run(void)
{
    try {
        // app code
        //...
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

// define our application
App app;

int main()
{
    if (app.init())
        return app.run();
}
