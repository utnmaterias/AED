#include <iostream>
#include <fstream>
#include <array>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo_de_entrada>" << std::endl;
        return 1;
    }

    // Abrir el archivo con el nombre recibido por línea de comandos
    std::ifstream archivo(argv[1]);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo " << argv[1] << std::endl;
        return 1;
    }

    std::array<int, 12> ventas_por_mes = {0};  // Inicializamos el arreglo con ceros
    int venta, mes;

    // Leer los datos de ventas hasta el final del archivo
    while (archivo >> mes >> venta) {
        if (mes >= 0 && mes < 12) {
            //ventas_por_mes[mes] += venta;  // Sumar la venta al mes correspondiente
            ventas_por_mes.at(mes) += venta;  // Sumar la venta al mes correspondiente
        }
    }

    // Imprimir ventas por mes
    std::cout << "Ventas por mes:" << std::endl;
    for (int i = 0; i < 12; ++i) {
        std::cout << "Mes " << i + 1 << ": " << ventas_por_mes[i] << std::endl;
    }

    return 0;
}
