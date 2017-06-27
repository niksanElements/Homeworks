#include "Vector2D.h"
#include <cmath>
#include <stdio.h>

#define  MAX_OBJECTS 1000

typedef struct {
	char tYpe; void *obj;
}Drawable;

Drawable pt[MAX_OBJECTS];
UINT iCount = 0;
char objType = 'p';
char charBuf[60];
POINT pntBuf[100];
int pntGot;
int pntsToTake = 1;

int USERX = 12, USERY = 10, WW = 1000, HH = 600;

Point dispToUser(POINT p) 
{
	return Point((2.*p.x / WW - 1)*USERX, (1. - 2.*p.y / HH)*USERY);
}

//????????????? ?? ?????????????  ? ????????? ??????????
POINT userToDisp(Point p) 
{
	POINT r; r.x = (int)((p.getX() / USERX + 1)*WW / 2);
	r.y = (int)((1 - p.getY() / USERY)*HH / 2);
	return r;
}

void regObject() {
	Point p;
	switch (objType) {
	case 'p':
		pt[iCount].tYpe = 'p';
		pt[iCount].obj = new Point(dispToUser(pntBuf[0]));
		break;
	case 'L':
		pt[iCount].tYpe = 'L';
		pt[iCount].obj = new Line(
			dispToUser(pntBuf[0]),
			dispToUser(pntBuf[1])
			);
		break;
	case 'P':
		pt[iCount].tYpe = 'P';
		pt[iCount].obj = new PolyOpen(pntBuf, pntGot);

		break;
	}
	iCount++;
}

void drawPoint(HWND hwnd, const Point& pp)
{
	static const int PointRadius = 3;
	POINT p = userToDisp(pp);
	HDC hdc = GetDC(hwnd);
	Ellipse(hdc, p.x - PointRadius, p.y - PointRadius, p.x + PointRadius, p.y + PointRadius);
	ReleaseDC(hwnd,hdc);
}

void drawLine(HWND hwnd, POINT a, POINT b) {
	HDC hdc = GetDC(hwnd);
	MoveToEx(hdc, a.x, a.y, NULL);
	LineTo(hdc, b.x, b.y);
	ReleaseDC(hwnd, hdc);
}

void drawLine(HWND hwnd, const Line & L) {
	POINT p1 = userToDisp(L.getA()),
		p2 = userToDisp(L.getB());
	drawLine(hwnd, p1, p2);
}

void drawPoly(HWND hwnd, const PolyOpen & L) {
	for (int i = 1; i < L.getSz(); i++)
		drawLine(hwnd, Line(L.getP()[i], L.getP()[i - 1]));
}

//???????????? ?? ??????????? ??? ? ????????????? ???????
void drawAxes(HWND hwnd) {
	drawLine(hwnd, Line(Point(-USERX + 1, 0), Point(USERX - 1, 0)));
	drawLine(hwnd, Line(Point(0, -USERY + 1), Point(0, USERY - 1)));
	for (double x = -USERX + 1; x < USERX; x += 1)
		drawLine(hwnd, Line(Point(x, 0), Point(x, 0.15)));
	for (double y = -USERY + 1; y < USERY - 1; y += 1)
		drawLine(hwnd, Line(Point(0, y), Point(-0.15, y)));
}


void mouseEcho(HWND hwnd, LPARAM lParam)
{
	static const int place = DT_SINGLELINE | DT_BOTTOM | DT_LEFT;
	char mouf[30] = "", spac[] = "                             ";
	RECT rect; HDC hdc; POINT pd; Point pu;
	pu = dispToUser(pd);
	snprintf(mouf, 30, "%6.2f   %6.2f", pu.getX(), pu.getY());
	hdc = GetDC(hwnd);
	GetClientRect(hwnd, &rect);
	DrawText(hdc, (LPCWSTR)spac, -1, &rect, place);
	DrawText(hdc, (LPCWSTR)mouf, -1, &rect, place);
	ReleaseDC(hwnd, hdc);
}

void drawMarker(HWND hwnd, POINT p) 
{
	HDC hdc = GetDC(hwnd);
	Rectangle(hdc, p.x - 2, p.y - 2, p.x + 3, p.y + 3);
	ReleaseDC(hwnd, hdc);
}


void showMsg(HWND hwnd, const char* msg)
{
	char spac[] = "                             ";
	RECT rect; HDC hdc;
	UINT mode = DT_CENTER | DT_BOTTOM | DT_SINGLELINE;
	hdc = GetDC(hwnd);
	GetClientRect(hwnd,&rect);
	DrawText(hdc, (LPCWSTR)spac, 1, &rect, mode);
	DrawText(hdc, (LPCWSTR)msg, 1, &rect, mode);
	ReleaseDC(hwnd, hdc);
	memcpy(charBuf, msg, 60);
}

LRESULT getMouseMoveEvent(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT pp;
	switch (message)
	{
	case WM_LBUTTONUP:
		pp.x = LOWORD(lParam); pp.y = HIWORD(lParam);
		pntBuf[pntGot++] = pp; drawMarker(hwnd, pp);
		break;
	case WM_MOUSEMOVE:
		mouseEcho(hwnd, lParam);
		break;
	case WM_RBUTTONDOWN:
		if (pntGot == pntsToTake || pntsToTake == -1)regObject();
		pntGot = 0;
		break;
	case WM_RBUTTONUP:
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}

LRESULT getKbdEvetn(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_KEYDOWN || message == WM_CHAR)
	{
		switch (wParam)
		{
		case VK_F1:
			objType = 'p'; pntsToTake = 1;
			showMsg(hwnd, "INPUT POINTS");
			break;
		case VK_F2:
			objType = 'L'; pntsToTake = 2;
			showMsg(hwnd, "INPUT LINES");
			break;
		case VK_F3:
			objType = 'P'; pntsToTake = -1;
			showMsg(hwnd, "INPUT POLYGON");
			break;
		case 27: exit(0);
		}
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void redrawAll(HWND hwnd)
{
	PAINTSTRUCT ps; HDC hdc; UINT i;
	hdc = BeginPaint(hwnd, &ps);	EndPaint(hwnd, &ps);
	for (i = 1; i < iCount; i++) {
		switch (pt[i].tYpe) {
		case 'p': drawPoint(hwnd, *(Point*)(pt[i].obj)); break;
		case 'L': drawLine(hwnd, *(Line*)(pt[i].obj)); break;
		case 'P': drawPoly(hwnd, *(PolyOpen*)(pt[i].obj)); break;
		}
	}
	drawAxes(hwnd);
	showMsg(hwnd, charBuf);
}