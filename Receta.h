#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct ItemReceta {
    string nombreInsumo;
    float cantidadUtil;
};

class Insumo {
    private:
        string nombre;
        float stock;
    public:
        Insumo(const string& nombre, float stockInicio);
        string getNombre() const;
        float getStock() const;
        bool consumir(float cantidad);
        void reponer(float cantidad);
};

class Almacen {
    private:
        vector<Insumo> insumos;
    public:
        void cargarBase(const string& archivoInsumos);
        bool hayStock(const string& nombreInsumo, float cantidad) const;
        bool descontar(const string& nombreInsumo, float cantidad);
};

class Receta {
    private:
        string nombreProducto;
        vector<ItemReceta> items;
    public:
        Receta(const string& nombreProducto);
        bool cargarDefinicion(const string& archivoRecetas);
        bool producir(Almacen& almacen);
};

