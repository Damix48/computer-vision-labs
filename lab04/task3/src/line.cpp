#include "line.h"

#include <math.h>

#include <opencv2/core.hpp>

Line::Line(float i, float j, bool cartesian) {
  if (cartesian) {
    m = i;
    q = j;
  } else {
    float a = cos(i), b = sin(i);

    m = (-a / b);
    q = (j / b);
  }
}

Line Line::fromPolar(float _theta, float _rho) {
  return Line(_theta, _rho, false);
}
Line Line::fromCartesian(float _m, float _q) {
  return Line(_m, _q, true);
}

cv::Point2d Line::intersection(const Line& line1, const Line& line2) {
  float x = (line2.q - line1.q) / (line1.m - line2.m);
  return line1.getPointFromX(x);
}

cv::Point2d Line::getPointFromX(float x) const {
  float y = m * x + q;
  return cv::Point2d(x, y);
}

cv::Point2d Line::getPointFromY(float y) const {
  float x = (y - q) / m;
  return cv::Point2d(x, y);
}