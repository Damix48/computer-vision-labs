# Report on Lab 04

## Task 1
The program take 1 input: the RGB image path.
```shell
./task1/build/main image.jpg
```
To edit the Canny image without using global variable I code a `CannyImage` class.

```c++
class CannyImage {
  cv::Mat original;
  int aperture;

  cv::Mat edge;
  int threshold1;
  int threshold2;

 public:
  CannyImage(cv::Mat src, int t1 = 0, int t2 = 0, int a = 3);

  void setT1(int t1);
  void setT2(int t2);

  cv::Mat update();
};
```

I pass the pointer of `CannyImage` instance on the two callback that update the two thresohold using the two methods `setT1()` `setT2()`. Using the `.update()` method an `cv::Mat` is returned, it is the Canny image.

## Task 2
The program take 1 input: the RGB image path.
```shell
./task2/build/main image.jpg
```
For this second task I compute the first derivative on `x` and `y` using `cv::Sobel()`. After I compute the angle of the gradient using `atan2()` of the brighest pixels. The result it is the pixel with angle of about 45 and 90 degrees where the original pixels are white.

## Task 3
The program take 1 input: the RGB image path.
```shell
./task3/build/main image.jpg
```
I code a `Line` class that helped me to find the points of the two lines I get from `cv::HoughLines`. Since `cv::HoughLines` return the lines in the polar coordinates the class convert them in the cartesian.

```c++
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
```

With `getPointFromY()` I found the 2 points in the bottom of the image, with `intersection()` I found the intersection of the two lines. Using `cv::fillConvexPoly()` I drawn the triangle on the street.


# Task 4
The program take 1 input: the RGB image path.
```shell
./task4/build/main image.jpg
```

I simply blur a lot the image and used the `cv::HoughCircles()` with some custom parameters.