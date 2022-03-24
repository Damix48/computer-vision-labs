#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

void createHist(cv::Mat src, cv::Mat& hist_img, int n_bins, int hist_w = 512, int hist_h = 400);

int main(int argc, char** argv) {
  cv::Mat img = cv::imread(argv[1]);
  cv::Mat img_gray, histogram;

  cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);

  cv::Mat hist_img;
  createHist(img_gray, hist_img, 64);

  cv::Mat img_gray_eq;
  cv::equalizeHist(img_gray, img_gray_eq);

  cv::Mat hist_img_eq;
  createHist(img_gray_eq, hist_img_eq, 64);

  cv::namedWindow("Original", cv::WINDOW_NORMAL);
  cv::imshow("Original", img);

  cv::namedWindow("Gray", cv::WINDOW_NORMAL);
  cv::imshow("Gray", img_gray);

  cv::namedWindow("Histogram");
  cv::imshow("Histogram", hist_img);

  cv::namedWindow("Gray equalized", cv::WINDOW_NORMAL);
  cv::imshow("Gray equalized", img_gray_eq);

  cv::namedWindow("Histogram equalized");
  cv::imshow("Histogram equalized", hist_img_eq);

  int key = cv::waitKey(0);

  return 0;
}

void createHist(cv::Mat src, cv::Mat& hist_img, int n_bins, int hist_w, int hist_h) {
  cv::Mat hist;
  hist_img = cv::Mat(hist_h, hist_w, CV_8U);

  float range[] = {0, 256};
  const float* ranges[] = {range};
  int channels[] = {0};

  cv::calcHist(&src, 1, channels, cv::Mat(), hist, 1, &n_bins, ranges, true, false);

  int bin_w = hist_w / n_bins;

  cv::normalize(hist, hist, 0, hist_img.rows, cv::NORM_MINMAX, -1, cv::Mat());

  for (int i = 0; i < n_bins; i++) {
    cv::rectangle(
        hist_img,
        cv::Point(bin_w * i, hist_h),
        cv::Point(bin_w * (i + 1), hist_h - cvRound(hist.at<float>(i))),
        cv::Scalar(255, 0, 0),
        cv::FILLED);
  }
}