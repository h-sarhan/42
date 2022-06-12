#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>


int	get_exit_status(int status)
{
	return ((status & 0xff00) >> 8);
}
int	main(int argc, char *argv[])
{
	int pid = fork();
	if (pid == -1)
	{
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execlp("which", "which", "pig", NULL);
	}
	else
	{
		int status;
		wait(&status);
		printf("EXIT STATUS IS %d\n", get_exit_status(status));
		printf("EXIT STATUS 2 IS %d\n", WEXITSTATUS(status));
		printf("Success!\n");
	}
	return (0);
}