#include <ctest.h>

#include "libapp/pwgen.h"

#define N 28

CTEST (check_generation, check_numbers)
{
    char real = getRandChar('0', '9');
    int left = (int) '0';
    int right = (int) '9';
    ASSERT_INTERVAL(left, right, real);


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
    ASSERT_EQUAL(expected, real);
}