#include <stdio.h>

void pn(int*n,int l){while(l--)l?printf("%d ",*n++):printf("\n");}

int	main()
{
	int nums[] = {1, 2, 3, 4};
	pn(nums, 4);
}
