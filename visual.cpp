#include "visual.h"
#include "greedy.h"
#include "graph.h"
#include <pshpack2.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};

void Visual::Paint(Greedy& G){
	for (int i = 0; i < 3000; ++ i){
		for (int j = 0; j < 3000; ++ j){
			pRGB[i][j].r = 255;
			pRGB[i][j].g = 255;
			pRGB[i][j].b = 255;
		}
	}
	double rate;
	if (G.N > G.M) rate = 3000./G.N/2;
		else rate = 3000./G.M/2;
	
	for (int i = G.K+1; i <= (G.K+1)*G.row; i+=G.K+1)
		for (int j = G.K+1; j <= (G.K+1)*G.col; j+=G.K+1){
			int ii = i, jj = j;
			while (G.MAP[ii][jj]!=-1 && ii!=0 && jj!=0 && ii!=G.N-1 && jj!=G.M-1){
				int iii = ii+dx[G.MAP[ii][jj]], jjj = jj+dy[G.MAP[ii][jj]];
				int i1 = (int)(ii*rate), j1 = (int)(jj*rate);
				int i2 = (int)(iii*rate), j2 = (int)(jjj*rate);
				for (int k1 = min(i1,i2)*2; k1 <= max(i1,i2)*2 && k1 < 3000; ++k1)
					for (int k2 = min(j1,j2)*2; k2 <= max(j1,j2)*2 && k2 < 3000; ++k2){
						pRGB[k1][k2].r = 60;
						pRGB[k1][k2].g = 179;
						pRGB[k1][k2].b = 113;
					}
				ii = iii; jj = jjj;
			}
		}
	
	for (int i = 1; i <= G.row; ++ i){
		for (int j = 1; j <= G.col; ++ j){
			int i1 = (int)((G.K+1)*i*rate), j1 = (int)((G.K+1)*j*rate);
			for (int k1 = max(i1*2-2, 0); k1 < min(3000, i1*2+2); k1++)
				for (int k2 = max(j1*2-2, 0); k2 < min(3000, j1*2+2); k2++){
					pRGB[k1][k2].r = 0;
					pRGB[k1][k2].g = 0;
					pRGB[k1][k2].b = 255;
				}
		}
	}
	
	// 生成BMP图片
	generateBmp( (BYTE*)pRGB, 3000, 3000, "greedy.bmp" );
}

void Visual::Paint(Graph& G){
	for (int i = 0; i < 3000; ++ i){
		for (int j = 0; j < 3000; ++ j){
			pRGB[i][j].r = 255;
			pRGB[i][j].g = 255;
			pRGB[i][j].b = 255;
		}
	}
	
	double rate;
	if (G.N > G.M) rate = 3000./G.N/2;
		else rate = 3000./G.M/2;
		
	for (int i = 0; i < G.N; ++i)
		for (int j = 0; j < G.M; ++j){
			//if (i+i > G.N || j+j > G.M) continue;
			int i1 = (int)(i*rate), j1 = (int)(j*rate);
			
			for (Edge* e = G.E[G.Number[i][j]+1]; e != NULL; e = e->next)
			if (e->flow == 0 && e->cost >= 0){
				int p = e->y;
				if (p == G.Number[i][j] || p == G.S || p == G.T)
					continue;
				//int i2 = (int)((p/G.M)*rate), j2 = (int)((p%G.M)*rate);
				int i2, j2;
				if (i < G.N-1 && p == G.Number[i+1][j]){
					i2 = (int)((i+1)*rate);
					j2 = (int)(j*rate);
				} else
				if (i > 0 && p == G.Number[i-1][j]){
					i2 = (int)((i-1)*rate);
					j2 = (int)(j*rate);
				} else
				if (j < G.M-1 && p == G.Number[i][j+1]){
					i2 = (int)(i*rate);
					j2 = (int)((j+1)*rate);
				} else
				if (j > 0 && p == G.Number[i][j-1]){
					i2 = (int)(i*rate);
					j2 = (int)((j-1)*rate);
				}
				
				for (int k1 = min(i1,i2)*2; k1 <= max(i1,i2)*2 && k1 < 3000; ++k1)
					for (int k2 = min(j1,j2)*2; k2 <= max(j1,j2)*2 && k2 < 3000; ++k2){
						pRGB[k1][k2].r = 60;
						pRGB[k1][k2].g = 179;
						pRGB[k1][k2].b = 113;
					}
		}
	}
	
	for (int i = 1; i <= G.row; ++ i){
		for (int j = 1; j <= G.col; ++ j){
			int i1 = (int)((G.K+1)*i*rate), j1 = (int)((G.K+1)*j*rate);
			for (int k1 = max(i1*2-2, 0); k1 < min(3000, i1*2+2); k1++)
				for (int k2 = max(j1*2-2, 0); k2 < min(3000, j1*2+2); k2++){
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
	generateBmp( (BYTE*)pRGB, 3000, 3000, "flow.bmp" );
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
