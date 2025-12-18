#pragma once
#include<iostream>
#include<vector>
#include<iomanip>
#include<sstream>
#include<map>
#include<fstream>
#include<algorithm>
#include"Receta.h"

class Producto {
protected:
    std::string nombre;
    std::string idProducto;
    int stockActual;
    int stockMinimo;
    float precio;
public:
    Producto();
    virtual ~Producto() = default;
    Producto(std::string n, int sa, int sm); 
    //getters
    int getStockActual();
    int getStockMinimo();
    float getPrecio();
    std::string getIdProducto();
    std::string getNombre();
    //setters
    virtual void actualizarStock(int cant) { stockActual += cant; }
    virtual char prefijoId() = 0;
    void setId(std::string id);
    //indicadores
    bool estaBajoMinimo();
    //metodos
    virtual void mostrarDatos();
    virtual std::string ssdatos();

    int producir(int cant, Almacen& almacen);
    
    //lectura
    virtual void cargarDesdeStream(std::stringstream &ss)=0;
};

Producto::Producto(){
    idProducto="*000";
    nombre = "No hay nombre disponible";
    stockActual = 0;
    stockMinimo = 0;
    precio = 0;
}
Producto::Producto(std::string n, int sa, int sm){
    nombre = n;
    stockActual = sa;
    stockMinimo = sm;
    precio = 0;
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
}
int Producto::getStockActual(){ return stockActual; }
int Producto::getStockMinimo(){ return stockMinimo; }
float Producto::getPrecio(){ return precio; }
std::string Producto::getIdProducto(){ return idProducto; }
std::string Producto::getNombre(){ return nombre; }
void Producto::setId(std::string id){ idProducto = id; }

std::string Producto::ssdatos(){
    std::string datos;
    datos = idProducto + "," + 
    nombre + "," + 
    std::to_string(stockActual) + "," + 
    std::to_string(stockMinimo);
    return datos;
}

int Producto::producir(int cant, Almacen& almacen){
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
        std::cout << "No se encontro Receta para " << nombre << std::endl;
    }
    return c;
}

class Torta : public Producto{
    private: 
        int maxPorciones;
    public:
        Torta();
        Torta(std::string n, int sa, int sm,int mp, float p);
        int getMaxPorciones();
        void actualizarStock(int cant) override;
        void mostrarDatos() override;
        char prefijoId() override {return 'T';}
        std::string ssdatos() override;
        void cargarDesdeStream(std::stringstream &ss) override;
};

Torta::Torta() : Producto() {
    maxPorciones = 0;
    precio = 0;
}
Torta::Torta(std::string n, int sa, int sm, int mp, float p)
: Producto(n,sa,sm){
    maxPorciones = mp;
    precio = p;
}
int Torta::getMaxPorciones(){ return maxPorciones; }

void Torta::actualizarStock(int cant){
    stockActual += cant;
}
void Torta::mostrarDatos(){
    Producto::mostrarDatos();
    std::cout<<" N de porciones: "<<std::left<<std::setw(2)<<maxPorciones;
    std::cout<<" Precio: " << precio<<std::endl;
}
std::string Torta::ssdatos(){
    return Producto::ssdatos() + "," +
           std::to_string(maxPorciones) + "," +
           std::to_string(precio);
}
void Torta::cargarDesdeStream(std::stringstream &ss){
    std::string token;
    std::getline(ss,nombre,',');
    std::getline(ss,token,','); stockActual = std::stoi(token);
    std::getline(ss,token,','); stockMinimo = std::stoi(token);
    std::getline(ss,token,','); maxPorciones = std::stoi(token);
    std::getline(ss,token,','); precio = std::stof(token);
}
class Inventario{
    private:
        std::map<std::string,Producto*> productos;
        std::map<char,int> contadores;
        std::string formatearId(int n);
    public:
        ~Inventario();
        Producto* agregarProducto(Producto*);
        void actualizarStock(std::string id, int cant);
        
        int producir(std::string id,int cant,Almacen& almacen);
        
        Producto* buscarPorId(std::string id);
        void venderProducto(std::string id , int );
        void mostrarProductos();
        void guardarProductos();
        void cargarProductos();
        void mostrarBajoMinimo();
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
Producto* Inventario::agregarProducto(Producto * p){
    char pref = p->prefijoId();
    int &contador= contadores[pref];
    contador++;
    std::string id= std::string(1,pref) + formatearId(contador);
    p->setId(id);
    productos[id]=p;
    return p;
}
Producto* Inventario::buscarPorId(std::string id){
    auto it = productos.find(id);
    if (it !=productos.end()) return it->second;
    else return nullptr;
}

void Inventario::actualizarStock(std::string id, int cant){ 
    Producto * p = buscarPorId(id);
    if(p) p->actualizarStock(cant);
}

int Inventario::producir(std::string id,int cant,Almacen& almacen){
    Producto *p = buscarPorId(id);
    if(p){
        return p->producir(cant,almacen);
    }
    return 0;
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
    int cantProductos;
    leer.open("Productos.txt",std::ios::in);
    if(!leer){
        return;
    }
    leer>>cantProductos;
    for(int i = 0;i<cantProductos;i++){
        char indice;
        int cant;
        leer>>indice;
        leer>>cant;
        contadores[indice] = cant;
    }
    std::string linea;
    std::getline(leer, linea); // Limpiar buffer inicial
    while (std::getline(leer, linea)) {
        if (linea.empty()) continue;
        std::stringstream ss(linea);
        std::string id;
        std::getline(ss, id, ',');
        Producto * p = nullptr;
        if (id[0] == 'T') 
            p = new Torta();
        
        if(p){
            p->setId(id);
            p->cargarDesdeStream(ss);
            productos[id]=p;
        }
    }
    leer.close();
}

void Inventario::guardarProductos(){
    std::ofstream guardar;
    guardar.open("Productos.txt",std::ios::out);
    if(!guardar){
        std::cout<<"No se pudo abrir el archivo para guardar"<<std::endl;
        return;
    }
    guardar<<contadores.size()<<std::endl; 
    for(auto &c : contadores){
        guardar<<c.first<<" "<<c.second<<std::endl; 
    }
    for(auto &p : productos){ 
        guardar<<p.second->ssdatos()<<std::endl;
    }
    guardar.close();
}

void Inventario::mostrarBajoMinimo(){
    for(auto &x : productos){
        if(x.second->estaBajoMinimo())
            x.second->mostrarDatos();
    }
}