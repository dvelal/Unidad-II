#pragma once
#include"Producto.h"
#include<iostream>
#include<cstring>
#include<sstream>
using namespace std;
class ItemVenta {
    private:
        Producto *producto;
        int cantidad;
        float subTotal;

    public:
        ItemVenta(Producto *p, int c);
        //calculos y otros
        float calcularSubtotal();
        string datosItemVenta();
        //getters
        Producto* getProducto();
        int getCantidad();
        float getSubtotal();
        //setters
        
};

ItemVenta::ItemVenta(Producto *p, int c) {
    producto = p;
    cantidad = c;
    calcularSubtotal();
}
float ItemVenta::calcularSubtotal() {
    subTotal = cantidad * producto->getPrecio();
}
std::string ItemVenta::datosItemVenta(){
    string datos;
    stringstream ss;
    ss << to_string(cantidad)
       << producto->getIdProducto()
       << producto->getNombre()
       << producto->getPrecio()
       << to_string(calcularSubtotal());
    return ss.str();
}
Producto* ItemVenta::getProducto() {
    return producto;
}
int ItemVenta::getCantidad() {
    return cantidad;
}
float ItemVenta::getSubtotal() {
    return subTotal;
}
