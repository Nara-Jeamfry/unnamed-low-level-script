#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fgs.h"

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
		
		
		last_function->value = actual;
		last_function->next = malloc(sizeof(functions));
		last_function = last_function->next;
		actual = malloc(sizeof(function));
	}
	
	for(i=0; i<function_count; i++)
	{
		op = fi[offset++];
		actual = findFunction(op, result);
		fprintf(stdout, "Code for function %s:\n\n", actual->name);
		while(op != 0)
		{
			op = fi[offset++];
			switch(op)
			{
				case BYT_GOTO:
					fprintf(stdout, "%d: Goto: %d\n", offset-2, fi[offset++]);
					break;
				case BYT_PUSHVAR:
					fprintf(stdout, "%d: Push: %d\n", offset-2, fi[offset++]);
					break;
				case BYT_PUSHINT:
					fprintf(stdout, "%d: Push: %d\n", offset-2, fi[offset++]);
				case BYT_EQ:
				case BYT_NEQ:
				case BYT_LTI:
				case BYT_GEI:
				default:
					fprintf(stdout, "%d: Unknown op %d\n", offset-1, op);
			}
		}
		
		fprintf(stdout, "Function %d ended at offset %d\n", i+1, offset-1);
		
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
	
	file = fopen("output.byt", "rb");
	
	return file;
}

int main()
{
	fprintf(stdout, "Benvingut a l'intèrpret de FastGameScript!\n\nIntentarem llegir el codi de l'arxiu \"output.fgs\"!\n");
	
	FILE * file = open_file("output.byt");
	
	if(file==NULL)
	{
		fprintf(stdout, "Error al llegir caca pipi :( \n");
		exit(1);
	}
	
	read_file(parse_file(file));
	
	fclose(file);
}