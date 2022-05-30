//
// Created by nikla on 23/05/2022.
//

#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <fstream>
#include <string>
#include "bank.h"


bank::bank(string bankName) {
    _bankname = bankName;
}

void bank::writeToFile(string bank, string users) {
    ofstream bankaccounts(bank, ios::out);
    for(auto* acc : _bankaccounts){
        bankaccounts << acc->toFile() << endl;
    }
    bankaccounts.close();
    ofstream userdat(users,ios::out);
    for(auto &user : _owners){
        userdat<< user.toFile() <<endl;
    }
userdat.close();


}

void bank::readFromFile(string bankaccounts,string users) {
    ifstream bankacc(bankaccounts);
    char buffer[256];

    if (!bankacc)
        throw runtime_error("could not open file");
    while (!bankacc.eof()) {
        /*istringstream is;
        is >> _owner >> "#" >> _pinCode >> "#" >> _id >> "#" >> _accountnr >> "#" >> _lastUpdate >> "#" >> _balance >> "#";
        for (string &record: _statementRecords) {
            is >> record >> "," << endl;
        }
        is >> "#";
        for (auto &activity: _activities) {
            is >> activity->toString() >> "," << endl;
        }
        is << "#";
        is << _interestRate << "#" << endl;
*/
        bankacc.getline(buffer,256,'#');
        cout<< buffer <<endl;
        cout<<"NEW ACCOUNT DATA"<<endl;
    }
    bankacc.close();
    ifstream u(users);
    if(!u)
        throw std::runtime_error("Could not open user file");
    while (!u.eof()) {
        u.getline(buffer,256,'#');
        cout<< buffer <<endl;
        cout <<"NEW USER DATA" << endl;
    }
}

void bank::createGiro(int ownerID, float startAmount, float dispolimit, DateTime date) {
    try {
        for (auto &user: _owners) {
            if (user.getID() == ownerID) {
                _bankaccounts.push_back(new Giro(ownerID, startAmount, dispolimit));
                user.addAccount(new Giro(ownerID, startAmount, dispolimit));
                //cout<<g.getPIN()<<endl;
                return;
            }
        }
        throw runtime_error("No account was found with the id " + to_string(ownerID));
    } catch (runtime_error &e) {
        cerr << e.what() << endl;

    }
}


void bank::createSavingsAccount(int ownerID, float startAmount, float interestRate, DateTime date) {
    try {
        for (auto &user: _owners) {
            if (user.getID() == ownerID) {
                _bankaccounts.push_back(new Savingsaccount(ownerID, startAmount, interestRate));
                user.addAccount(new Savingsaccount(ownerID, startAmount, interestRate));
                return;
            }
        }
        throw runtime_error("No user was found with the id " + to_string(ownerID));
    } catch (runtime_error &e) {
        cerr << e.what() << endl;

    }
    //TODO
}

void bank::removeAccount(int number) {
    //TODO
    try {
        for (int i = 0; i < _bankaccounts.size(); i++) {
            if (_bankaccounts[i]->getID() == number) {
                _bankaccounts.erase(_bankaccounts.begin() + i);
            }
        }
        throw runtime_error("No account was found with the id ");
    } catch (runtime_error &e) {
        cerr << e.what() << endl;
    }
}

string bank::customerList() {
    ostringstream os;
    try {
        if (_owners.size() == 0) {
            throw runtime_error(" No customers yet");
        }
        for (auto &user: _owners) {
            os << user.toString() << "\n";
        }
    } catch (runtime_error &e) {
        cerr << e.what() << endl;
    }
    return os.str();
}

void bank::payIn(int accountNr, float amount, DateTime date) {
    try {
        for (auto &account: _bankaccounts) {
            if (account->getID() == accountNr) {
                account->payIn(amount);
                return;
            }
        }
        throw runtime_error("No account with ID " + to_string(accountNr) + " found");
    } catch (runtime_error &e) {
        cerr << e.what() << endl;
    }
}

void bank::withdraw(int accountNr, float amount, DateTime date) {
    try {
        for (auto &account: _bankaccounts) {
            if (account->getID() == accountNr) {
                account->withdrawl(amount);
                return;
            }
            throw runtime_error("No account with ID " + to_string(accountNr) + " found");
        }
    } catch (runtime_error &e) {
        cerr << e.what() << endl;
    }
}

void bank::transfer(int ownerAccountNr, int recieverAccountID, float amount, string message, DateTime date) {
    bool found = false;
    Bankaccount* accountTO;
    try {
        for (auto &account: _bankaccounts) {
            if(account->getID()== recieverAccountID){
                accountTO = account;
                found = true;
            }
        }
        for (auto &account: _bankaccounts) {
            if (account->getID() == ownerAccountNr) {
                if(!found){
                    throw runtime_error("No receiver account with ID " +to_string(recieverAccountID));
                }
                accountTO->transferTo(amount,ownerAccountNr,recieverAccountID,message);
                account->transfer(amount,ownerAccountNr,recieverAccountID,message,DateTime());
                //account->addActivity(Activity("transfered ",amount));
                return;
            }
            throw runtime_error("No account with ID " + to_string(ownerAccountNr) + " found");
        }
    } catch (runtime_error &e) {
        cerr << e.what() << endl;
    }
}

void bank::interestPayment(DateTime date) {
    //TODO
}

bool bank::isAccountValid(int accountID) {
    for (auto &account:_bankaccounts) {
        if(account->getID() == accountID){
            return true;
        }
    }
    return false;
}

bool bank::isCustomerValid(int userID) {
    for (auto &user:_owners) {
        if(user.getID() == userID){
            return true;
        }
    }
    return false;
}

string bank::getstatement(int accountID) {
    //TODO: PINCODE?
    try {
        for (auto &account: _bankaccounts) {
            if (account->getID() == accountID) {
                account->addActivity(Activity("stament"));
                return account->statement();
            }
        }
        throw runtime_error(&"No account was found with the id "[accountID]);
    } catch (runtime_error &e) {
        cerr << e.what() << endl;
    }
}

string bank::listOfAccounts() {
    ostringstream os;
    for (auto &account: _bankaccounts) {
        os << account->toString() << "\n";
    }
    return os.str();
}

void bank::newCustomer(string name, Address address) {
    owner newuser(name, address);

    try {
        for (auto &user: _owners)
            if (newuser == user) {
                throw runtime_error("Customer already exists");
            }
    } catch (runtime_error &e) {
        cerr << e.what() << endl;
    }
    _owners.push_back(newuser);
}

void bank::removeCustomer(int id) {
    try {
        for (int i = 0; i < _owners.size(); i++) {
            if (_owners[i].getID() == id) {
                _owners.erase(_owners.begin() + i);
                return;
            }
        }
        throw runtime_error("No customers was found with the id " + to_string(id));
    } catch (runtime_error &e) {
        cerr << e.what() << endl;
    }
}

void bank::editCustomer(int id, string name, Address adress) {
    owner newOwner(name,adress);
    try {
        for (int i = 0; i < _owners.size(); i++) {
            if (_owners[i].getID() == id) {
                _owners[i] = newOwner;
                return;
            }
        }
        throw runtime_error("No customer was found with the id " + to_string(id));
    } catch (runtime_error &e) {
        cerr << e.what() << endl;
    }
}

string bank::getAction(int accountID) {
    try {
        for (auto &account: _bankaccounts) {
            if (account->getID() == accountID) {
                account->addActivity(Activity("Viewed activities"));
                auto activities = account->getActivities();
                ostringstream os;
                for(auto &activity : activities){
                    os<<activity->toString() << endl;
                }
                return os.str();
            }
        }
        throw runtime_error(&"No account was found with the id "[accountID]);
    } catch (runtime_error &e) {
        cerr << e.what() << endl;
    }
}

