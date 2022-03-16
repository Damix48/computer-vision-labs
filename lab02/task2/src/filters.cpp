#include <filters.h>

#include <iostream>
#include <opencv2/imgproc.hpp>

void min_filter(int kernel_size, cv::Mat src, cv::Mat dst) {
  if (kernel_size % 2 == 0) {
    return;
  }

  dst = cv::Mat::zeros(src.rows, src.cols, CV_8U);

  std::cout << src.rows << " " << src.cols << std::endl;
  std::cout << dst.rows << " " << dst.cols << std::endl;

  int s = 0;

  for (int i = 0; i < dst.rows - 0; i++) {
    for (int j = 0; j < dst.cols - 0; j++) {
      int min = 255;
      // for (int k = -kernel_size / 2; k < kernel_size / 2 + 1; k++) {
      //   for (int w = -kernel_size / 2; w < kernel_size / 2 + 1; w++) {
      //     // std::cout << k << " " << w << std::endl;
      //     int curr = src.at<u_char>(i + k, j + w);
      //     if (min > curr) {
      //       min = curr;
      //     }
      //   }
      // }
      dst.at<u_char>(i, j) = src.at<u_char>(i, j);
      s++;
    }
  }

  std::cout << s << std::endl;

  cv::imshow("dd", src);
  cv::imshow("d", dst);
  int key = cv::waitKey(0);

  std::cout
      << kernel_size << std::endl;
}