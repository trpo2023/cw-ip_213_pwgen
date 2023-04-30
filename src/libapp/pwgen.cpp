#include <cstdlib>
#include <ctime>

using namespace std;

char getRandchar(char start, char end)
{
    return (char)(start + rand() % (end - start + 1));
}
