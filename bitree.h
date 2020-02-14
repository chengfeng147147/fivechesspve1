#include<stdlib.h>
#include<string.h>
#include"link.h"
#ifndef _BITREE_H
#define _BITREE_H

typedef int (cmp_f)(void*p, void*q);
typedef struct _biTNode{

	void *p;
	int offset;
	_biTNode *lchild, *rchild, *mchild;

};
typedef struct _biTNode BiTNode;
typedef struct _biTree{
	int length;
	cmp_f*cmp;
	BiTNode*parentNode;
	BiTNode*curNode;
};
typedef struct _biTree BiTree;
extern int char_cmpfunc(void*p, void*q);
extern BiTree*biTree_init(int length, cmp_f cmp);
extern void curNode_init(BiTree*bitree);
extern int bitree_append(BiTree*bitree, int*offset, void*p, cmp_f cmp);
extern BiTNode* BiNode_find(BiTree*bitree, void*p, cmp_f cmp);
extern void bitree_destruct(BiTree* bitree);
#endif