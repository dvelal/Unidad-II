#pragma once
#include<iostream>
#include<vector>
#include<Receta.h>
class Producto{
    protected:
        int idProducto;
        std::string nombre;
        int stockActual;
        int stockMinimo;
    public:
        Producto();
        virtual void actualizarStock(int) = 0;
        bool estaBajoMinimo();
        void mostrarDatos();
        int getStock();
        int getIdProducto();
        std::string getNombre();
};
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

class Torta : public Producto{
    private: 
        int maxPorciones;
        float precio;
        //Receta * receta;
    public:
        Torta();
        Torta(int, std::string nombre);
        void venderTorta(int);
        void actualizarStock(int cant);
        void mostrarDatos();
};
Torta::Torta()
:Producto::Producto()
{
    maxPorciones = 0;
    precio = 0;
}
Torta::Torta(int id,std::string n)
:Producto::Producto(){
    idProducto = id;
    nombre= n;
}
void Torta::actualizarStock(int cant){
    //hornearTorta() o algo parecido para descontar los insumos
    stockActual = cant;
}
void Torta::mostrarDatos(){
    Producto::mostrarDatos();
    std::cout<<"N de porciones: "<<maxPorciones;
    std::cout<<"\nPrecio: " << precio<<std::endl;
}

class Inventario{
    private:
        std::vector<Producto*> productos;
    public:
        
        ~Inventario();
        void agregarProducto(Producto*);
        void actualizarStock();
        Producto* buscarPorId(int id);
        void venderProducto(int , int );
        void mostrarProductos();
        void cargarDesdeArchivo(const std::string&);
        void guardarEnArchivo(const std::string&);
};

Inventario::~Inventario() {
    for (auto p : productos)
        delete p;
}
void Inventario::agregarProducto(Producto * p){
    productos.push_back(p);
}
Producto* Inventario::buscarPorId(int id){
    for(auto &p: productos){
        if(p->getIdProducto()== id)
            return p;
    }
    return nullptr;
}
void Inventario::venderProducto(int id, int cantidad){
    Producto* p = buscarPorId(id);
    if (p){
        p->actualizarStock(p->getStock() - cantidad);
    }
    if (!p){
        std::cout<<"Producto no encontrado"<<std::endl;
    }
}
void Inventario::mostrarProductos(){
    std::string nombre;
    for(auto &p : productos){
        nombre=p->getNombre();
    }
}





