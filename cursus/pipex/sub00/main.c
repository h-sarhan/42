#include <unistd.h>
#include "pipex.h"

int	main(int argc, char **argv)
{
	ft_printf("%s %s %s\n", argv[0], argv[1], argv[2]);
	// execlp("awk", "awk", "{count++} END {print count}", NULL);
}