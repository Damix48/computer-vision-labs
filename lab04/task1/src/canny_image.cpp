
#include "canny_image.h"

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

CannyImage::CannyImage(cv::Mat src, int t1, int t2, int a) : original(src), edge(src), threshold1(t1), threshold2(t2), aperture(a) {}

void CannyImage::update() {
  cv::Mat img_temp;

  cv::blur(original, img_temp, cv::Size(3, 3));

  cv::Canny(img_temp, edge, threshold1, threshold2, aperture, true);

  cv::imshow("Image", edge);
}