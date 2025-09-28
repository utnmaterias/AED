# Arreglos & Dimensiones — Total de Ventas

## Objetivos
• Demostramos capacidad de construcción de tipos compuestos mediante la aplicación sucesiva de producto cartesiano.
• Aplicamos ciclos for clásicos y ciclos for de intervalos (range_for).
• Aplicamos redireccionamiento de los flujos estándar.

## Temas
• Producto cartesiano.
• Secuencias finitas.
• Tipos std::array<T,N>.
• Inferencia de tipo con auto.
• Streams (flujos).
• Redirección de entrada y salida.
• Interfaz fluida.
• for clásico: for ( sentencia-inic condición ; expresión ) sentencia
• for intervalo: for ( sentencia-inic declaracion-for-intervalo : inicializador-for-intervalo ) sentencia

## Problema
“Dado los importes, mostramos las ventas totales”, y que después necesidades puntuales:
• #1: Dados los importes, mostramos ventas totales.
• #2: Dados los importes y meses (de 0 a 11), mostramos ventas totales por mes.
• #3: Dados los importes, meses, y números de los tres vendedores (0, 1, 2), mostramos total de ventas por mes y vendedor.
• #4: Dados los importes, meses, tres vendedores, y cuatro regiones (0, 1, 2, 4), mostramos total de ventas por mes, vendedor, y región.

## Restricciones
• Creamos archivos con set de datos diferentes para cada solución:
---
```
◦ Test0.txt
◦ Test1.txt
◦ Test2.txt
◦ Test3.txt
```
---
• Los datos se extraen en vez de cin con argv y arvc, no vienen en orden, los importes son enteros, el resultado se envía a cout
• Aplicamos std::array<T,N> y no T[N].
• Aplicamos operación •.at(•) y no •[•].
• Total de importes: Los cuatro problemas presentan el total de importes, que se implementan con múltiples dimensiones, a continuación.

◦ Soluciones a problema #1:
▪ ★ 1 variable entera (cero dimensiones)

◦ Soluciones a problema #2:
▪ 12 variables enteras (cero dimensiones, no aprovecha patron)
▪ ★ 1 variable arreglo de 12 enteros (una dimensión, aprovecha patron)

◦ Soluciones a problema #3:
▪ 6 variables enteras
▪ 3 variables arreglos de 12 enteros
▪ ★ 1 variable arreglo de 3 arreglos de 12 enteros (dos dimensiones)

◦ Soluciones a problema #4:
▪ 144 variables enteras
▪ 12 variables arreglo de 12 enteros
▪ 4 variables arreglos de 3 arreglos de 12 enteros
▪ ★ 1 variable arreglo de 4 arreglos de 3 arreglos de 12 enteros (tres dimensiones)

• Cada solución esta en archivos diferentes:
---
```
◦ Dim0.cpp
◦ Dim1.cpp
◦ Dim2.cpp
◦ Dim3.cpp
```
---

## Crédito Extra
Los siguientes ítems opcionales se basan en el problema #4, y se resuelven en Dim3Extra.cpp:

• Implementamos funciones para representar a los vendedores con strings y regiones con enum (Norte, Sur, Este, y Oeste), no con números.
• Implementamos las funciones LeerDatos y MostrarTotales
• Presentamos las tablas lo más claro posible con formato, alineación numérica y con títulos.
• Agregamos estadísticas, que aplica máximo, mínimo, y promedio. Por ejemplo: GetVendedorConMasVentas(mes, región).
• Describimos en readme.md las ventajas y desventajas de aplicar:
◦ for-intervalo en vez de for clásico.
◦ std::array<T,N> en vez de T[N].
◦ •.at(•) en vez de •[•].

## Tareas:
Por cada problema: Diseñamos el set de datos para la prueba e Implementamos la solución.
Ejecutamos la solución con redirección de la entrada para que lea del set de datos de prueba con argv y argc. Por ejemplo: Dim0 Test0.txt

## Productos:
---
```
DD-Dims
|-- README.md
|-- Test0.txt
|-- Dim0.cpp
|-- Test1.txt
|-- Dim1.cpp
|-- Test2.txt
|-- Dim2.cpp
|-- Test3.txt
|-- Dim3.cpp
|-- Dim3Extra.cpp
|-- Generar Archivos de Entrada.cpp
`-- Ver Dimensiones.bat
```
---
