#include <iostream>
#include <array>
#include <fstream>

// Definir constantes para vendedores, regiones y meses
constexpr int NUM_VENDEDORES = 3;
constexpr int NUM_REGIONES = 4;
constexpr int NUM_MESES = 12;

// Enum para las regiones
enum class Region {
    Norte = 0,
    Sur,
    Este,
    Oeste
};

// Definir la matriz de ventas 3D (región, vendedor, mes)
using MatrizVentas = std::array<std::array<std::array<int, NUM_MESES>, NUM_VENDEDORES>, NUM_REGIONES>;

// Función para leer los datos y llenar la matriz de ventas
MatrizVentas ventasPorRegionYVendedor(std::istream& in) {
    MatrizVentas ventas = {}; // Inicializa todo a cero

    int importe, region, vendedor, mes;
    while (in >> importe >> region >> vendedor >> mes) {
        // Verificar si los índices son válidos
        if (region < 0 || region >= NUM_REGIONES || vendedor < 0 || vendedor >= NUM_VENDEDORES || mes < 0 || mes >= NUM_MESES) {
            std::cerr << "Datos fuera de rango: region=" << region << " vendedor=" << vendedor << " mes=" << mes << std::endl;
            continue; // Ignorar los datos inválidos
        }

        // Usar los índices directamente para acceder a la matriz 3D
        ventas.at(region).at(vendedor).at(mes) += importe;
    }

    return ventas;
}

// Función para obtener el nombre de la región
std::string nombreRegion(Region region) {
    switch (region) {
        case Region::Norte: return "Norte";
        case Region::Sur: return "Sur";
        case Region::Este: return "Este";
        case Region::Oeste: return "Oeste";
        default: return "Desconocida";
    }
}

// Función para calcular el máximo de ventas
int ventasMaximas(const MatrizVentas& ventas, int mes, Region region) {
    int maxVenta = -1;  // Inicializamos con un valor mínimo posible
    for (int v = 0; v < NUM_VENDEDORES; ++v) {
        if (ventas.at(static_cast<int>(region)).at(v).at(mes) > maxVenta) {
            maxVenta = ventas.at(static_cast<int>(region)).at(v).at(mes);
        }
    }
    return maxVenta;
}

// Función para calcular el mínimo de ventas
int ventasMinimas(const MatrizVentas& ventas, int mes, Region region) {
    int minVenta = 1001;  // Inicializamos con un valor máximo mayor que el valor esperado
    for (int v = 0; v < NUM_VENDEDORES; ++v) {
        if (ventas.at(static_cast<int>(region)).at(v).at(mes) < minVenta) {
            minVenta = ventas.at(static_cast<int>(region)).at(v).at(mes);
        }
    }
    return minVenta;
}

// Función para calcular el promedio de ventas
int ventasPromedio(const MatrizVentas& ventas, int mes, Region region) {
    int suma = 0;
    for (int v = 0; v < NUM_VENDEDORES; ++v) {
        suma += ventas.at(static_cast<int>(region)).at(v).at(mes);
    }
    return suma / NUM_VENDEDORES;  // Promedio entero
}

// Función para mostrar las ventas con formato
void mostrarTotales(const MatrizVentas& ventas) {
    std::cout << "Region   Vendedor   Mes   Ventas" << std::endl;

    // Mostrar las ventas por región, vendedor y mes
    for (int r = 0; r < NUM_REGIONES; ++r) {
        Region region = static_cast<Region>(r);
        std::cout << "\nRegion " << nombreRegion(region) << ":\n";

        for (int v = 0; v < NUM_VENDEDORES; ++v) {
            std::cout << "  Vendedor " << v << ":\n";
            for (int m = 0; m < NUM_MESES; ++m) {
                std::cout << "    Mes " << m + 1 << ": " << ventas.at(r).at(v).at(m) << std::endl;
            }
        }
    }

    // Mostrar estadísticas de cada región y mes
    for (int m = 0; m < NUM_MESES; ++m) {
        std::cout << "\nEstadisticas para el Mes " << m + 1 << ":\n";
        for (int r = 0; r < NUM_REGIONES; ++r) {
            Region region = static_cast<Region>(r);
            std::cout << "  Region " << nombreRegion(region) << ":\n";
            std::cout << "    Maximo: " << ventasMaximas(ventas, m, region) << std::endl;
            std::cout << "    Minimo: " << ventasMinimas(ventas, m, region) << std::endl;
            std::cout << "    Promedio: " << ventasPromedio(ventas, m, region) << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    // Comprobamos si el usuario pasó un archivo como argumento
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <archivo_de_entrada>\n";
        return 1;
    }

    // Abrimos el archivo de entrada
    std::ifstream archivo(argv[1]);
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo: " << argv[1] << "\n";
        return 1;
    }

    // Leer los datos y obtener las ventas
    MatrizVentas ventas = ventasPorRegionYVendedor(archivo);

    // Mostrar los totales de ventas con formato
    mostrarTotales(ventas);

    return 0;
}
