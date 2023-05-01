#include <clocale>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string.h>

#include "macr.h"

using namespace std;

char getRandChar(char start, char end)
{
    return (char)(start + rand() % (end - start + 1));
}

char* generateRandomWord(void)
{
    FILE *file = fopen("words.txt", "r");
    int size = 1;
    char *buffer = (char*) malloc(SIZE * sizeof(char));
    char **words = (char**)malloc(sizeof(char*));;
    while(fgets(buffer, SIZE, file)) {
        words = (char**) realloc(words, (size) * sizeof(char*));
        words[size - 1] = (char*) malloc((strlen(buffer))*sizeof(char));
        strcpy(words[size - 1], buffer);
        size++;
    }
    fclose(file);
    free(buffer);
    return words[rand() % (size-1)];   
}

void helpMessage(void)
{
    setlocale(LC_ALL, "Russian");
    cout << "\nЗапуск: make run ARGS=[pw_length] [number_of_pw] [OPTION], где:\
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

char* generateOneParam(char** argv)
{
    int passwordLength = atoi(argv[1]);
    if (passwordLength == 0) {
        cout << "\nError: wrong password length" << endl;
        return NULL;
    }
    char* password = (char*)malloc(passwordLength * sizeof(char));
    int p = 0;  
    if (string(argv[2]) == "-0") {
        for (int i = 0; i < passwordLength; i++)
            password[p++] = getRandChar('0', '9');
    } 
    else if (string(argv[2]) == "-A") {
        for (int i = 0; i < passwordLength; i++)
            password[p++] = getRandChar('A', 'Z');
    }
    else if (string(argv[2]) == "-a") {
        for (int i = 0; i < passwordLength; i++)
            password[p++] = getRandChar('a', 'z');
    }
    else if (string(argv[2]) == "-Aa") {
        for (int i = 0; i < passwordLength; i++)
            password[p++] = genUpLow();
    }
    else if (string(argv[2]) == "-symbols") {
        for (int i = 0; i < passwordLength; i++)
            password[p++] = genSym();
    }
    return password;
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

char* generateSeveralParam(int count, char** values)
{
    int passwordLength = atoi(values[1]);
    if (passwordLength == 0) {
        cout << "\nError: wrong password length" << endl;
        return NULL;
    }
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
            password[p++] = genUpLow();
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
            password[p++] = genUpLow();
        else if (string(args[k]) == "-symbols")
            password[p++] = genSym();
    }
    return password;
}

