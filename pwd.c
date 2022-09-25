#include "pwd.h"

void pwd()
{
    char buffer[1000];
    getcwd(buffer, 1000);
    printf("%s\n", buffer);
}