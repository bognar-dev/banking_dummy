//
// Created by nikla on 23/05/2022.
//

#ifndef BANKING08_OWNER_H
#define BANKING08_OWNER_H

#include <string>
#include "Bankaccount.h"

using namespace std;

class owner {
protected:
    int _number;
    int _userid;
    string _name;
    string _adress;
public:
    void setName(string name);
    void setAdress(string address);
    string toString();
    owner parse(string line);
    void addAccount(Bankaccount account);
    void removeAccount(Bankaccount account);
    vector<Bankaccount*> getAccounts();

};


#endif //BANKING08_OWNER_H
