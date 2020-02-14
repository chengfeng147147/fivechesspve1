
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include"fivechesslogic.h"
#include"imageshow.h"
#include<synchapi.h>
#include"stack.h"
#include"bitree.h"
int main()
{   
	int winner;
	int colour;
	int steps = 1;
	int go_judge=NULL;
	Link*link;
	link=link_init();
	LinkNode*linkNode;
	initialize();
	stack_initi();
	game_background();
	go(2, 3);
	colour = steps % 2 == 0 ? 1 : -1;
	steps++;
	set_chess_pieces(2, 3, colour);

	scan_chessboard(link);
	linkNode=ai_go(link);
	colour = steps % 2 == 0 ? 1 : -1;
	steps++;
	set_chess_pieces(linkNode->x, linkNode->y, colour);

	go(1, 2);
	colour = steps % 2 == 0 ? 1 : -1;
	steps++;
	set_chess_pieces(1, 2, colour);

	scan_chessboard(link);
	linkNode = ai_go(link);
	colour = steps % 2 == 0 ? 1 : -1;
	steps++;
	set_chess_pieces(linkNode->x, linkNode->y, colour);

	
	


	link_destruct(link);
	while (1){}
	return 0;
}