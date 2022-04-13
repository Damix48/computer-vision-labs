#ifndef LINE_H
#define LINE_H

#include <opencv2/core.hpp>

class Line {
  float m;
  float q;

  Line(float _m, float _q, bool cartesian);

 public:
  static Line fromPolar(float _theta, float rho);
  static Line fromCartesian(float _m, float _q);

  static cv::Point2d intersection(const Line& line1, const Line& line2);

  cv::Point2d getPointFromX(float x) const;
  cv::Point2d getPointFromY(float y) const;
};
#endif  // LINE_H