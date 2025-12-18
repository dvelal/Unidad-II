#include <iostream>
#include <string>
#include <limits>
#include "Receta.h"
#include "Producto.h" 
#include "Venta.h"

using namespace std;

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar() {
    cout << "\n[SISTEMA] Presione Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void mostrarCabecera(string titulo) {
    limpiarPantalla();
    cout << "========================================" << endl;
    cout << "   " << titulo << endl;
    cout << "========================================" << endl;
}

int main() {
    Almacen miAlmacen;
    Inventario miInventario;
    miAlmacen.cargarBase();
    miInventario.cargarProductos();

    int opcion;
    do {
        mostrarCabecera("SISTEMA DE GESTION: PASTELERIA");
        cout << " 1. Almacen (Ver/Reponer Insumos)" << endl;
        cout << " 2. Catalogo (Inventario de Tortas)" << endl;
        cout << " 3. Produccion (Hornear Tortas)" << endl;
        cout << " 4. Registro (Crear Nueva Receta/Producto)" << endl;
        cout << " 5. Punto de Venta (Boletas)" << endl;
        cout << " 6. Consultar Boletas Guardadas" << endl;
        cout << " 0. Salir y Guardar" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                mostrarCabecera("MODULO DE ALMACEN");
                miAlmacen.mostrarInsumos();
                cout << "\n[1] Reponer/Agregar Insumo | [0] Volver: ";
                int op1; cin >> op1;
                if(op1 == 1) {
                    string nom; float cant; string uni;
                    cout << "Nombre del insumo: "; cin >> nom;
                    cout << "Cantidad a sumar: "; cin >> cant;
                    cout << "Unidad de medida: "; cin >> uni;
                    miAlmacen.reponerInsumos(nom, cant, uni);
                    cout << "\n[OK] Stock de " << nom << " actualizado." << endl;
                    pausar();
                }
                break;
            }

            case 2: {
                mostrarCabecera("CATALOGO DE PRODUCTOS");
                miInventario.mostrarProductos();
                cout << "\n--- ALERTAS DE STOCK BAJO ---" << endl;
                miInventario.mostrarBajoMinimo();
                pausar();
                break;
            }

            case 3: {
                mostrarCabecera("MODULO DE PRODUCCION");
                miInventario.mostrarProductos();
                string id; int cant;
                cout << "\nIngrese ID del producto a hornear: "; cin >> id;
                Producto *p = miInventario.buscarPorId(id);
                if(!p){
                    cout<<"No existe el ID. Cree el producto antes"<<endl;
                    pausar();
                    continue;
                }
                cout << "Cantidad de unidades: "; cin >> cant;
                
                int fabricados = miInventario.producir(id, cant, miAlmacen);
                
                if (fabricados == cant) {
                    cout << "\n[EXITO] Se fabricaron " << fabricados << " unidades correctamente." << endl;
                } else if (fabricados > 0) {
                    cout << "\n[ADVERTENCIA] Solo se pudieron fabricar " << fabricados << " unidades por falta de insumos." << endl;
                } else {
                    cout << "\n[ERROR] No se pudo producir nada. Revise el stock de insumos." << endl;
                }
                pausar();
                break;
            }

            case 4: { 
                mostrarCabecera("REGISTRO DE NUEVA TORTA");
                string nombreT; float precioT; int minT, porcT;
                
                cout << "Nombre de la nueva torta: "; cin.ignore(); getline(cin, nombreT);
                cout << "Precio de venta: "; cin >> precioT;
                cout << "Stock minimo de seguridad: "; cin >> minT;
                cout << "Numero de porciones: "; cin >> porcT;

                Receta nuevaR(nombreT);
                char mas;
                do {
                    string ins; float cIns;
                    cout << "\n--- Agregar ingrediente a la receta ---" << endl;
                    cout << "Nombre del insumo (ej: Harina): "; cin >> ins;
                    cout << "Cantidad necesaria (ej: 0.5): "; cin >> cIns;
                    nuevaR.agregarInsumo(ins, cIns, "unid");
                    cout << "Agregar otro ingrediente? (s/n): "; cin >> mas;
                } while (mas == 's' || mas == 'S');

                nuevaR.crearReceta();

                Producto* nuevaTorta = new Torta(nombreT, 0, minT, porcT, precioT);
                miInventario.agregarProducto(nuevaTorta);

                cout << "\n[OK] Receta de '" << nombreT << "' creada y aniadida al catalogo con ID: " << nuevaTorta->getIdProducto() << endl;
                pausar();
                break;
            }

            case 5: {
                mostrarCabecera("PUNTO DE VENTA");

                string fecha, hora;
                cout << "Ingrese la fecha de hoy (dd/mm/aa): "; cin >> fecha;
                cout << "Ingrese la hora (hh:mm): "; cin >> hora;
                Venta nuevaVenta(fecha, hora); 
                string id; int cant; char mas;
                
                do {
                    miInventario.mostrarProductos();
                    cout << "\nIngrese ID del producto: "; cin >> id;
                    Producto* p = miInventario.buscarPorId(id);
                    if(p) {
                    cout << "Cantidad a vender: "; cin >> cant;
                        if(p->getStockActual()>= cant){
                            nuevaVenta.agregarItem(p, cant);
                            cout << "[+] Agregado. Otro producto? (s/n): "; cin >> mas;
                        }else {
                            cout<<"No hay stock suficiente. Reintentar? (s/n) "; cin>>mas;
                        }
                    } else {
                        cout << "[!] ID no existe. Reintentar? (s/n): "; cin >> mas;
                    }
                } while (mas == 's' || mas == 'S');

                limpiarPantalla();
                if(nuevaVenta.confirmarVenta()) {
                    cout << "========================================" << endl;
                    cout << "          VENTA CONFIRMADA             " << endl;
                    nuevaVenta.mostrarVenta();
                } else {
                    cout << "\n[DENEGADO] No hay suficiente stock de tortas para completar el pedido." << endl;
                }
                pausar();
                break;
            }

            case 6: {
                mostrarCabecera("HISTORIAL DE VENTAS");
                cout << "Ingrese el ID de la boleta: ";
                int op6; cin >> op6;
                Venta::buscarBoletaPorId(op6);
                pausar();
                break;
            }

            case 0:
                mostrarCabecera("SALIENDO DEL SISTEMA");
                cout << "[SISTEMA] Guardando bases de datos..." << endl;
                miAlmacen.guardarBase();
                miInventario.guardarProductos();
                cout << "[OK] Todo guardado. Vuelva pronto!" << endl;
                break;

            default:
                cout << "\n[!] Opcion no valida. Intente de nuevo." << endl;
                pausar();
        }
    } while (opcion != 0);

    return 0;
}