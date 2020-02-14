
#include"link.h"
#include"bitree.h"

#define LENGTH 19
#define WIDTH  19
#define EMPTY 0
#define BLACK 1
#define WHITE -1
#define STRING 10


typedef struct SStep{
	int x;
	int y;
	int color;
};
typedef struct SStep sstep;
typedef struct _LinkfileNode{
	SStep sstep;
	int grade;
	
	struct _LinkfileNode* next;

};
typedef struct _LinkfileNode LinkfileNode;

typedef struct _rLink{
	LinkfileNode* head;
	LinkfileNode* tail;
};
typedef struct _rLink rLink;
extern int* get_data();

extern void initialize();
extern void stack_initi();
extern int go(int x, int y);
extern void regret(int* px,int* py,int* colour);

extern void recover_chess(int*x, int*y, int*colour);

extern int get_winner(int x,int y);

extern void write_file( char* playname, char* playname2);
extern BiTree* read_file(BiTree*bitree);
extern rLink*find_chessmanual(BiTree*bitree, char* userblack, char*userwhite);
extern int rlink_append(rLink*rlink, int*x, int*y, int*color);
extern int get_rlinkfirst(rLink*rlink, int*x, int*y, int*colour);
extern rLink* rlink_init();
extern void rlink_destruct(rLink* rlink);
extern void scan_chessboard(Link*link);
extern LinkNode* ai_go(Link*link);
