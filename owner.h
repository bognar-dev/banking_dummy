//
// Created by nikla on 23/05/2022.
//

#ifndef BANKING08_OWNER_H
#define BANKING08_OWNER_H

#include <string>
#include "Bankaccount.h"

using namespace std;
struct Address{
    friend ostream &operator<<(ostream& os, const Address& a);
public:
    string _street;
    int _housenumber;
    string _postcode;
    Address(string street = "", int housenumber = 0, string postcode = "");
    bool operator==(const Address& a){
        return a._street == _street && a._housenumber == _housenumber && a._postcode == _postcode;
    }
};

class owner {
protected:
    int _number;
    int _userID;
    string _name;
    Address _address;
    vector<Bankaccount*> _accounts;
public:
    owner(int number,int userID, string name, Address address = Address());
    owner();
    void setName(string name);
    void setAddress(Address address);
    string toString();
    owner parse(string line);
    void addAccount(Bankaccount* account);
    void removeAccount(Bankaccount* account);
    vector<Bankaccount*> getAccounts();
    int getID();
    bool operator==(const owner& o){
        return _name == o._name && _address == o._address && _accounts.size() == o._accounts.size();
    }
};


#endif //BANKING08_OWNER_H
