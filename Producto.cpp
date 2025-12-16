#include"Producto.h"
Producto::Producto(){
    idProducto=-1;
    nombre = "No hay nombre disponible";
    stockActual = 0;
    stockMinimo = 0;
}
bool Producto::estaBajoMinimo(){
    if(stockActual < stockMinimo)
        return true;
    else return false;
}
void Producto::mostrarDatos(){
    std::cout<<"ID: "<<idProducto;
    std::cout<<"\nProducto: "<<nombre;
    std::cout<<"\nStock "<<stockActual<<std::endl;
    if(estaBajoMinimo()){
        std::cout<<"\tHay que reponer el producto"<<std::endl;
    }
}
int Producto::getStock(){
    return stockActual;
}
int Producto::getIdProducto(){
    return idProducto;
}
std::string Producto::getNombre(){
    return nombre;
}
