/*
 * BMP文件格式
 * 点阵是按BGR方式存放的,默认存放顺序是从下向上,从左向右
 * 对于图片的每一行数据长度必须是4的倍数,不足以0补齐
 * 猜测:整个文件的长度应该也是4或8的倍数
 */

#include "ReadBmp.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int ReadBmp(const char *pszFileName)
{
	puts("Read BMP Begin!");
	FILE *fp;

	BMPFILEHEADER stFileHeader;
	BMPINF stInfoHeader;

	if((fp = fopen(pszFileName, "rb")) == NULL)
	{
		printf("%s---%d:文件:%s 读取失败", __FILE__, __LINE__, pszFileName);
		return -1;
	}

	//获取文件头
	fseek(fp, 0, 0);
	fread(&stFileHeader, sizeof(stFileHeader), 1, fp);
	printf("%s---%d:文件头fileHeader size    =[%d]\n", __FILE__, __LINE__, sizeof (stFileHeader)		);
	printf("%s---%d:文件头fileHeader.bType      =[%2x]\n", __FILE__, __LINE__, stFileHeader.bType     );
	printf("%s---%d:文件头fileHeader.bSize      =[%4x][%d]\n", __FILE__, __LINE__, stFileHeader.bSize, stFileHeader.bSize     );
	printf("%s---%d:文件头fileHeader.bReserved1 =[%2x]\n", __FILE__, __LINE__, stFileHeader.bReserved1);
	printf("%s---%d:文件头fileHeader.bReserved2 =[%2x]\n", __FILE__, __LINE__, stFileHeader.bReserved2);
	printf("%s---%d:文件头fileHeader.bOffset    =[%4x]\n", __FILE__, __LINE__, stFileHeader.bOffset   );

	fread(&stInfoHeader, sizeof(stInfoHeader), 1, fp);
	printf("%s---%d:文件头infoHeader size    =[%d]\n", __FILE__, __LINE__, sizeof (stInfoHeader)		);
	printf("%s---%dinfo:infoHeader.bInfoSize     = [%4x]\n", __FILE__, __LINE__,   stInfoHeader.bInfoSize     );
	printf("%s---%dinfo:infoHeader.bWidth        = [%4x]\n", __FILE__, __LINE__,   stInfoHeader.bWidth        );
	printf("%s---%dinfo:infoHeader.bHeight       = [%4x]\n", __FILE__, __LINE__,   stInfoHeader.bHeight       );
	printf("%s---%dinfo:infoHeader.bPlanes       = [%2x]\n", __FILE__, __LINE__,   stInfoHeader.bPlanes       );
	printf("%s---%dinfo:infoHeader.bBitCount     = [%2x]\n", __FILE__, __LINE__,   stInfoHeader.bBitCount     );
	printf("%s---%dinfo:infoHeader.bCompression  = [%4x]\n", __FILE__, __LINE__,   stInfoHeader.bCompression  );
	printf("%s---%dinfo:infoHeader.bmpImageSize  = [%4x]\n", __FILE__, __LINE__,   stInfoHeader.bmpImageSize  );
	printf("%s---%dinfo:infoHeader.bXPelsPerMeter= [%4x]\n", __FILE__, __LINE__,   stInfoHeader.bXPelsPerMeter);
	printf("%s---%dinfo:infoHeader.bYPelsPerMeter= [%4x]\n", __FILE__, __LINE__,   stInfoHeader.bYPelsPerMeter);
	printf("%s---%dinfo:infoHeader.bClrUsed      = [%4x]\n", __FILE__, __LINE__,   stInfoHeader.bClrUsed      );
	printf("%s---%dinfo:infoHeader.bClrImportant = [%4x]\n", __FILE__, __LINE__,   stInfoHeader.bClrImportant );


	//获取点阵数据
	unsigned int uiBytePerLineCnt = (stInfoHeader.bWidth*3+3)/4*4; //考虑补齐,每行应读取的字节数
	printf("[%s][%d] uiBytePerLineCnt=%u\n", __FILE__, __LINE__, uiBytePerLineCnt);

	//高度处理,如果是负数,表明存放顺序是从上向下,从左向右
	unsigned int uiHightConvert = (int)stInfoHeader.bHeight>=0?stInfoHeader.bHeight:(~(stInfoHeader.bHeight-1));
	printf("[%s][%d] uiHightConvert=%u(%#x)\n", __FILE__, __LINE__, uiHightConvert, uiHightConvert);

	int iRet = fseek(fp, stFileHeader.bOffset, SEEK_SET);
	if(0 != iRet)
	{
		printf("[%s][%d] fseek error!\n", __FILE__, __LINE__);
		return -1;
	}

	int fd=open("ConvertRus.txt", O_WRONLY|O_CREAT);
	if(-1 == fd)
	{
		printf("[%s][%d]Open File Error!\n", __FILE__, __LINE__);
		return -1;
	}


	unsigned char ucLineBuff[2048];
	for(unsigned int uiRow=0; uiRow<uiHightConvert; ++uiRow)
	{
		memset(ucLineBuff, 0, sizeof(ucLineBuff));
		size_t uiReadCnt = fread(ucLineBuff, uiBytePerLineCnt, 1, fp);
		if(1 != uiReadCnt)
		{
			printf("[%s][%d]uiReadCnt error! uiRow[%u], uiReadCnt[%u]\n", __FILE__, __LINE__, uiRow, uiReadCnt);
			return -1;
		}
		write(fd, ucLineBuff, stInfoHeader.bWidth*3);
	}

	close(fd);
	fclose(fp);

	puts("Read BMP END!");
	return 0;
}

