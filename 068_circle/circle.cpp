#include <cmath>
#include "circle.h"
#define PI 3.14159

using namespace std;

double Circle::intersectionArea(const Circle & otherCircle){
  if(this==&otherCircle) return PI*pow(radius, 2);
  double d=distanceCenter(otherCircle);
  if(d>radius+otherCircle.getr()) return 0;
  if(abs(radius-otherCircle.getr())>d) return PI*pow((radius>otherCircle.getr()?otherCircle.getr():radius), 2);
  double a1=acos((radius*radius+d*d-otherCircle.getr()*otherCircle.getr())/(2*radius*d));
  double a2=acos((otherCircle.getr()*otherCircle.getr()+d*d-radius*radius)/(2*otherCircle.getr()*d));
  return (a1*radius*radius+a2*otherCircle.getr()*otherCircle.getr()-radius*d*sin(a1));  
}
