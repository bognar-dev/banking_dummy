// *******************************************************************
// main.cpp           (Hauptprogamm zum Bank-Beispiel)
// *******************************************************************

#include <iostream>
#include <string>
#include "bank.h"

using namespace std;

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
    cout << " (11) Get Account Activities\n\n";
    cout << " (12) Exit\n";
    cout << "------------------------------------------------\n";
    cout << " Please choose: ";

    int choice;
    cin >> choice;

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
    cout << " Please Choose: \n";

    int choice;
    cin >> choice;

    return choice;
}

// *******************************************************************
int main() {
    int choice;
    bank Bank("DKB");
    do {
        choice = hauptMenue();
        if (choice == 1) {
            Bank.readFromFile("data.dat","users.dat");
            // lesen aus Datei
        } else if (choice == 2) {
            Bank.writeToFile("data.dat","users.dat");
            // schreiben in Datei
        } else if (choice == 3) {
            //===========================================================
            int choice2;
            do {
                choice2 = stammdatenMenue();
                if (choice2 == 1) {
                    //new customer
                    string name;
                    Address address;
                    cout << "please enter the name" << endl;
                    cin >> name;
                    cout << "please enter the address (Street,NR,Address)" << endl;
                    cin >> address;
                    Bank.newCustomer(name, address);

                    //Bank.newCustomer("Hans", Address("Mullerstr",33,"41065"));
                } else if (choice2 == 2) {
                    //delete customer
                    int id;
                    cout << "Give the userID to delete the user" << endl;
                    cin >> id;
                    Bank.removeCustomer(id);
                } else if (choice2 == 3) {
                    //change customer
                    int id;
                    cout << "Give the userID to change the user" << endl;
                    cin >> id;
                    string name;
                    Address address;
                    cout << "please enter the name" << endl;
                    cin >> name;
                    cout << "please enter the address (Street,NR,Address)" << endl;
                    cin >> address;
                    Bank.editCustomer(id, name, address);

                } else if (choice2 == 4) {
                    int id;
                    int choice3;
                    float balance;
                    cout << "Give the userID to Add an account" << endl;
                    cin >> id;
                    cout << "give starting Balance" << endl;
                    cin >> balance;
                    cout << "for Giro enter 1, for Savingsaccount 2" << endl;
                    cin >> choice3;
                    if (choice3 == 1) {
                        float dispolimit;
                        cout << "What is the dispolimit?" << endl;
                        cin >> dispolimit;
                        Bank.createGiro(id, balance, dispolimit);
                    } else if (choice3 == 2) {
                        Bank.createSavingsAccount(id, balance);
                    }

                } else if (choice2 == 5) {
                    // delete account
                    int number;
                    cout << "Please provide the account number to delete" << endl;
                    cin >> number;
                    Bank.removeAccount(number);
                } else if (choice2 != 6) {
                    cout << "no valid input!\n";
                }
            } while (choice2 != 6);
            //============================================================
        } else if (choice == 4) {
            float amount;
            int accountNr;
            cout << "Which account you want to payIn? (acountNr)" << endl;
            cin >> accountNr;
            cout << "please enter the amount you want to payIn" << endl;
            cin >> amount;
            Bank.payIn(accountNr, amount);
            // einzahlen
        } else if (choice == 5) {
            float amount;
            int accountNr;
            cout << "Which account you want to withdrawl from? (acountNr)" << endl;
            cin >> accountNr;
            cout << "please enter the amount you want to withdrawl" << endl;
            cin >> amount;
            Bank.withdraw(accountNr, amount);// auszahlen
        } else if (choice == 6) {
            float amount;
            int accountNr;
            int accountNrTo;
            string message;
            cout << "Which account you want to transfer from? (acountNr)" << endl;
            cin >> accountNr;
            cout << "Which account you want to transfer to? (acountNr)" << endl;
            cin >> accountNrTo;
            cout << "please enter the amount you want to transfer" << endl;
            cin >> amount;// überweisen
            cout << "please enter a message :" << endl;
            cin >> message;
            Bank.transfer(accountNr, accountNrTo, amount, message);
            choice = 0;
        } else if (choice == 7) {
            int accountNr;
            cout << "Please give the account number to get your statement" << endl;
            cin >> accountNr;
            cout << Bank.getstatement(accountNr) << endl;// Kontoauszug anzeigen
        } else if (choice == 8) {
            cout << Bank.customerList() << endl;// Kundenliste anzeigen
        } else if (choice == 9) {
            // Kontenliste anzeigen
            cout << Bank.listOfAccounts() << endl;
        } else if (choice == 10) {  // Zinsgutschrift
        } else if (choice == 11) {//get account activities
        } else if (choice == 0) {
        } else if (choice != 12) {
            cout << "no valid input!\n";
        }
    } while (choice != 12);
}

