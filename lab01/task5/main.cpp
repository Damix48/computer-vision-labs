#include <iostream>
#include <opencv2/highgui.hpp>

int main(int argc, char** argv) {
  cv::Mat img = cv::imread(argv[1]);
  cv::Mat channels1[3];
  cv::Mat channels2[3];
  cv::Mat channels3[3];

  cv::split(img, channels1);
  cv::split(img, channels2);
  cv::split(img, channels3);

  int n_channels = img.channels();

  std::cout << n_channels << std::endl;

  if (n_channels == 3) {
    channels1[1] = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
    channels1[2] = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);

    channels2[0] = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
    channels2[2] = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);

    channels3[0] = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
    channels3[1] = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
  }

  cv::Mat img_out1, img_out2, img_out3;
  cv::merge(channels1, 3, img_out1);
  cv::merge(channels2, 3, img_out2);
  cv::merge(channels3, 3, img_out3);

  cv::imshow("Example 1", img_out1);
  cv::imshow("Example 2", img_out2);
  cv::imshow("Example 3", img_out3);

  int key = cv::waitKey(0);
  std::cout << key << std::endl;

  return 0;
}