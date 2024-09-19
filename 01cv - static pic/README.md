# LAB 01

## Task 1: Explore the source code for finding the center of the lightbulb

   1. Convert the image from RGB to YCbCr. Use Y channel for further operations.

      ```C++
      JPEG 8bit conversion:

      Y  =       + 0.299    * R + 0.587    * G + 0.114    * B
      Cb = 128   - 0.168736 * R - 0.331264 * G + 0.5      * B
      Cr = 128   + 0.5      * R - 0.418688 * G - 0.081312 * B
      ```

   2. Use thresholding to separate object. Try different thresholds.

## Task 2: Find the red cup in static image

   1. Use similar approach as in Task 1 to find the object, but search for RED color in HSV color model, and use existing functions.

      ```C++
      // Convert image to HSV using OpenCV.
      cv::CvtColor(img_RGB, img_HSV, cv::COLOR_BGR2HSV);
      ```

   2. Use color information to separate the object from background. Manually
       (two nested for loops, as in previous task) or with the OpenCV:

      ```C++
      // Set threshold range (example values)
      cv::Scalar lower_threshold = cv::Scalar(10,0,0);
      cv::Scalar upper_threshold = cv::Scalar(20,255,255);
      ```

      ⚠ Example range in HSV is not correct - only has valid range of Hues, but all Saturations and all Values are accepted. Why is it not very smart? Use 'HSV-MAP.png' to find and set a proper range.

      ```C++
      // Compute threshold
      cv::InRangeS(img_HSV, lower_threshold, upper_threshold, img_dest);

      // Find all non-zero (ie. white) pixels in thresholded image
      std::vector<cv::Point> whitePixels;
      cv::findNonZero(scene_threshold, whitePixels);

      // Count white pixels
      int whiteCnt = whitePixels.size();

      // Count SUM of X_coords, Y_coords of white pixels
      // You need C++17 for std::reduce()
      cv::Point2f whiteAccum = std::reduce(whitePixels.begin(), whitePixels.end());

      // or faster = parallel version, with automatic multi-threading
      cv::Point2f whiteAccum = std::reduce(std::execution::par_unseq, whitePixels.begin(), whitePixels.end());

      // Divide by whiteCnt to get average, ie. centroid (only if whiteCnt != 0 !!!)
      cv::Point2f centroid_absolute = whiteAccum / whiteCnt;
      // Compute NORMALIZED coordinates
      cv::Point2f centroid_normalized = { centroid_absolute.x / scene.cols, centroid_absolute.y / scene.rows }; 
      ```

   3. (optional) Use morphological operations (dilatation, erosion, ...) to improve accuracy of the result.

## Task 3: Find the red object in sequence of images - camera stream or video

   1. Open capture device (camera or file) stream in init() function, store capture device variable as protected in App class. If camera is not found, open video file.

   2. Use similar approach as in Task 2 to find moving object. Refactor your code, create new method with object tracker:

      ```C++
      cv::Point2f object_search(cv::Mat & img) { ... }
      ```

   3. Modify App::run(), so that there is only loop that grabs image from capture device until it is empty, calls object_search() and prints result, and test ESC key.

   4. Use sample code in time_measure.c to find the fastest approach. Try to spend at most **10 milliseconds** per frame.

   5. (optional) resize the image, if speed is too low (less pixels to analyze)

      ```C++
      cv::Resize(source_frame, frame, cv::INTER_NEAREST); //or CV_INTER_LINEAR etc.
      ```

## Task 4: Find the center of your face :-)

   1. Use code from Task 3 and sample code from "face detect" directory.
