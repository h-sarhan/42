#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int	main(int argc, char *argv[])
{
	int pid = fork();
	if (pid == -1)
	{
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execlp("ping", "ping", "-c", "3", "google.com", NULL);
	}
	else
	{
		wait(NULL);
		printf("Success!\n");
	}
	return (0);
}