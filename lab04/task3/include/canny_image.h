#ifndef CANNY_IMAGE_H
#define CANNY_IMAGE_H

#include <opencv2/core.hpp>

class CannyImage {
  cv::Mat original;
  int aperture;

  cv::Mat edge;
  int threshold1;
  int threshold2;

 public:
  CannyImage(cv::Mat src, int t1 = 0, int t2 = 0, int a = 3);

  void setT1(int t1);
  void setT2(int t2);

  cv::Mat update();
};

#endif  // CANNY_IMAGE_H