# LAB 04

## Task 1: Explore the source code for lossy compression

The program requires a camera. It produces continuous stream of compressed JPEG images that fit within required size limit (bandwidth). This is similar to MJPEG compression. Use 'q' or 'a' key to increase or decrease available bandwidth. Use ESC key to terminate.

- measure time needed to compress an image
- measure time needed to decompress an image
- compare times: what is the assymetry ratio of the compression?

## Task 2: Use similar approach as in sample code, but replace limitation by bandwith with limitation by quality

1. Implement the function:

   ```C++
   std::vector<uchar> lossy_quality_limit(cv::Mat& input_img, float target_quality)
   ```

   Use PSNR (Peak Signal to Noise Ratio) or SSIM (Structural Similarity) - functions getPSNR() or getMSSIM() - from <https://docs.opencv.org/2.4/doc/tutorials/highgui/video-input-psnr-ssim/video-input-psnr-ssim.html#image-similarity-psnr-and-ssim> to estimate quality of the compressed image.

For PSNR, target_quality will be in dB.
For SSIM, target_quality will be average of RGB SSIM.

## Task 3: Use multithreading (some variant)

- main + grabber/encoder/decoder
- main + grabber/encoder + decoder
- main + grabber + encoder + decoder
- encoder itself can be multithreaded...
- ...

## Task 4: (OPTIONAL)

1. Create a structure for two types of frames:
   - independent (full) frame
   - delta frame - difference between two consecutive frames
2. Create a function, that compresses the difference between two consecutive frames.
3. Try to encode full frame and delta frame in all cases. Choose the smaller variant and send it to the decoder. You MUST start with full frame.
4. Modify decoder accordingly.
5. Evaluate the compression ratio improvement when using delta frames vs. no delta frames.
