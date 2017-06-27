#include <windows.h>
#include "draw.h"
#include "textures.h"

using namespace draw;
using namespace textures;


BOOL CreateGLContexts(HWND hWnd, HDC& hDC, HGLRC& hRC)
{
    static PIXELFORMATDESCRIPTOR pfd;
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 16;
    pfd.cRedBits = 0;
    pfd.cRedShift = 0;
    pfd.cGreenBits = 0;
    pfd.cGreenShift = 0;
    pfd.cBlueBits = 0;
    pfd.cBlueShift = 0;
    pfd.cAlphaBits = 0;
    pfd.cAlphaShift = 0;
    pfd.cAccumBits = 0;
    pfd.cAccumRedBits = 0;
    pfd.cAccumGreenBits = 0;
    pfd.cAccumBlueBits = 0;
    pfd.cAccumAlphaBits = 0;
    pfd.cDepthBits = 16;
    pfd.cStencilBits = 0;
    pfd.cAuxBuffers = 0;
    pfd.iLayerType = PFD_MAIN_PLANE;
    pfd.bReserved = 0;
    pfd.dwLayerMask = 0;
    pfd.dwVisibleMask = 0;
    pfd.dwDamageMask = 0;

    hDC = GetDC(hWnd);

    int	PixelFormat;
    PixelFormat = ChoosePixelFormat(hDC, &pfd);

    if (!PixelFormat)
    {
        MessageBox(0, "Can't Find A Suitable PixelFormat.", "Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    if(!SetPixelFormat(hDC, PixelFormat, &pfd))
    {
        MessageBox(0, "Can't Set The PixelFormat.", "Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    hRC = wglCreateContext(hDC);

    if(!hRC)
    {
        MessageBox(0, "Can't Create A GL Rendering Context.", "Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    if(!wglMakeCurrent(hDC, hRC))
    {
        MessageBox(0, "Can't activate GLRC.", "Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    return TRUE;
}

void ReleaseGLContexts(HWND hWnd, HDC hDC, HGLRC hRC)
{
    ChangeDisplaySettings(NULL, 0);
    wglMakeCurrent(hDC, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ){
    switch (msg){
        case WM_CREATE:
            if (CreateGLContexts(hWnd, hDC, hRC)){
                GetClientRect(hWnd, &ClientRect);
                const char *file [] = {"brick.bmp"};
                initTextures(file,1);
                InitGL(ClientRect.right, ClientRect.bottom);
            }
            else PostQuitMessage(0);
        break;

        case WM_KEYDOWN:
            switch (wParam){
                case VK_ESCAPE:
                case VK_RETURN:
                case VK_SPACE:
                    SendMessage(hWnd, WM_CLOSE, 0, 0);
                break;
                case VK_LEFT: model= 5;   break;
                case VK_RIGHT:togglewire();        break;
            }
            genmodel(); anim=true;
        break;
        case WM_CHAR:
            switch(wParam){
                case 'A': anim=false;        break;
                case 'a': anim=true;         break;
                case 'w': togglewire();		 break;
                case 'h': help();			 break;
                case 'L': lightDist++;		 break;
                case 'l': lightDist--;		 break;
                case 'Z': zoom++;			 break;
                case 'z': zoom--;			 break;
                case '\033': exit(EXIT_SUCCESS); break;
            }
            genmodel();
        break;


        case WM_SIZE:
            GetClientRect(hWnd, &ClientRect);
            ResizeGLScene(ClientRect.right, ClientRect.bottom);
        break;

        case WM_CLOSE:
            ReleaseGLContexts(hWnd, hDC, hRC);
            DestroyWindow(hWnd);
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
        break;

        default:
            return (DefWindowProc(hWnd, msg, wParam, lParam));
    }
    return (0);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{

    WNDCLASSEX    wc;

    wc.cbSize           = sizeof(WNDCLASSEX);
    wc.style            = 0;
    wc.lpfnWndProc      = (WNDPROC)WndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIcon(NULL, IDI_APPLICATION) ;
    wc.hIconSm          = LoadIcon(NULL, IDI_APPLICATION) ;
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH)(COLOR_WINDOW);
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = ClassName;

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Failed To Register The Window Class.", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    GetWindowRect(GetDesktopWindow(), &ScreenRect);

    hWnd = CreateWindowEx(0, ClassName, "Win32 & OpenGL demo without GLUT",
    WS_OVERLAPPEDWINDOW, (ScreenRect.right - 500) / 2 , (ScreenRect.bottom - 500) / 2,
    500, 500, NULL, NULL, hInstance, NULL);

    if (!hWnd){
        MessageBox(NULL, "Window Creation Failed.", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    MSG msg;

    while (1){
        while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)){
            if (GetMessage(&msg, NULL, 0, 0)){
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else return msg.wParam;
        }
        DrawGLScene(anim);
        glFinish();
        SwapBuffers(hDC);
    }
}
