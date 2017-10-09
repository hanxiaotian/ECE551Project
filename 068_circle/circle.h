#include "point.h"

class Circle{
 private:
  Point center;
  const double radius;
 public:
 Circle(Point point, double num):center(point),radius(num){}
  double getr() const {return radius;}
  void move(double dx, double dy){center.move(dx,dy);}
  Point getCenter() const {return center;}
  double distanceCenter(const Circle & otherCircle){return center.distanceFrom(otherCircle.getCenter());}
  double intersectionArea(const Circle & otherCircle);
};
