#ifndef SHAPE_H_
#define SHAPE_H_

#define MAX_OVJECTS 1000

#include <windows.h>


namespace vector2d
{

class Point;
class Shape;

Point displayToUser(POINT p,bool snapOn = false);
POINT userToDisplay(Point);


double roundd(double d,int gridDens = 1);
void drawAxes(HWND hwnd);
void LineBres(HDC hdc,POINT a,POINT b,COLORREF c = RGB(0,150,0));
void Ellipse(HDC hdc,POINT cen,int a,int b,COLORREF c = RGB(0,150,0));
void Circle(HDC hdc,POINT cen,int rad,COLORREF c = RGB(0,150,0));
void EquilateralTriangle(HDC hdc,Point c,Point mc,COLORREF col = RGB(0,150,0));
void rhomb(HDC hdc,Point a,Point b,COLORREF col = RGB(0,150,0));
void Poligon(HDC hdc,POINT cen,int rad,int n,COLORREF col = RGB(0,150,0));
void Star(HDC hdc,POINT cen,int rad,int p = 5,int q = 7,COLORREF col = RGB(0,150,0));
void FillEquilateralTriangle(HDC hdc,Point c,Point mc,COLORREF col = RGB(0,150,0));
void test(HDC hdc,POINT a,POINT b,COLORREF col = RGB(0,150,0));

/* Reqursive functions */
void hexagon(HDC hdc,POINT a,POINT b,int n,COLORREF col = RGB(0xFF,0x00,0x00));
void hexagon_2(HDC hdc,POINT a,POINT b,int n,COLORREF col = RGB(0xFF,0x00,0x00));


typedef struct sShapeObjectes
{
    Shape * pt[MAX_OVJECTS];       //shape buffer
    UINT iCount = 0;              //count of shapes
    char currentShape = 'p';      //
    char charBuf[120];
    POINT pntBuf[100];            //point buffer
    int pntGot;                   //free point
    int pntsToTake = 1;
    int sidesRegPoly =3;
    bool scaleIsotropic = false;
    bool snapOn = false;
    int gridDens = 1;
    double mx, my;
}ShapeObjectes;


const double PI = 3.1415926536;
const int POINT_RADIUS = 4;
const int USERX = 12;
const int USERY = 10;
const int HH = 500;
const int WW = 500;

class Shape
{
public:
    virtual void Draw(HWND) const = 0;
};

}
#endif // SHAPE_H_
