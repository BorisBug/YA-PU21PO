#include <stdio.h>
#include "module.h"
#include <string.h>

#ifdef TEST
#include "double.h"
#endif

static char string[BUFSIZ + 1] = {0};

char *get_string(void)
{
    strcpy(string, "");

    int i = 0;
    char ch = 0;

    while ((i < BUFSIZ) && (ch != '\n') && (ch != EOF))
    {
        ch = getchar();
        string[i++] = ch;
    }

    return string;
}
