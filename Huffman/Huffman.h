#pragma once
#ifndef HUFFMANTREE
#define HUFFMANTREE
typedef struct {
	int weight;
	int parent, lchild, rchild;
}HTNode,*HuffmanTree;
typedef char **HuffmanCode;
//typedef char HuffmanCode[2][256];
bool Select(HuffmanTree HT, int n, int &s1, int &s2);
bool HuffmanCodeing(HuffmanTree &HT, HuffmanCode &HC, int *w, int n);
int HuffmanCoding(HuffmanCode &pHC, HuffmanTree &pHT);
void testHufTree(HuffmanTree HT);
void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC);


#endif