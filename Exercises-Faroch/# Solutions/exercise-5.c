/**
 * @file exercise-5.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief Make a program to print your full name to the terminal.
 *        Your full name shall be a string defined as a macro in the command line when you compile your program.
 *
 *        To compile and run the program in a terminal run:
 *              gcc exercise-7.c -D FULL_NAME='"Faroch Mehri"' -o exercise-7 && ./exercise-7
 *
 * @version 0.1
 * @date 2021-10-02
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdio.h>

int main(void)
{
#ifndef FULL_NAME
#error FULL_NAME is required. Define FULL_NAME when you compile the program
#else
    (void)printf("%s\n", FULL_NAME);
#endif

    return 0;
}
