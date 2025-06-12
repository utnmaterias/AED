#include <cassert> // funcion assert
#include <string> // string
#include <cmath>   // Para usar std::fabs
int main() {
    // bool
    assert(true == true);
    assert(false == false);
    assert(true != false);
    assert(true && !false);
    assert (false != not false and false == not true); // uso de 'not' como operador lógico (equivalente a !)
    // char
    assert('A' == 65);         // Código ASCII // 'A' tiene el valor ASCII 65
    assert('B' != 'C');         // Comparación de caracteres distintos
    assert('1' + 1 == '2');     // Operación con char como int  // '1' (ASCII 49) + 1 = '2' (ASCII 50)
    assert('A' + 1 == 'B');    // 'A' (65) + 1 = 'B' (66)
    //unsigned
    assert (10u + 5u == 15u); // Suma de enteros sin signo
    assert(0u < 1u);          // Comparación entre unsigned
    // int operaciones básicas con enteros
    assert(5 + 3 == 8);
    assert(-5+10 == 5);
    assert(-10 < 0);
    assert(100 - 50 == 50);
    // double operaciones con punto flotante
    assert(0.5 + 0.5 == 1.0);
    assert(2.0 * 3.0 == 6.0);
    assert(0.1 + 0.2 > 0.29 && 0.1 + 0.2 < 0.31);  // forma segura
    
    // Crédito Extra: ¿es exactamente 1.0?
    //assert(0.1 * 10 != 1.0);  // ¿por qué falla?
    //assert((0.1 * 10) != 1.0);   // Demostración del error NO es exactamente 1.0
    //assert((0.1 * 10) < 1.0);    // Pero es muy cercano
    
    assert(((0.1 * 10) - 1.0 < 1e-9) || ((1.0 - 0.1 * 10) < 1e-9)); // demostración de que son casi iguales
    //Esto demuestra tanto el problema como la forma correcta de trabajar con doubles.
    /*
        ¿Por qué 0.1 * 10 != 1.0?
        En C++ (y casi todos los lenguajes), los valores de tipo double o float no pueden representar exactamente algunos números decimales, como 0.1.

        El valor real almacenado por 0.1 no es exactamente 0.1, sino algo como:
        0.10000000000000000555... (en binario IEEE 754)

        Al multiplicarlo por 10, obtienes algo muy cercano a 1.0, pero no exactamente 1.0, por eso:
        assert((0.1 * 10) != 1.0); // Esta afirmación es verdadera

        Esto no es un error de C++, sino una limitación de la representación binaria de los números en punto flotante.
    */
    //Intentamos probar que la suma de diez veces un décimo (0.1) es uno (1.0) pero la consola nos tiró el mensaje: Assertion failed: (0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1+0.1) == 1.0
    //Esto se da por un error de aproximación, debido a la representación binaria que tienen los números de punto flotante (0.1) en la computadora. En binario, el número 1/10 (0.0001100110011...) no se puede representar exactamente como una secuencia finita de dígitos binarios, por lo que siempre va a haber una pequeña impresición.
    //Así que la suma de estos números nunca va a exactamente 1.0, siempre va a haber una pequeña impresión.
    //Para solucionar esto podríamos usar variables
    double a = 0.1 * 10;
    double b = 1.0;
    assert(std::fabs(a - b) < 1e-9); // Comparación segura con tolerancia
    assert(std::fabs((0.1 * 10) - 1.0) < 1e-9); // Comparación segura sin variables
    
    // string
    using std::string;
    assert(string("Hola") + string(" Mundo") == "Hola Mundo"); // Concatenación de strings
    assert(string("ABC").length() == 3);                       // Longitud de un string
    assert(string("Hola") + " Mundo" == "Hola Mundo");         // Concatenación con literal

    // Representaciones literales alternativas (Crédito Extra)
    // Notaciones alternativas
    assert(0xA == 10);   // Hexadecimal (0xA = 10)
    assert(012 == 10);   // Octal (012 = 10 decimal)
    assert(10 == 10);    // decimal
    assert(10u == 10);   // unsigned int literal

    assert(1e1 == 10.0); // Notación científica (1 × 10^1)

    // bool con valores enteros
    assert(bool(1) == true);    // 1 se interpreta como true
    assert(bool(0) == false);   // 0 se interpreta como false
    assert(42 == 0x2A);         // 42 decimal es igual a 0x2A hexadecimal
    assert(3.14e0 == 3.14);     // Notación científica (3.14 × 10^0)
}
