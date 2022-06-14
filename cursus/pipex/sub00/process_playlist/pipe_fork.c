#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	int arr[] = {1, 2, 3, 4, 1, 2, 988089};
	int	arrSize = sizeof(arr) / sizeof(int);
	int	fd[2];
	int	start;
	int	end;

	if (pipe(fd) == -1)
		return (1);

	int	id = fork();
	if (id == -1)
		return (1);

	if (id == 0)
	{
		start = 0;
		end = arrSize / 2;
	}
	else
	{
		start = arrSize / 2;
		end = arrSize;
	}

	int	sum = 0;
	int	i;

	i = start;
	while (i < end)
	{
		sum += arr[i];
		i++;
	}
	printf("Calculated partial sum: %d\n", sum);
	if (id == 0)
	{
		close(fd[0]);
		if (write(fd[1], &sum, sizeof(int) == -1))
		{
			return (1);
		}
		close(fd[1]);
	}
	else
	{
		wait(NULL);
		int	sum_from_child;
		close(fd[1]);
		if (read(fd[0], &sum_from_child, sizeof(int)) == -1)
		{
			return (1);
		}
		close(fd[0]);

		int	total_sum;

		total_sum = sum + sum_from_child;
		printf("Total sum is %d\n", total_sum);
	}
	
	return (0);
}