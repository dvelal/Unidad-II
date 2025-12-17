#include<string>
#include <vector>
#include<Producto.h>

class Venta {
private:
    int idVenta;
    string fecha;
    string hora;
    float total;
    vector<ItemVenta> listItems;

public:
    Venta(int id, string f, string h);

    void agregarItem(Producto p, int cantidad);
    void calcularTotal();
    void mostrarVenta();
    vector<ItemVenta> getItems();
};

Venta::Venta(int id, string f, string h) {
    idVenta = id;
    fecha = f;
    hora = h;
    total = 0;
}

void Venta::agregarItem(Producto p, int cantidad) {
    ItemVenta item(p, cantidad);
    listItems.push_back(item);
}

void Venta::calcularTotal() {
    total = 0;
    for (auto &item : listItems) {
        total = total + item.getSubtotal();
    }
}

void Venta::mostrarVenta() {
    cout << "Venta N°: " << idVenta << endl;
    cout << "Fecha: " << fecha << " Hora: " << hora << endl;

    for (ItemVenta &item : listItems) {
        cout << item.getProducto().getNombre()
             << " x" << item.getCantidad()
             << " = " << item.getSubtotal() << endl;
    }

    cout << "TOTAL: " << total << endl;
}
#include<string>

Venta::Venta(int id, string f, string h) {
    idVenta = id;
    fecha = f;
    hora = h;
    total = 0;
}

void Venta::agregarItem(Producto p, int cantidad) {
    ItemVenta item(p, cantidad);
    listItems.push_back(item);
}

void Venta::calcularTotal() {
    total = 0;
    for (auto &item : listItems) {
        total = total + item.getSubtotal();
    }
}

void Venta::mostrarVenta() {
    cout << "Venta N°: " << idVenta << endl;
    cout << "Fecha: " << fecha << " Hora: " << hora << endl;

    for (ItemVenta &item : listItems) {
        cout << item.getProducto().getNombre()
             << " x" << item.getCantidad()
             << " = " << item.getSubtotal() << endl;
    }

    cout << "TOTAL: " << total << endl;
}