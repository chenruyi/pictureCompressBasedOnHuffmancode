#include "Compress.h"
#include<string>

#include<iostream>
#include<fstream>
using namespace std;
int InitHead(const char * pFileName, HEAD & sHead)
{
	//初始化文件头
	strcpy_s(sHead.type, "HUF");//文件类型
	sHead.length = 0;
	for (int i = 0; i < 256; i++)
	{
		sHead.weight[i] = 0;
	}
	ifstream filein1(pFileName, ios::in | ios::binary);
	int ch;
	while (true)
	{
		ch = filein1.get();
		if (filein1.eof())	break;
		
		sHead.weight[ch]++;
		sHead.length++;
	}
	filein1.clear();
	filein1.close();
	return 1;
}
char Str2byte(const char * pBinStr)
{
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;//左移
		if (pBinStr[i] == '1')
		{
			b = b | 0x01;
		}
	}
	return b;
}

bool Compress(const char * pFilename)
{
	HuffmanTree pHT;
	HuffmanCode pHC;
	ifstream fin2(pFilename, ios::in | ios::binary);
	int weight[256] = { 0 };
	int ch ;	
	while (true)
	{
		ch = fin2.get();
		if (fin2.eof())	break;
		weight[ch]++;		
	}
	fin2.clear();
	fin2.close();
	
	HuffmanCodeing(pHT, pHC, weight, 256);
	int plength=0;
	//计算缓冲区大小
	static int nSize = 0;
	for (int i = 0; i < 256; i++)
	{
		nSize += weight[i] * strlen(pHC[i+1]);
		plength += weight[i] * 8;
	}
	plength = plength / 8;
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
	
	//压缩编码
	static char *pBuffer = (char *)malloc(nSize * sizeof(char));
	
	Encode(pFilename, pHC, pBuffer, nSize);
	if (!pBuffer)
	{
		return 0;
	}
	HEAD filehead;
	if (InitHead(pFilename, filehead))
	{
		int len= WriteFile(pFilename, filehead, pBuffer, nSize);
		if (len>0)
		{
			cout << "原文件大小：" << plength << "字节" << endl;
			cout << "压缩后文件大小：" << len << "字节" << endl;
			cout << "压缩比：" << (plength - len)*100.0 / plength <<"%"<< endl;
			
		}
	}

	return true;
}

int Encode(const char * pFilename, const HuffmanCode pHC, char * &pBuffer, const int nSize)
{
	ifstream filein3(pFilename, ios::in | ios::binary);
	if (!pBuffer)
	{
		std::cerr << "开辟缓冲区失败 " << std::endl;
		return 0;
	}
	char cd[SIZE] = { 0 };
	int pos = 0;//缓冲区指针
	int ch;
	
	while (!filein3.eof())
	{
		ch = filein3.get();
		 if (ch ==-1 ) 
			 continue;
		strcat_s(cd, pHC[ch+1]);
		
		while (strlen(cd) >= 8)
		{
			pBuffer[pos++] = Str2byte(cd);
			
			for (int i = 0; i < SIZE - 8; i++)
			{
				cd[i] = cd[i + 8];
			}
		}
	}
	filein3.clear();
	filein3.close();

	if (strlen(cd) > 0)
	{
		pBuffer[pos++] = Str2byte(cd);
		
	}
	
	return 1;
}

int WriteFile(const char * pFilename, const HEAD sHead, const char* pBuffer, const int nSize)
{
	char filename[256] = { 0 };
	strcpy_s(filename, pFilename);
	strcat_s(filename, ".buf");

	ofstream fileout1(filename, ios::app|ios::binary);
	
	fileout1.write((char*)&sHead, sizeof(HEAD));
	for (int i = 0; i <=nSize; i++)
	{
		fileout1.write((char*)& pBuffer[i], sizeof(pBuffer[i]));
	}
	fileout1.clear();
	fileout1.close();
	
	cout << "生成压缩文件：" << filename << endl;

	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nSize;
	return len;
	
}
