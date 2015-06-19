#include <iostream>
#include<cstring>
using namespace std;

#include "Hex.cpp"

int main ()
{
    Hex a("a42-", 4);
    Hex b("25", 2);
    (a%b).print();
}
