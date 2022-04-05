#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "canny_image.h"

void onTrackbarT1Updated(int pos, void* data) {
  CannyImage* image = static_cast<CannyImage*>(data);
  image->setT1(pos);
  cv::imshow("Image", image->update());
}

void onTrackbarT2Updated(int pos, void* data) {
  CannyImage* image = static_cast<CannyImage*>(data);
  image->setT2(pos);
  cv::imshow("Image", image->update());
}

int main(int argc, char** argv) {
  cv::Mat img = cv::imread(argv[1]);

  CannyImage image(img);

  cv::namedWindow("Image");
  cv::createTrackbar("Canny threshold 1", "Image", 0, 200, onTrackbarT1Updated, &image);
  cv::createTrackbar("Canny threshold 2", "Image", 0, 600, onTrackbarT2Updated, &image);
  cv::imshow("Image", img);

  cv::waitKey(0);

  return 0;
}