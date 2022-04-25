#include <math.h>

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/intensity_transform.hpp>

#include "utils_opencv.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    return EXIT_FAILURE;
  }

  cv::Mat img = cv::imread(argv[1]);

  cv::Mat imgGray, blurred, loga, close, imgThreshold;

  cv::medianBlur(img, blurred, 5);

  cv::cvtColor(blurred, imgGray, cv::COLOR_BGR2GRAY);

  cv::intensity_transform::logTransform(imgGray, loga);

  cv::threshold(loga, imgThreshold, 20, 255, cv::THRESH_TRIANGLE);

  cv::bitwise_not(imgThreshold, imgThreshold);

  cv::dilate(imgThreshold, imgThreshold, cv::Mat());

  cv::Mat labels, stats, centroids;

  int numberLabels = cv::connectedComponentsWithStats(imgThreshold, labels, stats, centroids);

  std::vector<uchar> colorsConnected;
  colorsConnected.push_back(0);

  for (int i = 1; i < numberLabels; i++) {
    if (stats.at<int>(i, cv::CC_STAT_AREA) > 100) {
      colorsConnected.push_back(255);
    } else {
      colorsConnected.push_back(0);
    }
  }

  for (int i = 0; i < imgGray.rows; i++) {
    for (int j = 0; j < imgGray.cols; j++) {
      imgGray.at<uchar>(i, j) = colorsConnected[labels.at<int>(i, j)];
    }
  }

  showImage("Cracks", imgGray);

  cv::waitKey(0);

  return 0;
}