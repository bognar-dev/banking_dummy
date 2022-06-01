//
// Created by nikla on 22/05/2022.
//
//TODO interst Rate, etc...
#include <iomanip>
#include <iostream>
#include "Bankaccount.h"

int Bankaccount::_number = 9000;
int Bankaccount::_accountCount = 0;

string Bankaccount::randomPIN() {
    srand((unsigned int) __TIME__);
    string pin;
    for (int i = 0; i < 4; ++i) {
        pin += to_string((rand() % 10));
    }
    return pin;
}

bool Bankaccount::operator==(const Bankaccount &b) const {
    return (_number == b._number);
}


Bankaccount::Bankaccount(float balance, int owner, int id) {
    _accountnr = _number++;
    _owner = owner;
    _pinCode = Bankaccount::randomPIN();
    _id = _accountCount++;
    _balance = balance;
}

void Bankaccount::interestBalance(DateTime date) {
    //TODO
}

string Bankaccount::toString() {
    ostringstream os;
    os << "Accountnumber: " << _accountnr << " Owner: " << _owner << " ID: " << _id << " Last activity: "
       << _lastUpdate;
    return os.str();
}

string Bankaccount::getPIN() {
    return _pinCode;
}

int Bankaccount::getOwner() const {
    return _owner;
}

int Bankaccount::getID() {
    return _accountnr;
}

void Bankaccount::addActivity(Activity activity) {
    _activities.push_back(&activity);
}

vector<Activity *> Bankaccount::getActivities() {
    return _activities;
}
//Bankaccount::~Bankaccount() = default;

void Giro::payIn(float amount, DateTime d) {
    _balance += amount;
    ostringstream os;
    os << setw(17) << d.toString("en_GB.UTF8") << "|" << setw(26) << "|" << setw(26) << "|" << "+" << setw(24) << amount
       << "|" << setw(25);
    //if (_balance < 0) { os << "-"; }
    os << setw(20) << fixed << _balance << "|";
    _activities.push_back(new Activity("PayIn: ", amount, d));
    _statementRecords.push_back(os.str());
}


float Bankaccount::balance() {
    return _balance;
}

void Bankaccount::addRecord(Bankaccount *account, string record) {
    account->_statementRecords.push_back(record);
}

Giro::Giro(int owner, float startAmount, float dispolimit, float debitinterest) : Bankaccount() {
    _owner = owner;
    _balance = startAmount;
    _dispoLimit = dispolimit;
    _debitInterest = debitinterest;
    _activities.push_back(new Activity("Account created", 0, DateTime()));
}

string Giro::toFile() {
    ostringstream os;
    os << _owner << "#" << _pinCode << "#" << _id << "#" << _accountnr << "#" << _lastUpdate << "#" << _balance << "#";
    for (string &record: _statementRecords) {
        os << record << ",";
    }
    os << "#";
    for (Activity *activity: _activities) {
        os << activity->toString() << ",";
    }
    os << "#";
    os << _dispoLimit << "#" << _debitInterest << "#" << endl;
    return os.str();
}

//Giro::~Giro() = default;

void Giro::withdrawl(float amount, DateTime d) {
    try {
        if ((_balance - amount) < -(_dispoLimit)) {
            throw runtime_error("Your dispolimit has been exeeded!");
        }
        _balance -= amount;
        ostringstream os;
        os << setw(17) << d.toString("en_GB.UTF8") << "|" << setw(26) << "|" << setw(26) << "|" << "-" << setw(24)
           << amount << "|" << setw(25);
        os << setw(20) << fixed << _balance << "|";
        _statementRecords.push_back(os.str());
        _activities.push_back(new Activity("Withdrawl: ", amount, d));
    } catch (runtime_error &e) {
        std::cerr << e.what() << endl;
    }
}

void Bankaccount::changeBalance(float amount) {
    _balance += amount;
}

void Giro::transfer(float amount, int accountnumber, int receiver, string discription, DateTime d) {
    try {
        if (_balance - amount <= 0) {
            throw runtime_error("Your balance cant be negative!");
        }
        _balance -= amount;

        ostringstream os;
        os << setw(17) << d.toString("en_GB.UTF8") << "|" << setw(25) << discription << "|" << setw(25) << receiver
           << "|" << "-" << setw(24) << amount << "|" << setw(25);
        os << setw(20) << fixed << _balance << "|";
        _activities.push_back(new Activity(("Transfer, " + discription + " : "), amount, d));
        _statementRecords.push_back(os.str());
    } catch (runtime_error &e) {
        std::cerr << e.what() << endl;
    }
}

void Giro::transferTo(float amount, int accountnumber, int receiver, string discription, DateTime d) {
    try {
        _balance += amount;

        ostringstream os;
        os << setw(17) << d.toString("en_GB.UTF8") << "|" << setw(25) << discription << "|" << setw(25) << accountnumber
           << "|" << "+" << setw(24) << fixed << amount << "|" << setw(25);
        os << setw(20) << fixed << _balance << "|";
        _activities.push_back(new Activity(("Transfer, " + discription + " : "), amount, d));
        _statementRecords.push_back(os.str());
    } catch (runtime_error &e) {
        std::cerr << e.what() << endl;
    }
}

string Giro::statement() {
    ostringstream statement;
    statement << setw(17) << "Date" << "|" << setw(25) << "Discription" << "|" << setw(25) << "Receiver/Sender" << "|"
              << setw(25) << "Withdrawl/Deposit" << "|";
    statement << setw(20) << "Balance" << "|" << "\n";
    for (auto &record: _statementRecords) {
        statement << record << "\n";
    }
    ostringstream balance_setprecision4;
    balance_setprecision4 << fixed << _balance << setprecision(4);
    string currentBalance = "Current Balance: " + balance_setprecision4.str();
    statement << setw(116) << "==========" << "|" << "\n" << setw(116) << fixed << currentBalance << "|" << "\n";
    return statement.str();
}

Savingsaccount::Savingsaccount(int owner, float startAmount, float interestRate) : Bankaccount() {
    _interestRate = interestRate;
    _owner = owner;
    _balance = startAmount;
    _activities.push_back(new Activity("Account created"));
}

string Savingsaccount::toFile() {
    ostringstream os;
    os << _owner <<"#" << _pinCode <<"#" << _id <<"#" << _accountnr <<"#" << _lastUpdate <<"#" << _balance <<"#";
    for (string &record: _statementRecords) {
        os << record << ",";
    }
    os <<"#";
    for (auto &activity: _activities) {
        os << activity->toString() << ",";
    }
    os <<"#";
    os << _interestRate <<"#" << endl;
    return os.str();
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
        _activities.push_back(new Activity("Withdrawl: ", amount, d));
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
    balance_setprecision4 << fixed << _balance << setprecision(4);
    string currentBalance = "Current Balance: " + balance_setprecision4.str();
    statement << setw(64) << "==========" << "\n" << setw(64) << fixed << currentBalance << "\n";
    return statement.str();
}

void Savingsaccount::payIn(float amount, DateTime d) {
    _balance += amount;
    ostringstream os;
    os << setw(17) << d.toString("en_GB.UTF8") << "|" << "+" << setw(24) << amount << "|" << setw(25);
    os << setw(20) << fixed << _balance;
    _activities.push_back(new Activity("PayIn: ", amount, d));
    _statementRecords.push_back(os.str());
}

void Savingsaccount::transfer(float amount, int accountnumber, int reiceiver, string discription, DateTime d) {

}

void Savingsaccount::transferTo(float amount, int accountnumber, int reiceiver, string discription, DateTime d) {

}
