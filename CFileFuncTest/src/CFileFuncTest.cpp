//============================================================================
// Name        : CFileFuncTest.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
using namespace std;

void fseekTest();

int main() {
	cout << "Test Begin!" << endl; // prints
	fseekTest();
	cout << "Test End!" << endl; // prints
	return 0;
}


void fseekTest()
{
	FILE* fpBinTest = fopen("/mnt/hgfs/Share/test.bin","wb+");
	if(NULL == fpBinTest)
	{
		puts("fopen fail!");
		return;
	}



	unsigned char ucFileType[2] = {0x00, 0x01};
	unsigned char ucFileCnt[2] = {0x00, 0x00};
	printf("ftell before fwrite[%lu]\n", ftell(fpBinTest));
//	写文件类型
	fwrite(ucFileType, 1, sizeof(ucFileType), fpBinTest);
	printf("ftell after fwrite1[%lu]\n", ftell(fpBinTest));

//	写文件数量
	fwrite(ucFileCnt, 1, sizeof(ucFileCnt), fpBinTest);
	printf("ftell after fwrite2[%lu]\n", ftell(fpBinTest));

//	fseek 读文件数量信息
	if(fseek(fpBinTest, 2, SEEK_SET))
		puts("fseek error!");

	unsigned char ucReadBuff[3] = {0};
	fread(ucReadBuff, 1, 2, fpBinTest);
	printf("Read Content[%#X %#X]\n", ucReadBuff[0], ucReadBuff[1]);

//	fseek 写交易数据
	unsigned char ucContent[100];
	if(fseek(fpBinTest, 0, SEEK_END))
		puts("fseek error!");
	printf("ftell after SEEK_END[%lu]\n", ftell(fpBinTest));

	for(int i=0; i<100; ++i)
		ucContent[i] = i+ 0x30;
	if(1 != fwrite(ucContent, sizeof(ucContent), 1, fpBinTest))
		printf("[%d]fwrite error!",__LINE__);
	printf("ftell after fwrite3[%lu]\n", ftell(fpBinTest));

//写文件数量
	if(fseek(fpBinTest, 2, SEEK_SET))
		puts("fseek error!");

	ucFileCnt[0] = 0x10; ucFileCnt[1] = 0x11;
	if(1 != fwrite(ucFileCnt, sizeof(ucFileCnt), 1, fpBinTest))
		printf("[%d]fwrite error!",__LINE__);

	printf("ftell after fwrite4[%lu]\n", ftell(fpBinTest));



//	fflush(fpBinTest);
	fclose(fpBinTest);

}
