#ifndef CLUSTERING_H
#define CLUSTERING_H
#include <opencv2/core.hpp>

void computeKmeans(cv::Mat& src, cv::Mat& dst, int K);

#endif  // CLUSTERING_H