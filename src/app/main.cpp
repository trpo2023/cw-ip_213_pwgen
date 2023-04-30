#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include <libapp/pwgen.h>

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    bool numbersOnly = false, lowRegistrOnly = false, upRegistrOnly = false,
         upLowRegistr = false, symbols = false;
    int passwordLength = 0;
    string password;
    if (argc >= 2)
        passwordLength = atoi(argv[1]);
    if (argc >= 3) {
        if (string(argv[2]) == "-0")
            numbersOnly = true;
        if (string(argv[2]) == "-A")
            upRegistrOnly = true;
        if (string(argv[2]) == "-a")
            lowRegistrOnly = true;
        if (string(argv[2]) == "-Aa")
            upLowRegistr = true;
        if (string(argv[2]) == "-symbols")
            symbols = true;
    }
    if (numbersOnly) {
        for (int i = 0; i < passwordLength; i++)
            password += getRandChar('0', '9');
    }

    else if (upRegistrOnly) {
        for (int i = 0; i < passwordLength; i++)
            password += getRandChar('A', 'Z');
    }

    else if (lowRegistrOnly) {
        for (int i = 0; i < passwordLength; i++)
            password += getRandChar('a', 'z');
    }

    else if (upLowRegistr) {
        for (int i = 0; i < passwordLength; i++)
            password += genAa();
    }

    else if (symbols) {
        for (int i = 0; i < passwordLength; i++)
            password += genSym();
    }
    cout << "Password: " << password << endl;
    return 0;
}