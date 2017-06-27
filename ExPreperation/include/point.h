#ifndef POINT_H_
#define POINT_H_

#include "shape.h"

namespace vector2d
{

class Point : public Shape
{
    public:
        /** Default constructor */
        Point();
        Point(double x,double y);
        Point(POINT p);
        /** Default destructor */
        virtual ~Point();
        /** Copy constructor
         *  \param other Object to copy from
         */
        Point(const Point& other);
        /** Assignment operator
         *  \param other Object to assign from
         *  \return A reference to this
         */
        Point& operator=(const Point& other);

        double getX();
        double getY();

        Point operator!()const;
        Point operator*(double k)const;
        Point operator-(const Point& p)const;
        Point operator+(const Point& p)const;
        double operator*(const Point& p)const;
        double operator%(const Point& p)const;
        double mod()const;
        virtual void Draw(HWND hwnd)const;

        double x;
        double y;

    protected:

    private:
};

}
#endif // POINT_H_
