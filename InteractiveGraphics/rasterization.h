
#include "vector2D.h"

void swap(int *p,int *q){int t=*p;*p=*q;*q=t;}

/**
    Interactive algorithm for rasterization on Line.
    Bresenham's line algorithm.
 */
void lineBres(HDC hdc,POINT p1,POINT p2, COLORREF c){
	int x0=p1.x, y0=p1.y, x1=p2.x, y1=p2.y, x, y, dx,dy,err,yst;
	BOOL str=abs(y1-y0)>abs(x1-x0);
	//If the angle is big then x and y let to be coordinated.
	if(str)  {swap(&x0,&y0);swap(&x1,&y1);}
	//The fist point must be on the left compare to the second one.
	if(x0>x1){swap(&x0,&x1);swap(&y0,&y1);}
	dx=x1-x0, dy=abs(y1-y0), err=0;
	yst= y0<y1 ? 1:-1; y=y0;
	for (x=x0;x<=x1;x++){
		if(str) SetPixel (hdc,y,x,c);
		else    SetPixel (hdc,x,y,c);
		err+=dy;
		if(2*err>=dx){y+=yst;err-=dx;}
	}
}

/**
    Michner's algorithm.
*/
void circle(HDC hdc,POINT cen,int R,COLORREF c){
	int x0=cen.x,y0=cen.y,x=0,y=R,d=3-2*R;//It begins form top point
	while(x<=y){//Calculate the pixes for the top 8'ts for the circle.
		// For the rest are used symmetry.
		SetPixel (hdc,x0+x,y0+y,c);SetPixel (hdc,x0-x,y0+y,c);
		SetPixel (hdc,x0+x,y0-y,c);SetPixel (hdc,x0-x,y0-y,c);
		SetPixel (hdc,x0+y,y0+x,c);SetPixel (hdc,x0+y,y0-x,c);
		SetPixel (hdc,x0-y,y0+x,c);SetPixel (hdc,x0-y,y0-x,c);
		d=d<0?d+4*x++ +6:d+4*(x++ -y--)+10;
	}
}

void ellipse(HDC hdc,POINT cen,int a,int b,COLORREF c){
	int x0=cen.x,y0=cen.y,x=0,y=b>a?b:a,d=3-2*y;
	int xt,yt,xq,yq;
	while(x<=y){
		if(b>a){xt=x*a/b; yt=y*a/b;	xq=x; yq=y;}
		else   {xq=x*b/a; yq=y*b/a; xt=x ;yt=y;}
		SetPixel (hdc,x0+xt,y0+yq,c);SetPixel (hdc,x0-xt,y0+yq,c);
		SetPixel (hdc,x0+xt,y0-yq,c);SetPixel (hdc,x0-xt,y0-yq,c);
		SetPixel (hdc,x0+yt,y0+xq,c);SetPixel (hdc,x0+yt,y0-xq,c);
		SetPixel (hdc,x0-yt,y0+xq,c);SetPixel (hdc,x0-yt,y0-xq,c);
		d=d<0?d+4*x++ +6:d+4*(x++ -y--)+10;
	}
}
