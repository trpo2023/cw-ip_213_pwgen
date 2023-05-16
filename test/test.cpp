#include <cstdlib>
#include <ctest.h>
#include <cstring>
#include <ctime>
#include <iostream>

#include <libapp/pwgen.h>
#include <libapp/macr.h>

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
        if ((x < 'A') || (x > 'Z')) {
            if(x < 'A') {
                real = 1;
                break;
            }
            else if((x > 'Z') && ((x < 'a') || (x > 'z'))) {
                real = 1;
                break;
            }
        }
    }
    const int expected = 0;
    delete[] string;
    ASSERT_EQUAL(expected, real);
}

CTEST(check_password, default_gen) {
    int real = 0;
    int expected = 0;
    srand(time(NULL));
    char** passwords = generateDefault();
    for(int i = 0; i < ROW; i++)
        for(int j = 0; j < COL; j++)
            if ((passwords[i][j] < '!') || (passwords[i][j] > 'z')) {
                real = 1;
                break;
            }
    for(int i = 0; i < ROW; i++)
        free(passwords[i]);
    free(passwords);
    ASSERT_EQUAL(expected, real);
}

CTEST(check_password, lower_case) {
    char **args = (char**)malloc(4*sizeof(char*));
    for(int i = 0; i < 4; i++) {
        args[i] = (char*)malloc(2*sizeof(char));
    }
    int expected = 0;
    int real = 0;
    strcpy(args[1], "10");
    strcpy(args[2], "1");
    strcpy(args[3], "-a");
    srand(time(NULL));
    char** passwords = generateSeveralParam(4, args);
    for (int i = 0; i < atoi(args[2]); i++)
        for (int j = 0; j < atoi(args[1]); j++) {
            if((passwords[i][j] < 'a') || (passwords[i][j] > 'z')) {
                real = 1;
                break;
            }
        }
    for (int i = 0; i < 4; i++) {
        free(args[i]);
        if(i < 1)
            free(passwords[i]);
    }
    free(args);
    free(passwords);
    ASSERT_EQUAL(expected, real);
}

CTEST(check_password, upper_case)
{
    char** args = (char**)malloc(4 * sizeof(char*));
    for (int i = 0; i < 4; i++) {
        args[i] = (char*)malloc(2 * sizeof(char));
    }
    int expected = 0;
    int real = 0;
    strcpy(args[1], "10");
    strcpy(args[2], "1");
    strcpy(args[3], "-A");
    srand(time(NULL));
    char** passwords = generateSeveralParam(4, args);
    for (int i = 0; i < atoi(args[2]); i++)
        for (int j = 0; j < atoi(args[1]); j++) {
            if ((passwords[i][j] < 'A') || (passwords[i][j] > 'Z')) {
                real = 1;
                break;
            }
        }
    for (int i = 0; i < 4; i++) {
        free(args[i]);
        if (i < 1)
            free(passwords[i]);
    }
    free(args);
    free(passwords);
    ASSERT_EQUAL(expected, real);
}