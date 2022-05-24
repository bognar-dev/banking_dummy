//
// Created by nikla on 23/05/2022.
//

#include <iostream>
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

void bank::createGiro(int ownerID, int pinCode, float startAmount, int dispolimit, DateTime date) {
    //TODO
}

void bank::createSavingsAccount(int ownerID, int pinCode, float startAmount, int interestRate, DateTime date) {
    //TODO
}

void bank::removeAccount(int number) {
    //TODO
}

vector<owner> bank::customerList(){
    return _owners;
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

