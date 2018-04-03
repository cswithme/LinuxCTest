#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <fcntl.h>  
#include <limits.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <unistd.h>
  
#define FIFO_NAME "/tmp/my_fifo"  
#define BUFFER_SIZE PIPE_BUF
  
int main()  
{  
    int pipe_fd;  
    int res;  
  
    // int open_mode = O_RDONLY|O_NONBLOCK;  
    int open_mode = O_RDONLY; 
    char buffer[BUFFER_SIZE + 1];  
    int bytes = 0;  
  
    memset(buffer, '\0', sizeof(buffer));  
  
    printf("read Process %d opeining FIFO O_RDONLY\n", getpid());  
    pipe_fd = open(FIFO_NAME, open_mode);  
    printf("read Process %d open result %d\n", getpid(), pipe_fd);  
  
    if (pipe_fd != -1)  
    {  
        do{  
            res = read(pipe_fd, buffer, BUFFER_SIZE);  
            bytes += res;  
            printf("read<%d>%d, res[%d]\n", getpid(),bytes, res);
            usleep(100 * 1000);
            
            static int icnt = 0;
            if(icnt++ > 3)
                break;
        }while(res > 0);  
        close(pipe_fd);  
    }  
    else  
    {  
        exit(EXIT_FAILURE);  
    }  
  
    printf("read Process %d finished, %d bytes read!!!!!!!!!\n", getpid(), bytes);  
    exit(EXIT_SUCCESS);  
}


// 如果管道的写端不存在，则认为已经读到了数据的末尾，读函数返回的读出字节数为0；

// 当管道的写端存在时，如果请求的字节数目大于PIPE_BUF，则返回管道中现有的数据字节数，
// 如果请求的字节数目不大于PIPE_BUF，则返回管道中现有数据字节数（此时，管道中数据量小于请求的数据量）；或者返回请求的字节数（此时，管道中数据量不小于请求的数据量）。