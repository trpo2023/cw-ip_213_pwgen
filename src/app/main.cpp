#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include <libapp/pwgen.h>

using namespace std;

int main(int argc, char** argv)
{
    srand(time(NULL));
    bool numbersOnly;
    bool lowRegistrOnly;
    bool upRegistrOnly;
    bool upLowRegistr;
    int passwordLength;
    string password;
    if (argc >= 2)
        passwordLength = stoi(argv[2]);

    if (argc >= 3 && string(argv[3]) == "-0") 
        numbersOnly = true;
    
    if (argc >= 3 && string(argv[3]) == "-A") 
        upRegistrOnly = true;

    if (argc >= 3 && string(argv[3]) == "-a")
        lowRegistrOnly = true;

    if (argc >= 3 && string(argv[3]) == "-a") 
        upLowRegistr = true;
    
    if (numbersOnly) {
        for (int i = 0; i < passwordLength; i++)
            password += getRandChar('0', '9');
    }  
    
    else if (upRegistrOnly) {
        for (int i = 0; i < passwordLength; i++)
            password += getRandChar('0', '9');
    }

    else if (lowRegistrOnly) {
        for (int i = 0; i < passwordLength; i++)
            password += getRandChar('0', '9');
    }

    else if (upLowRegistr) {
        for (int i = 0; i < passwordLength; i++)
            password += getRandChar('0', '9');
    }
    cout << "Password: " << password << endl;
    return 0;
}