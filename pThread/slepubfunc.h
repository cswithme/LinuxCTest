/*
 *filename:	slepubfunc.h
 *brief:		定义一些终端设备公用的小函数
 *Created on: 2011-5-31
 *Author: 	jiangzj
 */

#ifndef SLEPUBFUNC_H_
#define SLEPUBFUNC_H_

//#include "slepublic/slepublic/slepublic.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
//信号量操作 zhangbb 2012
#include <signal.h>
#include <semaphore.h>
#include <errno.h>
#include <stdlib.h>
using namespace std;

#ifndef WORD
typedef unsigned short      WORD;
#endif

typedef struct __ST_TIMEOUT_JUDGE {
	timespec start;
	timespec end;
	int iTimeout;
} ST_TIMEOUT_JUDGE;

enum EM_TIMEOUT_FLAG {
	TIMEOUT_SECOND = 0,/*秒*/
	TIMEOUT_MILLI_SECOND = 1,
/*毫秒*/
};

/*! \fn HexStringToHex(unsigned char *pHexString, unsigned char *pHex)
 * \brief
 * \param[in] 	pHexString 		---010D2303
 * \param[out] 	pHex 				---pHex[0]=1; pHex[1]=13; pHex[2]=35; pHex[3]=3;
 * \return 	 	void
 * \author 		郭玉臻
 * \date 		 	2010-03-16
 */
void HexStringToHex(unsigned char *pHexString, unsigned char *pHex);

/*! \fn BcdStringToBcd(unsigned char *pBcdString, unsigned char *pBcd)
 * \brief
 * \param[in] 	pBcdString 		---20100316
 * \param[out] 	pBcd 				---pHex[0]=20; pHex[1]=10; pHex[2]=3; pHex[3]=16;
 * \return 	 	void
 * \author 		郭玉臻
 * \date 		 	2010-03-16
 */
void BcdStringToBcd(unsigned char *pBcdString, unsigned char *pBcd);

/*! \fn BcdToString(unsigned char *pszBcd, int iStringLength, unsigned char *pszBcdString)
 * \brief
 * \param[in] 	pszBcd 			---pszBcd[0]=20; pszBcd[1]=10; pszBcd[2]=3; pszBcd[3]=16;
 * \param[out] 	pszBcdString 		---20100316
 * \return 	 	void
 * \author 		郭玉臻
 * \date 		 	2010-03-16
 */
void BcdToString(unsigned char *pszBcd, int iStringLength,
		unsigned char *pszBcdString);

/*! \fn HexToString(unsigned char *pszHex, int iStringLength, unsigned char *pszHexString)
 * \brief
 * \param[in] 	pszHex 			---pHex[0]=1; pHex[1]=13; pHex[2]=35; pHex[3]=3;
 * \param[out] 	pszHexString 		---010D2303
 * \return 	 	void
 * \author 		郭玉臻
 * \date 		 	2010-03-16
 */
void HexToString(unsigned char *pszHex, int iStringLength,
		unsigned char *pszHexString);

/*! \fn int PubNumericToBCDStr(unsigned char *pcNStr, int iNLen, unsigned char *pcBCDStr)
 *  \brief  将缓冲区的数字字符串转化成BCD码数据
 *  \param[in] pcNStr 数字字符串
 *  \param[in] iNLen 数字字符串长度
 *  \param[out] pcBCDStr 数字字符串
 *  \return  0 成功 -1 失败
 *  \date    2010-05-04
 */

int PubNumericToBCDStr(unsigned char *pcNStr, int iNLen,
		unsigned char *pcBCDStr);

/**
 * \brief  		GetCurrentTime 获取当前的系统时间
 * \param[in]:	入参：
 * \param[out]:	出参：char *szDate,char *szTime
 * \return: 		返回类型：void
 * \author:		作者：songyn
 * \date:			时间：2010-04-13
 */
void GetCurrentTime(unsigned char *szDate, unsigned char *szTime);

void GetLocalTime(char *pszTime);//获取当前时间


/*!\fn
 * \brief 	 获取当前时间(7HEX 格式)
 * \param[out] pszTime 格式为:  pszDateTimeHexStr = {0x20, 0x14, 0x04, 0x02, 0x18, 0x36, 0x45}
 *             表示2014年04月02日 18点36分45秒
 * \return 	 void
 * \author
 * \date 		2014-04-02
 */
void GetLocalDateTimeHexStr(char *pszDateTimeHexStr);


/**
 * \brief  		GetCurrentTimeStr 获取当前的系统时间 字符串编码
 * \param[in]:	入参：无
 * \param[out]:	出参：char *szDate,char *szTime
 * \return: 		返回类型：void
 * \author:		作者：songyn
 * \date:			时间：2010-04-13
 */
void GetCurrentTimeStr(char *pszDate, char *pszTime);

void StringToBcd(unsigned char *pString, unsigned char *pBcd);

bool StringToBCD(const char* pszWord, char * pszBcdRet);

char NumericToBCD(const char* pszWord);

void GetLocalTime(char *pszDate, char *pszTime);

void ReverseInt(char *pszSource, char *pszDest);

void GetLocalTimeString(char *pszTime);

//zhangbb add 2013-03-06
void ConvertSecToString(int iSecond, char *pszDate, char *pszTime);
void ConvertSecToString(int iSecond, char *pszDateTime);

void StringToId(char *pInputString, char *pOutputString);

void IdToString(char *pInputString, char *pOutputString);
void HexStringtoHEX(unsigned char *pHexString, unsigned char *pHex);

//按separator分割字符串
void Split(char *src, const char *separator, char **dest, int *num);

/*截取src字符串中,从下标为start开始到end-1(end前面)的字符串保存在dest中(下标从0开始)*/
void substring(char *dest, char *src, int start, int end);

int GetComplileDate(int *piYear, int *piMonth, int *piDay);

/**
 * \brief  		 将字节数组转换成对应的字符串，如：{0x12,0x34} 转换成"12 34"
 * \param[in]:	pcBytes: 输入char*
 * 				iByteSize: pcBytes长度
 * 				iStringSize:pszString 长度，起安全预警作用，防止内存溢出
 * \param[out]:	pszString:格式化后字符
 *
 * \return: 	返回类型：void
 * \author:		作者：guoxh
 * \date:			时间：2010-04-13
 */
bool BytesToHexStringForLog(unsigned char * pcBytes, char * pszString,
		int iByteSize,int iStringSize);

int sem_wait_i(sem_t *Sem, int iTimeout);

int initStTimeoutJudge(ST_TIMEOUT_JUDGE *pst_timeout_judge, int iTimeout,
		EM_TIMEOUT_FLAG emTimeoutFlag);

bool CheckTimeOut(ST_TIMEOUT_JUDGE *pst_timeout_judge);

int DateConvent(char*DbfDate, char*DbfTime, char*OperDate);

void SwitchTime(unsigned int iTime, char *pszDate, char *pszTime);

/*! ReverseWord

 * 函数功能 将接受来的数据和发送的数据翻转
 * 输入参数：	WORD value 需要翻转的数值
 * \return 翻转之后的数值
 * \author 王洪峰
 */
WORD ReverseWord(WORD wValue);

unsigned int Crc16(char * pStart, int length, unsigned int crc16);

void PrintBufContent(char *buf, unsigned int iBufLen);

int PubStrTimeToTime_t( const char *pcaDate, const char *pcaTime, time_t *ttm );


/* 20130108
 * 由参数指定时间, 转换为 从2000年1月1日开始的秒数
 *
 * GMT	Long类型的数，用于表示格林威治标准时间，数值上等于系统参数设定的起始日期到所要表示时刻所经过的秒数
 *
 * 如：系统默认设定为2000年1月1日，则0秒即标识格林威治的2000年1月1日 00:00:00
 *
 **/
int PubStrToTime(const char *pcaDate, const char *pcaTime, time_t *ttm );


/* 将从2000年1月1日0点 开始算起的秒数，转换为 时间字符串
 * 如： 414674373 转换为： pszDate = 20130220 ， pszTime = 111933
 * 参数 tTimeFrom2000  2000年1月1日0点 算起的秒数  */
int DateTimeConvert_Convert_TimeTFrom2000_To_DateTimeString(time_t tTimeFrom2000, char *pszDate, char *pszTime);

/* 将从2000年1月1日0点 开始算起的秒数，转换为 struct tm 类型的对象
 * 如： 414674373 转换为： （pszDate = 20130220 pszTime = 111933）
 * 参数 tTimeFrom2000 :  2000年1月1日0点 算起的秒数 */
int DateTimeConvert_Convert_TimeTFrom2000_To_TM(time_t tTimeFrom2000, struct tm *tmDateTime);


/* 将字符串格式的日期（pDate 格式为：20130320），转换为2000年01月01日 开始的天数,
 * 如： 当 2000年01月01日， 换后的的值为： iDateInterval = 1 */
int DateTimeConvert_Convert_DateString_To_Date2From2000(char *pDate, int *piDateInterval);

/* 将2000年01月01日 开始的天数, 转换为 日期字符串， 转换后， pDate 的格式为： 20130320
 * 如： 当iDateInterval = 1， 表示 2000年01月01日 */
int DateTimeConvert_Convert_Date2From2000_To_DateString(int iDateInterval, char *pDate);

/* 将2000年01月01日 开始的天数, 转换为 tm *tmDateTime 类型的结构
 * 如： 当iDateInterval = 1， 表示 2000年01月01日 */
int DateTimeConvert_Convert_Date2From2000_To_TM(int iDateInterval, struct tm *tmDateTime);

/* 例如： 20130101 转换为： 20 13 01 01 Motol */
int HexStringToMotolUintValue(char *pszHexString, unsigned int *uiValue);

/* 例如： 20130101 转换为： 20 13 01 01 Motol */
int HexStringToMotolIntValue(char *pszHexString, int *uiValue);

/* 例如： 20130101 转换为： 20 13 01 01 Motol  */
int HexStringToMotolIntBuffer(char *pszHexString, char *pszUintBuf);

/* 例如： 20130101 转换为： 01 01 13 20 Intel */
int HexStringToIntelUintValue(char *pszHexString, unsigned int *uiValue);

/* 例如： 20130101 转换为： 01 01 13 20 Intel */
int HexStringToIntelIntValue(char *pszHexString, int *uiValue);

/* 例如： 20130101 转换为： 01 01 13 20 Intel */
int HexStringToIntelIntBuffer(char *pszHexString, char *pszUintBuf);

//系统默认设定为2000年1月1日，则0秒即标识格林威治的2000年1月1日 00:00:00
int PubGetOriTime( const char *pcaDate, const char *pcaTime, time_t *ttm );

/*将元转换成分，indata:单位为元的字符串数组;返回值为分的整数*/
int YuanToFen(const char * indata);


/*! \fn char CreateDirectory( const char *szDirectoryPath , int iDirPermission)
 * \brief 		以指定的权限创建目录，
 * \param[in] 	szDirectoryPath	需要创建的文件目录路径
 * \param[in] 	iDirPermission	创建目录时，为所创建的目录所指定的权限
 * \return 		bool 返回结果，成功返回True 失败返回false
 * \author 		张保兵
 * \date 		2013-06-26
 */
bool CreateDirectory( const char *szDirectoryPath , int iDirPermission );

/*! \fn char CheckTimeOut(ST_TIMEOUT_JUDGE *pst_timeout_judge_start, ST_TIMEOUT_JUDGE *pst_timeout_judge_end, int iTimeout)
 * \brief 		判断两个时刻时间是否超时，
 * \param[in] 	pst_timeout_judge_start 开始时刻
 * \param[in] 	pst_timeout_judge_end	结束时刻
 * \param[in] 	iTimeout	超时时间
 * \return 		bool 返回结果，成功返回True 失败返回false
 * \author 		张保兵
 * \date 		2013-06-26
 */
bool CheckTimeOut(ST_TIMEOUT_JUDGE *pst_timeout_judge_start, ST_TIMEOUT_JUDGE *pst_timeout_judge_end, int iTimeout);

bool ModifyIPString(char *pszInBuff, char *pszOutBuff);

void HEXStringToHEX(unsigned char *pHexString, unsigned char *pHex);

#endif /* SLEPUBFUNC_CPP_ */

