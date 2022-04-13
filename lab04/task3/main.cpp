#include <math.h>

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

#include "canny_image.h"
#include "line.h"

void getEdgesInWhiteMarking(const cv::Mat& src, const cv::Mat& edges, cv::Mat& dst, int tollerance = 40) {
  if (dst.rows != src.rows && dst.cols != src.rows) {
    dst = cv::Mat::zeros(src.rows, src.cols, CV_8U);
  }

  for (int i = 0; i < dst.rows; i++) {
    for (int j = 0; j < dst.cols; j++) {
      if (src.at<uchar>(i, j) > 255 - tollerance && edges.at<uchar>(i, j) == 255) {
        dst.at<uchar>(i, j) = 255;
      }
    }
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "You need to pass a path to an image." << std::endl;
    return EXIT_FAILURE;
  }

  cv::Mat img = cv::imread(argv[1]);
  cv::Mat imgGray, edges, whiteEdges;
  std::vector<cv::Vec2f> houghLines;
  std::vector<Line> lines;

  cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

  CannyImage cannyEdges(img, 100, 400);

  edges = cannyEdges.update();
  getEdgesInWhiteMarking(imgGray, edges, whiteEdges);

  cv::HoughLines(whiteEdges, houghLines, 1, CV_PI / 90, 20, 0);

  for (size_t i = 0; i < 2; i++) {
    float rho = houghLines[i][0], theta = houghLines[i][1];

    Line line = Line::fromPolar(theta, rho);
    lines.push_back(line);

    cv::line(img, line.getPointFromY(0), line.getPointFromY(img.rows), cv::Scalar(255, 0, 0), 1, cv::LINE_AA);
  }

  std::vector<cv::Point> points;
  points.push_back(lines[0].getPointFromY(img.rows));
  points.push_back(lines[1].getPointFromY(img.rows));
  points.push_back(Line::intersection(lines[0], lines[1]));

  cv::fillConvexPoly(img, points, cv::Scalar(0, 0, 255));

  cv::namedWindow("Gray", cv::WINDOW_NORMAL);
  cv::imshow("Gray", img);

  cv::waitKey(0);

  return 0;
}