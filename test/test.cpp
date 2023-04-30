#include <ctest.h>

#include <libapp/pwgen.h>

CTEST (check_generation, check_numbers)
{
    char real = getRandChar('0', '9');
    int left = (int) '0';
    int right = (int) '9';
    ASSERT_INTERVAL(left, right, real);
}