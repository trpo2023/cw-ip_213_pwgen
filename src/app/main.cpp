#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include <libapp/list.h>
#include <libapp/pwgen.h>

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    if (argc == 1) {
        char** passwords = generateDefault();
        listDefPassword(passwords);
    } else if (argc == 2) {
        if (string(argv[1]) == "-help") {
            helpMessage();
        }
        
        else if (string(argv[1]) == "-word") { 
            cout << generateRandomWord();
        } 
        
        else {
            cout << "Error: few arguments" << endl;
            return 1;
        }
    } else if (argc == 3) {
        cout << generateOneParam(argv) << endl;
    } else if (argc > 3) {
        cout << generateSeveralParam(argc, argv) << endl;
    }
    return 0;
}