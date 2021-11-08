#include <stdio.h>
#include <ctype.h>

int my_isdigit(int c)
{
    return c >= '0' && c <= '9';
//  return c >= 48 && c <= 57;
}

int char_to_number(char c)
{
    if(!my_isdigit(c))
    {
        printf("What!!\n");
        return 0;
    }

    return c - '0';
}

int main()
{
    int number;

    number = 0;
    printf("1) %d\n", number);

    number = '0';
    printf("2) %d\n", number);

    printf("3) %d\n", char_to_number('0'));
    printf("4) %d\n", char_to_number('1'));
    printf("5) %d\n", char_to_number('2'));
    printf("6) %d\n", char_to_number('A')); // not what we want

    printf("---------\n");

    // what i want
    number = 7 - 1;
    printf("A) %d\n", number);

    // what i have
    number = '7' - '1';
    printf("B) %d\n", number); // --> 6 ??

    // the problem is combining ASCII & numbers
    number = '7' - 1;
    printf("C) %d\n", number); // --> 54 ??

    // how to solve it
    number = char_to_number('7') - char_to_number('1');
    printf("D) %d\n", number);


    return 0;
}
