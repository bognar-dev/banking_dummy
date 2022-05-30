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
    static int _accountCount;
    static int _number;
    int _owner;
    string _pinCode;
    int _id;
    int _accountnr;
    DateTime _lastUpdate;
    vector< Activity*> _activities;
    float _balance;
    vector<string> _statementRecords;
public:
    Bankaccount(float balance = 0, int owner = 0,int id = 0);
    void virtual withdrawl(float amount = 0, DateTime d = DateTime()) = 0;
    void virtual payIn(float amount = 0, DateTime d = DateTime()) = 0;
    void interestBalance(DateTime date);
    void addRecord(Bankaccount* account,string record);
    string virtual toFile() = 0;
    string toString();
    string randomPIN();
    int getOwner() const;
    int getID();
    string getPIN();
    void addActivity(Activity activity);
    vector<Activity*>getActivities();
    float balance();
    void changeBalance(float amount);
    virtual void transfer(float amount, int accountnumber,int reiceiver, string discription , DateTime d) = 0;
    virtual void transferTo(float amount , int accountnumber  , int reiceiver , string discription , DateTime d = DateTime()) = 0;
    virtual string statement () = 0;
    bool operator ==(const Bankaccount& b) const;


};

class Giro : public Bankaccount {
    friend ostream& operator<<(ostream&, const Giro&);
    friend istream& operator<<(istream&, const Giro&);
protected:
    float _dispoLimit;
    float _debitInterest;

public:
    Giro(int owner,float startbalance,float dispoLimit = 0, float debitInterest = 1.5);
    void withdrawl(float amount = 0, DateTime d = DateTime());
    void payIn(float amount = 0, DateTime d = DateTime());
    void transfer(float amount = 0, int accountnumber  = 0, int reiceiver = 0, string discription = "", DateTime d = DateTime());
    void transferTo(float amount = 0, int accountnumber  = 0, int reiceiver = 0, string discription = "", DateTime d = DateTime());
    string statement();
    string toFile();

};

class Savingsaccount : public Bankaccount {
    //friend ostream& operator<<(ostream&, const Savingsaccount&);
    friend istream& operator>>(istream&, const Savingsaccount&);
protected:
    float _interestRate;
public:
    Savingsaccount(int owner,float startAmount,float interestRate = 0);
    void withdrawl(float amount = 0, DateTime d = DateTime());
    void payIn(float amount = 0, DateTime d = DateTime());
    string statement();
    void transfer(float amount , int accountnumber , int reiceiver , string discription , DateTime d);
    void transferTo(float amount , int accountnumber , int reiceiver, string discription , DateTime d);
    string toFile();
};

#endif //BANKING08_BANKACCOUNT_H
