# Trabajo Practico 05 – Ordenamiento de Poligonos

## 🎯 Objetivos

- Diseñar e implementar tipos compuestos (estructuras).
- Aplicar composición de tipos (`Punto`, `SecuenciaPuntos`, `Poligono`, `SecuenciaPoligonos`).
- Demostrar capacidad de simular estructuras dinámicas con arreglos estaticos.
- Practicar lectura y escritura con flujos estandar (`cin` / `cout`).
- Implementar ordenamientos simples (Selección).

---

## 🧩 Descripcion del problema

Dado un flujo de polígonos representados por sus vertices (puntos), se debe:

1. Leerlos desde la entrada estandar (`cin`).
2. Emitirlos primero ordenados por **cantidad de lados**.
3. Luego ordenados por **perimetro**.

Cada polígono se representa como una secuencia de puntos, **cerrando** con el primero repetido al final.

### Ejemplo de entrada (`desordenados.txt`):
```cmd
1 1 2 2 3 1 1 1
4 4 4 5 5 5 5 4 4 4

Este archivo contiene:
- Un triángulo (3 lados)
- Un cuadrado (4 lados)
```

## 📤 Ejemplo de salida esperada (`ordenados.txt`)
```cmd
--- Ordenado por cantidad de lados ---
1 1 2 2 3 1 1 1
4 4 4 5 5 5 5 4 4 4
--- Ordenado por perímetro ---
1 1 2 2 3 1 1 1
4 4 4 5 5 5 5 4 4 4
```

## ⚙️ Estructuras implementadas

### `Punto`
```cpp
struct Punto {
    double x, y;
};
double GetDistancia(Punto, Punto);
```

### `SecuenciaPuntos`
```cpp
struct SecuenciaPuntos {
    std::array<Punto, 100> puntos;
    unsigned cantidad;
};
void AddPunto(SecuenciaPuntos&, Punto);
unsigned GetCantidad(const SecuenciaPuntos&);
```

### `Poligono`
```cpp
struct Poligono {
    SecuenciaPuntos puntos;
    Color color;
    void AddPunto(Punto);
    unsigned GetCantidadDeLados() const;
    double GetPerimetro() const;
};
```

### `SecuenciaPoligonos`
```cpp
struct SecuenciaPoligonos {
    std::array<Poligono, 1000> poligonos;
    unsigned cantidad;
};
void AddPoligono(SecuenciaPoligonos&, const Poligono&);
void OrdenarPorCantidadDeLados(SecuenciaPoligonos&);
void OrdenarPorPerimetro(SecuenciaPoligonos&);
```

🧮 Funcionalidad del programa
Entrada: flujo de puntos (cin)
Salida: polígonos ordenados (cout).

Ejecución esperada: 
  ```cmd
  pol < desordenados.txt > ordenados.txt
  ```
El archivo ejecutable debe llamarse pol.

🧪 Pruebas incluidas
Dentro de main() se realizan pruebas automáticas con assert para:
Distancia entre puntos (GetDistancia)
Cantidad de lados (GetCantidadDeLados)
Cálculo de perímetro (GetPerimetro)
Si alguna prueba falla, el programa se detiene con un assertion failed.

🧱 Compilación (Code::Blocks o terminal)
Se usa c++ con MinGW, el proyecto se compila directamente como: 
  ```cmd
  g++ pol.cpp -o pol
  ```
---

## 🧠 Créditos extra (opcional)
Se desarrolló una versión extendida del trabajo (`polextra.cpp`) que incorpora nuevas funcionalidades y pruebas adicionales:
### 🔹 Nuevas funciones en `SecuenciaPuntos`
```cpp
Punto GetPunto(unsigned i) const;
void RemovePunto(unsigned i);
```

📁 Estructura del proyecto
```cmd
05-Polígonos/
├── readme.md
├── pol.cpp
├── polextra.cpp
├── desordenados.txt
└── ordenados_esperado.txt
```

👨‍💻 Autores
Nombres de Grupo 7: 
Anibal Zanutti

Materia: Algoritmos y Estructura de Datos
Lenguaje: C++
Entorno: Code::Blocks + MinGW (Windows)
Año: 2025
