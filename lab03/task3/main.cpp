#include <iostream>
#include <opencv2/highgui.hpp>

void onMouse(int event, int x, int y, int, void* _img) {
  cv::Mat* img = static_cast<cv::Mat*>(_img);

  if (event == cv::EVENT_LBUTTONUP) {
    int kernel_size = 9;
    int sum_b = 0;
    int sum_g = 0;
    int sum_r = 0;
    int n_pixels = 0;
    for (int k = -kernel_size / 2; k < kernel_size / 2 + 1; k++) {
      for (int w = -kernel_size / 2; w < kernel_size / 2 + 1; w++) {
        if ((y + k > 0) && (y + k < img->rows) && (x + w > 0) && (x + k < img->cols)) {
          cv::Vec3b pixel = img->at<cv::Vec3b>(y + k, x + w);
          sum_b += pixel[0];
          sum_g += pixel[1];
          sum_r += pixel[2];

          n_pixels++;
        }
      }
    }

    std::cout << "Color mean (9x9) around ("
              << x << ", " << y << "): ("
              << sum_b / n_pixels << ", "
              << sum_g / n_pixels << ", "
              << sum_r / n_pixels << ")"
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