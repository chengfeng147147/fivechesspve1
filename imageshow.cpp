#include"imageshow.h"
#include<graphics.h>
#include <conio.h>
#define X 10
#define MAX_X 460
#define Y 50
#define MAX_Y 500
#define N 19
#define D 25

void game_background()
{
	
	
	
	initgraph(1200, 800);
	setfillcolor(YELLOW);
	solidrectangle(0,0,1200,800);

	setlinecolor(BLACK);//ª≠∆Â≈Ã

	for (int y= Y; y <= MAX_Y; y += 25)
	{
		line(X, y, MAX_X, y);
	}
	for (int x = X; x <=MAX_X ; x += 25)
	{
		line(x,Y , x,MAX_Y );
	}
	

	settextstyle(50, 0, _T("∑¬ÀŒ"));
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	outtextxy(475, 230, _T("ŒÂ◊”∆Â"));

	setlinestyle(PS_SOLID, 1);
	setlinecolor(BLACK);
	fillrectangle(700, 100, 900, 175);
	settextstyle(50, 0, _T("∑¬ÀŒ"));
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(720, 120, _T("ª⁄∆Â"));

	setlinestyle(PS_SOLID, 1);
	setlinecolor(BLACK);
	fillrectangle(700, 200, 900, 275);
	settextstyle(50, 0, _T("∑¬ÀŒ"));
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(720, 220, _T("µ•»À"));



	setlinestyle(PS_SOLID, 1);
	setlinecolor(BLACK);
	fillrectangle(700, 300, 900, 375);
	settextstyle(50, 0, _T("∑¬ÀŒ"));
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(720, 320, _T("≤È’“"));
}


void set_chess_pieces(int x,int y,int colour)
{
	int pixel_x, pixel_y;
	pixel_x = y * 25 + X;
	pixel_y =x * 25 + Y;
	if (colour == 1)
	{
		setlinestyle(PS_SOLID, 1);
		setlinecolor(BLACK);
		setfillcolor(BLACK);
		fillcircle(pixel_x, pixel_y, 10);
	}
	else if (colour==-1)
	{
		setlinestyle(PS_SOLID, 1);
		setlinecolor(WHITE);
		setfillcolor(WHITE);
		fillcircle(pixel_x, pixel_y, 10);
	}
	else{
		return;
	}
}
void show_winner(int winner)
{
	if (winner == 1)

	{
		settextstyle(50, 0, _T("∑¬ÀŒ"));
		setbkmode(TRANSPARENT);
		settextcolor(RED);
		outtextxy(MAX_X / 2, MAX_Y / 2, _T("∫⁄∆Â §"));
	}
	else if(winner==-1){
		settextstyle(50, 0, _T("∑¬ÀŒ"));
		setbkmode(TRANSPARENT);
		settextcolor(RED);
		outtextxy(MAX_X / 2, MAX_Y / 2, _T("∞◊∆Â §"));

	}
}

void regret_imageshow(int x,int y)
{
	int radius = 10;
	int pixel_x, pixel_y;
	int colour;
	pixel_x = x * 25 + X;
	pixel_y = y * 25 + Y;
	
	setlinestyle(PS_SOLID, 1);
	setlinecolor(YELLOW);
	setfillcolor(YELLOW);
	fillcircle(pixel_x, pixel_y, radius);
	setlinecolor(BLACK);
	if (pixel_x == X&&pixel_y<MAX_Y&&pixel_y>Y)
	{
		line(pixel_x, pixel_y - D / 2, pixel_x, pixel_y + D / 2);
		line(pixel_x, pixel_y, pixel_x + D / 2, pixel_y);
	}
	else if (pixel_x == MAX_X&&pixel_y<MAX_Y&&pixel_y>Y)
	{
		line(pixel_x, pixel_y - D / 2, pixel_x, pixel_y + D / 2);
		line(pixel_x, pixel_y, pixel_x , pixel_y);
	}
	else if (pixel_y == MAX_Y&&pixel_x<MAX_X&&pixel_x>X)
	{
		line(pixel_x, pixel_y - D / 2, pixel_x, pixel_y);
		line(pixel_x - D / 2, pixel_y, pixel_x + D / 2, pixel_y);
	}
	else if (pixel_y == Y&&pixel_x<MAX_X&&pixel_x>X)
	{
		line(pixel_x, pixel_y, pixel_x, pixel_y + D / 2);
		line(pixel_x - D / 2, pixel_y, pixel_x + D / 2, pixel_y);
	}
	else if (pixel_x == X&&pixel_y == Y)
	{
		line(pixel_x, pixel_y, pixel_x, pixel_y + D / 2);
		line(pixel_x, pixel_y, pixel_x + D / 2, pixel_y);
	}
	else if (pixel_x == X&&pixel_y == MAX_Y)
	{
		line(pixel_x, pixel_y - D / 2, pixel_x, pixel_y);
		line(pixel_x, pixel_y, pixel_x + D / 2, pixel_y);
	}
	else if (pixel_x == MAX_X&&pixel_y == Y)
	{
		line(pixel_x, pixel_y, pixel_x, pixel_y + D / 2);
		line(pixel_x - D / 2, pixel_y, pixel_x, pixel_y);
	}
	else if (pixel_x == MAX_X&&pixel_y == MAX_Y)
	{
		line(pixel_x, pixel_y - D / 2, pixel_x, pixel_y);
		line(pixel_x - D / 2, pixel_y, pixel_x, pixel_y);
	}
	else
	{
		line(pixel_x, pixel_y - D / 2, pixel_x, pixel_y + D / 2);
		line(pixel_x - D / 2, pixel_y, pixel_x + D / 2, pixel_y);

	}
	
}

void get_username(char* userblack, char* userwhite ){
	InputBox((LPTSTR)userblack, 10, _T("userblack "));
	InputBox((LPTSTR)userwhite, 10, _T("userwhite"));
}
void get_pattern( int* pvp){
	
	InputBox((LPTSTR)pvp, 10, _T("pvp ‰»Î1£¨pve≥ˆ»Î2"));
}
void get_timeshow(int* time){
	InputBox((LPTSTR)time, 10, _T("time "));
}

int get_mouse(int *px,int*py)
{
	MOUSEMSG m;
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			break;
		}
	}
	if (m.uMsg == WM_LBUTTONDOWN&&m.x >= X&&m.x <= MAX_X&&m.y >= Y&&m.y <= MAX_Y)
	{
		*px = m.x;
		*py = m.y;
		return 1;
	}
	if (m.uMsg == WM_LBUTTONDOWN&&m.x <= 900 && m.x >= 700 && m.y <= 175 && m.y >= 100)
	{
		return 2;
	}
	if (m.uMsg == WM_LBUTTONDOWN&&m.x <= 900 && m.x >= 700 && m.y <= 275 && m.y >= 200)
	{
		return 3;
	}
	if (m.uMsg == WM_LBUTTONDOWN&&m.x <= 900 && m.x >= 700 && m.y <= 375 && m.y >= 300)
	{
		return 4;
	}
	else{
		return 0;
	}

}
void change_x_px(int *x,int *y,int* px,int*py)
{
	int i;
	int j;
	for (i = 0; i < N;i++){
		for ( j = 0; j < N; j++)
		{
			if (abs(*py - i * 25 - Y) < 12 && abs(*px - j * 25 - X) < 12)
			{
				*x = j;
				*y = i;
			}
		}

	}
}