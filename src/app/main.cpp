#include <ctime>
#include <iostream>

using namespace std;

#include <libapp/pwgen.h>

#define N 10

int main()
{
    srand(time(NULL));
    gen_sym();
    help_message();
    return 0;
}