#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
//CITB601 Графично програмиране, НБУ, 2016

//файл point.h. Изготвил: Ст.Иванов

#include <math.h>
#include <iostream>
const double PI=4.*atan(1.);

//Помощен клас за смятане с тримерни вектори
class Point{
	double x,y,z;	//координатите
public:
	//Конструктор. Всички оператори го ползват
	Point(double X=0.,double Y=0.,double Z=0.):x(X),y(Y),z(Z){}
	//Единичен вектор
	Point operator!()const{double m=mod();
		return Point(x/m,y/m,z/m);
	}
	//Събиране и изваждане
	Point operator +(const Point & p)const{
		return Point(x+p.x,y+p.y,z+p.z);
	}
	Point operator -(const Point & p)const{
		return Point(x-p.x,y-p.y,z-p.z);
	}
	Point operator -()const{
		return Point(-x,-y,-z);
	}
	//Векторно произведение (cross product)
	Point operator *(const Point & p)const{
		return Point(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);
	}
	//Умножение с число
	Point operator *(double d)const{
		return Point(x*d,y*d,z*d);
	}
	//Скаларно произведение (dot product)
	double operator %(const Point & p)const{
		return x*p.x+y*p.y+z*p.z;
	}
	//Модул
	double mod()const{return sqrt(*this%*this);}
	//Връща компонентите като масив (за OpenGL)
	const double * arr()const{
		return &x;
	}
    std::ostream& insert(std::ostream& os)const{
        return os<<'('<<x<<','<<y<<','<<z<<')'<<std::endl;
    }
};

std::ostream& operator<<(std::ostream & os, const Point & p){
    return p.insert(os);
}


#endif // POINT_H_INCLUDED


