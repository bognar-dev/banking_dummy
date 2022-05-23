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
    cout << "| Hauptmenü:             |\n";
    cout << "+------------------------+\n\n";
    cout << "  (1) Daten aus einer Datei einlesen\n";
    cout << "  (2) Daten in einer Datei abspeichern\n";
    cout << "  (3) Stammdaten-Dialog\n";
    cout << "  (4) einzahlen\n";
    cout << "  (5) auszahlen\n";
    cout << "  (6) überweisen\n";
    cout << "  (7) Kontoauszug anzeigen\n";
    cout << "  (8) Kundenliste anzeigen\n";
    cout << "  (9) Kontenliste anzeigen\n";
    cout << " (10) Zinsgutschrift\n\n";
    cout << " (11) Programm beenden\n";
    cout << "------------------------------------------------\n";
    cout << " Ihre Auswahl? ";

    int auswahl;
    cin >> auswahl;

    return auswahl;
}

// *******************************************************************
int stammdatenMenue() {
    cout << "\n\n";
    cout << "+------------------------+\n";
    cout << "| Stammdaten pflegen:    |\n";
    cout << "+------------------------+\n\n";
    cout << " (1) Kunde anlegen\n";
    cout << " (2) Kunde entfernen\n";
    cout << " (3) Kundendaten ändern\n";
    cout << " (4) Konto anlegen\n";
    cout << " (5) Konto entfernen\n\n";
    cout << " (6) Abbruch\n";
    cout << " -----------------------------------------------\n";
    cout << " Ihre Auswahl?\n";

    int auswahl;
    cin >> auswahl;

    return auswahl;
}

// *******************************************************************
int main() {
    int auswahl;

    do {
        auswahl = hauptMenue();
        if (auswahl == 1) {          // lesen aus Datei
        } else if (auswahl == 2) {   // schreiben in Datei
        } else if (auswahl == 3) {   // Stammdaten-Dialog
        } else if (auswahl == 4) {   // einzahlen
        } else if (auswahl == 5) {   // auszahlen
        } else if (auswahl == 6) {   // überweisen
        } else if (auswahl == 7) {   // Kontoauszug anzeigen
        } else if (auswahl == 8) {   // Kundenliste anzeigen
        } else if (auswahl == 9) {   // Kontenliste anzeigen
        } else if (auswahl == 10) {  // Zinsgutschrift
        } else if (auswahl != 11)
            cout << "unbekannte Auswahl\n";
    } while (auswahl != 11);
}

