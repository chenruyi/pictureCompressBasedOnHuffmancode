#include "Compress.h"

#include<string>
#include<cstring>
#include<iostream>
#include<fstream>
using namespace std;
int InitHead(const char * pFileName, HEAD & sHead)
{
	//初始化文件头
	strcpy_s(sHead.type, "HUF");//文件类型
	sHead.length = 0;
	for (int i = 0; i < SIZE; i++)
	{
		sHead.weight[i] = 0;
	}
	ifstream fin(pFileName, ios::in | ios::binary);
	int ch;
	while (!fin.eof())
	{
		ch = fin.get();
		sHead.weight[ch]++;
		sHead.length++;
	}
	fin.close();
	return 0;
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

int Compress(const char * pFilename)
{
	HuffmanTree pHT;
	HuffmanCode pHC;
	
	int weight[256] = { 0 };
	int ch ;
	
	
	//////哈夫曼编码
	//FILE *in; fopen_s(&in, pFilename, "rb");
	//while ((ch = fgetc(in)) != EOF)
	//{
	//	weight[ch++];
	//}
	//fclose(in);
	ifstream fin(pFilename, ios::in | ios::binary);
	while (!fin.eof())
	{
		ch=fin.get();
		weight[ch]++;
		
	}
	fin.close();
	
	//HuffmanCodeing(pHT, pHC, weight, 256);
	HuffmanCodeing(pHT, pHC, weight, 256);
	//TestHufCode(0, pHT, pHC);
	//cout << pHC[0][0];
	//计算缓冲区大小
	int nSize = 0;
	for (int i = 0; i < 256; i++)
	{
		nSize += weight[i] * strlen(pHC[i+1]);
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;

	//压缩编码
	char *pBuffer=NULL ;
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
			cout << "文件大小：" << len << "字节" << endl;
		}
	}
	return 1;
}

int Encode(const char * pFilename, const HuffmanCode pHC, char * &pBuffer, const int nSize)
{
	pBuffer = (char *)malloc(nSize * sizeof(char));
	if (!pBuffer)
	{
		std::cerr << "开辟缓冲区失败 " << std::endl;
		return 0;
	}
	char cd[SIZE] = { 0 };
	int pos = 0;//缓冲区指针
	int ch;
	ifstream fin(pFilename, ios::in | ios::binary);
	while (!fin.eof())
	{
		ch = fin.get();
		 if (ch ==-1 ) 
			 continue;
		for (int i = 0; i <= 256; i++)
		{
			
			cd[i] = pHC[ch+1][i];
		}
		//if (ch >= 255)
		//	cout << ch << "   " << cd<<endl;
		//strcat_s(cd, pHC[ch]);
		//strcpy_s(cd, pHC[ch]);
		
		while (strlen(cd) >= 8)
		{
			pBuffer[pos++] = Str2byte(cd);
			for (int i = 0; i < SIZE - 8; i++)
			{
				cd[i] = cd[i + 8];
			}
		}
	}
	if (strlen(cd) > 0)
	{
		pBuffer[pos++] = Str2byte(cd);
	}
	fin.close();
	
	return 1;
}

int WriteFile(const char * pFilename, const HEAD sHead, const char* pBuffer, const int nSize)
{
	char filename[256] = { 0 };
	strcpy_s(filename, pFilename);
	strcat_s(filename, ".buf");

	ofstream fout(filename, ios::app|ios::binary);
	
	fout.write((char*)&sHead, sizeof(HEAD));
	fout.write(pBuffer, sizeof(char));
	fout.close();
	cout << "生成压缩文件：" << filename << endl;
	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nSize;
	return len;
	return 0;
}
