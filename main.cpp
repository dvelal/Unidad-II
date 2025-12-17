#include<iostream>
#include<vector>
#include"Producto.h"
#include"Receta.h"
#include"Torta.h"
int main(){
    Inventario inventario;
    Almacen almacen;
    inventario.cargarProductos();//leer los productos del inventario
    almacen.cargarBase();
    bool close = false;
    while(!close){
        std::cout<<"1. Venta\n"
                 <<"2. Administrar Inventario\n"
                 <<"3. Administrar Almacen\n"<<std::endl;    
                 char opt;
                 cin>>opt;
                 switch(opt){
                    case '1':{//ventas
                        //opciones

                        char opt1;
                        cin>>opt1;
                        switch(opt1){
                            case '1':
                            break;
                        }

                    }
                    break;

/////////////////////////////////////////////////////////////////////////////////////////                    
                    case '2':{//inventario
                        bool close2 = false;
                        do{
                        std::cout<<"Escoge una opción: "<<std::endl;
                        std::cout<<"1. Agregar Producto\n";
                        std::cout<<"2. Mostrar productos\n";
                        std::cout<<"3. Producir\n";
                        std::cout<<"4. Mostrar productos bajo minimo\n";
                        std::cout<<"0. Volver"<<std::endl;
                        char opt2;
                        cin>>opt2;
                        switch(opt2){
                            //////////////////////Agregar producto
                            case '1':{
                                std::cout<<"/////////Agregar Producto/////////"<<std::endl;
                                std::cout<<"Que producto quiere ingresar?"<<std::endl;;
                                std::cout<<"a. Torta"<<std::endl;
                                //otros produtos...
                                char opt2_1;
                                cin>>opt2_1;
                                switch(opt2_1){
                                    case 'a':
                                        std::string nombre; 
                                        int sm,mp;
                                        float p;
                                        cout<<"Ingrese el nombre del producto:\n";
                                        cin.ignore();
                                        getline(cin,nombre);
                                        std::cout<<"Ingrese el Stock Minimo: "; std::cin>>sm;
                                        std::cout<<"Ingrese el tamaño de la torta en porciones: "; std::cin>>mp;
                                        std::cout<<"Ingrese el precio de la torta: ";std::cin>>p;
                                        Producto *pT = inventario.agregarProducto(new Torta(nombre,0,sm,mp,p));
                                        cout<<"Se creo el producto exitosamente :"<<endl;
                                        pT->mostrarDatos();
                                    break;
                                }
                                break;
                            }    
                            case '2':{//////////7mostrar productos
                                std::cout<<"/////////////////////////  Lista de Productos  /////////////////////////"<<std::endl;
                                inventario.mostrarProductos();
                                
                            break;
                            }
                            case '3':{//////////Producir
                                std::cout<<"/////////////////////////  Producir  /////////////////////////"<<std::endl;
                                std::string id;
                                std::cout<<"Ingresa id del producto a producir: \n";
                                cin>>id;

                                Producto *p = inventario.buscarPorId(id);
                                if(!p){
                                    std::cout<<"El producto no existe";
                                    break;
                                }
                                p->mostrarDatos();
                                int cant;
                                std::cout<<"Cuanta[s] "<<p->getNombre()<<" va a producir?"<<std::endl;
                                cin>>cant;
                                inventario.producir(id,cant,almacen);
                                std::cout<<"Se agregaron correctamente: "<<cant<<" "<<p->getNombre()<<std::endl;
                                p->mostrarDatos();
                            break;
                            }
                            case '4':{//////mostrar producto bajo minimo

                                //inventario.actualizarStock();
                                
                                
                                break;
                            }
                            case '0':{/////salir de ventas
                                close2 = true;
                                break;
                            }
                        }

                        }while(!close2);
                    }
                    break;
//////////////////////////////////////////////////////////////////////////////Almacen de insumos
                    case '3':{//administrar insumos
                        bool close3 = false;
                        do{
                            //opciones


                            char opt3;
                            cin>>opt3;
                            switch(opt3){
                                case '1':{////////comentario de case 1

                                }
                                break;
                                case '2':{/////////////comentario de case 2
                                }
                                break;
                            }

                        }while(!close3);
                    }
                 }
        
    }//close

    inventario.guardarProductos();
    almacen.guardarBase();
    
    return 0;
}