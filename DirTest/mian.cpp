/*
 * mian.cpp
 *
 *  Created on: 2017-8-16
 *      Author: root
 *      文件操作练习
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#include <arpa/inet.h>

using namespace std;
typedef unsigned char BYTE;

//获取指定目录中的所有文件名
bool getDirFileName(const char *szDirName,vector<string>  *pFilename)
{
	DIR *pDir = opendir(szDirName);
	if(pDir == NULL)
	{
		puts("Open Dir Err");
		return false;
	}
	struct dirent *dirp = NULL;

	while((dirp = readdir(pDir)) != NULL)
	{
		pFilename->push_back(dirp->d_name);
		//puts(dirp->d_name);
	}
	return true;
}

bool readBinFile(const char *szFileName)
{
	int fd = open(szFileName,O_RDONLY);
	if(fd == -1)
	{
		puts("Open File Fail!");
		return false;
	}
	unsigned char ucReadBuff[20];
	memset(ucReadBuff,0,sizeof(ucReadBuff));

	size_t iReadByteCnt = 0,iReadCnt=0;
	while((iReadByteCnt = read(fd, ucReadBuff, 16))!=0 && iReadCnt++ < 10)
	{
		printf("Read %d times:\n", iReadCnt);
		for(size_t i=0; i<iReadByteCnt; i++)
		{
			printf("%#X ",ucReadBuff[i]);
		}
		putchar('\n');
		for(size_t i=0; i<iReadByteCnt; i++)
		{
			printf("%c",ucReadBuff[i]);
		}
		putchar('\n');
		memset(ucReadBuff, 0, sizeof(ucReadBuff));

	}
	close(fd);
	return true;
}



int main()
{
	puts("Test Begin!");
	struct
	{
		int iNum;
		unsigned char szBuff[4];
	} stTemp;

	unsigned int iCnt = 0x12345678;
	*(int *)stTemp.szBuff = htonl(iCnt++);

//	readBinFile("/home//G60BBOOT.PRG");
//	readUpdateFile("/home/G60BBOOT.PRG");
//	vector<string> fileName;
//	getDirFileName("/Afc/Run",&fileName);
//
//	for(vector<string>::iterator it = fileName.begin(); it!=fileName.end(); it++ )
//	{
//		cout<<*it<<endl;
//	}
	puts("Test End!");
	return 0;

}

