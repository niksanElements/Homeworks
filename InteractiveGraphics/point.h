
#ifndef POINT_H_
#define  POINT_H_

#include <math.h>

static const double PI = 3.1415926536;

class Point {
	double x;
	double y;
public:
	Point() :x(0.0), y(0.0) {}
	Point(double x, double y) :x(x), y(y) {}
	double getX() const { return x; }
	double getY() const { return y; }
	Point operator *(double k)const { return Point(x*k, y*k); }
	Point operator -(const Point& b)const {
		return Point(x - b.x, y - b.y);
	}
	Point operator +(const Point& b)const {
		return Point(x + b.x, y + b.y);
	}
	Point operator !()const {
		double m = mod(); return Point(x / m, y / m);
	}
	Point rotL() const { return Point(-y, x); }
	Point rotR() const { return Point(y, -x); }
	Point rotA(double a) const {
		double ar = a*PI / 180., si = sin(ar), co = cos(ar);
		return *this*co + rotL()*si;
	}
	double operator *(const Point& b)const { return x*b.x + y*b.y; }
	double operator %(const Point& q)const { return q.x*y - x*q.y; }
	double mod()const { return sqrt(*this * *this); }
	bool operator==(const Point& p) const {
		return (*this - p).mod() < 1e-10;
	}
};

#endif