#include <iostream>
#include <opencv2/calib3d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

#include "utils_opencv.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    std::cout << "USAGE:" << std::endl
              << "main [folder of checkerboard image] [image for testing remap]" << std::endl;
    return EXIT_FAILURE;
  }

  std::vector<std::string> files;

  cv::glob(argv[1], files);

  cv::Mat image = cv::imread(argv[2]);
  cv::Mat imageRemapped;

  std::vector<cv::Mat> images;

  cv::Size patternSize(6, 5);

  std::vector<std::vector<cv::Vec3f>> objectPoints;
  std::vector<std::vector<cv::Vec2f>> imagePoints;
  cv::Mat cameraMatrix;
  cv::Mat distCoeffs;
  std::vector<cv::Mat> rvecs;
  std::vector<cv::Mat> tvecs;
  cv::Mat stdDeviationsIntrinsics;
  cv::Mat stdDeviationsExtrinsics;
  cv::Mat perViewErrors;

  cv::Mat R;
  cv::Mat newCameraMatrix;
  cv::Mat map1;
  cv::Mat map2;

  for (int i = 0; i < files.size(); i++) {
    cv::Mat img = cv::imread(files[i]);
    images.push_back(img);
  }

  for (int i = 0; i < images.size(); i++) {
    std::vector<cv::Vec2f> corners;
    bool found = cv::findChessboardCorners(images[i], patternSize, corners);
    if (found) {
      imagePoints.push_back(corners);

      std::vector<cv::Vec3f> points;
      for (int j = 0; j < 5; j++) {
        for (int k = 0; k < 6; k++) {
          points.push_back(cv::Vec3f(j, k, 0));
        }
      }
      objectPoints.push_back(points);
    }
  }

  cv::calibrateCamera(objectPoints, imagePoints, images[0].size(), cameraMatrix, distCoeffs, rvecs, tvecs, stdDeviationsIntrinsics, stdDeviationsExtrinsics, perViewErrors);

  double meanReprojectionError = cv::mean(perViewErrors)[0];

  std::cout << "Mean Reprojection Error: " << meanReprojectionError << std::endl;

  cv::initUndistortRectifyMap(cameraMatrix, distCoeffs, R, newCameraMatrix, images[0].size(), CV_32FC1, map1, map2);

  cv::remap(image, imageRemapped, map1, map2, cv::INTER_LINEAR);

  showImage("img", image);
  showImage("img map", imageRemapped);

  cv::waitKey(0);

  return 0;
}