
#include "canny_image.h"

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

CannyImage::CannyImage(cv::Mat src, int t1, int t2, int a) : original(src), edge(src), threshold1(t1), threshold2(t2), aperture(a) {}

void CannyImage::setT1(int t1) {
  threshold1 = t1;
}

void CannyImage::setT2(int t2) {
  threshold2 = t2;
}

cv::Mat CannyImage::update() {
  cv::Mat img_temp;

  cv::blur(original, img_temp, cv::Size(3, 3));

  cv::Canny(img_temp, edge, threshold1, threshold2, aperture, true);

  return edge;
}