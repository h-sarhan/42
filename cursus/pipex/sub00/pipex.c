#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	// char *env_args[] = {"PATH=/bin/", NULL};
	// execve("/bin/ls", argv, env_args);
	char	*bin_path = "/bin/";
	bin_path = ft_strjoin(bin_path, argv[1]);
	char **args = ft_split("~", ' ');
	execve(bin_path, args, envp);
    return 0;
}