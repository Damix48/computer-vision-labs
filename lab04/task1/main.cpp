#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "canny_image.h"

void onTrackbarUpdated(int pos, void* data) {
  CannyImage* image = static_cast<CannyImage*>(data);
  image->update();
}

int main(int argc, char** argv) {
  cv::Mat img = cv::imread(argv[1]);

  CannyImage image(img);

  cv::namedWindow("Image");
  cv::createTrackbar("Canny threshold 1", "Image", &image.threshold1, 200, onTrackbarUpdated, &image);
  cv::createTrackbar("Canny threshold 2", "Image", &image.threshold2, 600, onTrackbarUpdated, &image);
  cv::imshow("Image", img);

  cv::waitKey(0);

  return 0;
}