#include <iostream>

using namespace std;

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
