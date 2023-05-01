#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include <libapp/pwgen.h>
#include <libapp/list.h>

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    if (argc == 1) {
        char** passwords = generateDefault();
        listDefPassword(passwords);
    } else if (argc == 2) {
        cout << "Error: few arguments" << endl;
        return 1;
    } else if (argc == 3) {
        char* k = generateOneParam(argv);
        cout << k << endl;
    }
    else
    return 0;
}