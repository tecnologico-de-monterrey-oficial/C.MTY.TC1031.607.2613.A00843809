#include <iostream>
#include "Fraction.h"
using namespace std;

int main(){
    int x = 42;
    int* p = &x;
    cout << "x: " << x << endl;
    cout << "&x: " << &x << endl;
    cout << "p: " << p << endl;
    cout << "*p: " << *p << endl;

    int* q = new int(5);
    cout << "q: " << q << endl;
    cout << "*q: " << *q << endl;

    delete q;
    cout << "q: " << q << endl;
    cout << "*q: " << *q << endl;

    Fraction* f = new Fraction(2,3);
    cout << f << endl;

    return 0;
}