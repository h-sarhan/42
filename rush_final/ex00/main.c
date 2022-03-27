/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hassanAsarhan@outlook.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 08:36:44 by hsarhan           #+#    #+#             */
/*   Updated: 2022/03/27 21:25:35 by mwasef           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char	*create_buffer(char *file_name);
void	convert(int num, char *buffer);
void	convert_3_digits(int digits, char *buffer, int add_space);
int		ft_atoi(char *str);

int	validate_file(char *file_name)
{
	int	file;

	file = open(file_name, O_RDONLY);
	if (file == -1)
		write(1, "Dict Error\n", 11);
	return (file != -1);
}

int	verify_arg(char *arg)
{
	while (*arg != '\0')
	{
		if (*arg == '-' || *arg == '.')
		{
			write(1, "Error\n", 6);
			return (0);
		}
		arg++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	int		num;
	char	*file_name;
	char	*buffer;

	file_name = "numbers.dict";
	num = 0;
	if (argc == 2 || argc == 3)
	{
		num = ft_atoi(argv[argc - 1]);
		if (argc == 3)
		{
			file_name = argv[1];
			if (!validate_file(file_name))
				return (0);
		}
		if (verify_arg(argv[argc - 1]))
		{
			buffer = create_buffer(file_name);
			convert(num, buffer);
			free(buffer);
		}
	}
	return (0);
}
