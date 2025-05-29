#pragma once
 
#include<string> 


class  kg{
  static  HDC  hdc  ; 
    static  HWND  hwnd ;
    static HINSTANCE  hInst  ;
    static HGDIOBJ  currentObj  ;
public:
	  ~kg();
	static void initLib(HINSTANCE hInstance, HWND);

	static void BeginPaint(HWND h, LPPAINTSTRUCT lpPaint);
	static BOOL  BeginPath();
	static BOOL CloseFigure();
    // 1. Создание объектов
    static HPEN CreatePen(int style, int width, COLORREF color);
    static HBRUSH CreateSolidBrush(COLORREF color);
    static HRGN PathToRegion();
  
    static HCURSOR LoadCursor(LPCWSTR name);
    static HICON LoadIcon(LPCWSTR name);

    // 2. Управление окнами
#undef CreateWindow
    static HWND CreateWindow(
        LPCWSTR className,
        LPCWSTR title,
        DWORD style,
        int x, int y,
        int width, int height,
        HWND parent = nullptr,
        HMENU menu = nullptr,
        HINSTANCE hInstance= nullptr,
         LPVOID lpParam= nullptr
    );
#undef CreateWindowW
    static HWND CreateWindowW(
        LPCWSTR className,
        LPCWSTR title,
        DWORD style,
        int x, int y,
        int width, int height,
        HWND parent = nullptr,
        HMENU menu = nullptr,
        HINSTANCE hInstance= nullptr,
         LPVOID lpParam= nullptr
    );

    static ATOM RegisterClass(const WNDCLASSW* wc);
    static void DestroyWindow();
    static int ShowWindow(int nCmdShow);
    static BOOL UpdateWindow();
    static void InvalidateRect(const RECT* rect = nullptr, BOOL erase = TRUE);

    // 3. Контекст устройства
    static HDC GetDC();
    static int ReleaseDC();
    static HDC BeginPaint(PAINTSTRUCT* ps);

    static void EndPaint(PAINTSTRUCT* ps);
    static int SetMapMode(int mode);
    static int SetPolyFillMode(int mode);
    static void SetViewportExt(int x, int y, SIZE* size = nullptr);
    static void SetViewportOrg(int x, int y, SIZE* size = nullptr);
    static void SetWindowExt(int x, int y, SIZE* size = nullptr);

    // 4. Рисование
    static void LineTo(int x, int y);
    static void MoveToEx(int x, int y, POINT* pt = nullptr);
    static void Rectangle(int left, int top, int right, int bottom);
    static void Ellipse(int left, int top, int right, int bottom);
    static void SetPixel(int x, int y, COLORREF color);
    static void Polyline(const POINT* points, int count);
    static void Polygon(const POINT* points, int count);
    static void PolyBezier(const POINT* points, DWORD count);

    // 5. Пути 
    static void EndPath();
    static void StrokePath();
    static void FillPath();

    // 6. Сообщения
    static BOOL GetMessage(LPMSG msg, UINT min = 0, UINT max = 0);
    static LRESULT DispatchMessage(const MSG* msg);
    static BOOL TranslateMessage(const MSG* msg);
    static void PostQuitMessage(int code);
    static LRESULT DefWindowProc(UINT msg, WPARAM wParam, LPARAM lParam);

    // 7. Утилиты
    static void DeleteObject(HGDIOBJ obj);
    static HGDIOBJ SelectObject(HGDIOBJ obj);
    static BOOL PtInRect(const RECT * rect, POINT pt);
    static void FillRect(const RECT* rc, HBRUSH brush);
    static int MessageBox(LPCWSTR text, LPCWSTR caption, UINT type);
    static HWND SetCapture();
    static BOOL ReleaseCapture();

     static BOOL SetRect( LPRECT lprc,int xLeft, int yTop,int xRight, int yBottom);

};