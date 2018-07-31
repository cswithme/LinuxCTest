/*
 * MutilThreadTest.cpp
 *
 *  测试libxml2库在其他线程正在读取xml库的时候调用xmlCleanupParser 会不会造成程序dump
 *  https://stackoverflow.com/questions/18307146/xml-memory-leak-with-valgrind-in-xmlsaveformatfileenc-using-libxml2
 *  Created on: 2018-6-14
 *      Author: root
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <pthread.h>

#include "PubXml.h"

static pthread_barrier_t threadBarrier;
//
bool ReadXmlFileImmediately(const char* szFileName)
{

	CPubXml cPubXml;
	xmlXPathObjectPtr pstXPath = NULL;
	if (!cPubXml.LoadXmlFile("/Afc/Config/HttpPost.xml", "UTF-8"))
	{
		printf("[%s][%s][%d] /Afc/Config/HttpPost.xml fail\n", __FILE__ , __FUNCTION__, __LINE__);
		cPubXml.FreeXmlPathContext();
		return false;
	}

	pstXPath = cPubXml.GetNodeSet("/HttpPostConfig/ServerURL");
	if(NULL == pstXPath)
	{
		printf("[%s][%s][%d] /HttpPostConfig/ServerURL config error\n", __FILE__ , __FUNCTION__, __LINE__);
		cPubXml.FreeXmlPathContext();
		return false;
	}
	char szTemp[1024] = {0};
	cPubXml.GetAttribute(pstXPath->nodesetval->nodeTab[0], "IpAddr", szTemp);
	printf("[%s][%s][%d] IpAddr = %s\n", __FILE__ , __FUNCTION__, __LINE__, szTemp);

	memset(szTemp,0,sizeof(szTemp));
	cPubXml.GetAttribute(pstXPath->nodesetval->nodeTab[0], "Port", szTemp);
	printf("[%s][%s][%d] Port = %s\n", __FILE__ , __FUNCTION__, __LINE__, szTemp);

	memset(szTemp,0,sizeof(szTemp));
	cPubXml.GetAttribute(pstXPath->nodesetval->nodeTab[0], "Porject", szTemp);
	printf("[%s][%s][%d] Porject = %s\n", __FILE__ , __FUNCTION__, __LINE__, szTemp);

	pstXPath = cPubXml.GetNodeSet("/HttpPostConfig/OtherCfg");
	if(NULL == pstXPath)
	{
		printf("[%s][%s][%d] /HttpPostConfig/OtherCfg config error\n", __FILE__ , __FUNCTION__, __LINE__);
		cPubXml.FreeXmlPathContext();
		return false;
	}
	memset(szTemp,0,sizeof(szTemp));
	cPubXml.GetAttribute(pstXPath->nodesetval->nodeTab[0], "IsSSL", szTemp);
	printf("[%s][%s][%d] IsSSL = %s\n", __FILE__ , __FUNCTION__, __LINE__, szTemp);

	memset(&szTemp,0,sizeof(szTemp));
	cPubXml.GetAttribute(pstXPath->nodesetval->nodeTab[0], "ConnectTimeOut", szTemp);
	printf("[%s][%s][%d] ConnectTimeOut = %s\n", __FILE__ , __FUNCTION__, __LINE__, szTemp);

	memset(&szTemp,0,sizeof(szTemp));
	cPubXml.GetAttribute(pstXPath->nodesetval->nodeTab[0], "TimeOut", szTemp);
	printf("[%s][%s][%d] TimeOut = %s\n", __FILE__ , __FUNCTION__, __LINE__, szTemp);

	memset(&szTemp,0,sizeof(szTemp));
	cPubXml.GetAttribute(pstXPath->nodesetval->nodeTab[0], "TryTimes", szTemp);
	printf("[%s][%s][%d] TryTimes = %s\n", __FILE__ , __FUNCTION__, __LINE__, szTemp);


	cPubXml.FreeXmlPathContext();
	return true;
}

void *threadFunc(void *parm)
{
	pthread_barrier_wait(&threadBarrier);

	CPubXml pubXml;
	bool bRet =pubXml.LoadXmlFile("/Afc/Config/LedLiYaDeUpdate.xml", "utf8");
	if(false == bRet)
	{
		puts("加载配置文件失败");
		return NULL;
	}

	int i=5;
	while(i--)
	{
		printf("i=%d\n", i);
		if(bRet)
		{
			bRet =pubXml.GetNodeSetByPath("/led/ledNeedUpdate");
			printf("[%s][%d]加载/led/ledNeedUpdate节点结果：[ %d ]\n", __FILE__, __LINE__, bRet);
		}

		if(bRet)
		{
			char szValueTemp[40] = {0};
			bRet =pubXml.GetValue(szValueTemp);
			printf("[%s][%d]文本节点内容：[ %s ] , bRet[%d]\n", __FILE__, __LINE__, szValueTemp, bRet);
		}
		usleep(950 * 1000);
	}
	pubXml.FreeXmlPathContext();

	return NULL;
}


void MutileThreadTest()
{
	pthread_t pidReadXml;
	if(0 != pthread_create(&pidReadXml, NULL, threadFunc, NULL))
	{
		puts("thread Create Error!");
	}


	pthread_barrier_init(&threadBarrier, NULL, 2);
	pthread_barrier_wait(&threadBarrier);

	puts("------------------Begin to ReadXmlFileImmediately------------------");
	ReadXmlFileImmediately(NULL);
	puts("-------------------ReadXmlFileImmediately Finish!-------------------");

	pthread_barrier_destroy(&threadBarrier);
	pthread_join(pidReadXml, NULL);
	puts("pthread_join Sucess!");
}
