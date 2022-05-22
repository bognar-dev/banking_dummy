#include <iostream>
#include <unistd.h>
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
    s.withdrawl(50);
    s.payIn(100);
    s.withdrawl(50);

    cout <<g.statement()<<endl;
    cout<<s.statement()<<endl;

    return 0;
}
