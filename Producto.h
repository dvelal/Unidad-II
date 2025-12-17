#pragma once
#include<iostream>
#include<vector>
#include<iomanip>
#include"Receta.h"

class Producto{
    protected:
        std::string idProducto;
        std::string nombre;
        int stockActual;
        int stockMinimo;
    public:
        Producto();
        virtual ~Producto() = default;
        Producto(std::string n, int sa, int sm); 
        //getters
        int getStockActual();
        int getStockMinimo();
        std::string getIdProducto();
        std::string getNombre();
        //setters
        virtual void actualizarStock(int) = 0;
        virtual char prefijoId() = 0;
        void setId(std::string id);
        //indicadores
        bool estaBajoMinimo();
        virtual void mostrarDatos();
        
};
Producto::Producto(){
    idProducto="000";
    nombre = "No hay nombre disponible";
    stockActual = 0;
    stockMinimo = 0;
}
Producto::Producto(std::string n, int sa, int sm){
    nombre = n;
    stockActual = sa;
    stockMinimo = sm;
}
bool Producto::estaBajoMinimo(){
    if(stockActual < stockMinimo)
        return true;
    else return false;
}
void Producto::mostrarDatos(){
    std::cout<<"ID: "<<idProducto;
    std::cout<<std::left<<" Producto: "<<std::setw(20)<<nombre;
    std::cout<<"  Stock: "<<std::setw(5)<<stockActual;;
    if(estaBajoMinimo()){
        std::cout<<"\tHay que reponer el producto";
    }
}
int Producto::getStockActual(){
    return stockActual;
}
int Producto::getStockMinimo(){
    return stockMinimo;
}
std::string Producto::getIdProducto(){
    return idProducto;
}
std::string Producto::getNombre(){
    return nombre;
}
void Producto::setId(std::string id){
    idProducto = id;
}

#include<map>
#include<sstream>

class Inventario{
    private:
        std::map<std::string,Producto*> productos;
        std::map<char,int> contadores;
        std::string formatearId(int n);
    public:
        
        ~Inventario();
        void agregarProducto(Producto*);
        void actualizarStock(std::string id, int cant);
        Producto* buscarPorId(std::string id);
        void venderProducto(std::string id , int );
        void mostrarProductos();
        void cargarProductos(const std::string&);
        void guardarProductos(const std::string&);
        //Producto* accederProductoPorId(std::string id);
};

Inventario::~Inventario() {
    for (auto &p : productos)
        delete p.second;
}
std::string Inventario::formatearId(int n){
    std::stringstream ss;
    ss<< std::setw(3) << std::setfill('0') << n;
    return ss.str();
}
void Inventario::agregarProducto(Producto * p){//supongamos que no se duplican los productos
    char pref = p->prefijoId();
    int &contador= contadores[pref];
    contador++;
    std::string id= std::string(1,pref) + formatearId(contador);
    p->setId(id);
    productos[id]=p;
}
Producto* Inventario::buscarPorId(std::string id){
    auto it = productos.find(id);
    if (it !=productos.end()) return it->second;
    else return nullptr;
}

//corregir, ya que venderProducto supone torta::actualizar stcok
//como directo, y actualizarstock supone un actualizar por suma
void Inventario::actualizarStock(std::string id, int cant){ //falta implementar
    Producto * p = buscarPorId(id);
    if(p){
        p->actualizarStock(cant);
    }
}
void Inventario::venderProducto(std::string id, int cantidad){
    Producto* p = buscarPorId(id);  
    if (!p){
        std::cout<<"Producto no encontrado"<<std::endl;
        return;
    }
    if(cantidad <= 0){
        std::cout<<"Cantidad invalida\n";
        return;
    }
    p->actualizarStock(-cantidad);
}
void Inventario::mostrarProductos(){
    for(auto &par : productos){
        par.second->mostrarDatos();
    }
}

class Torta : public Producto{
    private: 
        int maxPorciones;
        float precio;
        vector<Receta> receta;
    public:
        Torta();
        Torta(std::string n, int sa, int sm,int mp, float p);
        void venderTorta(int);
        void actualizarStock(int cant);
        void mostrarDatos();
        char prefijoId() {return 'T';}
        int producir(int cant, Almacen& almacen);
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
    stockActual += cant;
}

void Torta::mostrarDatos(){
    Producto::mostrarDatos();
    std::cout<<" N de porciones: "<<maxPorciones;
    std::cout<<" Precio: " << precio<<std::endl;
}

int Torta::producir(int cant, Almacen& almacen){
    Receta recet(nombre);
    int c = 0;
    if(recet.cargarDefinicion()){
        for(int i = 0; i < cant; i++){
            if(recet.producir(almacen)){
                stockActual++;
                c++;
            } else {
                break;
            }
        }
    } else {
        cout << "No se encontro Receta" << endl;
    }
    return c;
};


