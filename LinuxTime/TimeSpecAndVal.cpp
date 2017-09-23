/*
 * TimeSpecAndVal.cpp
 * 比较精确的时间计数
 *  Created on: 2017-9-22
 *      Author: root
 */
#include <stdio.h>
#include <time.h>
#include <sys/time.h> //gettimeofday

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
