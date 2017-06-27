#ifndef GTESERV_H_
#define GTESERV_H_

#include "vector2d.h"
#include "rasterization.h"
#include <Windows.h>


extern int USERX, USERY, WW, HH;

//Равнинни геометрични обекти с функции за изобразяване
//Всички класове задължително припокриват функцията void draw(HWND)const

//Чертае отсечка
inline void drawLine(HWND hwnd, POINT a, POINT b){
	HDC hdc = GetDC(hwnd);
	//SetDCBrushColor(hdc, RGB(240,255,0));
	    lineBres(hdc, a, b, RGB(0,230,150));
	ReleaseDC(hwnd, hdc);
}

//Права (и отсечка) в равнината
class Line:public Shape{
	Point a, b, k; //крайни точки на отсечка и направляващ вектор
public:
	Line(Point a, Point k, int) :a(a), b(a + k), k(!k){}
	Line(Point a, Point b) :a(a), b(b), k(!(b - a)){}
	//Конструктор от дисплейно зададени точки
	Line(POINT A, POINT B){
		a=dispToUser(A), b=dispToUser(B); k=!(b-a);
	}
	Point getA()const{ return a; }
	Point getB()const{ return b; }
	//Отношения между геометрични обекти:
	//Права включва точка
	bool operator >(const Point& p)const{
		return (a - k*((p - a)*k)).mod()<1e-10;
	}
	//Съвпадение на прави
	bool operator==(const Line& L) const { return *this>L.a && L>a; }
	//Успоредност на прави
	bool operator||(const Line& L) const { return fabs(k%L.k)<1e-10; }
	//Пресичане на прави
	Point operator%(const Line& L) const {
		//при успоредност или съвпадение резултатът не е точка
		//условно се задава горният десен ъгъл на полето
		if (*this || L) return Point(USERX,USERY);
		double d = k%L.k, d2 = k % (a - L.a);
		return L.a + L.k*(d2 / d);
	}
	void draw(HWND hwnd)const{
		POINT p1 = userToDisp(a), p2 = userToDisp(b);
		drawLine(hwnd, p1, p2);
	}
};

//Отворен многоъгълник в равнината
class PolyOpen:public Shape{
	Point * pnts; int n;
public:
	PolyOpen(Point * p, int n) :n(n){
		pnts = new Point[n];
		for (int i = 0; i<n; i++)pnts[i] = p[i];
	}
	//Конструктор от масив от екранни точки
	PolyOpen(POINT * p, int n) :n(n){
		pnts = new Point[n];
		for (int i = 0; i<n; i++)pnts[i] = dispToUser(p[i]);
	}
	void draw(HWND hwnd)const{
		for (int i = 1; i<n; i++)
			Line(pnts[i], pnts[i - 1]).draw(hwnd);
	}
};

//Затворен многоъгълник в равнината
class PolyClosed:public Shape{
protected:
	Point * pnts; int n;
public:
	PolyClosed(int n=0):n(n){pnts = new Point[n+1];}
	PolyClosed(Point * p, int n) :n(n){
		pnts = new Point[n+1];
		for (int i = 0; i<n; i++)pnts[i] = p[i];
		pnts[n] = pnts[0];
	}
	//Конструктор от масив от екранни точки
	PolyClosed(POINT * p, int n) :n(n){
		pnts = new Point[n+1];
		for (int i = 0; i<n; i++)pnts[i] = dispToUser(p[i]);
		pnts[n] = pnts[0];
	}
	void draw(HWND hwnd)const{
		for (int i = 1; i<=n; i++)
			Line(pnts[i], pnts[i - 1]).draw(hwnd);
	}
};

//Правилен многоъгълник
class PolyRegular: public PolyClosed {
	Point center, appex;
public:
	PolyRegular(Point c, Point a, int n):PolyClosed(n), center(c), appex(a){
		Point r = appex-center;
		for(int i=0;i<=n;i++)pnts[i]=center + r.rotA(360./n*i);
	}
	PolyRegular(POINT c, POINT a, int n): PolyClosed(n){
		center = dispToUser(c), appex = dispToUser(a);
		Point r = appex-center;
		for(int i=0;i<=n;i++)pnts[i]=center + r.rotA(360./n*i);
	}
	//изобразяването се наследява
};

//Окръжност
class Circle:public Shape{
	Point center; double r;
public:
	Circle():center(Point()),r(0.){}
	Circle(Point c, Point b):center(c), r((b-c).mod()){}
	Circle(POINT c, POINT b):center(dispToUser(c)){
		r=(dispToUser(b)-center).mod();
	}
	void draw(HWND hwnd)const{
		POINT cn = userToDisp(center);
		//при анизотропно мащабиране окръжността е елипса
		int a = userToDisp(Point(r,0.)).x - WW/2;
		int b = HH/2-userToDisp(Point(0.,r)).y;
		HDC hdc = GetDC(hwnd);
			ellipse(hdc, cn, a, b, RGB(0,150,0));
		ReleaseDC(hwnd, hdc);
	}
};

//Добавяне на нови класове:

//Квадрат по две диагонални точки.
class Square:public Shape{
	Point a, b, c, d;
public:
	Square(POINT A, POINT C){
		a = dispToUser(A), c = dispToUser(C);
		Point ac = (c-a)*0.5;
		b = a + ac + ac.rotR(), d = a + ac - ac.rotR();
	}
	void draw(HWND hwnd)const{
		Line(a,b).draw(hwnd);Line(c,b).draw(hwnd);
		Line(a,d).draw(hwnd);Line(c,d).draw(hwnd);
	}
};

//Правоъгълник по краищата на една страна и точка,
//през която минава насрещната страна
class CRectangle: public Shape{
	Point a, b, c, d;
public:
	CRectangle(POINT A, POINT B, POINT M){
		a = dispToUser(A), b = dispToUser(B);
		Point ab = (b-a), p=ab.rotL(); Line L(Point(M),ab,1);
		c = L%Line(b,p,1), d=L%Line(a,p,1);
	}
	void draw(HWND hwnd)const{
		Line(a,b).draw(hwnd);Line(c,b).draw(hwnd);
		Line(a,d).draw(hwnd);Line(c,d).draw(hwnd);
	}
};

//Окръжност през 3 точки
class Circumscriber: public Shape{
	Circle cr;
public:
	Circumscriber(POINT A, POINT B, POINT C){
		Point a(A), b(B), c(C);
		Point ab = b-a, bc = c-b;
		Line s1(a+ab*0.5, ab.rotL(),1),s2(b+bc*0.5, bc.rotL(),1);
		cr = Circle(s1%s2, a);
	}
	void draw(HWND hwnd)const{cr.draw(hwnd);}
};

// TODO: Proper calculation for the Triangle
class EquilateralTriengle: public Shape {
    POINT a,b,c,d;
public:
    EquilateralTriengle(POINT p1, POINT p2){
        c = p1; d = p2;

        double dist_os = 4;

        double dist_bed = 6;

        Point C = dispToUser(p1);
        Point D = dispToUser(p2);

        double dist = sqrt(pow(C.getX() - D.getX(),2)+ pow(C))

        Point A = C.rotA(-30.) - Point(0,6.);
        a = userToDisp(A);

    }
    void draw(HWND hwnd) const{
        drawLine(hwnd,c,d);
        drawLine(hwnd,a,c);
    }
};

#endif // GTESERV_H_
