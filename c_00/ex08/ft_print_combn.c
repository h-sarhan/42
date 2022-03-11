#include <unistd.h>

void	print_inner_combn(int n, int start)
{
	char	num;
	int		n_copy;
	int		iteration;
	char	start_char;	

	iteration = 0;
	while ((iteration + start) <= 9)
	{
		n_copy = n;
		while (n_copy > 1)
		{
			start_char = start - n_copy + 1 + '0';
			write(1, &start_char, 1);
			n_copy--;
		}
		num = iteration + start + '0';
		write(1, &num, 1);
		if (start != 9)
		{
			write(1, ", ", 2);
		}
		iteration++;
	}
}

void	ft_print_combn(int n)
{
	int	iteration;

	iteration = n - 1;
	while (iteration <= 9)
	{
		print_inner_combn(n, iteration);
		iteration++;
	}
	write(1, "\n", 1);
}

int	main(void)
{
	ft_print_combn(2);
}
