#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    s.insert(0, "a");
    s.insert(1, "b");
    s.insert(2, "c");
    s.insert(3, "b");
    s.insert(4, "e");
    assert(s.remove("b") == 2);
    assert(s.size() == 3);
    string x;
    assert(s.get(0, x)  &&  x == "a");
    assert(s.get(1, x)  &&  x == "c");
    assert(s.get(2, x)  &&  x == "e");

    Sequence s1;
    s1.insert(0, "paratha");
    s1.insert(0, "focaccia");
    Sequence s2;
    s2.insert(0, "roti");
    s1.swap(s2);
    assert(s1.size() == 1  &&  s1.find("roti") == 0  &&  s2.size() == 2  &&
           s2.find("focaccia") == 0  &&  s2.find("paratha") == 1);
    cout << "Passed all tests" << endl;
}

