//
// Created by nikla on 22/05/2022.
//

#ifndef BANKING08_BANKACCOUNT_H
#define BANKING08_BANKACCOUNT_H


#include <vector>
#include <sstream>
#include "datetime.hpp"
using namespace std;

class Bankaccount {
protected:
    float _balance;
    vector<string> _statementRecords;
public:
    Bankaccount();
    void virtual withdrawl(float amount, DateTime d) = 0;
    void payIn(float amount = 0, DateTime d = DateTime());
    float balance();
    string statement();
    virtual ~Bankaccount();
};

class Giro : public Bankaccount{
protected:
    float _dispoLimit;
    float _debitInterest;

public:
    Giro(float dispoLimit = 0, float debitInterest = 1.5);
    void withdrawl(float amount = 0,DateTime d = DateTime());
    void transferToDifferentAccount(string accountnumber ="00000000000",int amount = 0 ,DateTime d = DateTime());
    ~Giro();

};

class Savingsaccount : public Bankaccount{
protected:
    float _interestRate;
public:
    Savingsaccount(float interestRate = 0);
    void withdrawl(float amount = 0, DateTime d = DateTime());
};
#endif //BANKING08_BANKACCOUNT_H
