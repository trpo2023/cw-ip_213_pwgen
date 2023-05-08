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

void generateRandomWord(char* word)
{
    FILE* file = fopen("words.txt", "r");
    if (file == NULL) {
        return;
    }
    int size = 1;
    char* buffer = (char*)malloc(SIZE * sizeof(char));
    char** words = (char**)malloc(sizeof(char*));
    while (fgets(buffer, SIZE, file)) {
        words = (char**)realloc(words, (size) * sizeof(char*));
        words[size - 1] = (char*)malloc((strlen(buffer)) * sizeof(char));
        strcpy(words[size - 1], buffer);
        size++;
    }
    fclose(file);
    free(buffer);
    int idx = rand() % (size - 1);
    word = (char*)realloc(word, strlen(words[idx]) * sizeof(char));
    strcpy(word, words[idx]);
    for (int i = 0; i < (size - 1); i++)
        free(words[i]);
    free(words);
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
    bool hasWord = false;
    for (int g = 0; g < passwordCount; g++) {
        int p = 0;
        passwords[g] = (char*)malloc(passwordLength * sizeof(char));
        for (int i = 0; i < newSize; i++) {
            if (string(sortsArgs[i]) == "-word") {
                hasWord = true;
            }
        }
        if (hasWord) {
            for (int i = 0; i < newSize - 1; i++) {
                if (string(sortsArgs[i]) == "-0")
                    passwords[g][p++] = getRandChar('0', '9');
                else if (string(sortsArgs[i]) == "-A")
                    passwords[g][p++] = getRandChar('A', 'Z');
                else if (string(sortsArgs[i]) == "-a")
                    passwords[g][p++] = getRandChar('a', 'z');
                else if (string(sortsArgs[i]) == "-Aa")
                    passwords[g][p++] = genUpLow();
                else if (string(sortsArgs[i]) == "-symbols")
                    passwords[g][p++] = genSym();
            }
            for (int i = newSize - 1; i < passwordLength; i++) {
                int k = rand() % (count - 3);
                if (string(sortsArgs[k]) == "-0")
                    passwords[g][p++] = getRandChar('0', '9');
                else if (string(sortsArgs[k]) == "-A")
                    passwords[g][p++] = getRandChar('A', 'Z');
                else if (string(sortsArgs[k]) == "-a")
                    passwords[g][p++] = getRandChar('a', 'z');
                else if (string(sortsArgs[k]) == "-Aa")
                    passwords[g][p++] = genUpLow();
                else if (string(sortsArgs[k]) == "-symbols")
                    passwords[g][p++] = genSym();
                else
                    i--;
            }
            char* temp = (char*)malloc(sizeof(char));
            generateRandomWord(temp);
            passwords[g] = (char*)realloc(
                    passwords[g],
                    (passwordLength + strlen(temp)) * sizeof(char));
            int idx = 0;
            for (int i = passwordLength; idx < (int)strlen(temp); i++) {
                passwords[g][i] = temp[idx++];
            }
            free(temp);

        } else {
            for (int i = 0; i < newSize; i++) {
                if (string(sortsArgs[i]) == "-0")
                    passwords[g][p++] = getRandChar('0', '9');
                else if (string(sortsArgs[i]) == "-A")
                    passwords[g][p++] = getRandChar('A', 'Z');
                else if (string(sortsArgs[i]) == "-a")
                    passwords[g][p++] = getRandChar('a', 'z');
                else if (string(sortsArgs[i]) == "-Aa")
                    passwords[g][p++] = genUpLow();
                else if (string(sortsArgs[i]) == "-symbols")
                    passwords[g][p++] = genSym();
            }
            for (int i = newSize; i < passwordLength; i++) {
                int k = rand() % (count - 3);
                if (string(sortsArgs[k]) == "-0")
                    passwords[g][p++] = getRandChar('0', '9');
                else if (string(sortsArgs[k]) == "-A")
                    passwords[g][p++] = getRandChar('A', 'Z');
                else if (string(sortsArgs[k]) == "-a")
                    passwords[g][p++] = getRandChar('a', 'z');
                else if (string(sortsArgs[k]) == "-Aa")
                    passwords[g][p++] = genUpLow();
                else if (string(sortsArgs[k]) == "-symbols")
                    passwords[g][p++] = genSym();
            }
        }
    }
    for (int i = 0; i < count - 3; i++)
        free(args[i]);
    free(args);

    for (int i = 0; i < newSize; i++)
        free(sortsArgs[i]);
    free(sortsArgs);
    return passwords;
}
