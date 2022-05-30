//
// Created by nikla on 23/05/2022.
//

#include "Activity.h"
Activity::Activity(string information,float amount, DateTime day){
    _information = information;
    _amount = amount;
    _day = day;
}
Activity::Activity(string information, DateTime day) {
    _information = information;
    _day = day;
}

string Activity::toString(){
    ostringstream os;
    os<<"information: "<<_information<< " amount: "<<_amount<<" date: "<<_day;
    return os.str();
}

Activity Activity::parse(string line) {
    //TODO
}