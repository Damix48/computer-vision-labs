#include <filters.h>

#include <iostream>
#include <opencv2/imgproc.hpp>

void min_filter(cv::Mat src, cv::Mat& dst, int kernel_size) {
  if (kernel_size % 2 == 0) {
    return;
  }

  dst = cv::Mat::zeros(src.rows, src.cols, src.type());

  for (int i = 0; i < dst.rows; i++) {
    for (int j = 0; j < dst.cols; j++) {
      u_char min = 255;
      for (int k = -kernel_size / 2; k < kernel_size / 2 + 1; k++) {
        for (int w = -kernel_size / 2; w < kernel_size / 2 + 1; w++) {
          if ((i + k > 0) && (i + k < dst.rows) && (j + w > 0) && (j + k < dst.cols)) {
            u_char curr = src.at<u_char>(i + k, j + w);
            if (min > curr) {
              min = curr;
            }
          }
        }
      }
      dst.at<u_char>(i, j) = min;
    }
  }
}