
#include "vent.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

int main() {
    // Crear productos (ejemplo)
    Producto* p1 = new Torta("Chocolate", 10, 3, 8, 25.0);
    Producto* p2 = new Torta("Vainilla", 8, 2, 8, 20.0);

    // Crear venta
    Venta v(1, "17/12/2025", "19:45");

    // Agregar items a la venta
    v.agregarItem(p1, 2);
    v.agregarItem(p2, 1);

    // Calcular total
    v.calcularTotal();

    // Mostrar por pantalla
    v.mostrarVenta();

    // Generar boleta (archivo)
    v.generarBoleta();

    // Liberar memoria
    delete p1;
    delete p2;

    return 0;
}

