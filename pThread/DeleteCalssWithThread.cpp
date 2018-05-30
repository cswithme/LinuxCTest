/*
 * DeleteCalssWithThread.cpp
 *
 *  Created on: 2018-5-11
 *      Author: root
 */

/*
 * 类中包含线程，线程会访问类中的成员与方法,
 * 分配在堆上的对象被删除后,线程依然运行，会不会出core
 */
#include "DeleteCalssWithThread.h"

void DeleteCalssWithThreadTest()
{
	puts("DeleteCalssWithThreadTest begin!");
	CClassWithThread *pClassWithThread = new CClassWithThread;
	pClassWithThread->Init();

	for(int i=0; i<5; i++)
	{
		usleep(1000 * 1000);
		printf("Main thread running! i=%d\n", i);
	}
	puts("Delete pClassWithThread!!!!!");
	delete pClassWithThread;
	pClassWithThread = NULL;
	puts("Delete pClassWithThread finish!!!!!");

	sleep(40);

	puts("DeleteCalssWithThreadTest end!");
}


CClassWithThread::CClassWithThread()
{
	printf("CClassWithThread creat, this<%p>\n", this);
}

void CClassWithThread::Init()
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	int iErr = pthread_create(&m_tid, &attr, ThreadFunc, this);
	if(iErr != 0)
	{
		puts("pthread_create fail!");
		exit(-1);
	}
	sleep(1);
	pthread_attr_destroy(&attr);
}

void *CClassWithThread::ThreadFunc(void *Parm)
{
	CClassWithThread *pThis = (CClassWithThread *)Parm;
	pThis = pThis;
	int iThreadCycleCnt = 0;
	while(1)
	{
		printf("ThreadFunc Running! iThreadCycleCnt[%d]\n", iThreadCycleCnt++);
		pThis->m_listTest.push_back(iThreadCycleCnt);
		pThis->ShowCntValue();
		usleep(1500 * 1000);
	}

	return NULL;
}



CClassWithThread::~CClassWithThread()
{
	printf("CClassWithThread destructor called!\n");
}



void CClassWithThread::ShowCntValue()
{
	printf("[%s] showCntValue[%d]\n", __FUNCTION__, m_iCnt++);
}

