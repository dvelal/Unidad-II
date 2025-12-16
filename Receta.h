#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct ItemReceta {
    string nombreInsumo;
    float cantidadUtil;
};

class Insumo {
    private:
        string nombre;
        float stock;
    public:
        Insumo(const string& nombre, float stockInicio);
        string getNombre() const;
        float getStock() const;
        bool consumir(float cantidad);
        void reponer(float cantidad);
};

Insumo :: Insumo (const string& nombre, float stockInicio) : nombre(nombre){
    stock = stockInicio;
}

string Insumo :: getNombre() const {
    return nombre;
}

float Insumo :: getStock() const {
    return stock;
}

bool Insumo :: consumir(float cantidad){
    if(stock < cantidad){
        return false;
    } else {
        stock = stock - cantidad;
        return true;
    }
}

void Insumo :: reponer (float cantidad){
    stock = stock + cantidad;
}

class Almacen {
    private:
        vector<Insumo> insumos;
    public:
        void cargarBase();
        void guardarBase();
        void mostrarInsumos();
        bool hayStock(const string& nombreInsumo, float cantidad) const;
        bool descontar(const string& nombreInsumo, float cantidad);
};

void Almacen :: cargarBase(){
    ifstream Insumos;
    Insumos.open("Insumos.txt");
    if(Insumos.is_open()){
        string nom;
        float stocks;
        while(Insumos >> nom >> stocks){
            insumos.push_back(Insumo(nom, stocks));
        }
        Insumos.close();
    } else {
        cout << "No se puedo abrir el archivo de insumos\n";
    }
}

void Almacen::guardarBase() {
    ofstream archivo("Insumos.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo guardar el archivo de insumos\n";
        return;
    }
    for (const Insumo& insumo : insumos) {
        archivo << insumo.getNombre() << " " << insumo.getStock() << endl;
    }
    archivo.close();
}

void Almacen :: mostrarInsumos() {
    cout << "Lista de Insumos: \n";
    for(const Insumo& insumo : insumos){
        cout << "\t" << insumo.getNombre() << " " << insumo.getStock() << endl;
    }
}

bool Almacen :: hayStock(const string& nombreInsumo, float cantidad) const {
    for (const Insumo& insumo : insumos){
        if(insumo.getNombre() == nombreInsumo){
            if (insumo.getStock() >= cantidad){
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

bool Almacen :: descontar(const string& nombreInsumo, float cantidad){
    for(Insumo& insumo : insumos){
        if (insumo.getNombre() == nombreInsumo){
            return insumo.consumir(cantidad);
        }
    }
    return false;
}

class Receta {
    private:
        string nombreProducto;
        vector<ItemReceta> items;
    public:
        Receta(const string& nombreProducto);
        bool cargarDefinicion(const string& archivoReceta);
        bool producir(Almacen& almacen);
};

Receta :: Receta(const string& nombreProducto) : nombreProducto(nombreProducto) {}

bool Receta :: cargarDefinicion(const string& archivoReceta){
    string ruta = "RECETAS/" + archivoReceta;
    ifstream receta(ruta);
    if(receta.is_open()){
        items.clear();
        ItemReceta item;
        while (receta >> item.nombreInsumo >> item.cantidadUtil){
            items.push_back(item);
        }
        receta.close();
        return true;
    } else {
        return false;
    }
}

bool Receta :: producir(Almacen& almacen){
    for(const ItemReceta& item : items){
        if(!almacen.hayStock(item.nombreInsumo, item.cantidadUtil)){
            cout << "Falta insumo: " << item.nombreInsumo << endl;
            return false;
        }
    }
    for(const ItemReceta& item : items){
        almacen.descontar(item.nombreInsumo, item.cantidadUtil);
    }
    return true;
}

