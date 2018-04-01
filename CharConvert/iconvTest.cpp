/*
 * iconvTest.cpp
 *
 *  Created on: 2017-10-28
 *      Author: root
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iconv.h>

//bool convertAnsiToUtf8()
//{
//
//}

char* convertToCString(char *pszStr, size_t szStrLength)
{

	if(pszStr == NULL) return pszStr;

	char *pszTemp = pszStr+szStrLength-1;
	while(pszTemp != pszStr-1)
	{
		if(*pszTemp != 0x20)
		{
			*(pszTemp+1) = 0;
			break;
		}
		--pszTemp;
	}

	if(pszTemp == pszStr-1) //入参全为空格
		*(pszStr+1) = 0;

	return pszStr;
}

/*
 * 编码转换
 * pszOldEncoding：待转换的编码类型 可通过iconv --list查找
 * pszNewEncoding：要转换成的编码类型 +[//TRANSLIT]：遇到无法转换的字符就找相近字符替换；IGNORE ：遇到无法转换字符跳过. e.g."UNICODE//IGNORE"
 *
 * CodeConvert("GB18030" ,"UTF8",   szSrc, uSrcLen,  szRus, &uRusLen)
 *
 *!!!!!!pszSrcData和pszDestData都必须是有存储空间的不能定义为常量!!!!!!
 *!!!!!!pszSrcData和pszDestData都必须是有存储空间的不能定义为常量!!!!!!
 *
 * pszSrcData
 * iSrcLength：要转换的最长字节数
 *
 * pszDestData
 * *piDestLength：入参<pszDestData的长度>,出参<pszDestData剩余的字节数>
 */
bool CodeConvert(const char *pszOldEncoding,const char *pszNewEncoding,
		 char *pszSrcData,size_t iSrcLength,char *pszDestData,size_t *piDestLength)
{
	if(NULL==pszSrcData || NULL==pszDestData)
	{
		*piDestLength = 0;
		puts("pszSrcData or pszDestData is NULL!");
		return false;
	}

	iconv_t pcd;
//	char *pszNewEncoding = "GB18030//IGNORE";
//	char *pszOldEncoding = "UTF-8";
	pcd = iconv_open(pszNewEncoding,pszOldEncoding);
	if ( (iconv_t)-1 == pcd )
	{
//		m_cLog.LogError("[%s][%s][%d]  iconv_open failure", __FILE__ , __FUNCTION__, __LINE__);
		puts("iconv_open failure");
		*piDestLength = 0;
		return false;
	}

	memset(pszDestData, 0, sizeof(pszDestData));

//	printf("Before: pszSrcData<%p>, pszDestData<%p>, &iSrcLength<%p>, piDestLength<%p>\n",
//			pszSrcData, pszDestData, &iSrcLength,piDestLength);
//	printf("Before: iSrcLength[%u], piDestLength[%u]\n", iSrcLength, *piDestLength);

	int iResult = iconv(pcd,&pszSrcData,&iSrcLength,&pszDestData,piDestLength);//iconv 调用前后 pszSrcData、pszDestData指针所指向的地址会变

//	printf("After: pszSrcData<%p>, pszDestData<%p>, &iSrcLength<%p>, piDestLength<%p>\n",
//				pszSrcData, pszDestData, &iSrcLength,piDestLength);
//	printf("After: iSrcLength[%u], piDestLength[%u]\n", iSrcLength, *piDestLength);

	if(iResult == -1)
	{
//		m_cLog.LogError("[%s][%s][%d]  iconv failure", __FILE__ , __FUNCTION__, __LINE__);
		puts("iconv failure");
		return false;
	}

	iconv_close(pcd);
	return true;
}

//当文本编码已经为tuf-8时,使用GB18030->utf8的结果
void functionTest()
{
	puts("\n\n functionTest Begin!");

	char szIn[50] = {0};
	snprintf(szIn, sizeof(szIn), "单程票");
	char szRus[50] = {0};
	unsigned int uiRusLen = sizeof(szRus);
	printf("单程票<%s> strlen(单程票):%u sizeof(单程票):%u\n","单程票", strlen("单程票"), sizeof("单程票"));
//	if(!CodeConvert("UTF-8", "GB18030" , szIn, strlen(szIn),  szRus, &uiRusLen))
	if(!CodeConvert("GB18030" , "UTF-8", szIn, strlen(szIn),  szRus, &uiRusLen))
	{
		puts("CodeConvert Error!");
	}
	printf("rus<%s> strlen(rus)%u\n", szRus, strlen(szRus));
	puts("functionTest end!\n");
}

int main()
{
	//IGNORE
//	char szSrc[]= {0xC6, 0xD5, 0xCD, 0xA8, 0xB5, 0xA5, 0xB3, 0xCC, 0xC6, 0xB1, 0x00, 0x20};
	char szSrc[33]= {0xC6, 0xD5, 0xCD, 0xA8, 0xB5, 0xA5, 0xB3, 0xCC, 0xC6, 0xB1, 0x20,
			0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
			0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20};
	size_t uSrcLen = sizeof(szSrc);

	char szRus[88] = {0};
	size_t uRusLen = sizeof(szRus);

	if(!CodeConvert("GB18030" ,"UTF8",   szSrc, uSrcLen,  szRus, &uRusLen))
	{
//		m_cLog.LogError("[%s][%s][%d] CodeConvert(): UTF-8 to GB18030 failure", __FILE__ , __FUNCTION__, __LINE__);
		puts("CodeConvert Error!");
	}
	printf("RusStr[%s]", szRus);
//	printf("RusStr[%s]", convertToCString(szRus,sizeof(szRus)-uRusLen));

	for(unsigned int i=0; i< sizeof(szRus)-uRusLen; ++i)
		printf("%02X ", *((unsigned char*)szRus + i) );
	putchar('\n');

	functionTest();

	return 0;
}
