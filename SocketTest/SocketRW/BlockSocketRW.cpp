/*
 * BlockSocketRW.cpp
 *
 *  Created on: 2019-10-24
 *      Author: root
 */

#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>

#include "SocketRW.h"

int SocketWrite(int socketfd, const uint8_t *u8TxDate, uint32_t u32TxLen)
{
	int iRet = send(socketfd, u8TxDate, u32TxLen, 0);
	if(-1 == iRet) {
		printf("[%s][%s][%d] Socket send faile, %s!\n", __FILE__, __FUNCTION__, __LINE__, strerror(errno));
	}
	else{
		printf("[%s][%s][%d] Socket send sucess\n", __FILE__, __FUNCTION__, __LINE__);
	}
	return iRet;
}

int SocketRead(int socketfd, uint8_t *u8RxDate, uint32_t u32RxBuffLen)
{
	int iRet = recv(socketfd, u8RxDate, u32RxBuffLen, 0);
	if(-1 == iRet) {
		printf("[%s][%s][%d] Socket Recv faile, %s!\n", __FILE__, __FUNCTION__, __LINE__, strerror(errno));
	}
	else if(0 == iRet) {
		printf("[%s][%s][%d] Recv Socket already closed!\n", __FILE__, __FUNCTION__, __LINE__);
	}
	else{
		printf("[%s][%s][%d] Socket Recv sucess, recvLen(%u)\n", __FILE__, __FUNCTION__, __LINE__, iRet);
	}
	return iRet;
}

void SocketRWTest(int socketfd)
{
	const char *pszSend = "0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz\n";

	if(0<SocketWrite(socketfd, (const uint8_t*)pszSend, strlen(pszSend))) {
		char szReadBuff[512]; memset(szReadBuff, 0, sizeof(szReadBuff));
		uint32_t u32ReadLen = SocketRead(socketfd, (uint8_t*)szReadBuff, sizeof(szReadBuff));
		printf("[%s][%s][%d] Socket recvLen(%u): [%s]\n", __FILE__, __FUNCTION__, __LINE__, u32ReadLen, szReadBuff);
		close(socketfd);
	}
}


