#ifndef ERROR156GUI_H
#define ERROR156GUI_H

#include <windows.h>

// --- STRUCTURES ---
typedef struct {
    HWND hwnd;
    HINSTANCE hInstance;
} e156_Window;

// --- API PROTOTYPES ---
e156_Window e156_Init(const char* title, int w, int h);
void e156_Button(e156_Window* win, const char* text, int x, int y, int w, int h, int id);
void e156_Label(e156_Window* win, const char* text, int x, int y, int w, int h);
void e156_Input(e156_Window* win, int x, int y, int w, int h, int id);
void e156_Checkbox(e156_Window* win, const char* text, int x, int y, int w, int h, int id);
int e156_Loop();
void e156_MessageBox(const char* title, const char* msg);

#ifdef ERROR156_IMPLEMENTATION

// Internal Procedure
LRESULT CALLBACK e156_Proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_DESTROY) { PostQuitMessage(0); return 0; }
    return DefWindowProc(hwnd, msg, wp, lp);
}

e156_Window e156_Init(const char* title, int w, int h) {
    e156_Window win;
    win.hInstance = GetModuleHandle(NULL);
    WNDCLASS wc = {0};
    wc.lpfnWndProc = e156_Proc;
    wc.hInstance = win.hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
    wc.lpszClassName = "e156_class";
    RegisterClass(&wc);

    win.hwnd = CreateWindow("e156_class", title, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                            CW_USEDEFAULT, CW_USEDEFAULT, w, h, NULL, NULL, win.hInstance, NULL);
    
    // Set default font
    HFONT hFont = CreateFont(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET, 
                             OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
                             DEFAULT_PITCH | FF_SWISS, "Segoe UI");
    SendMessage(win.hwnd, WM_SETFONT, (WPARAM)hFont, TRUE);
    
    return win;
}

void e156_Button(e156_Window* win, const char* text, int x, int y, int w, int h, int id) {
    HWND btn = CreateWindow("BUTTON", text, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 
                            x, y, w, h, win->hwnd, (HMENU)(intptr_t)id, win->hInstance, NULL);
    SendMessage(btn, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
}

void e156_Label(e156_Window* win, const char* text, int x, int y, int w, int h) {
    HWND lbl = CreateWindow("STATIC", text, WS_VISIBLE | WS_CHILD, 
                            x, y, w, h, win->hwnd, NULL, win->hInstance, NULL);
    SendMessage(lbl, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
}

void e156_Input(e156_Window* win, int x, int y, int w, int h, int id) {
    HWND edt = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 
                            x, y, w, h, win->hwnd, (HMENU)(intptr_t)id, win->hInstance, NULL);
    SendMessage(edt, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
}

void e156_Checkbox(e156_Window* win, const char* text, int x, int y, int w, int h, int id) {
    HWND chk = CreateWindow("BUTTON", text, WS_VISIBLE | WS_CHILD | BS_CHECKBOX | BS_AUTOCHECKBOX, 
                            x, y, w, h, win->hwnd, (HMENU)(intptr_t)id, win->hInstance, NULL);
    SendMessage(chk, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
}

int e156_Loop() {
    MSG msg;
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) return 0;
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 1;
}

void e156_MessageBox(const char* title, const char* msg) {
    MessageBox(NULL, msg, title, MB_OK | MB_ICONINFORMATION);
}

#endif // IMPLEMENTATION

#endif // ERROR156GUI_H
