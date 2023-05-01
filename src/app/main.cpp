#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include <libapp/list.h>
#include <libapp/macr.h>
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
        } else if (string(argv[1]) == "-word") {
            cout << generateRandomWord();
        } else {
            cout << "Error: few arguments\n";
            return 2;
        }
    } else if (argc == 3) {
        cout << "Error: few arguments\n";
        return 2;
    } else if (argc >= 4) {
        listPassword(generateSeveralParam(argc, argv), atoi(argv[2]));
    }
    return 0;
}