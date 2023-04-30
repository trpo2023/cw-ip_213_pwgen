#include <clocale>
#include <iostream>

using namespace std;

void hello(void)
{
    cout << "Hello" << endl;
}

void help_message(void)
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
char gen_sym()
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
