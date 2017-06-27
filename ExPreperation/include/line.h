#ifndef LINE_H_
#define LINE_H_

#include "point.h"
#include <windows.h>

namespace vector2d
{

class Line: public Shape
{
    public:
        Line(Point a, Point b);
        Line(Point a,Point k,int);
        Line(POINT A,POINT B);

        /** Default destructor */
        virtual ~Line();

        Point getStartPoint() const;
        Point getEndPoint() const;

        bool operator>(const Point& p)const;
        double operator==(const Line& l)const;

        virtual void Draw(HWND hwnd)const;

    protected:

    private:
        Point a;
        Point b;
        Point k;
};

}

#endif // LINE_H_
