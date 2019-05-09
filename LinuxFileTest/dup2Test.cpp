/*
 * dup2Test.cpp
 *
 *  Created on: 2019-5-9
 *      Author: root
 */
#include "extern.h"

//测试使用 rename 和 dup2的情况下 文件描述赋的变化
//rename(filename, newname) 重命名文件
//dup2 复制文件描述符
//linux下系统调用都是原子的

//ret fd
int _OpenFile(const char* pszFileName)
{
	int _flags = O_CREAT | O_APPEND | O_WRONLY;
	mode_t _mode = 664;
	int _fd = ::open(pszFileName, _flags, _mode);
	if(-1 == _fd){
		printf("%s open error, %s !\n", pszFileName, strerror(errno));
	}
	return _fd;
}

//在多线程的情况下，利用dump的原子性，实现日志的roll back
//log4cpp 中 RollingFileAppender::rollOver 实现方式为直接close fd ,然后再打开新的文件，在此期间的写入操作会有问题
void DupTest()
{
	char szTmp[32];
	const char *szFileName = "/Afc/Log/testDup.log";

	//1 open file
	int g_fd = _OpenFile(szFileName);
	printf("_OpenFile finish, fd(%d)!\n", g_fd);
	gets(szTmp);

	//for test 写入已经关闭的文件
//	close(g_fd);
//	printf("will write to closed file!\n");
//	int iRet = write(g_fd, "1111111111", strlen("1111111111"));
//	if(-1 == iRet) {
//		printf("write content error, %s !\n", strerror(errno));
//		exit(-1);
//	}
//	gets(szTmp);

	//2 write file content
	write(g_fd, "1111111111", strlen("1111111111"));
	printf("write file finish!\n");
	gets(szTmp);

	//3 rename file
	const char *szBackupFileName = "/Afc/Log/testDupBak.log";
	rename(szFileName, szBackupFileName);
	/*
	 *  xxx rename之后，fd会指向重命名后的文件
	 *  此时对该fd进行write操作，写入的内容会进入rename之后的文件中
	 */
	printf("rename file finish!\n");
	gets(szTmp);

	//4 write file content after rename
	write(g_fd, "222222222222", strlen("2222222222222222"));
	printf("write file content after rename!\n");
	gets(szTmp);

	//5 open new file
	int _fdTmp = _OpenFile(szFileName); //"/Afc/Log/testDup.log"
	printf("open new file, _fdTmp(%d), g_fd(%d)!\n", _fdTmp, g_fd);
	gets(szTmp);

	//6 dup2 file    int dup2(int oldfd, int newfd)
	dup2(_fdTmp, g_fd);
	/*
	 * befor dup2:
	 * _fdTmp=>testDup.log g_fd=>testDupBak.log
	 *
	 * After dup2
	 * dup2 关闭newfd(g_fd=>testDupBak.log)指向的文件
	 * 并将oldfd(_fdTmp=>testDup.log)复制给g_fd
	 * 故_fdTmp=>testDup.log  g_fd=>testDup.log
	 */
	printf("dup2 finish, _fdTmp(%d), g_fd(%d)!\n", _fdTmp, g_fd);
	gets(szTmp);

	//7 close 多余的 _fdTmp
	close(_fdTmp);
	printf("After close _fdTmp,test funish!\n");
	gets(szTmp);

}
