#include <iostream>
#include <unistd.h>
#include <vector>
#include "Bankaccount.h"
using namespace std;
int main() {
    Giro g;
    Savingsaccount s;
    g.payIn(350.5);
    //sleep(5);
    g.payIn(32.5);
    g.withdrawl(150);
    g.withdrawl(500);
    g.withdrawl(12.50);
    g.transfer(50,"DE49234093890","EDEKA");
    s.withdrawl(50);
    s.payIn(100.50);
    s.withdrawl(50.53);
    s.withdrawl(51);

    //cout <<g.statement()<<endl;
    //cout<<s.statement()<<endl;
    std::vector<Bankaccount*> DKB;
    for (int i = 0; i < 10; ++i) {
        DKB.push_back(new Giro(-1));
        DKB.push_back(new Savingsaccount());
    }
    DKB.push_back(&g);
    DKB.push_back(&s);
    for (int i = 0; i < 22; ++i) {
        DKB[i]->payIn(i);
        DKB[i]->withdrawl(i+1);
        cout<<DKB[i]->statement()<<endl;
        //cout<<DKB.size()<<endl;
    }

    return 0;
}
