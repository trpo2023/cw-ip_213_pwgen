#include <cstdlib>
#include <ctest.h>
#include <ctime>
#include <cstring>

#include <libapp/pwgen.h>
#include <libapp/macr.h>
#include <libapp/sort.h>

#define N 28

CTEST(check_generation, number)
{
    srand(time(NULL));
    char real = getRandChar('0', '9');
    int left = (int)'0';
    int right = (int)'9';
    ASSERT_INTERVAL(left, right, real);
}

CTEST(check_generation, symbol)
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
    srand(time(NULL));
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

CTEST(check_generation, upper_case)
{
    srand(time(NULL));
    char real = getRandChar('A', 'Z');
    int left = (int)'A';
    int right = (int)'Z';
    ASSERT_INTERVAL(left, right, real);
}

CTEST(check_generation, lower_case)
{
    srand(time(NULL));
    char real = getRandChar('a', 'z');
    int left = (int)'a';
    int right = (int)'z';
    ASSERT_INTERVAL(left, right, real);
}

CTEST(check_generation, up_and_low_case)
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
    srand(time(NULL));
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
    ASSERT_EQUAL(expected, real);
    for (int i = 0; i < lenArgs; i++) {
        free(args[i]);
    }
    free(args);
}

CTEST(check_password, default_gen) 
{
    int real = 0;
    int expected = 0;
    srand(time(NULL));
    char** passwords = generateDefault();
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            if ((passwords[i][j] < '!') || (passwords[i][j] > 'z')) {
                real = 1;
            }
        }
    }
    ASSERT_EQUAL(expected, real);
}