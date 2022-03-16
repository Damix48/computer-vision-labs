#include <opencv2/highgui.hpp>

void min_filter(cv::Mat src, cv::Mat& dst, int kernel_size);
void max_filter(cv::Mat src, cv::Mat& dst, int kernel_size);