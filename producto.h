#pragma once
#include<iostream>
#include<vector>
#include<iomanip>
#include<sstream>
#include"Receta.h"

class Producto{
    protected:
        std::string nombre;
        std::string idProducto;
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
        virtual std::string ssdatos();
        
};
Producto::Producto(){
    idProducto="*000";
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
std::string Producto::ssdatos(){
    std::string datos;
    datos = idProducto + " " + 
    nombre + " " + 
    std::to_string(stockActual) + " " + 
    std::to_string(stockMinimo);
    return datos;
}

#include<map>
#include<fstream>


class Inventario{
    private:
        std::map<std::string,Producto*> productos;
        std::map<char,int> contadores;
        std::string formatearId(int n);
    public:
        
        ~Inventario();
        Producto* agregarProducto(Producto*);
        void actualizarStock(std::string id, int cant);
        Producto* buscarPorId(std::string id);
        void venderProducto(std::string id , int );
        void mostrarProductos();
        void guardarProductos();
        void cargarProductos(const std::string&);
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
Producto* Inventario::agregarProducto(Producto * p){//supongamos que no se duplican los productos
    //se establece el id
    char pref = p->prefijoId();
    int &contador= contadores[pref];
    contador++;
    std::string id= std::string(1,pref) + formatearId(contador);
    p->setId(id);
    //aquí se agrega el producto a inventario
    productos[id]=p;
    return p; //devuelve la direccion del producto
}
Producto* Inventario::buscarPorId(std::string id){
    auto it = productos.find(id);
    if (it !=productos.end()) return it->second;
    else return nullptr;
}


void Inventario::actualizarStock(std::string id, int cant){ 
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
void Inventario::cargarProductos(){
    std::ifstream leer;
    leer.open("Productos.txt",std::ios::in);
    if(!leer){
        std::cout<<"No se pudo abrir el archivo"<<endl;
        return;
    }
    //leer cantidad de productos
}
void Inventario::guardarProductos(){
    std::ofstream guardar;
    guardar.open("Productos.txt",std::ios::out);
    if(!guardar){
        std::cout<<"No se pudo abrir el archivo"<<endl;
        return;
    }
    guardar<<contadores.size()<<endl; //si hay 3 contadores quiere decir que hay 3 tipos de producto si hay 4, 4 y así...
    for(auto &c : contadores){
        guardar<<c.first<<" "<<c.second<<std::endl; //escribe el caracter del id y la cantidad del contador ej: T 1 //quiere decir que hay 1 producto tipo torta
                                        //al leer se leera T y se guardara el 1 en contadores["T"].
    }
    for(auto &p : productos){ //escribe los datos de los productos. aquí ya se guarda el id de cada producto
        guardar<<p.second->ssdatos()<<endl;//al leer se leera primero el id y con el primer caracter se sabra su clase()
    }
    guardar.close();
}






