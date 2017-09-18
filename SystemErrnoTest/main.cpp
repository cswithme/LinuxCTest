#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main()
{
    fopen("xxx.txt","r");//file doesn't exit
    printf("errno is %d, %s\n",errno,strerror(errno));
    int iSysCallRet = 0;
    const char *pszCmd1 = "tar -tvf xxx";
    iSysCallRet = system(pszCmd1);
    printf("cmd [%s] iSysCallRet is %d, errno = %d\n",pszCmd1, iSysCallRet, errno);
}
