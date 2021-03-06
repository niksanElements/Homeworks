
#include <windows.h>
#include "draw.h"

using namespace globals;
GLuint txtNum = 7;
const char* filenameArray[] = {
		"NBU.bmp",
		"brick.bmp",
		"wood.bmp",
		"stone.bmp",
		"floor.bmp",
		"ceiling.bmp",
		"stripes.bmp"
};

BOOL CreateGLContexts(HWND hWnd, HDC& hDC, HGLRC& hRC){
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

void ReleaseGLContexts(HWND hWnd, HDC hDC, HGLRC hRC){
    ChangeDisplaySettings(NULL, 0);
    wglMakeCurrent(hDC, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
}

void keyPressed(WPARAM wParam){
    switch (wParam){
        case VK_ESCAPE:
            SendMessage(hWnd, WM_CLOSE, 0, 0);
        break;
        case VK_LEFT: roty-=0.5;  break;
        case VK_RIGHT:roty+=0.5;  break;
        case VK_DOWN: rotx-=0.5;  break;
        case VK_UP  : rotx+=0.5;  break;
        case VK_HOME: rotz+=0.5;  break;
        case VK_END : rotz-=0.5;  break;
        case VK_RETURN: level+=5; break;
        case VK_SPACE:if(level>10)level-=5; break;

      }
}
void charPressed(WPARAM wParam){
    switch(wParam){
        case 'A': anim=false;        break;
        case 'a': anim=true;rotx=0, roty=0, rotz=0;
            break;
        case 'r': incCol(model,0);   break;
        case 'g': incCol(model,1);   break;
        case 'b': incCol(model,2);   break;
        case 'R': decCol(model,0);   break;
        case 'G': decCol(model,1);   break;
        case 'B': decCol(model,2);   break;
        case 'w': togglewire();		 break;
        case 'm': model=(model+1)%models;
                                     break;
        case 'h': help();			 break;
        case 'L': lightDist++;		 break;
        case 'l': lightDist--;		 break;
	    case 't': tglTexture();		 break;
	    case 'T': setTexture();		 break;
        case 'Z': zoom++;			 break;
        case 'z': zoom--;			 break;
        case 's': glShadeModel(GL_SMOOTH); break;
        case 'S': glShadeModel(GL_FLAT); break;
    }
}
void mouseAct(UINT msg, LPARAM lParam){
    using globals::mot; using globals::PAN; using globals::ROT;
    static bool ld=false, rd=false;
    if(msg==WM_LBUTTONDOWN){ld=true;return;}
    if(msg==WM_RBUTTONDOWN){rd=true;return;}
    int x = LOWORD (lParam), y = HIWORD (lParam);
    switch(msg){
        case WM_MOUSEMOVE:
            if(ld){mot = PAN;}
            if(rd){mot = ROT;}
            motion(x,y );
        break;
        case WM_LBUTTONUP: ld=false; mot=0;
        break;
        case WM_RBUTTONUP: rd=false; mot=0;
        break;
     }
 }

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ){
    switch (msg){
        case WM_CREATE:
            if (CreateGLContexts(hWnd, hDC, hRC)){
                GetClientRect(hWnd, &ClientRect);
                initTextures( filenameArray );
                InitGL(ClientRect.right, ClientRect.bottom);
            }
            else PostQuitMessage(0);
        break;

        case WM_KEYDOWN: keyPressed(wParam);
        break;

        case WM_CHAR:
            charPressed(wParam);genmodel();
        break;

        case WM_LBUTTONDOWN: case WM_LBUTTONUP: case WM_MOUSEMOVE:
        case WM_RBUTTONDOWN: case WM_RBUTTONUP: mouseAct(msg, lParam);
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

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow){

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

    hWnd = CreateWindowEx(0, ClassName, "Win32 & OpenGL textured models demo",
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
