#include <ctime>
#include <iostream>

using namespace std;

#include <libapp/pwgen.h>

#define N 10

int main()
{
    srand(time(NULL));
    genSym();
    helpMessage();
    return 0;
}