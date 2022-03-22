#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv) {
  cv::Mat img = cv::imread(argv[1]);
  cv::Mat img_gray, histogram;

  cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);

  int hbins = 30, sbins = 32;
  int histSize[] = {hbins, sbins};
  // hue varies from 0 to 179, see cvtColor
  float hranges[] = {0, 180};
  // saturation varies from 0 (black-gray-white) to
  // 255 (pure spectrum color)
  float sranges[] = {0, 256};
  const float* ranges[] = {hranges, sranges};
  cv::MatND hist;
  // we compute the histogram from the 0-th and 1-st channels
  int channels[] = {0, 1};
  calcHist(&img, 1, channels, cv::Mat(),  // do not use mask
           hist, 2, histSize, ranges,
           true,  // the histogram is uniform
           false);

  double maxVal = 0;
  minMaxLoc(hist, 0, &maxVal, 0, 0);
  int scale = 10;
  cv::Mat histImg = cv::Mat::zeros(sbins * scale, hbins * 10, CV_8UC3);
  for (int h = 0; h < hbins; h++)
    for (int s = 0; s < sbins; s++) {
      float binVal = hist.at<float>(h, s);
      int intensity = cvRound(binVal * 255 / maxVal);
      cv::rectangle(histImg, cv::Point(h * scale, s * scale),
                    cv::Point((h + 1) * scale - 1, (s + 1) * scale - 1),
                    cv::Scalar::all(intensity),
                    -1);
    }

  cv::imshow("Original", img);
  cv::imshow("Gray", img_gray);
  cv::imshow("Histogram", histImg);

  // cv::imwrite(argv[2], img_gray);

  int key = cv::waitKey(0);

  return 0;
}