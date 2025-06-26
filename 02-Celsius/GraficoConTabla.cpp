#include <windows.h>
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>

#define ID_EDIT_CELSIUS     2001
#define ID_BTN_GRAF_CELSIUS 2002
#define ID_BTN_TAB_CELSIUS  2003

#define ID_EDIT_FARENHEIT     2011
#define ID_BTN_GRAF_FARENHEIT 2012
#define ID_BTN_TAB_FARENHEIT  2013

HWND hTablaWnd = NULL;
HWND hEditTabla = NULL;
HINSTANCE hInst;

char funcionStr[256];
std::string funcionActual = "";
bool graficarCelsius = false;
bool graficarFahrenheit = false;

// -------- FUNCIONES de Conversiones
double Celsius(double f);
double Fahrenheit(double c);
double EvaluarFuncion(const std::string& func, double x);
std::string GenerarTablaValores(const std::string& funcion, double minX, double maxX, double paso);
void DibujarGraficas(HWND hWnd, HDC hdc);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void VerTabla(HWND hWndPrincipal, int editId, const char* titulo);
LRESULT CALLBACK TablaWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {
    const char CLASS_NAME[] = "MiVentanaFunciones";
    WNDCLASS wc = { };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(173, 216, 230)); // Light Blue Color de Fondo

    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(0, CLASS_NAME, "Graficador de Funciones",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL, NULL, hInst, NULL);

    ShowWindow(hWnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// -------- FUNCIONES de Conversiones
double Celsius(double f) {
    return (5.0 / 9.0) * (f - 32.0);
}

double Fahrenheit(double c) {
    return (9.0 / 5.0) * c + 32.0;
}

// -------- FUNCIONES AUXILIARES --------
double EvaluarFuncion(const std::string& func, double x) {
    std::string f = func;
    f.erase(remove(f.begin(), f.end(), ' '), f.end());

    if (f == "Celsius(x)") return Celsius(x);
    else if (f == "Fahrenheit(x)") return Fahrenheit(x);

    return 0.0;
}

std::string GenerarTablaValores(const std::string& funcion, double minX, double maxX, double paso) {
    std::string tabla = "   x\t|\ty\r\n----------------------\r\n";
    for (double x = minX; x <= maxX; x += paso) {
        double y = EvaluarFuncion(funcion, x);
        char linea[64];
        sprintf(linea, "%6.2f\t|\t%6.2f\r\n", x, y);
        tabla += linea;
    }
    return tabla;
}

void DibujarGraficas(HWND hWnd, HDC hdc) {
    RECT rect;
    GetClientRect(hWnd, &rect);
    int ancho = rect.right;
    int alto = rect.bottom;

    // Márgenes
    const int margenIzq = 60;
    const int margenDer = 40;
    const int margenSup = 40;
    const int margenInf = 60;

    int zonaAncho = ancho - margenIzq - margenDer;
    int zonaAlto = alto - margenSup - margenInf;

    // Escala visual
    double minX = -40.0, maxX = 100.0;  // Fahrenheit(x): Celsius de -40 a 120
    double minY = -40.0, maxY = 100.0;  // Suficiente para ambas funciones

    // Escalas
    double escalaX = zonaAncho / (maxX - minX);
    double escalaY = zonaAlto / (maxY - minY);

    // Origen en pantalla
    int origenX = margenIzq + static_cast<int>((0.0 - minX) * escalaX);
    int origenY = margenSup + static_cast<int>((maxY - 0.0) * escalaY);

    auto ConvertirX = [&](double x) { return margenIzq + static_cast<int>((x - minX) * escalaX); };
    auto ConvertirY = [&](double y) { return margenSup + static_cast<int>((maxY - y) * escalaY); };

    // -------- Cuadrícula --------
    HPEN hGridPen = CreatePen(PS_SOLID, 1, RGB(230, 230, 230));
    SelectObject(hdc, hGridPen);

    // Verticales cada 10 unidades
    for (int i = (int)minX; i <= (int)maxX; i += 10) {
        int x = ConvertirX(i);
        MoveToEx(hdc, x, margenSup, NULL);
        LineTo(hdc, x, alto - margenInf);
    }

    // Horizontales cada 10 unidades
    for (int i = (int)minY; i <= (int)maxY; i += 10) {
        int y = ConvertirY(i);
        MoveToEx(hdc, margenIzq, y, NULL);
        LineTo(hdc, ancho - margenDer, y);
    }
    DeleteObject(hGridPen);

    // -------- Ejes --------
    HPEN hAxisPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, hAxisPen);

    // Eje X
    MoveToEx(hdc, margenIzq, origenY, NULL);
    LineTo(hdc, ancho - margenDer, origenY);

    // Eje Y
    MoveToEx(hdc, origenX, margenSup, NULL);
    LineTo(hdc, origenX, alto - margenInf);

    DeleteObject(hAxisPen);

    // -------- Etiquetas --------
    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(0, 0, 0));

    for (int i = (int)minX; i <= (int)maxX; i+=10) {
        int x = ConvertirX(i);
        char label[10];
        sprintf(label, "%d", i);
        TextOut(hdc, x - 12, origenY + 8, label, strlen(label));
    }

    for (int i = (int)minY; i <= (int)maxY; i+=10) {
        int y = ConvertirY(i);
        char label[10];
        sprintf(label, "%d", i);
        TextOut(hdc, origenX - 35, y - 8, label, strlen(label));
    }

    TextOut(hdc, ancho - 60, origenY - 20, "X", 1);
    TextOut(hdc, origenX + 10, margenSup + 5, "Y", 1);

    // -------- Graficar funciones --------
    if (graficarFahrenheit) {
        HPEN hFarenheitPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); // rojo
        SelectObject(hdc, hFarenheitPen);

        bool primera = true;
        for (int px = 0; px < zonaAncho; ++px) {
            double xVal = minX + px / escalaX;
            double yVal = Fahrenheit(xVal);

            if (yVal < minY || yVal > maxY) {
                primera = true;
                continue;
            }

            int x = ConvertirX(xVal);
            int y = ConvertirY(yVal);

            if (primera) {
                MoveToEx(hdc, x, y, NULL);
                primera = false;
            } else {
                LineTo(hdc, x, y);
            }
        }

        DeleteObject(hFarenheitPen);
    }

    if (graficarCelsius) {
        HPEN hCelsiusPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255)); // azul
        SelectObject(hdc, hCelsiusPen);

        bool primera = true;
        for (int px = 0; px < zonaAncho; ++px) {
            double xVal = minX + px / escalaX;
            double yVal = Celsius(xVal);

            if (yVal < minY || yVal > maxY) {
                primera = true;
                continue;
            }

            int x = ConvertirX(xVal);
            int y = ConvertirY(yVal);

            if (primera) {
                MoveToEx(hdc, x, y, NULL);
                primera = false;
            } else {
                LineTo(hdc, x, y);
            }
        }

        DeleteObject(hCelsiusPen);
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
        HINSTANCE hInst = (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE);
        CreateWindow("STATIC", "Seleccione las funciones a graficar:", WS_VISIBLE | WS_CHILD,
        500, 430, 270, 20, hWnd, NULL, hInst, NULL);
        // Celsius
        CreateWindow("STATIC", "Celsius(x)", WS_VISIBLE | WS_CHILD | WS_BORDER,
            500, 450, 90, 20, hWnd, (HMENU)ID_EDIT_CELSIUS, hInst, NULL);
        CreateWindow("BUTTON", "Graficar F a C", WS_VISIBLE | WS_CHILD,
            590, 450, 100, 20, hWnd, (HMENU)ID_BTN_GRAF_CELSIUS, hInst, NULL);
        CreateWindow("BUTTON", "Tabla F a C", WS_VISIBLE | WS_CHILD,
            690, 450, 80, 20, hWnd, (HMENU)ID_BTN_TAB_CELSIUS, hInst, NULL);
        // Fahrenheit
        CreateWindow("STATIC", "Fahrenheit(x)", WS_VISIBLE | WS_CHILD | WS_BORDER,
            500, 470, 90, 20, hWnd, (HMENU)ID_EDIT_FARENHEIT, hInst, NULL);
        CreateWindow("BUTTON", "Graficar C a F", WS_VISIBLE | WS_CHILD,
            590, 470, 100, 20, hWnd, (HMENU)ID_BTN_GRAF_FARENHEIT, hInst, NULL);
        CreateWindow("BUTTON", "Tabla C a F", WS_VISIBLE | WS_CHILD,
            690, 470, 80, 20, hWnd, (HMENU)ID_BTN_TAB_FARENHEIT, hInst, NULL);
        break;
    }
    case WM_COMMAND:{
        int editId = 0;

        switch (LOWORD(wParam)) {
        case ID_BTN_GRAF_CELSIUS: editId = ID_EDIT_CELSIUS; break;
        case ID_BTN_GRAF_FARENHEIT: editId = ID_EDIT_FARENHEIT; break;
        }

        if (editId) {
            GetWindowText(GetDlgItem(hWnd, editId), funcionStr, 256);
            funcionActual = funcionStr;
            if (funcionActual == "Celsius(x)") {
                graficarCelsius = !graficarCelsius;  // alterna entre true y false
            } else if (funcionActual == "Fahrenheit(x)") {
                graficarFahrenheit = !graficarFahrenheit;  // alterna entre true y false
            }
            InvalidateRect(hWnd, NULL, TRUE);
        }

        // --- Botones de TABLA ---
        switch (LOWORD(wParam)) {
            case ID_BTN_TAB_CELSIUS:
                VerTabla(hWnd, ID_EDIT_CELSIUS, "Tabla de Celsius(x)= Celsius(x)");
                break;

            case ID_BTN_TAB_FARENHEIT:
                VerTabla(hWnd, ID_EDIT_FARENHEIT, "Tabla de Fahrenheit(x)= Fahrenheit(x)");
                break;
        }
        break;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        DibujarGraficas(hWnd, hdc);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

void VerTabla(HWND hWndPrincipal, int editId, const char* titulo) {
    const char* CLASS_NAME = "TablaFuncionClass";

    static bool claseRegistrada = false;
    if (!claseRegistrada) {
        WNDCLASS wc = {};
        wc.lpfnWndProc = TablaWindowProc;
        wc.hInstance = hInst;
        wc.lpszClassName = CLASS_NAME;
        wc.hbrBackground = CreateSolidBrush(RGB(173, 216, 230)); // Light Blue Color de Fondo
        RegisterClass(&wc);
        claseRegistrada = true;
    }

    // Obtener función desde el EDIT
    char funcionStr[256];
    GetWindowText(GetDlgItem(hWndPrincipal, editId), funcionStr, 256);
    std::string funcion(funcionStr);
    std::string tablaTexto = GenerarTablaValores(funcion, -10.0, 10.0, 1.0);

    // Crear la ventana
    HWND hwnd = CreateWindowEx(0, CLASS_NAME, titulo, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 450, 600,
        hWndPrincipal, nullptr, hInst, (LPVOID)new std::string(tablaTexto));

    ShowWindow(hwnd, SW_SHOW);
}

LRESULT CALLBACK TablaWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hEdit;

    switch (msg) {
    case WM_CREATE: {
        // Recuperar texto pasado como parámetro
        CREATESTRUCT* pcs = (CREATESTRUCT*)lParam;
        std::string* tablaPtr = (std::string*)pcs->lpCreateParams;

        hEdit = CreateWindow("EDIT", tablaPtr->c_str(),
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT |
            ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
            10, 10, 410, 520, hwnd, NULL,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

        delete tablaPtr; // liberamos memoria
        return 0;
    }

    case WM_DESTROY:
        return 0;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}
