#include <iostream>   
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cctype>
#include <fstream>

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLD    "\033[1m"

struct Contacto {
    string nombre;
    string telefono; 
};

static bool esSoloDigitos(const string& s) {
    if (s.empty()) return false;
    for (unsigned char ch : s) if (ch < '0' || ch > '9') return false;
    return true;
}

static string solicitarTelefono8() {
    while (true) {
        cout << CYAN << " Ingresa telefono (exactamente 8 digitos): " << RESET;
        string t; getline(cin, t);

        size_t l = t.find_first_not_of(" \t\r\n");
        size_t r = t.find_last_not_of(" \t\r\n");
        if (l == string::npos) t.clear();
        else t = t.substr(l, r - l + 1);

        if (!esSoloDigitos(t)) {
            cout << RED << " Error: Solo digitos 0-9.\n" << RESET;
            continue;
        }
        if (t.size() != 8) {
            cout << RED << " Error: Deben ser exactamente 8 digitos.\n" << RESET;
            continue;
        }
        return t;
    }
}

static void agregarContacto(vector<Contacto>& agenda) {
    Contacto c;
    cout << YELLOW << " Nombre: " << RESET;
    getline(cin, c.nombre);
    c.telefono = solicitarTelefono8();
    agenda.push_back(c);
    cout << GREEN << " Contacto agregado correctamente.\n" << RESET;
}

static void mostrarContactos(const vector<Contacto>& agenda) {
    if (agenda.empty()) {
        cout << RED << " No hay contactos registrados.\n" << RESET;
        return;
    }

    cout << BOLD << BLUE << "\n LISTA DE CONTACTOS\n" << RESET;
    for (size_t i = 0; i < agenda.size(); ++i)
        cout << YELLOW << (i + 1) << ") " << RESET
        << BOLD << agenda[i].nombre << RESET
        << " - " << CYAN << agenda[i].telefono << RESET << "\n";
}

static string toLowerCopy(string s) {
    for (char& c : s) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    return s;
}

static void buscarContacto(const vector<Contacto>& agenda) {
    if (agenda.empty()) {
        cout << RED << " No hay contactos registrados.\n" << RESET;
        return;
    }

    cout << MAGENTA << " Buscar nombre: " << RESET;
    string q; getline(cin, q); q = toLowerCopy(q);
    bool ok = false;

    cout << BLUE << "\n Resultados:\n" << RESET;
    for (size_t i = 0; i < agenda.size(); ++i) {
        if (toLowerCopy(agenda[i].nombre).find(q) != string::npos) {
            cout << GREEN << (i + 1) << ") " << RESET
                << BOLD << agenda[i].nombre << RESET
                << " - " << CYAN << agenda[i].telefono << RESET << "\n";
            ok = true;
        }
    }
    if (!ok) cout << RED << " Sin coincidencias.\n" << RESET;
}

int main() {
    vector<Contacto> agenda;
    while (true) {
        cout << BOLD << "\n " << BLUE << " AGENDA TELEFONICA" << RESET << BOLD << " \n" << RESET
            << YELLOW << "1)" << RESET << " Agregar contacto\n"
            << YELLOW << "2)" << RESET << " Mostrar contactos\n"
            << YELLOW << "3)" << RESET << " Buscar contacto\n"
            << YELLOW << "0)" << RESET << " Salir\n"
            << CYAN << " Opcion: " << RESET;

        int op;
        if (!(cin >> op)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "  Opción inválida. Intenta de nuevo.\n" << RESET;
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (op == 1) agregarContacto(agenda);
        else if (op == 2) mostrarContactos(agenda);
        else if (op == 3) buscarContacto(agenda);
        else if (op == 0) {
            cout << GREEN << " ¡Hasta luego!\n" << RESET;
            break;
        }
        else cout << RED << "  Opción inválida.\n" << RESET;
    }
    return 0;
}
