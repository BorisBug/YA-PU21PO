/**
 * @file exercise-4.c
 * @author Faroch Mehri (faroch.mehri@ya.se)
 * @brief The Hello World program.
 *        To compile the program in a terminal run: gcc exercise-6.c -o exercise-6
 *        To run the program run: ./exercise-6
 * @version 0.1
 * @date 2021-10-02
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdio.h> // The C standard io library

/**
 * @brief The entry point to the program
 *
 * @return int The exit code of the program returned to the operation system
 */
int main(void)
{
    /**
     * Print Hello World to the standard output
     * The returned value of printf is discard.
     */
    (void)printf("Hello World!\n");

    return 0; // The program is completed successfully. Therefore 0 is returned to the OS.
}
