// load clasifier
class App {

private:
    cv::CascadeClassifier face_cascade = cv::CascadeClassifier("resources/haarcascade_frontalface_default.xml");
}
//-----------------------------------------------------------------------

int App::init(){
    //open capture device
}

int App::run()
{

	cv::VideoCapture capture = init(); // open camera or video

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

cv::Point2f find_face(cv::Mat & frame)
{
    cv::Point2f center(0.0f, 0.0f); // for result

	cv::Mat scene_grey;
	cv::cvtColor(frame, scene_grey, cv::COLOR_BGR2GREY);

	std::vector<cv::Rect> faces;
	face_cascade.detectMultiScale(scene_grey, faces);
        
	if (faces.size() > 0)
	{
          // faces[0].x      -- absolute coordinates
          // faces[0].y      -- absolute coordinates
          // faces[0].width
          // faces[0].height
    
          // compute "center" as normalized coordinates of the face  
          center.x = ...
          center.y = ...    
	}

	std::cout << "found normalized center: " << center << std::endl;

    return center;      
}


