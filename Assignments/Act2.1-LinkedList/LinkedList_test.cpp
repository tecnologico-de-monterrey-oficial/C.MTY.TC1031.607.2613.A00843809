#include <iostream>
#include "LinkedList.h"
using namespace std;

int main(){
    LinkedList<string> list;
    list.push_front("b");
    list.push_front("a");
    list.push_back("c");
    list.push_front("@");
    list.insert(2, "x");
    list.print();

    return 0;
}