#include <iostream>
#include <fstream>

constexpr int NUM_VENDEDORES = 3;
constexpr int NUM_REGIONES = 4;
constexpr int NUM_MESES = 12;

// Función para generar un número pseudo-aleatorio entre min y max
int generarNumeroAleatorio(int min, int max, int& contador) {
    // Utilizamos un contador como semilla simple
    contador = (contador * 123456789 + 987654321) % 1000000007;  // Algoritmo simple de modificación
    return min + (contador % (max - min + 1));
}

void generarArchivoPrueba(const std::string& nombreArchivo, int tipoArchivo) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo) {
        std::cerr << "No se pudo crear el archivo " << nombreArchivo << std::endl;
        return;
    }

    // Contador para generar "números aleatorios"
    int contador = 12345;  // Valor inicial para el contador, puede cambiar

    // Generación de datos según el tipo de archivo
    if (tipoArchivo == 0) { // Test0.txt: Un solo valor total de ventas
        int totalVentas = 0;
        for (int r = 0; r < NUM_REGIONES; ++r) {
            for (int v = 0; v < NUM_VENDEDORES; ++v) {
                for (int m = 0; m < NUM_MESES; ++m) {
                    int venta = generarNumeroAleatorio(1, 1000, contador);  // Genera una venta aleatoria entre 1 y 1000
                    totalVentas += venta;
                }
            }
        }
        archivo << totalVentas << std::endl; // Guardamos el total de ventas
    } else if (tipoArchivo == 1) { // Test1.txt: Ventas por mes (una dimensión)
        for (int m = 0; m < NUM_MESES; ++m) {
            int ventasMes = 0;
            for (int r = 0; r < NUM_REGIONES; ++r) {
                for (int v = 0; v < NUM_VENDEDORES; ++v) {
                    int venta = generarNumeroAleatorio(1, 1000, contador);  // Genera una venta aleatoria entre 1 y 1000
                    ventasMes += venta;
                }
            }
            archivo << ventasMes << " "; // Guardamos la venta total para ese mes
        }
        archivo << std::endl;
    } else if (tipoArchivo == 2) { // Test2.txt: Ventas por vendedor y mes (dos dimensiones)
        for (int v = 0; v < NUM_VENDEDORES; ++v) {
            for (int m = 0; m < NUM_MESES; ++m) {
                int ventasVendedorMes = 0;
                for (int r = 0; r < NUM_REGIONES; ++r) {
                    int venta = generarNumeroAleatorio(1, 1000, contador);  // Genera una venta aleatoria entre 1 y 1000
                    ventasVendedorMes += venta;
                }
                archivo << ventasVendedorMes << " "; // Guardamos la venta para ese vendedor y mes
            }
            archivo << std::endl;
        }
    } else if (tipoArchivo == 3) { // Test3.txt: Ventas por región, vendedor y mes (tres dimensiones)
        for (int r = 0; r < NUM_REGIONES; ++r) {
            for (int v = 0; v < NUM_VENDEDORES; ++v) {
                for (int m = 0; m < NUM_MESES; ++m) {
                    int venta = generarNumeroAleatorio(1, 1000, contador);  // Genera una venta aleatoria entre 1 y 1000
                    archivo << r << " " << v << " " << m << " " << venta << std::endl;  // Guardamos los datos en el archivo
                }
            }
        }
    }

    std::cout << "Archivo de prueba " << nombreArchivo << " generado exitosamente!" << std::endl;
}

int main() {
    // Generar los archivos de prueba con diferentes datos
    generarArchivoPrueba("Test0.txt", 0);  // Test0.txt: Total de ventas
    generarArchivoPrueba("Test1.txt", 1);  // Test1.txt: Ventas por mes
    generarArchivoPrueba("Test2.txt", 2);  // Test2.txt: Ventas por vendedor y mes
    generarArchivoPrueba("Test3.txt", 3);  // Test3.txt: Ventas por región, vendedor y mes

    return 0;
}
