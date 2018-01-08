#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <errno.h>

#define	DEF_PAGER	"/usr/bin/less"		/* default pager program */
#define DEF_FILE_READ "/etc/aliases"
#define MAXLINE 1024

static void err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
	char	buf[MAXLINE];

	vsnprintf(buf, MAXLINE-1, fmt, ap);
	if (errnoflag)
		snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s",
		  strerror(error));
	strcat(buf, "\n");
	fflush(stdout);		/* in case stdout and stderr are the same */
	fputs(buf, stderr);
	fflush(NULL);		/* flushes all stdio output streams */
}

void err_quit(const char* szErrMsg)
{
	printf("Error[%s]!", szErrMsg);
	exit(-1);
}

void err_sys(const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(1, errno, fmt, ap);
	va_end(ap);
	exit(1);
}

int Pipe2Test(int argc, char *argv[])
{
	/*open file to read!*/
	FILE *fp = NULL;
	if (argc != 2)
	{
		printf("Use Default File[%s] to read!\n", DEF_FILE_READ);
		if ((fp = fopen(DEF_FILE_READ, "r")) == NULL)
			err_sys("can't open %s", DEF_FILE_READ);
	}
	else
	{
		if ((fp = fopen(argv[1], "r")) == NULL)
			err_sys("can't open %s", argv[1]);
	}

	/*创建管道*/
	int		fd[2];
	if (pipe(fd) < 0)	err_sys("pipe error");

	/*创建进程*/
	int pid;
	if ((pid = fork()) < 0)	err_sys("fork error");

	else if (pid > 0) //parent
	{
		close(fd[0]);		/* close read end */

		//从打开的文件中读取内容,并写入pipe中
		int n=0;
		char line[1024] = {0};

		while (fgets(line, sizeof(line)-1, fp) != NULL)
		{
			n = strlen(line);
			if (write(fd[1], line, n) != n)
				err_sys("write error to pipe");
		}

		if (ferror(fp))
			err_sys("fgets error");

		close(fd[1]);	/* close write end of pipe for reader */

		if (waitpid(pid, NULL, 0) < 0)
			err_sys("waitpid error");

		return 0;
	}

	else
	{										/* child */
		close(fd[1]);	/* close write end */
		if (fd[0] != STDIN_FILENO) {
			if (dup2(fd[0], STDIN_FILENO) != STDIN_FILENO)
				err_sys("dup2 error to stdin");
			close(fd[0]);	/* don't need this after dup2 */
		}

		const char *argv0 = DEF_PAGER;
		if ((argv0 = strrchr(DEF_PAGER, '/')) != NULL)
			argv0++;		/* step past rightmost slash */
		if(execl(DEF_PAGER, argv0, (char *)0) <0)
		{
			err_sys("execl error for %s", DEF_PAGER);
		}

#if 0
		/* get arguments for execl() */
		if ((pager = getenv("PAGER")) == NULL)
			pager = DEF_PAGER;
		if ((argv0 = strrchr(pager, '/')) != NULL)
			argv0++;		/* step past rightmost slash */
		else
			argv0 = pager;	/* no slash in pager */

		if (execl(pager, argv0, (char *)0) < 0)
			err_sys("execl error for %s", pager);
#endif
	}

	return 0;
}

