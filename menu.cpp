#include <iostream>
#include <string>

using namespace std;

void menu(){
// Definición de colores ANSI
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define B_BLUE  "\033[44m"
    // Limpiar pantalla
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    // Encabezado principal
    cout << CYAN << "  .------------------------------------------------------------------------------------------." << endl;
    cout << " /  " << "                            SISTEMA GESTOR: PASTELERIA CENTRAL                            " << RESET << CYAN << "\\" << endl;
    cout << " |--------------------------------------------------------------------------------------------|" << endl;

    // FILA 1: VENTAS E INVENTARIO
    cout << " | " << YELLOW << BOLD << "      [ 1 ] SECCION DE VENTAS              " << RESET << CYAN << "||" << GREEN << BOLD << "      [ 2 ] INVENTARIO (VITRINA)            " << RESET << CYAN << "  |" << endl;
    cout << " | " << YELLOW << "                (i)  (i)  (i)              " << RESET << CYAN << "||" << GREEN << "          _________________________          " << RESET << CYAN << " |" << endl;
    cout << " | " << YELLOW << "                 |    |    |               " << RESET << CYAN << "||" << GREEN << "         |_________________________|         " << RESET << CYAN << " |" << endl;
    cout << " | " << YELLOW << "                _|____|____|_              " << RESET << CYAN << "||" << GREEN << "         |  " << WHITE << "______" << GREEN << "   " << WHITE << "______" << GREEN << "   " << WHITE << "____" << GREEN << " |        " << RESET << CYAN << "  |" << endl;
    cout << " | " << YELLOW << "               | ^^^^^^^^^^^ |             " << RESET << CYAN << "||" << GREEN << "         | " << WHITE << "|      | |      | |    |" << GREEN << "|         " << RESET << CYAN << " |" << endl;
    cout << " | " << YELLOW << "             __|_____________|__           " << RESET << CYAN << "||" << GREEN << "         | " << WHITE << "| (O)  | | (&)  | | [] |" << GREEN << "|         " << RESET << CYAN << " |" << endl;
    cout << " | " << YELLOW << "            |:::::::::::::::::::|          " << RESET << CYAN << "||" << GREEN << "         | " << WHITE << "|______| |______| |____|" << GREEN << "|         " << RESET << CYAN << " |" << endl;
    cout << " | " << YELLOW << "            |  " << BOLD << "   O F E R T A   " << RESET << YELLOW << "|          " << RESET << CYAN << "||" << GREEN << "         |  " << WHITE << "______" << GREEN << "   " << WHITE << "______" << GREEN << "   " << WHITE << "____" << GREEN << " |         " << RESET << CYAN << " |" << endl;
    cout << " | " << YELLOW << "            |___________________|          " << RESET << CYAN << "||" << GREEN << "         | " << WHITE << "|______| |______| |____|" << GREEN << "|         " << RESET << CYAN << " |" << endl;
    cout << " | " << YELLOW << "           (_____________________)         " << RESET << CYAN << "||" << GREEN << "         |_________________________|         " << RESET << CYAN << " |" << endl;
    
    cout << " |--------------------------------------------||----------------------------------------------|" << endl;

    // FILA 2: ALMACEN Y SALIDA
    cout << " | " << MAGENTA << BOLD << "      [ 3 ] ALMACEN DE INSUMOS             " << RESET << CYAN << "||" << RED << BOLD << "      [ 4 ] SALIR DEL SISTEMA               " << RESET << CYAN << "  |" << endl;
    cout << " | " << MAGENTA << "              __________                   " << RESET << CYAN << "||" << RED << "                ________________            " << RESET << CYAN << "  |" << endl;
    cout << " | " << MAGENTA << "             /         /|                  " << RESET << CYAN << "||" << RED << "               |  ____________  |           " << RESET << CYAN << "  |" << endl;
    cout << " | " << MAGENTA << "            /________ / |  " << WHITE << "__________" << MAGENTA << "     " << RESET << CYAN << " ||" << RED << "               | |            | |           " << RESET << CYAN << "  |" << endl;
    cout << " | " << MAGENTA << "           |   " << WHITE << "____" << MAGENTA << "   | | " << WHITE << "/         /|" << MAGENTA << "     " << RESET << CYAN << "||" << RED << "               | |    " << BOLD << "EXIT" << RESET << RED << "    | |           " << RESET << CYAN << "  |" << endl;
    cout << " | " << MAGENTA << "           |  " << WHITE << "|HAR |" << MAGENTA << "  | |" << WHITE << "/________ / |" << MAGENTA << "     " << RESET << CYAN << "||" << RED << "               | |    ____    | |           " << RESET << CYAN << "  |" << endl;
    cout << " | " << MAGENTA << "           |  " << WHITE << "|____|" << MAGENTA << "  | |   " << WHITE << "____" << MAGENTA << "   | |" << MAGENTA << "     " << RESET << CYAN << "||" << RED << "               | |   |    |   | |           " << RESET << CYAN << "  |" << endl;
    cout << " | " << MAGENTA << "           |__________|/" << WHITE << "|  |AZUC|  | |" << MAGENTA << "     " << RESET << CYAN << "||" << RED << "               | |   |   o|   | |           " << RESET << CYAN << "  |" << endl;
    cout << " | " << MAGENTA << "                        |  " << WHITE << "|____|" << MAGENTA << "  | /" << MAGENTA << "     " << RESET << CYAN << "||" << RED << "               | |___|____|___| |           " << RESET << CYAN << "  |" << endl;
    cout << " | " << MAGENTA << "                        |__________|/"       << RESET << CYAN << "      ||" << RED << "               |________________|           " << RESET << CYAN << "  |" << endl;
    
    cout << "  \\___________________________________________________________________________________________/" << RESET << endl;
    
    cout << "\n   " << BOLD << WHITE << ">>> SELECCIONE UNA RUTA: " << RESET;
}

int main(){
    menu();
    return 0;
}
    /*int opcion;
    cin >> opcion;

    // Respuesta visual
    cout << "\n";
    switch(opcion) {
        case 1: cout << YELLOW << " [!] Cargando catalogo de productos..." << RESET << endl; break;
        case 2: cout << GREEN << " [!] Verificando stock en vitrina..." << RESET << endl; break;
        case 3: cout << MAGENTA << " [!] Abriendo inventario de materia prima..." << RESET << endl; break;
        case 4: cout << RED << " [!] Finalizando jornada. Guardando datos..." << RESET << endl; break;
        default: cout << WHITE << B_BLUE << " [?] Opcion desconocida. " << RESET << endl;
    }
    cout << endl;

    return 0;
}*/