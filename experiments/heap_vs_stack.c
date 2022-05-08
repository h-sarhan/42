#include <stdio.h>
#include <stdlib.h>

void print_nums(int *nums, int len)
{
	int	i = 0;

	printf("[");
	while (i < len - 1)
	{
		printf("%d, ", nums[i]);
		i++;
	}
	printf("%d]\n", nums[i]);
}

int *func()
{
	int	num_amount = 3;
	//int	nums[num_amount];
	int	*nums = malloc(sizeof(int) * num_amount);
	nums[0] = 1;
	nums[1] = 2;
	nums[2] = 3;
	return nums;
}

int main()
{
	int *nums = func();
	
	print_nums(nums, 3);
	free(nums);
}

