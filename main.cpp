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
        std::cout<<"2. Mostrar productos\n";
        std::cout<<"3. Reponer stock\n";
        std::cout<<"4. Mostrar productos bajo minimo\n";
        std::cout<<"0. Volver"<<std::endl;
        char opt;
        cin>>opt;
        switch(opt){
            case '1':{
                std::cout<<"/////////Agregar Producto/////////"<<std::endl;
                std::cout<<"Que producto quiere ingresar?"<<std::endl;;
                std::cout<<"a. Torta"<<std::endl;
                //otros produtos...
                char opt2;
                cin>>opt2;
                switch(opt2){
                    case 'a':
                        Torta tortaDeChocolate;
                        inventario.agregarProducto(&tortaDeChocolate);
                    break;
                }
                break;
            }    
            case '2':{
                std::cout<<"/////////////////////////  Lista de Productos  /////////////////////////"<<std::endl;
                inventario.mostrarProductos();
                
            break;
            }
            case '3':{
                std::cout<<"/////////////////////////  Reponer stock  /////////////////////////"<<std::endl;
                std::string id;
                std::cout<<"Ingresa id del producto: \n";
                cin>>id;

                Producto *p = inventario.buscarPorId(id);
                if(!p){
                    "El producto no existe";
                    break;
                }
                p->mostrarDatos();
                int cant;
                std::cout<<"Cuanta[s] "<<p->getNombre()<<" va a ingresar?"<<std::endl;
                cin>>cant;
                inventario.actualizarStock(id,cant);
                std::cout<<"Se agregaron correctamente: "<<cant<<" "<<p->getNombre()<<std::endl;
                p->mostrarDatos();
            break;
            }
            case '4':{

                //inventario.actualizarStock();
                
                
                break;
            }
            case '0':
                close = true;
                break;
        }

    }while(!close);
    
    return 0;
}