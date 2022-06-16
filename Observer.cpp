//
// Created by nikla on 16/06/2022.
//

#include "Observer.h"
static int UniqueIDcount = 0;
bool Observer::operator==(const Observer& o) const {
    return (_ID == o._ID);
}

Observer::Observer(string userfile,string bankfile){
    _ID = UniqueIDcount++;
    _bankfile = bankfile;
    _userfile = userfile;
}

void Observer::autosave(bank &Bank) {
    Bank.writeToFile(_bankfile,_userfile);
}


int Observer::getID(){
    return _ID;
}

