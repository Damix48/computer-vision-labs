#include <math.h>

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {
  cv::Mat img = cv::imread(argv[1]);
  cv::Mat imgGray, laplacian;

  cv::GaussianBlur(img, img, cv::Size(3, 3), 0, 0);

  cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

  cv::Mat dst = cv::Mat::zeros(imgGray.rows, imgGray.cols, CV_8U);
  cv::Mat x = cv::Mat::zeros(imgGray.rows, imgGray.cols, CV_8U);
  cv::Mat y = cv::Mat::zeros(imgGray.rows, imgGray.cols, CV_8U);

  // cv::Mat_<int> kernelX(2, 1);
  // cv::Mat_<int> kernelY(1, 2);
  cv::Mat_<int> kernelX(3, 3);
  cv::Mat_<int> kernelY(3, 3);

  // kernelX << -1, 1;
  // kernelY << -1, 1;
  // kernelX << -1, -1, -1, 2, 2, 2, -1, -1, -1;
  // kernelY << -1, 2, -1, -1, 2, -1, -1, 2, -1;
  kernelX << -1, -2, -1, 0, 0, 0, 1, 2, 1;
  kernelY << -1, 0, 1, -2, 0, 2, -1, 0, 1;

  cv::filter2D(imgGray, x, CV_8U, kernelX);
  cv::filter2D(imgGray, y, CV_8U, kernelY);

  cv::Laplacian(imgGray, laplacian, CV_8U);

  // cv::Sobel(imgGray, x, CV_8U, 1, 0);
  // cv::Sobel(imgGray, y, CV_8U, 0, 1);

  cv::imshow("laplacian", laplacian);
  cv::imshow("x", x);
  cv::imshow("y", y);

  // cv::Mat theta = cv::Mat(x.rows, x.cols, CV_16F);

  cv::Mat temp = cv::Mat::zeros(x.rows, x.cols, CV_8UC3);
  cv::Mat angles;

  cv::cvtColor(temp, angles, cv::COLOR_BGR2HLS);

  for (int i = 0; i < dst.rows - 1; i++) {
    for (int j = 0; j < dst.cols - 1; j++) {
      float dx = x.at<u_char>(i, j);
      float dy = y.at<u_char>(i, j);
      if (dx > 50 || dy > 50) {
        float tetha = atan2(dy, dx) * 180 / M_PI;
        // if ((tetha > 43 && tetha < 47)) {
          angles.at<cv::Vec3b>(i, j)[0] = atan(dy / dx) * 180 * 4 / M_PI;
          angles.at<cv::Vec3b>(i, j)[1] = 100;
          angles.at<cv::Vec3b>(i, j)[2] = 50;
        // }
      }
    }
  }

  cv::cvtColor(angles, temp, cv::COLOR_HLS2BGR);

  cv::namedWindow("Image", cv::WINDOW_NORMAL);
  cv::imshow("Image", imgGray);
  cv::imshow("Angles", angles);

  for (int i = 0; i < dst.rows - 1; i++) {
    for (int j = 0; j < dst.cols - 1; j++) {
      if (y.at<u_char>(i, j) > 50) {
        if (imgGray.at<u_char>(i, j) > 220) {
          dst.at<u_char>(i, j) = 255;
          if (imgGray.at<u_char>(i, j + 1) > 220) {
            y.at<u_char>(i, j + 1) = 255;
          }
          if (imgGray.at<u_char>(i + 1, j) > 220) {
            y.at<u_char>(i + 1, j) = 255;
          }
        }
      }
    }
  }

  cv::imshow("dest", dst);

  cv::waitKey(0);

  return 0;
}