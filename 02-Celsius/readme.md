# Proyecto 02-Celsius

Este proyecto implementa la conversión entre temperaturas Celsius y Fahrenheit utilizando funciones en C++. Incluye pruebas con assert y comparación de valores en punto flotante con tolerancia.

## Archivos
- Temp.cpp: Contiene la lógica, funciones, pruebas y generación de tablas.
- Grafico.cpp: Contiene el grafico de las funciones y generación de tablas.
- readme.md: Este archivo.

## Funciones implementadas
- AreNear: compara dos valores double con tolerancia.
- Fahrenheit
- Celsius

## Compilador y estándar

- **Compilador utilizado:** g++ 8.1.0 (Code::Blocks 20.03 con MinGW)  
- **Versión del lenguaje C++:** C++17  
- **Comandos de compilación:**
  Para compilar los dos archivos por separado: Temp.cpp y Grafico.cpp

```cmd
g++ -std=c++17 Temp.cpp -o Temp.exe
g++ -std=c++17 Grafico.cpp -o Grafico.exe -lgdi32
```

## 🔍 ¿Por qué se usa `-lgdi32`?

El flag `-lgdi32` le dice al linker que incluya la **librería gráfica de Windows**, necesaria para funciones como:

- `CreatePen`
- `MoveToEx`
- `LineTo`
- `TextOut`
- `BeginPaint`
- etc.

## ✅ Requisitos para Grafico.cpp

- Solo compila en **Windows** (porque usa la API Win32).
- No requiere librerías externas, salvo las que ya vienen con MinGW (como `gdi32`).
