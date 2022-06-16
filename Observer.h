//
// Created by nikla on 16/06/2022.
//

#ifndef BANKING08_OBSERVER_H
#define BANKING08_OBSERVER_H
#include <string>
#include "bank.h"


using namespace std;
class bank;
class Observer{
protected:
    int _ID;
    string _userfile;
    string _bankfile;

public:
    bool operator ==(const Observer& o) const;
    Observer(string userfile, string bankfile);
    void autosave(bank &Bank);
    int getID();
};

#endif //BANKING08_OBSERVER_H
