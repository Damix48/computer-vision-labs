#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {
  cv::Mat img = cv::imread(argv[1]);
  cv::Mat img_gray;

  cv::namedWindow("Example 1", cv::WINDOW_NORMAL);
  cv::imshow("Example 1", img);

  cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);

  cv::namedWindow("Example 1 gray", cv::WINDOW_NORMAL);
  cv::imshow("Example 1 gray", img_gray);

  cv::imwrite(argv[2], img_gray);

  int key = cv::waitKey(0);

  return 0;
}