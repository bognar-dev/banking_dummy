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
    public:
    bool operator ==(const Observer& o) const;
    Observer();
    int getID();
    virtual void autosave(bank &Bank) = 0;


};
class Filesaver : public Observer{
protected:
    string _userfile;
    string _bankfile;

public:
    Filesaver(string userfile, string bankfile);
    void autosave(bank &Bank);
};

class CountObserver : public Observer{
    protected:
    string _countingfile;
    public:
    CountObserver(string countfile);
    void autosave(bank &Bank);

};

#endif //BANKING08_OBSERVER_H
