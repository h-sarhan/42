#include <stdio.h>

int	sum(int nums[], int size)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (i < size)
	{
		sum += nums[i];
		i++;
	}
	return (sum);
}

int	main()
{
	int nums[] = {1, 1, 1, 1, 2};

	printf("%d\n", sum(nums, 5));
}