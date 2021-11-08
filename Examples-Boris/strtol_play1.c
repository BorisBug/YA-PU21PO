#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void play()
{
    //str to l
    long value = 0;
    const char *strnum = NULL;
    char *next = NULL;

    strnum = "123";
    value = strtol(strnum, &next, 10);
    printf("A) %ld\n", value); // -> 123
    printf("A) %s\n", next);

    strnum = "101";
    value = strtol(strnum, &next, 10);
    printf("B) %ld\n", value); // -> 101

    strnum = "101";
    value = strtol(strnum, &next, 2);
    printf("C) %ld\n", value); // -> 5

    strnum = "101";
    value = strtol(strnum, &next, 16);
    printf("D) %ld\n", value); // -> 257

    strnum = "A";
    value = strtol(strnum, &next, 16);
    printf("E) %ld\n", value); // -> 10

    strnum = "A";
    value = strtol(strnum, &next, 10);
    printf("F) %ld\n", value); // ->  0

    strnum = "121";
    value = strtol(strnum, &next, 2);
    printf("%ld\n", value); // -> 1


    strnum = "101";
    value = strtol(strnum, &next, 10);
    printf("X1) %ld\n", value); // -> 101
    printf("X1) %s\n", next);

    strnum = "101-";
    value = strtol(strnum, &next, 10);
    printf("X2) %ld\n", value); // -> 101
    printf("X2) '%s'\n", next);
 
    strnum = "101-234";
    value = strtol(strnum, &next, 10);
    printf("X3) %ld\n", value); // -> 101
    printf("X3) '%s'\n", next); // 

/*  101(10)  =  101
    101(2)        5
    101(16)     256 + 0 + 1 = 257 
    111(16)     256 + 16 + 1
    */
}

void play_with_strtol()
{
    long value = 0;
    const char *strnum = NULL;
    char *next = NULL;

    char xxx = 3;
    char arr[4] = {'1', '2', '3', '\0'};

    /*
    addr  var  val
    0C10  xxx   3
    0c11  arr   49 ('1')
    0C12  arr   50 ('2')
    0C13  arr   51 ('3')
    0C14  arr    0
    0C16
    */

    strnum = "123";
    value = strtol(strnum, &next, 10);
    printf("A) Testing: %s\n", strnum);
    printf("value = %ld next = '%s'\n", value, next);

    strnum = "123-456";
    value = strtol(strnum, &next, 10);
    printf("B) Testing: %s\n", strnum);
    printf("value = %ld next = '%s'\n", value, next);

    next++;
    value = strtol(next, &next, 10);
    printf("C) Testing: %s\n", strnum);
    printf("value = %ld next = '%s'\n", value, next);
}

void play_with_strtol_v2()
{
    long y, m, d = 0;
    const char *strnum = NULL;
    char *next = NULL;

    strnum = "1975-11-21 10:10";

    y = strtol(strnum, &next, 10);
    printf("A) Testing: %s\n", strnum);
    printf("value = %ld next = '%s'\n", y, next);

    if(next[0] != '-' || !isdigit(next[1]))
    {
        printf("This is not the right fucking format!\n");
    }

    m = strtol(next, &next, 10);
    printf("B) Testing: %s\n", next);
    printf("value = %ld next = '%s'\n", m, next);

    next++;

    d = strtol(next, &next, 10);
    printf("C) Testing: %s\n", next);
    printf("value = %ld next = '%s'\n", d, next);
}


void pos_neg(short c)
{
    // char
    //if((c & 0x80) == 0)

    // short
    //if((c & 0x8000) == 0)
    
    // long
    //if((c & 0x80000000) == 0)

    // long long
    //if((c & 0x8000000000000000) == 0)

    if((c & 0x8000) == 0)
        printf("positive\n");
    else
        printf("negative\n");
}

int main()
{
    //pos_neg(0x0A);
    //pos_neg(0x7F);
    //pos_neg(0x7FFF);
    //pos_neg(0x8000);
    //play();
    //play_with_strtol();
    play_with_strtol_v2();

    return 0;
}

/*
256
          BIN           DEC  HEX
128 64 32 16  8 4 2 1   ___  ___
  8  4  2  1  8 4 2 1   ___  ___
              - - - - - - -  - - 
  0  1  1  1  0 0 0 0    0     0
              0 0 0 1    1     1
              0 0 1 0
              0 0 1 1
              0 1 0 0
              0 1 0 1
              0 1 1 0
              0 1 1 1

              1
              0 1 0 0    4     4
              1 0 0 1    9     9
              1 0 1 0   10     A
              1 1 1 1   15     F
  0  0  0  1  0 0 0 0   16    10
  0  0  1  0  0 0 0 1   33    21
  0  0  1  0  0 0 1 1  291   123
  0  1  1  1  0 0 1 0         72
  1  1  1  1  0 0 1 0  242    F2
  1  1  1  1  1 1 1 1  255    FF
  0  0  0  0  0 0 0 0  256   100
  0  1  1  1           127    0x7F
  1  0  0  0                  0x80          
                              0x01
value of top left = byte & 0x80

signed char c = ?;



  bits      unsigned    signed
0 0 0 0           0          0
0 0 0 1           1          1
0 0 1 0           2          2
0 0 1 1           3          3
0 1 0 0           4          4
0 1 0 1           5          5
0 1 1 0           6          6
0 1 1 1           7          7
1 0 0 0           8         -8
1 0 0 1           9         -7
1 0 1 0          10         -6
1 0 1 1          11         -5
1 1 0 0          12         -4
1 1 0 1          13         -3
1 1 1 0          14         -2
1 1 1 1          15         -1

----

1 0 0 0           8         -8  -128
1 0 0 1           9         -7
1 0 1 0          10         -6
1 0 1 1          11         -5
1 1 0 0          12         -4
1 1 0 1          13         -3
1 1 1 0          14         -2
1 1 1 1          15         -1
0 0 0 0           0          0
0 0 0 1           1          1
0 0 1 0           2          2
0 0 1 1           3          3
0 1 0 0           4          4
0 1 0 1           5          5
0 1 1 0           6          6
0 1 1 1           7          7  



void pos_neg(short c)
{
    if(c & 0x80 != 0)
        printf("positive")
    else
        printf("positive")
}

                        123     1      2     3 
                            256*1 + 16*2 + 1*3 = 291(dec)
*/