#include <cstdlib>
#include <string.h>

#include <libapp/macr.h>

char** countingSort(char** arr, int oldSize, int* newSize)
{
    int size = 0;
    int count = 0;
    int index = 0;
    char** args = (char**)malloc(sizeof(char*));
    for (int i = 0; i < oldSize; i++) {
        bool flag = false;
        for (int j = 0; j < oldSize; j++) {
            if (i == j) {
                break;
            }

            if ((strcmp(arr[i], arr[j])) == 0) {
                flag = true;
                break;
            }
        }

        if (!flag) {
            args = (char**)realloc(args, (++size) * sizeof(char*));
            args[index] = (char*)malloc(strlen(arr[i]) * sizeof(char));
            strcpy(args[index], arr[i]);
            index += 1;
            count += 1;
        }
    }
    *(newSize) = count;
    return args;
}
