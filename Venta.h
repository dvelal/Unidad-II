#include<string>
#include <vector>

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