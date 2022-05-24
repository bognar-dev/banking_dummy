//
// Created by nikla on 22/05/2022.
//

#ifndef BANKING08_BANKACCOUNT_H
#define BANKING08_BANKACCOUNT_H


#include <vector>
#include <sstream>
#include "datetime.hpp"
#include "Activity.h"

using namespace std;

class Bankaccount {
protected:
    int _number;
    int _owner;
    string _pinCode;
    int _id;
    DateTime _lastUpdate;
    vector< Activity*> _activities;
    float _balance;
    vector<string> _statementRecords;
public:
    Bankaccount(float balance = 0,int accNumber = 0, int owner = 0, string pinCode = "",int id = 0);
    void virtual withdrawl(float amount = 0, DateTime d = DateTime()) = 0;
    void virtual payIn(float amount = 0, DateTime d = DateTime()) = 0;
    void interestBalance(DateTime date);
    string toString();
    int getOwner() const;
    int getID();
    void addActivity(Activity activity);
    vector<Activity*>getActivities();
    float balance();
    virtual string statement() = 0;
    bool operator ==(const Bankaccount& b) const;
};

class Giro : public Bankaccount {
protected:
    float _dispoLimit;
    float _debitInterest;

public:
    Giro(float dispoLimit = 0, float debitInterest = 1.5);
    void withdrawl(float amount = 0, DateTime d = DateTime());
    void payIn(float amount = 0, DateTime d = DateTime());
    void transfer(float amount = 0, string accountnumber = "00000000000", string discription = "", DateTime d = DateTime());
    string statement();

};

class Savingsaccount : public Bankaccount {
protected:
    float _interestRate;
public:
    Savingsaccount(float interestRate = 0);
    void withdrawl(float amount = 0, DateTime d = DateTime());
    void payIn(float amount = 0, DateTime d = DateTime());
    string statement();
};

#endif //BANKING08_BANKACCOUNT_H
