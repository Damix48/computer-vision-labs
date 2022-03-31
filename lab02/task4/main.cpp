#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {
  cv::Mat img_gray = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  cv::Mat histogram;

  cv::Mat hist;

  int histSize = 256;
  float range[] = {0, 256};
  const float* ranges[] = {range};
  int channels[] = {0};

  cv::calcHist(&img_gray, 1, channels, cv::Mat(), hist, 1, &histSize, ranges, true, false);

  int hist_w = 512, hist_h = 400;
  int bin_w = cvRound((double)hist_w / histSize);

  cv::Mat hist_img = cv::Mat(hist_h, hist_w, CV_8U);

  cv::normalize(hist, hist, 0, hist_img.rows, cv::NORM_MINMAX, -1, cv::Mat());

  for (int i = 0; i < histSize; i++) {
    cv::rectangle(
        hist_img,
        cv::Point(bin_w * i, hist_h),
        cv::Point(bin_w * (i + 1), hist_h - cvRound(hist.at<float>(i))),
        cv::Scalar(255, 0, 0),
        -1,
        8);
  }

  cv::namedWindow("Gray", cv::WINDOW_NORMAL);
  cv::imshow("Gray", img_gray);

  cv::namedWindow("Histogram");
  cv::imshow("Histogram", hist_img);

  int key = cv::waitKey(0);

  return 0;
}