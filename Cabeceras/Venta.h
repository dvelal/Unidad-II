#pragma once
#include "Producto.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;


class ItemVenta {
    private:
        Producto* producto;
        int cantidad;
        float subTotal;

    public:
        ItemVenta(Producto* p, int c);
        Producto* getProducto();
        int getCantidad();
        float getSubtotal();
};

ItemVenta::ItemVenta(Producto* p, int c) {
    producto = p;
    cantidad = c;
    subTotal = cantidad * producto->getPrecio();
}

Producto* ItemVenta::getProducto() { return producto; }
int ItemVenta::getCantidad() { return cantidad; }
float ItemVenta::getSubtotal() { return subTotal; }


class Venta {
    private:
        int idVenta;
        string fecha;
        string hora;
        float total;
        bool cancelada;
        vector<ItemVenta> items;

        int obtenerId();
        void guardarBoleta();

    public:
        Venta(string f, string h);

        int getIdVenta();
        void agregarItem(Producto* p, int cantidad);
        bool confirmarVenta();
        void cancelarVenta();
        void mostrarVenta(); 

        static void buscarBoletaPorId(int id);
};

Venta::Venta(string f, string h) {
    fecha = f;
    hora = h;
    total = 0;
    cancelada = false;
    idVenta = obtenerId() + 1;
}

int Venta::getIdVenta() { return idVenta; }

void Venta::agregarItem(Producto* p, int cantidad) {
    if (cantidad <= 0 || p == nullptr) return;
    items.emplace_back(p, cantidad);
}

bool Venta::confirmarVenta() {
    for (auto& it : items) {
        if (it.getProducto()->getStockActual() < it.getCantidad()) {
            return false; 
        }
    }

    for (auto& it : items) {
        it.getProducto()->actualizarStock(-it.getCantidad());
        total += it.getSubtotal();
    }

    guardarBoleta();
    return true;
}

void Venta::cancelarVenta() {
    if (cancelada) return;

    for (auto& it : items) {
        it.getProducto()->actualizarStock(it.getCantidad());
    }

    cancelada = true;
    guardarBoleta();
}

void Venta::mostrarVenta() {
    cout << "\n================================" << endl;
    cout << "VENTA #" << idVenta << endl;
    cout << "Fecha: " << fecha << " | Hora: " << hora << endl;
    cout << "Estado: " << (cancelada ? "CANCELADA" : "CONFIRMADA") << endl;
    cout << "--------------------------------" << endl;
    
    for (auto& it : items) {
        cout << left << setw(15) << it.getProducto()->getNombre()
             << " x" << setw(3) << it.getCantidad()
             << " | Subt: $" << fixed << setprecision(2) << it.getSubtotal() << endl;
    }

    cout << "--------------------------------" << endl;
    cout << "TOTAL: $" << total << endl;
    cout << "================================\n" << endl;
}

int Venta::obtenerId() {
    ifstream file("BOLETAS/ventas.txt");
    string linea;
    int ultimoId = 0;

    if(!file.is_open()) return 0;

    while (getline(file, linea)) {
        if (linea.find("VENTA ") == 0) {
            stringstream ss(linea);
            string palabra;
            ss >> palabra >> ultimoId;
        }
    }
    file.close();
    return ultimoId;
}

void Venta::guardarBoleta() {
    ofstream boleta("BOLETAS/ventas.txt", ios::app);

    if (!boleta.is_open()) {
        cout << "[ERROR] No se pudo acceder a BOLETAS/ventas.txt" << endl;
        return;
    }

    boleta << "VENTA " << idVenta << endl;
    boleta << "FECHA " << fecha << endl;
    boleta << "HORA " << hora << endl;
    boleta << "ESTADO " << (cancelada ? "CANCELADA" : "CONFIRMADA") << endl;

    boleta << fixed << setprecision(2);
    boleta << "PRODUCTOS:" << endl;
    for (auto& it : items) {
      boleta << "- " << left << setw(15) << it.getProducto()->getNombre() << " "
             << "cant: " << it.getCantidad() << " "
             << "subt: " << it.getSubtotal() << endl;
    }

    boleta << "TOTAL " << total << endl;
    boleta << "END" << endl << endl;

    boleta.close();
}

void Venta::buscarBoletaPorId(int id) {
    ifstream file("BOLETAS/ventas.txt");
    string linea;
    bool mostrar = false;

    if(!file.is_open()) {
        cout << "No hay registro de ventas." << endl;
        return;
    }

    cout << "\n--- RESULTADO DE BUSQUEDA ---" << endl;
    while (getline(file, linea)) {
        if (linea == "VENTA " + to_string(id))
            mostrar = true;

        if (mostrar) {
            cout << linea << endl;
            if (linea == "END") {
                mostrar = false;
                break; 
            }
        }
    }
    file.close();
}