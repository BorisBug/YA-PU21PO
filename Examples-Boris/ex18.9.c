#include <stdio.h>

/*
Beskrivning
1. Create an int. Then, create a pointer that points at the address of this int with &.
   Finally, print both the pointer and the dereferenced value of the address the pointer is pointing at.

2. Create a function that returns the address a pointer you send in is pointing at.

3. Create a function that returns a string of the values at an address being sent into the function.
   Use a void-pointer to accept multiple types of input and translate it to chars.

4. Create a wild pointer and print it. The make it a null pointer and never speak of this again.

5. Create an array of five int-pointers. Point them all at the same number.
   Loop through the pointers, and add 2 to the number for each loop. Finally, print the number.

6. Redo the above task, but use a pointer to iterate through the array of pointers instead.

7. Create an array of structs. Use a pointer and +/- to change some values in the third,
   fifth and first structs in the list, in that order.

8. Create a multidimensional array with the dimensions 3/3.
   Loop through it and print all the values using pointers.

9. Create a pointer to a pointer
*/




/*
2. Create a function that returns the address a pointer you send in is pointing at.
Boris:
a) create a function
b) parameter is apointer.
c) return parameter.
*/

char *function_2(char *p)
{
    short int si = 0x012C; // 300
    printf("The value inside of %p is %d\n", &p, *p);
   // printf("%lu\n", sizeof(si));

    return p;
}

/*
3. Create a function that returns a string of the values at an address being sent into the function.
   Use a void-pointer to accept multiple types of input and translate it to chars.
*/
void function_3(void *mem, unsigned int size)
{
    unsigned char *c = mem;

    for(unsigned int i=0; i<size; i++)
    {
    //  printf("%u ", c[i]);
        printf("%02X ", c[i]);
    //  printf("%02X ", mem[i]);
    }

    printf("\n");
    //printf("%lu\n", sizeof(size));
}



void create_mem_file()
{
    FILE *file = fopen("mem.txt", "w+");
    int start = 0x2A00;
    fprintf(file, "addr\tvar\t\tvalue...\n");
    for(int i=start; i<start+400; i++)
        fprintf(file, "0x%04X\t.\t.\t.\n", i);
    fclose(file);
}

int main()
{
    //create_mem_file();

    /*1. Create an int. Then, create a pointer that points at the address of this int with &.
    Finally, print both the pointer and the dereferenced value of the address the pointer is pointing at.
    */
    printf("\n\n\n\n");

    printf("1) **********************\n");

    int a = 5; //--> sizeof = 4
    int *pa = &a;
    printf("a=%i  *pa=%i\n", a, *pa);

    /*
    2. Create a function that returns the address a pointer you send in is pointing at.
    Boris:
    a) create a function
    b) parameter is apointer.
    c) return parameter.
    */
    printf("2) **********************\n");

    char s2[10] = "abcdef";
    char *s22 = "ABCD";
    char *p2 = NULL;
    printf("s2 %p\n", s2);
    p2 = function_2(s2);
    printf("p2 %p\n", p2);

    /*
    3. Create a function that returns a string of the values at an address being sent into the function.
    Use a void-pointer to accept multiple types of input and translate it to chars.
    */

    printf("3) **********************\n");
    //char s3[6] = {10,20,30,40,50,60};
    char s3[6] = "Hello";

    function_3(s3, sizeof(s3));
    short sho3 = 0x012F; // 303
    function_3(&sho3, sizeof(sho3));
    long int3 = 0x00000000AABBCCDD;
    function_3(&int3, sizeof(int3));
    char *p3 = "012";
    char *mistery = "F";
    function_3(p3, sizeof(p3));
    // output: 30 31 32 00 46 00 61 62 
    // what?? look at that 46 above after the null of "012"
    // constants are stored in the data section of the program

/*
4. Create a wild pointer and print it. The make it a null pointer and never speak of this again.
*/
    printf("%lu\n", sizeof(s2));

    return 0;
}