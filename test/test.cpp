#include <cstdlib>
#include <ctest.h>
#include <cstring>

#include "libapp/pwgen.h"
#include "libapp/sort.h"

#define N 28

using namespace std;

CTEST(check_generation, check_numbers)
{
    char real = getRandChar('0', '9');
    int left = (int)'0';
    int right = (int)'9';
    ASSERT_INTERVAL(left, right, real);
}

CTEST(check_generation, check_symbol)
{
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
    for (int i = 0; i < N; i++) {
        if (x == string[i]) {
            real = 1;
            break;
        }
    }
    const int expected = 1;
    delete[] string;
    ASSERT_EQUAL(expected, real);
}

CTEST(check_generation, check_upper_case)
{
    char real = getRandChar('A', 'Z');
    int left = (int)'A';
    int right = (int)'Z';
    ASSERT_INTERVAL(left, right, real);
}

CTEST(check_generation, check_lower_case)
{
    char real = getRandChar('a', 'z');
    int left = (int)'a';
    int right = (int)'z';
    ASSERT_INTERVAL(left, right, real);
}

CTEST(check_generation, check_up_and_low)
{
    char* string = new char[N];
    int k = 0;
    for (char j = 'A'; j <= 'Z'; j++) {
        string[k++] = j;
    }
    for (char j = 'a'; j <= 'z'; j++) {
        string[k++] = j;
    }
    int real = 0;
    int x = genUpLow();
    for (int i = 0; i < N; i++) {
        if (x == string[i]) {
            real = 1;
            break;
        }
    }
    const int expected = 1;
    delete[] string;
    ASSERT_EQUAL(expected, real);
}

CTEST (check_arguments, check_sort) 
{
    int expected = 0, real = 0, idx = 0, size = 0;
    const char* arr[] = {"-a", "-A", "-A", "-0", "--symbols", "-a"};
    const char* sortArr[] = {"-a", "-A", "-0", "--symbols"};
    int lenArgs = sizeof(arr) / sizeof(arr[0]);
    int lenSortArgs = sizeof(sortArr) / sizeof(sortArr[0]);
    char** args = (char**)malloc(sizeof(char*));
    for (int i = 0; i < lenArgs; i++) {
        args = (char**)realloc(args, (++size) * sizeof(char*));
        args[idx] = (char*)malloc(strlen(arr[i]) * sizeof(char));
        strcpy(args[idx], arr[i]);
        idx += 1;
    }
    int newSize = 0;
    int check[lenSortArgs];
    char** sortArgs = countingSort(args, lenArgs, &newSize);
    for (int i = 0; i < newSize; i++) {
        if (strcmp(sortArr[i], sortArgs[i]) == 0) {
            check[i] = 0;
        }
    }
    for (int i = 0; i < lenSortArgs; i++) {
        if (check[i] != 0) {
            real = 1;
        }
    }
    for (int i = 0; i < lenArgs; i++) {
        free(args[i]);
    }
    free(args);
    ASSERT_EQUAL(expected, real);
}