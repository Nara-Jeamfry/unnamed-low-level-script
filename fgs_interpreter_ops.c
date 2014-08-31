#include <stdio.h>
#include <stdlib.h>
#include "fgs_stack.h"

#ifndef VERBOSE
#define VERBOSE
char verbose;
#endif

void memError(char * funct)
{
	printf("--%s-- Cannot allocate memory. Exiting...\n", funct);
	exit(3);
}

void addi(stack * st)
{
	stacke * aux1, * aux2;

	aux1 = malloc(sizeof(stacke));	
	aux2 = malloc(sizeof(stacke));

	if(aux1 == NULL || aux2 == NULL)
	{
		memError("addi");
	}

	StackPopI(st, aux1);
	StackPopI(st, aux2);
	aux1->value.literalI += aux2->value.literalI;

	StackPushI(st, aux1);

	free(aux1);
	free(aux2);
}

void addf(stack * st)
{
	stacke * aux1, * aux2;

	aux1 = malloc(sizeof(stacke));
	aux2 = malloc(sizeof(stacke));

	if(aux1 == NULL || aux2 == NULL)
	{
		memError("addi");
	}

	StackPopF(st, aux1);
	StackPopF(st, aux2);
	aux1->value.literalF += aux2->value.literalF;

	StackPushF(st, aux1);

	free(aux1);
	free(aux2);
}

void subi(stack * st)
{
	stacke * aux1, * aux2, * auxres;

	aux1 = malloc(sizeof(stacke));
	aux2 = malloc(sizeof(stacke));

	if(aux1 == NULL || aux2 == NULL)
	{
		memError("addi");
	}

	StackPopI(st, aux1);
	StackPopI(st, aux2);
	aux2->value.literalI -= aux1->value.literalI;

	StackPushI(st, aux2);

	free(aux1);
	free(aux2);
}

int lti(stack *st)
{
	return comp_generic(st, 0);
}

int lei(stack *st)
{
	return comp_generic(st, 1);
}

int gti(stack *st)
{
	return comp_generic(st, 2);
}

int gei(stack *st)
{
	return comp_generic(st, 3);
}

int eq(stack *st)
{
	return comp_generic(st, 4);
}

int neq(stack *st)
{
	return comp_generic(st, 5);
}
/* this shouldn't be called standalone. receives int for type and checks the type of operation. */
/* lti: 0;
   lei: 1;
   gti: 2;
   gei: 3;
   eq:  4;
   neq: 5; */
int comp_generic(stack * st, int type)
{
	stacke * aux1, * aux2;
	int result;

	aux1 = malloc(sizeof(stacke));
	aux2 = malloc(sizeof(stacke));

	if(aux1 == NULL || aux2 == NULL)
	{
		memError("addi");
	}

	if(verbose)
		fprintf(stdout, "--debugFunction-- Comparing %d and %d.\n", aux2->value.literalI, aux1->value.literalI);

	StackPopI(st, aux1);
	StackPopI(st, aux2);
	if(aux2->type == aux1->type)
	{
		if(aux2->type == 0)
		{
			switch(type)
			{
				case 0: /* lti */
					if(aux2->value.literalI < aux1->value.literalI)
						result = 1;
					else
						result = 3;
					break;
				case 1: /* lei */
					if(aux2->value.literalI <= aux1->value.literalI)
						result = 1;
					else
						result = 3;
					break;
				case 2: /* gti */
					if(aux2->value.literalI > aux1->value.literalI)
						result = 1;
					else
						result = 3;
					break;
				case 3: /* gei */
					if(aux2->value.literalI >= aux1->value.literalI)
						result = 1;
					else
						result = 3;
					break;
				case 4: /* eq */
					if(aux2->value.literalI == aux1->value.literalI)
						result = 1;
					else
						result = 3;
					break;
				case 5: /* neq */
					if(aux2->value.literalI != aux1->value.literalI)
						result = 1;
					else
						result = 3;
					break;
			}
		}
		else if(aux2->type == 1)
		{
			switch(type)
			{
				case 0: /* lti */
					if(aux2->value.literalF < aux1->value.literalF)
						result = 1;
					else
						result = 3;
					break;
				case 1: /* lei */
					if(aux2->value.literalF <= aux1->value.literalF)
						result = 1;
					else
						result = 3;
					break;
				case 2: /* gti */
					if(aux2->value.literalF > aux1->value.literalF)
						result = 1;
					else
						result = 3;
					break;
				case 3: /* gei */
					if(aux2->value.literalF >= aux1->value.literalF)
						result = 1;
					else
						result = 3;
					break;
				case 4: /* eq */
					if(aux2->value.literalF == aux1->value.literalF)
						result = 1;
					else
						result = 3;
					break;
				case 5: /* neq */
					if(aux2->value.literalF != aux1->value.literalF)
						result = 1;
					else
						result = 3;
					break;
			}
		}
		else if(aux2->type == 2)
		{
			printf("UNIMPLEMENTED");
			exit(6);
		}
	}
	else
	{
		printf("UNIMPLEMENTED");
		exit(6);
	}

	free(aux1);
	free(aux2);	

	return result;
}

