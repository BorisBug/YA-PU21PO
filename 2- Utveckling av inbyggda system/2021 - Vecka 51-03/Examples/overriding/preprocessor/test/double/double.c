#include <stdio.h>
#include <string.h>

#include "double.h" // Don't include double.h if you want to use the original getchar

static char buffer[BUFSIZ] = {0};

int get_char(void)
{
    static int index = 0;
    return buffer[index++];
}

void set_iobuf(const char *str)
{
    strcpy(buffer, str);
}
