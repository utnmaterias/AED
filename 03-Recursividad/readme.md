# TP de Recursividad: 
Recursion.cpp: Generador de Frases, Números Binarios recursivoy Matriz Transpuesta.

PaisajeFractal.cpp: Uso del Algoritmo Diamond Square para generar Paisaje Fractal 3d con desplazamiento, usando gdi en Windows.

Este programa en C++ realiza las siguientes funciones recursivas:

1. **EscribirFrase:** Imprime una frase repetida n veces con un contador ascendente.
2. **GenerarBinarios:** Genera e imprime todos los números binarios de `n` bits junto con su valor decimal.
3. **GenerarTranspuesta:** Imprime una matriz transpuesta de números binarios para `n` bits, mostrando la conversión decimal/binaria organizada en filas y columnas.

---

## Descripción de funciones

- **EscribirFrase(int veces):**  
  Imprime la frase "Voy a practicar programacion" `veces` veces, usando recursión para contar hacia arriba.

- **GenerarBinarios(int n, string actual = ""):**  
  Genera todos los números binarios de longitud `n`. Utiliza recursión para construir los binarios bit a bit y luego calcula su valor decimal.

- **GenerarTranspuesta(int n, int fila = 0, int col = 0):**  
  Imprime una matriz transpuesta de números binarios de `n` bits, organizada en filas y columnas, sin usar ciclos explícitos.

---
```
## Ejemplo de salida para n=4:

0 = 0000
1 = 0001
2 = 0010
3 = 0011
4 = 0100
5 = 0101
6 = 0110
7 = 0111
8 = 1000
9 = 1001
10 = 1010
11 = 1011
12 = 1100
13 = 1101
14 = 1110
15 = 1111

## Ejemplo de salida para n=5:

00000 = 0  00100 = 4  01000 = 8  01100 = 12  10000 = 16  10100 = 20  11000 = 24  11100 = 28
00001 = 1  00101 = 5  01001 = 9  01101 = 13  10001 = 17  10101 = 21  11001 = 25  11101 = 29
00010 = 2  00110 = 6  01010 = 10  01110 = 14  10010 = 18  10110 = 22  11010 = 26  11110 = 30
00011 = 3  00111 = 7  01011 = 11  01111 = 15  10011 = 19  10111 = 23  11011 = 27  11111 = 31
```
---

## Descripción del Paisaje Fractal

Este programa en C++ genera un paisaje fractal 3D desplazable utilizando funciones recursivas. Las principales funcionalidades recursivas incluyen:

- **Generación fractal del terreno:**  
  Se implementa el algoritmo *Diamond-Square* mediante una función recursiva que subdivide progresivamente el mapa de alturas para crear un terreno natural con variaciones aleatorias.

- **Refinamiento del mapa de altura:**  
  La función recursiva calcula alturas intermedias entre puntos conocidos, promediando y agregando ruido aleatorio para simular la irregularidad natural del paisaje.

- **Construcción de bloques del terreno:**  
  Se generan secciones del terreno que se desplazan horizontalmente, asegurando continuidad y detalle mediante llamadas recursivas para subdividir el espacio.

Este enfoque recursivo permite construir mapas de altura con niveles de detalle ajustables y un efecto visual de scroll infinito sobre el paisaje generado.

---
## Compilador y estándar

- **Compilador utilizado:** g++ 8.1.0 (Code::Blocks 20.03 con MinGW)  
- **Versión del lenguaje C++:** C++17  
- **Comandos de compilación:**

```cmd
g++ -std=c++17 Recursion.cpp -o Recursion.exe
```

```cmd
g++ -std=c++17 PaisajeFractal.cpp -o PaisajeFractal.exe
```

