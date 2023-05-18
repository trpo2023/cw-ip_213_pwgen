#include <cstdlib>
#include <cstring>
#include <ctest.h>
#include <ctime>
#include <iostream>

#include <libapp/list.h>
#include <libapp/macr.h>
#include <libapp/pwgen.h>
#include <libapp/sort.h>

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
    char* string = new char[SYM];
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
    for (int i = 0; i < SYM; i++) {
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
    char* string = new char[SYM];
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
    for (int i = 0; i < SYM; i++) {
        if ((x < 'A') || (x > 'Z')) {
            if (x < 'A') {
                real = 1;
                break;
            } else if ((x > 'Z') && ((x < 'a') || (x > 'z'))) {
                real = 1;
                break;
            }
        }
    }
    const int expected = 0;
    delete[] string;
    ASSERT_EQUAL(expected, real);
}

CTEST(check_password, default_gen)
{
    int real = 0;
    int expected = 0;
    srand(time(NULL));
    char** passwords = generateDefault();
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            if ((passwords[i][j] < '!') || (passwords[i][j] > 'z')) {
                real = 1;
                break;
            }
    for (int i = 0; i < ROW; i++)
        free(passwords[i]);
    free(passwords);
    ASSERT_EQUAL(expected, real);
}

CTEST(check_password, lower_case)
{
    char** args = (char**)malloc(4 * sizeof(char*));
    for (int i = 0; i < 4; i++) {
        args[i] = (char*)malloc(2 * sizeof(char));
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
            if ((passwords[i][j] < 'a') || (passwords[i][j] > 'z')) {
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

CTEST(check_password, upper_case)
{
    char** arg = (char**)malloc(4 * sizeof(char*));
    for (int i = 0; i < 4; i++) {
        arg[i] = (char*)malloc(2 * sizeof(char));
    }
    int expected = 0;
    int real = 0;
    strcpy(arg[1], "10");
    strcpy(arg[2], "1");
    strcpy(arg[3], "-A");
    srand(time(NULL));
    char** passwords = generateSeveralParam(4, arg);
    for (int i = 0; i < atoi(arg[2]); i++)
        for (int j = 0; j < atoi(arg[1]); j++) {
            if ((passwords[i][j] < 'A') || (passwords[i][j] > 'Z')) {
                real = 1;
                break;
            }
        }
    for (int i = 0; i < 4; i++) {
        free(arg[i]);
        if (i < 1)
            free(passwords[i]);
    }
    free(arg);
    free(passwords);
    ASSERT_EQUAL(expected, real);
}

CTEST(check_password, symbols)
{
    int expected = 0;
    int real = 0;
    char** args = new char*[4];
    for (int i = 0; i < 4; i++) {
        args[i] = new char[25];
    }
    strcpy(args[0], "test");
    strcpy(args[1], "10");
    strcpy(args[2], "1");
    strcpy(args[3], "--symbols");
    srand(time(NULL));
    char** password = generateSeveralParam(4, args);
    for (int i = 0; i < atoi(args[2]); i++) {
        for (int j = 0; j < atoi(args[1]); j++) {
            if (password[i][j] < '!') {
                real = 1;
                break;
            } else if ((password[i][j] > '/') && (password[i][j] < ':')) {
                real = 1;
                break;
            } else if ((password[i][j] > '@') && (password[i][j] < '[')) {
                real = 1;
                break;
            } else if (password[i][j] > '`') {
                real = 1;
                break;
            }
        }
    }
    delete[] args;
    for (int i = 0; i < 1; i++) {
        delete[] password[i];
    }
    delete[] password;
    ASSERT_EQUAL(expected, real);
}

CTEST(check_password, numbers)
{
    int expected = 0;
    int real = 0;
    char** args = (char**)malloc(4 * sizeof(char*));
    for (int i = 0; i < 4; i++) {
        args[i] = (char*)malloc(2 * sizeof(char));
    }
    strcpy(args[1], "10");
    strcpy(args[2], "1");
    strcpy(args[3], "-0");
    srand(time(NULL));
    char** passwords = generateSeveralParam(4, args);
    for (int i = 0; i < atoi(args[2]); i++)
        for (int j = 0; j < atoi(args[1]); j++) {
            if ((passwords[i][j] < '0') || (passwords[i][j] > '9')) {
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

CTEST(check_password, up_and_low_case)
{
    int expected = 0;
    int real = 0;
    char** args = (char**)malloc(4 * sizeof(char*));
    for (int i = 0; i < 4; i++) {
        args[i] = (char*)malloc(2 * sizeof(char));
    }
    strcpy(args[1], "10");
    strcpy(args[2], "1");
    strcpy(args[3], "-Aa");
    srand(time(NULL));
    char** passwords = generateSeveralParam(4, args);
    for (int i = 0; i < atoi(args[2]); i++)
        for (int j = 0; j < atoi(args[1]); j++) {
            if (passwords[i][j] < 'A') {
                real = 1;
                break;
            } else if ((passwords[i][j] > 'Z') && (passwords[i][j] < 'a')) {
                real = 1;
                break;
            } else if (passwords[i][j] > 'z') {
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

CTEST(check_args, sort)
{
    int expected = 0, real = 0, idx = 0, size = 0;
    const char* arr[] = {"-a", "-A", "-A", "-0", "--symbols", "-a"};
    const char* sortArr[] = {"-a", "-A", "-0", "--symbols"};
    int lenArgs = sizeof(arr) / sizeof(arr[0]);
    char** args = (char**)malloc(sizeof(char*));
    for (int i = 0; i < lenArgs; i++) {
        args = (char**)realloc(args, (++size) * sizeof(char*));
        args[idx] = (char*)malloc(strlen(arr[i]) * sizeof(char));
        strcpy(args[idx], arr[i]);
        idx += 1;
    }
    int newSize = 0;
    char** sortArgs = countingSort(args, lenArgs, &newSize);
    for (int i = 0; i < newSize; i++) {
        if (strcmp(sortArr[i], sortArgs[i]) != 0) {
            real = 1;
            break;
        }
    }

    for (int i = 0; i < lenArgs; i++) {
        free(args[i]);
    }
    free(args);
    ASSERT_EQUAL(expected, real);
}

CTEST(check_args, correct)
{
    int expected = 0, idx = 0, size = 4;
    char** arr = new char*[size];
    for (int i = 0; i < size; i++) {
        arr[i] = new char[size];
    }
    strcpy(arr[0], "app");
    strcpy(arr[1], "4");
    strcpy(arr[2], "6");
    strcpy(arr[3], "-a");
    int real = checkArgs(size, arr, &idx);
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    ASSERT_EQUAL(expected, real);
}

CTEST(check_args, one_param_uncor)
{
    int expected = 5, idx = 0, size = 2;
    char** arr = new char*[size];
    for (int i = 0; i < size; i++) {
        arr[i] = new char[4];
    }
    strcpy(arr[0], "app");
    strcpy(arr[1], "-help");
    int real = checkArgs(size, arr, &idx);
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    ASSERT_EQUAL(expected, real);
}

CTEST(check_args, two_param)
{
    int expected = 1, idx = 0, size = 3;
    char** arr = new char*[size];
    for (int i = 0; i < size; i++) {
        arr[i] = new char[4];
    }
    strcpy(arr[0], "app");
    strcpy(arr[1], "4");
    strcpy(arr[2], "6");
    int real = checkArgs(size, arr, &idx);
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    ASSERT_EQUAL(expected, real);
}

CTEST(check_args, three_param_len)
{
    int expected = 2, idx = 0, size = 4;
    char** arr = new char*[size];
    for (int i = 0; i < size; i++) {
        arr[i] = new char[size];
    }
    strcpy(arr[0], "app");
    strcpy(arr[1], "0");
    strcpy(arr[2], "6");
    strcpy(arr[3], "-a");
    int real = checkArgs(size, arr, &idx);
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    ASSERT_EQUAL(expected, real);
}

CTEST(check_args, three_param_count)
{
    int expected = 3, idx = 0, size = 4;
    char** arr = new char*[size];
    for (int i = 0; i < size; i++) {
        arr[i] = new char[size];
    }
    strcpy(arr[0], "app");
    strcpy(arr[1], "2");
    strcpy(arr[2], "0");
    strcpy(arr[3], "-a");
    int real = checkArgs(size, arr, &idx);
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    ASSERT_EQUAL(expected, real);
}

CTEST(check_args, four_param_uncor)
{
    int expected = 4, idx = 0, size = 4;
    char** arr = new char*[size];
    for (int i = 0; i < size; i++) {
        arr[i] = new char[size];
    }
    strcpy(arr[0], "app");
    strcpy(arr[1], "4");
    strcpy(arr[2], "6");
    strcpy(arr[3], "-Tok");
    int real = checkArgs(size, arr, &idx);
    for (int i = 0; i < size; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    ASSERT_EQUAL(expected, real);
}
