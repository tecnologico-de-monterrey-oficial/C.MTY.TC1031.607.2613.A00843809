#ifndef Log_h
#define Log_h

#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <iomanip>

using namespace std;

struct Log {
    string monthStr;
    int monthNum;
    int day;
    int year;
    string timeStr;
    int hour;
    int minute;
    int second;
    string ip;
    string event;
    long long timestampKey; // AAAA MM DD HH MM SS como entero para comparar en O(1)
    int dayKey;             // AAAA MM DD como entero para buscar por día

    Log() : monthStr(""), monthNum(0), day(0), year(0), timeStr(""),
            hour(0), minute(0), second(0), ip(""), event(""),
            timestampKey(0), dayKey(0) {}

    // Convierte el nombre del mes a su número correspondiente (1 a 12)
    static int monthToNumber(const string& m) {
        if (m == "Jan") return 1;
        if (m == "Feb") return 2;
        if (m == "Mar") return 3;
        if (m == "Apr") return 4;
        if (m == "May") return 5;
        if (m == "Jun") return 6;
        if (m == "Jul") return 7;
        if (m == "Aug") return 8;
        if (m == "Sep") return 9;
        if (m == "Oct") return 10;
        if (m == "Nov") return 11;
        if (m == "Dec") return 12;
        return 0;
    }

    // Revisa si un string contiene únicamente dígitos
    static bool isDigitsOnly(const string& s) {
        if (s.empty()) return false;
        for (size_t i = 0; i < s.length(); i++) {
            if (s[i] < '0' || s[i] > '9') return false;
        }
        return true;
    }

    // Valida si una fecha (mes, día, año) existe en el calendario
    static bool isValidDate(int m, int d, int y) {
        if (y < 1970 || y > 2100) return false;
        if (m < 1 || m > 12) return false;
        int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        bool leap = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
        if (leap) daysInMonth[2] = 29;
        return d >= 1 && d <= daysInMonth[m];
    }

    // Valida el formato de una dirección IPv4 (X.X.X.X con valores 0-255)
    static bool isValidIP(const string& ipStr) {
        stringstream ss(ipStr);
        string segment;
        int count = 0;
        while (getline(ss, segment, '.')) {
            if (!isDigitsOnly(segment) || segment.length() > 3) return false;
            int val = stoi(segment);
            if (val < 0 || val > 255) return false;
            count++;
        }
        // Revisar que no termine en punto y que tenga exactamente 4 octetos
        if (ipStr.empty() || ipStr.back() == '.') return false;
        return count == 4;
    }

    // Valida y parsea una cadena de día con formato "Mmm DD AAAA" (ej. "Sep 14 2024")
    static bool parseDayQuery(const string& input, int& outDayKey, string& normalizedDate) {
        stringstream ss(input);
        string mStr, dStr, yStr, extra;
        if (!(ss >> mStr >> dStr >> yStr) || (ss >> extra)) {
            return false;
        }
        int m = monthToNumber(mStr);
        if (m == 0 || !isDigitsOnly(dStr) || !isDigitsOnly(yStr) || yStr.length() != 4) {
            return false;
        }
        int d = stoi(dStr);
        int y = stoi(yStr);
        if (!isValidDate(m, d, y)) {
            return false;
        }
        outDayKey = y * 10000 + m * 100 + d;
        ostringstream oss;
        oss << mStr << " " << setw(2) << setfill('0') << d << " " << y;
        normalizedDate = oss.str();
        return true;
    }

    // Constructor que valida y convierte una línea del archivo de log
    static Log parseLine(const string& line) {
        if (line.empty()) {
            throw invalid_argument("Línea vacía");
        }

        stringstream ss(line);
        string mStr, dStr, yStr, tStr, ipStr;
        if (!(ss >> mStr >> dStr >> yStr >> tStr >> ipStr)) {
            throw invalid_argument("Faltan campos obligatorios en el registro");
        }

        int m = monthToNumber(mStr);
        if (m == 0) {
            throw invalid_argument("Mes inválido (" + mStr + ")");
        }

        if (!isDigitsOnly(dStr) || !isDigitsOnly(yStr) || yStr.length() != 4) {
            throw invalid_argument("Formato de día o año no numérico");
        }
        int d = stoi(dStr);
        int y = stoi(yStr);
        if (!isValidDate(m, d, y)) {
            throw invalid_argument("Fecha fuera de rango (" + mStr + " " + dStr + " " + yStr + ")");
        }

        // Validar hora HH:MM:SS
        if (tStr.length() != 8 || tStr[2] != ':' || tStr[5] != ':') {
            throw invalid_argument("Formato de hora inválido (" + tStr + ")");
        }
        string hhStr = tStr.substr(0, 2);
        string mmStr = tStr.substr(3, 2);
        string ssStr = tStr.substr(6, 2);
        if (!isDigitsOnly(hhStr) || !isDigitsOnly(mmStr) || !isDigitsOnly(ssStr)) {
            throw invalid_argument("La hora contiene caracteres no numéricos");
        }
        int hh = stoi(hhStr);
        int mm = stoi(mmStr);
        int sec = stoi(ssStr);
        if (hh < 0 || hh > 23 || mm < 0 || mm > 59 || sec < 0 || sec > 59) {
            throw invalid_argument("Valores de hora fuera de rango (" + tStr + ")");
        }

        // Validar IP
        if (!isValidIP(ipStr)) {
            throw invalid_argument("Dirección IP inválida (" + ipStr + ")");
        }

        // Obtener descripción del evento
        string evt;
        getline(ss, evt);
        // Quitar espacio inicial y posible '\r' al final
        if (!evt.empty() && evt[0] == ' ') {
            evt = evt.substr(1);
        }
        if (!evt.empty() && evt.back() == '\r') {
            evt.pop_back();
        }
        if (evt.empty()) {
            throw invalid_argument("Descripción del evento vacía");
        }

        Log log;
        log.monthStr = mStr;
        log.monthNum = m;
        log.day = d;
        log.year = y;
        log.timeStr = tStr;
        log.hour = hh;
        log.minute = mm;
        log.second = sec;
        log.ip = ipStr;
        log.event = evt;
        log.dayKey = y * 10000 + m * 100 + d;
        log.timestampKey = (long long)log.dayKey * 1000000LL + hh * 10000LL + mm * 100LL + sec;
        return log;
    }

    string getDateString() const {
        ostringstream oss;
        oss << monthStr << " " << setw(2) << setfill('0') << day << " " << year;
        return oss.str();
    }

    string toString() const {
        ostringstream oss;
        oss << monthStr << " " << setw(2) << setfill('0') << day << " " << year
            << " " << timeStr << " " << ip << " " << event;
        return oss.str();
    }

    // Operadores de comparación por fecha y hora
    bool operator<(const Log& other) const {
        return this->timestampKey < other.timestampKey;
    }
    bool operator>(const Log& other) const {
        return this->timestampKey > other.timestampKey;
    }
    bool operator<=(const Log& other) const {
        return this->timestampKey <= other.timestampKey;
    }
    bool operator>=(const Log& other) const {
        return this->timestampKey >= other.timestampKey;
    }
    bool operator==(const Log& other) const {
        return this->timestampKey == other.timestampKey &&
               this->ip == other.ip &&
               this->event == other.event;
    }
};

inline ostream& operator<<(ostream& os, const Log& log) {
    os << log.toString();
    return os;
}

#endif