#include <filters.h>

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {
  cv::Mat img = cv::imread(argv[1]);
  cv::Mat img_gray;
  cv::Mat img_min;

  cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
  min_filter(img_gray, img_min, 15);

  return 0;
}