#include <iostream>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

#include "utils_opencv.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    return EXIT_FAILURE;
  }

  cv::Mat img1 = cv::imread(argv[1]);
  cv::Mat img2 = cv::imread(argv[2]);

  std::vector<cv::KeyPoint> keypoints1, keypoints2;
  cv::Mat descriptors1, descriptors2, out;

  cv::Ptr<cv::ORB> orb = cv::ORB::create();

  orb->detectAndCompute(img1, cv::noArray(), keypoints1, descriptors1);
  orb->detectAndCompute(img2, cv::noArray(), keypoints2, descriptors2);

  cv::Ptr<cv::BFMatcher> matcher = cv::BFMatcher::create(cv::NORM_HAMMING, true);
  // cv::FlannBasedMatcher matcher = cv::FlannBasedMatcher(cv::makePtr<cv::flann::LshIndexParams>(12, 20, 2));

  std::vector<cv::DMatch> matches;
  std::vector<cv::DMatch> goodMatches;

  matcher->match(descriptors1, descriptors2, matches);

  for (int i = 0; i < matches.size(); i++) {
    std::cout << matches[i].distance << std::endl;
    if (matches[i].distance < 30) {
      goodMatches.push_back(matches[i]);
    }
  }

  cv::drawMatches(img1, keypoints1, img2, keypoints2, matches, out);

  showImage("out", out);

  cv::waitKey(0);

  return 0;
}