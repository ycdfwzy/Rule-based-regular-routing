#ifndef VISUAL_H_
#define VISUAL_H_

#include "graph.h"
#include <pshpack2.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

typedef long BOOL;
typedef long LONG;
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef unsigned short WORD;

//位图文件头文件定义
//其中不包括文件类型信息（由于结构体的内存结构决定，要是加了的话将不能正确的读取文件信息）
typedef struct {
	WORD    bfType;//文件类型，必须是0x424D,即字符“BM”
	DWORD   bfSize;//文件大小
	WORD    bfReserved1;//保留字
	WORD    bfReserved2;//保留字
	DWORD   bfOffBits;//从文件头到实际位图数据的偏移字节数
} BMPFILEHEADER_T;

struct BMPFILEHEADER_S{
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
};
typedef struct{
	DWORD      biSize;//信息头大小
	LONG       biWidth;//图像宽度
	LONG       biHeight;//图像高度
	WORD       biPlanes;//位平面数，必须为1
	WORD       biBitCount;//每像素位数
	DWORD      biCompression;//压缩类型
	DWORD      biSizeImage;//压缩图像大小字节数
	LONG       biXPelsPerMeter;//水平分辨率
	LONG       biYPelsPerMeter;//垂直分辨率
	DWORD      biClrUsed;//位图实际用到的色彩数
	DWORD      biClrImportant;//本位图中重要的色彩数
} BMPINFOHEADER_T;//位图信息头定义

class Visual{
	public:
		Visual(){}
		~Visual(){}
		void Paint(Graph& G);
		void generateBmp(BYTE*, int, int, char*);
		struct {
		BYTE b;
		BYTE g;
		BYTE r;
		} pRGB[1000][1000];
};

#endif