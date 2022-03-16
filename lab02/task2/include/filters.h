#include <opencv2/highgui.hpp>

void min_filter(int kernel_size, cv::Mat src, cv::Mat dst);
void max_filter(int kernel_size, cv::Mat& image);