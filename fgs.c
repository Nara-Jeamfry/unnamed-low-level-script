/*
	Fast Game Scripting
	fgs.c
	Purpose: implements the main FastGameScript API.
	
	@author Marc López Baz
	@version 0.5 01/09/2014
*/ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "fgs.h"
#include "fgs_internals.h"
#include "prac3.h"

struct fgs_state {
	fgsfile *compiled_files;
	
	bfgsfile *loaded_files;
	
	functions *list;
	functions *tail;
};

/* ----------------CODE---------------- */

/** Initializes the FGS context, enabling all the functions.
	start_context
	
	This method initializes the context of the FGS interpreter.
*/
	
fgs_state *start_context()
{
	fgs_state *state = malloc(sizeof(fgs_state));
	
	initialize_state(state);
}

void initialize_state(fgs_state *fgs)
{
	fgs->compiled_files = NULL;
	fgs->loaded_files = NULL;
	fgs->list = NULL;
	fgs->tail = NULL;
}

void clean_state(fgs_state *fgs)
{
	fgsfile *files, *auxfgs;
	bfgsfile *codes, *auxbfgs;
	
	files = fgs->compiled_files;
	while(files)
	{
		free(files->name);
		
		auxfgs = files->next;
		free(files);
		files = auxfgs;
	}
	
	codes = fgs->loaded_files;
	while(codes)
	{
		free(codes->name); 
		free(codes->code);
		
		auxbfgs = codes->next;
		free(codes);
		codes = auxbfgs;
	}
}

void destroy_context(fgs_state *fgs)
{
	if(fgs)
	{
		clean_state(fgs);
		free(fgs);
	}
}

fgsfile * fgs_get_files(fgs_state *fgs)
{
	return fgs->compiled_files;
}

void fgs_set_file(fgs_state *fgs, fgsfile *file)
{
	fgs->compiled_files = file;
}

bfgsfile * fgs_get_codes(fgs_state *fgs)
{
	return fgs->loaded_files;
}

void fgs_set_code(fgs_state *fgs, bfgsfile *file)
{
	fgs->loaded_files = file;
}

void add_function(fgs_state * fgs, functions * f)
{
	if(!fgs->list)
	{
		fgs->list = f;
		fgs->tail = f;
		return;
	}
	if(!findFunctionByName(f->value->name, fgs->list))
	{
		fgs->tail->next = f;
		fgs->tail = f;
	}
}

functions * fgs_get_list(fgs_state * fgs)
{
	return fgs->list;
}

int add_file_to_state(fgs_state *fgs, char * name)
{
	FILE * file;
	
	unsigned char * byteCode;
	char * bytefile;
	
	compileFile(fgs, name);
	
	changeSourceToByteName(&bytefile, name);
	
	if(verbose)
		printf("--parse_file-- Checking if %s is already loaded...\n", bytefile);
		
	if(fileAlreadyLoaded(fgs_get_codes(fgs), bytefile))
	{
		if(verbose)
			printf("--parse_file-- ByteCode is up to date.\n\n", bytefile);
			
		free(bytefile);
		return;
	}
	
	byteCode = parse_file(fgs, bytefile);
	
	add_loaded_file(fgs, bytefile, byteCode);
	
	int result = read_file(fgs, byteCode);
	print("Closing the file...\n");
	
	free(bytefile); /* we have to free the name (changeSourceToByteName can't do it for us) */
}

/** Reads data from a FGS-ByteCode file.
	read_file
	
	This method receives an unsigned char array and reads interesting
	FastGameScript information from it. The unsigned char array MUST be
	a FastGameScript-ByteCode file compiled by FGS-compiler, otherwise,
	the function will return NULL. If the file header is the same that
	the one from FGS-ByteCode files, undefined behavior is caused.
	
	\param fi The byte array containing a FGS-ByteCode file contents.
	
	\return A functions * data struct containing the existing functions 
		and information about it.
*/
functions * read_file_wotototo(fgs_state * fgs, unsigned char * fi)
{
	int offset = 13, i, j, auxNumber, line;
	int function_count, type_count, var_count;
	unsigned char op;
	
	function *actual;
	function *aux;
	functions * func_container = NULL;
		
	type * types = NULL, *auxtype = NULL;
	char * auxString;
	while(op != 0)
	{
		
		
		if(verbose)
			fprintf(stdout, "Function %d ended at offset %X\n", i+1, offset-1);
		
	}
	
	if(verbose)
		fprintf(stdout, "Hey! Estic interpretant l'arxiu! :)\n");
	
	return NULL;
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
		if(list->value != NULL && !strcmp(list->value->name, name))
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
	unsigned char * op = actualFrame->func->start;
	char * auxText;
	char offset = actualFrame->func->offset;
	
	stacke * aux1, * aux2, * auxres;
	var * auxvar;
	
	while(op[actualFrame->pc] != 0)
	{
		if(debug)
			fprintf(stdout, "--debugFunction-- Now at op %X.\n", actualFrame->pc);
		switch(op[actualFrame->pc])
		{
			case BYT_GOTO:
				printd("--debugFunction-- Found goto\n");
				actualFrame->pc = op[(actualFrame->pc)+1];
				break;
			case BYT_PUSHI:
				printd("--debugFunction-- Found pushi\n");
				pushi(actualFrame->datastack, *(int *)&(op[(actualFrame->pc)+1]));
				actualFrame->pc = (actualFrame->pc)+5;
				break;
			case BYT_PUSHF:
				printd("--debugFunction-- Found pushf\n");
				pushf(actualFrame->datastack, *(float *)&(op[(actualFrame->pc)+1]));
				actualFrame->pc = (actualFrame->pc)+5;
				break;
			case BYT_PUSHS:
				printd("--debugFunction-- Found pushs\n");
				actualFrame->pc+=readStringBytes((op+(actualFrame->pc)+1), &auxText);
				pushs(actualFrame->datastack, auxText);
				free(auxText);
				auxText = NULL;
				break;
			case BYT_PUSHVAR:
				printd("--debugFunction-- Found pushvar\n");
				auxvar = findVariable(actualFrame->variables, op[(actualFrame->pc)+1]);
				pushvar(actualFrame->datastack, auxvar);
				actualFrame->pc = (actualFrame->pc)+2;
				break;
			case BYT_ADDI:
				printd("--debugFunction-- Found addi\n");
				addi(actualFrame->datastack);
				actualFrame->pc = (actualFrame->pc)+1;
				break;
			case BYT_SUBI:
				printd("--debugFunction-- Found subi\n");
				subi(actualFrame->datastack);
				actualFrame->pc = (actualFrame->pc)+1;
				break;
			case BYT_LTI:
				printd("--debugFunction-- Found lti\n");
				
				actualFrame->pc = (actualFrame->pc)+lti(actualFrame->datastack);
				
				break;
			case BYT_LEI:
				printd("--debugFunction-- Found lei\n");
				
				actualFrame->pc = (actualFrame->pc)+lei(actualFrame->datastack);
				
				break;
			case BYT_GTI:
				printd("--debugFunction-- Found gti\n");
				
				actualFrame->pc = (actualFrame->pc)+gti(actualFrame->datastack);
				
				break;
			case BYT_GEI:
				printd("--debugFunction-- Found gei\n");
				
				actualFrame->pc = (actualFrame->pc)+gei(actualFrame->datastack);
				
				break;
			case BYT_EQ:
				printd("--debugFunction-- Found eq\n");
				
				actualFrame->pc = (actualFrame->pc)+eq(actualFrame->datastack);
				
				break;
			case BYT_NEQ:
				printd("--debugFunction-- Found neq\n");
				
				actualFrame->pc = (actualFrame->pc)+neq(actualFrame->datastack);
				
				break;
			case BYT_POPVAR:
				printd("--debugFunction-- Found popvar\n");
				auxvar = findVariable(actualFrame->variables, op[(actualFrame->pc)+1]);
				popvar(actualFrame->datastack, auxvar);
				actualFrame->pc = (actualFrame->pc)+2;
				break;
			default:
				printd("--debugFunction-- Found unknown op\n");
				actualFrame->pc = (actualFrame->pc)+1;
		}
		printStatus(actualFrame);
	}
	if(debug)
		fprintf(stdout, "--debugFunction-- Now at op %X.\n", actualFrame->pc);
	printd("--debugFunction-- Found HALT!\n");
	
	return NULL;
}

frame * createFrame(fgs_state * fgs, char * function)
{
	frame * result = malloc(sizeof(frame));
	int i;
	var * aux, * lastaux;
	
	print("--createFrame-- Allocating memory...\n");
	result->variables = NULL;
	
	if(fgs->list == NULL)
	{
		print("--createFrame-- WELL THIS IS EMBARRASSING WE DO NOT HAVE FUNCTIONS THX\n");
		return NULL;
	}
	else
	{
		print("--createFrame-- We have functions! Let's search for it.\n");
		result->func = findFunctionByName(function, fgs->list);
		if(result->func == NULL)
		{
			print("--createFrame-- Woops. Didn't found that one.\n");
			return NULL;
		}
		else
			print("--createFrame-- FOUND!\n");
	}
	
	result->pc = result->func->offset+1;
	
	if(verbose)
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
			if(verbose)
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
	if(debug)
		fprintf(stdout, "--findVariable-- Searching var %d.\n", id);
	char found = 0;
	var * aux = variables;
	while(aux && !found)
	{
		if(aux->id == id)
		{
			printd("--findVariable-- Found :)\n");
			found = 1;
			return aux;
		}
		aux = aux->next;
	}
	printd("--findVariable-- Not found :(\n");
	return NULL;
}

int readStringBytes(char * source, char **destination)
{
	int length = (*source);
	
	if(verbose) printf("--readStringBytes-- Allocating %d bytes...\n", length+1);
	
	*destination = malloc(sizeof(char)*length + 1);
	
	if(!*destination)
	{
		printf("--readStringBytes-- Could not allocate %d bytes\n",length + 1); 
	}
	
	if(!memcpy(*destination, source+1, length))
	{
		printf("--readStringBytes-- Failed while copying %d bytes\n", length+1);
		exit(4);
	}
	
	(*destination)[length]='\0';
	
	if(verbose) printf("--readStringBytes-- Offset is %d\n", length+1);
	
	return length+1;
}