#include <stdlib.h>
#include <stdio.h>

int main()
{

    int *memory = calloc(0, sizeof(int));
    int i = 0;
    while (i < 1000000000)
    {

        *memory = rand();
        i++;
    }
}
