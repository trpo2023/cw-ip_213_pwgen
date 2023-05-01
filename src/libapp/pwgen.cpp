#include <clocale>
#include <cstdlib>
#include <ctime>
#include <iostream>

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
    char* symbols = new char[28];
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
    char sym = symbols[rand() % 28];
    delete[] symbols;
    return sym;
}

char genAa()
{
    char* symbols = new char[52];
    int k = 0;
    for (char j = 'A'; j <= 'Z'; j++) {
        symbols[k++] = j;
    }
    for (char j = 'a'; j <= 'z'; j++) {
        symbols[k++] = j;
    }
    char sym = symbols[rand() % 52];
    delete[] symbols;
    return sym;
}

char* generateOneParam(char** argv)
{
    bool numbersOnly = false, lowRegistrOnly = false, upRegistrOnly = false, upLowRegistr = false, symbols = false;
    int passwordLength = 0;
    passwordLength = atoi(argv[1]);
    char *password = (char*)malloc(passwordLength*sizeof(char));
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
    }
    else if (upRegistrOnly) {
        for (int i = 0; i < passwordLength; i++)
            password[p++] = getRandChar('A', 'Z');
    }
    else if (lowRegistrOnly) {
        for (int i = 0; i < passwordLength; i++)
            password[p++] = getRandChar('a', 'z');
    }
    else if (upLowRegistr) {
        for (int i = 0; i < passwordLength; i++)
            password[p++] = genAa();
    }
    else if (symbols) {
        for (int i = 0; i < passwordLength; i++)
            password[p++] = genSym();
    }
    return password;
}