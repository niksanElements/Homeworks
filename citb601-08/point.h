#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
//CITB601 �������� ������������, ���, 2016

//���� point.h. ��������: ��.������

#include <math.h>
#include <iostream>
const double PI=4.*atan(1.);

//������� ���� �� ������� � �������� �������
class Point{
	double x,y,z;	//������������
public:
	//�����������. ������ ��������� �� �������
	Point(double X=0.,double Y=0.,double Z=0.):x(X),y(Y),z(Z){}
	//�������� ������
	Point operator!()const{double m=mod();
		return Point(x/m,y/m,z/m);
	}
	//�������� � ���������
	Point operator +(const Point & p)const{
		return Point(x+p.x,y+p.y,z+p.z);
	}
	Point operator -(const Point & p)const{
		return Point(x-p.x,y-p.y,z-p.z);
	}
	Point operator -()const{
		return Point(-x,-y,-z);
	}
	//�������� ������������ (cross product)
	Point operator *(const Point & p)const{
		return Point(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);
	}
	//��������� � �����
	Point operator *(double d)const{
		return Point(x*d,y*d,z*d);
	}
	//�������� ������������ (dot product)
	double operator %(const Point & p)const{
		return x*p.x+y*p.y+z*p.z;
	}
	//�����
	double mod()const{return sqrt(*this%*this);}
	//����� ������������ ���� ����� (�� OpenGL)
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


