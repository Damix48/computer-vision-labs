#include <iostream>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv) {
  cv::Mat img = cv::imread(argv[1]);
  std::cout << img.channels() << std::endl;

  cv::namedWindow("Example 1");
  cv::imshow("Example 1", img);

  int key = cv::waitKey(0);
  std::cout << key << std::endl;

  return 0;
}