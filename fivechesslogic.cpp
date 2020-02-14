#include<stdio.h>
#include<time.h>
#include<string.h>
#include"stack.h"
#include "fivechesslogic.h"
#include<stdlib.h>
#include"bitree.h"
int judge_line(int* line, int length);
void judge_count(Link*link, int*currentchess, int* savechess, int i, int j, int grade, int *count);
typedef struct Data {
	int chess[WIDTH][LENGTH];
	int steps;
}_fivechess;
_fivechess Fivechess;
typedef struct filedata{
	int length;
	char playername[10];
	char playername2[10];
	int time[6];
	Step step[MAXCOUNT];

}Filedata;



int* get_data(){
	return (int*) Fivechess.chess;
}

void stack_initi() {
	stack_init();
}

void initialize()
{
	for (int x = 0; x < LENGTH; x++)
	{

		for (int y = 0; y < LENGTH; y++)
		{
			Fivechess.chess[x][y] = 0;

		}
	}
	Fivechess.steps = 1;
	
}
int go(int x, int y)
{
	Step step;
	
  if (Fivechess.chess[x][y] == 0)
	{
	  step.x = x;
	  step.y = y;
	  step.colour = Fivechess.steps%2==0?1:-1;
	  stack_push(&step);
	  Fivechess.chess[x][y] = step.colour;
	  Fivechess.steps++;
	  return 1;
	}
  return 0;
}
void regret(int *px,int *py,int* colour)
{
	Step step;

	stack_pop(&step);
	*px = step.x;
	*py = step.y;
	*colour = step.colour;
	Fivechess.chess[step.x][step.y] = 0;
	Fivechess.steps--;
	
	
}



int get_winner(int y, int x)
{
	int savex = x, savey = y;
	int savechess,count=0,cutcount;
	int line[LENGTH];
	
	savechess = judge_line(Fivechess.chess[y], LENGTH);//判断行
	if (savechess != EMPTY){ return savechess; }
	for (int i = 0; i < LENGTH; i++)//判断列
	{
		line[count] = Fivechess.chess[i][x];
		count++;
	}
	savechess = judge_line(line, LENGTH);
	if (savechess != EMPTY){ return savechess; }
	
	y += x;//左下右上，找到该点所在斜线的第一个点
	x = 0;
	if (y <= 18)
	{
		count = y + 1;
	}
	else
	{
		cutcount = y - 18;
		count = 19 - cutcount;
		y -= cutcount;
		x = cutcount;
	}
	for (int i = 0; i < count; i++)
	{
		line[i] = Fivechess.chess[y][x];
		y--; x++;
	}
	savechess = judge_line(line, count);
	if (savechess != EMPTY){
		return savechess;
	}
	x = savex;
	y = savey;
	x -= y;
	y = 0;
	if (x >= 0)
	{
		count = LENGTH - x;
		
	}
	else
	{
		cutcount = -x;
		count = LENGTH - cutcount;
		y += cutcount;
		x += cutcount;
	}
	for (int i = 0; i < count;i++)
	{
		line[i] = Fivechess.chess[y][x];
		y++;
		x++;
	}
	savechess = judge_line(line, count);
	if (savechess != EMPTY){
		return savechess;
	}
	return EMPTY;
}

int judge_line(int* line, int length){
	int savechess = EMPTY;
	int count = 0;
	int currentchess = EMPTY;

	for (int i = length; i > 0; i--){
		currentchess = *line;
		line++;
		if (currentchess == EMPTY){
			savechess = EMPTY;
			count = 0;
		}
		else if (currentchess == savechess){
			count++;
		}
		else {
			count = 1;
			savechess = currentchess;
		}

		if (count == 5) {
			return currentchess;
		}
	}
	return EMPTY;
}
void recover_chess(int*x,int*y,int*colour)
{
	Step step;
	stack_firstpop( &step);
	Fivechess.chess[step.x][step.y] = step.colour;
	*x = step.x;
	*y = step.y;
	*colour = step.colour;
	
}
void get_time(int* timepp)

   {          time_t timep;
				 tm *p;
			time(&timep);
			p = gmtime(&timep);
			
			*(timepp + 5) = p->tm_sec;
			*(timepp + 4)=p->tm_min; /*获取当前分*/
			*(timepp+3)= 8 + p->tm_hour;/*获取当前时,这里获取西方的时间,刚好相差八个小时*/
			*(timepp+2)= p->tm_mday;/*获取当前月份日数,范围是1-31*/
			*(timepp +1)= 1 + p->tm_mon;/*获取当前月份,范围是0-11,所以要加1*/
			*timepp=1900 + p->tm_year;/*获取当前年份,从1900开始，所以要加1900*/
   }
void write_file(   char* playname, char* playname2)
{
	

	FILE *fp;
	Step step;
	Filedata filedata;
	
	filedata.length = Fivechess.steps*sizeof(int)*3+6*sizeof(int)+2*STRING;
	strcpy(filedata.playername ,playname);
	strcpy(filedata.playername2 , playname2);

	

	for (int i = 0; i < 6; i++){
		filedata.time[i] = 9;
		
    }
	for (int i = 0; i < Fivechess.steps;i++)
	{
		stack_firstpop(&step);
		filedata.step[i].colour = step.colour;
		filedata.step[i].x = step.x;
		filedata.step[i].y= step.y;
	}
	firstpointer_init();
	fp = fopen("../chessmanual.bin", "ab");
	fseek(fp, 0, SEEK_END);
	fwrite(&filedata, filedata.length , 1, fp);
	fclose(fp);
}

BiTree* read_file(BiTree*bitree)
{
	FILE* fp;
	int offset1 = 0;
	int offset2 = 0;
	int offset3 = 0;
	char user1[10];
	char user2[10];
	int judge=1;
	int time[6];
	fp = fopen("../chessmanual.bin", "r");
	while (judge!=0)
	{
		
		offset2 = offset1;
		
		fseek(fp, offset1 + sizeof(int), SEEK_SET);
		fread(user1, sizeof(char[10]), 1, fp);
		fseek(fp, offset1 + sizeof(int)+sizeof(char[10]), SEEK_SET);
		fread(user2, sizeof(char[10]), 1, fp);
		fseek(fp, offset1 + sizeof(int)+sizeof(char[10]) + sizeof(char[10]), SEEK_SET);
		fread(time, sizeof(int[6]), 1, fp);
		curNode_init(bitree);
		bitree_append(bitree, &offset1, user1,char_cmpfunc);
		
		fseek(fp, offset1, SEEK_SET);
		fread(&offset1, sizeof(int), 1, fp);
		offset1 += offset2;
		fseek(fp, offset1, SEEK_SET);
		judge=fread(&offset3, sizeof(int), 1, fp);
		
	}
	fclose(fp);
	return bitree;
}
rLink*find_chessmanual( BiTree*bitree, char* userblack, char*userwhite){
	
	FILE* fp;
	rLink*rlink;
	BiTNode*bitnode;
	int offset;
	int offset1;
	int steps;
	int chessdata[3];
	curNode_init(bitree);
	bitnode = BiNode_find(bitree, userblack,char_cmpfunc);
	
	if (bitnode == NULL){
		return NULL;
	}
	offset= bitnode->offset;
	fp = fopen("../chessmanual.bin", "r");
	fseek(fp, offset, SEEK_SET);
	
	fread(&offset1, sizeof(int), 1, fp);
	steps = offset1 - (sizeof(int)+sizeof(char[10]) * 2 + sizeof(int[6]));
	steps = steps/12;
	rlink = rlink_init();
	for (int i = 0; i < steps; i++)
	{
		fseek(fp, offset + sizeof(int)+sizeof(char[10]) * 2 + sizeof(int[6]) + i * 3*(sizeof(int)), SEEK_SET);
		fread(chessdata, sizeof(int), 3, fp);
		
		Fivechess.chess[chessdata[0]][chessdata[1]] = chessdata[2];
		rlink_append(rlink, chessdata, &chessdata[1], &chessdata[2]);	
	}
	fclose(fp);
	return rlink;
}

int rlink_append(rLink*rlink,int*x,int*y,int*color)
{
	LinkfileNode* linkfilenode;
	linkfilenode = (LinkfileNode*)malloc(sizeof(LinkfileNode));
	if (linkfilenode == NULL){
		return 0;
	}
	linkfilenode->sstep.color = *color;
	linkfilenode->sstep.x = *x;
	linkfilenode->sstep.y = *y;
	linkfilenode->next = NULL;
	if (rlink->head == NULL){
		rlink->head = linkfilenode;
		rlink->tail = linkfilenode;
	}
	else{
		rlink->tail->next = linkfilenode;
		rlink->tail = rlink->tail->next;
	}
	return 1;

}
int get_rlinkfirst(rLink*rlink,int*x, int*y, int*color)
{
	if (rlink->head != NULL)
	{
		*x = rlink->head->sstep.x;
		*y = rlink->head->sstep.y;
		*color = rlink->head->sstep.color;
		
		rlink->head = rlink->head->next;
		return 1;
	}
	else
	{ 
		return 0; 
	}
	
}
rLink* rlink_init()
{
	rLink* rlink;
	rlink = (rLink*)malloc(sizeof(rLink));
	rlink->head = NULL;
	rlink->tail = NULL;
	return rlink;
}
void rlink_destruct(rLink* rlink){
	LinkfileNode* rlinknode, *rnextnode;

	rlinknode = rlink->head;
	while (rlinknode != NULL)
	{
		rnextnode = rlinknode->next;
		free(rlinknode);
		rlinknode = rnextnode;
	}
	free(rlink);
}
//单人
void scan_chessboard(Link*link)
{
	int currentchess = NULL, savechess = NULL;
	int count = NULL;
	int grade = NULL;

	int x, y, color;
	int k = 0;
	
	//正行扫描
	for (int i = 0; i < LENGTH; i++)
	{
		count = NULL;
		for (int j = 0; j < LENGTH; j++)
		{
			currentchess = Fivechess.chess[i][j];
			judge_count(link, &currentchess, &savechess, i, j, grade, &count);
		}
	}
	//反行扫描
	for (int i = LENGTH - 1; i >= 0; i--)
	{
		count = NULL;
		for (int j = LENGTH - 1; j >= 0; j--)
		{
			currentchess = Fivechess.chess[i][j];
			judge_count(link, &currentchess, &savechess, i, j, grade, &count);
		}
	}
	//反列扫描
	for (int i = LENGTH - 1; i >= 0; i--)
	{
		count = NULL;
		for (int j = LENGTH - 1; j >= 0; j--)
		{
			currentchess = Fivechess.chess[j][i];
			judge_count(link, &currentchess, &savechess, j, i, grade, &count);
		}
	}
	//正列扫描
	for (int i = 0; i < LENGTH; i++)
	{
		count = NULL;
		for (int j = 0; j < WIDTH; j++)
		{
			currentchess = Fivechess.chess[j][i];
			judge_count(link, &currentchess, &savechess, j, i, grade, &count);
		}
	}
	//\方向 反上半部分
	for (int i = LENGTH - 1; i >= 0; i--){
		k = i;
		count = NULL;
		for (int j = LENGTH - 1; j >= LENGTH - 1 - i; j--){
			currentchess = Fivechess.chess[k][j];
			k--;
			judge_count(link, &currentchess, &savechess, k + 1, j, grade, &count);
		}
	}
	//\方向 正上半部分
	for (int i = 0; i < LENGTH - 4; i++)
	{
		k = i;
		count = NULL;
		for (int j = 0; j < LENGTH - i; j++)
		{
			currentchess = Fivechess.chess[j][k];
			k++;
			judge_count(link, &currentchess, &savechess, j, k - 1, grade, &count);
		}

	}
	///反方向下半部分
	for (int i = 0; i < LENGTH; i++){
		k = i;
		count = NULL;
		for (int j = LENGTH - 1; j >= i; j--){
			currentchess = Fivechess.chess[j][k];
			k++;
			judge_count(link, &currentchess, &savechess, j, k-1, grade, &count);
		}
	}
	///正方向下半部分
	for (int i = 0; i < LENGTH ; i++){
		k = i;
		count = NULL;
		for (int j = LENGTH - 1; j >= i; j--){
			currentchess = Fivechess.chess[k][j];
			k++;
			judge_count(link, &currentchess, &savechess, k - 1, j, grade, &count);
		}
	}
	///反方向上半部分
	for (int i = 0; i < LENGTH ; i++)
	{
		k =  i;
		count = NULL;
		for (int j = 0; j <= i; j++)
		{
			currentchess = Fivechess.chess[k][j];
			k--;
			judge_count(link, &currentchess, &savechess, k + 1, j, grade, &count);
		}
	}
	///正方向上半部分
	for (int i = 0; i < LENGTH; i++)
	{
		k = i;
		count = NULL;
		for (int j = 0; j <= i; j++)
		{
			currentchess = Fivechess.chess[j][k];
			k--;
			judge_count(link, &currentchess, &savechess, j, k + 1, grade, &count);
		}
	}
	//\反下半部分
	for (int i = LENGTH - 1; i >= 4; i--){
		k = i;
		count = NULL;
		for (int j = LENGTH - 1; j >= LENGTH-1 - i; j--){
			currentchess = Fivechess.chess[j][k];
			k--;
			judge_count(link, &currentchess, &savechess, j, k + 1, grade, &count);
		}
	}
	//\正下半部分
	for (int i = 1; i < LENGTH - 4; i++)
	{
		k = i;
		count = NULL;
		for (int j = 0; j < LENGTH - i; j++)
		{
			currentchess = Fivechess.chess[k][j];
			k++;
			judge_count(link, &currentchess, &savechess, k - 1, j, grade, &count);
		}
	}
	
	
	
}
	
LinkNode* ai_go(Link*link)
{
	int x, y; int go_judge = 0;
	LinkNode*linkNode;
	while (go_judge == 0)
	{
		linkNode = find_maxgrade(link);
		linkNode->grade = -1;
		x = linkNode->x;
		y = linkNode->y;
		go_judge = go(x, y);
	}
	
	
	return linkNode;
}

void judge_count(Link*link,int *currentchess,int*savechess,int i,int j,int grade,int *count)
{
	int x, y,z;
	if (*currentchess == NULL&&*savechess == *currentchess)
	{
		*count = 0;
	}
	else if (*currentchess != NULL&&*currentchess == *savechess)
	{
		z = *count;
		z++;
		*count = z;
	}
	else if (*currentchess == NULL&&*savechess != *currentchess)
	{
		y = j;
		x = i;
		if (*count == 1)
		{
			if (*savechess == BLACK)
				grade = 10;
			else
				grade = 9;
			link_append_grade(link, &x, &y, &grade);
		}
		else if (*count == 2)
		{
			if (*savechess == BLACK)
				grade = 100;
			else
				grade = 99;
			link_append_grade(link, &x, &y, &grade);
		}
		else if (*count == 3)
		{
			if (*savechess == BLACK)
				grade = 1000;
			else
				grade = 999;
			link_append_grade(link, &x, &y, &grade);
		}
		else if (*count == 4)
		{
			if (*savechess == BLACK)
				grade = 100000;
			else
				grade = 99999;
			link_append_grade(link, &x, &y, &grade);
		}
		*savechess = *currentchess;
	}
	else
	{
		*count = 1;
		*savechess = *currentchess;
	}
}

