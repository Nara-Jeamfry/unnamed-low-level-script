#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fgs.h"
#include "prac3.h"

functions * read_file(char * fi)
{
	char header[13] = { 'g', 'a', 'm', 'e', '_', 's', 'c', 'r', 'i', 'p', 't', 3, 0 };
	if(memcmp(fi,header, 13))
	{	
		fprintf(stdout, "Hey! L'arxiu no és correcte! :(\n");
		return NULL;
	}
	
	int offset = 13, i, j;
	int function_count, type_count, var_count;
	char op;
	function *actual = malloc(sizeof(function));
	function *aux;
	functions * last_function;
	functions * result = last_function = malloc(sizeof(functions));
	type * types = NULL, *auxtype = NULL;
	
	function_count = fi[offset++];
	fprintf(stdout, "N. de funcions: %d\n", function_count);
	
	for(i=0; i<function_count; i++)
	{
		fprintf(stdout, "Funcio %d\n", i+1);
		actual->name = readStringBytes(&offset, fi);
		type_count = fi[offset++];
		actual->type_count = type_count;
		
		for(j=0; j<type_count; j++)
		{
			types = malloc(sizeof(type));
			if(auxtype)
			{
				auxtype->next = types;
			}
			types->name = readStringBytes(&offset, fi);
			fprintf(stdout, "Type %s\n", types->name);
			auxtype = types;
		}
		
		actual->types = types;
		types = NULL;
		
		actual->id = fi[offset++];
		fprintf(stdout, "Funcio %d: %s\n", actual->id, actual->name);
		
		actual->var_count = 7;
		
		
		last_function->value = actual;
		last_function->next = malloc(sizeof(functions));
		last_function = last_function->next;
		actual = malloc(sizeof(function));
	}
	
	int line = 0;
	
	for(i=0; i<function_count; i++)
	{
		line = offset;
		op = fi[offset++];
		actual = findFunction(op, result);
		actual->start = fi+offset;
		actual->offset = offset-2-line;
		fprintf(stdout, "Code for function %s, starting at %X:\n\n", actual->name, (unsigned char)actual->offset);
		while(op != 0)
		{
			op = fi[offset++];
			switch(op)
			{
				case BYT_GOTO:
					fprintf(stdout, "%X: goto %X\n", offset-3-line, fi[offset++]);
					break;
				case BYT_PUSHVAR:
					fprintf(stdout, "%X: pushvar %d\n", offset-3-line, fi[offset++]);
					break;
				case BYT_PUSHI:
					fprintf(stdout, "%X: pushi %d\n", offset-3-line, *(int *)&fi[offset++]);
					offset+=3;
					break;
				case BYT_PUSHF:
					fprintf(stdout, "%X: pushf %f\n", offset-3-line, *(float *)&fi[offset++]);
					offset+=3;
					break;
				case BYT_PUSHS:
					fprintf(stdout, "%X: pushs \"%s\"\n", offset-3-line, readStringBytes(&offset, fi));
					break;
				case BYT_POPVAR:
					fprintf(stdout, "%X: pop %d\n", offset-3-line, fi[offset++]);
					break;
				case BYT_I2S:
					fprintf(stdout, "%X: i2s\n", offset-3-line);
					break;
				case BYT_ADDI:
					fprintf(stdout, "%X: addi\n", offset-3-line);
					break;
				case BYT_SUBI:
					fprintf(stdout, "%X: subi\n", offset-3-line);
					break;
				case BYT_MULI:
					fprintf(stdout, "%X: muli\n", offset-3-line);
					break;
				case BYT_DIVI:
					fprintf(stdout, "%X: divi\n", offset-3-line);
					break;
				case BYT_ADDF:
					fprintf(stdout, "%X: addf\n", offset-3-line);
					break;
				case BYT_SUBF:
					fprintf(stdout, "%X: subf\n", offset-3-line);
					break;
				case BYT_MULF:
					fprintf(stdout, "%X: mulf\n", offset-3-line);
					break;
				case BYT_DIVF:
					fprintf(stdout, "%X: divf\n", offset-3-line);
					break;
				case BYT_ADDS:
					fprintf(stdout, "%X: adds\n", offset-3-line);
					break;
				case BYT_HALT:
					fprintf(stdout, "%X: return\n", offset-3-line);
					break;
				case BYT_EQ:
					fprintf(stdout, "%X: eq\n", offset-3-line);
					break;
				case BYT_NEQ:
					fprintf(stdout, "%X: neq\n", offset-3-line);
					break;
				case BYT_LTI:
					fprintf(stdout, "%X: lti\n", offset-3-line);
					break;
				case BYT_LEI:
					fprintf(stdout, "%X: lei\n", offset-3-line);
					break;
				case BYT_GTI:
					fprintf(stdout, "%X: gti\n", offset-3-line);
					break;
				case BYT_GEI:
					fprintf(stdout, "%X: gei\n", offset-3-line);
					break;
				default:
					fprintf(stdout, "%X: Unknown op %X\n", offset-2-line, op);
			}
		}
		
		fprintf(stdout, "Function %d ended at offset %X\n", i+1, offset-1);
		
	}
	
	fprintf(stdout, "Hey! Estic interpretant l'arxiu! :)\n");
	
	return result;
	
}

function *findFunction(char id, functions *list)
{
	char found = 0;
	while(list && !found)
	{
		if(list->value->id == id)
		{
			found = 1;
			return list->value;
		}
		list = list->next;
	}
	return NULL;
}

function *findFunctionByName(char * name, functions *list)
{
	char found = 0;
	while(list && !found)
	{
		if(!strcmp(list->value->name, name))
		{
			found = 1;
			return list->value;
		}
		list = list->next;
	}
	return NULL;
}

void * runFunction(frame *actualFrame)
{
	char * op = actualFrame->func->start;
	char offset = actualFrame->func->offset;
	
	stacke * aux1, * aux2, * auxres;
	var * auxvar;
	
	while(op[actualFrame->pc] != 0)
	{
		switch(op[actualFrame->pc])
		{
			case BYT_GOTO:
				actualFrame->pc = op[(actualFrame->pc)+1];
				break;
			case BYT_PUSHI:
				aux1 = malloc(sizeof(stacke));
				aux1->type = 0;
				aux1->value.literalI = *(int *)&(op[(actualFrame->pc)+1]);
				StackPush(actualFrame->datastack, aux1);
				actualFrame->pc = (actualFrame->pc)+5;
				break;
			case BYT_PUSHF:
				aux1 = malloc(sizeof(stacke));
				aux1->type = 0;
				aux1->value.literalF = *(float *)&(op[(actualFrame->pc)+1]);
				StackPush(actualFrame->datastack, aux1);
				actualFrame->pc = (actualFrame->pc)+5;
				break;
			case BYT_PUSHVAR:
				auxvar = findVariable(actualFrame->variables, op[(actualFrame->pc)+1]);
				aux1 = malloc(sizeof(stacke));
				aux1->type = 0;
				aux1->value.literalI = auxvar->value.literalI;
				StackPush(actualFrame->datastack, aux1);
				actualFrame->pc = (actualFrame->pc)+2;
				break;
			case BYT_ADDI:
				aux1 = StackPop(actualFrame->datastack);
				aux2 = StackPop(actualFrame->datastack);
				aux1->value.literalI += aux2->value.literalI;
				StackPush(actualFrame->datastack, aux1);
				actualFrame->pc = (actualFrame->pc)+1;
				break;
			case BYT_SUBI:
				aux1 = StackPop(actualFrame->datastack);
				aux2 = StackPop(actualFrame->datastack);
				aux2->value.literalI -= aux1->value.literalI;
				StackPush(actualFrame->datastack, aux2);
				actualFrame->pc = (actualFrame->pc)+1;
				break;
			case BYT_LTI:
				aux1 = StackPop(actualFrame->datastack);
				aux2 = StackPop(actualFrame->datastack);
				if(aux2->value.literalI < aux1->value.literalI)
				{
					actualFrame->pc = (actualFrame->pc)+1;
				}
				else
				{
					actualFrame->pc = (actualFrame->pc)+3;
				}
				break;
			case BYT_POPVAR:
				auxvar = findVariable(actualFrame->variables, op[(actualFrame->pc)+1]);
				aux1 = StackPop(actualFrame->datastack);
				auxvar->value.literalI = aux1->value.literalI;
				actualFrame->pc = (actualFrame->pc)+2;
				break;
			default:
				actualFrame->pc = (actualFrame->pc)+1;
		}
	}
	
	return NULL;
}

void * debugFunction(frame *actualFrame)
{
	char * op = actualFrame->func->start;
	char offset = actualFrame->func->offset;
	
	stacke * aux1, * aux2, * auxres;
	var * auxvar;
	
	while(op[actualFrame->pc] != 0)
	{
		fprintf(stdout, "--debugFunction-- Now at op %X.\n", actualFrame->pc);
		switch(op[actualFrame->pc])
		{
			case BYT_GOTO:
				print("--debugFunction-- Found goto\n");
				actualFrame->pc = op[(actualFrame->pc)+1];
				break;
			case BYT_PUSHI:
				print("--debugFunction-- Found pushi\n");
				aux1 = malloc(sizeof(stacke));
				aux1->type = 0;
				aux1->value.literalI = *(int *)&(op[(actualFrame->pc)+1]);
				StackPush(actualFrame->datastack, aux1);
				actualFrame->pc = (actualFrame->pc)+5;
				break;
			case BYT_PUSHF:
				print("--debugFunction-- Found pushf\n");
				aux1 = malloc(sizeof(stacke));
				aux1->type = 0;
				aux1->value.literalF = *(float *)&(op[(actualFrame->pc)+1]);
				StackPush(actualFrame->datastack, aux1);
				actualFrame->pc = (actualFrame->pc)+5;
				break;
			case BYT_PUSHVAR:
				print("--debugFunction-- Found pushvar\n");
				auxvar = findVariable(actualFrame->variables, op[(actualFrame->pc)+1]);
				aux1 = malloc(sizeof(stacke));
				aux1->type = 0;
				aux1->value.literalI = auxvar->value.literalI;
				StackPush(actualFrame->datastack, aux1);
				actualFrame->pc = (actualFrame->pc)+2;
				break;
			case BYT_ADDI:
				print("--debugFunction-- Found addi\n");
				aux1 = StackPop(actualFrame->datastack);
				aux2 = StackPop(actualFrame->datastack);
				aux1->value.literalI += aux2->value.literalI;
				StackPush(actualFrame->datastack, aux1);
				actualFrame->pc = (actualFrame->pc)+1;
				break;
			case BYT_SUBI:
				print("--debugFunction-- Found subi\n");
				aux1 = StackPop(actualFrame->datastack);
				aux2 = StackPop(actualFrame->datastack);
				aux2->value.literalI -= aux1->value.literalI;
				StackPush(actualFrame->datastack, aux2);
				actualFrame->pc = (actualFrame->pc)+1;
				break;
			case BYT_LTI:
				print("--debugFunction-- Found lti\n");
				aux1 = StackPop(actualFrame->datastack);
				aux2 = StackPop(actualFrame->datastack);
				fprintf(stdout, "--debugFunction-- Comparing %d and %d.\n", aux2->value.literalI, aux1->value.literalI);
				if(aux2->value.literalI < aux1->value.literalI)
				{
					print("--debugFunction-- It is less!\n");
					actualFrame->pc = (actualFrame->pc)+1;
				}
				else
				{
					print("--debugFunction-- It is NOT less!\n");
					actualFrame->pc = (actualFrame->pc)+3;
				}
				break;
			case BYT_POPVAR:
				print("--debugFunction-- Found popvar\n");
				auxvar = findVariable(actualFrame->variables, op[(actualFrame->pc)+1]);
				aux1 = StackPop(actualFrame->datastack);
				auxvar->value.literalI = aux1->value.literalI;
				actualFrame->pc = (actualFrame->pc)+2;
				break;
			default:
				print("--debugFunction-- Found unknown op\n");
				actualFrame->pc = (actualFrame->pc)+1;
		}
		printStatus(actualFrame);
	}
	fprintf(stdout, "--debugFunction-- Now at op %X.\n", actualFrame->pc);
	print("--debugFunction-- Found HALT!\n");
	
	return NULL;
}

void printStatus(frame * fr)
{
	fprintf(stdout, "Actual status: %d elems on stack.\n\n", fr->datastack->top+1);
}

frame * createFrame(char * function)
{
	frame * result = malloc(sizeof(frame));
	int i;
	var * aux, * lastaux;
	
	print("--createFrame-- Allocating memory...\n");
	result->variables = NULL;
	
	if(globalFunctions == NULL)
	{
		print("--createFrame-- WELL THIS IS EMBARRASSING WE DO NOT HAVE FUNCTIONS THX\n");
		return NULL;
	}
	else
	{
		print("--createFrame-- We have functions! Let's search for it.\n");
		result->func = findFunctionByName(function, globalFunctions);
		if(result->func == NULL)
			print("--createFrame-- Woops. Didn't found that one.\n");
		else
			print("--createFrame-- FOUND!\n");
	}
	
	result->pc = result->func->offset+1;
	
	fprintf(stdout, "--createFrame-- Gonna allocate all the variables (%d).\n", result->func->var_count);
	
	for(i=0; i<result->func->var_count; i++)
	{
		lastaux = malloc(sizeof(var));
	
		lastaux->id = i+1;
	
		if(result->variables == NULL)
		{
			print("--createFrame-- First variable! Added.\n");
			result->variables = lastaux;
			aux = lastaux;
		}
		else
		{
			fprintf(stdout, "--createFrame-- Added variable %d.\n", i+1);
			aux->next = lastaux;
			aux = lastaux;
		}
	}
	
	result->datastack = StackInit(128);
	print("--createFrame-- Stack reserved!\n");
	
	return result;
}

var *findVariable(var * variables, unsigned char id)
{
	fprintf(stdout, "--findVariable-- Searching var %d.\n", id);
	char found = 0;
	var * aux = variables;
	while(aux && !found)
	{
		if(aux->id == id)
		{
			print("Found :)\n");
			found = 1;
			return aux;
		}
		aux = aux->next;
	}
	print("--findVariable-- Not found :(\n");
	return NULL;
}

char *readStringBytes(int *offset, char * text)
{
	char length = *(text+*offset);
	
	(*offset)++;
	char *result = malloc(sizeof(char)*length + 1);
	
	memcpy(result, text+*offset, length);
	
	result[length]='\0';
	
	(*offset)+=length;
	
	return result;
}

char * parse_file(FILE * fi)
{
	int lSize;
	char * result;
	
	fseek(fi, 0, SEEK_END);
	lSize = ftell(fi);
	rewind(fi);
	
	result = malloc(sizeof(char)*lSize);
	int i = fread(result, 1, lSize, fi);
	if(result==NULL)
	{
		fprintf(stdout, "HEHEAIHEIAOEH");
	}
	if(i!=lSize)
	{
		fprintf(stdout, "aoisjoaija");
	}
	
	return result;
}

FILE * open_file(char * name)
{
	
	FILE * file;
	
	file = fopen(name, "rb");
	
	return file;
}

void print(char * text)
{
	fprintf(stdout, text);
}

void openFile(char * name)
{
	FILE * source = fopen(name, "r");
	char * pch;
	
	if(!source)
	{
		printf("couldn't open file \"%s\" for reading\n", name);
		exit(1);
	}
	
	pch = strchr(name, '.');
	char * output = malloc(sizeof(char) * (pch-name+1+5));
	strcpy(output, name);
	pch = strchr(output, '.');
	pch[1] = 'b';
	pch[2] = 'f';
	pch[3] = 'g';
	pch[4] = 's';
	pch[5] = '\0';
	
	fprintf(stdout, "--openFile-- Trying to save on \"%s\"\n", output);
	
	parseFile(source, output);
}

int main()
{
	fprintf(stdout, "Benvingut a l'intèrpret de FastGameScript!\n\n");
	
	char * name = "example_fibonacci_complexe.fgs";
	
	fprintf(stdout, "Intentarem llegir el codi de l'arxiu \"%s\"!\n", name);
	
	openFile(name);
	
	
	FILE * file = open_file("example_fibonacci_complexe.bfgs");
	frame * basicFrame;
	var * input;
	
	if(file==NULL)
	{
		fprintf(stdout, "Error al llegir caca pipi :( \n");
		exit(1);
	}
	
	char answ;
	scanf("%c\n", &answ);
	
	
	while(answ != 'n')
	{
		print("Reading file...\n");
		globalFunctions = read_file(parse_file(file));
		
		print("Closing the file...\n");
		
		print("Now, we're gonna try to load fibonacci function\n");
		basicFrame = createFrame("fibonacci");
		
		print("Selecting manually the input var for fibonacci\n");
		input = findVariable(basicFrame->variables, 1);
		input->type = 0;
		input->value.literalI = 70;
		
		fprintf(stdout, "Now var n is: %d\n", basicFrame->variables->value);
		
		print("HERE WE GO!\n");
		runFunction(basicFrame);
	
		fprintf(stdout, "Fibonacci number on %dth position is: %d\n", findVariable(basicFrame->variables, 1)->value.literalI, findVariable(basicFrame->variables, 4)->value.literalI);
		
		scanf("%c\n", &answ);
	}
	fclose(file);
}