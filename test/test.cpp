#include <ctest.h>
#include <cstdlib>

#include "libapp/pwgen.h"
#define N 28

CTEST(symbol, check_ok) {
    char* string = new char[N];
    int k = 0;
    for (char j = '!'; j <= '/'; j++) {
        string[k++] = j;
    }
    for (char j = ':'; j <= '@'; j++) {
        string[k++] = j;
    }
    for (char j = '['; j <= '`'; j++) {
        string[k++] = j;
    }
    int real = 0;
    int x = genSym();
    for(int i = 0; i < N; i++) {
        if(x == string[i]) {
            real = 1;
            break;
        }
    }
    const int expected = 1;
    delete[] string;
    ASSERT_EQUAL(expected, real);
}