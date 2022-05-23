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

    void virtual withdrawl(float amount = 0, DateTime d = DateTime()) = 0;

    void virtual payIn(float amount = 0, DateTime d = DateTime()) = 0;

    float balance();

    //void transfer(float amount ,string accountnumber ,string discription , DateTime d);
    virtual string statement() = 0;
    //virtual ~Bankaccount();
};

class Giro : public Bankaccount {
protected:
    float _dispoLimit;
    float _debitInterest;

public:
    Giro(float dispoLimit = 0, float debitInterest = 1.5);

    void withdrawl(float amount = 0, DateTime d = DateTime());

    void payIn(float amount = 0, DateTime d = DateTime());

    void
    transfer(float amount = 0, string accountnumber = "00000000000", string discription = "", DateTime d = DateTime());

    string statement();
    //~Giro();

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
