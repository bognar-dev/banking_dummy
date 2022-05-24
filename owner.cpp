//
// Created by nikla on 23/05/2022.
//

#include "owner.h"
ostream &operator<<(ostream &os, const Address &a) {
    os<<a._street<<a._housenumber<<a._postcode;
    return os;
}
Address::Address(string street, int housenumber, string postcode) {
    _street = street;
    _postcode = postcode;
    _housenumber = housenumber;
}


owner::owner(int number, int userID, string name, Address address) {
    _number = number;
    _userID = userID;
    _name = name;
    _address = address;
}

void owner::setName(string name) {
    _name = name;
}

void owner::setAddress(Address address) {
    _address = address;
}

string owner::toString() {
    ostringstream os;
    os<<"Number: "<<_number<<" User: "<<_userID<<"Name: "<<_name<<"Address: "<< _address;
    return os.str();
}

owner owner::parse(string line) {
    //TODO what is a parser?
}

void owner::addAccount(Bankaccount account) {
    _accounts.push_back(&account);
}

void owner::removeAccount(Bankaccount account) {
    for (auto& a : _accounts){
        if(a == &account) {
            _accounts.pop_back();
        }
    }
}

vector<Bankaccount*> owner::getAccounts(){
    return _accounts;
}