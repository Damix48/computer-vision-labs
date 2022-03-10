#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

int main(int argc, char** argv) {
  cv::Mat img = cv::imread(argv[1]);
  cv::Mat img_rotated, img_warped;

  cv::Point2f center = cv::Point2f(img.cols / 2, img.rows / 2);

  cv::Mat rotation_matrix = cv::getRotationMatrix2D(center, 45, 1);

  cv::Point2f input_points[3] = {cv::Point2f(0.f, 0.f), cv::Point2f(img.cols * 0.75, img.rows * 0.75), cv::Point2f(img.cols * 0.5, img.rows * 0.75)};
  cv::Point2f output_points[3] = {cv::Point2f(1.f, 1.f), cv::Point2f(img.cols * 0.5, img.rows * 0.75), cv::Point2f(img.cols * 0.5, img.rows * 0.75)};

  Point2f srcTri[3];
  srcTri[0] = Point2f(0.f, 0.f);
  srcTri[1] = Point2f(img.cols - 1.f, 0.f);
  srcTri[2] = Point2f(0.f, img.rows - 1.f);
  Point2f dstTri[3];
  dstTri[0] = Point2f(0.f, img.rows * 0.33f);
  dstTri[1] = Point2f(img.cols * 0.85f, img.rows * 0.25f);
  dstTri[2] = Point2f(img.cols * 0.15f, img.rows * 0.7f);

  cv::Mat warp_matrix = cv::getAffineTransform(input_points, output_points);

  cv::warpAffine(img, img_rotated, rotation_matrix, img_rotated.size());
  cv::warpAffine(img, img_warped, warp_matrix, img_warped.size());

  cv::imshow("Example 1", img_rotated);
  cv::imshow("Example 2", img_warped);

  int key = cv::waitKey(0);

  return 0;
}