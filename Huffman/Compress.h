#pragma once
#ifndef COMPRESS
#define COMPRESS
#define SIZE 512
#include"Huffman.h"
struct HEAD
{
	char type[4];	//文件类型
	int length;		//原文件长度
	int weight[256];//权值
};
int InitHead(const char*pFileName, HEAD &sHead);
char Str2byte(const char*pBinStr);
int Compress(const char *pFilename);
int Encode(const char*pFilename, const HuffmanCode pHC, char  * &pBuffer, const int nSize);
int WriteFile(const char*pFilename, const HEAD sHead, const char* pBuffer, const int nSize);
#endif
