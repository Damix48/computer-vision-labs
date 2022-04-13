#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "You need to pass a path to an image." << std::endl;
    return EXIT_FAILURE;
  }

  cv::Mat img = cv::imread(argv[1]);
  cv::Mat imgGray;
  std::vector<cv::Vec3f> houghCircles;

  cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

  cv::GaussianBlur(imgGray, imgGray, cv::Size(5, 5), 2, 2);

  cv::HoughCircles(imgGray, houghCircles, cv::HOUGH_GRADIENT, 1, img.rows / 8, 100, 20, 1, 20);

  for (size_t i = 0; i < houghCircles.size(); i++) {
    float x = houghCircles[i][0], y = houghCircles[i][1], r = houghCircles[i][2];
    cv::circle(img, cv::Point(x, y), r, cv::Scalar(0, 255, 0), cv::FILLED, cv::LINE_AA);
  }

  cv::namedWindow("Gray", cv::WINDOW_NORMAL);
  cv::imshow("Gray", img);

  cv::waitKey(0);

  return 0;
}