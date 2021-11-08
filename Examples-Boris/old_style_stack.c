#include <stdio.h>

// In this file you can see "old style C".
// Here it is easy to see how the parameters of the function where placed into the
// stack before creating its own vaiables also in stack, creating an enclosed scope.

int add(a,b)
int a;
int b;
{
    int r = a + b;
    return r;
}

int main(argc, argv)
int argc;
char **argv;
{
    int num1 = 10;
    int num2 = 20;
    printf("%d + %d = %d\n", num1, num2, add(num1,num2));
    return 0;
}