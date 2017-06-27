#ifndef UTIL_H_
#define UTIL_H_


namespace util
{

    typedef struct
    {
        double x;
        double y;
        double z;
    }Point;

    template<typename T>
    void swap(T& a, T& b)
    {
        T c = a;
        a = b;
        b = c;
    }

    Point vectorProduct(Point &p1,Point &p2)
    {
        Point n
        {
            p1.y * p2.z - p2.y * p1.z,
            -(p1.x*p2.z - p2.x*p1.z),
            p1.x * p2.y - p2.x*p1.y
        };

        return n;
    }

}

#endif // UTIL_H_
