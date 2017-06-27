#include "shape.h"

#include "point.h"
#include <cmath>
#include <algorithm>

namespace vector2d
{
    double roundd(double x,int gridDens){
        x*= gridDens;
        return (x>0.?(int)(x+.5):(int)(x-.5))*(1./gridDens);
    }

    Point displayToUser(POINT p,bool snapOn)
    {
        double mx = 2.*USERX/WW;
        double my = 2.*USERY/HH;

        if(!snapOn)
            return Point(mx*(p.x-WW/2.), my*(HH/2.-p.y));
        else
            return Point(roundd(mx*(p.x-WW/2.)), roundd(my*(HH/2.-p.y)));
    }

    POINT userToDisplay(Point p)
    {
        POINT r;

        double mx = 2.*USERX/WW;
        double my = 2.*USERY/HH;

        r.x = (int)(p.getX() / mx + WW / 2.);
        r.y = (int)(HH / 2. - p.getY() / my);
        return r;
    }

    void LineBres(HDC hdc,POINT p1,POINT p2,COLORREF c)
    {
        int x0=p1.x, y0=p1.y, x1=p2.x, y1=p2.y, x, y, dx,dy,err,yst;
        BOOL str=abs(y1-y0)>abs(x1-x0);
        if(str)
        {
            std::swap(x0,y0);
            std::swap(x1,y1);
        }

        if(x0>x1)
        {
            std::swap(x0,x1);
            std::swap(y0,y1);
        }

        dx=x1-x0;
        dy=abs(y1-y0);
        err=0;
        yst= y0<y1 ? 1:-1;
        y=y0;
        for (x=x0;x<=x1;x++)
            {
            if(str)
                SetPixel (hdc,y,x,c);
            else
                SetPixel (hdc,x,y,c);
            err+=dy;

            if(2*err>=dx){y+=yst;err-=dx;}
        }

    }

    void Ellipse(HDC hdc,POINT cen,int a,int b,COLORREF c)
    {
        int x0 = cen.x, y0 = cen.y;
        int x = 0, y = b > a ? b : a;
        int d = 3-2*y;
        int xt,yt,xq,yq;
        while(x <= y)
        {
            if (b > a)
            {
                xt = x*a/b;
                yt = y*a/b;
                xq = x;
                yq = y;
            }
            else
            {
                xq = x*b/a;
                yq = y*b/a;
                xt =x;
                yt = y;
            }

            SetPixel (hdc,x0+xt,y0+yq,c);SetPixel (hdc,x0-xt,y0+yq,c);
            SetPixel (hdc,x0+xt,y0-yq,c);SetPixel (hdc,x0-xt,y0-yq,c);
            SetPixel (hdc,x0+yt,y0+xq,c);SetPixel (hdc,x0+yt,y0-xq,c);
            SetPixel (hdc,x0-yt,y0+xq,c);SetPixel (hdc,x0-yt,y0-xq,c);

            d=d<0?d+4*x++ +6:d+4*(x++ -y--)+10;
        }
    }

    void Circle(HDC hdc,POINT cen,int rad,COLORREF c)
    {
        int x0 = cen.x, y0 = cen.y;
        int x = 0, y = rad;
        int d = 3-2*rad;

        while(x <= y)
        {
            SetPixel (hdc,x0+x,y0+y,c);SetPixel (hdc,x0-x,y0+y,c);
            SetPixel (hdc,x0+x,y0-y,c);SetPixel (hdc,x0-x,y0-y,c);
            SetPixel (hdc,x0+y,y0+x,c);SetPixel (hdc,x0+y,y0-x,c);
            SetPixel (hdc,x0-y,y0+x,c);SetPixel (hdc,x0-y,y0-x,c);

            d= d<0?d+4*x++ +6:d+4*(x++ -y--)+10;

        }
    }

    void EquilateralTriangle(HDC hdc,Point C,Point mc,COLORREF col)
    {
        Point a = (mc - C);
        double l = (a.mod()* sqrt(3)/2);
        double c = a.mod() * l * sqrt(3)/2;

        double d = sqrt(4*c*c*a.y*a.y - 4 *(c*c - a.x*a.x*l*l)*(a.x * a.x+ a.y*a.y));

        double y1 = (2 * c*a.y + d)/(2*(a.x * a.x + a.y*a.y));
        double y2 = (2 * c*a.y - d)/(2*(a.x * a.x + a.y*a.y));

        double x1 = (c - y1 * a.y)/a.x;
        double x2 = (c - y2 * a.y)/a.x;

        Point k1 (x1,y1);
        Point k2 (x2,y2);

        Point bb(C.x + x2,C.y+y2);
        Point aa(C.x + x1,C.y+y1);


        //LineBres(hdc,userToDisplay(C),userToDisplay(mc),col);
        LineBres(hdc,userToDisplay(aa),userToDisplay(bb),col);
        LineBres(hdc,userToDisplay(aa),userToDisplay(C),col);
        LineBres(hdc,userToDisplay(C),userToDisplay(bb),col);
        //LineBres(hdc,userToDisplay(C),userToDisplay(mc),col);
        //LineBres(hdc,userToDisplay(mc),userToDisplay(bb),col);
        //LineBres(hdc,userToDisplay(mc),userToDisplay(aa),col);
    }

    void rhomb(HDC hdc,Point a,Point b,COLORREF col)
    {
        Point ab = a- b;

        double x = (a.x + b.x)/2;
        double y = (a.y + b.y)/2;

        double mod = ab.mod();

        double D = (ab.x*ab.x)/16;

        double y1 = ab.x/4;
        double y2 = -y1;

        double x1 = (-ab.y*y1)/ab.x;
        double x2 = (-ab.y*y2)/ab.x;

        Point c (x+x1,y+y1);
        Point d (x+x2,y+y2);

        LineBres(hdc,userToDisplay(a),userToDisplay(c),col);
        LineBres(hdc,userToDisplay(b),userToDisplay(c),col);
        LineBres(hdc,userToDisplay(a),userToDisplay(d),col);
        LineBres(hdc,userToDisplay(b),userToDisplay(d),col);
    }

    void Poligon(HDC hdc,POINT cen,int rad,int n,COLORREF col)
    {

        POINT *vertexes = new POINT[n];

        for(int i = 0;i < n;i++)
        {
            vertexes[i] = {
                rad * cos(2*PI*i/n) + cen.x,
                rad * sin(2*PI*i/n) + cen.y
            };
        }

        int i;
        for(i = 0;i < n - 1;i++)
        {
            LineBres(hdc,vertexes[i],vertexes[i+1],col);
        }
        LineBres(hdc,vertexes[0],vertexes[i],col);

        delete []vertexes;
    }

    void Star(HDC hdc,POINT cen,int rad,int p,int q,COLORREF col)
    {
        int* x = new int[p];
        int* y = new int[p];
        bool *pointDone = new bool[p];

        for(int i = 0;i < p;i++)
        {
            x[i] = rad * cos(2*PI*i/p) + cen.x;
            y[i] = rad * sin(2*PI*i/p) + cen.y;
            pointDone[i] = false;
        }

        int current = 0;
        for(int i = 0;i < p;i++)
        {
            int next = (current + q) % p;
            LineBres(hdc,POINT {x[current],y[current]},POINT {x[next],y[next]},col);

            pointDone[current] = true;

            if(pointDone[next]){
                next += 1;
            }
            current = next;
        }

        delete []x;
        delete []y;
        delete []pointDone;
    }

void FillEquilateralTriangle(HDC hdc,Point C,Point mc,COLORREF col)
{
    Point a = (mc - C);
    double l = (a.mod()* sqrt(3)/2);
    double c = a.mod() * l * sqrt(3)/2;

    double d = sqrt(4*c*c*a.y*a.y - 4 *(c*c - a.x*a.x*l*l)*(a.x * a.x+ a.y*a.y));

    double y1 = (2 * c*a.y + d)/(2*(a.x * a.x + a.y*a.y));
    double y2 = (2 * c*a.y - d)/(2*(a.x * a.x + a.y*a.y));

    double x1 = (c - y1 * a.y)/a.x;
    double x2 = (c - y2 * a.y)/a.x;

    Point k1 (x1,y1);
    Point k2 (x2,y2);

    Point bb(C.x + x2,C.y+y2);
    Point aa(C.x + x1,C.y+y1);

    POINT p1 = userToDisplay(C);
    POINT p2 = userToDisplay(aa);
    POINT p3 = userToDisplay(bb);

    TRIVERTEX vertexes[3];

    vertexes[0].x = p1.x;
    vertexes[0].y = p1.y;
    vertexes[0].Red = GetRValue(col);
    vertexes[0].Green = GetGValue(col);
    vertexes[0].Blue = GetBValue(col);
    vertexes[0].Alpha = 0x0000;

    vertexes[1].x = p2.x;
    vertexes[1].y = p2.y;
    vertexes[1].Red = GetRValue(col);
    vertexes[1].Green = GetGValue(col);
    vertexes[1].Blue = GetBValue(col);
    vertexes[1].Alpha = 0x0000;

    vertexes[2].x = p3.x;
    vertexes[2].y = p3.y;
    vertexes[2].Red = GetRValue(col);
    vertexes[2].Green = GetGValue(col);
    vertexes[2].Blue = GetBValue(col);
    vertexes[2].Alpha = 0x0000;

    GRADIENT_TRIANGLE triangle;
    triangle.Vertex1 = 0;
    triangle.Vertex2 = 1;
    triangle.Vertex3 = 2;

   // GradientFill(hdc,vertexes,3,&triangle,1,GRADIENT_FILL_TRIANGLE);
}

void hexagon(HDC hdc,POINT a,POINT b,int n,COLORREF col)
{
    if(n <= 0)
    {
        LineBres(hdc,a,b,col);
        return;
    }
    else
    {
        POINT aa =
        {
            (a.x + 1./2.*b.x)/(1+1./2.),
            (a.y + 1./2.*b.y)/(1+1./2.)
        };
        POINT bb =
        {
            (a.x + 2.*b.x)/(1+2.),
            (a.y + 2.*b.y)/(1+2.)
        };

        int rad = sqrt(pow((aa.x - a.x),2)+pow((aa.y - a.y),2));

        POINT hexagon1[5];
        POINT hexagon2[5];

        for(int i = 0;i < 5;i++)
        {
            hexagon1[i] =
            {
                rad*cos(2*PI*i/5) + aa.x,
                rad*sin(2*PI*i/5) + aa.y,
            };
             hexagon2[i] =
            {
                rad*cos(2*PI*i/5) + bb.x,
                rad*sin(2*PI*i/5) + bb.y,
            };
        }

        for(int i = 0;i < 4;i++)
        {
            hexagon(hdc,hexagon1[i],hexagon1[i+1],n-1,col);
            hexagon(hdc,hexagon2[i],hexagon2[i+1],n-1,col);
        }
        hexagon(hdc,hexagon1[0],hexagon1[4],n-1,col);
        hexagon(hdc,hexagon2[0],hexagon2[4],n-1,col);

        //hexagon(hdc,a,aa,n-1,col);
        // hexagon(hdc,aa,bb,n-1,col);
        //hexagon(hdc,bb,b,n-1,col);
    }
}

void hexagon_2(HDC hdc,POINT a,POINT b,int n,COLORREF col)
{

    if(n == 0)
    {
        LineBres(hdc,a,b,col);
        return;
    }
    POINT c = {(a.x + b.x)/2,(a.y + b.y)/2};
    POINT ac = {(a.x+c.x)/2,(a.y + c.y)/2};
    POINT bc = {(b.x+c.x)/2,(b.y + c.y)/2};

    POINT v1 = {b.x - bc.x,b.y - bc.y};
    POINT v2 = {ac.x - a.x,ac.y - a.y};

    POINT cen1 = {b.x + v2.x,b.y+v2.y};
    POINT cen2 = {a.x - v1.x,a.y-v1.y};

    int rad = sqrt(pow((ac.x - c.x),2)+pow((ac.y - c.y),2));

    POINT hexagon1[6];
    POINT hexagon2[6];

    for(int i = 0;i < 6;i++)
    {
        hexagon1[i] =
        {
            rad*cos(2*PI*i/6) + cen1.x,
            rad*sin(2*PI*i/6) + cen1.y,
        };
         hexagon2[i] =
        {
            rad*cos(2*PI*i/6) + cen2.x,
            rad*sin(2*PI*i/6) + cen2.y,
        };
    }

    for(int i = 0;i < 5;i++)
    {
        hexagon_2(hdc,hexagon1[i],hexagon1[i+1],n-1,col);
        hexagon_2(hdc,hexagon2[i],hexagon2[i+1],n-1,col);
    }
    hexagon_2(hdc,hexagon1[0],hexagon1[5],n-1,col);
    hexagon_2(hdc,hexagon2[0],hexagon2[5],n-1,col);

    hexagon_2(hdc,bc,b,n-1,col);
    hexagon_2(hdc,ac,a,n-1,col);
    hexagon_2(hdc,bc,c,n-1,col);
    hexagon_2(hdc,ac,c,n-1,col);
}

void test(HDC hdc,POINT a,POINT b,COLORREF col)
{
    POINT v1 = {b.x - a.x,b.y - a.y};

    double ar = 90*PI / 180.;
    POINT v2 =
    {
        v1.x * cos(ar) + v1.y*sin(ar),
        -v1.x * sin(ar) + v1.y*cos(ar)
    };

    LineBres(hdc,a,b,col);
    LineBres(hdc,b,POINT {b.x + v2.x,b.y + v2.y});
}

}
