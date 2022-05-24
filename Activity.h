//
// Created by nikla on 23/05/2022.
//

#ifndef BANKING08_ACTIVITY_H
#define BANKING08_ACTIVITY_H

#include <string>
#include <sstream>
#include "datetime.hpp"

using namespace std;

class Activity {
protected:
    string _information;
    float _amount;
    DateTime _day;
public:
    Activity(string information, float amount,DateTime day = DateTime());
    Activity(string information, DateTime day = DateTime());
    string toString();
    Activity parse(string line);
};


#endif //BANKING08_ACTIVITY_H
