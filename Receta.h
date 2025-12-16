#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

struct ItemReceta {
    string nombreInsumo;
    float cantidadUtil;
    string unidad;
};

class Insumo {
    private:
        string nombre;
        float stock;
        string unidad;
    public:
        Insumo(const string& nombre, float stockInicio, const string& unidad);
        string getNombre() const;
        float getStock() const;
        string getUnidad() const;
        bool consumir(float cantidad);
        void reponer(float cantidad);
};

Insumo :: Insumo (const string& nombre, float stockInicio, const string& unidad) : nombre(nombre), stock(stockInicio), unidad(unidad) {}

string Insumo :: getNombre() const {
    return nombre;
}

float Insumo :: getStock() const {
    return stock;
}

string Insumo :: getUnidad() const {
    return unidad;
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
        void reponerInsumos(const string& nombreInsumo, float cantidad);
        bool hayStock(const string& nombreInsumo, float cantidad) const;
        bool descontar(const string& nombreInsumo, float cantidad);
};

void Almacen :: cargarBase(){
    ifstream Insumos;
    Insumos.open("Insumos.txt");
    if(Insumos.is_open()){
        string nom;
        float stocks;
        string unidad;
        while(Insumos >> nom >> stocks >> unidad){
            insumos.push_back(Insumo(nom, stocks, unidad));
        }
        Insumos.close();
    } else {
        cout << "No se puedo abrir el archivo de insumos\n";
    }
}

void Almacen :: guardarBase() {
    ofstream archivo("Insumos.txt");
    if (!archivo.is_open()) {
        cout << "No se pudo guardar el archivo de insumos\n";
        return;
    }
    for (const Insumo& insumo : insumos) {
        archivo << insumo.getNombre() << " " << insumo.getStock() << " " << insumo.getUnidad() << endl;
    }
    archivo.close();
}

void Almacen :: mostrarInsumos() {
    cout << "Lista de Insumos: \n";
    for(const Insumo& insumo : insumos){
        cout << "\t" << insumo.getNombre() << " " << insumo.getStock() << " " << insumo.getUnidad() << endl;
    }
}

void Almacen :: reponerInsumos(const string& nombreInsumo, float cantidad){
    for(Insumo& insumo : insumos){
        if (insumo.getNombre() == nombreInsumo){
            insumo.reponer(cantidad);
        }
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
        bool cargarDefinicion();
        bool producir(Almacen& almacen);
        void agregarInsumo(string nombreInsumo, float cantidadUtil, string unidad);
        void crearReceta();
};

Receta :: Receta(const string& nombreProducto) : nombreProducto(nombreProducto) {}

bool Receta :: cargarDefinicion(){
    string ruta = "RECETAS/" + nombreProducto + ".txt";
    ifstream receta(ruta);
    if(receta.is_open()){
        items.clear();
        ItemReceta item;
        while (receta >> item.nombreInsumo >> item.cantidadUtil >> item.unidad){
            items.push_back(item);
        }
        receta.close();
        return true;
    } else {
        return false;
    }
}

bool Receta :: producir(Almacen& almacen){
    bool faltantes = false;
    for(const ItemReceta& item : items){
        if(!almacen.hayStock(item.nombreInsumo, item.cantidadUtil)){
            cout << "Falta insumo: " << item.nombreInsumo << endl;
            faltantes = true;
        }
    }
    if(faltantes){
        return false;
    }
    for(const ItemReceta& item : items){
        almacen.descontar(item.nombreInsumo, item.cantidadUtil);
    }
    return true;
}

void Receta :: agregarInsumo(string nombreInsumo, float cantidadUtil, string unidad){
    ItemReceta item;
    item.nombreInsumo = nombreInsumo;
    item.cantidadUtil = cantidadUtil;
    item.unidad = unidad;
    items.push_back(item);
}

void Receta :: crearReceta(){
    string ruta = "RECETAS/" + nombreProducto + ".txt";
    ofstream RecetProduc(ruta);
    if(RecetProduc.is_open()){
        for(ItemReceta& item : items){
            RecetProduc << item.nombreInsumo << " " << item.cantidadUtil << " " << item.unidad << endl;
        }
        RecetProduc.close();
    } else {
        cout << "No se pudo crear Receta\n";
    } 
}

