#ifndef ENGINE3D_HPP
#define ENGINE3D_HPP

#include <windows.h>
#include <GL/gl.h>
#include <iostream>

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

namespace e3d {

struct Vector3 { float x, y, z; };
struct Color { float r, g, b, a; };
const Color RED = {1.0f, 0.0f, 0.0f, 1.0f};

class Engine {
public:
    HWND hwnd;
    HDC hdc;
    HGLRC hrc;
    bool running;

    Engine() : hwnd(NULL), hdc(NULL), hrc(NULL), running(true) {}

    // CRIA A JANELA E O CONTEXTO OPENGL AUTOMATICAMENTE
    void CreateWindow(const char* title, int width, int height) {
        WNDCLASS wc = {0};
        wc.lpfnWndProc = DefWindowProc; 
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = "Engine3DClass";
        wc.style = CS_OWNDC;
        RegisterClass(&wc);

        hwnd = ::CreateWindowEx(0, wc.lpszClassName, title, 
            WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
            CW_USEDEFAULT, CW_USEDEFAULT, width, height, 
            NULL, NULL, wc.hInstance, NULL);

        hdc = GetDC(hwnd);

        PIXELFORMATDESCRIPTOR pfd = {sizeof(pfd), 1};
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cDepthBits = 24;

        int format = ChoosePixelFormat(hdc, &pfd);
        SetPixelFormat(hdc, format, &pfd);
        hrc = wglCreateContext(hdc);
        wglMakeCurrent(hdc, hrc);

        glEnable(GL_DEPTH_TEST);
    }

    bool IsRunning() {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) running = false;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return running;
    }

    void BeginDrawing() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
    }

    void DrawCube(Vector3 pos, float s, Color col) {
        glPushMatrix();
        glTranslatef(pos.x, pos.y, pos.z);
        glColor4f(col.r, col.g, col.b, col.a);
        glBegin(GL_QUADS);
            glVertex3f(-s,-s, s); glVertex3f( s,-s, s); glVertex3f( s, s, s); glVertex3f(-s, s, s);
            glVertex3f(-s,-s,-s); glVertex3f(-s, s,-s); glVertex3f( s, s,-s); glVertex3f( s,-s,-s);
            // ... outras faces
        glEnd();
        glPopMatrix();
    }

    void EndDrawing() {
        SwapBuffers(hdc);
    }
};
}
#endif
