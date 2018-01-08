#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 200


int Pipe1Test()
{
	int		n;
	int		fd[2];
	pid_t	pid;
	char	line[MAXLINE];

	if (pipe(fd) < 0)
		puts("pipe error");

	if ((pid = fork()) < 0)
	{
		puts("fork error");
	}
	else if (pid > 0)	//parent
	{
		close(fd[0]);
		write(fd[1], "hello world xiaxiaxia\n", strlen("hello world xiaxiaxia\n"));
	}
	else //child
	{
		close(fd[1]);
		n = read(fd[0], line, MAXLINE);
		write(STDOUT_FILENO, line, n);
	}
	return 0;
}
