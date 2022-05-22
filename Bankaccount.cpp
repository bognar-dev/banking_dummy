//
// Created by nikla on 22/05/2022.
//

#include <iomanip>
#include <iostream>
#include "Bankaccount.h"

Bankaccount::Bankaccount() {
    _balance = 0;
    _statementRecords.size();
}

Bankaccount::~Bankaccount() = default;

void Bankaccount::payIn(float amount, DateTime date) {
    _balance += amount;
    ostringstream os;
    os << "+" << setw(18) << amount << "|" << setw(25) << date.toString("en_GB.UTF8") << "|";
    if (_balance < 0) { os << setw(5) << "-"; }
    os << setw(10) << _balance;
    _statementRecords.push_back(os.str());
}


float Bankaccount::balance() {
    return _balance;
}

string Bankaccount::statement() {
    ostringstream statement;
    statement << setw(19) << "Withdrawl/Deposit" << "|" << setw(25) << "Date" << "|";
    statement << setw(10) << "Balance"<<"\n";
    for (auto &record: _statementRecords) {
        statement << record << "\n";
    }
    statement << setw(56)<<"=========="<<"\n" << setw(56)<< _balance;
    return statement.str();
}

Giro::Giro(float dispolimit, float debitinterest) : Bankaccount() {
    _dispoLimit = dispolimit;
    _debitInterest = debitinterest;
}

Giro::~Giro() = default;

void Giro::withdrawl(float amount, DateTime d) {
    try {
        if ((_balance - amount) < _dispoLimit) {
            throw runtime_error("Your dispolimit has been exeeded!");
        }
        _balance -= amount;
        ostringstream os;
        os << "-" << setw(18) << amount << "|" << setw(25) << d.toString("en_GB.UTF8") << "|";
        if (_balance < 0) { os << setw(5) << "-"; }
        os << setw(10) << _balance;
        _statementRecords.push_back(os.str());
    } catch (runtime_error &e) {
        std::cerr<< e.what() << endl;
    }
}

void Giro::transferToDifferentAccount(string accountnumber, int amount, DateTime d) {
    try {
        if ((_balance - amount) < _dispoLimit) {
            throw runtime_error("Your dispolimit has been exeeded!");
        }
        _balance -= amount;
        ostringstream os;
        os << "-" << setw(18) << amount << "|" << setw(25) << d.toString("en_GB.UTF8") << "|";
        if (_balance < 0) { os << setw(5) << "-"; }
        os << setw(10) << _balance;
        _statementRecords.push_back(os.str());
    } catch (runtime_error &e) {
        std::cerr<< e.what() << endl;
    }
}

Savingsaccount::Savingsaccount(float interestRate) :Bankaccount(){
    _interestRate = interestRate;
}

void Savingsaccount::withdrawl(float amount, DateTime d) {
    try {
        if (_balance <= 0) {
            throw runtime_error("Your balance cant be negative!");
        }
        _balance -= amount;
        ostringstream os;
        os << "-" << setw(18) << amount << "|" << setw(25) << d.toString("en_GB.UTF8") << "|";
        if (_balance < 0) { os << setw(5) << "-"; }
        os << setw(10) << _balance;
        _statementRecords.push_back(os.str());
    } catch (runtime_error &e) {
        std::cerr<< e.what() << endl;
    }
}

