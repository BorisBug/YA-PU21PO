#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////
// length

int get_str_length(const char *ptr)
{
    return strlen(ptr);
}

void test_str_len(const char *str)
{
    int length = get_str_length(str);  // Function to get the length of the string
    printf("The length of %s is %d\n", str, length);
}

void play_with_len()
{
    test_str_len("123-456-789"); // --> 11
    test_str_len("123"); // --> 3
    test_str_len("ABCDEFG"); // --> 7
}

//////////////////////////////
// long

long get_long(const char *str)
{
    char *next = NULL;
    long value = strtol(str, &next, 10);
    return value;
}

long play_with_get_long()
{
    long y, m, d;
    const char *str;
    char *next = NULL;

    printf("\n\n\n");

    str = "1975-12-21";
    printf("Parsing: %s\n", str);

    y = strtol(str, &next, 10);
    printf("year = %ld next = '%s'\n", y, next);

    next++;
    m = strtol(next, &next, 10);
    printf("month = %ld next = '%s'\n", m, next);

    next++;
    d = strtol(next, &next, 10);
    printf("day = %ld next = '%s'\n", d, next);

 //   value = strtol(str, &next, 10);
 //   printf("value = %ld next = '%s'\n", value, next);

    return y;
}
/*
                 BINARY
 128 64 32 16   8 4 2 1          
   8  4  2  1   8 4 2 1   DEC    HEX
   _  _  _  _ . _ _ _ _
                0 0 0 0 = 0   -> 0x00
                0 0 1 0 = 2   -> 0x02
                0 1 0 0 = 4   -> 0x04
                1 0 1 0 = 10  -> 0x0A
                1 1 1 0 = 14  -> 0x0E
                1 1 1 1 = 15  -> 0x0F
   0  0  1  0   0 0 0 0 = 32  -> 0x20
   1  0  0  1   1 1 0 1 = 157 -> 0x9D

    0001 0000 0001 0000 = 4112 > 0x1010  
*/

int main()
{
    play_with_len();
    
    play_with_get_long();

    printf("bye!\n");

    return 0;
}

