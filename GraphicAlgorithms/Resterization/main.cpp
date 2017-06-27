//???? cliprect.h
#include <windows.h>
#include <stdio.h>
#include <math.h>

#define IDM_SYS_CLIP   1
#define IDM_SYS_LINE   2

void showCoord(HWND hwnd, LPARAM lParam) {
	TCHAR mouf[20], spac[20] = L"                   ";
	RECT rect; HDC hdc;
	wsprintf(mouf, L"%i   %i", LOWORD(lParam), HIWORD(lParam));
	hdc = GetDC(hwnd);
	GetClientRect(hwnd, &rect);
	DrawText(hdc, spac, -1, &rect,
		DT_SINGLELINE | DT_BOTTOM | DT_LEFT);
	DrawText(hdc, mouf, -1, &rect,
		DT_SINGLELINE | DT_BOTTOM | DT_LEFT);
	ReleaseDC(hwnd, hdc);
}


inline void swap(int &p, int &q) { int t = p; p = q; q = t; }

void lineBres(HDC hdc, POINT p1, POINT p2, COLORREF c) {
	int x0 = p1.x, y0 = p1.y, x1 = p2.x, y1 = p2.y;
	bool str = abs(y1 - y0) > abs(x1 - x0);
	if (str) { swap(x0, y0); swap(x1, y1); }
	if (x0 > x1) { swap(x0, x1); swap(y0, y1); }
	int dx = x1 - x0, dy = abs(y1 - y0), err = 0, y = y0;
	int yst = y0 < y1 ? 1 : -1;
	for (int x = x0; x <= x1; x++) {
		if (str) SetPixel(hdc, y, x, c);
		else    SetPixel(hdc, x, y, c);
		err += dy;
		if (2 * err >= dx) { y += yst; err -= dx; }
	}
}

class ClippingRectangle {
	double xmin, ymin, xmax, ymax;

	BYTE outcode(double x, double y) {
		BYTE code = 0;
		if (y > ymax)code += 8;
		else if (y < ymin)code += 4;
		if (x > xmax)code += 2;
		else if (x < xmin)code += 1;
		return code;
	}

	int CSClip(double &x1, double &y1, double &x2, double &y2) {
		BYTE code1 = outcode(x1, y1), code2 = outcode(x2, y2), code;
		double x, y;
		do {
			if (code1&code2)return 1;    //?????? ???
			if (code1 + code2 == 0)return 0; //?????? ?????
			code = code1 != 0 ? code1 : code2;
			if (code & 8) { x = x1 + (x2 - x1)*(ymax - y1) / (y2 - y1); y = ymax; }
			else if (code & 4) { x = x1 + (x2 - x1)*(ymin - y1) / (y2 - y1); y = ymin; }
			else if (code & 2) { y = y1 + (y2 - y1)*(xmax - x1) / (x2 - x1); x = xmax; }
			else if (code & 1) { y = y1 + (y2 - y1)*(xmin - x1) / (x2 - x1); x = xmin; }
			if (code == code1) { x1 = x; y1 = y; code1 = outcode(x1, y1); }
			else { x2 = x; y2 = y; code2 = outcode(x2, y2); }
		} while (true);
	}

public:
	ClippingRectangle(POINT p1, POINT p2) {
		double x1 = p1.x, y1 = p1.y, x2 = p2.x, y2 = p2.y;
		if (x1 < x2) { xmin = x1; xmax = x2; }
		else { xmin = x2; xmax = x1; }
		if (y1 < y2) { ymin = y1; ymax = y2; }
		else { ymin = y2; ymax = y1; }
	}

	void drawClipped(HWND hwnd, POINT P1, POINT P2) {
		HDC hdc; double x1, y1, x2, y2;
		x1 = P1.x; y1 = P1.y; x2 = P2.x; y2 = P2.y;
		int code = CSClip(x1, y1, x2, y2);
		hdc = GetDC(hwnd);
		if (code == 1)
			lineBres(hdc, P1, P2, RGB(0, 0, 250));
		else {
			POINT P11, P22;
			P11.x = (int)x1; P11.y = (int)y1;
			P22.x = (int)x2; P22.y = (int)y2;
			lineBres(hdc, P1, P11, RGB(0, 0, 250));
			lineBres(hdc, P11, P22, RGB(250, 0, 0));
			if (P2.x != P22.x || P2.y != P22.y)
				lineBres(hdc, P2, P22, RGB(0, 0, 250));
		}
		ReleaseDC(hwnd, hdc);
	}

	void redraw(HWND hwnd) {
		HDC hdc = GetDC(hwnd);
		MoveToEx(hdc, (int)xmin, (int)ymin, NULL);
		LineTo(hdc, (int)xmin, (int)ymax);
		LineTo(hdc, (int)xmax, (int)ymax);
		LineTo(hdc, (int)xmax, (int)ymin);
		LineTo(hdc, (int)xmin, (int)ymin);
		ReleaseDC(hwnd, hdc);
	}
};//???? ?? ???? cliprect.h

  //??????????????? ????????? ????? ?? ?????????? ?? Cohen-Sutherland
  //???? CSCB506 ??? ???????? ??????????? ?? ???
  //?????: ??. ??????, 2015


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = L"LinesDemo";
	HWND         hwnd;
	HMENU        hMenu;
	MSG          msg;
	WNDCLASS     wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("Can not register the window class!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		L" CITB601-3: Clipping rectangle. NBU 2016 Ivanov",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);
	hMenu = GetSystemMenu(hwnd, FALSE);
	//???????? ?? ??????? ? ?????????? ????
	AppendMenu(hMenu, MF_SEPARATOR, 0, NULL);
	AppendMenu(hMenu, MF_STRING, IDM_SYS_CLIP, TEXT("????????"));
	AppendMenu(hMenu, MF_STRING, IDM_SYS_LINE, TEXT("?????????"));

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
	static bool LBD = true; //?????? ?? ???????? ??? ????? ?? ???????
	static POINT P1, P2;   //?????? ????? ?? ????????? ? int ??????????
	static int ip = 0;      //?????? ?? ?????-????? ???????? ?????
	static int mode = 1;
	static ClippingRectangle * CR = NULL;
	switch (message)
	{
	case WM_SYSCOMMAND: //???????????? ?? ????????? ?? ?????????? ????
		switch (LOWORD(wParam)) {
		case IDM_SYS_CLIP:
			mode = 1;
			return 0;
		case IDM_SYS_LINE:
			mode = 2;
			return 0;
		}
		break;
	case WM_LBUTTONDOWN:
		LBD = true;
		return 0;

	case WM_MOUSEMOVE:
		showCoord(hwnd, lParam);
		return 0;

	case WM_LBUTTONUP:
		if (LBD) {
			LBD = !LBD;
			if (ip == 0) {//????????? ?? ????? ????? 
				P1.x = LOWORD(lParam);
				P1.y = HIWORD(lParam);
				ip++;
			}
			else {//????????? ?? ????? ????? 
				P2.x = LOWORD(lParam);
				P2.y = HIWORD(lParam);
				ip--;
				if (mode == 1) {
					if (CR != NULL) delete CR;
					CR = new ClippingRectangle(P1, P2);
					InvalidateRect(hwnd, NULL, TRUE);
				}
				else CR->drawClipped(hwnd, P1, P2);
			}
		}
		return 0;
	case WM_RBUTTONDOWN:
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_PAINT://????????? ?? ???? ???????
		if (CR != NULL)CR->redraw(hwnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

