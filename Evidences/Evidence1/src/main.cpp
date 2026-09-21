#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

class Registro {
private:
    string mes; int dia; int anio; string hora; string ip; string razon; string lineaCompleta;
    long long fechaValor;

    int mesANumero(const string& m) const {
        if (m == "Jan") return 1; if (m == "Feb") return 2; if (m == "Mar") return 3;
        if (m == "Apr") return 4; if (m == "May") return 5; if (m == "Jun") return 6;
        if (m == "Jul") return 7; if (m == "Aug") return 8; if (m == "Sep") return 9;
        if (m == "Oct") return 10; if (m == "Nov") return 11; if (m == "Dec") return 12;
        return 0;
    }

    void calcularFechaValor() {
        int m = mesANumero(mes);
        int h = 0, min = 0, s = 0; char sep;
        stringstream ss(hora);
        ss >> h >> sep >> min >> sep >> s;
        fechaValor = (long long)anio * 10000000000LL + (long long)m * 100000000LL + (long long)dia * 1000000LL + h * 10000 + min * 100 + s;
    }

public:
    Registro() { dia = 0; anio = 0; fechaValor = 0; }
    Registro(const string& linea) {
        lineaCompleta = linea;
        stringstream ss(linea);
        ss >> mes >> dia >> anio >> hora >> ip;
        getline(ss, razon);
        if (!razon.empty() && razon[0] == ' ') razon = razon.substr(1);
        calcularFechaValor();
    }
    Registro(string m, int d, int a, string h) {
        mes = m; dia = d; anio = a; hora = h;
        calcularFechaValor();
    }
    long long getFechaValor() const { return fechaValor; }
    string getLineaCompleta() const { return lineaCompleta; }

    bool operator<(const Registro& otro) const { return this->fechaValor < otro.fechaValor; }
    bool operator>(const Registro& otro) const { return this->fechaValor > otro.fechaValor; }
    bool operator<=(const Registro& otro) const { return this->fechaValor <= otro.fechaValor; }
    bool operator>=(const Registro& otro) const { return this->fechaValor >= otro.fechaValor; }
};

int main() {
    ifstream archivo("../data/log607-1.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return 1;
    }
    vector<Registro> listaLogs;
    string linea;
    while (getline(archivo, linea)) {
        if (!linea.empty()) listaLogs.push_back(Registro(linea));
    }
    archivo.close();
    cout << "Parsing exitoso. Total de registros: " << listaLogs.size() << endl;
    return 0;
}