#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <unistd.h>
#include <fcntl.h>  
#include <limits.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <signal.h>
  
#define FIFO_NAME "/tmp/my_fifo"  
#define BUFFER_SIZE PIPE_BUF
#define TEN_MEG (1024 * 30)  

void catchSIGPIPE(int sig)
{
    if(SIGPIPE == sig)
        puts("get Signal SIGPIPE!");
}

int main()  
{  
    signal(SIGPIPE, catchSIGPIPE);
    int pipe_fd;  
    int res;  
    int open_mode = O_WRONLY;  
  
    int bytes = 0;  
    char buffer[BUFFER_SIZE + 1];  
  
    if (access(FIFO_NAME, F_OK) == -1)  
    {  
        res = mkfifo(FIFO_NAME, 0777);  
        if (res != 0)  
        {  
            fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);  
            exit(EXIT_FAILURE);  
        }  
    }  
  
    printf("write Process %d opening FIFO O_WRONLY\n", getpid());  
    pipe_fd = open(FIFO_NAME, open_mode);  
    printf("write Process %d open result %d\n", getpid(), pipe_fd);  
  
   sleep(2);
    if (pipe_fd != -1)  
    {  
        while (bytes < TEN_MEG)  
        {  
            res = write(pipe_fd, buffer, BUFFER_SIZE);  
            if (res == -1)  
            {  
                fprintf(stderr, "Write error on pipe\n");  
                exit(EXIT_FAILURE);  
            }  
            bytes += res;  
            printf("write<%d>%d\n", getpid(),bytes);
            usleep(800 * 1000);
        }  
        close(pipe_fd);  
    }  
    else  
    {  
        exit(EXIT_FAILURE);  
    }  
  
    // sleep(5);
    printf("write Process %d finish, %d bytes write!!!!!!!!!\n", getpid(), bytes);  
    exit(EXIT_SUCCESS);  
}