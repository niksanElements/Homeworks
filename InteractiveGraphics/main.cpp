#include <cstdio>
#include <cstring>
#include "grserv.h"

// Function for Message Handle fro Win32 app
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow){
	static char szAppName[] = TEXT("CITB601-6:");
	HWND         hwnd;
	MSG          msg;
	WNDCLASS     wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(180, 200, 200));
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("Can not register the window class!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT(" CITB601-6: Maintaining shapes as polymorphic objects"),
		WS_OVERLAPPEDWINDOW, 200, 0, WW, HH,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){

	if (message >= WM_MOUSEFIRST  && message <= WM_MBUTTONDBLCLK)
		return getMouseEvent(hwnd, message, wParam, lParam);
	if (message >= WM_KEYFIRST && message <= WM_KEYLAST)
		return getKbdEvent(hwnd, message, wParam, lParam);
	switch (message){
	case WM_CREATE:
		// RedirectIOToConsole();
		showMess(hwnd, "For help press 'h' and see the console window.");
		rescale();
		return 0;
	case WM_SIZE:  // resizing the Windows
		WW = LOWORD(lParam);
		HH = HIWORD(lParam);
		rescale();
		return 0;
	case WM_PAINT:
		redrawAll(hwnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
