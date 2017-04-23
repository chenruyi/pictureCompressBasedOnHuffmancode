#include "Huffman.h"
#include<string>
#include<iostream>
#include<stdlib.h>
bool Select(HuffmanTree HT, int n, int & s1, int & s2)
{
	int i = 1, s3;
	while (HT[i].parent != 0)
		i++;
	s1 = i;
	i++;                                     //���ҵ�һ��
	while (HT[i].parent != 0)
		i++;
	s2 = i;                            //���ҵڶ���
	if (HT[s1].weight>HT[s2].weight)
	{
		s3 = s1;
		s1 = s2;
		s2 = s3;
	}
	for (i++; i <= n; i++)//�ٰ�ʣ�±����Ƚ�
	{
		if (HT[i].parent == 0)
		{
			if (HT[i].weight<HT[s1].weight)
				s1 = i;
			else if (HT[i].weight<HT[s2].weight)
				s2 = i;
		}
	}
	return true;
}

bool HuffmanCodeing(HuffmanTree & HT, HuffmanCode & HC, int * w, int n)
{
	//w���n���ַ���Ȩֵ��>0��,����շ�����HT,�����n���ַ��ĺշ�������HC
	if (n <= 1) { printf("ERROR!!n<0!!");	exit(0); }
	int m = 2 * n - 1;
	int i = 0;
	HuffmanTree p;
	HT = (HuffmanTree)malloc((m +1) * sizeof(HTNode));
	p = HT+1;
	for (i = 1; i <= n; i++) {
		//	*p={*w,0,0,0}; 
		p->weight = *w;
		p->lchild = 0;
		p->parent = 0;
		p->rchild = 0;

		p = p + 1;
		w = w + 1;

	}
	for (; i <= m; ++i, ++p) {
		//	*p={0,0,0,0};
		p->weight = 0;
		p->lchild = 0;
		p->parent = 0;
		p->rchild = 0;

	}
	int s1 = 0, s2 = 0;
	for (i = n + 1; i <= m; ++i) {
		//�����շ�����
		//��HT[1...i-1]ѡ��parentΪ0��weight��С��������㣬�����Ϊs1��s2
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//testHufTree(HT);
	HC = (HuffmanCode)malloc(( n + 1 ) * sizeof(char *));
	HuffmanCoding(HC, HT);


	//////��Ҷ�ӵ�����������ÿ���ַ��ĺշ�������
	//HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));
	//if (HC == NULL) { printf("�ռ����ʧ��"); }
	//char *cd;
	//cd = (char *)malloc(n * sizeof(char));
	//cd[n - 1] = '\0';
	//
	//for (i = 1; i <= n; i++) {
	//	int start = n - 1;
	//	int c, f;
	//	for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
	//		//��Ҷ�ӵ������������
	//		if (HT[f].lchild == c) cd[--start] = '0';
	//		else cd[--start] = '1';
	//		
	//		HC[i] = (char *)malloc((n - start) * sizeof(char));
	//		if (HC[i] == NULL) { printf("�ռ����ʧ��"); }
	//		strcpy_s(HC[i],512,&cd[start]); //(HC[i], cd[start]);
	//}
	//free(cd);
	//TestHufCode(0, HT, HC);
	return true;
}

int HuffmanCoding(HuffmanCode & pHC, HuffmanTree & pHT)
{
	char cd[256] = { "\0" };
	int cdlen = 0;
	for (int i = 1; i < 512; i++)
	{
		pHT[i].weight = 0;
	}
	int p = 511;
	while (p != 0)
	{
		if (pHT[p].weight == 0)
		{
			pHT[p].weight = 1;
			if (pHT[p].lchild != 0)
			{
				p = pHT[p].lchild;
				cd[cdlen++] = '0';
			}
			else if (pHT[p].rchild == 0)
			{
				pHC[p] = (char *)malloc((cdlen + 1)*sizeof(char));
				cd[cdlen] = '\0';
				for (int i = 0; i <= cdlen; i++)
				{
					pHC[p][i] = cd[i];
				}
				//strcpy_s(pHC[p],sizeof(cd), cd);
				//std::cout <<"----------\n"<<p << "\t" << pHC[p] << std::endl;
			}
		}
		else if (pHT[p].weight == 1)
		{
			pHT[p].weight = 2;
			if (pHT[p].rchild != 0)
			{
				p = pHT[p].rchild;
				cd[cdlen++] = '1';
			}
		}
		else
		{
			pHT[p].weight = 0;
			p = pHT[p].parent;
			--cdlen;
		}
	}


	return 1;
}

void testHufTree(HuffmanTree HT)
{

	std::cout << " " << "\t" << "Ȩֵ" << "\t" << "���ڵ�" << "\t" << "����" << "�Һ���" <<std::endl;
	for (int i = 1; i < 512; i++)
	{

		std::cout << i << "\t" << HT[i].weight << "\t" << HT[i].parent << "\t"<< HT[i].lchild << "\t" << HT[i].rchild<<"\n";
	}
}

void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC)
{
	if (pHT[root].lchild == 0 && pHT[root].rchild == 0)
	{
		printf("0x%02X\t%s\n", root - 1, pHC[root - 1]);
	}
	if (pHT[root].lchild)
	{
		TestHufCode(pHT[root].lchild, pHT, pHC);
	}
	if (pHT[root].rchild)
	{
		TestHufCode(pHT[root].rchild, pHT, pHC);
	}
}
