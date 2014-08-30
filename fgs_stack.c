#include <stdlib.h>
#include <stdio.h>
#include "fgs_stack.h"

stack * StackInit(int size)
{
	stack * result = malloc(sizeof(stack));
	
	result->top = -1;
	result->maxSize = size;
	
	return result;
}

char StackEmpty(stack * st)
{
	return (st->top < 0) ? 1 : 0;
}

char StackFull(stack * st)
{
/* 	fprintf(stdout, "Top: %d. Max Size: %d.", st->top, st->maxSize-1);
 */	char aux = (st->top >= st->maxSize-1) ? 1 : 0;
/* 	fprintf(stdout, "Result: %d.\n", aux);
 */	return aux;
	
}

char StackDestroy(stack * st)
{
	stacke * element;

	while(!StackEmpty(st))
	{
		element = st->contents->last;
		free(st->contents);
		st->contents = element;
	}
	
	st->contents = NULL;
	st->maxSize = 0;
	st->top = -1;
}

void StackPush(stack * st, stacke * elem)
{
	stacke * element;
	if(!StackFull(st))
	{
		if(verbose)
			fprintf(stdout, "--StackPush-- Correctly pushed value %d.\n", elem->value.literalI);
		element = st->contents;
		st->contents = malloc(sizeof(stacke));
		st->contents->value.literalI = elem->value.literalI;
		st->contents->last = element;
		st->top++;
	}
}

stacke * StackPop(stack * st)
{
	stacke * element;
	if(!StackEmpty(st))
	{
		element = st->contents;
		st->contents = element->last;
		st->top--;
		if(verbose)
			fprintf(stdout, "--StackPush-- Correctly poped value %d.\n", element->value.literalI);
		return element;
	}
}