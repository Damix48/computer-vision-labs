#include <math.h>

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/intensity_transform.hpp>

#include "utils_opencv.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    return EXIT_FAILURE;
  }

  cv::Mat img = cv::imread(argv[1]);

  cv::GaussianBlur(img, img, cv::Size(5, 5), 7, 7);
  cv::Mat imgHSL, shirts;

  cv::Scalar yellow_low(15, 40, 40);
  cv::Scalar yellow_upp(30, 255, 255);

  cv::cvtColor(img, imgHSL, cv::COLOR_BGR2HSV);

  cv::inRange(imgHSL, yellow_low, yellow_upp, shirts);

  showImage("img", img);
  showImage("shirts", shirts);

  cv::waitKey(0);

  return 0;
}