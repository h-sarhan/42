#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
int main()
{
    printf("%d", atoi("-2147483648"));
    printf(" = %d\n", INT_MIN);
}
