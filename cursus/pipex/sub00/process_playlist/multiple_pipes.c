/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsarhan <hsarhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 12:53:30 by hsarhan           #+#    #+#             */
/*   Updated: 2022/06/15 13:12:07 by hsarhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int	main()
{
	int	fd[3][2];
	int	i;
	for (i = 0; i < 3; i++)
	{
		if (pipe(fd[i]) == -1)
		{
			return (1);
		}
	}
	
	int	pid1 = fork();
	if (pid1 == -1)
		return (2);
	if (pid1 == 0)
	{
		//Child process 1
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);
		close(fd[2][1]);
		int	x;
		if (read(fd[0][0], &x, sizeof(int)) == -1)
			return (1);
		x += 5;
		if (write(fd[1][1], &x, sizeof(int)) == -1)
			return (1);
		close(fd[0][0]);
		close(fd[1][1]);
		return (0);
	}
	int	pid2 = fork();
	if (pid2 == -1)
		return (1);
	if (pid2 == 0)
	{
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		int	x;
		if (read(fd[1][0], &x, sizeof(int)) == -1)
			return (1);
		x += 5;
		if (write(fd[2][1], &x, sizeof(int)) == -1)
			return (1);

		close(fd[2][1]);
		close(fd[1][0]);
		return (0);
	}
	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[2][1]);
	int x = 0;
	if (write(fd[0][1], &x, sizeof(int)) == -1)
		return (1);
	if (read(fd[2][0], &x, sizeof(int)) == -1)
		return (1);
	printf("Result is %d\n", x);
	close(fd[0][1]);
	close(fd[2][0]);
	
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}