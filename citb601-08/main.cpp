#include <windows.h>
#include "draw.h"
#include "menu.h"

using namespace globals;

LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
bool EnableOpenGL( HWND hwnd, HDC*, HGLRC* );
void DisableOpenGL( HWND, HDC, HGLRC );

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow ) {

    WNDCLASSEX    wc;

    wc.cbSize           = sizeof( WNDCLASSEX );
    wc.style            = 0;
    wc.lpfnWndProc      = ( WNDPROC )WndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIcon( NULL, IDI_APPLICATION ) ;
    wc.hIconSm          = LoadIcon( NULL, IDI_APPLICATION ) ;
    wc.hCursor          = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground    = ( HBRUSH )( COLOR_WINDOW );
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = ClassName;

    if ( !RegisterClassEx( &wc ) ) {
        MessageBox( NULL, "Failed To Register The Window Class.", "Error", MB_OK | MB_ICONERROR );
        return 0;
    }

    GetWindowRect( GetDesktopWindow(), &ScreenRect );

    hWnd = CreateWindowEx( 0, ClassName, "GLUT free Win32 & OpenGL demo",
                           WS_OVERLAPPEDWINDOW, ( ScreenRect.right - 500 ) / 2 , ( ScreenRect.bottom - 500 ) / 2,
                           500, 500, NULL, NULL, hInstance, NULL );

    if ( !hWnd ) {
        MessageBox( NULL, "Window Creation Failed.", "Error", MB_OK | MB_ICONERROR );
        return 0;
    }
    HMENU hmenu = mkMenu();
    SetMenu( hWnd, hmenu );
    ShowWindow( hWnd, SW_SHOW );
    UpdateWindow( hWnd );

    MSG msg;

    while ( 1 ) {
        while ( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) ) {
            if ( GetMessage( &msg, NULL, 0, 0 ) ) {
                TranslateMessage( &msg );
                DispatchMessage( &msg );
            } else return msg.wParam;
        }
        DrawGLScene( anim );
        glFinish();
        SwapBuffers( hDC );
    }
}

LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
    switch ( msg ) {
        case WM_CREATE:
            if ( EnableOpenGL( hWnd, &hDC, &hRC ) ) {
                GetClientRect( hWnd, &ClientRect );
                InitGL( ClientRect.right, ClientRect.bottom );
            } else PostQuitMessage( 0 );
            help();
            break;
        case WM_COMMAND:
            return getMenuEvent( hWnd, msg, wParam, lParam );
        case WM_KEYDOWN:
            keyPressed( wParam );
            break;

        case WM_CHAR:
            charPressed( wParam );
            genmodel();
            break;

        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_MOUSEMOVE:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
            mouseAct( msg, lParam );
            break;

        case WM_SIZE:
            GetClientRect( hWnd, &ClientRect );
            SetGLView( ClientRect.right, ClientRect.bottom );
            break;

        case WM_CLOSE:
            DisableOpenGL ( hWnd, hDC, hRC );
            DestroyWindow( hWnd );
            break;

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return ( DefWindowProc( hWnd, msg, wParam, lParam ) );
    }
    return ( 0 );
}

bool EnableOpenGL( HWND hwnd, HDC* hDC, HGLRC* hRC ) {
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;
    *hDC = GetDC( hwnd );
    ZeroMemory( &pfd, sizeof( pfd ) );

    pfd.nSize = sizeof( pfd );
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat( *hDC, &pfd );

    SetPixelFormat( *hDC, iFormat, &pfd );

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );

    wglMakeCurrent( *hDC, *hRC );
    return true;
}

void DisableOpenGL ( HWND hwnd, HDC hDC, HGLRC hRC ) {
    wglMakeCurrent( NULL, NULL );
    wglDeleteContext( hRC );
    ReleaseDC( hwnd, hDC );
}

