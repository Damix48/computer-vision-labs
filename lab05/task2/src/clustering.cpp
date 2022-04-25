#include "clustering.h"

#include <iostream>
#include <opencv2/core.hpp>

void computeKmeans(cv::Mat& src, cv::Mat& dst, int K) {
  if (dst.rows == 0 && dst.cols == 0) {
    dst = cv::Mat(src.size(), CV_8UC1);
  }

  cv::Mat pixels(src.rows * src.cols, 5, CV_32F);

  for (int i = 0; i < src.rows; i++) {
    for (int j = 0; j < src.cols; j++) {
      pixels.at<float>(i * src.cols + j, 0) = (float)i / src.rows;
      pixels.at<float>(i * src.cols + j, 1) = (float)j / src.cols;

      cv::Vec3b color = src.at<cv::Vec3b>(i, j);

      pixels.at<float>(i * src.cols + j, 2) = color[0] / 255.0;
      pixels.at<float>(i * src.cols + j, 3) = color[1] / 255.0;
      pixels.at<float>(i * src.cols + j, 4) = color[2] / 255.0;
    }
  }

  std::cout << "Pixels loaded" << std::endl;

  cv::Mat labels, centers;

  cv::kmeans(pixels, K, labels, cv::TermCriteria(cv::TermCriteria::EPS, 10, 0.01), 10, cv::KMEANS_PP_CENTERS, centers);

  std::cout << "kmeans completed" << std::endl;

  for (int i = 0; i < dst.rows; i++) {
    for (int j = 0; j < dst.cols; j++) {
      dst.at<uchar>(i, j) = 255 / (labels.at<int>(i * src.cols + j) + 1);
    }
  }
}
