//
// Created by nikla on 22/05/2022.
//

#include <iomanip>
#include <iostream>
#include "Bankaccount.h"

Bankaccount::Bankaccount() {
    //TODO add parameters
    _balance = 0;
    _statementRecords.size();
}

void Bankaccount::interestBalance(DateTime date) {
    //TODO
}

string Bankaccount::toString(){
    //TODO
};
int Bankaccount::getOwner() {
    //TODO
}

vector<Activity*>Bankaccount::getActivities(){
    //TODO
}
//Bankaccount::~Bankaccount() = default;

void Giro::payIn(float amount, DateTime d) {
    _balance += amount;
    ostringstream os;
    os << setw(17) << d.toString("en_GB.UTF8") << "|" << setw(26) << "|" << setw(26) << "|" << "+" << setw(24) << amount
       << "|" << setw(25);
    //if (_balance < 0) { os << "-"; }
    os << setw(20) << _balance << "|";
    _statementRecords.push_back(os.str());
}


float Bankaccount::balance() {
    return _balance;
}

Giro::Giro(float dispolimit, float debitinterest) : Bankaccount() {
    _dispoLimit = dispolimit;
    _debitInterest = debitinterest;
}

//Giro::~Giro() = default;

void Giro::withdrawl(float amount, DateTime d) {
    try {
        if ((_balance - amount) < _dispoLimit) {
            throw runtime_error("Your dispolimit has been exeeded!");
        }
        _balance -= amount;
        ostringstream os;
        os << setw(17) << d.toString("en_GB.UTF8") << "|" << setw(26) << "|" << setw(26) << "|" << "-" << setw(24)
           << amount << "|" << setw(25);
        os << setw(20) << _balance << "|";
        _statementRecords.push_back(os.str());
    } catch (runtime_error &e) {
        std::cerr << e.what() << endl;
    }
}

void Giro::transfer(float amount, string accountnumber, string discription, DateTime d) {
    try {
        if (_balance - amount <= 0) {
            throw runtime_error("Your balance cant be negative!");
        }
        _balance -= amount;

        ostringstream os;
        os << setw(17) << d.toString("en_GB.UTF8") << "|" << setw(25) << discription << "|" << setw(25) << accountnumber
           << "|" << "-" << setw(24) << amount << "|" << setw(25);
        os << setw(20) << _balance << "|";
        _statementRecords.push_back(os.str());
    } catch (runtime_error &e) {
        std::cerr << e.what() << endl;
    }
}

string Giro::statement() {
    ostringstream statement;
    statement << setw(17) << "Date" << "|" << setw(25) << "Discription" << "|" << setw(25) << "Receiver" << "|"
              << setw(25) << "Withdrawl/Deposit" << "|";
    statement << setw(20) << "Balance" << "|" << "\n";
    for (auto &record: _statementRecords) {
        statement << record << "\n";
    }
    ostringstream balance_setprecision4;
    balance_setprecision4 << _balance << setprecision(4);
    string currentBalance = "Current Balance: " + balance_setprecision4.str();
    statement << setw(116) << "==========" << "|" << "\n" << setw(116) << currentBalance << "|" << "\n";
    return statement.str();
}

Savingsaccount::Savingsaccount(float interestRate) : Bankaccount() {
    _interestRate = interestRate;
}

void Savingsaccount::withdrawl(float amount, DateTime d) {
    try {
        if (_balance - amount <= 0) {
            throw runtime_error("Your balance cant be negative!");
        }
            _balance -= amount;
        ostringstream os;
        os << setw(17) << d.toString("en_GB.UTF8") << "|" << "-" << setw(24) << amount << "|" << setw(25);
        os << setw(20) << _balance;
        _statementRecords.push_back(os.str());
    } catch (runtime_error &e) {
        std::cerr << e.what() << endl;
    }
}

string Savingsaccount::statement() {
    ostringstream statement;
    statement << setw(17) << "Date" << "|" << setw(25) << "Withdrawl/Deposit" << "|";
    statement << setw(20) << "Balance" << "\n";
    for (auto &record: _statementRecords) {
        statement << record << "\n";
    }
    ostringstream balance_setprecision4;
    balance_setprecision4 << _balance << setprecision(4);
    string currentBalance = "Current Balance: " + balance_setprecision4.str();
    statement << setw(64) << "==========" << "\n" << setw(64) << currentBalance << "\n";
    return statement.str();
}

void Savingsaccount::payIn(float amount, DateTime d) {
    _balance += amount;
    ostringstream os;
    os << setw(17) << d.toString("en_GB.UTF8") << "|" << "+" << setw(24) << amount << "|" << setw(25);
    os << setw(20) << _balance;
    _statementRecords.push_back(os.str());
}

