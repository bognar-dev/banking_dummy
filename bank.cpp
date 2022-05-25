//
// Created by nikla on 23/05/2022.
//

#include <iostream>
#include <unistd.h>
#include "bank.h"



bank::bank(string bankName){
    _bankname = bankName;
}

void bank::writeToFile(string filename) {
 //TODO
}

void bank::readFromFile(string filename) {
    //todo
}

void bank::createGiro(int ownerID, float startAmount, float dispolimit, DateTime date) {
    try {
        for (auto& account:_bankaccounts) {
            if(account->getID() == ownerID){
                _bankaccounts.push_back(new Giro(ownerID, startAmount, dispolimit));
            }
        }
        throw runtime_error("No account was found with the id " + to_string(ownerID));
    }catch(runtime_error &e) {
        cerr << e.what() << endl;

    }
}



void bank::createSavingsAccount(int ownerID, float startAmount, int interestRate, DateTime date) {
    //TODO
}

void bank::removeAccount(int number) {
    //TODO
    try {
        for (auto& account:_bankaccounts) {
            if(account->getID() == number){

            }
        }
        throw runtime_error("No account was found with the id ");
    }catch(runtime_error &e) {
        cerr << e.what() << endl;
    }
}

string bank::customerList(){
    ostringstream os;
    try {
    if(_owners.size()==0){
        throw runtime_error(" No customers yet");
    }
    for(auto& user:_owners){
        os<<user.toString()<<"\n";
    }
    }catch (runtime_error &e) {
        cerr<<e.what()<<endl;
    }
    return os.str();
}

void bank::payIn(int accountID, float amount, DateTime date) {
    //TODO
}

void bank::withdraw(int accountID, float amount, DateTime date) {
    //TODO
}

void bank::transfer(int ownerAccountID, int recieverAccountID, float amount, string message, DateTime date) {
    //TODO
}

void bank::interestPayment(DateTime date) {
    //TODO
}

bool bank::isAccountValid(int accountID) {
    //todo
}

bool bank::isCustomerValid(int userID) {
    //TODO
}

string bank::getstatement(int accountID) {
    //TODO: PINCODE?
    try {
    for (auto& account:_bankaccounts) {
        if(account->getID() == accountID){
            account->addActivity(Activity("stament"));
            return account->statement();
        }
    }
    throw runtime_error(&"No account was found with the id " [ accountID]);
    }catch(runtime_error &e) {
        cerr << e.what() << endl;
    }
}

string bank::listOfAccounts() {
    ostringstream os;
    for (auto& account:_bankaccounts){
    os<< account->toString()<<"\n";
    }
    return os.str();
}

void bank::newCustomer(string name, Address address) {
    owner newuser(name,address);

    try{
        for (auto& user : _owners)
        if(newuser == user){
            throw runtime_error("Customer already exists");
        }
    }catch(runtime_error &e) {
        cerr << e.what() << endl;
    }
    _owners.push_back(newuser);
}

void bank::removeCustomer(int id) {
//TODO
}

void bank::editCustomer(int id, string name, Address adress) {
//TODO
}

