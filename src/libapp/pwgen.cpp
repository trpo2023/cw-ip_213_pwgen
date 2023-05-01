#include <clocale>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string.h>

#include "macr.h"

using namespace std;

char getRandChar(char start, char end)
{
    return (char)(start + rand() % (end - start + 1));
}

void helpMessage(void)
{
    setlocale(LC_ALL, "Russian");
    cout << "Запуск: ./pwgen [OPTION] [pw_length] [number_of_pw], где:\
        \n[OPTION] – параметры пароля (аргументы командной строки).\
        \n[pw_length] – длина генерируемого пароля.\
        \n[number_of_pw] – количество генерируемых паролей\
        \nОписание аргументов командной строки\
        \n\t•	-0, – сгенерированный пароль будет содержать только цифры.\
        \n\t•	-A,  – сгенерированный пароль будет содержать только заглавные буквы.\
        \n\t•	-a, – cгенерированный пароль будет содержать только строчные буквы.\
        \n\t•	-symbols – сгенерированный пароль будет содержать только символы.\
        \n\t•	-Aa – сгенерированный пароль будет содержит заглавные и строчные буквы.\
        \n\t•	-word – добавляет в пароль случайное слово.\
        \n\t•	-help – распечатать справочное сообщение.\
" << endl;
}

char genSym()
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

char genAa()
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

char* generateOneParam(char** argv)
{
    bool numbersOnly = false, lowRegistrOnly = false, upRegistrOnly = false,
         upLowRegistr = false, symbols = false;
    int passwordLength = atoi(argv[1]);
    char* password = (char*)malloc(passwordLength * sizeof(char));
    if (string(argv[2]) == "-0")
        numbersOnly = true;
    if (string(argv[2]) == "-A")
        upRegistrOnly = true;
    if (string(argv[2]) == "-a")
        lowRegistrOnly = true;
    if (string(argv[2]) == "-Aa")
        upLowRegistr = true;
    if (string(argv[2]) == "-symbols")
        symbols = true;
    int p = 0;
    if (numbersOnly) {
        for (int i = 0; i < passwordLength; i++)
            password[p++] = getRandChar('0', '9');
    } else if (upRegistrOnly) {
        for (int i = 0; i < passwordLength; i++)
            password[p++] = getRandChar('A', 'Z');
    } else if (lowRegistrOnly) {
        for (int i = 0; i < passwordLength; i++)
            password[p++] = getRandChar('a', 'z');
    } else if (upLowRegistr) {
        for (int i = 0; i < passwordLength; i++)
            password[p++] = genAa();
    } else if (symbols) {
        for (int i = 0; i < passwordLength; i++)
            password[p++] = genSym();
    }
    return password;
}

char** generateDefault()
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

char* generateSeveralParam(int count, char** values)
{
    int passwordLength = atoi(values[1]);
    char* password = (char*)malloc(passwordLength * sizeof(char));
    char** args = (char**)malloc((count - 2) * sizeof(char*));
    for (int i = 0; i < count - 2; i++) {
        args[i] = (char*)malloc(strlen(values[i + 2]) * sizeof(char));
        strcpy(args[i], values[i + 2]);
    }
    int p = 0;
    for (int i = 0; i < count - 2; i++) {
        if (string(args[i]) == "-0")
            password[p++] = getRandChar('0', '9');
        else if (string(args[i]) == "-A")
            password[p++] = getRandChar('A', 'Z');
        else if (string(args[i]) == "-a")
            password[p++] = getRandChar('a', 'z');
        else if (string(args[i]) == "-Aa")
            password[p++] = genAa();
        else if (string(args[i]) == "-symbols")
            password[p++] = genSym();
    }

    for (int i = count - 2; i < passwordLength; i++) {
        int k = rand() % (count - 2);
        if (string(args[k]) == "-0")
            password[p++] = getRandChar('0', '9');
        else if (string(args[k]) == "-A")
            password[p++] = getRandChar('A', 'Z');
        else if (string(args[k]) == "-a")
            password[p++] = getRandChar('a', 'z');
        else if (string(args[k]) == "-Aa")
            password[p++] = genAa();
        else if (string(args[k]) == "-symbols")
            password[p++] = genSym();
    }
    return password;
}