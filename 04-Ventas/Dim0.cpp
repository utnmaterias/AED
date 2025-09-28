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

    int total_ventas = 0;
    int venta;

    // Leer los valores de venta desde el archivo
    while (archivo >> venta) {
        total_ventas += venta;  // Sumar cada venta al total
    }

    // Imprimir el total de ventas
    std::cout << "Total de Ventas: " << total_ventas << std::endl;

    return 0;
}
