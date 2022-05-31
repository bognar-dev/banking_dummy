//
// Created by nikla on 23/05/2022.
//

#include <iomanip>
#include <iostream>
#include "owner.h"

ostream &operator<<(ostream &os, const Address &a) {
    os << a._street << " " << a._housenumber << " " << a._postcode;
    return os;
}

istream &operator>>(istream &is, Address &a) {

    getline(is, a._street);
    getline(is, a._postcode);
    cin >> a._housenumber;

    return is;
}


Address::Address(string street, int housenumber, string postcode) {
    _street = street;
    _postcode = postcode;
    _housenumber = housenumber;
}

string Address::toFile() {
    ostringstream os;
    os << _street << "#" << _housenumber << "#" << _postcode << "#";
    return os.str();
}


int owner::_usercount = 1;
int owner::_userIDgeneration = 1;

void owner::setOwnerCount(int count) {
    _usercount = count + 1;
    _userIDgeneration = count + 1;
}


owner::owner(int number, int userID, string name, Address address) {
    _number = number;
    _userID = userID;
    _name = name;
    _address = address;
}

owner::owner(string name, Address address) {
    _number = _usercount++;
    _userID = _userIDgeneration++;
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
    os << "Number: " << _number << " UserID: " << _userID << " Name: " << _name << " Address: " << _address;
    return os.str();
}

string owner::toFile() {
    ostringstream os;
    os << "#" << _number << "#" << _userID << "#" << _name << "#" << _address.toFile();
    return os.str();
}

owner owner::parse(string line) {
    //TODO what is a parser?
}

void owner::addAccount(Bankaccount *account) {
    _accounts.push_back(account);
}

void owner::removeAccount(Bankaccount *account) {
    for (auto &a: _accounts) {
        if (a == account) {
            _accounts.pop_back();
        }
    }
}

vector<Bankaccount *> owner::getAccounts() {
    return _accounts;
}

int owner::getID() {
    return _userID;
}