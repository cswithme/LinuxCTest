/*
 * main.cpp
 * 在使用pthread_xxx功能时，需要链接libpthread.so
 *	Thread func Test
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include "apue.h"
#include <time.h>

void CleanupFuncTest();
void PthreadBarrierTest();
void Pthread_atforkTest();
void DeleteCalssWithThreadTest();
void semTest();
void semTest2();

//计算函数运行时间
typedef void (*P_Func)();
unsigned long caclFuncRunTime(P_Func pFunc, unsigned int uiFuncRunCnt = 1);
unsigned long caclFuncRunTime(P_Func pFunc, unsigned int uiFuncRunCnt)
{
	struct timespec tsBegin,tsEnd;
	clock_gettime(CLOCK_REALTIME, &tsBegin);
	printf("Before Call Func: tv_sec[%ld], tv_usec[%ld](ns)\n", tsBegin.tv_sec, tsBegin.tv_nsec);

	for(unsigned int i=0; i<uiFuncRunCnt; ++i)
		pFunc(); //call func

	clock_gettime(CLOCK_REALTIME, &tsEnd);
	printf("After Call Func: tv_sec[%ld], tv_usec[%ld](ns)\n", tsEnd.tv_sec, tsEnd.tv_nsec);

	unsigned long ulTimeUsedMs = (tsEnd.tv_sec - tsBegin.tv_sec)*1000 + (tsEnd.tv_nsec - tsBegin.tv_nsec)/1000000;
	printf("func exe use %lu ms \n",ulTimeUsedMs);
	return ulTimeUsedMs;

}

int main(void)
{
//	CleanupFuncTest();

//	caclFuncRunTime(PthreadBarrierTest, 1);
//	PthreadBarrierTest();

//	Pthread_atforkTest();

//	DeleteCalssWithThreadTest();

//	semTest();
	semTest2();
	exit(0);
}
