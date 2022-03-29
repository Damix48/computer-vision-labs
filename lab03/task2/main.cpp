#include <iostream>
#include <opencv2/highgui.hpp>

void onMouse(int event, int x, int y, int, void* _img) {
  cv::Mat* img = static_cast<cv::Mat*>(_img);

  if (event == cv::EVENT_LBUTTONUP) {
    cv::Vec3b pixel = img->at<cv::Vec3b>(y, x);
    std::cout << "Color at ("
              << x << ", " << y << "): ("
              << (int)pixel[0] << ", "
              << (int)pixel[1] << ", "
              << (int)pixel[2] << ")"
              << std::endl;
  }
}

int main(int argc, char** argv) {
  cv::Mat img = cv::imread(argv[1]);

  cv::namedWindow("Image");
  cv::imshow("Image", img);

  cv::setMouseCallback("Image", onMouse, &img);

  cv::waitKey(0);

  return 0;
}