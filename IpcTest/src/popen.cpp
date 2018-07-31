/*
 * popen.cpp
 *
 *  Created on: 2018-7-31
 *      Author: root
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <errno.h>

//可以将调用linux命令的结果获取到程序内部
void popenTest()
{
	puts("popenTest begin!");

	const char *pszCmd = "date";
//	const char *pszCmd = "du -h --max-depth=1 /etc";
	char szBuff[256] = {0};
	FILE *fd = popen(pszCmd,"r");

	if(NULL == fd)
	{
		printf("popen fail! <%s>", strerror(errno));
		return;
	}

	while(NULL != fgets(szBuff, sizeof(szBuff), fd))
	{
		puts(szBuff);

	}

	pclose(fd);

	puts("popenTest end!");
}
