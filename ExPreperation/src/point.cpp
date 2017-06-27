#include "point.h"

#include <cmath>

namespace vector2d
{

Point::Point():
    x(0.0),y(0.0)
{
}

Point::Point(double x,double y):
    x(x),y(y)
{
}

Point::~Point()
{
}

Point::Point(const Point& other)
{
    this->x = other.x;
    this->y = other.y;
}

Point& Point::operator=(const Point& rhs)
{
    if (this == &rhs) return *this; // handle self assignment

    this->x = rhs.x;
    this->y = rhs.y;

    return *this;
}

double Point::getX()
{
    return this->x;
}
double Point::getY()
{
    return this->y;
}

Point Point::operator*(double k)const
{
    return Point(this->x*k,this->y*k);
}
Point Point::operator-(const Point& p)const
{
    return Point(this->x - p.x,this->y - p.y);
}

Point Point::operator+(const Point& p)const
{
    return Point(this->x + x,this->y + y);
}

double Point::operator*(const Point& p)const
{
    return this->x * x + this->y * y;
}
double Point::operator%(const Point& p)const
{
    return this->x * p.y - this->y * p.x;
}
double Point::mod()const
{
    return sqrt(this->x * this->x + this->y * this->y);
}
void Point::Draw(HWND hwnd)const
{
    POINT p = userToDisplay(*this);

    HDC hdc = GetDC(hwnd);

    Ellipse(hdc,p.x - POINT_RADIUS,p.y - POINT_RADIUS,p.x + POINT_RADIUS,p.y + POINT_RADIUS);
    // SetPixel(hdc, p.x, p.y, RGB(0,150,0));

    ReleaseDC(hwnd,hdc);
}

Point Point::operator!()const
{
    double m = mod();
    return Point(this->x/m,this->y/m);
}

}
