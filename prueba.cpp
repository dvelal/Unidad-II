#include<iostream>
#include<vector>
#include"Producto.h"
#include"Receta.h"
#include"Torta.h"

using namespace std;
int main(){
    Inventario inventario;
    cout<<"Agrega el producto"<<endl;//por la prueba ya sabes que es torta
    string nombre; 
    int sa,sm,mp;
    float p;
    getline(cin,nombre);
    cin>>sa>>sm>>mp>>p;
    inventario.agregarProducto(new Torta(nombre,sa,sm,mp,p));  
    inventario.mostrarProductos();
    string id;
    cin>>id;
    int cant;
    cin>>cant;
    inventario.actualizarStock(id,cant);
    inventario.mostrarProductos();



    return 0;
}