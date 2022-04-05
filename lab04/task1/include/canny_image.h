#ifndef CANNY_IMAGE_H
#define CANNY_IMAGE_H

#include <opencv2/core.hpp>

class CannyImage {
  cv::Mat original;
  int aperture;

 public:
  cv::Mat edge;
  int threshold1;
  int threshold2;

  CannyImage(cv::Mat src, int t1 = 0, int t2 = 0, int a = 3);

  void update();
};

#endif  // CANNY_IMAGE_H