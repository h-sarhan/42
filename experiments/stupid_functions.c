#include <stdio.h>

void	print_nums(int *nums, int len)
{
	while(len--)
		printf("%d ", *nums++);
}

int	main()
{
	int nums[] = {1, 2, 3, 4};
	print_nums(nums, 4);
	
}
