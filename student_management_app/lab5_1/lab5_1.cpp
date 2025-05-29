// lab5_1.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "lab5_1.h"
#include "kg.h"
#pragma comment(lib, "kg.lib")

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB51, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB51));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB51));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB51);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = kg::CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   kg::ShowWindow(nCmdShow);
   kg::UpdateWindow();

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
const int WIDTH = 400;
const int HEIGHT = 300;
float v11, v12, v13, v21, v22, v23, v31, v32, v33, v43; 
float rho = 300., thetta = 75., phi = 30., ScreenDist = 500.; 
float A, B, C, D, An, Bn, Cn; 
float xt[3], yt[3], zt[3]; 
float Al, Bl, Cl;
float alpha;
float th, ph, costh, cosph, sinth, sinph;
float factor = atan(1.0) / 45.; 
PAINTSTRUCT ps;
static HBRUSH hBrush;
class TFPoint
{
public:
    float X;
    float Y;
    float Z;
};
TFPoint CubePoints[] =
{
{-50,-50, -50},
{ 50,-50, -50},
{ 50, 50, -50},
{-50, 50, -50},
{-50, 50, 50},
{-50,-50, 50},
{ 50,-50, 50},
{ 50, 50, 50}
};
int Gran[6][4] =
{
 {0,3,4,5},
 {0,5,6,1},
 {2,7,4,3},
 {7,6,5,4},
 {0,1,2,3},
 {2,1,6,7}
};
void VidMatCoeff(float rho, float thetta, float phi)
{
    th = thetta * factor; ph = phi * factor;
    costh = cos(th); sinth = sin(th); cosph = cos(ph); sinph = sin(ph);
    v11 = -sinth; v12 = -cosph * costh; v13 = -sinph * costh;
    v21 = costh; v22 = -cosph * sinth; v23 = -sinph * sinth;
    v31 = 0.; v32 = sinph; v33 = -cosph;
    v43 = rho;
}
POINT Perspective(float x, float y, float z)
{
    POINT point;
    float xe, ye, ze;
    VidMatCoeff(rho, thetta, phi);
    xe = v11 * x + v21 * y;
    ye = v12 * x + v22 * y + v32 * z;
    ze = v13 * x + v23 * y + v33 * z + v43;
    point.x = ScreenDist * xe / ze + 400.;
    point.y = ScreenDist * ye / ze + 300.;
    return point;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    POINT point1[4];
    int sx, sy, xPos, yPos, zDelta;
    switch (message)
    {
    case WM_MOUSEMOVE:
        sx = LOWORD(lParam);
        sy = HIWORD(lParam);
        thetta += ((sx % 180) - 90) / 10;
        phi += ((sy % 180) - 90) / 10;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_MOUSEWHEEL:
        zDelta = (int)wParam;
        ScreenDist -= zDelta / 1000000.;
        InvalidateRect(hWnd, NULL, TRUE);
        break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            kg::DestroyWindow();
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        kg::BeginPaint(&ps);
        th = thetta * factor; ph = phi * factor;
        costh = cos(th); sinth = sin(th); cosph = cos(ph); sinph = sin(ph);
        A = rho * sinph * costh; B = rho * sinph * sinth; C = rho * cosph;
        Al = A / (sqrt(A * A + B * B + C * C));
        Bl = B / (sqrt(A * A + B * B + C * C));
        Cl = C / (sqrt(A * A + B * B + C * C));
        for (int i = 0; i < 6; i++)
        { 
            for (int j = 0; j < 3; j++)
            {
                xt[j] = CubePoints[Gran[i][j]].X;
                yt[j] = CubePoints[Gran[i][j]].Y;
                zt[j] = CubePoints[Gran[i][j]].Z;
            }
            
            A = yt[0] * (zt[1] - zt[2]) - yt[1] * (zt[0] - zt[2]) + yt[2] * (zt[0] - zt[1]);
            B = -(xt[0] * (zt[1] - zt[2]) - xt[1] * (zt[0] - zt[2]) + xt[2] * (zt[0] - zt[1]));
            C = xt[0] * (yt[1] - yt[2]) - xt[1] * (yt[0] - yt[2]) + xt[2] * (yt[0] - yt[1]);
            
            An = A / (sqrt(A * A + B * B + C * C));
            Bn = B / (sqrt(A * A + B * B + C * C));
            Cn = C / (sqrt(A * A + B * B + C * C));
            
            alpha = (An * Al + Bn * Bl + Cn * Cl);
            
            for (int j = 0; j < 4; j++)
            {
                point1[j] = Perspective(CubePoints[Gran[i][j]].X,
                    CubePoints[Gran[i][j]].Y,
                    CubePoints[Gran[i][j]].Z);
            }
            D = point1[0].x * (point1[1].y - point1[2].y) -
                point1[1].x * (point1[0].y - point1[2].y) +
                point1[2].x * (point1[0].y - point1[1].y);
            if (D < 0)
            {
                hBrush = CreateSolidBrush(RGB((1 - alpha) * 255,
                    (1 - alpha) * 255, (1 - alpha) * 255));
                kg::SelectObject( hBrush);
                kg::Polygon( point1, 4);
            }
        }
        kg::EndPaint( &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
