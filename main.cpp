// *******************************************************************
// main.cpp           (Hauptprogamm zum Bank-Beispiel)
// *******************************************************************

#include <iostream>
#include <string>
#include <cfloat>
#include "bank.h"

using namespace std;
// *******************************************************************
string stringInput(string message){

}

int intInput(string message,long long int minLimit = LONG_LONG_MIN,long long int maxLimit = LONG_LONG_MAX){
    std::string line;
    int num;
    //split onto multiple lines for readability
    while((std::cout << message <<" :") //make sure the user knows what you expect
          &&    std::getline(std::cin, line)
          &&    !(std::istringstream{line} >> num)
                && !(std::istringstream{line} >> num)
                && (num < minLimit || num > maxLimit)
            )//construct a stringstream from `line` and read it into `num`
             //this loop continues on bad input and ends on good input
    {
        std::cerr << "Invalid input, try again." << std::endl; //let the user know they made a mistake
    }
    //hooray, we can use `num`!
    return num;
}

// *******************************************************************
float floatInput(string message,float minLimit = FLT_MIN,float maxLimit = FLT_MAX){
    std::string line;
    float num;
    //split onto multiple lines for readability
    while((std::cout << message <<endl) //make sure the user knows what you expect
          &&    std::getline(std::cin, line)
          &&    !(std::istringstream{line} >> num)
          && !(std::istringstream{line} >> num)
          && (num < minLimit || num > maxLimit)
            )//construct a stringstream from `line` and read it into `num`
        //this loop continues on bad input and ends on good input
    {
        std::cerr << "Invalid input, try again." << std::endl; //let the user know they made a mistake
    }
    //hooray, we can use `num`!
    return num;
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
    cout << " (11) Get Account Activities\n\n";
    cout << " (12) Exit\n";
    cout << "------------------------------------------------\n";
    int choice;
    choice = intInput("Please Choose",1,12);
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
    choice = intInput("Please Choose",1,6);

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
                    string street;
                    string postcode;
                    int nr;
                    cout << "please enter the name" << endl;
                    getline(cin,name);
                    cout <<"please enter the street" << endl;
                    getline(cin,street);
                    nr = intInput("please enter your house number",0);
                    cout << "please enter the postcode" <<endl;
                    getline(cin,postcode);
                    Bank.newCustomer(name,Address(street,nr,postcode));

                    //Bank.newCustomer("Hans", Address("Mullerstr",33,"41065"));
                } else if (choice2 == 2) {
                    //delete customer
                    int id;
                    id = intInput("Give the userID to delete the user",0);
                    Bank.removeCustomer(id);
                } else if (choice2 == 3) {
                    //change customer
                    int id;
                    cout << "Give the userID to change the user" << endl;
                    cin >> id;
                    string name;
                    string street;
                    string postcode;
                    int nr;
                    cout << "please enter the name" << endl;
                    cin >> name;
                    cout <<"please enter the street" << endl;
                    cin >> street;
                    nr = intInput("please enter your house number");
                    cout << "please enter the postcode" <<endl;
                    cin>>postcode;
                    Bank.editCustomer(id, name, Address(street,nr,postcode));

                } else if (choice2 == 4) {
                    int id;
                    int choice3;
                    float balance;
                    id = intInput("Give the userID to Add an account",1);
                    balance = floatInput("give starting Balance",0);
                    choice3 = intInput("for Giro enter 1, for Savingsaccount 2",1,2);
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
                    number = intInput("Please provide the account number to delete",9000);
                    Bank.removeAccount(number);
                } else if (choice2 != 6) {
                    cout << "no valid input!\n";
                }
            } while (choice2 != 6);
            //============================================================
        } else if (choice == 4) {
            float amount;
            int accountNr;
            accountNr = intInput("Which account you want to payIn? (acountNr)",9000);
            amount = floatInput("please enter the amount you want to payIn",0);
            Bank.payIn(accountNr, amount);
            // einzahlen
        } else if (choice == 5) {
            float amount;
            int accountNr;
            accountNr = intInput("Which account you want to withdrawl from? (acountNr)",9000);
            amount = floatInput("please enter the amount you want to withdrawl",0);
            Bank.withdraw(accountNr, amount);// auszahlen
        } else if (choice == 6) {
            float amount;
            int accountNr;
            int accountNrTo;
            string message;
            accountNr = intInput("Which account you want to transfer from? (acountNr)",9000);
            accountNrTo = intInput("Which account you want to transfer to? (acountNr)",9000);
            amount =floatInput("please enter the amount you want to transfer",0);
            cout << "please enter a message :" << endl;
            getline(cin,message);
            Bank.transfer(accountNr, accountNrTo, amount, message);
            choice = 0;
        } else if (choice == 7) {
            int accountNr;
            accountNr = intInput("Please give the account number to get your statement",9000);
            cout << Bank.getstatement(accountNr) << endl;// Kontoauszug anzeigen
        } else if (choice == 8) {
            cout << Bank.customerList() << endl;// Kundenliste anzeigen
        } else if (choice == 9) {
            // Kontenliste anzeigen
            cout << Bank.listOfAccounts() << endl;
        } else if (choice == 10) {  // Zinsgutschrift
        } else if (choice == 11) {
            int accountNr;
            accountNr = intInput("Please give the account number to get your activities",9000);
            cout << Bank.getAction(accountNr) << endl;
            //get account activities
        } else if (choice == 0) {
        } else if (choice != 12) {
            cout << "no valid input!\n";
        }
    } while (choice != 12);
}

