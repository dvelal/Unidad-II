#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Receta.h"
using namespace std;

int main() {
    Almacen almacen;

    // Cargar insumos iniciales
    almacen.cargarBase();
    almacen.mostrarInsumos();
    // Crear receta (el nombre es solo informativo)
    string nome;
    cin >> nome;
    Receta receta(nome);
    /*for(int i = 0; i < 2; i++){
        string in; float can; string uni;
        cin >> in >> can >> uni;
        receta.agregarInsumo(in, can, uni);
    }
    receta.crearReceta();*/

    // Cargar definición de la receta desde archivo
    if (!receta.cargarDefinicion()) {
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
    }
    almacen.mostrarInsumos();
    almacen.guardarBase();
    return 0;

}
