#include <math.h>

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

void findStreetLineInThisParticularImage(const cv::Mat& src, cv::Mat& dst) {
  int tollearance = 3;

  if (dst.rows != src.rows && dst.cols != src.rows) {
    dst = cv::Mat(src.rows, src.cols, CV_8U);
  }

  cv::Mat x = cv::Mat::zeros(src.rows, src.cols, CV_8U);
  cv::Mat y = cv::Mat::zeros(src.rows, src.cols, CV_8U);

  cv::Sobel(src, x, CV_8U, 1, 0);
  cv::Sobel(src, y, CV_8U, 0, 1);

  for (int i = 0; i < dst.rows - 1; i++) {
    for (int j = 0; j < dst.cols - 1; j++) {
      float dx = x.at<u_char>(i, j);
      float dy = y.at<u_char>(i, j);
      if (dx > 100 || dy > 100) {
        if (src.at<uchar>(i, j) > 220) {
          float theta = atan2(dy, dx) * 180 / M_PI;
          if ((theta > 45 - tollearance && theta < 45 + tollearance) || (theta > 90 - tollearance && theta < 90 + tollearance)) {
            dst.at<uchar>(i, j) = 255;
          }
        }
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
  cv::Mat imgGray, lines;

  cv::GaussianBlur(img, img, cv::Size(3, 3), 0, 0);

  cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

  findStreetLineInThisParticularImage(imgGray, lines);

  cv::namedWindow("Lines", cv::WINDOW_NORMAL);
  cv::imshow("Lines", lines);

  cv::waitKey(0);

  return 0;
}