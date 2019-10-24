/*
 *filename:	slepubfunc.cpp
 *brief:		定义一些终端设备公用的小函数
 *Created on: 2011-5-31
 *Author: 	jiangzj
 */

#include "slepubfunc.h"
#include "time.h"
#include <stdio.h>
#include <iostream>

#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
/*! ReverseWord

 * 函数功能 将接受来的数据和发送的数据翻转
 * 输入参数：	WORD value 需要翻转的数值
 * \return 翻转之后的数值
 * \author 王洪峰
 */
WORD ReverseWord(WORD wValue) {
	return (wValue >> 8) | ((wValue & 0xFF) << 8);
}

unsigned int Crc16(char * pStart, int length, unsigned int crc16) {
	unsigned int crc16_tab[256] = { 0x0000, 0x1189, 0x2312, 0x329b, 0x4624,
			0x57ad, 0x6536, 0x74bf, 0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c,
			0xdbe5, 0xe97e, 0xf8f7, 0x1081, 0x0108, 0x3393, 0x221a, 0x56a5,
			0x472c, 0x75b7, 0x643e, 0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed,
			0xcb64, 0xf9ff, 0xe876, 0x2102, 0x308b, 0x0210, 0x1399, 0x6726,
			0x76af, 0x4434, 0x55bd, 0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e,
			0xfae7, 0xc87c, 0xd9f5, 0x3183, 0x200a, 0x1291, 0x0318, 0x77a7,
			0x662e, 0x54b5, 0x453c, 0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef,
			0xea66, 0xd8fd, 0xc974, 0x4204, 0x538d, 0x6116, 0x709f, 0x0420,
			0x15a9, 0x2732, 0x36bb, 0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868,
			0x99e1, 0xab7a, 0xbaf3, 0x5285, 0x430c, 0x7197, 0x601e, 0x14a1,
			0x0528, 0x37b3, 0x263a, 0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9,
			0x8960, 0xbbfb, 0xaa72, 0x6306, 0x728f, 0x4014, 0x519d, 0x2522,
			0x34ab, 0x0630, 0x17b9, 0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a,
			0xb8e3, 0x8a78, 0x9bf1, 0x7387, 0x620e, 0x5095, 0x411c, 0x35a3,
			0x242a, 0x16b1, 0x0738, 0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb,
			0xa862, 0x9af9, 0x8b70, 0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c,
			0xd3a5, 0xe13e, 0xf0b7, 0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64,
			0x5fed, 0x6d76, 0x7cff, 0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad,
			0xc324, 0xf1bf, 0xe036, 0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5,
			0x4f6c, 0x7df7, 0x6c7e, 0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e,
			0xf2a7, 0xc03c, 0xd1b5, 0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66,
			0x7eef, 0x4c74, 0x5dfd, 0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af,
			0xe226, 0xd0bd, 0xc134, 0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7,
			0x6e6e, 0x5cf5, 0x4d7c, 0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028,
			0x91a1, 0xa33a, 0xb2b3, 0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60,
			0x1de9, 0x2f72, 0x3efb, 0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9,
			0x8120, 0xb3bb, 0xa232, 0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1,
			0x0d68, 0x3ff3, 0x2e7a, 0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a,
			0xb0a3, 0x8238, 0x93b1, 0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62,
			0x3ceb, 0x0e70, 0x1ff9, 0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab,
			0xa022, 0x92b9, 0x8330, 0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3,
			0x2c6a, 0x1ef1, 0x0f78 };

	crc16 = 0xFFFF;
	//	register        U8_t  *pS = pStart;
	register char *pS = (char *) pStart; //modify niuxsh 20110620( 错误：从类型 ‘char*’ 到类型 ‘U8_t*’ 的转换无效)
	register const unsigned int *p_crc16_tab = crc16_tab;

	while (length--)
		crc16 = (crc16 >> 8) ^ p_crc16_tab[(crc16 ^ *pS++) & 0xff];

	return crc16;
}

/**
 * \brief  		GetCurrentTime 获取当前的系统时间 BCD编码
 * \param[in]:	入参：无
 * \param[out]:	出参：char *szDate,char *szTime
 * \return: 		返回类型：void
 * \author:		作者：songyn
 * \date:			时间：2010-04-13
 */
void GetCurrentTime(unsigned char *szDate, unsigned char *szTime) {
	//gCoreLog.LogInfo(0,0,(char*)"[%s][%d]计算时间。",__FILE__,__LINE__);
//	time_t timep;
//	struct tm *p;
//	time(&timep);
//	p = localtime(&timep); //获取当前时间
	time_t tm_l;
	struct tm Time;
	tm_l = time(NULL);
	struct tm *p = localtime_r(&tm_l, &Time);

	unsigned char szYear[2] = { 0 };
	//int iyear = 1900+p->tm_year;
	//memcpy(szYear,(void*)iyear,sizeof(iyear));
	szYear[1] = (1900 + p->tm_year) % 100 / 10 * 16 + (1900 + p->tm_year) % 100
			% 10;
	szYear[0] = (1900 + p->tm_year) / 100 / 10 * 16 + (1900 + p->tm_year) / 100
			% 10;
	unsigned char szMonth = (1 + p->tm_mon) / 10 * 16 + (1 + p->tm_mon) % 10;
	unsigned char szDay = p->tm_mday / 10 * 16 + p->tm_mday % 10;

	unsigned char szHour = p->tm_hour / 10 * 16 + p->tm_hour % 10;
	unsigned char szMin = p->tm_min / 10 * 16 + p->tm_min % 10;
	unsigned char szSec = p->tm_sec / 10 * 16 + p->tm_sec % 10;

	memcpy(szDate, szYear, sizeof(szYear));
	memcpy(szDate + sizeof(szYear), &szMonth, sizeof(szMonth));
	memcpy(szDate + sizeof(szYear) + sizeof(szMonth), &szDay, sizeof(szDay));

	memcpy(szTime, &szHour, sizeof(szHour));
	memcpy(szTime + sizeof(szHour), &szMin, sizeof(szMin));
	memcpy(szTime + sizeof(szHour) + sizeof(szMin), &szSec, sizeof(szSec));
}
/**
 * \brief  		GetCurrentTimeStr 获取当前的系统时间 字符串编码
 * \param[in]:	入参：无
 * \param[out]:	出参：char *szDate,char *szTime
 * \return: 		返回类型：void
 * \author:		作者：songyn
 * \date:			时间：2010-04-13
 */
void GetCurrentTimeStr(char *pszDate, char *pszTime) {
	if ((pszDate == NULL) || (pszTime == NULL)) {
		return;
	}

	time_t tm_l;
	struct tm Time;
	tm_l = time(NULL);
	struct tm tm_p = *localtime_r(&tm_l, &Time);

	sprintf(pszDate, "%04d%02d%02d", tm_p.tm_year + 1900, tm_p.tm_mon + 1,
			tm_p.tm_mday);

	sprintf(pszTime, "%02d%02d%02d", tm_p.tm_hour, tm_p.tm_min, tm_p.tm_sec);

}

/*! \fn CTvmTicketTpuApp::HexStringToHex(unsigned char *pHexString, unsigned char *pHex)
 * \brief
 * \param[in] 	pHexString 		---010D2303
 * \param[out] 	pHex 				---pHex[3]=0x01; pHex[2]=0x13; pHex[1]=0x35; pHex[0]=0x03;
 * \return 	 	void
 * \author 		郭玉臻
 * \date 		 	2010-03-16
 */
void HexStringToHex(unsigned char *pHexString, unsigned char *pHex) {
	if (NULL == pHexString) {
		return;
	}
	char szTemp[16] = { 0 };

	unsigned int uiTmp = 0;
	int iLength = strlen((char*) pHexString);
	int k = iLength / 2 - 1;
	for (int i = 0; i < iLength; i++) {
		memcpy(szTemp, pHexString + i, 2);
		sscanf(szTemp, "%02x", &uiTmp);
		pHex[k--] = uiTmp;
		i++;
	}
	return;
}

/*! \fn CTvmTicketTpuApp::HEXStringToHEX(unsigned char *pHexString, unsigned char *pHex)
 * \brief
 * \param[in] 	pHexString 		---010D2303
 * \param[out] 	pHex 				---pHex[0]=0x01; pHex[1]=0x0D; pHex[2]=0x23; pHex[3]=0x03;
 * \return 	 	void
 * \author 		lixm
 * \date 		 	2014-10-21
 */
void HEXStringToHEX(unsigned char *pHexString, unsigned char *pHex) {
	if (NULL == pHexString) {
		return;
	}
	char szTemp[16] = { 0 };

	unsigned int uiTmp = 0;
	int iLength = strlen((char*) pHexString);
	int k = 0;
	for (int i = 0; i < iLength; i++) {
		memcpy(szTemp, pHexString + i, 2);
		sscanf(szTemp, "%02X", &uiTmp);
		pHex[k++] = uiTmp;
		i++;
	}
	return;
}


/*! \fn CTvmTicketTpuApp::BcdStringToBcd(unsigned char *pBcdString, unsigned char *pBcd)
 * \brief
 * \param[in] 	pBcdString 		---20100316
 * \param[out] 	pBcd 				---pHex[0]=20; pHex[1]=10; pHex[2]=3; pHex[3]=16;
 * \return 	 	void
 * \author 		郭玉臻
 * \date 		 	2010-03-16
 */
void BcdStringToBcd(unsigned char *pBcdString, unsigned char *pBcd) {
	if (NULL == pBcdString) {
		return;
	}
	char szTemp[16] = { 0 };
	int k = 0;
	int iLength = strlen((char*) pBcdString);
	for (int i = 0; i < iLength; i++) {
		memcpy(szTemp, pBcdString + i, 2);
		sscanf(szTemp, "%d", (int*) &pBcd[k++]);
		i++;
	}
	return;
}

/*! \fn BcdToString(unsigned char *pszBcd, int iStringLength, unsigned char *pszBcdString)
 * \brief
 * \param[in] 	pszBcd 			---pszBcd[0]=20; pszBcd[1]=10; pszBcd[2]=3; pszBcd[3]=16;
 * \param[out] 	pszBcdString 		---20100316
 * \return 	 	void
 * \author 		郭玉臻
 * \date 		 	2010-03-16
 */
void BcdToString(unsigned char *pszBcd, int iStringLength,
		unsigned char *pszBcdString) {
	char szTemp[16] = { 0 };
	for (int i = 0; i < iStringLength; i++) {
		sprintf(szTemp, "%02d", (int) pszBcd[i]);
		strcat((char*) pszBcdString, szTemp);
	}
	return;
}

/*! \fn HexToString(unsigned char *pszHex, int iStringLength, unsigned char *pszHexString)
 * \brief
 * \param[in] 	pszHex 			---pHex[0]=1; pHex[1]=13; pHex[2]=35; pHex[3]=3;
 * \param[out] 	pszHexString 		---010D2303
 * \return 	 	void
 * \author 		郭玉臻
 * 					jiangzj 在调用此函数前进行memset(pszHexString, 0, ***);
 * \date 		 	2010-03-16
 */
void HexToString(unsigned char *pszHex, int iStringLength,
		unsigned char *pszHexString) {
	if ((NULL == pszHex) || (NULL == pszHexString) || (0 >= iStringLength)) {
		return;
	}
	char szTemp[16] = { 0 };
	memset(pszHexString, 0, strlen((char *) pszHexString)); //如果pszHexString不为空串，则可能会溢出。
	for (int i = 0; i < iStringLength; i++) {
		sprintf(szTemp, "%02x", (int) pszHex[i]);
		strcat((char*) pszHexString, szTemp);
	}

	//	if( ( NULL == pszHex) || ( NULL == pszHexString) || ( 0 >= iStringLength))
	//	{
	//		return ;
	//	}
	//
	//	char szTemp[16]={0};
	//	char szDesStr[10]={0};
	//	for(int i=0; i<iStringLength; i++)
	//	{
	//		sprintf(szTemp, "%02x", (int)pszHex[i]);
	//		strcat((char*)szDesStr, szTemp);
	//	}
	//	strcpy( (char *)pszHexString,  szDesStr);
	return;
}

/*! \fn int PubNumericToBCDStr(unsigned char *pcNStr, int iNLen, unsigned char *pcBCDStr)
 *  \brief  将缓冲区的数字字符串转化成BCD码数据
 *  \param[in] pcNStr 数字字符串
 *  \param[in] iNLen 数字字符串长度
 *  \param[out] pcBCDStr 数字字符串
 *  \return  0 成功 -1 失败
 *  \date    2010-05-04
 */

int PubNumericToBCDStr(unsigned char *pcNStr, int iNLen,
		unsigned char *pcBCDStr) {
	unsigned char *pN = pcNStr;
	unsigned char *pB = pcBCDStr;
	unsigned char caBuffer[2];
	unsigned char cHigh, cLow;
	unsigned char iCount = 0;
	unsigned char iNCount = iNLen / 2 + iNLen % 2;

	if ((pcNStr == NULL) || (pcBCDStr == NULL)) {
		printf("[%s:%d] 转BCD码参数错误 !", __FILE__, __LINE__);
		return -1;
	}

	for (iCount = 0; iCount < iNCount; iCount++) {
		if ((iCount == 0) && (iNLen % 2 != 0)) {
			memset(caBuffer, '\0', sizeof(caBuffer));
			memcpy(caBuffer + 1, pN, 1);
			cHigh = (unsigned char) ((*(caBuffer + 0) - 0x30) << 4);
			cLow = (unsigned char) (*(caBuffer + 1) - 0x30);
			*pB = (unsigned char) (cHigh + cLow);
			pB += 1;
			pN += 1;
		} else {
			cHigh = (unsigned char) ((*(pN + 0) - 0x30) << 4);
			cLow = (unsigned char) (*(pN + 1) - 0x30);
			*pB = (unsigned char) (cHigh + cLow);
			pB += 1;
			pN += 2;
		}
	}
	return 0;
}

/*! \fn char NumericToBCD(const char* pcWord)
 * \brief 		把十进制的字符串转换成BCD码，如“20”-> 0x20
 * \param[in] 	pszWord	十进制的字符串
 * \return 		char 		BCD
 * \author 		孙桂刚
 * \date 		2009-09-01
 */
bool StringToBCD(const char* pszWord, char * pszBcdRet) {
	if (pszWord == NULL) {
		return false;
	}
	if ((strlen(pszWord) % 2) != 0) {
		return false;
	}
	unsigned int j = 0;
	for (unsigned int i = 0; i < strlen(pszWord); i = i + 2) {
		pszBcdRet[j] = NumericToBCD(pszWord + i);
		j++;
	}

	return pszBcdRet;
}

/*! \fn StringToBcd()
 * \brief 	 字符串转BCD码
 * \param[in]  pString 字符串 “20100308”
 * \param[out] pBcd BCD码 0x20 0x10 0x03 0x08
 * \return 	 void
 * \author 	 牛更五
 * \date 		2010-03-03
 */
void StringToBcd(unsigned char *pString, unsigned char *pBcd) {
	int k = 0;
	unsigned i = 0;
	unsigned char ucValue = 0;
	unsigned char szPack[32] = { 0 };

	memcpy(szPack, pString, strlen((const char *) pString));
	if ((strlen((const char *) szPack) % 2) != 0) {
		return;
	}

	for (i = 0; i < strlen((const char *) szPack); i++) {
		ucValue = (szPack[i++] & 0x0F) << 4;
		ucValue |= szPack[i] & 0x0F;
		pBcd[k++] = ucValue;
	}

	return;
}

/*! \fn char NumericToBCD(const char* pcWord)
 * \brief 		把十进制的字符串转换成BCD码，如“20”-> 0x20
 * \param[in] 	pszWord	十进制的字符串
 * \return 		char 		BCD
 * \author 		焦华杰
 * \date 		2009-09-01
 */
char NumericToBCD(const char* pszWord) {
	char szTemp[2] = { 0 };
	memcpy(szTemp, pszWord, sizeof(szTemp));

	if (pszWord[0] > '9' || pszWord[0] < '0')
		szTemp[0] = '0';

	if (pszWord[1] > '9' || pszWord[1] < '0')
		szTemp[1] = '0';

	char cHigh = (char) ((szTemp[0] - 0x30) << 4);
	char cLow = (char) (szTemp[1] - 0x30);

	return ((char) (cHigh + cLow));
}

/*! \fn GetLocalTime(char *pszTime)
 * \brief 	 获取当前时间
 * \param[out] pszTime 格式为："YYYYMMDDHHMMSS"
 * \return 	 void
 * \author 	 牛更五
 * \date 		2010-3-8
 */
void GetLocalTime(char *pszTime)
{
//	time_t timep;
//	struct tm *pTm;
	char szBuff[15] = { 0 };
//
//	time(&timep);
//	pTm = localtime(&timep);
	time_t tm_l;
	struct tm Time;
	tm_l = time(NULL);
	struct tm *pTm = localtime_r(&tm_l, &Time);
	fprintf(stderr, "Data=[%04d%02d%02d] Time=[%02d%02d%02d]\n", pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday,  pTm->tm_hour, pTm->tm_min, pTm->tm_sec);

	sprintf(szBuff, "%d%02d%02d", (1900 + pTm->tm_year), (1 + pTm->tm_mon),
			pTm->tm_mday);
	sprintf(szBuff + 8, "%02d%02d%02d", pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
	memcpy(pszTime, szBuff, 14);
}


/*! \fn GetLocalTime(char *pszTime)
 * \brief 	 获取当前时间(7HEX 格式)
 * \param[out] pszTime 格式为:  pszDateTimeHexStr = {0x20, 0x14, 0x04, 0x02, 0x18, 0x36, 0x45}
 *             表示2014年04月02日 18点36分45秒
 * \return 	 void
 * \author
 * \date 		2014-04-02
 */
void GetLocalDateTimeHexStr(char *pszDateTimeHexStr)
{
	time_t currentT;
	struct tm *tmCurrent;
	currentT = time(NULL);
	struct tm Time;
	tmCurrent = localtime_r(&currentT, &Time);

	//当前日期
	char szCurDate[9] = {0};
	int iCurDate = 0;
	sprintf(szCurDate, "%04d%02d%02d", tmCurrent->tm_year+1900, tmCurrent->tm_mon+1, tmCurrent->tm_mday);
	iCurDate = strtoll(szCurDate, NULL, 16);
	iCurDate = htonl(iCurDate);
	memcpy(pszDateTimeHexStr, &iCurDate, 4);	//当前日历日期

	//当前时间
	char szCurTime[9] = {0};
	int iCurTime = 0;
	sprintf(szCurTime, "%02d%02d%02d%s", tmCurrent->tm_hour, tmCurrent->tm_min, tmCurrent->tm_sec, "00");
	iCurTime = strtoll(szCurTime, NULL, 16);
	iCurTime = htonl(iCurTime);
	memcpy(pszDateTimeHexStr + 4, &iCurTime, 3);	 //当前日历时间

}



void GetLocalTime(char *pszDate, char *pszTime) {
	if ((pszDate == NULL) || (pszTime == NULL)) {
		return;
	}

	time_t tm_l;
	struct tm tm_p;
	struct tm Time;
	tm_l = time(NULL);
	tm_p = *localtime_r(&tm_l, &Time);

	sprintf(pszDate, "%04d%02d%02d", tm_p.tm_year + 1900, tm_p.tm_mon + 1,
			tm_p.tm_mday);

	sprintf(pszTime, "%02d%02d%02d", tm_p.tm_hour, tm_p.tm_min, tm_p.tm_sec);

}

void ConvertSecToString(int iSecond, char *pszDate, char *pszTime)
{
	if ((pszDate == NULL) || (pszTime == NULL))
	{
			return;
	}

	time_t tm_l;
	struct tm tm_p;
	struct tm Time;
	tm_l = (time_t)iSecond;
	tm_p = *localtime_r(&tm_l, &Time);
	sprintf(pszDate, "%04d%02d%02d", tm_p.tm_year + 1900, tm_p.tm_mon + 1,
			tm_p.tm_mday);
	sprintf(pszTime, "%02d%02d%02d", tm_p.tm_hour, tm_p.tm_min, tm_p.tm_sec);
}

void ConvertSecToString(int iSecond, char *pszDateTime)
{
	if(pszDateTime == NULL)
	{
			return;
	}

	time_t tm_l;
	struct tm tm_p;
	struct tm Time;
	tm_l = (time_t)iSecond;
	tm_p = *localtime_r(&tm_l, &Time);
	sprintf(pszDateTime, "%04d%02d%02d%02d%02d%02d", tm_p.tm_year + 1900, tm_p.tm_mon + 1, tm_p.tm_mday,tm_p.tm_hour, tm_p.tm_min, tm_p.tm_sec);
}


/*! \fn ReverseInt(char *pszSource, char *pszDest)
 * \brief 	 交换一个长度为4个字节的数组
 * \param[in]  pszSource 数据源
 * \param[out] pszDest 目标地址
 * \return 	 void
 * \author
 * \date 		2010-3-8
 */
void ReverseInt(char *pszSource, char *pszDest) {
	pszDest[0] = pszSource[3];
	pszDest[1] = pszSource[2];
	pszDest[2] = pszSource[1];
	pszDest[3] = pszSource[0];
}

/*! \fn GetLocalTime(char *pszTime)
 * \brief 	 获取当前时间
 * \param[out] pszTime 格式为："YYYYMMDDHHMMSS"
 * \return 	 void
 * \author
 * \date 		2010-3-8
 */
void GetLocalTimeString(char *pszTime) {
	time_t timep;
	struct tm *pTm;
	struct tm Time;
	char szBuff[15] = { 0 };

	time(&timep);
	pTm = localtime_r(&timep, &Time);

	fprintf(stderr, "tm_l = %ld Data=[%04d%02d%02d] Time=[%02d%02d%02d]\n", timep, pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday,  pTm->tm_hour, pTm->tm_min, pTm->tm_sec);

	sprintf(szBuff, "%d%02d%02d", (1900 + pTm->tm_year), (1 + pTm->tm_mon),
			pTm->tm_mday);
	sprintf(szBuff + 8, "%02d%02d%02d", pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
	memcpy(pszTime, szBuff, 14);
}

void StringToId(char *pInputString, char *pOutputString) {
	//根据天津钱票箱编码最新规则为10进制8位，－－20111226
	if (NULL == pInputString || NULL == pOutputString) {
		return;
	}

	//	memcpy(pOutputString,pInputString, strlen( pInputString));
	strcpy(pOutputString, pInputString);
	return;

	//////////////////////////////////////////////////////////////
	//	char szTemp[9] = {"FFFFFFFF"};
	//	char szResult[10] = {"FFFFFFFFF"};
	//	if(NULL==pInputString || NULL==pOutputString)
	//	{
	//		return ;
	//	}
	//	memset(pOutputString, 0, sizeof(pOutputString));
	//	if(strncmp(szTemp,pInputString,8)==0)
	//	{
	//		memcpy(pOutputString,szResult,9);
	//		return;
	//	}
	//	memcpy(pOutputString,pInputString,4);
	//	char sza[5]={0};
	//	memcpy(sza,pInputString+6,2);
	//	memcpy(sza+2,pInputString+4,2);
	//	sza[5]='\0';
	//	unsigned int i=0;
	//	sscanf(sza,"%x",&i);
	//	sprintf(pOutputString+4,"%05d",(int)i);
	////	pOutputString[10]= '\0';
	//	return;
}

void IdToString(char *pInputString, char *pOutputString) {
	//根据天津钱票箱编码最新规则为10进制8位，－－20111226
	if (NULL == pInputString || NULL == pOutputString) {
		return;
	}

	memcpy(pOutputString, pInputString, strlen(pInputString));
	return;
	///////////////////////////////////////////////////////////
	//	char szTemp[9] = {"FFFFFFFF"};
	//	char szResult[10] = {"FFFFFFFFF"};
	//	if(NULL==pInputString || NULL==pOutputString)
	//	{
	//		return ;
	//	}
	//	memset(pOutputString, 0, sizeof(pOutputString));
	//	if(strncmp(szTemp,pInputString,8)==0)
	//	{
	//		memcpy(pOutputString,szResult,9);
	//		return;
	//	}
	//	memcpy(pOutputString,pInputString,4);
	//	char sza[6]={0};
	//	memcpy(sza,pInputString+4,5);
	//	unsigned int i=0;
	//	sscanf(sza,"%d",&i);
	//
	//	char szHex[6]= { 0};
	//	sprintf( szHex, "%04x", i);
	//
	//	memcpy(pOutputString+4, szHex+2, 2);
	//	memcpy(pOutputString+6, szHex, 2);
	//
	//	return;
}

//与 HexStringToHex 转换后的结果对应字节是相反的
void HexStringtoHEX(unsigned char *pHexString, unsigned char *pHex) {
	if (NULL == pHexString) {
		return;
	}
	char szTemp[16] = { 0 };
	int k = 0;
	int iLength = strlen((char*) pHexString);
	for (int i = 0; i < iLength; i++) {
		memcpy(szTemp, pHexString + i, 2);
		sscanf(szTemp, "%x", (int*) &pHex[k++]);
		i++;
	}
	return;

}

void Split(char *src, const char *separator, char **dest, int *num) {
	char *pNext;
	int count = 0;

	if (src == NULL || strlen(src) == 0)
		return;
	if (separator == NULL || strlen(separator) == 0)
		return;

	pNext = strtok(src, separator);

	while (pNext != NULL) {
		*dest++ = pNext;
		++count;
		pNext = strtok(NULL, separator);
	}

	*num = count;
}

/*截取src字符串中,从下标为start开始到end-1(end前面)的字符串保存在dest中(下标从0开始)*/
void substring(char *dest, char *src, int start, int end) {
	//char *p=src;
	int i = start;
	if (start > (int) strlen(src))
		return;

	if (end > (int) strlen(src))
		end = strlen(src);

	while (i < end) {
		dest[i - start] = src[i];
		i++;
	}
	dest[i - start] = '\0';
	return;
}

int GetComplileDate(int *piYear, int *piMonth, int *piDay) {
	const int MONTH_PER_YEAR = 12;
	const char szEnglishMonth[MONTH_PER_YEAR][4] = { "Jan", "Feb", "Mar",
			"Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	char szTmp[40] = { 0 };
	char szMonth[4] = { 0 };
	int iYear, iMonth, iDay;//,,
	int iResult = 0;
	sprintf(szTmp, "%s", __DATE__);

	sscanf(szTmp, "%s %d %d", szMonth, &iDay, &iYear);
	sscanf(szMonth, "%d", &iMonth);

	strncpy(szMonth, szTmp, 4);
	szMonth[3] = '\0';
	for (int i = 0; MONTH_PER_YEAR; i++) {
		if (strncmp(szMonth, szEnglishMonth[i], 3) == 0) {
			iMonth = i + 1;
			break;
		}
	}

	iResult = iYear * 65536 + iMonth * 256 + iDay;
	*piYear = iYear;
	*piMonth = iMonth;
	*piDay = iDay;
	return iResult;
}

bool BytesToHexStringForLog(unsigned char * pcBytes, char * pszString, int iByteSize ,int iStringSize)
{
	if(pcBytes == NULL || pszString == NULL || iByteSize < 0 || iStringSize < 0)
	{
		return false;
	}

	int offset = 0;
	for (int i=0;i<16;i++)
	{
		if(i%16 == 0)
		{
			if (offset + 1 > iStringSize -1)
			{
				return false;
			}
			offset += sprintf(pszString+offset,"\n");
		}

		if (offset + 3 > iStringSize -1)
		{
			return false;
		}
		offset += sprintf (pszString+offset, "%02x ", i) ;
	}

	for (int i = 0; i < iByteSize ; i ++)
	{
		if(i%16 == 0)
		{
			if (offset + 1 > iStringSize -1)
			{
				return false;
			}
			offset += sprintf(pszString+offset,"\n");
		}

		if (offset + 3 > iStringSize -1)
		{
			return false;
		}
		offset += sprintf (pszString+offset, "%02X ", * (pcBytes + i)) ;
	}

	return true ;
}

/*! initStTimeoutJudge( ST_TIMEOUT_JUDGE *pst_timeout_judge, int iTimeout,EM_TIMEOUT_FLAG emTimeoutFlag )
 * \brief	初始化超时等待结构体，iTimeout为等待时间数值。
 * \param(in) *pst_timeout_judge 超时等待结构体
 * \param(in) iTimeout 等待时间数
 * \param(in) emTimeoutFlag 等待时间的单位标记，秒、毫秒
 * \param(out) void
 * \return int 成功返回0，其他失败
 */
int initStTimeoutJudge(ST_TIMEOUT_JUDGE *pst_timeout_judge, int iTimeout,
		EM_TIMEOUT_FLAG emTimeoutFlag) {
	timespec end;
	clock_gettime(CLOCK_MONOTONIC, &end);
	memcpy(&pst_timeout_judge->start, &end, sizeof(end));

	long int iMs;//毫秒数
	switch (emTimeoutFlag) {
	case TIMEOUT_SECOND:
		iMs = iTimeout * 1000;
		break;
	case TIMEOUT_MILLI_SECOND:
		iMs = iTimeout;
		break;
	default:
		break;
	}
	long int iNesc = 0;//需要等待的纳秒数
	iNesc = (iMs % 1000) * (1000 * 1000);
	if ((1000 * 1000 * 1000 - end.tv_nsec) > iNesc) {
		end.tv_sec += (iMs / 1000); //+加上等待时间的秒数
		end.tv_nsec += iNesc;//+加上等待时间纳秒数
	} else {
		end.tv_sec += (iMs / 1000) + 1; //+加上等待时间的秒数
		end.tv_nsec += iNesc - 1000 * 1000 * 1000;//+加上等待时间纳秒数
	}
	memcpy(&pst_timeout_judge->end, &end, sizeof(end));
	pst_timeout_judge->iTimeout = iTimeout;
	return 0;
}

bool CheckTimeOut(ST_TIMEOUT_JUDGE *pst_timeout_judge) {
	timespec times;
	clock_gettime(CLOCK_MONOTONIC, &times);
	if (times.tv_sec > pst_timeout_judge->end.tv_sec)
		return true;
	else if (times.tv_sec == pst_timeout_judge->end.tv_sec && times.tv_nsec
			> pst_timeout_judge->end.tv_nsec)
		return true;
	return false;
}


//zhangbb add 判断两个时刻之间的差值是否超时
bool CheckTimeOut(ST_TIMEOUT_JUDGE *pst_timeout_judge_start, ST_TIMEOUT_JUDGE *pst_timeout_judge_end, int iTimeout)
{
	if(pst_timeout_judge_start->end.tv_sec - pst_timeout_judge_end->end.tv_sec >= iTimeout)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*! sem_wait_i( sem_t *Sem, int iTimeout )
 * 函数功能 等待信号量变成0，iTimeout为等待时间，若mswait<0则无穷等待，否则等待若干iTimeout毫秒。
 * \param *Sem 等待的信号量
 * \param iTimeout 超时等待时间
 * \return iResult 等于0时说明等待到信号
 */
int sem_wait_i(sem_t *Sem, int iTimeout) {
	//等待信号量变成0，iTimeout为等待时间，若iTimeout<0则无穷等待，否则等待若干iTimeout毫秒。
	int iResult = 100;
	if (iTimeout < 0) {
		while (((iResult = sem_wait(Sem)) != 0) && (errno == EINTR))
			;
		//等待信号量，errno==EINTR屏蔽其他信号事件引起的等待中断
		return iResult;
	} else {
		/**
		 long int iNesc = 0;//需要等待的纳秒数
		 timespec times;

		 clock_gettime(CLOCK_REALTIME, &times); //获取当前时间
		 iNesc = (iTimeout % 1000) * (1000 * 1000);
		 if ((1000 * 1000 * 1000 - times.tv_nsec) > iNesc) {
		 times.tv_sec += (iTimeout / 1000); //+加上等待时间的秒数
		 times.tv_nsec += iNesc;//+加上等待时间纳秒数
		 } else {
		 times.tv_sec = times.tv_sec + (iTimeout / 1000) + 1; //+加上等待时间的秒数
		 times.tv_nsec = iNesc - 1000 * 1000 * 1000 + times.tv_nsec;//+加上等待时间纳秒数
		 }
		 while (((iResult = sem_timedwait(Sem, &times)) != 0)
		 && (errno == EINTR)) {
		 ;
		 }
		 //等待信号量，errno==EINTR屏蔽其他信号事件引起的等待中断;
		 */

		ST_TIMEOUT_JUDGE st_timeout_judge;
		initStTimeoutJudge(&st_timeout_judge, iTimeout, TIMEOUT_MILLI_SECOND);
		while (true) {
			iResult = sem_trywait(Sem);
			if(iResult == 0 || CheckTimeOut(&st_timeout_judge))
				break;
			usleep(10*1000);
		}
		return iResult;
	}
}

int DateConvent(char*DbfDate, char*DbfTime, char*OperDate) {
	bool bDate = false;
	bool bTime = false;
	char temp[9];
	memset(temp, 0, 8);
	char temp2[7];
	memset(temp2, 0, 6);
	char cYear[5];
	memset(cYear, 0, 5);
	char cMonth[3] = { 0 };
	memset(cMonth, 0, 3);
	char cDay[3] = { 0 };
	memset(cDay, 0, 3);
	char cHour[3] = { 0 };
	memset(cHour, 0, 3);
	char cMin[3] = { 0 };
	memset(cMin, 0, 3);
	char cSec[3] = { 0 };
	memset(cSec, 0, 3);
	if (DbfDate != NULL) {
		memcpy(temp, DbfDate, sizeof(temp));
		memcpy(cYear, &temp[0], 4);
		memcpy(cMonth, &temp[0] + 4, 2);
		memcpy(cDay, &temp[0] + 6, 2);
		bDate = true;
	}
	if (DbfTime != NULL) {
		memcpy(temp2, DbfTime, sizeof(temp2));
		memcpy(cHour, &temp2[0], 2);
		memcpy(cMin, &temp2[0] + 2, 2);
		memcpy(cSec, &temp2[0] + 4, 2);
		bTime = true;
	}
	char ctemp[50];
	memset(ctemp, 0, 50);
	if (bDate && !bTime) {
		sprintf(ctemp, "%4s-%2s-%2s", cYear, cMonth, cDay);
	} else if (!bDate && bTime) {
		sprintf(ctemp, "%2s:%2s:%2s", cHour, cMin, cSec);
	} else if (bDate && bTime) {
		sprintf(ctemp, "%4s-%2s-%2s %2s:%2s:%2s", cYear, cMonth, cDay, cHour,
				cMin, cSec);
	}
	bDate = false;
	bTime = false;
	strcpy(OperDate, ctemp);
	return 0;
}

void SwitchTime(unsigned int iTime, char *pszDate, char *pszTime) {
	if ((pszDate == NULL) || (pszTime == NULL)) {
		return;
	}

	struct tm tm_p;
	struct tm Time;
	tm_p = *localtime_r((time_t *) &iTime, &Time);

	sprintf(pszDate, "%04d%02d%02d", tm_p.tm_year + 1900, tm_p.tm_mon + 1,
			tm_p.tm_mday);

	sprintf(pszTime, "%02d%02d%02d", tm_p.tm_hour, tm_p.tm_min, tm_p.tm_sec);
}

void PrintBufContent(char *buf, unsigned int iBufLen) {
	int index = 0;
	int iLen = iBufLen;
	for (index = 0; index < iLen; index++) {
		if (index % 16 == 0)
			printf("\n");

		printf(" %02X \n", (unsigned char) buf[index]);
	}

	printf("\n");
}

int PubStrTimeToTime_t( const char *pcaDate, const char *pcaTime, time_t *ttm )
{
    char   caYear[5] = { '\0' };
    char   caMon[5] = { '\0' };
    char   caDay[5] = { '\0' };
    char   caHour[5] = { '\0' };
    char   caMin[5] = { '\0' };
    char   caSec[5] = { '\0' };
    struct tm ltm;
    if( NULL == pcaDate || NULL == pcaTime || NULL == ttm )
    {
       return -1;
    }
    memcpy( caYear, pcaDate, 4 );
    memcpy( caMon, pcaDate + 4, 2 );
    memcpy( caDay, pcaDate + 4 + 2, 2 );
    memcpy( caHour, pcaTime, 2 );
    memcpy( caMin, pcaTime + 2, 2 );
    memcpy( caSec, pcaTime + 2 + 2, 2 );
    memset( &ltm, 0, sizeof( ltm ) );
    ltm.tm_year = atoi( caYear ) - 2000;
    ltm.tm_mon = atoi( caMon ) - 1;
    ltm.tm_mday = atoi( caDay ) - 1;
    ltm.tm_hour = atoi( caHour );
    ltm.tm_min = atoi( caMin );
    ltm.tm_sec = atoi( caSec );
    if( -1 == ( *ttm = mktime( &ltm ) ) )
    {
         return -1;
    }
    return 0;
}


/* 20130108
 * 由参数指定时间, 转换为 从1970年1月1日开始的秒数
 *
 * GMT	Long类型的数，用于表示格林威治标准时间，数值上等于系统参数设定的起始日期到所要表示时刻所经过的秒数
 *
 * 如：系统默认设定为1970年1月1日，则0秒即标识格林威治的1970年1月1日 00:00:00
 *
 * */
int PubGetOriTime( const char *pcaDate, const char *pcaTime, time_t *ttm )
{
	char	caYear[5] = { '\0' };
	char	caMon[5] = { '\0' };
	char	caDay[5] = { '\0' };
	char	caHour[5] = { '\0' };
	char	caMin[5] = { '\0' };
	char	caSec[5] = { '\0' };

	struct tm ltm;

	if( NULL == pcaDate || NULL == pcaTime || NULL == ttm )
	{
       return -1;
	}

	memcpy( caYear, pcaDate, 4 );
	memcpy( caMon, pcaDate + 4, 2 );
	memcpy( caDay, pcaDate + 4 + 2, 2 );

	memcpy( caHour, pcaTime, 2 );
	memcpy( caMin, pcaTime + 2, 2 );
	memcpy( caSec, pcaTime + 2 + 2, 2 );

	memset( &ltm, 0, sizeof( ltm ) );

	ltm.tm_year = atoi( caYear ) - 1900;
	ltm.tm_mon = atoi( caMon ) - 1;
	ltm.tm_mday = atoi( caDay );
	ltm.tm_hour = atoi( caHour );
	ltm.tm_min = atoi( caMin );
	ltm.tm_sec = atoi( caSec );

	if( -1 == ( *ttm = mktime( &ltm ) ) )
	{
		return -1;
	}

	return 0;

}/* end of func */



/* 20130108
 * 由参数指定时间, 转换为 从2000年1月1日开始的秒数
 *
 * GMT	Long类型的数，用于表示格林威治标准时间，数值上等于系统参数设定的起始日期到所要表示时刻所经过的秒数
 *
 * 如：系统默认设定为2000年1月1日，则0秒即标识格林威治的2000年1月1日 00:00:00
 *
 * */
int PubStrToTime(const char *pcaDate, const char *pcaTime, time_t *ttm )
{
	char	caYear[5] = { '\0' };
	char	caMon[5] = { '\0' };
	char	caDay[5] = { '\0' };
	char	caHour[5] = { '\0' };
	char	caMin[5] = { '\0' };
	char	caSec[5] = { '\0' };

  time_t  tOriTime;   //xuyk add 20130108
	struct tm ltm;

	if( NULL == pcaDate || NULL == pcaTime || NULL == ttm )
	{
		return -1;
	}

	memcpy( caYear, pcaDate, 4 );
	memcpy( caMon, pcaDate + 4, 2 );
	memcpy( caDay, pcaDate + 4 + 2, 2 );

	memcpy( caHour, pcaTime, 2 );
	memcpy( caMin, pcaTime + 2, 2 );
	memcpy( caSec, pcaTime + 2 + 2, 2 );

	memset( &ltm, 0, sizeof( ltm ) );

	ltm.tm_year = atoi( caYear ) - 1900;
	ltm.tm_mon = atoi( caMon ) - 1;
	ltm.tm_mday = atoi( caDay );
	ltm.tm_hour = atoi( caHour );
	ltm.tm_min = atoi( caMin );
	ltm.tm_sec = atoi( caSec );

	if( -1 == ( *ttm = mktime( &ltm ) ) )
	{
		return -1;
	}

   //xuyk add 20130108 sta
   PubGetOriTime("20000101", "000000", &tOriTime);
   *ttm -= tOriTime;
   //xuyk add 20130108 end

	return 0;
}/* end of func */


/* 将从2000年1月1日0点 开始算起的秒数，转换为 时间字符串
 *
 * 如： 414674373 转换为： pszDate = 20130220 ， pszTime = 111933
 *
 *  tTimeFrom2000  2000年1月1日0点 算起的秒数
 *
 *  */
int DateTimeConvert_Convert_TimeTFrom2000_To_DateTimeString(time_t tTimeFrom2000, char *pszDate, char *pszTime)
{

  //2000年1月1日0点， 从1970年算起的描述
  time_t tTime2000From1970;
  PubGetOriTime("20000101", "0000", &tTime2000From1970); //从1970年开始 到 2000年的 秒数

  time_t tTimeFrom1970 = tTimeFrom2000 + tTime2000From1970;

  struct tm *tmTime;
  struct tm Time;
  tmTime = localtime_r(&tTimeFrom1970, &Time);

  sprintf(pszDate, "%04d%02d%02d", tmTime->tm_year + 1900, tmTime->tm_mon + 1, tmTime->tm_mday);
  sprintf(pszTime, "%02d%02d%02d", tmTime->tm_hour, tmTime->tm_min, tmTime->tm_sec);

  return 0;
}



/* 将从2000年1月1日0点 开始算起的秒数，转换为 struct tm 类型的对象
 *  如： 414674373 转换为： pszDate = 20130220 ， pszTime = 111933
 *  tTimeFrom2000  2000年1月1日0点 算起的秒数    *
 *  */
int DateTimeConvert_Convert_TimeTFrom2000_To_TM(time_t tTimeFrom2000, struct tm *tmDateTime)
{

  //2000年1月1日0点， 从1970年算起的描述
  time_t tTime2000From1970;
  PubGetOriTime("20000101", "0000", &tTime2000From1970); //从1970年开始 到 2000年的 秒数

  time_t tTimeFrom1970 = tTimeFrom2000 + tTime2000From1970;

  struct tm Time;
  tmDateTime = localtime_r(&tTimeFrom1970, &Time);

  return 0;
}

/* 将2000年01月01日 开始的天数, 转换为 日期字符串
 * 如： 当iDateInterval = 1， 表示 2000年01月01日
 * 转换后， pDate 的格式为： 20130320
 * */
int DateTimeConvert_Convert_Date2From2000_To_DateString(int iDateInterval, char *pDate)
{
	/* variables */
	time_t	tTm;
	struct	tm	stTime;
	struct	tm	*pstTime;

	/* initialize */
	memset( &stTime, 0, sizeof( stTime ) );

	stTime.tm_year = 2000 - 1900;
	stTime.tm_mon = 1 - 1;
	stTime.tm_mday = 1;
	stTime.tm_hour = 1;
	stTime.tm_min = 1;
	stTime.tm_sec = 1;

	if( -1 == ( tTm = mktime( &stTime ) ) )
	{
		return -1;
	}

	/* get time */
	tTm += iDateInterval * 24 * 60 * 60;
	pstTime = localtime(&tTm);

	sprintf((char *)pDate, "%4d%02d%02d", 1900 + pstTime->tm_year, 1 + pstTime->tm_mon, pstTime->tm_mday);

	return 0;
}

/* 将2000年01月01日 开始的天数, 转换为 tm *tmDateTime 类型的结构
 * 如： 当iDateInterval = 1， 表示 2000年01月01日
 * */
int DateTimeConvert_Convert_Date2From2000_To_TM(int iDateInterval, struct tm *tmDateTime)
{
	/* variables */
	time_t	tTm;
	struct	tm	stTime;

	/* initialize */
	memset(&stTime, 0, sizeof(stTime));

	stTime.tm_year = 2000 - 1900;
	stTime.tm_mon = 1 - 1;
	stTime.tm_mday = 1;
	stTime.tm_hour = 1;
	stTime.tm_min = 1;
	stTime.tm_sec = 1;

	if(-1 == (tTm = mktime( &stTime )))
	{
		return -1;
	}

	/* get time */
	tTm += iDateInterval * 24 * 60 * 60;
	tmDateTime = localtime(&tTm);

	return 0;
}




/* 将字符串格式的日期，转换为2000年01月01日 开始的天数,
 * 如： 当 2000年01月01日 ， 换后的的值为： iDateInterval = 1
 *   pDate 格式为：20130320 */
int DateTimeConvert_Convert_DateString_To_Date2From2000(char *pDate, int *piDateInterval)
{
	/* variables */
	char	caYear[5] = { '\0' };
	char	caMon[5] = { '\0' };
	char	caDay[5] = { '\0' };

	time_t	tTmFr;
	time_t	tTmTo;
	struct	tm	stTime;

	/* initialize */
	memset( &stTime, 0, sizeof( stTime ) );

	/* date From */
	stTime.tm_year = 2000 - 1900;
	stTime.tm_mon = 1 - 1;
	stTime.tm_mday = 1;
	stTime.tm_hour = 1;
	stTime.tm_min = 1;
	stTime.tm_sec = 1;

	if( -1 == ( tTmFr = mktime( &stTime ) ) )
	{
		return -1;
	}

	/* date To */
	memcpy( caYear, pDate, 4 );
	memcpy( caMon, pDate + 4, 2 );
	memcpy( caDay, pDate + 4 + 2, 2 );

	stTime.tm_year = atoi( caYear ) - 1900;
	stTime.tm_mon = atoi( caMon ) - 1;
	stTime.tm_mday = atoi( caDay );
	stTime.tm_hour = 1;
	stTime.tm_min = 1;
	stTime.tm_sec = 1;

	if( -1 == ( tTmTo = mktime( &stTime ) ) )
	{
		return -1;
	}

	/* get time */
	(*piDateInterval) = (tTmTo - tTmFr) / (24 * 60 * 60);

	return 0;
}



/* 例如： 20130101 转换为： 0x20130101 Motol序列 */
int HexStringToMotolUintValue(char *pszHexString, unsigned int *uiValue)
{
	if(pszHexString == NULL)
	{
		*uiValue = 0;
		return -1;
	}

	*uiValue = strtoll(pszHexString, NULL, 16);
	//*uiValue = htonl(*uiValue);

	printf("uiValue = %u", *uiValue);

	return 0;
}

/* 例如： 20130101 转换为： 0x20130101  Motol序列  */
int HexStringToMotolIntValue(char *pszHexString, int *uiValue)
{
	if(pszHexString == NULL)
	{
		*uiValue = 0;
		return -1;
	}

	*uiValue = strtoll(pszHexString, NULL, 16);
	//*uiValue = htonl(*uiValue);
    printf("iValue = %d", *uiValue);

	return 0;
}

/* 例如： 20130101 转换为： 0x20130101  Motol序列   */
int HexStringToMotolIntBuffer(char *pszHexString, char *pszUintBuf)
{
	unsigned int iValue;

	if(pszHexString == NULL)
	{
		iValue = 0;
		return -1;
	}

	if(pszUintBuf == NULL)
	{
		iValue = 0;
		return -1;
	}

	iValue = strtoll(pszHexString, NULL, 16);
	iValue = htonl(iValue);
	memcpy(pszUintBuf, &iValue, 4);

	//printf("iValue = %s", pszUintBuf);

	return 0;
}

/* 例如： 20130101 转换为： 0x20130101 Intel序列 */
int HexStringToIntelUintValue(char *pszHexString, unsigned int *uiValue)
{
	if(pszHexString == NULL)
	{
		*uiValue = 0;
		return -1;
	}

	*uiValue = strtoll(pszHexString, NULL, 16);
	*uiValue = htonl(*uiValue);

	printf("uiValue = %u", *uiValue);

	return 0;
}

/* 例如： 20130101 转换为： 0x20130101  Intel序列  */
int HexStringToIntelIntValue(char *pszHexString, int *uiValue)
{
	if(pszHexString == NULL)
	{
		*uiValue = 0;
		return -1;
	}

	*uiValue = strtoll(pszHexString, NULL, 16);
	*uiValue = htonl(*uiValue);
    printf("iValue = %d", *uiValue);

	return 0;
}

/* 例如： 20130101 转换为： 0x20130101  Intel序列   */
int HexStringToIntelIntBuffer(char *pszHexString, char *pszUintBuf)
{
	unsigned int iValue;

	if(pszHexString == NULL)
	{
		iValue = 0;
		return -1;
	}

	if(pszUintBuf == NULL)
	{
		iValue = 0;
		return -1;
	}

	iValue = strtoll(pszHexString, NULL, 16);
	memcpy(pszUintBuf, &iValue, 4);

	//printf("iValue = %s", pszUintBuf);

	return 0;
}

/*将元转换成分，indata:单位为元的字符串数组;返回值为分的整数*/
//int YuanToFen(const char * indata)
//{
//	string a(indata);
//	int index = a.find_first_of('.');
//	string tmp(indata);
//	int tmplen = tmp.erase(0,index+1).length();
//	if(tmplen>2)
//		tmp.erase(2,tmplen-2);
//	a.erase(index,tmplen).replace(index,2,tmp.c_str());
//	return atoi(a.c_str());
//}

/*将元转换成分，indata:单位为元的字符串数组;返回值为分的整数*/
int YuanToFen(const char * indata)
{
	float fData = atof(indata);

	int fd = 10*10;

	if(fData>0)
	{
		return int(fData*fd+0.5);
	}
	else
	{
		return int(fData*fd-0.5);
	}
}


/*! \fn char CreateDirectory( const char *szDirectoryPath , int iDirPermission)
 * \brief 		以指定的权限创建目录，
 * \param[in] 	szDirectoryPath	需要创建的文件目录路径
 * \param[in] 	iDirPermission	创建目录时，为所创建的目录所指定的权限
 * \return 		bool 返回结果，成功返回True 失败返回false
 * \author 		张保兵
 * \date 		2013-06-26
 */
bool CreateDirectory( const char *szDirectoryPath , int iDirPermission )
{
	/*
	以指定的权限创建目录.
	对于指定要创建的目录，如果其父目录不存在(递归至要生成的目标上报的根目录)，那么会创建其对应的父目录
	例如，指定要创建的目录: "/foo/bar"，如果/foo/目录不存在，那么在创建 bar 目录之前会创建 /foo 目录
	对于要生成的目标目录，"./foo/bar" 等价于 "foo/bar"
	*/

	if ( NULL == szDirectoryPath )
	{
		#ifdef DEBUG
		fprintf( stderr , "[%s][%d][%s][parameter < szDirectoryPath > for < CreateDirectory > should not be NULL]\n" , __FILE__ , __LINE__ , __FUNCTION__ );
		#endif
		return false;
	}

	const int iPathLength = static_cast< int >( strlen( szDirectoryPath ) );
	if ( iPathLength > 256 )
	{
		#ifdef DEBUG
		fprintf( stderr , "[%s][%d][%s][the path length(%d) exceeds system max path length(%d)]\n" , \
		__FILE__ , __LINE__ , __FUNCTION__ , iPathLength , PATH_MAX );
		#endif
		return false;
	}
	char szPathBuffer[ /*PATH_MAX*/256 ] = { 0 };
	memcpy( szPathBuffer , szDirectoryPath , iPathLength );
	for ( int i = 0 ; i < iPathLength ; ++i )
	{
		char &refChar = szPathBuffer[ i ];
		//目录分隔符
		if ( ( '/' == refChar ) && ( 0 != i ) )
		{
			refChar = '\0';
			//判断当前目录是否存在
			int iStatus = access( szPathBuffer , F_OK );
			if ( 0 != iStatus )
			{
				if ( ( ENOTDIR == errno ) || ( ENOENT == errno ) )
				{
					//以指定权限创建目录
					iStatus = mkdir( szPathBuffer , iDirPermission );
					if ( 0 != iStatus )
					{
					#ifdef DEBUG
					fprintf( stderr , "[%s][%d][%s][< mkdir > fail , ErrCode:%d , ErrMsg:%s]\n" , \
					__FILE__ , __LINE__ , __FUNCTION__ , errno , strerror( errno ) );
					#endif
					return false;
					}
				}
				else
				{
					#ifdef DEBUG
					fprintf( stderr , "[%s][%d][%s][< access > fail , RetCode: %d , ErrCode:%d , ErrMsg:%s]\n" , \
						__FILE__ , __LINE__ , __FUNCTION__ , iStatus , errno , strerror( errno ) );
					#endif
					return false;
				}
			}
			refChar = '/';
		}
	}
	return true;
}


/*! \fn char ModifyIPString( const char *szDirectoryPath , int iDirPermission)
 * \brief 		修正IP字符串
 * \param[in]
 * \param[in]
 * \return 		bool 返回结果，成功返回True 失败返回false
 * \author 		张保兵
 * \date 		2013-07-20
 */
bool ModifyIPString(char *pszInBuff, char *pszOutBuff)
{
	if(pszInBuff == NULL)
	{
		return false;
	}

	//10. 15. 121. 152
	char * pDelim = (char*)".";
	char szTemp[300] = {0};
	char * p = NULL;
	int index = 0;
	p = strtok(pszInBuff, pDelim);
	sprintf(szTemp, "%d.",atoi(p));
	strcat(pszOutBuff, szTemp);
	index++;

	while((p = strtok(NULL, pDelim)))
	{
		if(index != 3)
		{
			sprintf(szTemp, "%d.",atoi(p));
			strcat(pszOutBuff, szTemp);
		}
		else
		{
			sprintf(szTemp, "%d",atoi(p));
			strcat(pszOutBuff, szTemp);
		}
		index++;
	}


	pDelim = NULL;

	return true;
}
