//============================================================================
// Name        : MutiCoreCpuTest.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================


/*比较多核处理器对线程效率的影响*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>

using namespace std;

pthread_barrier_t g_barrier;

sem_t g_semFinish;

const unsigned int uiThreadCnt = 1;

void *threadFunc(void *parm)
{
	unsigned int iCount = *(unsigned int *)parm;
	printf("iCount = %u\n", iCount);
	unsigned long ulRus = 0;

	pthread_barrier_wait(&g_barrier);

	for(unsigned int i=0; i<iCount; ++i)
		for(int k=0; k<10000; ++k)
			for(int k=0; k<10000; ++k)
				ulRus += k;

	sem_post(&g_semFinish);
	return NULL;
}

int main() {
	cout << "" << endl; // prints 

	pthread_barrier_init(&g_barrier, NULL, uiThreadCnt+1 );
	sem_init(&g_semFinish, 0, 0);

	pthread_t pid[uiThreadCnt];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	for(unsigned int i=0; i<uiThreadCnt; ++i)
		memset(&pid[i], 0, sizeof(pthread_t));

	int iCnt = 10000 / uiThreadCnt;

	for(unsigned int i=1; i<=uiThreadCnt; ++i)
	{
//		if(pthread_create(&pid1, &attr, threadFunc, &iCnt) != 0)
//			puts("pthread create fail!");
//
//		if(pthread_create(&pid2, &attr, threadFunc, &iCnt) != 0)
//			puts("pthread create fail!");

		if(pthread_create(&pid[i], &attr, threadFunc, &iCnt) != 0)
			puts("pthread create fail!");
	}


	struct timespec tsBegin,tsEnd;

	pthread_barrier_wait(&g_barrier); //等待计算开始
	clock_gettime(CLOCK_REALTIME, &tsBegin);
	printf("Before Call Func: tv_sec[%ld], tv_usec[%ld](ns)\n", tsBegin.tv_sec, tsBegin.tv_nsec);
	puts("Calc Begin!");


	unsigned int uiCntTemp = uiThreadCnt;
	while(uiCntTemp--)	sem_wait(&g_semFinish); //等待计算结束
	clock_gettime(CLOCK_REALTIME, &tsEnd);
	printf("After Call Func: tv_sec[%ld], tv_usec[%ld](ns)\n", tsEnd.tv_sec, tsEnd.tv_nsec);
	printf("!!!!!!!!!!!!time spend: tv_sec[%ld], tv_usec[%ld](ns)!!!!!!!!!", tsEnd.tv_sec-tsBegin.tv_sec, tsEnd.tv_nsec-tsBegin.tv_nsec);

	sem_destroy(&g_semFinish);
	pthread_barrier_destroy(&g_barrier);

	return 0;
}
