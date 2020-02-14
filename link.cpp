#include"link.h"
#include<stdlib.h>
#include<string.h>
Link* link_init()
{
	Link* link;
	link = (Link*)malloc(sizeof(Link));
	link->head = NULL;
	link->tail = NULL;
	return link;
}
int link_append(Link* link, char* userblack, char*userwhite,int* offset)
{
	LinkNode* linknode;
	linknode = (LinkNode*)malloc(sizeof(LinkNode));
	if (linknode == NULL){
		return 0;
	}
	strncpy(linknode->userblack, userblack,10);
	strncpy(linknode->userwhite, userwhite,10);
	
	linknode->offset = *offset;
	linknode->next = NULL;
	if (link->head == NULL){
		link->head = linknode;
		link->tail = linknode;
	}
	else{
		link->tail->next = linknode;
		link->tail = link->tail->next;
	}
	return 1;

}
int link_append_grade(Link* link, int *x,int*y,int*grade)
{
	LinkNode* linknode;
	linknode = (LinkNode*)malloc(sizeof(LinkNode));
	if (linknode == NULL){
		return 0;
	}
	linknode->grade = *grade;
	linknode->x = *x;
	linknode->y = *y;

	
	linknode->next = NULL;
	if (link->head == NULL){
		link->head = linknode;
		link->tail = linknode;
	}
	else{
		link->tail->next = linknode;
		link->tail = link->tail->next;
	}
	return 1;

}
LinkNode* link_find(Link* link,char* userblack,char* userwhite,int* time)
{
	LinkNode* curpointer;
	curpointer = link->head;
	while (curpointer != NULL){
		if (strcmp(userblack, curpointer->userblack)==0 ||strcmp(userwhite, curpointer->userwhite)==0 )
			break;
		
		else{
			curpointer = curpointer->next;
		}
	}
	return curpointer;
}
void link_destruct(Link* link){
	LinkNode* linknode, *nextnode;

	linknode=link->head;
	while (linknode != NULL)
	{
		nextnode = linknode->next;
		free(linknode);
		linknode = nextnode;
	}
	free(link);
}
LinkNode* find_maxgrade(Link*link)
{
	LinkNode* currentNode;
	int grade[365] = {0};
	int Length = 0;
	int maxgrade=0;
	currentNode = link->head;
	while (currentNode!=NULL)
	{
		grade[Length] = currentNode->grade;
		Length++;
		currentNode=currentNode->next;
	}
	maxgrade = grade[0];
	for (int j = 0; j < Length; j++)
	{
		if (maxgrade < grade[j])
		{
			maxgrade = grade[j];
		}
	}
	currentNode = link->head;
	while (currentNode!=NULL)
	{
		if (maxgrade == currentNode->grade)
		{
			return currentNode;
		}
		else
		{
			currentNode = currentNode->next;
		}
	}
	return currentNode;
}