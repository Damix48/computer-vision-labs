#include <iostream>
#include <opencv2/calib3d.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <vector>

#include "panoramic_utils.h"
#include "utils_opencv.h"

int main(int argc, char** argv) {
  if (argc < 3) {
    return EXIT_FAILURE;
  }

  std::vector<std::string> files;

  cv::glob(argv[1], files);
  double angle = atof(argv[2]);
  double ratio = 3;

  std::vector<cv::Mat> images;
  std::vector<cv::Mat> colimages;

  std::vector<std::vector<cv::KeyPoint>> keypoints;
  std::vector<cv::Mat> descriptors;

  for (int i = 0; i < files.size(); i++) {
    cv::Mat img = cv::imread(files[i]);

    colimages.push_back(img);

    images.push_back(cylindricalProj(img, angle));

    cv::Ptr<cv::SIFT> sift = cv::SIFT::create();

    std::vector<cv::KeyPoint> keypoint;
    cv::Mat descriptor;

    sift->detectAndCompute(images[i], cv::noArray(), keypoint, descriptor);

    descriptors.push_back(descriptor);
    keypoints.push_back(keypoint);
  }

  std::vector<std::vector<cv::DMatch>> matches;

  for (int i = 1; i < descriptors.size(); i++) {
    cv::Ptr<cv::BFMatcher> matcher = cv::BFMatcher::create(cv::NORM_L2, true);

    std::vector<cv::DMatch> match;
    std::vector<cv::DMatch> goodMatch;

    matcher->match(descriptors[i - 1], descriptors[i], match);

    float minDistance = match[0].distance;

    for (int j = 1; j < match.size(); j++) {
      if (match[j].distance < minDistance) {
        minDistance = match[j].distance;
      }
    }

    // std::cout << minDistance << std::endl;

    for (int j = 0; j < match.size(); j++) {
      if (match[j].distance < ratio * minDistance) {
        goodMatch.push_back(match[j]);
      }
    }

    matches.push_back(goodMatch);
  }

  std::vector<cv::Mat> homographies;

  for (int i = 0; i < matches.size(); i++) {
    std::vector<cv::DMatch> match = matches[i];

    std::vector<cv::Point2f> points1;
    std::vector<cv::Point2f> points2;

    // std::cout << match.size();

    for (int j = 0; j < match.size(); j++) {
      points1.push_back(keypoints[i][match[j].queryIdx].pt);
      points2.push_back(keypoints[i + 1][match[j].trainIdx].pt);
    }

    // std::cout << points1.size() << " " << points2.size() << std::endl;

    homographies.push_back(cv::findHomography(points1, points2, cv::RANSAC));
    // std::cout << std::endl
    //           << homographies[i]
    //           << std::endl;
  }

  for (int i = 0; i < homographies.size() - 1; i++) {
    showImage("img1", images[i]);
    showImage("img2", images[i + 1]);
    cv::Mat wrap, wrapinverso, result;
    cv::warpPerspective(images[i], wrap, homographies[i], cv::Size(images[i + 1].cols + images[i].cols, images[i].rows));
    cv::warpPerspective(images[i + 1], wrapinverso, homographies[i], cv::Size(images[i + 1].cols + images[i].cols, images[i].rows), cv::WARP_INVERSE_MAP);
    showImage("wrap", wrap);
    showImage("wrapinverso", wrapinverso);

    cv::Mat half1(wrapinverso, cv::Rect(0, 0, images[i].cols, images[i].rows));
    // cv::Mat half2(result, cv::Rect(images[i].cols, images[i].rows, images[i + 1].cols, images[i + 1].rows));

    images[i].copyTo(half1);
    showImage("result", wrapinverso);

    cv::waitKey(0);
  }

  return 0;
}