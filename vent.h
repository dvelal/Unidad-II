#pragma once
#include "Producto.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class ItemVenta {
private:
    Producto* producto;
    int cantidad;
    float subTotal;

public:
    ItemVenta(Producto* p, int c) {
        producto = p;
        cantidad = c;
        calcularSubtotal();
    }

    float calcularSubtotal() {
        subTotal = cantidad * producto->getPrecio();
        return subTotal;
    }

    string datosItemVenta() {
        stringstream ss;
        ss << producto->getNombre()
           << " x" << cantidad
           << " = " << subTotal;
        return ss.str();
    }

    Producto* getProducto() {
        return producto;
    }

    int getCantidad() {
        return cantidad;
    }

    float getSubtotal() {
        return subTotal;
    }
};

class Venta {
private:
    int idVenta;
    string fecha;
    string hora;
    float total;
    vector<ItemVenta> listItems;

public:
    Venta(int id, string f, string h) {
        idVenta = id;
        fecha = f;
        hora = h;
        total = 0;
    }

    void agregarItem(Producto* p, int cantidad) {
        ItemVenta item(p, cantidad);
        listItems.push_back(item);
    }

    void calcularTotal() {
        total = 0;
        for (auto& item : listItems) {
            total += item.getSubtotal();
        }
    }

    void mostrarVenta() {
        cout << "Venta N°: " << idVenta << endl;
        cout << "Fecha: " << fecha << " Hora: " << hora << endl;

        for (auto& item : listItems) {
            cout << item.getProducto()->getNombre()
                 << " x" << item.getCantidad()
                 << " = " << item.getSubtotal() << endl;
        }

        cout << "TOTAL: " << total << endl;
    }

    void generarBoleta(){
        string ruta = "BOLETAS/ventas.txt";
        ofstream Boletas(ruta, ios :: app);
        if(Boletas.is_open()){
            Boletas<<fecha<< " " <<hora<<endl; 
            for(ItemVenta& item : listItems){
                Boletas << item.datosItemVenta() << endl;
            }
            Boletas << "TOTAL: " << total;
        Boletas.close();
        } else {
            cout << "No se pudo generar boleta\n";
        } 
    }
};
