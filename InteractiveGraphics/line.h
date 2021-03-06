#ifndef LINE_H_
#define LINE_H_

#include "point.h"

class Line {
	Point a, b, k; //?????? ????? ?? ??????? ? ??????????? ??????
public:
	Line(Point a, Point k, int) :a(a), b(a + k), k(!k) {}
	Line(Point a, Point b) :a(a), b(b), k(!(b - a)) {}
	Point getA()const { return a; }
	Point getB()const { return b; }
	//????? ??????? ?????
	bool operator >(const Point& p)const {
		return (a - k*((p - a)*k)).mod() < 1e-10;
	}
	bool operator==(const Line& L) const { return *this > L.a && L > a; }
	//??????????? ?? ?????
	bool operator||(const Line& L) const { return k%L.k < 1e-10; }
	//????????? ?? ?????
	Point operator%(const Line& L) const {
		if (*this || L) return k*1e10;
		double d = k%L.k, d2 = k % (a - L.a);
		return L.a + L.k*(d2 / d);
	}
};


#endif
