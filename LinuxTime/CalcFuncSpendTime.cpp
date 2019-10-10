/*
 * CalcFuncSpendTime.cpp
 *
 *  Created on: 2019-9-10
 *      Author: root
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h> //gettimeofday
#include <unistd.h>

typedef void (*Ptr_Func)(void * parm); //需要计算的函数指针
unsigned long CaclFuncRunTime(Ptr_Func pFunc, void* parm, unsigned int uiFuncRunCnt = 1);

unsigned long CaclFuncRunTime(Ptr_Func pFunc, void* parm, unsigned int uiFuncRunCnt)
{
	struct timespec tsBegin,tsEnd;
	int iRet = clock_gettime(CLOCK_MONOTONIC, &tsBegin);
//	printf("iRet(%d)Before Call Func: tv_sec[%ld], tv_usec[%ld](ns)\n", iRet, tsBegin.tv_sec, tsBegin.tv_nsec);

	for(unsigned int i=0; i<uiFuncRunCnt; ++i)
		pFunc(parm); //call func

//	clock_gettime(CLOCK_REALTIME, &tsEnd);
	clock_gettime(CLOCK_MONOTONIC, &tsEnd); //CLOCK_REALTIME会被修改系统的动作干扰

	printf("After Call Func: tv_sec[%ld], tv_usec[%ld](ns)\n", tsEnd.tv_sec, tsEnd.tv_nsec);

	unsigned long ulTimeUsedMs = (tsEnd.tv_sec - tsBegin.tv_sec)*1000 + (tsEnd.tv_nsec - tsBegin.tv_nsec)/1000000;
	printf("***********************func exe use %lu ms ***********************\n",ulTimeUsedMs);

//    printf("Time spend:tv_sec[%ld], tv_usec[%ld](ns)\n", tsEnd.tv_sec-tsBegin.tv_sec,
//			tsEnd.tv_nsec-tsBegin.tv_nsec);
	return ulTimeUsedMs;

}

void func2(void *parm)
{
	char szTemp[4096];
	memset(szTemp, 0, sizeof(szTemp));
	szTemp[0] = 22;
}

void testCalcRunTime()
{
//	int iTemp = 0x666;
//	caclFuncRunTime(func, (void *)&iTemp);

//	puts("\ninit: ");
	caclFuncRunTime(func2, NULL, 1);
//	puts("\nmemset: ");
//	caclFuncRunTime(func2, NULL, 1000*1000);
}
