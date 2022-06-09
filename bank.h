//
// Created by nikla on 23/05/2022.
//

#ifndef BANKING08_BANK_H
#define BANKING08_BANK_H

#include <vector>
#include <string>
#include <ctime>
#include "owner.h"
#include "Bankaccount.h"
#include "datetime.hpp"

using namespace std;
class bank {
    friend Giro;
    friend Bankaccount;
    friend Savingsaccount;
protected:
    vector<Bankaccount *> _bankaccounts;
    vector<owner> _owners;
    string _bankname;
    static int _usercount;
    static int _accountcount;
public:
    bank(string bankName);
    void writeToFile(string bankaccountfile,string usersfile);
    void readFromFile(string bankaccountfile,string usersfile);
    void createGiro(int ownerID,float startAmount,float dispolimit = 0, DateTime date= DateTime());
    void createSavingsAccount(int ownerID,float startAmount,float interestRate = 0, DateTime date= DateTime());
    void removeAccount(int number);
    string listOfAccounts();
    void newCustomer(string name,Address adress);
    void removeCustomer(int id);
    void editCustomer(int id,string name,Address adress);
    string customerList();
    void payIn(int accountID,float amount,DateTime date = DateTime());
    void withdraw(int accountID,float amount,DateTime date = DateTime());
    void transfer(int ownerAccountID,int recieverAccountID ,float amount,string message,DateTime date = DateTime());
    void interestPayment(DateTime date = DateTime());
    bool isAccountValid(int accountID);
    bool isCustomerValid(int userID);
    string getstatement(int accountID);
    string getAction(int accountID);
    bool PinVerification(int accountNr,int pin);


};


#endif //BANKING08_BANK_H
