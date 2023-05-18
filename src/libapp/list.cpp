#include <iostream>

#include <libapp/macr.h>

void listDefPassword(char** passwords)
{
    printf("\n");
    for (int i = 0; i < ROW; i += 4) {
        printf("%s   %s   %s   %s\n",
               passwords[i],
               passwords[i + 1],
               passwords[i + 2],
               passwords[i + 3]);
    }
    printf("\n");
}

void listPassword(char* password)
{
    printf("%s\n", password);
}

void listPassword(char** passwords, int row)
{
    for (int i = 0; i < row; i++) {
        printf("%s\n", passwords[i]);
    }
}