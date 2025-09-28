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

    // Inicializamos el arreglo de ventas por vendedor y mes con ceros
    std::array<std::array<int, 12>, 3> ventas_por_vendedor_y_mes = {0};
    int venta, mes, vendedor;

    // Leer los datos de ventas hasta el final del archivo
    while (archivo >> vendedor >> mes >> venta) {
        if (vendedor >= 0 && vendedor < 3 && mes >= 0 && mes < 12) {
            //ventas_por_vendedor_y_mes[vendedor][mes] += venta;  // Sumar la venta al vendedor y mes correspondiente
            ventas_por_vendedor_y_mes.at(vendedor).at(mes)+= venta;  // Sumar la venta al vendedor y mes correspondiente
        }
    }

    // Imprimir ventas por vendedor y mes
    std::cout << "Ventas por vendedor y mes:" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "Vendedor " << i << ":" << std::endl;
        for (int j = 0; j < 12; ++j) {
            //std::cout << "Mes " << j + 1 << ": " << ventas_por_vendedor_y_mes[i][j] << std::endl;
            std::cout << "Mes " << j + 1 << ": " << ventas_por_vendedor_y_mes.at(i).at(j)<< std::endl;
        }
    }

    return 0;
}
