#include <iostream>
#include <array>
#include <sstream>
#include <cmath>
#include <string>
#include <cassert>

// ==== ESTRUCTURAS BASICAS ====

struct Punto { double x, y; };
struct Color { unsigned char r, g, b; };
constexpr unsigned MAX_PUNTOS = 100;
constexpr unsigned MAX_POLIGONOS = 10;

struct SecuenciaPuntos {
    std::array<Punto, MAX_PUNTOS> puntos;
    unsigned cantidad = 0;

    void Add(Punto p) {
        assert(cantidad < MAX_PUNTOS);
        puntos.at(cantidad++) = p;
    }

    Punto GetPunto(unsigned i) const {
        assert(i < cantidad);
        return puntos.at(i);
    }

    void RemovePunto(unsigned i) {
        assert(i < cantidad);
        for (unsigned j = i; j < cantidad - 1; ++j)
            puntos.at(j) = puntos.at(j + 1);
        cantidad--;
    }
};

struct Poligono {
    SecuenciaPuntos pts;
    Color color{0, 0, 255};
};

// ==== FUNCIONES GEOMETRICAS ====

double GetDistancia(Punto a, Punto b) {
    return std::sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

double GetPerimetro(const Poligono& p) {
    double per = 0;
    for (unsigned i = 1; i < p.pts.cantidad; ++i)
        per += GetDistancia(p.pts.puntos.at(i-1), p.pts.puntos.at(i));
    return per;
}

unsigned GetCantidadDeLados(const Poligono& p) {
    return (p.pts.cantidad > 1) ? p.pts.cantidad - 1 : 0;
}

// ==== SECUENCIA DE POLIGONOS ====

struct SecuenciaPoligonos {
    std::array<Poligono, MAX_POLIGONOS> poligonos;
    unsigned cantidad = 0;

    void Add(Poligono p) {
        assert(cantidad < MAX_POLIGONOS);
        poligonos.at(cantidad++) = p;
    }
};

// ==== ORDENAMIENTO ====

void OrdenarPorLados(SecuenciaPoligonos& sec) {
    for (unsigned i = 0; i < sec.cantidad - 1; ++i) {
        unsigned min = i;
        for (unsigned j = i + 1; j < sec.cantidad; ++j)
            if (GetCantidadDeLados(sec.poligonos.at(j)) < GetCantidadDeLados(sec.poligonos.at(min)))
                min = j;
        if (min != i) std::swap(sec.poligonos.at(i), sec.poligonos.at(min));
    }
}

void OrdenarPorPerimetro(SecuenciaPoligonos& sec) {
    for (unsigned i = 0; i < sec.cantidad - 1; ++i) {
        unsigned min = i;
        for (unsigned j = i + 1; j < sec.cantidad; ++j)
            if (GetPerimetro(sec.poligonos.at(j)) < GetPerimetro(sec.poligonos.at(min)))
                min = j;
        if (min != i) std::swap(sec.poligonos.at(i), sec.poligonos.at(min));
    }
}

// ==== LECTURA DESDE STDIN ====

Poligono LeerPoligonoDesdeLinea(const std::string& linea) {
    Poligono p;
    std::istringstream iss(linea);
    double x, y;
    while (iss >> x >> y)
        p.pts.Add({x, y});
    return p;
}

// ==== SALIDA ====

void EscribirPoligonos(const SecuenciaPoligonos& sec, std::ostream& out) {
    for (unsigned i = 0; i < sec.cantidad; ++i) {
        for (unsigned j = 0; j < sec.poligonos.at(i).pts.cantidad; ++j)
            out << sec.poligonos.at(i).pts.puntos.at(j).x << " "
                << sec.poligonos.at(i).pts.puntos.at(j).y << " ";
        out << "\n";
    }
}

// ==== MAIN ====

int main() {
    SecuenciaPoligonos sec;
    std::string linea;

    // Leer polígonos desde el stdin (una línea = un polígono)
    while (std::getline(std::cin, linea) && sec.cantidad < MAX_POLIGONOS) {
        if (linea.empty()) continue;
        Poligono p = LeerPoligonoDesdeLinea(linea);
        if (p.pts.cantidad > 0)
            sec.Add(p);
    }

    // === Polígonos originales ===
    std::cout << "=== Poligonos originales ===\n";
    for (unsigned i = 0; i < sec.cantidad; ++i)
        std::cout << "Poligono " << i+1
                  << ": lados=" << GetCantidadDeLados(sec.poligonos.at(i))
                  << ", perimetro=" << GetPerimetro(sec.poligonos.at(i)) << "\n";
    std::cout << "\n";

    // === Ordenar por lados ===
    SecuenciaPoligonos porLados = sec;
    OrdenarPorLados(porLados);
    std::cout << "=== Poligonos ordenados por lados ===\n";
    for (unsigned i = 0; i < porLados.cantidad; ++i)
        std::cout << "Poligono " << i+1
                  << ": lados=" << GetCantidadDeLados(porLados.poligonos.at(i))
                  << ", perimetro=" << GetPerimetro(porLados.poligonos.at(i)) << "\n";
    std::cout << "\n";

    // === Ordenar por perímetro ===
    SecuenciaPoligonos porPer = sec;
    OrdenarPorPerimetro(porPer);
    std::cout << "=== Poligonos ordenados por perimetro ===\n";
    for (unsigned i = 0; i < porPer.cantidad; ++i)
        std::cout << "Poligono " << i+1
                  << ": lados=" << GetCantidadDeLados(porPer.poligonos.at(i))
                  << ", perimetro=" << GetPerimetro(porPer.poligonos.at(i)) << "\n";
    std::cout << "\n";

    // === Prueba de GetPunto y RemovePunto ===
    std::cout << "=== Prueba de GetPunto y RemovePunto ===\n";
    for (unsigned i = 0; i < sec.cantidad; ++i) {
        Poligono &p = sec.poligonos.at(i);
        if (p.pts.cantidad > 1) {
            std::cout << "Poligono " << i+1 << " antes: "
                      << "lados=" << GetCantidadDeLados(p)
                      << ", perimetro=" << GetPerimetro(p) << "\n";
            Punto primer = p.pts.GetPunto(0);
            std::cout << "  Primer punto: (" << primer.x << ", " << primer.y << ")\n";
            p.pts.RemovePunto(0);
            std::cout << "  Luego de Remove: "
                      << "lados=" << GetCantidadDeLados(p)
                      << ", perimetro=" << GetPerimetro(p) << "\n\n";
        }
    }

    // === Escribir polígonos ordenados en formato original ===
    std::cout << "=== Salida en formato de coordenadas ===\n";
    EscribirPoligonos(porLados, std::cout);
    EscribirPoligonos(porPer, std::cout);

    return 0;
}

