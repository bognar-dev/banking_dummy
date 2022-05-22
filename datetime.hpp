// ===================================================================
// datetime.h
// simple wrapper for time_t, struct tm, mktime(), difftime(), ...
// ===================================================================

#pragma once

#include <string>
#include <ostream>

class DateTime {
    friend std::ostream& operator<<(std::ostream&, const DateTime&);

protected:
    int _day, _month, _year;
    int _second, _minute, _hour;
    time_t _time;
    tm _timeinfo;

public:
    DateTime();
    DateTime(int d, int m, int y, int hh, int mm, int sc);

    int diff(DateTime dt);
    std::string toString(std::string locale);
};

