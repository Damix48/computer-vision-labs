#include <iostream>
#include <opencv2/highgui.hpp>

class RGB {
 public:
  int r, g, b;

  RGB(int _r = 0, int _g = 0, int _b = 0) : r(_r), g(_g), b(_b) {}
  RGB(const cv::Vec3b pixel) : r(pixel[2]), g(pixel[1]), b(pixel[0]) {}

  RGB operator+(const RGB& rgb) {
    return RGB(r + rgb.r, g + rgb.g, b + rgb.b);
  }

  RGB operator-(const RGB& rgb) {
    return RGB(r - rgb.r, g - rgb.g, b - rgb.b);
  }

  RGB operator/(const int& a) {
    return RGB(r / a, g / a, b / a);
  }

  friend std::ostream& operator<<(std::ostream& os, const RGB& rgb);

  bool isInThreshold(const RGB& mean, int threshold) {
    return (abs(r - mean.r) < threshold) && (abs(g - mean.g) < threshold) && (abs(b - mean.b) < threshold);
  }
};

std::ostream& operator<<(std::ostream& os, const RGB& rgb) {
  os << "(" << rgb.r << ", " << rgb.g << ", " << rgb.b << ")";
  return os;
}

RGB kernelMean(cv::Mat& src, int x, int y, int kernelSize) {
  RGB sum = RGB(0, 0, 0);

  int n_pixels = 0;

  for (int k = -kernelSize / 2; k < kernelSize / 2 + 1; k++) {
    for (int w = -kernelSize / 2; w < kernelSize / 2 + 1; w++) {
      if ((y + k > 0) && (y + k < src.rows) && (x + w > 0) && (x + k < src.cols)) {
        cv::Vec3b pixel = src.at<cv::Vec3b>(y + k, x + w);

        sum = sum + pixel;

        n_pixels++;
      }
    }
  }

  RGB mean = sum / n_pixels;

  return mean;
}

void onMouse(int event, int x, int y, int, void* _img) {
  cv::Mat* img = static_cast<cv::Mat*>(_img);

  if (event == cv::EVENT_LBUTTONUP) {
    RGB mean = kernelMean(*img, x, y, 9);
    std::cout << "Color mean (9x9) around (" << x << ", " << y << "): " << mean << std::endl;
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