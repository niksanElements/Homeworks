#include "line.h"

namespace vector2d
{

Line::Line(Point a, Point b):
    a(a),b(b),k(b - a)
{}

Line::Line(Point a,Point k,int):
    a(a),b(a+k),k(k)
{}

Line::Line(POINT A,POINT B)
{
    a = displayToUser(A);
    a = displayToUser(B);
    k = a + k;
}

/** Default destructor */
Line::~Line()
{}

Point Line::getStartPoint() const
{
    return this->a;
}
Point Line::getEndPoint() const
{
    return this->b;
}

bool Line::operator>(const Point& p)const
{
    Point p1 = this->a - p;
    Point p2 = this->b - p;

    return p1*p2 == p1.mod()*p2.mod();
}
double Line::operator==(const Line& l)const
{
    return *this > l.a && *this > l.b;
}

void Line::Draw(HWND hwnd)const
{
    POINT A = userToDisplay(this->a);
    POINT B = userToDisplay(this->b);
    HDC hdc = GetDC(hwnd);
    LineBres(hdc,A,B);
    ReleaseDC(hwnd,hdc);
}

}
