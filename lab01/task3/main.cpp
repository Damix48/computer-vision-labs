#include <iostream>
#include <opencv2/highgui.hpp>

void create_chessboard(cv::Mat& image, int size);

int main(int argc, char** argv) {
  int size = 256;

  cv::Mat img1 = cv::Mat(size, size, CV_8UC1);
  cv::Mat img2 = cv::Mat(size, size, CV_8UC1);

  size = 300;

  cv::Mat img3 = cv::Mat(size, size, CV_8UC1);
  cv::Mat img4 = cv::Mat(size, size, CV_8UC1);

  for (int i = 0; i < img1.rows; i++) {
    for (int j = 0; j < img1.cols; j++) {
      img1.at<unsigned char>(i, j) = static_cast<unsigned char>(i);
    }
  }

  for (int i = 0; i < img2.rows; i++) {
    for (int j = 0; j < img2.cols; j++) {
      img2.at<unsigned char>(j, i) = static_cast<unsigned char>(i);
    }
  }

  create_chessboard(img3, 20);
  create_chessboard(img4, 30);

  cv::imshow("Example 1", img1);
  cv::imshow("Example 2", img2);
  cv::imshow("Example 3", img3);
  cv::imshow("Example 4", img4);

  char key = cv::waitKey(0);
  std::cout << key << std::endl;

  return 0;
}

void create_chessboard(cv::Mat& image, int size) {
  for (int i = 0; i < image.rows; i++) {
    for (int j = 0; j < image.cols; j++) {
      if ((j / size) % 2 == 0) {
        if ((i / size) % 2 == 0) {
          image.at<unsigned char>(i, j) = 255;
        } else {
          image.at<unsigned char>(i, j) = 0;
        }
      } else {
        if ((i / size) % 2 == 0) {
          image.at<unsigned char>(i, j) = 0;
        } else {
          image.at<unsigned char>(i, j) = 255;
        }
      }
    }
  }
}
