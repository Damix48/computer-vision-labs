#include <filters.h>

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {
  cv::Mat img = cv::imread(argv[1]);
  cv::Mat img_gray;
  cv::Mat img_min;
  cv::Mat img_max;

  cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
  min_filter(img_gray, img_min, 3);
  max_filter(img_gray, img_max, 3);

  cv::imshow("Original", img);
  cv::imshow("Gray", img_gray);
  cv::imshow("Min filter", img_min);
  cv::imshow("Max filter", img_max);

  cv::waitKey(0);

  return 0;
}