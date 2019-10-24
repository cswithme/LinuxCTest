//============================================================================
// Name        : libeventTest.cpp
// Author      : 
// Version     :libevent-2.0.21-stable
// Copyright   : 
// Description :
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#include <event2/event.h>

#include "ServerSocket.h"

#define BUFFSIZE 1024

using namespace std;

static struct event_base *evBase = NULL;

typedef struct __ST_CONNECT_STATUS{

	int connectFd;

	uint8_t u8RxBuff[BUFFSIZE];
	uint32_t u32RxCnt;

	uint8_t u8TxBuff[BUFFSIZE];
	uint32_t u32TxCnt;
	uint32_t u32CurTxIndex;

	struct event *rxEvent;
	struct event *txEvent;
}ST_CONNECT_STATUS;

void doAcceptCb(evutil_socket_t sfd, short what, void* parm);
void doReadCb(evutil_socket_t sfd, short what, void* parm);
void doWriteCb(evutil_socket_t sfd, short what, void* parm);

ST_CONNECT_STATUS *ConnectStatusStructNew(struct event_base *evBase, int connectFd)
{
	ST_CONNECT_STATUS *pstConnectStatus = new ST_CONNECT_STATUS();
	pstConnectStatus->u32RxCnt = 0;
	pstConnectStatus->u32TxCnt = 0;
	pstConnectStatus->u32CurTxIndex = 0;

	pstConnectStatus->connectFd = connectFd;
	pstConnectStatus->rxEvent = event_new(evBase, connectFd, EV_READ|EV_PERSIST, doReadCb, pstConnectStatus);
	pstConnectStatus->txEvent = event_new(evBase, connectFd, EV_WRITE|EV_PERSIST, doWriteCb, pstConnectStatus);
	return pstConnectStatus;
}

void ConnectStatusStructDel(ST_CONNECT_STATUS *pstConnectStatus)
{
	event_del(pstConnectStatus->rxEvent);
	event_del(pstConnectStatus->txEvent);

	event_free(pstConnectStatus->rxEvent);
	event_free(pstConnectStatus->txEvent);

	delete pstConnectStatus;
}

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

static void printEventType(short what)
{
	if(EV_TIMEOUT & what) puts("EV_TIMEOUT");
	else if(EV_TIMEOUT & what) puts("EV_READ");
	else if(EV_READ & what) puts("EV_READ");
	else if(EV_WRITE & what) puts("EV_WRITE");
	else if(EV_SIGNAL & what) puts("EV_SIGNAL");
	else if(EV_PERSIST & what) puts("EV_PERSIST");
	else if(EV_ET & what) puts("EV_ET");
	else printf("UNKNOW Event(%d)!\n", what);
}

void timercb(evutil_socket_t sfd, short what, void* parm)
{
	printf("timercb parm[%p]\n", parm);
	printEventType(what);
}

/*
 * libevent timeout test
 */
void evTimerTest()
{
	struct event_base *evBase = event_base_new();

	struct timeval tv = {0, 990*1000};
//	struct event *timeEvent = evtimer_new(evBase, timercb, NULL); //timercb只会执行一次
	struct event *timeEvent = event_new(evBase, -1, EV_TIMEOUT|EV_PERSIST, timercb, NULL); //timercb会重复执行

	evtimer_add(timeEvent, &tv);

	event_base_dispatch(evBase);

	event_free(timeEvent);
	event_base_free(evBase);
	puts("event_base_dispatch end");

}

void doAcceptCb(evutil_socket_t sfd, short what, void* parm)
{
	printEventType(what);
	socklen_t clientAddrLen = 0;
	struct sockaddr_in clientAddr; memset(&clientAddr, 0, sizeof(clientAddr));
	int clientfd = accept((int)sfd, (sockaddr*)&clientAddr, &clientAddrLen);
	printf("[%s][%s][%d] accept ret clientfd(%d)\n", __FILE__, __FUNCTION__, __LINE__, clientfd);

	ST_CONNECT_STATUS *pst = ConnectStatusStructNew(evBase, clientfd);
	event_add(pst->rxEvent, NULL);
}

void doReadCb(evutil_socket_t sfd, short what, void* parm)
{

	if(!(what|EV_READ)){
		printEventType(what);
		printf("[%s][%s][%d] Get Wrong event\n", __FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ST_CONNECT_STATUS *pst = (ST_CONNECT_STATUS *)parm;
	int iReadSize = SocketRead(sfd, pst->u8RxBuff+pst->u32RxCnt, BUFFSIZE-pst->u32RxCnt);

	if(iReadSize == 0){
		printf("[%s][%s][%d] doReadCb fd(%d) closed!\n", __FILE__, __FUNCTION__, __LINE__, sfd);
		ConnectStatusStructDel(pst);
		close(sfd);
	}
	else if(iReadSize<0){
		printf("[%s][%s][%d] doReadCb fd(%d) Read error!\n", __FILE__, __FUNCTION__, __LINE__, sfd);
	}
	else{
		printf("[%s][%s][%d] doReadCb fd(%d) Read (%d) Byte!\n", __FILE__, __FUNCTION__, __LINE__, sfd, iReadSize);
		pst->u32RxCnt += iReadSize;
		if(pst->u8RxBuff[pst->u32RxCnt-1] == '\n'){
			//把收到的第一行复制到发送缓存中发送回去
			printf("[%s][%s][%d] ********** sfd(%d) Rx:%s\n", __FILE__, __FUNCTION__, __LINE__, sfd, pst->u8RxBuff);
			memcpy(pst->u8TxBuff, pst->u8RxBuff, pst->u32RxCnt);
			pst->u32TxCnt = pst->u32RxCnt;
			pst->u32CurTxIndex = 0;
			pst->u32RxCnt = 0;//todo 收到的第二行会扔掉
			//添加发送event
			event_add(pst->txEvent, NULL);
		}
	}
}

void doWriteCb(evutil_socket_t sfd, short what, void* parm)
{
	if(!(what | EV_WRITE)) {
		printEventType(what);
		printf("[%s][%s][%d] Get Wrong event\n", __FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ST_CONNECT_STATUS *pst = (ST_CONNECT_STATUS *) parm;
	int iTxSize = SocketWrite(sfd, pst->u8TxBuff+pst->u32CurTxIndex, pst->u32TxCnt-pst->u32CurTxIndex);

	if(iTxSize<0){
		if (errno == EAGAIN) return;
		else {
			printf("[%s][%s][%d] SocketWrite faile\n", __FILE__, __FUNCTION__, __LINE__);
			ConnectStatusStructDel(pst);
			close(sfd);
		}
	}
	else if(iTxSize==0){
		printf("[%s][%s][%d] SocketWrite Txsize=0, Unknow event\n", __FILE__, __FUNCTION__, __LINE__);
	}
	else{
		pst->u32CurTxIndex += iTxSize;
		printf("[%s][%s][%d] sfd(%d) SocketWrite %d Byte\n", __FILE__, __FUNCTION__, __LINE__, sfd, iTxSize);

		if(pst->u32CurTxIndex == pst->u32TxCnt){
			printf("[%s][%s][%d] ********** sfd(%d) Tx:%s\n", __FILE__, __FUNCTION__, __LINE__, sfd, pst->u8TxBuff);
			event_del(pst->txEvent);
		}
	}
}

void evServerSocketTest()
{
	evBase = event_base_new();

	int socketfd = CreateListenSocket(23333);
	struct event *socketEvent = event_new(evBase, socketfd, EV_READ|EV_PERSIST, doAcceptCb, NULL); //会重复执行
//	struct event *socketEvent = event_new(evBase, socketfd, EV_READ, doAcceptCb, NULL); //

//	struct timeval tv = {5, 1*1000};
//	event_add(socketEvent, &tv);
	event_add(socketEvent, NULL);

	puts("Start event loop!");
	event_base_dispatch(evBase);

	event_free(socketEvent);
	event_base_free(evBase);
	evBase = NULL;
}




