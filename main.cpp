#include<iostream>
#include<vector>
#include"Producto.h"
#include"Receta.h"
#include"Torta.h"
int main(){
    Inventario inventario;
    //inventario.cargarProductos();//leer los productos del inventario
    bool close = false;
    do{
        std::cout<<"Escoge una opción: "<<std::endl;
        std::cout<<"1. Agregar Producto\n";
        std::cout<<"2. Actualizar stock\n";
        std::cout<<"3.... \n";//...
        std::cout<<"0. Salir"<<std::endl;
        char opt;
        cin>>opt;
        switch(opt){
            case '1':
                std::cout<<"Que producto quiere ingresar?"<<std::endl;;
                std::cout<<"a. Torta"<<std::endl;
                char opt2;
                cin>>opt2;
                switch(opt2){
                    case 'a':
                        Torta tortaDeChocolate;
                        inventario.agregarProducto(&tortaDeChocolate);
                    break;
                }
                break;
            case '2':
                //inventario.actualizarStock();
            
                
            break;
            case '0':
                close = true;
                break;
        }

    }while(!close);
    
    return 0;
}