#include <iostream>
#include <unistd.h>
#include "Bankaccount.h"
using namespace std;
int main() {
    Giro g;
    g.payIn(350.5);
    //sleep(5);
    g.payIn(32.5);
    g.withdrawl(150);
    g.withdrawl(500);
    cout<<g.balance()<<endl;


    cout <<g.statement()<<endl;

    return 0;
}
