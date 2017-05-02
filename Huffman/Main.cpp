#include<iostream>
#include<stdlib.h>
#include<fstream>
#include"Compress.h"
#include"Huffman.h"
using namespace std;
int main()
{
	char filename[256];

	cout << "============Huffman文件压缩==========" << endl;
	cout << "请输入文件名：";
	cin >> filename;
	
	if (Compress(filename) == 1)
	{
		cout << "压缩成功" << endl;
	}
	
		
	

	return 0;
}