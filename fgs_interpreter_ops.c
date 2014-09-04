#include <stdio.h>
#include <stdlib.h>
#include "fgs_stack.h"
#include "fgs.h"

#ifndef VERBOSE
#define VERBOSE
char verbose;
#endif

#ifndef DEBUGVERBOSE
#define DEBUGVERBOSE
char debug;
#endif


void memError(char * funct)
{
	printf("--%s-- Cannot allocate memory. Exiting...\n", funct);
}

void pushi(stack * st, int value)
{
	stacke * aux1 = malloc(sizeof(stacke));
	
	if(!aux1)
	{
		memError("pushi");
	}
		
	aux1->type = 0;
	aux1->value.literalI = value;
	StackPushI(st, aux1);
	free(aux1);
}

void pushf(stack * st, float value)
{
	stacke * aux1 = malloc(sizeof(stacke));
	
	if(!aux1)
	{
		memError("pushf");
	}
	
	aux1->type = 1;
	aux1->value.literalF = value;
	StackPushF(st, aux1);
	free(aux1);
}

void pushs(stack * st, char * value)
{
	stacke * aux1 = malloc(sizeof(stacke));
	
	if(!aux1)
	{
		memError("pushs");
	}
	
	aux1->type = 2;
	aux1->value.literalS = value;
	StackPushS(st, aux1);
	free(aux1);
}

void pushvar(stack * st, var variable)
{
	if(variable.type == 0)
	{
		pushi(st, variable.value.literalI);
	}
	else if(variable.type == 1)
	{
		pushf(st, variable.value.literalF);
	}
	else if(variable.type == 2)
	{
		pushs(st, variable.value.literalS);
	}
	else
	{
		printf("Unknown variable type, cannot push.\n");
		exit(4);
	}
}

void popvar(frame * f, stack * st, unsigned char variable)
{
	stacke * aux = malloc(sizeof(stacke));
	int stack_type = StackType(st);
	
	if(stack_type == 0)
	{
		StackPopI(st, aux);
		setVariableI(f, variable, aux->value.literalI);
	}
	else if(stack_type == 1)
	{
		StackPopF(st, aux);
		setVariableF(f, variable, aux->value.literalF); 
	}
	else if(stack_type == 2)
	{
		StackPopS(st, aux);
		setVariableS(f, variable, aux->value.literalS);
	}
	else if(stack_type == -1)
	{
		printf("Stack is empty.");
	}
	else
	{
		printf("Unknown variable type, cannot pull.\n");
		free(aux);
		exit(4);
	}
	
	free(aux);
}

void operate(stack * st, int type)
{
	stacke * aux1, * aux2;
	char * resultString;
	
	aux1 = malloc(sizeof(stacke));	
	aux2 = malloc(sizeof(stacke));

	if(aux1 == NULL || aux2 == NULL)
	{
		memError("arithmetic operation");
	}
	
	StackPopI(st, aux1);
	StackPopI(st, aux2);
	
	switch(type)
	{
		case 0:
			aux2->value.literalI += aux1->value.literalI;
			break;
		case 1:
			aux2->value.literalI -= aux1->value.literalI;
			break;
		case 2:
			aux2->value.literalI *= aux1->value.literalI;
			break;
		case 3:
			aux2->value.literalI /= aux1->value.literalI;
			break;
		case 4:
			aux2->value.literalF += aux1->value.literalF;
			break;
		case 5:
			aux2->value.literalF -= aux1->value.literalF;
			break;
		case 6:
			aux2->value.literalF *= aux1->value.literalF;
			break;
		case 7:
			aux2->value.literalF /= aux1->value.literalF;
			break;
		case 8:
			resultString = malloc(strlen(aux2->value.literalS)+strlen(aux1->value.literalS)+1);
			strcpy(resultString, aux2->value.literalS);
			strcat(resultString, aux1->value.literalS);
			free(aux2->value.literalS);
			aux2->value.literalS = resultString;
			break;
	}
	
	StackPushI(st, aux2);

	free(aux1);
	free(aux2);
}

void addi(stack * st)
{
	operate(st, 0);
}

void subi(stack * st)
{
	operate(st, 1);
}

void muli(stack * st)
{
	operate(st, 2);
}

void divi(stack * st)
{
	operate(st, 3);
}

void addf(stack * st)
{
	operate(st, 4);
}

void subf(stack * st)
{
	operate(st, 5);
}

void mulf(stack * st)
{
	operate(st, 6);
}

void divf(stack * st)
{
	operate(st, 7);
}

void adds(stack *st)
{
	operate(st, 8);
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

	if(debug)
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
			printf("UNIMPLEMENTED comparer for strings\n");
			exit(6);
		}
	}
	else
	{
		printf("UNIMPLEMENTED types differ\n");
		exit(6);
	}

	free(aux1);
	free(aux2);	

	return result;
}

