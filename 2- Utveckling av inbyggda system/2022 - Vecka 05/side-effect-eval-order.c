#include <stdio.h>
#include <stdint.h>

#define CUBE(X) ((X) * (X) * (X))

int k = 20;

static inline int cube(int i)
{
    return i * i * i;
}

int funcA()
{
    k = k + 10;

    return k;
}

int add(int a, int b)
{
    return a + b;
}

int main()
{
    int p = 3;
    uint8_t x = 3;

    // Compare the outputs of the 2 following statements.
    printf("%d, %d, %d, %d\n", x++, x, ++x, x); // Multiple side effects on x and the order is not guaranteed.
    printf("%d, %d, %d, %d\n", p++, p, ++p, p); // Multiple side effects on p and the order is not guaranteed.

    uint8_t y = 10, z = 2 * y; // The order is guaranteed.
    printf("%d - %d\n", y, z); // 10, 20

    int i = 2;
    int a = 81 / CUBE(++i); // 3 Side effects on i
    int b = 81 / cube(++i); // One side effect on i

    p = i++ * i++; // 2 side effects on i
    printf("p = %d\n", p);

    int m = 5;
    p = add(m, ++m); // is this 5 + 6, or 6 + 6?
    printf("p = %d\n", p);

    printf("k = %d\n", funcA()); // A persistent side effect on k

    m = 5, p = 5;
    p = p++;                          // 2 side effects on p
    m = ++m;                          // 2 side effects on m
    printf("m = %d, p = %d\n", m, p); // Compare m and p
}
