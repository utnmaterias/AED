#include <windows.h>
#include <iostream>
#define ID_BTN_TABLA 1001

// Declaración de variables
HWND hTablaWnd = NULL;
// Declaración de funciones
double Fahrenheit(double c);
double Celsius(double f);
void DibujarGraficas(HWND hWnd, HDC hdc);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Punto de entrada de la aplicación
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const char g_szClassName[] = "Ventana";
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = g_szClassName;

    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "Fallo al registrar la clase de la ventana", "Error", MB_OK);
        return 0;
    }

    HWND hWnd = CreateWindow(g_szClassName, "Grafico de Temperaturas", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 640, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        MessageBox(NULL, "Fallo al crear la ventana", "Error", MB_OK);
        return 0;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

// Procedimiento de la ventana
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
        // Crear botón
        CreateWindow("BUTTON", "Ver Tabla",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            650, 20, 100, 30, hWnd, (HMENU)ID_BTN_TABLA,
            (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_BTN_TABLA) {
            if (!hTablaWnd) {
                hTablaWnd = CreateWindow("Ventana", "Tablas de Conversion",
                    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                    100, 100, 450, 600, hWnd, NULL,
                    (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

                // Control EDIT multilinea para mostrar texto
                HWND hEdit = CreateWindow("EDIT", "",
                    WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
                    10, 20, 410, 520, hTablaWnd, NULL,
                    (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);

                std::string tabla;

                // Tabla Celsius → Fahrenheit
                tabla += "Celsius -> Fahrenheit\r\n";
                tabla += "----------------------\r\n";
                for (int c = -30; c <= 100; c += 5) {
                    char linea[50];
                    //sprintf(linea, "%4d°C\t= %6.1f°F\n", c, Fahrenheit(c));
                    sprintf(linea, "%4d grados C\t= %6.1f grados F\r\n", c, Fahrenheit(c));
                    tabla += linea;
                }
                tabla += "\nFahrenheit -> Celsius\r\n";
                tabla += "----------------------\r\n";
                for (int f = -30; f <= 212; f += 10) {
                    char linea[50];
                    //sprintf(linea, "%4d°F\t= %6.1f°C\n", f, Celsius(f));
                    sprintf(linea, "%4d grados F\t= %6.1f grados C\r\n", f, Celsius(f));
                    tabla += linea;
                }

                SetWindowText(hEdit, tabla.c_str());
            } else {
                ShowWindow(hTablaWnd, SW_SHOW);
            }
        }
        break;

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
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Conversiones
double Fahrenheit(double c) {
    return (9.0 / 5.0) * c + 32.0;
}

double Celsius(double f) {
    return (5.0 / 9.0) * (f - 32.0);
}

// Dibujo
void DibujarGraficas(HWND hWnd, HDC hdc) {
    RECT rect;
    GetClientRect(hWnd, &rect);
    int ancho = rect.right - rect.left;
    int alto = rect.bottom - rect.top;

    // Márgenes
    int margenIzq = 60;
    int margenDer = 40;
    int margenSup = 40;
    int margenInf = 60;

    int zonaAncho = ancho - margenIzq - margenDer;
    int zonaAlto = alto - margenSup - margenInf;

    // Rango de temperatura
    double minC = -30.0, maxC = 100.0;       // Rango Celsius
    double minF = -30.0, maxF = 200.0;       // Rango Fahrenheit

    // Escalas
    double escalaX = zonaAncho / (maxC - minC); // Celsius
    double escalaY = zonaAlto / (maxF - minF);  // Fahrenheit

    // Origen (0°C, 32°F)
    int origenX = margenIzq + (0.0 - minC) * escalaX;
    int origenY = margenSup + (maxF - 32.0) * escalaY;

    // Funciones de conversión
    auto ConvertirX = [&](double c) -> int {
        return origenX + static_cast<int>(c * escalaX);
    };

    auto ConvertirY = [&](double f) -> int {
        return origenY - static_cast<int>((f - 32.0) * escalaY);
    };

    // Dibujar cuadrícula
    HPEN hGridPen = CreatePen(PS_SOLID, 1, RGB(220, 220, 220));
    SelectObject(hdc, hGridPen);

    for (int i = 0; i <= 10; ++i) {
        int x = margenIzq + i * zonaAncho / 10;
        MoveToEx(hdc, x, margenSup, NULL);
        LineTo(hdc, x, alto - margenInf);
    }

    for (int i = 0; i <= 10; ++i) {
        int y = margenSup + i * zonaAlto / 10;
        MoveToEx(hdc, margenIzq, y, NULL);
        LineTo(hdc, ancho - margenDer, y);
    }

    DeleteObject(hGridPen);

    // Ejes
    HPEN hAxisPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
    SelectObject(hdc, hAxisPen);

    // Eje X
    MoveToEx(hdc, margenIzq, origenY, NULL);
    LineTo(hdc, ancho - margenDer, origenY);

    // Eje Y
    MoveToEx(hdc, origenX, margenSup, NULL);
    LineTo(hdc, origenX, alto - margenInf);

    DeleteObject(hAxisPen);

    // Etiquetas
    TextOut(hdc, ancho - 100, origenY + 20, "Celsius", 7);
    TextOut(hdc, origenX - 30, margenSup - 20, "Fahrenheit", 10);

    // Marcas Celsius (eje X)
    for (int c = -30; c <= 100; c += 10) {
        int x = ConvertirX(c);
        char label[10];
        sprintf(label, "%d", c);
        TextOut(hdc, x - 10, origenY + 5, label, strlen(label));
    }

    // Marcas Fahrenheit (eje Y)
    for (int f = -30; f <= 200; f += 20) {
        int y = ConvertirY(f);
        char label[10];
        sprintf(label, "%d", f);
        TextOut(hdc, origenX - 45, y - 7, label, strlen(label));
    }

    // Dibujar Celsius → Fahrenheit (Azul)
    HPEN hBluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
    SelectObject(hdc, hBluePen);

    for (int c = -30; c <= 100; ++c) {
        double f = Fahrenheit(c);
        int x = ConvertirX(c);
        int y = ConvertirY(f);
        if (c == -30)
            MoveToEx(hdc, x, y, NULL);
        else
            LineTo(hdc, x, y);
    }

    DeleteObject(hBluePen);

    // Dibujar Fahrenheit → Celsius (Verde)
    HPEN hGreenPen = CreatePen(PS_SOLID, 2, RGB(0, 180, 0));
    SelectObject(hdc, hGreenPen);

    for (int f = -30; f <= 200; ++f) {
        double c = Celsius(f);
        int x = ConvertirX(c);
        int y = ConvertirY(f);
        if (f == -30)
            MoveToEx(hdc, x, y, NULL);
        else
            LineTo(hdc, x, y);
    }

    DeleteObject(hGreenPen);
}
