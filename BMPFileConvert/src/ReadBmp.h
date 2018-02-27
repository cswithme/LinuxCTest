/*
 * ReadBmp.h
 *
 *  Created on: 2018-2-26
 *      Author: root
 */

#ifndef READBMP_H_
#define READBMP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int ReadBmp(const char *pszFileName);

#pragma pack(push,1)

/*位图文件头*/
typedef struct BMP_FILE_HEADER
{
    unsigned short bType;             /*  文件标识符          */
    unsigned int bSize;            /*  文件的大小          */
    unsigned short bReserved1;        /*  保留值,必须设置为0  */
    unsigned short bReserved2;        /*  保留值,必须设置为0  */
    unsigned int bOffset;          /*  文件头的最后到图像数据位开始的偏移量    偏移量0x0A*/
} BMPFILEHEADER;

/*位图信息头*/
typedef struct BMP_INFO
{
    unsigned int bInfoSize;       /*  信息头的大小             */
    unsigned int bWidth;          /*  图像的宽度               */
    unsigned int bHeight;         /*  图像的高度               */
    unsigned short bPlanes;          /*  图像的位面数             */
    unsigned short bBitCount;        /*  每个像素的位数           */
    unsigned int bCompression;    /*  压缩类型                 */
    unsigned int bmpImageSize;    /*  图像的大小,以字节为单位  */
    unsigned int bXPelsPerMeter;  /*  水平分辨率               */
    unsigned int bYPelsPerMeter;  /*  垂直分辨率               */
    unsigned int bClrUsed;        /*  使用的色彩数             */
    unsigned int bClrImportant;   /*  重要的颜色数             */
} BMPINF;

typedef struct BMP_COLOR
{
	unsigned char ucBlue;
	unsigned char ucGreen;
	unsigned char ucRead;
} BMPCOLOR;

#pragma pack(pop)


#endif /* READBMP_H_ */
