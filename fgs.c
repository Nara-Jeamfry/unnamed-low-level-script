#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fgs.h"


char *readStringBytes(int *offset, char * text);

functions * read_file(char * fi)
{
	char header[13] = { 'g', 'a', 'm', 'e', '_', 's', 'c', 'r', 'i', 'p', 't', 3, 0 };
	if(memcmp(fi,header, 13))
	{	
		fprintf(stdout, "Hey! L'arxiu no és correcte! :(\n");
		return NULL;
	}
	
	int offset = 13, i;
	int function_count, type_count, var_count;
	function *actual = malloc(sizeof(function)), aux;
	functions * last_function;
	functions * result = last_function = malloc(sizeof(functions));
	
	function_count = fi[offset++];
	fprintf(stdout, "N. de funcions: %d\n", function_count);
	
	for(i=0; i<function_count; i++)
	{
		actual->name = readStringBytes(&offset, fi);
		fprintf(stdout, "Funcio %d: %s\n", i+1, actual->name);
		
		actual->id = fi[offset++];
		
		last_function->value = actual;
		last_function->next = malloc(sizeof(functions));
		last_function = last_function->next;
		actual = malloc(sizeof(function));
	}
	
	fprintf(stdout, "Hey! Estic interpretant l'arxiu! :)\n");
	
}

char *readStringBytes(int *offset, char * text)
{
	char length = text[*offset++];
	char *result = malloc(sizeof(char)*length);
	
	memcpy(result, text+*offset, length);
	
	offset+=length;
	
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