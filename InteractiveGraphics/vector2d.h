#ifndef VECTOR_2D_H_
#define VECTOR_2D_H_

/************************************************************************/
/* Frame work for 2d graphics vectors.                                  */
/************************************************************************/

#include <cmath>
#include <windows.h>

const double PI = 3.1415926536;

//Интерфейс за геометрични обекти:
//Възможност за визуализация
class Shape{
public:
	virtual void draw(HWND)const =0;
};

class Point;

//Преобразувания между дисплейни и потребителски координати
//Дефиницията е в grserv.h
Point dispToUser(POINT);
POINT userToDisp(Point);

//Точка в равнината, представена като вектор
class Point:public Shape{
	double x;
	double y;
public:
	Point() :x(0.0), y(0.0){}
	Point(double x, double y) :x(x), y(y){}
	//Конструктор от дисплейно зададена точка
	Point(POINT p){*this = dispToUser(p);}
	double getX() const { return x; }
	double getY() const { return y; }
	//Векторни операции:
	//Мащабиране
	Point operator *(double k)const { return Point(x*k, y*k); }
	//Изваждане
	Point operator -(const Point& b)const{
		return Point(x - b.x, y - b.y);
	}
	//Събиране
	Point operator +(const Point& b)const{
		return Point(x + b.x, y + b.y);
	}
	//Единичен вектор
	Point operator !()const{
		double m = mod(); return Point(x / m, y / m);
	}
	//Завъртян наляво под прав ъгъл
	Point rotL() const { return Point(-y, x); }
	//Завъртян надясно под прав ъгъл
	Point rotR() const { return Point(y, -x); }
	//Завъртян на ъгъл в градуси
	Point rotA(double a) const {
		double ar = a*PI / 180., si = sin(ar), co = cos(ar);
		return *this*co + rotL()*si;
	}
	//Скаларно произведение
	double operator *(const Point& b)const{ return x*b.x + y*b.y; }
	//Векторно произведение (стойност на компонентата z с обратен знак)
	double operator %(const Point& q)const{ return q.x*y - x*q.y; }
	//Модул на вектор
	double mod()const{ return sqrt(*this * *this); }
	bool operator==(const Point& p) const {
		return (*this - p).mod()<1e-10;
	}
	//Изобразяване в прозорец (точката като кръгче)
	void draw(HWND hwnd)const{
		static const int POINT_RADIUS = 3;
		POINT p = userToDisp(*this);
		HDC hdc = GetDC(hwnd);
		Ellipse(hdc, p.x - POINT_RADIUS, p.y - POINT_RADIUS,
			p.x + POINT_RADIUS, p.y + POINT_RADIUS);
		SetPixel(hdc, p.x, p.y, RGB(0,150,0));
		ReleaseDC(hwnd, hdc);
	}
};


#endif
