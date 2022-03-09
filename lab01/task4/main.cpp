#include <iostream>
#include <opencv2/highgui.hpp>
int main(int argc, char** argv) {
  cv::Mat img = cv::imread(argv[1]);
  cv::Mat channels[3];

  cv::split(img, channels);

  int n_channels = img.channels();

  std::cout << n_channels << std::endl;

  if (n_channels == 3) {
    channels[0] = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);  // Delete blue
    channels[1] = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);  // Delete green
    channels[2] = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);  // Delete red
  }

  cv::Mat img_out;
  cv::merge(channels, 3, img_out);

  cv::namedWindow("Example 1");
  cv::imshow("Example 1", img_out);

  int key = cv::waitKey(0);
  std::cout << key << std::endl;

  return 0;
}