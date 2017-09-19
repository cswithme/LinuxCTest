#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[])
{
    printf("errno is %d, %s\n",errno,strerror(errno));
    int iSysCallRet = 0;
    //const char *pszCmd1 = "tar -tvf xxx"; /home/gitHub/LinuxCTest/SystemErrnoTest
    char szCmd1[50] = {0};
    if(argc > 1)
        sprintf(szCmd1,"/home/gitHub/LinuxCTest/SystemErrnoTest/myCmd %s", argv[1]);
    else
        sprintf(szCmd1,"/home/gitHub/LinuxCTest/SystemErrnoTest/myCmd");
    iSysCallRet = system(szCmd1);
    printf("cmd [%s] iSysCallRet is %#X, errno = %d\n",szCmd1, iSysCallRet, errno);
    
    return 0;
}
