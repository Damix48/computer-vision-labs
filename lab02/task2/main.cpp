#include <filters.h>

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {
  cv::Mat img_gray = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  cv::Mat img_min;
  cv::Mat img_max;

  min_filter(img_gray, img_min, 3);
  max_filter(img_gray, img_max, 3);

  cv::namedWindow("Gray", cv::WINDOW_NORMAL);
  cv::imshow("Gray", img_gray);

  cv::namedWindow("Min filter", cv::WINDOW_NORMAL);
  cv::imshow("Min filter", img_min);

  cv::namedWindow("Max filter", cv::WINDOW_NORMAL);
  cv::imshow("Max filter", img_max);

  cv::waitKey(0);

  return 0;
}