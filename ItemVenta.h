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