#include <stdio.h>

int	get_num_digits(int nb)
{
	int	num_digits;

	num_digits = 0;
	if (nb == 0)
	{
		return (1);
	}
	while (nb > 0)
	{
		nb /= 10;
		num_digits++;
	}
	return (num_digits);
}

int	power_of_10(int power)
{
	int	value;

	value = 1;
	while (power > 0)
	{
		value *= 10;
		power--;
	}
	return (value);
}

void	ft_putnbr(int nb)
{
	char	num_char;
	int		num_digits;
	int		num;

	if (nb < 0)
	{
		write(1, "-", 1);
		nb *= -1;
	}	
	num_digits = get_num_digits(nb);
	while (num_digits > 0)
	{
		num = nb / power_of_10(num_digits - 1);
		num_char = num + '0';
		write(1, &num_char, 1);
		nb -= num * power_of_10(num_digits - 1);
		num_digits--;
	}
}
