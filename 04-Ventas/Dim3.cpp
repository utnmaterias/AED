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

    // Inicializamos el arreglo de ventas por región, vendedor y mes con ceros
    std::array<std::array<std::array<int, 12>, 3>, 4> ventas_por_region_vendedor_y_mes = {0};
    int venta, mes, vendedor, region;

    // Leer los datos de ventas hasta el final del archivo
    while (archivo >> region >> vendedor >> mes >> venta) {
        if (region >= 0 && region < 4 && vendedor >= 0 && vendedor < 3 && mes >= 0 && mes < 12) {
            ventas_por_region_vendedor_y_mes.at(region).at(vendedor).at(mes)+= venta;  // Sumar la venta a la región, vendedor y mes correspondientes
        }
    }

    // Imprimir ventas por región, vendedor y mes
    std::cout << "Ventas por region, vendedor y mes:" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << "Region " << i << ":" << std::endl;
        for (int j = 0; j < 3; ++j) {
            std::cout << "  Vendedor " << j << ":" << std::endl;
            for (int k = 0; k < 12; ++k) {
                std::cout << "    Mes " << k + 1 << ": " << ventas_por_region_vendedor_y_mes.at(i).at(j).at(k)<< std::endl;
            }
        }
    }

    return 0;
}
