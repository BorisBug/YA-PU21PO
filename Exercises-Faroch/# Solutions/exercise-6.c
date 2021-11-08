/**
 * @file exercise-6.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief Display size. min and max of the basic data types
 * @version 0.1
 * @date 2021-10-03
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdio.h>
#include <limits.h>
#include <float.h>

enum color
{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    WHITE,
    BLACK
};

int main(void)
{
    // Size, min and max values of char
    printf("[char] size: %lu, min: %d and max: %d\n", sizeof(char), CHAR_MIN, CHAR_MAX);

    // Size, min and max values of signed char
    printf("[signed char] size: %lu, min: %d and max: %d\n", sizeof(signed char), SCHAR_MIN, SCHAR_MAX);

    // Size, min and max values of unsigned char
    printf("[unsigned char] size: %lu, min: %u and max: %u\n", sizeof(unsigned char), 0U, UCHAR_MAX);

    // Size, min and max values of short int
    printf("[short int] size: %lu, min: %d and max: %d\n", sizeof(short int), SHRT_MIN, SHRT_MAX);

    // Size, min and max values of unsigned short int
    printf("[unsigned short int] size: %lu, min: %u and max: %u\n", sizeof(unsigned short int), 0U, USHRT_MAX);

    // Size, min and max values of int
    printf("[int] size: %lu, min: %d and max: %d\n", sizeof(int), INT_MIN, INT_MAX);

    // Size, min and max values of unsigned int
    printf("[unsigned int] size: %lu, min: %u and max: %u\n", sizeof(unsigned int), 0U, UINT_MAX);

    // Size, min and max values of long int
    printf("[long int] size: %lu, min: %ld and max: %ld\n", sizeof(long int), LONG_MIN, LONG_MAX);

    // Size, min and max values of unsigned long int
    printf("[unsigned long int] size: %lu, min: %lu and max: %lu\n", sizeof(unsigned long int), 0UL, ULONG_MAX);

    // Size, min and max values of long long int
    printf("[long long int] size: %lu, min: %lld and max: %lld\n", sizeof(long long int), LLONG_MIN, LLONG_MAX);

    // Size, min and max values of usigned long long int
    printf("[unsigned long long int] size: %lu, min: %llu and max: %llu\n", sizeof(unsigned long long int), 0ULL, ULLONG_MAX);

    // Size, min and max values of float
    printf("[float] size: %lu, min: %g and max: %g\n", sizeof(float), -FLT_MAX, FLT_MAX);

    // Size, min and max values of double
    printf("[double] size: %lu, min: %g and max: %g\n", sizeof(double), -DBL_MAX, DBL_MAX);

    // Size, min and max values of long double
    printf("[long double] size: %lu, min: %Lg and max: %Lg\n", sizeof(long double), -LDBL_MAX, LDBL_MAX);

    // Size of enum color
    printf("[enum color] size: %lu\n", sizeof(enum color));

    return 0;
}
