#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include <libapp/pwgen.h>

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));
    if(argc == 3) {
        char* k = generateOneParam(argv);
        cout << k << endl;
    }
    return 0;
}