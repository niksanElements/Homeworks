#ifndef POLY_OPEN_H_
#define POLY_OPEN_H_

#include "point.h"
#include <Windows.h>

extern Point dispToUser(POINT);

class PolyOpen {
	Point * pnts; int n;
public:
	PolyOpen(Point * p, int n) :n(n) {
		pnts = new Point[n];
		for (int i = 0; i < n; i++)pnts[i] = p[i];
	}
	//??????????? ?? ????? ?? ??????? ?????
	PolyOpen(POINT * p, int n) :n(n) {
		pnts = new Point[n];
		for (int i = 0; i < n; i++)pnts[i] = dispToUser(p[i]);
	}

	const Point * getP()const { return pnts; }
	int getSz()const { return n; }
};


#endif
