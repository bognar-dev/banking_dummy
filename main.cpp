// *******************************************************************
// main.cpp           (Hauptprogamm zum Bank-Beispiel)
// *******************************************************************

#include <iostream>
#include <string>
#include <cfloat>
#include "Observer.h"
#include "bank.h"

using namespace std;

// *******************************************************************
string stringInput(string message) {
    string line;
    cout << message << endl;
    getline(cin, line);
    return line;

}

int intInput(string message, long long int minLimit = LONG_LONG_MIN, long long int maxLimit = LONG_LONG_MAX) {
    std::string line;
    int num = 0;
    //split onto multiple lines for readability
    std::cout << message << endl;
    while (!(std::istringstream{line} >> num)
           && (num <= minLimit || num >= maxLimit)
           && std::getline(std::cin, line)
            ) {
        std::istringstream is{line};
        if ((is >> num) && !(is >> line) && (num >= minLimit && num <= maxLimit)) {
            return num;
        }
        std::cerr << "Invalid input, try again." << std::endl;
    }
    return 0;

}

// *******************************************************************
float floatInput(string message, float minLimit = FLT_MIN, float maxLimit = FLT_MAX) {
    std::string line;
    float num = 0;
    //split onto multiple lines for readability
    std::cout << message << endl;
    while (!(std::istringstream{line} >> num)
           && (num <= minLimit || num >= maxLimit)
           && std::getline(std::cin, line)
            ) {
        std::istringstream is{line};
        if ((is >> num) && !(is >> line) && (num >= minLimit && num <= maxLimit)) {
            return num;
        }
        std::cerr << "Invalid input, try again." << std::endl;
    }
}

// *******************************************************************
int hauptMenue() {
    cout << "\n\n";
    cout << "+------------------------+\n";
    cout << "| Menu:             |\n";
    cout << "+------------------------+\n\n";
    cout << "  (1) Read from file\n";
    cout << "  (2) Write to file\n";
    cout << "  (3) Data-Dialog\n";
    cout << "  (4) PayIn\n";
    cout << "  (5) Withdraw\n";
    cout << "  (6) Transfer\n";
    cout << "  (7) Get statement\n";
    cout << "  (8) Show users\n";
    cout << "  (9) Show accounts\n";
    cout << " (10) Interest balance\n";
    cout << " (11) Get Account Activities\n";
    cout << " (12) Toggle autosave\n\n";
    cout << " (13) Exit\n";
    cout << "------------------------------------------------\n";
    int choice;
    choice = intInput("Please Choose", 1, 13);
    return choice;
}

// *******************************************************************
int stammdatenMenue() {
    cout << "\n\n";
    cout << "+------------------------+\n";
    cout << "| Data menu:    |\n";
    cout << "+------------------------+\n\n";
    cout << " (1) New customer\n";
    cout << " (2) Delete customer\n";
    cout << " (3) Change customer\n";
    cout << " (4) New account\n";
    cout << " (5) Delete account\n\n";
    cout << " (6) Return\n";
    cout << " -----------------------------------------------\n";

    int choice;
    choice = intInput("Please Choose", 1, 6);

    return choice;
}

// *******************************************************************
int main() {
    int choice;
    bank Bank("DKB");
    Observer obs("users.dat","data.dat");
    Observer obs1("obsusr.dat","obsacc.dat");
    do {
        choice = hauptMenue();
        if (choice == 1) {
            Bank.readFromFile("data.dat", "users.dat");
            Bank.notifyObservers();
            // lesen aus Datei
        } else if (choice == 2) {
            Bank.writeToFile("data.dat", "users.dat");
            Bank.notifyObservers();
            // schreiben in Datei
        } else if (choice == 3) {
            //===========================================================
            int choice2;
            do {
                choice2 = stammdatenMenue();
                if (choice2 == 1) {
                    //new customer
                    string name;
                    string street;
                    string postcode;
                    int nr;
                    name = stringInput("please enter the name");
                    street = stringInput("please enter the street");
                    nr = intInput("please enter your house number", 0);
                    postcode = stringInput("please enter the postcode");
                    Bank.newCustomer(name, Address(street, nr, postcode));
                    Bank.notifyObservers();
                    //Bank.newCustomer("Hans", Address("Mullerstr",33,"41065"));
                } else if (choice2 == 2) {
                    //delete customer
                    int id;
                    id = intInput("Give the userID to delete the user", 0);
                    Bank.removeCustomer(id);
                    Bank.notifyObservers();
                } else if (choice2 == 3) {
                    //change customer
                    int id;
                    id = intInput("Give the userID to change the user", 1);
                    string name;
                    string street;
                    string postcode;
                    int nr;
                    name = stringInput("please enter the name");
                    street = stringInput("please enter the street");
                    nr = intInput("please enter your house number");
                    postcode = stringInput("please enter the postcode");
                    Bank.editCustomer(id, name, Address(street, nr, postcode));
                    Bank.notifyObservers();

                } else if (choice2 == 4) {
                    int id;
                    int choice3 = 0;
                    float balance;
                    id = intInput("Give the userID to Add an account", 1);
                    balance = floatInput("give starting Balance", 0);

                    do {
                        choice3 = intInput("for Giro enter 1, for Savingsaccount 2", 1, 2);
                        if (choice3 == 1) {
                            float dispolimit;
                            dispolimit = floatInput("What is the dispolimit?", 0);
                            Bank.createGiro(id, balance, dispolimit);
                            Bank.notifyObservers();
                        } else if (choice3 == 2) {
                            Bank.createSavingsAccount(id, balance);
                            Bank.notifyObservers();
                        }
                    } while ((choice3 != 1) && (choice3 != 2));
                    // final else statement add
                } else if (choice2 == 5) {
                    // delete account
                    int number;
                    number = intInput("Please provide the account number to delete", 9000);
                    Bank.removeAccount(number);
                    Bank.notifyObservers();
                } else if (choice2 != 6) {
                    cout << "no valid input!\n";
                }
            } while (choice2 != 6);
            //============================================================
        } else if (choice == 4) {
            float amount;
            int accountNr;
            int PIN;
            accountNr = intInput("Which account you want to payIn? (acountNr)", 9000);
            PIN = intInput("Please enter your PIN 4 digits", 0);
            while (!(Bank.PinVerification(accountNr, PIN))) {
                PIN = intInput("Wrong PIN, please try again \n To exit press 0", 0);
            }
            amount = floatInput("please enter the amount you want to payIn", 0);
            Bank.payIn(accountNr, amount);
            // einzahlen
        } else if (choice == 5) {
            float amount;
            int accountNr;
            int PIN;
            accountNr = intInput("Which account you want to withdrawl from? (acountNr)", 9000);
            PIN = intInput("Please enter your PIN 4 digits", 0);
            while (!(Bank.PinVerification(accountNr, PIN))) {
                PIN = intInput("Wrong PIN, please try again \n To exit press 0", 0);
            }
            amount = floatInput("please enter the amount you want to withdrawl", 0);
            Bank.withdraw(accountNr, amount);// auszahlen
        } else if (choice == 6) {
            float amount;
            int accountNr;
            int accountNrTo;
            string message;
            int PIN;
            accountNr = intInput("Which account you want to transfer from? (acountNr)", 9000);
            PIN = intInput("Please enter your PIN 4 digits", 0);
            while (!(Bank.PinVerification(accountNr, PIN))) {
                PIN = intInput("Wrong PIN, please try again \n To exit press 0", 0);
            }
            accountNrTo = intInput("Which account you want to transfer to? (acountNr)", 9000);
            amount = floatInput("please enter the amount you want to transfer", 0);
            message = stringInput("please enter a message :");
            Bank.transfer(accountNr, accountNrTo, amount, message);
            choice = 0;
        } else if (choice == 7) {
            int accountNr;
            int PIN;
            accountNr = intInput("Please give the account number to get your statement", 9000);
            PIN = intInput("Please enter your PIN 4 digits", 0);
            while (!(Bank.PinVerification(accountNr, PIN))) {
                PIN = intInput("Wrong PIN, please try again. Press Escape to leave", 0);
            }
            cout << Bank.getstatement(accountNr) << endl;// Kontoauszug anzeigen
        } else if (choice == 8) {
            cout << Bank.customerList() << endl;// Kundenliste anzeigen
        } else if (choice == 9) {

            // Kontenliste anzeigen
            cout << Bank.listOfAccounts() << endl;
        } else if (choice == 10) {  // Zinsgutschrift
        } else if (choice == 11) {
            int accountNr;
            int PIN;
            accountNr = intInput("Please give the account number to get your activities", 9000);
            PIN = intInput("Please enter your PIN 4 digits", 0);
            while (!(Bank.PinVerification(accountNr, PIN))) {
                PIN = intInput("Wrong PIN, please try again. Press Escape to leave", 0);
            }
            cout << Bank.getAction(accountNr) << endl;
            //get account activities
        } else if (choice == 0) {
        } else if (choice == 12) {
            bool save = intInput("For turning on autosave press (1) for switching off (0)",0,1);
            if(save){
                Bank.logInObserver(obs);
                Bank.logInObserver(obs1);
                cout<<"Autosave is on";
            }
            else{
                Bank.logOutObserver(obs);
                cout<<"Autosave was switched off"<<endl;
            }

        } else if (choice != 13) {
            cout << "no valid input!\n";
        }
    } while (choice != 13);
    //Bank.writeToFile("data.dat", "users.dat");
}

