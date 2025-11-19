#include <windows.h>
#include <array>
#include <sstream>
#include <ctime>
#include <cstdlib>

constexpr unsigned MAX_PUNTOS = 8;
constexpr unsigned MAX_POLIGONOS = 40;

struct Punto { double x, y; };
struct Poligono {
    std::array<Punto, MAX_PUNTOS> pts;
    unsigned cantidad = 0;
    COLORREF color;
    double vx = 0, vy = 0;
};

const char* datosPoligonos = R"DATA(
1 1 2 3 3 1 1 1
4 4 4 6 6 6 6 4 4 4
6 1 7 0 8 1 6 1
0 0 0 1 1 1 1 0 0 0
5 5 6 7 7 6 6.5 4.5 5 4 5 5
7 2 8 4 9 3 8.5 1.5 7.5 1 7 2
3 2 4 5 5 2 3 2
0 5 2 6 4 6 6 5 4 4 2 4 0 5
2 10 4 12 6 10 2 10
10 5 11 7 13 7 14 5 12 3 10 5
8 8 9 10 11 10 12 8 10 6 8 8
1 10 2 12 3 11 2 9 1 10
5 5 4 6 4.5 7 5.5 7 6 6 5 5
2 2 3 4 4 2 2 2
5 8 6 10 7 8 5 8
8 3 9 5 10 3 8 3
11 6 12 8 13 6 11 6
14 2 15 4 16 2 14 2
4 4 4.5 5 5.5 5.5 6.5 5 7 4 6.5 3 5.5 2.5 4.5 3 4 4
10 10 11 12 12 10 10 10
12 4 13 6 14 4 12 4
14 8 15 10 16 8 14 8
16 2 17 4 18 2 16 2
18 6 19 8 20 6 18 6
20 10 21 12 22 10 20 10
22 4 23 6 24 4 22 4
24 8 25 10 26 8 24 8
1.5 1.5 3 4.5 4.5 1.5 1.5 1.5
4.5 4.5 5.5 7 7.5 6 5.5 4.5
6.5 1.5 7.5 0.5 8.5 1.5 6.5 1.5
0.5 0.5 0.5 1.5 1.5 1.5 1.5 0.5 0.5 0.5
5.5 5.5 6.5 7.5 7.5 6.5 7 5 5.5 5
7.5 2.5 8.5 4.5 9.5 3.5 9 1.5 7.5 2.5
3.5 2.5 4.5 5.5 5.5 2.5 3.5 2.5
0.5 5.5 2.5 6.5 4.5 6.5 6.5 5.5 4.5 4.5 2.5 4.5 0.5 5.5
2.5 10.5 4.5 12.5 6.5 10.5 2.5 10.5
10.5 5.5 11.5 7.5 13.5 7.5 14.5 5.5 12.5 3.5 10.5 5.5
8.5 8.5 9.5 10.5 11.5 10.5 12.5 8.5 10.5 6.5 8.5 8.5
1.5 10.5 2.5 12.5 3.5 11.5 2.5 9.5 1.5 10.5
5.5 5.5 4.5 6.5 4.75 7.5 5.75 7.5 6.0 6.5 5.5 5.5
)DATA";


std::array<Poligono, MAX_POLIGONOS> poligonos;
unsigned cantidadPoligonos = 0;

int lastMouseX = -1, lastMouseY = -1;
/*
void DibujarPoligono(HDC hdc, const Poligono& p) {
    if (p.cantidad < 2) return;
    MoveToEx(hdc, (int)p.pts[0].x, (int)p.pts[0].y, nullptr);
    for (unsigned i = 1; i < p.cantidad; ++i)
        LineTo(hdc, (int)p.pts[i].x, (int)p.pts[i].y);
    LineTo(hdc, (int)p.pts[0].x, (int)p.pts[0].y);
}
*/
void DibujarPoligono(HDC hdc, const Poligono& p) {
    if (p.cantidad < 2) return;

    POINT pts[MAX_PUNTOS];
    for (unsigned i = 0; i < p.cantidad; ++i) {
        pts[i].x = (LONG)p.pts[i].x;
        pts[i].y = (LONG)p.pts[i].y;
    }

    HBRUSH brush = CreateSolidBrush(p.color);   // color de relleno
    HPEN pen = CreatePen(PS_SOLID, 2, p.color); // color del borde
    HGDIOBJ oldBrush = SelectObject(hdc, brush);
    HGDIOBJ oldPen = SelectObject(hdc, pen);

    Polygon(hdc, pts, p.cantidad);

    SelectObject(hdc, oldBrush);
    SelectObject(hdc, oldPen);
    DeleteObject(brush);
    DeleteObject(pen);
}

unsigned CargarPoligonos() {
    std::istringstream input(datosPoligonos);
    std::string linea;
    unsigned cnt = 0;
    while (std::getline(input, linea) && cnt < MAX_POLIGONOS) {
        if (linea.empty() || linea[0] == '#') continue;
        std::istringstream ss(linea);
        Poligono p;
        double x, y;
        while (ss >> x >> y) {
            if (p.cantidad < MAX_PUNTOS)
                p.pts[p.cantidad++] = { x * 50, y * 50 };
        }
        if (p.cantidad > 0) {
            p.color = RGB(rand() % 256, rand() % 256, rand() % 256);
            p.vx = (rand() % 5 + 1) * ((rand() % 2) ? 1 : -1);
            p.vy = (rand() % 5 + 1) * ((rand() % 2) ? 1 : -1);
            poligonos[cnt++] = p;
        }
    }
    return cnt;
}

void MoverPoligonos(int ancho, int alto) {
    for (unsigned i = 0; i < cantidadPoligonos; ++i) {
        Poligono& p = poligonos[i];
        for (unsigned j = 0; j < p.cantidad; ++j) {
            p.pts[j].x += p.vx;
            p.pts[j].y += p.vy;
        }
        double minX = 1e9, maxX = -1e9, minY = 1e9, maxY = -1e9;
        for (unsigned j = 0; j < p.cantidad; ++j) {
            if (p.pts[j].x < minX) minX = p.pts[j].x;
            if (p.pts[j].x > maxX) maxX = p.pts[j].x;
            if (p.pts[j].y < minY) minY = p.pts[j].y;
            if (p.pts[j].y > maxY) maxY = p.pts[j].y;
        }
        bool rebote = false;
        if (minX < 0 || maxX > ancho) { p.vx = -p.vx; rebote = true; }
        if (minY < 0 || maxY > alto) { p.vy = -p.vy; rebote = true; }
        if (rebote)
            p.color = RGB(rand() % 256, rand() % 256, rand() % 256);
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
        PostQuitMessage(0);
        break;
    case WM_MOUSEMOVE:
        if (lastMouseX >= 0 && lastMouseY >= 0) {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);
            if (abs(x - lastMouseX) > 3 || abs(y - lastMouseY) > 3)
                PostQuitMessage(0);
        }
        lastMouseX = LOWORD(lParam);
        lastMouseY = HIWORD(lParam);
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
    srand((unsigned)time(0));

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    const char CLASS_NAME[] = "ProtectorPoligonos";
    WNDCLASSA wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = CLASS_NAME;
    RegisterClassA(&wc);

    HWND hWnd = CreateWindowExA(0, CLASS_NAME, "Protector de Polígonos",
        WS_POPUP, 0, 0, screenWidth, screenHeight,
        nullptr, nullptr, hInst, nullptr);

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, screenWidth, screenHeight, SWP_SHOWWINDOW);
    ShowCursor(FALSE);

    cantidadPoligonos = CargarPoligonos();

    HDC hdc = GetDC(hWnd);
    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP memBM = CreateCompatibleBitmap(hdc, screenWidth, screenHeight);
    SelectObject(memDC, memBM);
    HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));

    MSG msg = {};
    while (true) {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) goto salir;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        RECT r = { 0, 0, screenWidth, screenHeight };
        FillRect(memDC, &r, blackBrush);

        MoverPoligonos(screenWidth, screenHeight);
        for (unsigned i = 0; i < cantidadPoligonos; ++i) {
            HPEN pen = CreatePen(PS_SOLID, 2, poligonos[i].color);
            SelectObject(memDC, pen);
            DibujarPoligono(memDC, poligonos[i]);
            DeleteObject(pen);
        }

        BitBlt(hdc, 0, 0, screenWidth, screenHeight, memDC, 0, 0, SRCCOPY);
        Sleep(16);
    }

salir:
    ShowCursor(TRUE);
    DeleteObject(memBM);
    DeleteDC(memDC);
    ReleaseDC(hWnd, hdc);
    return 0;
}
