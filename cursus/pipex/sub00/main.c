#include <unistd.h>
#include "pipex.h"

// int	main(int argc, char **argv)
// {
// 	// ft_printf("%s %s %s\n", argv[0], argv[1], argv[2]);
// 	execlp("awk", "awk", "\"{count++} END {print count}\"", NULL);
// }

// int	main(int argc, char **argv)
// {
// 	int num = ft_atoi(argv[1]);
// 	int i = 1;
// 	while (i < 10)
// 	{
// 		// printf("%d x %d = %d\n", i, num, i * num);
// 		ft_putnbr_fd(i, 1);
// 		ft_putstr_fd(" x ", 1);
// 		ft_putnbr_fd(num, 1);
// 		ft_putstr_fd(" = ", 1);
// 		ft_putnbr_fd(num * i, 1);
// 		ft_putchar_fd('\n', 1);
// 		i++;
// 	}
// }