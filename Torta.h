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