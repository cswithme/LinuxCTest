//============================================================================
// Name        : CPubXmlTest.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "PubXml.h"
using namespace std;

bool PubXmlTest()
{
	CPubXml pubXml;
	bool bRet =pubXml.LoadXmlFile("/Afc/Config/LedLiYaDeUpdate.xml", "utf8");
	if(false == bRet)
	{
		puts("加载配置文件失败");
		return bRet;
	}

	if(bRet)
	{
		bRet =pubXml.GetNodeSetByPath("/led/ledNeedUpdate");
		printf("[%s][%d]加载/led/ledNeedUpdate节点结果：[ %d ]\n", __FILE__, __LINE__, bRet);
	}

	if(bRet)
	{
		char szValueTemp[40] = {0};
		bRet =pubXml.GetValue(szValueTemp);
		printf("[%s][%d]文本节点内容：[ %s ]\n", __FILE__, __LINE__, szValueTemp);
	}

	if(bRet)
	{
		pubXml.SetValue("666");
	}

	if(bRet)
	{
		char szValueTemp[40] = {0};
		bRet =pubXml.GetValue(szValueTemp);
		printf("[%s][%d]文本节点内容：[ %s ]\n", __FILE__, __LINE__, szValueTemp);
	}
	pubXml.SaveXmlFile();

	pubXml.FreeXmlPathContext();
	return bRet;


}


int main()
{
	cout << "Test CPubXmlTest!" << endl; // prints
	PubXmlTest();
	puts("Test end!");
	//LedShowParam.xml
	return 0;
}
