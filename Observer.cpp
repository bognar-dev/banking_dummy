//
// Created by nikla on 16/06/2022.
//

#include <fstream>
#include "Observer.h"

static int UniqueIDcount = 0;

bool Observer::operator==(const Observer &o) const {
    return (_ID == o._ID);
}

Filesaver::Filesaver(string userfile, string bankfile) {
    _bankfile = bankfile;
    _userfile = userfile;
}

void Filesaver::autosave(bank &Bank) {
    Bank.writeToFile(_bankfile, _userfile);
}


int Observer::getID() {
    return _ID;
}

Observer::Observer() {
    _ID = UniqueIDcount++;
}

CountObserver::CountObserver(string countfile) {
_countingfile = countfile;

}

void CountObserver::autosave(bank &Bank){
    istringstream is(Bank.getstatement(9000));
    ofstream f(_countingfile);
    f<<is.str();

}
