#include<iostream>
#include<stdlib.h>
#include<fstream>
#include"Compress.h"
#include"Huffman.h"
using namespace std;
int main()
{
	cout << "============Huffman文件压缩==========" << endl;
	cout << "请输入文件名：";
	//char filename [256];
	//cin >> filename;
	char *filename = "F://picture.bmp";
	//int ch;
	//int weight[256] = { 0 };
	//ifstream fin(filename, ios::in|ios::binary);
	//while (!fin.eof())
	//{
	//	ch = fin.get();
	//	weight[ch]++;
	//	//cout << ch<<" ";
	//	if(ch<0)
	//		cout << "\n" << ch << '\t' << weight[ch] << endl;
	//}
	//
	//fin.close();
	
	if (Compress(filename))
	{
		cout << "文件压缩成功" << endl;
	}
	
	return 0;
}