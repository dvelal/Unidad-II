#include<ItemVenta.h>

ItemVenta::ItemVenta(Producto p, int c) {
    producto = p;
    cantidad = c;
    calcularSubtotal();
}

void ItemVenta::calcularSubtotal() {
    subtotal = cantidad * producto.getPrecio();
}

Producto ItemVenta::getProducto() {
    return producto;
}

int ItemVenta::getCantidad() {
    return cantidad;
}

float ItemVenta::getSubtotal() {
    return subtotal;
}
