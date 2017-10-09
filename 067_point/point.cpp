#include "point.h"
#include <cmath>

double Point::distanceFrom(const Point &p){
  return std::sqrt(std::pow(this->x-p.getx(),2)+std::pow(this->y-p.gety(),2));
}
