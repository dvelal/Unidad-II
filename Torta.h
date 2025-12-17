#pragma once
#include"Producto.h"
class Torta : public Producto{
    private: 
        int maxPorciones;
        float precio;
        //Receta * receta;
    public:
        Torta();
        Torta(std::string n, int sa, int sm,int mp, float p);
        void venderTorta(int);
        void actualizarStock(int cant);
        void mostrarDatos();
        char prefijoId() {return 'T';}
        std::string ssdatos();
};
Torta::Torta()
:Producto::Producto()
{
    maxPorciones = 0;
    precio = 0;
}
Torta::Torta(std::string n, int sa, int sm, int mp, float p)
:Producto::Producto(n,sa,sm){
    maxPorciones = mp;
    precio = p;
}
void Torta::actualizarStock(int cant){
    //hornearTorta() o algo parecido para descontar los insumos
    stockActual += cant;
}
void Torta::mostrarDatos(){
    Producto::mostrarDatos();
    std::cout<<" N de porciones: "<<maxPorciones;
    std::cout<<" Precio: " << precio<<std::endl;
}

std::string Torta::ssdatos(){
    std::string datos;
    datos = Producto::ssdatos() + "," +
    std::to_string(maxPorciones) + "," +
    std::to_string(precio);
    return datos;
}