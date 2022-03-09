#include <iostream>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv) {
  int height = 256;
  int width = 256;
  cv::Mat img1 = cv::Mat(height, width, CV_8UC1);
  cv::Mat img2 = cv::Mat(height, width, CV_8UC1);

  for (int i = 0; i < height - 1; i++) {
    for (int j = 0; j < width - 1; j++) {
      img1.at<unsigned char>(i, j) = static_cast<unsigned char>(i);
    }
  }

  for (int i = 0; i < height - 1; i++) {
    for (int j = 0; j < width - 1; j++) {
      img2.at<unsigned char>(j, i) = static_cast<unsigned char>(i);
    }
  }

  cv::imshow("Example 1", img1);
  cv::imshow("Example 2", img2);

  char key = cv::waitKey(0);
  std::cout << key << std::endl;

  return 0;
}