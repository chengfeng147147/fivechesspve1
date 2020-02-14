#include"stack.h"


struct stepStack{
		Step step[MAXCOUNT];
		int stack_lastpointer;
		int stack_firstpointer;
		int count;
}step_stack;
void firstpointer_init(){
	step_stack.stack_firstpointer = 0;
}
void stack_init(){
	step_stack.stack_lastpointer = 0;
	step_stack.stack_firstpointer=0;
	step_stack.count = 0;
}
int stack_push(Step* step){
	if (step_stack.count < MAXCOUNT){
		step_stack.step[step_stack.stack_lastpointer].x = step->x;
		step_stack.step[step_stack.stack_lastpointer].y = step->y;
		step_stack.step[step_stack.stack_lastpointer].colour = step->colour;
		step_stack.stack_lastpointer++;
		step_stack.count++;
		return 1;
	}
	else{
		return 0;
	}
}

int stack_pop(Step* step){
	if (step_stack.count > 0){
		step->x = step_stack.step[step_stack.stack_lastpointer - 1].x;
		step->y = step_stack.step[step_stack.stack_lastpointer - 1].y;
		step->colour = step_stack.step[step_stack.stack_lastpointer - 1].colour;
		step_stack.stack_lastpointer--;
		step_stack.count++;
		return 1;
	}
	else{
		return 0;
	}
}
int stack_firstpop(Step* step){
	if (step_stack.stack_firstpointer < step_stack.count){
		step->x = step_stack.step[step_stack.stack_firstpointer].x;
		step->y = step_stack.step[step_stack.stack_firstpointer].y;
		step->colour = step_stack.step[step_stack.stack_firstpointer].colour;
		step_stack.stack_firstpointer++;
		return 1;
	}
	else{
		return 0;
	}
}


