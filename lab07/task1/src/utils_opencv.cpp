#include "utils_opencv.h"

#include <opencv2/highgui.hpp>
#include <string>

void showImage(std::string title, cv::Mat& image) {
  cv::namedWindow(title, cv::WINDOW_NORMAL);
  cv::imshow(title, image);
}
