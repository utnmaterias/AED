/*
¿Qué hace el programa completo?
Imprime "Voy a practicar programación" 42 veces (usando recursión).
Muestra todos los números de 0 a 15 con su binario de 4 bits (como matriz de 4 columnas).
Imprime una matriz transpuesta de los 32 binarios de 5 bits, con su valor decimal.
*/
#include <iostream>    // Biblioteca para entrada/salida estándar
#include <string>      // Biblioteca para usar strings (std::string)
using std::cout;       // Evita tener que escribir std::cout todo el tiempo
using std::string;     // Lo mismo para std::string

/*	#include <cassert>
	using namespace std; */

// Declaraciones de funciones
void EscribirFrase(int veces);
void GenerarBinarios(int n, int i = 0);
void GenerarTranspuesta(int n, int fila = 0, int col = 0);

// OTro ejemplo de BARt
//void repetirFrase(unsigned veces = 42);

/*
double calcularAhorro(int dias, double monto);
void muestra();
void mostrarDia(int dia, int total, double monto);
void probar();
*/

int main() {
    EscribirFrase(42);         // Imprime la frase 42 veces en orden ascendente
    cout << "\n";              // Línea en blanco
    GenerarBinarios(4);        // Imprime todos los binarios de 4 bits con su valor decimal
    cout << "\n";              // Línea en blanco
    GenerarTranspuesta(5);     // Imprime la matriz transpuesta para n = 5 (32 valores)
    return 0;                  // Fin del programa
	
/*	OTRO EJEMPLO DE BART
	repetirFrase(); 
    assert(true); // Prueba con assert por default
    cout << (42 == 42 ? "\nCompletado correctamente" : "Error"); // muestra el estado de la prueba

 EJEMPLO DE RECURSIVIDAD
 	cout << "=== AHORRO RECURSIVO ===\n";
    muestra();
    probar();
    // realizamos una verificaion final sobre el estado
    cout << (calcularAhorro(3, 10) == 70 ? "El proceso esta Correcto\n" : "En el proceso hay un Error\n");
*/    
}



/*  double calcularAhorro(int dias, double monto) {
    return (dias == 1) ? monto : monto + calcularAhorro(dias - 1, monto * 2);
}

void muestra(){
     cout << "\n=== EJEMPLOS ";
    mostrarDia(1, 3, 10.0);  // 3 días con $10
    
    cout << "\n- - - - - - - - - - - -";
    mostrarDia(1, 4, 5.0);   // 4 días con $5
    
    cout << "\n- - - - - - - - - - - - ";
    mostrarDia(1, 5, 1.0);    // ===5 días con $1
    
}
void mostrarDia(int dia, int total, double monto) {
    cout << "\nDia " << dia << ": $" << monto;
    if(dia > 1) cout << " (2 x $" << monto/2 << ")";
    
    if(dia < total) {
        mostrarDia(dia + 1, total, monto * 2);
    } else {
        double total_acumulado = calcularAhorro(total, monto/(1 << (total-1)));
        cout << "\nTotal acumulado: $" << total_acumulado << "\n";
    }
}

void probar() {
    cout << "\n\n=== PRUEBAS ===";
    
    assert(calcularAhorro(1, 10) == 10.0);
    cout << "\nPrueba 1: 1 dia con $10 - OK";
	
    assert(calcularAhorro(3, 10) == 70.0);  // 10 + 20 + 40
    cout << "\nPrueba 2: 3 dias con $10 - OK";
	
    assert(calcularAhorro(4, 5) == 75.0);   // 5 + 10 + 20 + 40
    cout << "\nPrueba 3: 4 dias con $5 - OK";
	
    assert(calcularAhorro(5, 1) == 31.0);   // 1 + 2 + 4 + 8 + 16
    cout << "\nPrueba 4: 5 dias con $1 - OK";
	
    assert(calcularAhorro(2, 100) == 300.0); // 100 + 200
    cout << "\nPrueba 5: 2 dias con $100 - OK";
	
    assert(calcularAhorro(3, 0.5) == 3.5);  // 0.5 + 1 + 2
    cout << "\nPrueba 6: 3 dias con $0.50 - OK";
	
    cout << "\n- - - - - - - - - - - - ";
    cout << "\nTodas las pruebas pasaron\n";
}
*/
void EscribirFrase(int veces) {
    if (veces == 0) return;    // Caso base: no imprimir si veces == 0
    EscribirFrase(veces - 1);  // Llamada recursiva primero (para imprimir en orden ascendente)
    // Imprime el número y la frase
    cout << veces << ". " << "Voy a practicar programacion" << "\n";
    // Si el cout estuviera antes de la llamada recursiva, sería en orden descendente (42 → 1)
}

/*OTro ejemplo de BARt
void repetirFrase(unsigned veces ) {
    // CasoBase: Escribe la frase (con el operador ternario cada 3 frases, hay unsalto delinea))
    // EOC: cuando llegue a 0, termina la recursión
    if(veces == 0) return;
    
    cout << "voy a practicar programacion" << (veces % 3 == 1 ? "\n" : " ");
    
    repetirFrase(veces - 1);
}
*/

void GenerarBinarios(int n, int i) {
    int total = 1 << n;     // Calcula 2^n (cantidad total de combinaciones)
    if (i == total) return; // Caso base: termina cuando i alcanza el total

    // Convertir i a binario con n dígitos
    string bin = "";                       // Binario como string
    for (int j = n - 1; j >= 0; --j) {
        bin += ((i >> j) & 1) ? '1' : '0'; // Obtiene cada bit de i desde el más significativo
    }

    cout << i << "=" << bin << " ";      // Imprime decimal = binario
    if ((i + 1) % n == 0) cout << "\n";    // Salto de línea cada n elementos para formato en filas

    GenerarBinarios(n, i + 1);  // Llamada recursiva al siguiente número

	

}

void GenerarTranspuesta(int n, int fila, int col) {
    int total = 1 << n;               // Calcula el total de combinaciones posibles con n bits: 2^n (por ejemplo, 32 si n = 5).
    int filas = 1 << (n / 2);         // Equilibrado Define cuántas filas en la matriz, usando 2^(n/2). Una forma más cuadrada.
    int columnas = total / filas;     // Calcula la cantidad de columnas necesarias para cubrir el total (total = filas × columnas).

    if (fila == filas) return;        // Caso base de la recursión: si ya se imprimieron todas las filas, termina la función.

    // Este es el índice transpuesto: normalmente recorrerías como fila * columnas + col, para transponer, col * filas + fila.
    int valor = col * filas + fila;   // Transposición [col][fila]

    // Convierte valor a binario de n bits e imprime cada bit de izquierda a derecha (desde el más significativo).
    // valor >> i mueve el bit i a la derecha, y & 1 extrae el bit.
    for (int i = n - 1; i >= 0; i--) {
        cout << ((valor >> i) & 1 ? '1' : '0');
    }
    cout << "=" << valor << "  ";   // Imprime el valor decimal al lado del binario, con algo de espaciado para alinearlo.

    if (col == columnas - 1) {                // Si llegó al final de la fila (última columna)
        cout << "\n";                         // Salto de linea
        GenerarTranspuesta(n, fila + 1, 0);   // pasa a la próxima fila
    } else {
        GenerarTranspuesta(n, fila, col + 1); // sigue a la próxima columna en la misma fila. 
                                              // Si no llegó al final de la fila, avanza una columna a la derecha.
    }
}

/*
¿Qué se logra?
Recorre una matriz virtual de filas × columnas en orden transpuesto y sin usar memoria extra.
Imprime cada posición en binario alineado con su valor decimal.
*/
