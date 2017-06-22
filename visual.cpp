#include "visual.h"
#include "graph.h"
#include <pshpack2.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

void Visual::Paint(Graph& G){
	
	for (int i = 0; i < 1000; ++ i){
		for (int j = 0; j < 1000; ++ j){
			pRGB[i][j].r = 255;
			pRGB[i][j].g = 255;
			pRGB[i][j].b = 255;
		}
	}
	
	double rate;
	if (G.N < G.M) rate = 1000./G.N/3;
		else rate = 1000./G.M/3;
	//cout << rate << endl;
	//60,179,113
	//cout << G.N << " " << G.M << endl;
	for (int i = 0; i < G.n/2-1; ++ i){
		int i1 = (int)((i/G.M)*rate), j1 = (int)((i%G.M)*rate);
		for (int j = 0; j < G.node[i+G.n/2-1].size(); ++ j)
		if (G.flow[i+G.n/2-1][j] == 0 && G.cost[i+G.n/2-1][j] >= 0){
			if (G.node[i+G.n/2-1][j] == i  || G.node[i+G.n/2-1][j] == G.S || G.node[i+G.n/2-1][j] == G.T)
				continue;
			int p = G.node[i+G.n/2-1][j];
			int i2 = (int)((p/G.M)*rate), j2 = (int)((p%G.M)*rate);
			for (int k1 = min(i1,i2)*3; k1 <= max(i1,i2)*3 && k1 < 1000; ++k1)
				for (int k2 = min(j1,j2)*3; k2 <= max(j1,j2)*3 && k2 < 1000; ++k2){
					pRGB[k1][k2].r = 60;
					pRGB[k1][k2].g = 179;
					pRGB[k1][k2].b = 113;
				}
		}
	}
	
	for (int i = 1; i <= G.row; ++ i){
		for (int j = 1; j <= G.col; ++ j){
			int i1 = (int)((G.K+1)*i*rate), j1 = (int)((G.K+1)*j*rate);
			for (int k1 = max(i1*3-2, 0); k1 <= min(1000, i1*3+2); k1++)
				for (int k2 = max(j1*3-2, 0); k2 <= min(1000, j1*3+2); k2++){
					pRGB[k1][k2].r = 0;
					pRGB[k1][k2].g = 0;
					pRGB[k1][k2].b = 255;
				}
				/*
			int x = (G.K+1)*i, y = (G.K+1)*j;
			int id = x*G.M+y;
			for (int k = 0; k < G.node[id].size(); ++ k)
			if (G.flow[id][k] == 0 && G.node[id][k] != G.S){
				int p = G.node[id][k];
				int i2 = (int)((p/G.M)*rate), j2 = (int)((p%G.M)*rate);
				for (int k1 = min(i1,i2)*3; k1 <= max(i1,i2)*3 && k1 < 1000; ++k1)
					for (int k2 = min(j1,j2)*3; k2 <= max(j1,j2)*3 && k2 < 1000; ++k2){
						pRGB[k1][k2].r = 60;
						pRGB[k1][k2].g = 179;
						pRGB[k1][k2].b = 113;
					}
				}*/
		}
	}
	
	// 生成BMP图片
	//char* filename = "show.bmp";
	generateBmp( (BYTE*)pRGB, 1000, 1000, "show.bmp" );
}

void Visual::generateBmp(BYTE* pData, int width, int height, char* filename){//生成Bmp图片，传递RGB值，传递图片像素大小，传递图片存储路径
	int size = width*height*3; // 每个像素点3个字节
	// 位图第一部分，文件信息
	BMPFILEHEADER_T bfh;
	bfh.bfType = 0X4d42;  //bm
	bfh.bfSize = size  // data size
		+ sizeof( BMPFILEHEADER_T ) // first section size
		+ sizeof( BMPINFOHEADER_T ) // second section size
		;
	bfh.bfReserved1 = 0; // reserved

	bfh.bfReserved2 = 0; // reserved
	bfh.bfOffBits = bfh.bfSize - size;
	// 位图第二部分，数据信息
	BMPINFOHEADER_T bih;
	bih.biSize = sizeof(BMPINFOHEADER_T);
	bih.biWidth = width;
	bih.biHeight = height;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = 0;
	bih.biSizeImage = size;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;      
	FILE * fp = fopen( filename,"wb" );
	if( !fp ) return;
	fwrite( &bfh, 1, sizeof(BMPFILEHEADER_T), fp );
	fwrite( &bih, 1, sizeof(BMPINFOHEADER_T), fp );
	fwrite( pData, 1, size, fp );
	fclose( fp );
}
