#include"bitree.h"
#include"link.h"
int char_cmpfunc(void*p, void*q)
{
	char *a;
	char *b;
	a = (char*)p;
	b = (char*)q;
	return strcmp(a, b);
}
BiTree*biTree_init(int length, cmp_f cmp)
{
		BiTree*bitree;
		bitree = (BiTree*)malloc(sizeof(BiTree));
		bitree->length = length;
		bitree->cmp = cmp;
		bitree->parentNode = NULL;
		bitree->curNode = NULL;

		return bitree;
	
}
void curNode_init(BiTree*bitree)
{
	bitree->curNode = bitree->parentNode;
}
BiTNode* init_bitNode(){

	BiTNode*bitNode;
	bitNode = (BiTNode*)malloc(sizeof(BiTNode));
	//bitNode = NULL;
	bitNode->lchild = NULL;
	bitNode->rchild = NULL;
	bitNode->mchild = NULL;
	return bitNode;
}
int bitree_append(BiTree*bitree, int*offset, void*p, cmp_f cmp)
{

	BiTNode* bitnode, *tempnode;
	int judge;
	bitnode = init_bitNode();
	tempnode = init_bitNode();
	//p = 
		bitnode->p = malloc(bitree->length);
	memcpy(bitnode->p, p, bitree->length);
	bitnode->offset = *offset;


	if (bitree->curNode == NULL)
	{
		bitree->parentNode = bitnode;
		bitree->curNode = bitnode;
		return 1;
	}
	else{
		judge = cmp(p, bitree->curNode->p);
	}
	if (judge > 0)
	{
		if (bitree->curNode->lchild == NULL)
		{
			bitree->curNode->lchild = bitnode;
			return 1;
		}
		else{
			bitree->curNode = bitree->curNode->lchild;
			bitree_append(bitree,offset ,p, cmp);
		}
	}
	else if (judge<0)
	{
		if (bitree->curNode->rchild == NULL)
		{
			bitree->curNode->rchild = bitnode;
			return 1;
		}
		else{
			bitree->curNode = bitree->curNode->rchild;
			bitree_append(bitree, offset, p, cmp);
		}
	}
	else {
		if (judge == 0)
		{

			bitree->curNode->mchild = bitnode;
			return 1;
		}
		
	}
	return 1;
}
BiTNode* BiNode_find(BiTree*bitree, void*p, cmp_f cmp)
{

	int judge;
	BiTNode*tempNode;
	tempNode = (BiTNode*)malloc(sizeof(BiTNode));
	if (bitree->curNode == NULL)
	{
		return bitree->curNode;
	}
	judge = cmp(p, bitree->curNode->p);
	if (judge > 0)
	{
		bitree->curNode = bitree->curNode->lchild;
		BiNode_find(bitree, p, cmp);
	}
	else if (judge < 0)
	{
		bitree->curNode = bitree->curNode->rchild;
		BiNode_find(bitree, p, cmp);
	}
	else if (judge == 0)
	{
		return bitree->curNode; // 返回不完整 ；加栈
	}
}

void destruct_node(BiTNode *node){
	if (node->lchild != NULL){
		destruct_node(node->lchild);
		//free(node->lchild);
	}
	if (node->rchild != NULL){
		destruct_node(node->rchild);
		//free(node->rchild);
	}
	if (node->mchild != NULL){
		destruct_node(node->mchild);
		//free(node->mchild);
	}
	free(node->p);
	free(node);
}

void bitree_destruct(BiTree* bitree){

	destruct_node(bitree->parentNode);
	free(bitree);
}