#include"Producto.h"
class ItemVenta {
    private:
        Producto producto;
        int cantidad;
        float subTotal;

    public:
        ItemVenta(Producto p, int c);
        float calcularSubtotal();
        Producto getProducto();
        int getCantidad();
};


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
