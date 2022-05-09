#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*
int	main()
{
	                
	char str1[] = "fou-bar/lol";
	 //            0    5   
	 //            ^    ^   
	 // src      strt  end  
	 //               3    8
	 //               ^    ^
	 // dest         strt end
	char str2[] = "foo-bar/lol";
	memcpy(&str1[0], &str1[3], 5);
	memmove(&str2[0], &str2[3], 5);
	printf("memcpy result = %s\n", str1);
	printf("memmove result = %s\n", str2);
	//printf("str_cpy: %s\n", str_cpy);
	//printf("memmove: %s\n", str_mv);
}
*/
#include <stdio.h>
#include <string.h>

int main (void)
{
    char string [] = "stackoverflow";
    char *third, *fourth;
    third = string;
    fourth = string;

    puts(string);
    memcpy(third+5, third, 7);
    puts(third);
    memmove(fourth+5, fourth, 7);
    puts(fourth);
    return 0;
}
