# Ejemplo de Tipos de Datos en C++

Este TP demuestra el uso de los tipos de datos básicos en C++ mediante expresiones y pruebas con `assert`.

## Tipos de datos usados:
- `bool`
- `char`
- `unsigned`
- `int`
- `double`
- `string`

## Restricciones:
- No se utilizan variables.
- No se usa `cin` ni `cout`.
- Solo se usan valores literales.

## Observaciones

- Se demuestra que `0.1 * 10 != 1.0` debido a la representación binaria de `double`.
- Se usan notaciones literales alternativas como hexadecimal (`0xA`), octal (`012`) y científica (`1e1`).

## Crédito Extra

**¿Son todos los tipos?**

No. C++ también tiene tipos como `long`, `long long`, `float`, `wchar_t`, `char16_t`, `char32_t`, y tipos definidos por el usuario como `enum`, `struct`, `class`.

**Notaciones literales**

- Hexadecimal: `0xA`
- Octal: `012`
- Científica: `1e1`
- Unsigned: `10u`
- Float: `1.0f`

## Compilador y estándar

- **Compilador utilizado:** g++ 8.1.0 (Code::Blocks 20.03 con MinGW)  
- **Versión del lenguaje C++:** C++17  
- **Comando de compilación:**
  ```cmd
  g++ -std=c++17 tipos.cpp -o tipos.exe

