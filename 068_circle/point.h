#include <iostream>

using namespace std;

class Point{
 private:
  double x;
  double y;
 public:
  Point():x(0),y(0){}
  void move(double dx, double dy){
    x+=dx;
    y+=dy;
  }
  double getx() const {return x;}
  double gety() const {return y;}
  double distanceFrom (const Point &p);
};
