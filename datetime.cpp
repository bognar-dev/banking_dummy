#include <ostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "datetime.hpp"
using namespace std;

#define SEC_PER_DAY  (60 * 60 * 24)

// -------------------------------------------------------------------
ostream& operator<<(ostream& os, const DateTime& dt) {
    os << "(" << setw(2) << setfill('0') << dt._day << ".";
    os << setw(2) << setfill('0') << dt._month;
    os << "." << dt._year << " -- ";
    os << setw(2) << setfill('0') << dt._hour << ":";
    os << setw(2) << setfill('0') << dt._minute << ":";
    os << setw(2) << setfill('0') << dt._second << ")";

    return os;
}

// -------------------------------------------------------------------
DateTime::DateTime() {
    _time = time(0);
    _timeinfo = * localtime(&_time);

    _year = _timeinfo.tm_year + 1900;
    _month = _timeinfo.tm_mon + 1;
    _day = _timeinfo.tm_mday;

    _hour = _timeinfo.tm_hour;
    _minute = _timeinfo.tm_min;
    _second = _timeinfo.tm_sec;
}

// -------------------------------------------------------------------
DateTime::DateTime(int d, int m, int y, int hh, int mm, int sc) {
    _year = y;
    _month = m;
    _day = d;

    _hour = hh;
    _minute = mm;
    _second = sc;

    tm t;
    t.tm_year =_year - 1900;
    t.tm_mon = _month - 1;
    t.tm_mday = _day;

    t.tm_hour = _hour;
    t.tm_min = _minute;
    t.tm_sec = _second;

    _time = mktime(&t);
    _timeinfo = * localtime(&_time);
}

// -------------------------------------------------------------------
int DateTime::diff(DateTime dt) {
    return ::difftime(_time, dt._time) / SEC_PER_DAY;
}

// -------------------------------------------------------------------
string DateTime::toString(string loc) {
    char buffer[256];
    ostringstream os;

    setlocale(LC_ALL, loc.c_str());
    strftime(buffer, 256, "%c", &_timeinfo);
    os << buffer;

    return os.str();
}

