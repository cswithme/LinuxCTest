#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void printFD(pid_t pid)
{
    char szCmd[128] = {0};
    sprintf(szCmd, "ls -lp --color=auto /proc/%d/fd", pid);
    printf("pid(%d), fd open:\n", pid);
    system(szCmd);
}

int main(void)
{
    puts("Run test.cpp");
	int fd, pid;
	char buffer[20];
	// fd = open("./wo.txt", O_RDONLY);
    fd = open("./wo.txt", O_RDONLY|O_CLOEXEC);
	printf("fd = %d\n", fd);
	// int val = fcntl(fd, F_GETFD);
	// val |= FD_CLOEXEC;
	// fcntl(fd, F_SETFD, val);

	pid = fork();
	if(pid == 0) {
		//子进程中，此描述符并不关闭，仍可使用
         usleep(200 * 1000);
        printf("\nAfter fork, i am the child process, my process id is %d\n", getpid());
        printFD(getpid());
        
		char child_buf[10];
		memset(child_buf, 0, sizeof(child_buf));
		ssize_t bytes = read(fd, child_buf, sizeof(child_buf) - 1);
		printf("child, read bytes:%d, content(%s) \n", bytes, child_buf);

		//execl执行的程序里，此描述符被关闭，不能再使用它
		char fd_str[5];
		memset(fd_str, 0, sizeof(fd_str));
		sprintf(fd_str, "%d", fd);
		int ret = execl("./exe1", "exe1", fd_str, NULL);
		if(-1 == ret) perror("ececl fail:");
    }
    else if(pid > 0){
        printf("\ni am the parent process, my process id is %d\n",getpid());
        printFD(getpid());
        
        waitpid(pid, NULL, 0);
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes = read(fd, buffer, sizeof(buffer) - 1);
        printf("parent, read bytes:%d, content(%s) \n", bytes, buffer);
        
        printf("\nparent process after waitpid %d\n",getpid());
        printFD(getpid());
    }

	
}