#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include"fivechesslogic.h"
#include"imageshow.h"
#include<synchapi.h>
#include"stack.h"
#include"bitree.h"


#define PLAY 1
#define REPLAY 2
int main()
{

	int winner;
	int x, y, px, py, rx, ry;//Æå×Ó×ø±ê
	int restart = 1;
	int judgego;
	char player1[10], player2[10];
	char userblack[10], userwhite[10];
	int steps = 1;
	int colour;
	int rcolour;
	int judge,judge1;
	BiTree*bitree;
	rLink *rlink;
	int status = PLAY;
	int end = FALSE;
	int pvp;
	Link* link;
	LinkNode*linkNode;
	link= link_init();
	
		while (1)
		{
			if (restart)
			{
				//end = FALSE;
				initialize();
				stack_initi();
				game_background();
				restart = 0;
				steps = 1;
				get_pattern(&pvp);
				get_username(player1, player2);

			}

			judge = get_mouse(&px, &py);
			switch (judge){
			case 1://Âä×Ó
				if (status == PLAY&&!end){
					change_x_px(&y, &x, &px, &py);
					judgego = go(x, y);
					if (judgego){
						colour = steps % 2 == 0 ? 1 : -1;
						steps++;
						set_chess_pieces(x, y, colour);
					}
				}
				break;
			case 2://»ÚÆå
				if (status == PLAY&&!end){
					int regretx, regrety, regretcolour;
					regret(&regretx, &regrety, &regretcolour);
					regret_imageshow(regretx, regrety);
					steps--;
				}
				break;
			case 4://¸´ÅÌ
				if (status == REPLAY){
					end = get_rlinkfirst(rlink, &rx, &ry, &rcolour);
					if (end){
						set_chess_pieces(rx, ry, rcolour);
					}
					else{
						restart = 1;
						status = PLAY;
						rlink_destruct(rlink);
						bitree_destruct(bitree);
					}
					end = !end;
				}
				else{
					game_background();

					bitree = biTree_init(sizeof(char[10]), char_cmpfunc);
					bitree = read_file(bitree);
					get_username(userblack, userwhite);
					rlink = rlink_init();
					rlink = find_chessmanual(bitree, userblack, userwhite);
					status = REPLAY;
				}
			default:
				break;

			}
			if (status == PLAY&&judge == 1){
				winner = get_winner(x, y);
				if (winner)
				{
					show_winner(winner);
					write_file(player1, player2);
					Sleep(3000);
					restart = 1;
					end = FALSE;
					link_destruct( link);
				}
				else if (winner ==0 && pvp == 50)
				{
					scan_chessboard(link);
					linkNode=ai_go(link);
					colour = steps % 2 == 0 ? 1 : -1;
					steps++;
					set_chess_pieces(linkNode->x, linkNode->y, colour);
					winner = get_winner(linkNode->x, linkNode->y);
					if (winner)
					{
						show_winner(winner);
						write_file(player1, player2);
						Sleep(3000);
						restart = 1;
						end = FALSE;
						link_destruct(link);
					}
				}
			}
		}
	


	system("pause");
	return 0;
}