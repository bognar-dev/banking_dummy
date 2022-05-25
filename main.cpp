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
    cout << " (10) Interest balance\n\n";
    cout << " (11) Exit\n";
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
            Bank.readFromFile("data.dat");
            // lesen aus Datei
        } else if (choice == 2) {
            Bank.writeToFile("data.dat");
            // schreiben in Datei
        } else if (choice == 3) {
            //===========================================================
            int choice2;
                    do{
                        choice2 = stammdatenMenue();
                    if (choice2 == 1) {
                        //new customer
                        //Bank.newCustomer("Hans", Address("Mullerstr",33,"41065"));
                    } else if (choice2 == 2) {
                        //delete customer
                    }else if(choice2 == 3){
                        //change customer

                    }else if (choice2 == 4){
                        // new account
                    } else if (choice2 == 5) {
                        // delete account
                    } else if (choice2 != 6) {
                        cout << "no valid input!\n";
                    }}while(choice2 != 6);
            //============================================================
            } else if (choice == 4) {   // einzahlen
            } else if (choice == 5) {   // auszahlen
            } else if (choice == 6) {   // überweisen
            } else if (choice == 7) {   // Kontoauszug anzeigen
            } else if (choice == 8) {
            //cout<<Bank.customerList()<<endl;// Kundenliste anzeigen
            } else if (choice == 9) {
            // Kontenliste anzeigen
            //Bank.listOfAccounts();
            } else if (choice == 10) {  // Zinsgutschrift
            } else if (choice != 11)
                cout << "no valid input!\n";
        }
        while (choice != 11);
    }

