/*
 * LocalAndGmtime.cpp
 *	time_t 带有年月日的结构体 互转
 *  Created on: 2017-9-22
 *      Author: root
 */
#include <time.h>
#include <stdio.h>

void printTmStruct(tm *pTm)
{
	printf("tm_year[%d], tm_mon[%d], tm_mday[%d]\n",pTm->tm_year +1900, pTm->tm_mon, pTm->tm_mday);
	printf("tm_hour[%d], tm_min[%d], tm_sec[%d]\n",pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
}

void localAndGmtimeFuncTest()
{
	time_t tTime = time(NULL);

	struct tm *pTm;

	pTm = gmtime(&tTime);//xxx 将time_t转化为带有年月日的结构体
	puts("gmtime Rus: gmtime return UTC0 time");
	printTmStruct(pTm); putchar('\n');
	time_t tmMakeGm = mktime(pTm);//mktime与localtime函数功能相反

	pTm = localtime(&tTime);//xxx 将time_t转化为带有年月日的结构体
	puts("localtime Rus: gmtime return UTCx time,由/etc/localtime决定时区");
	printTmStruct(pTm); putchar('\n');
	time_t tmMakeLocal = mktime(pTm);//xxx wrong use! mktime与localtime函数功能相反

	printf("time[%ld], tmMakeGm[%ld], tmMakeLocal[%ld]\n", tTime, tmMakeGm, tmMakeLocal);
}
