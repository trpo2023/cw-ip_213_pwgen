#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include <libapp/list.h>
#include <libapp/macr.h>
#include <libapp/pwgen.h>

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    int idx = 0;
    int check = checkArgs(argc, argv, &idx);
    if (check) {
        if (check == 1) {
            cout << "Error: Few arguments" << endl;
            return 1;
        }

        if (check == 2) {
            cout << "Error: wrong password length" << endl;
            return 2;
        }

        if (check == 3) {
            cout << "Error: wrong password count" << endl;
            return 3;
        }

        if (check == 4) {
            cout << "Error: unexpected argument \"" << argv[idx] << "\""
                 << endl;
            return 4;
        }

        if (check == 5) {
            cout << "Error: expected \"--help\" " << endl;
            return 5;
        }
    }

    if (argc >= 4) {
        listPassword(generateSeveralParam(argc, argv), atoi(argv[2]));
    }
    return 0;
}
