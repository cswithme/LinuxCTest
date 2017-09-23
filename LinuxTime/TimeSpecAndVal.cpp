/*
 * TimeSpecAndVal.cpp
 * 比较精确的时间计数
 *  Created on: 2017-9-22
 *      Author: root
 */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h> //gettimeofday
#include <unistd.h>

void testTimeofday()
{
	struct timeval stTv;
	if(gettimeofday(&stTv,NULL) != 0) //gettimeofday两个入参均可为空
	{
		puts("gettimeofday fail!");
		return;
	}
	printf("gettimeofday return: tv_sec[%ld], tv_usec[%ld](us)\n", stTv.tv_sec, stTv.tv_usec);
}

void testClock_gettime()
{
	struct timespec stTs;

	//xxx clock_getres 可获取时钟精度
	if(clock_getres(CLOCK_REALTIME, &stTs) != 0)
	{
		puts("clock_getres fail!");
		return;
	}
	printf("CLOCK_REALTIME 时钟精度: tv_sec[%ld], tv_usec[%ld](ns)\n", stTs.tv_sec, stTs.tv_nsec);

	if(clock_gettime(CLOCK_REALTIME, &stTs) != 0) //xxx -l rt
	{
		puts("clock_gettime fail!");
		return;
	}
	printf("clock_gettime return: tv_sec[%ld], tv_usec[%ld](ns)\n", stTs.tv_sec, stTs.tv_nsec);
}

void TimeSpecAndValTest()
{
	testTimeofday();
	testClock_gettime();
}

//xxx 计算某个函数执行的时间 -l rt

typedef void (*P_Func)(void * parm);
unsigned long caclFuncRunTime(P_Func pFunc, void* parm, unsigned int uiFuncRunCnt = 1);
unsigned long caclFuncRunTime(P_Func pFunc, void* parm, unsigned int uiFuncRunCnt)
{
	struct timespec tsBegin,tsEnd;
	clock_gettime(CLOCK_REALTIME, &tsBegin);
	printf("Before Call Func: tv_sec[%ld], tv_usec[%ld](ns)\n", tsBegin.tv_sec, tsBegin.tv_nsec);

	for(unsigned int i=0; i<uiFuncRunCnt; ++i)
		pFunc(parm); //call func

	clock_gettime(CLOCK_REALTIME, &tsEnd);
	printf("After Call Func: tv_sec[%ld], tv_usec[%ld](ns)\n", tsEnd.tv_sec, tsEnd.tv_nsec);

	unsigned long ulTimeUsedMs = (tsEnd.tv_sec - tsBegin.tv_sec)*1000 + (tsEnd.tv_nsec - tsBegin.tv_nsec)/1000000;
	printf("func exe use %lu ms \n",ulTimeUsedMs);
	return ulTimeUsedMs;

}

void func(void *parm)
{
//	printf("Func Run begin, parm is %p\n",parm);
//	printf("*(int *)parm is %X\n",*(int *)parm);
	usleep(245 * 1000);

//	puts("Func Run end");
}

void func1(void *parm)
{
	char szTemp[4096] = {0};
	szTemp[0] = 22;
}

void func2(void *parm)
{
	char szTemp[4096];
	memset(szTemp, 0, sizeof(szTemp));
	szTemp[0] = 22;
}

void testCalcRunTime()
{
	int iTemp = 0x666;
	caclFuncRunTime(func, (void *)&iTemp);

	puts("\ninit: ");
	caclFuncRunTime(func1, NULL, 1000*1000);
	puts("\nmemset: ");
	caclFuncRunTime(func2, NULL, 1000*1000);
}
