#include <clocale>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string.h>

#include "macr.h"
#include "sort.h"

using namespace std;

char getRandChar(char start, char end)
{
    return (char)(start + rand() % (end - start + 1));
}

void helpMessage(void)
{
    setlocale(LC_ALL, "Russian");
    cout << "\nЗапуск: make run ARGS=\"[PW_LEN] [NUM_OF_PW] [OPTION]\", где:\
        \n[OPTION] – параметры пароля (аргументы командной строки).\
        \n[PW_LEN] – длина генерируемого пароля.\
        \n[NUM_OF_PW] – количество генерируемых паролей\
        \n\nОписание аргументов командной строки:\
        \n• -0, – сгенерированный пароль будет содержать только цифры.\
        \n• -A,  – сгенерированный пароль будет содержать только заглавные буквы.\
        \n• -a, – cгенерированный пароль будет содержать только строчные буквы.\
        \n• -symbols – сгенерированный пароль будет содержать только символы.\
        \n• -Aa – сгенерированный пароль будет содержит заглавные и строчные буквы.\
        \n• -word – добавляет в пароль случайное слово.\
        \n• -help – распечатать справочное сообщение.\
" << endl;
}

char genSym(void)
{
    char* symbols = new char[SYM];
    int k = 0;
    for (char j = '!'; j <= '/'; j++) {
        symbols[k++] = j;
    }
    for (char j = ':'; j <= '@'; j++) {
        symbols[k++] = j;
    }
    for (char j = '['; j <= '`'; j++) {
        symbols[k++] = j;
    }
    char sym = symbols[rand() % SYM];
    delete[] symbols;
    return sym;
}

char genUpLow(void)
{
    char* symbols = new char[LET];
    int k = 0;
    for (char j = 'A'; j <= 'Z'; j++) {
        symbols[k++] = j;
    }
    for (char j = 'a'; j <= 'z'; j++) {
        symbols[k++] = j;
    }
    char sym = symbols[rand() % LET];
    delete[] symbols;
    return sym;
}

char** generateDefault(void)
{
    char** passwords = new char*[ROW];
    for (int i = 0; i < ROW; i++) {
        passwords[i] = new char[COL];
    }
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            passwords[i][j] = getRandChar('!', 'z');
        }
    }
    return passwords;
}

void genPassword(int start, int end, bool flag, char *password, char** args, int size, int* p) {
    for (int i = start; i < end; i++) {
        int k = i;
        if(flag) 
            k = rand() % (size);
        if (string(args[k]) == "-0")
            password[(*p)++] = getRandChar('0', '9');
        else if (string(args[k]) == "-A")
            password[(*p)++] = getRandChar('A', 'Z');
        else if (string(args[k]) == "-a")
            password[(*p)++] = getRandChar('a', 'z');
        else if (string(args[k]) == "-Aa")
            password[(*p)++] = genUpLow();
        else if (string(args[k]) == "-symbols")
            password[(*p)++] = genSym();
    }
}

char** generateSeveralParam(int count, char** values)
{
    const int passwordLength = atoi(values[1]);
    if (passwordLength == 0) {
        cout << "\nError: wrong password length" << endl;
        return NULL;
    }
    int passwordCount = atoi(values[2]);
    if (atoi(values[2]) == 0) {
        cout << "\nError: wrong password count" << endl;
        return NULL;
    }
    char** passwords = (char**)malloc(passwordCount * sizeof(char*));
    char** args = (char**)malloc((count - 3) * sizeof(char*));
    for (int i = 0; i < count - 3; i++) {
        args[i] = (char*)malloc(strlen(values[i + 3]) * sizeof(char));
        strcpy(args[i], values[i + 3]);
    }
    int newSize = 0;
    char** sortsArgs = countingSort(args, count - 3, &newSize);
    for (int g = 0; g < passwordCount; g++) {
        int p = 0;
        passwords[g] = (char*)malloc(passwordLength * sizeof(char));
        genPassword(0, newSize, false, passwords[g], sortsArgs, newSize, &p);
        genPassword(newSize, passwordLength, true, passwords[g], sortsArgs, newSize, &p);
        // for (int i = 0; i < newSize; i++) {
        //     if (string(sortsArgs[i]) == "-0")
        //         passwords[g][p++] = getRandChar('0', '9');
        //     else if (string(sortsArgs[i]) == "-A")
        //         passwords[g][p++] = getRandChar('A', 'Z');
        //     else if (string(sortsArgs[i]) == "-a")
        //         passwords[g][p++] = getRandChar('a', 'z');
        //     else if (string(sortsArgs[i]) == "-Aa")
        //         passwords[g][p++] = genUpLow();
        //     else if (string(sortsArgs[i]) == "-symbols")
        //         passwords[g][p++] = genSym();
        // }
        // for (int i = newSize; i < passwordLength; i++) {
        //     int k = rand() % (newSize);
        //     if (string(sortsArgs[k]) == "-0")
        //         passwords[g][p++] = getRandChar('0', '9');
        //     else if (string(sortsArgs[k]) == "-A")
        //         passwords[g][p++] = getRandChar('A', 'Z');
        //     else if (string(sortsArgs[k]) == "-a")
        //         passwords[g][p++] = getRandChar('a', 'z');
        //     else if (string(sortsArgs[k]) == "-Aa")
        //         passwords[g][p++] = genUpLow();
        //     else if (string(sortsArgs[k]) == "-symbols")
        //         passwords[g][p++] = genSym();
        // }
    }
    for (int i = 0; i < count - 3; i++)
        free(args[i]);
    free(args);

    for (int i = 0; i < newSize; i++)
        free(sortsArgs[i]);
    free(sortsArgs);
    return passwords;
}
