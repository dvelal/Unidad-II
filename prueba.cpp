#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Receta.h"
#include "Producto.h"
using namespace std;

int main() {
    Almacen almacen;

    // Cargar insumos iniciales
    almacen.cargarBase();
    almacen.mostrarInsumos();
    // Crear receta (el nombre es solo informativo)

    int c;
    int cant;
    cin >> cant;
    Torta recet("Tchocolate", 0, 2, 8, 10);
    c = recet.producir(cant, almacen);
    cout << c << endl;

    // Cargar definición de la receta desde archivo
    /*if (!receta.cargarDefinicion()) {
        cout << "Error al cargar la receta\n";
        return 1;
    }

    // Intentar producir
    if (receta.producir(almacen)) {
        cout << "Producto fabricado con exito\n";
    } else {
        cout << "No se pudo fabricar el producto\n";
        cout << "Reponer: ";
        float rep;
        string insumo;
        cin >> insumo;
        cin >> rep;
        almacen.reponerInsumos(insumo, rep);
    }*/
    almacen.mostrarInsumos();
    almacen.guardarBase();
    return 0;

}
