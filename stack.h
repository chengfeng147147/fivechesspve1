
#define MAXCOUNT 361
typedef struct step{

	int x;
	int y;
	int colour;
}Step;
extern void firstpointer_init();
extern void stack_init();
extern int stack_push(Step* step);
extern int stack_pop(Step* step);
extern int stack_firstpop(Step* step);
