#include <iostream>
#include <string>
// for codebloks:
// #include "BigNum.h"

// for others:
#include "BigNum.cpp"
using namespace std;



int main()
{
    BigNum A;
    A = 56;
    BigNum B("78");
    A += 871;

    if(B > A)
    {
        cout << "B > A" << endl;
    }


    if(B <= A)
        cout << "B <= A" << endl;

    cout << "A = ";
    A.printDelimiter();
    cout << "B = ";
    B.printDelimiter();
    BigNum Q;
    Q = A * "8";
    cout << "A * 8 = ";
    Q.printDelimiter();
    Q += 2;
    Q.printDelimiter();
    BigNum BIG = Q + 2;
    BIG.printDelimiter();

    BigNum INPUTBN;
    cin >> INPUTBN;
    cout << "Input BN: " << INPUTBN << " cascading" << endl;

    A = "1299999999955555555558888888888888877777777";
    B = "8888888887777777777744444444455555555555522";
    cout << "A = ";
    A.printDelimiter();
    cout << "B = ";
    B.printDelimiter();
    Q = A * B;
    cout << "A * B = ";
    Q.printDelimiter();
    return 0;
}
