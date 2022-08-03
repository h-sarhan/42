#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_putchar(char ch)
{
	return (write(STDOUT_FILENO, &ch, 1));
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_putstr(char *str)
{
	if (str == NULL)
		return (ft_putstr("(null)"));
	return (write(STDOUT_FILENO, str, ft_strlen(str)));
}

int	count_digits(int num)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	if (num == -2147483648)
		return (11);
	if (num < 0)
	{
		num *= -1;
		count++;
	}
	while (num > 0)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

int	ft_putnbr(int num)
{
	int	num_copy;

	num_copy = num;
	if (num_copy == -2147483648)
		return (ft_putstr("-2147483648"));
	if (num_copy == 0)
		return (ft_putchar('0'));
	if (num_copy < 0)
	{
		ft_putchar('-');
		num_copy *= -1; 
	}
	if (num_copy > 0)
	{
		if (num_copy / 10 != 0)
			ft_putnbr(num_copy / 10);
		ft_putchar((num_copy % 10) + '0');
	}
	return (count_digits(num));
}

int	count_udigits(unsigned int num)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

int	ft_putuint(unsigned int num)
{
	if (num == 0)
		return (ft_putchar('0'));
	if (num > 0)
	{
		if (num / 10 != 0)
			ft_putuint(num / 10);
		ft_putchar((num % 10) + '0');
	}
	return (count_udigits(num));
}

int	count_hexa(unsigned int num)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num = num / 16;
		count++;
	}
	return (count);
}

int	print_hex(unsigned int num, int cap)
{
	if (num == 0)
		return (ft_putchar('0'));
	if (num > 0)
	{
		if (num / 16 != 0)
			print_hex(num / 16, cap);
		if (num % 16 < 10)
			ft_putchar(num % 16 + '0');
		else if (num % 16 >= 10 && cap == 0)
			ft_putchar(num % 16 + 'a' - 10);
		else if (num % 16 >= 10 && cap == 1)
			ft_putchar(num % 16 + 'A' - 10);
	}
	return (count_hexa(num));
}

int	count_pointer(unsigned long num)
{
	int	count;

	count = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num = num / 16;
		count++;
	}
	return (count);
}

int	print_pointer(void *p)
{
	unsigned long num;

	num = (unsigned long) p;
	if (num == 0)
		return (ft_putchar('0') + 2);
	if (num > 0)
	{
		if (num / 16 != 0)
			print_pointer((void *)(num / 16));
		if (num % 16 < 10)
			ft_putchar(num % 16 + '0');
		else if (num % 16 >= 10)
			ft_putchar(num % 16 + 'a' - 10);
	}
	return (count_pointer(num) + 2);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	size_t	i;
	int		num_chars;

	i = 0;
	num_chars = 0;
	va_start(args, fmt);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%' && fmt[i + 1] == 'c')
			num_chars += ft_putchar(va_arg(args, int));
		else if (fmt[i] == '%' && fmt[i + 1] == 's')
			num_chars += ft_putstr(va_arg(args, char *));
		else if (fmt[i] == '%' && (fmt[i + 1] == 'd' || fmt[i + 1] == 'i'))
			num_chars += ft_putnbr(va_arg(args, int));
		else if (fmt[i] == '%' && fmt[i + 1] == 'u')
			num_chars += ft_putuint(va_arg(args, unsigned int));
		else if (fmt[i] == '%' && fmt[i + 1] == 'x')
			num_chars += print_hex(va_arg(args, unsigned int), 0);
		else if (fmt[i] == '%' && fmt[i + 1] == 'X')
			num_chars += print_hex(va_arg(args, unsigned int), 1);
		else if (fmt[i] == '%' && fmt[i + 1] == 'p')
		{
			ft_putstr("0x");
			num_chars += print_pointer(va_arg(args, void *));
		}
		else if (fmt[i] == '%' && fmt[i + 1] == '%')
			num_chars += ft_putchar('%');
		if (fmt[i] == '%')
			i++;
		else
			num_chars += ft_putchar(fmt[i]);
		i++;
	}
	va_end(args);
	return (num_chars);
}

// int	main()
// {
// 	ft_printf("%p\n", 0);
// 	printf("%p\n", 0);
// // // 	// ft_putnbr(123);
// }