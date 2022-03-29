#include <iostream>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv) {
  cv::Mat img = cv::imread(argv[1]);

  cv::namedWindow("Image");
  cv::imshow("Image", img);

  cv::waitKey(0);

  return 0;
}