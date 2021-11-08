#include <stdio.h>
#include <string.h>

void string_loop(const char* str)
{
    printf("Parsing %s\n", str);
    int len = strlen(str);

    for(int i=0, dig=0; i<len; i++)
    {
        // print anything that is NOT an 'A' nor '-'
        if(str[i]!='A' && str[i]!='-')
        {
           printf("%i:%c_is_%i ", dig++, str[i], str[i]-'0');
           //printf("%i ", str[i]-'0');
        }
    }

    printf("\n");
}

int main(int argc, char const *argv[])
{
    string_loop("AA987654-12-85-78AA");
    return 0;
}
