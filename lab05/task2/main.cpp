#include <math.h>

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/intensity_transform.hpp>

#include "clustering.h"
#include "utils_opencv.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    return EXIT_FAILURE;
  }

  cv::Mat img = cv::imread(argv[1]);
  cv::Mat out;

  showImage("img", img);

  cv::GaussianBlur(img, img, cv::Size(3, 3), 5, 5);

  showImage("blur", img);

  computeKmeans(img, out, 3);

  showImage("out", out);

  cv::waitKey(0);

  return 0;
}