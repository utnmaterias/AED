#include <iostream>
#include <cassert>
#include <cmath>      // std::sqrt
#include <array>

// =============================
// ======== PUNTO ==============
// =============================

struct Punto {
    double x, y;
};

// Devuelve la distancia entre dos puntos
double GetDistancia(Punto a, Punto b) {
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// =============================
// ======== COLOR ==============
// =============================

struct Color {
    unsigned char r, g, b;
};

// =============================
// === SECUENCIA DE PUNTOS =====
// =============================

constexpr unsigned CANTIDAD_MAXIMA_DE_PUNTOS = 100;

struct SecuenciaPuntos {
    std::array<Punto, CANTIDAD_MAXIMA_DE_PUNTOS> puntos;
    unsigned cantidad = 0;
};

void AddPunto(SecuenciaPuntos& sec, Punto p) {
    assert(sec.cantidad < CANTIDAD_MAXIMA_DE_PUNTOS);
    sec.puntos.at(sec.cantidad++) = p;  // <- .at() para seguridad
}

unsigned GetCantidad(const SecuenciaPuntos& sec) {
    return sec.cantidad;
}

// =============================
// ======== POLIGONO ===========
// =============================

struct Poligono {
    SecuenciaPuntos puntos;
    Color color{0, 0, 255}; // azul por defecto
};

void AddPunto(Poligono& p, Punto q) {
    AddPunto(p.puntos, q);
}

unsigned GetCantidadDeLados(const Poligono& p) {
    return (p.puntos.cantidad > 1) ? p.puntos.cantidad - 1 : 0;
}

double GetPerimetro(const Poligono& p) {
    double perimetro = 0;
    for (unsigned i = 1; i < p.puntos.cantidad; ++i)
        perimetro += GetDistancia(p.puntos.puntos.at(i - 1), p.puntos.puntos.at(i));
    return perimetro;
}

// =============================
// == SECUENCIA DE POLIGONOS ===
// =============================

constexpr unsigned CANTIDAD_MAXIMA_DE_POLIGONOS = 1000;

struct SecuenciaPoligonos {
    std::array<Poligono, CANTIDAD_MAXIMA_DE_POLIGONOS> poligonos;
    unsigned cantidad = 0;
};

void AddPoligono(SecuenciaPoligonos& sec, Poligono p) {
    assert(sec.cantidad < CANTIDAD_MAXIMA_DE_POLIGONOS);
    sec.poligonos.at(sec.cantidad++) = p;
}

// =============================
// ===== ORDENAMIENTO =========
// =============================

void OrdenarPorCantidadDeLados(SecuenciaPoligonos& sec) {
    for (unsigned i = 0; i < sec.cantidad - 1; ++i) {
        unsigned indiceMin = i;
        for (unsigned j = i + 1; j < sec.cantidad; ++j) {
            if (GetCantidadDeLados(sec.poligonos.at(j)) < GetCantidadDeLados(sec.poligonos.at(indiceMin))) {
                indiceMin = j;
            }
        }
        if (indiceMin != i) {
            Poligono temp = sec.poligonos.at(i);
            sec.poligonos.at(i) = sec.poligonos.at(indiceMin);
            sec.poligonos.at(indiceMin) = temp;
        }
    }
}

void OrdenarPorPerimetro(SecuenciaPoligonos& sec) {
    for (unsigned i = 0; i < sec.cantidad - 1; ++i) {
        unsigned indiceMin = i;
        for (unsigned j = i + 1; j < sec.cantidad; ++j) {
            if (GetPerimetro(sec.poligonos.at(j)) < GetPerimetro(sec.poligonos.at(indiceMin))) {
                indiceMin = j;
            }
        }
        if (indiceMin != i) {
            Poligono temp = sec.poligonos.at(i);
            sec.poligonos.at(i) = sec.poligonos.at(indiceMin);
            sec.poligonos.at(indiceMin) = temp;
        }
    }
}

// =============================
// ======== ENTRADA/SALIDA =====
// =============================

Poligono CrearPoligono(std::istream& in) {
    Poligono p;
    Punto primero, actual;

    if (!(in >> primero.x >> primero.y))
        return p; // fin del archivo

    AddPunto(p, primero);

    while (in >> actual.x >> actual.y) {
        AddPunto(p, actual);
        // si repite el primer punto, se cierra el polígono
        if (actual.x == primero.x && actual.y == primero.y)
            break;
    }

    return p;
}

SecuenciaPoligonos LeerPoligonos(std::istream& in) {
    SecuenciaPoligonos sec;
    while (true) {
        Poligono p = CrearPoligono(in);
        if (GetCantidadDeLados(p) == 0)
            break;
        AddPoligono(sec, p);
    }
    return sec;
}

void EscribirPoligono(const Poligono& p, std::ostream& out) {
    for (unsigned i = 0; i < p.puntos.cantidad; ++i)
        out << p.puntos.puntos.at(i).x << " " << p.puntos.puntos.at(i).y << " ";
    out << "\n";
}

void EscribirPoligonos(const SecuenciaPoligonos& sec, std::ostream& out) {
    for (unsigned i = 0; i < sec.cantidad; ++i)
        EscribirPoligono(sec.poligonos.at(i), out);
}

// =============================
// =========== MAIN ============
// =============================

int main() {
    // Pruebas unitarias
    {
        assert(std::abs(GetDistancia({0, 0}, {3, 4}) - 5) < 1e-9);

        Poligono tri;
        AddPunto(tri, {0, 0});
        AddPunto(tri, {1, 0});
        AddPunto(tri, {0, 1});
        AddPunto(tri, {0, 0});
        assert(GetCantidadDeLados(tri) == 3);
        assert(std::abs(GetPerimetro(tri) - (1 + std::sqrt(2) + 1)) < 1e-9);
    }

    // Procesamiento
    SecuenciaPoligonos sec = LeerPoligonos(std::cin);

    // Ordenar y escribir por cantidad de lados
    OrdenarPorCantidadDeLados(sec);
    std::cout << "=== Ordenado por cantidad de lados ===\n";
    EscribirPoligonos(sec, std::cout);

    // Ordenar y escribir por perímetro
    OrdenarPorPerimetro(sec);
    std::cout << "=== Ordenado por perimetro ===\n";
    EscribirPoligonos(sec, std::cout);

    return 0;
}
