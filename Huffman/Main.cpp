#include<iostream>
#include<stdlib.h>
#include<fstream>
#include"Compress.h"
#include"Huffman.h"
using namespace std;
int main()
{
	char filename[256];

	cout << "============Huffman�ļ�ѹ��==========" << endl;
	cout << "�������ļ�����";
	cin >> filename;
	
	if (Compress(filename) == 1)
	{
		cout << "ѹ���ɹ�" << endl;
	}
	
		
	

	return 0;
}