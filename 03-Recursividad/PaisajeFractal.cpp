#include <windows.h> // Librería de Windows para gráficos y manejo de ventanas
#include <ctime>     // Para generar números aleatorios con semilla basada en tiempo

#pragma comment(lib, "user32.lib")   // Funciones básicas de ventanas
#pragma comment(lib, "gdi32.lib")    // Funciones gráficas (dibujar, colores, etc)

// Constantes del terreno
const int EXPONENTE = 6;
const int TAM_MAPA = (1 << EXPONENTE) + 1; // Tamaño del lado del cuadrado: 2^exp + 1 = 65
const int VISIBLE = 65;     // Cantidad de columnas visibles en pantalla
const int EXTENSION = 200;  // Ancho total del mapa (permite scroll)

// Mapa de alturas donde se genera el terreno
float mapaAltura[TAM_MAPA][EXTENSION] = {0};

// Variables para el desplazamiento del terreno
int desplazamientoX = 0;
int inicioLogico = 0;

// Retorna un color dependiendo de la altura
COLORREF ObtenerColorPorAltura(float altura) {
    if (altura < 15) return RGB(20, 40, 160);       // Agua
    if (altura < 30) return RGB(194, 178, 128);     // Arena
    if (altura < 50) return RGB(34, 139, 34);       // Césped
    if (altura < 70) return RGB(0, 100, 0);         // Bosque
    if (altura < 90) return RGB(139, 137, 137);     // Montaña
    return RGB(255, 250, 250);                      // Nieve
}

// Algoritmo recursivo para generar terreno fractal Diamond-Square
void Diamante(int x, int y, int tam, float variacion) {
    if (tam < 2) return; // Caso base

    int mitad = tam / 2;
    int centroX = x + mitad;
    int centroY = y + mitad;

    // Paso "Diamante": promedio de las 4 esquinas
    float promedio = (
        mapaAltura[y][x] +
        mapaAltura[y][x + tam] +
        mapaAltura[y + tam][x] +
        mapaAltura[y + tam][x + tam]
    ) / 4.0f;

    // Asignar altura al centro con variación aleatoria
    mapaAltura[centroY][centroX] = promedio + ((rand() % 1000) / 1000.0f - 0.5f) * variacion;

    // Macro para asignar altura solo si aún no tiene valor
    #define ASIGNAR(i, j, valor) if (mapaAltura[j][i] == 0) mapaAltura[j][i] = valor

    float valor;

    // Paso "Square": puntos medios de los lados
    valor = (mapaAltura[y][x] + mapaAltura[y][x + tam] + mapaAltura[centroY][centroX]) / 3 + ((rand() % 1000) / 1000.0f - 0.5f) * variacion;
    ASIGNAR(centroX, y, valor);

    valor = (mapaAltura[y + tam][x] + mapaAltura[y + tam][x + tam] + mapaAltura[centroY][centroX]) / 3 + ((rand() % 1000) / 1000.0f - 0.5f) * variacion;
    ASIGNAR(centroX, y + tam, valor);

    valor = (mapaAltura[y][x] + mapaAltura[y + tam][x] + mapaAltura[centroY][centroX]) / 3 + ((rand() % 1000) / 1000.0f - 0.5f) * variacion;
    ASIGNAR(x, y + tam, valor);

    valor = (mapaAltura[y][x + tam] + mapaAltura[y + tam][x + tam] + mapaAltura[centroY][centroX]) / 3 + ((rand() % 1000) / 1000.0f - 0.5f) * variacion;
    ASIGNAR(x + tam, centroY, valor);

    // Llamadas recursivas para subdividir el cuadrado
    Diamante(x, y, mitad, variacion * 0.5f);
    Diamante(x + mitad, y, mitad, variacion * 0.5f);
    Diamante(x, y + mitad, mitad, variacion * 0.5f);
    Diamante(x + mitad, y + mitad, mitad, variacion * 0.5f);

    #undef ASIGNAR
}

// Genera un nuevo bloque del mapa a partir de una posición inicial
void GenerarBloque(int inicio) {
    if (inicio + TAM_MAPA >= EXTENSION) return;

    // Inicializar la sección a 0
    for (int y = 0; y < TAM_MAPA; y++)
        for (int x = inicio; x < inicio + TAM_MAPA; x++)
            mapaAltura[y][x] = 0;

    // Mantener continuidad con el bloque anterior
    mapaAltura[0][inicio] = mapaAltura[0][inicio - 1];
    mapaAltura[TAM_MAPA - 1][inicio] = mapaAltura[TAM_MAPA - 1][inicio - 1];

    // Esquinas derechas con altura aleatoria
    mapaAltura[0][inicio + TAM_MAPA - 1] = rand() % 100;
    mapaAltura[TAM_MAPA - 1][inicio + TAM_MAPA - 1] = rand() % 100;

    // Generar la sección con el algoritmo fractal
    Diamante(inicio, 0, TAM_MAPA - 1, 50);
}

// Dibuja el paisaje completo en perspectiva isométrica
void DibujarPaisaje(HDC hdc, int ancho, int alto, int desplazamiento) {
    POINT cuad[4]; // Cuatro puntos del cuadrilátero
    int centroX = ancho / 2;
    int centroY = alto / 3;

    for (int y = 0; y < TAM_MAPA - 1; y++) {
        for (int x = 0; x < VISIBLE - 1; x++) {
            int xRel = x + desplazamiento;
            if (xRel < 0 || xRel >= EXTENSION - 1) continue;

            // Cálculo de las coordenadas isométricas de los puntos
            cuad[0] = { (x - y) * 8 + centroX, (x + y) * 4 - (int)(mapaAltura[y][xRel] * 2.5f) + centroY };
            cuad[1] = { ((x + 1) - y) * 8 + centroX, ((x + 1) + y) * 4 - (int)(mapaAltura[y][xRel + 1] * 2.5f) + centroY };
            cuad[2] = { ((x + 1) - (y + 1)) * 8 + centroX, ((x + 1) + (y + 1)) * 4 - (int)(mapaAltura[y + 1][xRel + 1] * 2.5f) + centroY };
            cuad[3] = { (x - (y + 1)) * 8 + centroX, (x + (y + 1)) * 4 - (int)(mapaAltura[y + 1][xRel] * 2.5f) + centroY };

            // Promedio de altura para determinar color
            float promedio = (mapaAltura[y][xRel] + mapaAltura[y][xRel + 1] +
                              mapaAltura[y + 1][xRel + 1] + mapaAltura[y + 1][xRel]) / 4.0f;

            HBRUSH brocha = CreateSolidBrush(ObtenerColorPorAltura(promedio));
            HGDIOBJ anterior = SelectObject(hdc, brocha);
            Polygon(hdc, cuad, 4); // Dibuja el terreno

            SelectObject(hdc, anterior);
            DeleteObject(brocha);
        }
    }
}

// Función que maneja los eventos del sistema (ventana)
LRESULT CALLBACK ProcesoVentana(HWND ventana, UINT mensaje, WPARAM wp, LPARAM lp) {
    switch (mensaje) {
    case WM_CREATE:
        srand(time(NULL));         // Semilla para números aleatorios
        GenerarBloque(0);          // Primer bloque
        GenerarBloque(VISIBLE);    // Segundo bloque
        SetTimer(ventana, 1, 33, NULL); // Temporizador (~30 FPS)
        ShowCursor(FALSE);         // Ocultar cursor
        return 0;

    case WM_TIMER:
        desplazamientoX++;
        if (desplazamientoX >= TAM_MAPA - 1) {
            inicioLogico += desplazamientoX;
            desplazamientoX = 0;

            // Si se llega al final, reiniciar
            if (inicioLogico + VISIBLE >= EXTENSION - TAM_MAPA)
                inicioLogico = 0;

            GenerarBloque(inicioLogico + VISIBLE);
        }
        InvalidateRect(ventana, NULL, FALSE); // Solicita repintar
        return 0;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC dc = BeginPaint(ventana, &ps);
        RECT rect;
        GetClientRect(ventana, &rect);
        int ancho = rect.right;
        int alto = rect.bottom;

        // Dibujo en buffer (doble buffering)
        HDC memoriaDC = CreateCompatibleDC(dc);
        HBITMAP bmp = CreateCompatibleBitmap(dc, ancho, alto);
        HBITMAP anterior = (HBITMAP)SelectObject(memoriaDC, bmp);

        // Pintar cielo de fondo
        HBRUSH cielo = CreateSolidBrush(RGB(180, 220, 255));
        FillRect(memoriaDC, &rect, cielo);
        DeleteObject(cielo);

        // Dibujar paisaje
        DibujarPaisaje(memoriaDC, ancho, alto, inicioLogico + desplazamientoX);

        // Mostrar en pantalla
        BitBlt(dc, 0, 0, ancho, alto, memoriaDC, 0, 0, SRCCOPY);
        SelectObject(memoriaDC, anterior);
        DeleteObject(bmp);
        DeleteDC(memoriaDC);
        EndPaint(ventana, &ps);
        return 0;
    }

    // Cerrar con cualquier tecla o clic
    case WM_KEYDOWN:
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(ventana, mensaje, wp, lp);
}

// Función principal (entrada del programa)
int WINAPI WinMain(HINSTANCE instancia, HINSTANCE, LPSTR, int nCmdShow) {
    const char NOMBRE_CLASE[] = "FractalPaisaje";

    // Registrar clase de ventana
    WNDCLASS wc = {};
    wc.lpfnWndProc = ProcesoVentana;
    wc.hInstance = instancia;
    wc.lpszClassName = NOMBRE_CLASE;
    RegisterClass(&wc);

    // Obtener resolución de pantalla
    int anchoPantalla = GetSystemMetrics(SM_CXSCREEN);
    int altoPantalla = GetSystemMetrics(SM_CYSCREEN);

    // Crear ventana en pantalla completa
    HWND ventana = CreateWindowEx(
        0, NOMBRE_CLASE, "", WS_POPUP,
        0, 0, anchoPantalla, altoPantalla,
        NULL, NULL, instancia, NULL);

    if (!ventana) return 0;

    ShowWindow(ventana, SW_SHOWMAXIMIZED);

    // Bucle principal de eventos
    MSG mensaje = {};
    while (GetMessage(&mensaje, NULL, 0, 0)) {
        TranslateMessage(&mensaje);
        DispatchMessage(&mensaje);
    }

    return 0;
}

