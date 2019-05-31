#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void printFD(pid_t pid)
{
    char szCmd[128] = {0};
    sprintf(szCmd, "ls -lp --color=auto /proc/%d/fd", pid);
    printf("pid(%d), fd open:\n", pid);
    system(szCmd);
}

int main(int argc, char **args)
{
    puts("Run exec1.cpp");
    printf("\ni am the child process after exec, my process id is %d\n",getpid());
    printFD(getpid());
	char buffer[20];
	int fd = atoi(args[1]);
	memset(buffer, 0, sizeof(buffer));
	ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);
	if(bytes < 0) {
		perror("exe1: read fail:");
		return -1;
	}
	else {
		printf("exe1: read %d,%s\n", bytes, buffer);
	}
    puts("Wait input!");
    char szTmp[128];
    gets(szTmp);
	return 0;
}