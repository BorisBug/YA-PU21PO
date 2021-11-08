#include <stdio.h>

typedef struct 
{
    int y, m, d;
} ymd_t;

int get_YMD_v1(int *y, int *m, int *d)
{
    // if valid return 1
    if(1)
    {
        *y = 1990;
        *m = 10;
        *d = 28;
        return 1;
    }
    // error
    return 0;
}

int get_YMD_v2(ymd_t *ymd)
{
    // if valid return 1
    if(1)
    {
        ymd->y = 1990;
        ymd->m = 10;
        ymd->d = 28;
        return 1;
    }
    // error
    return 0;
}

ymd_t get_YMD_v3()
{
    ymd_t ymd;
    // if valid
    // --> not sure how to send the error!
    ymd.y = 1990;
    ymd.m = 10;
    ymd.d = 28;
    return ymd;
}

int main()
{
    int d, m, y;

    // v1: send 3 pointers --> OK
    if(get_YMD_v1(&y, &m, &d))
    { /* print values */ }
    else
    { /* print error */  }

    // v2: send 1 pointer --> BEST
    ymd_t ymd;
    if(get_YMD_v2(&ymd))
    { /* print values */ }
    else
    { /* print error */  }

    // v3: send 1 struct --> AVOID
    ymd_t ymd3 = get_YMD_v3();
    if(1 /* ?? */ ) // no verification inside, must be done outside
    { /* print values */ }
    else
    { /* print error */  }

    return 0;
}
