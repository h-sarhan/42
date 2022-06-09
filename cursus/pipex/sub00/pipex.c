#include "pipex.h"
extern char **environ;

int	main(int argc, char **argv)
{
	// char *env_args[] = {"PATH=/bin/", NULL};
	// execve("/bin/ls", argv, env_args);
	char	*bin_path = "/bin/";
	bin_path = ft_strjoin(bin_path, argv[2]);
	execve(bin_path, &argv[1], environ);
    return 0;
}