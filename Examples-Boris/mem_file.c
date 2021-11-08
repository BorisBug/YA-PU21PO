#include <stdio.h>

void create_mem_file()
{
    FILE *file = fopen("mem.txt", "w+");
    int start = 0x2A00;
    fprintf(file, "addr\tvar\t\tvalue...\n");
    for(int i=start; i<start+300; i++)
        fprintf(file, "0x%04X\t\t\t\n", i);
    fclose(file);
}

int main()
{
    create_mem_file();
    return 0;
}