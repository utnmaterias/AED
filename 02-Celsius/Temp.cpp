#include <iostream>
#include <cmath> //para fabs()
#include <cassert>
using std::cout;
using std::endl;

// Prototipos
bool AreNear(double a, double b, double tol = 0.001);
double Fahrenheit(double c);
double Celsius(double f);

// Función principal
int main() {
    // Pruebas AreNear
    assert(AreNear(1.00001, 1.00002, 0.001)); // debería ser true
    assert(!AreNear(1.0, 1.2, 0.01));         // debería ser false

    // Pruebas Celsius-Fahrenheit
    assert(AreNear(Fahrenheit(0), 32.0));
    assert(AreNear(Fahrenheit(100), 212.0));
    assert(AreNear(Celsius(32), 0.0));
    assert(AreNear(Celsius(212), 100.0));

    // Tabla de conversión Celsius -> Fahrenheit
    cout << "Celsius -> Fahrenheit\n";
    for (int c = -30; c <= 100; c += 10) {
        double f = Fahrenheit(c);
        cout.width(6);
        cout << c << " C = ";
        cout.width(6);
        cout.precision(1);
        cout << std::fixed << f << " F" << endl;
    }

    cout << "\nFahrenheit -> Celsius\n";
    for (int f = -20; f <= 220; f += 20) {
        double c = Celsius(f);
        cout.width(6);
        cout << f << " F = ";
        cout.width(6);
        cout.precision(1);
        cout << std::fixed << c << " C" << endl;
    }

    cout << "\nTodas las pruebas pasaron.\n";
    return 0;
}

// Definiciones
/*
bool AreNear(double a, double b, double tol){
    bool val = (a-b)<=tol && -(b-a)<=tol;
    //std::cout<<val;
    return val;
}
*/

bool AreNear(double a, double b, double tol) {
    return fabs(a - b) < tol;
}

double Fahrenheit(double c) {
    return (9.0 / 5.0) * c + 32;
}

double Celsius(double f) {
    return (5.0 / 9.0) * (f - 32);
}
