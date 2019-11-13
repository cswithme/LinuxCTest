/*
 * LocalAndGmtime.cpp
 *	time_t 带有年月日的结构体 互转
 *  Created on: 2017-9-22
 *      Author: root
 */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	//Fixit localtime函数不可重入,多线程调用应用localtime_r
	pTm = localtime(&tTime);//xxx 将time_t转化为带有年月日的结构体
	puts("localtime Rus: gmtime return UTCx time,由/etc/localtime决定时区");
	printTmStruct(pTm); putchar('\n');
	time_t tmMakeLocal = mktime(pTm);//xxx wrong use! mktime与localtime函数功能相反

	printf("time[%ld], tmMakeGm[%ld], tmMakeLocal[%ld]\n", tTime, tmMakeGm, tmMakeLocal);
}

int HexStrToDec(char *pszStr, int iStrLen)
{
	char szTmp[9]; memset(&szTmp, 0, sizeof(szTmp));
	char *pCurPos = szTmp;
	for(int i=0; i<iStrLen; ++i){
		pCurPos += sprintf(pCurPos, "%02X", pszStr[i]);
	}

	return atoi(szTmp);
}

int BCD_To_Decimal(const char *pszStr, int iStrLen)
{
	char szTmp[9]; memset(&szTmp, 0, sizeof(szTmp));
	char *pCurPos = szTmp;
	for(int i=0; i<iStrLen; ++i){
		pCurPos += sprintf(pCurPos, "%02X", pszStr[i]);
	}

	return atoi(szTmp);
}

//pszBCDTime "\x20\x19\x10\x16\x22\x21\x53"
//return 2019-10-16 22:21:13对应的time_t
time_t BCD_to_TimeT(const char* pszBCDTime)
{
//	const char* pszBCDTime = "\x20\x19\x10\x16\x22\x21\x53"; //2019-10-16 22:21:13
	struct tm tmTrans; memset(&tmTrans, 0, sizeof(struct tm));

	tmTrans.tm_sec = BCD_To_Decimal(pszBCDTime+6, 1);
	tmTrans.tm_min = BCD_To_Decimal(pszBCDTime+5, 1);
	tmTrans.tm_hour = BCD_To_Decimal(pszBCDTime+4, 1);
	tmTrans.tm_mday = BCD_To_Decimal(pszBCDTime+3, 1);
	tmTrans.tm_mon = BCD_To_Decimal(pszBCDTime+2, 1)-1;
	tmTrans.tm_year = BCD_To_Decimal(pszBCDTime+0, 2)-1900;

	return  mktime(&tmTrans);
}

//t 2019-10-16 22:21:13对应的time_t
//pszBCDTime(出参) "\x20\x19\x10\x16\x22\x21\x53"
void TimeT_to_BCD(time_t t, char* pszBCDTime)
{
	struct tm stTm;
	localtime_r(&t, &stTm);
	sprintf(pszBCDTime, "%04d%02d%02d%02d%02d%02d", stTm.tm_year+1900, stTm.tm_mon+1, stTm.tm_mday,
			stTm.tm_hour, stTm.tm_min, stTm.tm_sec);
}

//2019 1016 222113
void tempTest()
{
	char CurrentTime[8] = {0x20, 0x19, 0x10, 0x31, 0x23, 0x59, 0x50};
	time_t tBiz = BCD_to_TimeT(CurrentTime);
	char szBeginTime[8]; memset(szBeginTime, 0, sizeof(szBeginTime));
	TimeT_to_BCD(tBiz+10, szBeginTime);
	puts(szBeginTime);

//	struct tm tmTrans; memset(&tmTrans, 0, sizeof(struct tm));
//
//	tmTrans.tm_sec = HexStrToDec(CurrentTime+6, 1);
//	tmTrans.tm_min = HexStrToDec(CurrentTime+5, 1);
//	tmTrans.tm_hour = HexStrToDec(CurrentTime+4, 1);
//	tmTrans.tm_mday = HexStrToDec(CurrentTime+3, 1);
//	tmTrans.tm_mon = HexStrToDec(CurrentTime+2, 1)-1;
//	tmTrans.tm_year = HexStrToDec(CurrentTime+0, 2)-1900;
//
//	time_t tStartTime = mktime(&tmTrans)+10;
//	struct tm tmStartTime;
//	localtime_r(&tStartTime, &tmStartTime);
//
//	char szStartTime[8]; memset(szStartTime, 0, sizeof(szStartTime));
//	sprintf(szStartTime, "%04d%02d%02d%02d%02d%02d", tmStartTime.tm_year+1900, tmStartTime.tm_mon+1, tmStartTime.tm_mday,
//			tmStartTime.tm_hour, tmStartTime.tm_min, tmStartTime.tm_sec);
//
//	puts(szStartTime);

}
