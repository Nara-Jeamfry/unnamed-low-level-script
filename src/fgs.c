/**	\file fgs.c
	Implements the main FastGameScript API.
	
	This file holds the code that allows any C program to compile dynamically a .fgs script file, 
	run functions from it, and operate with the input and return values for these functions.

	\author Marc López Baz
	\version 0.6 
	\date 04/09/2014
*/ 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "fgs.h"
#include "fgs_internals.h"

struct fgs_state {
	fgsfile *compiled_files;
	
	bfgsfile *loaded_files;
	
	stack *mainstack;

	functions *list;
	functions *tail;
};

/* ----------------CODE---------------- */

/** 
	This method initializes the context of the FGS interpreter, declaring all the values as NULL, and
	allocating memory for all the needed information. The allocated memory is not freed, so a fgs_destroy_context()
	call must be made after this fgs_start_context call to deallocate the unneeded memory.
*/
	
fgs_state *fgs_start_context()
{
	fgs_state *state = (fgs_state *)malloc(sizeof(fgs_state));
	
	initialize_state(state);
	
	return state;
}

void initialize_state(fgs_state *fgs)
{
	fgs->compiled_files = NULL;
	fgs->loaded_files = NULL;
	fgs->list = NULL;
	fgs->tail = NULL;
	fgs->mainstack = StackInit(255);
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
	fgs->compiled_files = NULL;
	
	codes = fgs->loaded_files;
	while(codes)
	{
		free(codes->name); 
		free(codes->code);
		
		auxbfgs = codes->next;
		free(codes);
		codes = auxbfgs;
	}
	fgs->loaded_files = NULL;



	StackDestroy(fgs->mainstack);
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
	if(!findFunctionByName(f->value.value->name, fgs->list))
	{
		fgs->tail->next = f;
		fgs->tail = f;
	}
}

functions * fgs_get_list(fgs_state * fgs)
{
	return fgs->list;
}

int fgs_load_script(fgs_state *fgs, char * name)
{	
	unsigned char * byteCode;
	char * bytefile;
	
	compileFile(fgs, name);
	
	changeSourceToByteName(&bytefile, name);
	
	if(verbose)
		printf("--parse_file-- Checking if %s is already loaded...\n", bytefile);
		
	if(fileAlreadyLoaded(fgs_get_codes(fgs), bytefile))
	{
		if(verbose)
			printf("--parse_file-- ByteCode is up to date.\n\n");
			
		free(bytefile);
		return 0;
	}
	
	byteCode = parse_file(fgs, bytefile);

	if(!byteCode)
	{
		return 0;
	}
	
	add_loaded_file(fgs, bytefile, byteCode);
	
	if(!read_file(fgs, byteCode))
	{
		printf("Could not read file.\n");
	}
	print("Closing the file...\n");
	
	free(bytefile); /* we have to free the name (changeSourceToByteName can't do it for us) */
	return 1;
}

int fgs_call_function(fgs_state * fgs, char * function_name)
{
	frame * f = createFrame(fgs, function_name);
	int result;

	if(f == NULL)
	{
		if(verbose)
			printf("Could not find function %s.", function_name);
		free(f);
		return 0;
	}

	result = runFunction(f);

	free(f);
	return result;
}

void push_valueI(fgs_state * fgs, int value)
{
	pushi(fgs->mainstack, value);
}

void push_valueF(fgs_state * fgs, float value)
{
	pushf(fgs->mainstack, value);
}

void push_valueS(fgs_state * fgs, char *value)
{
	pushs(fgs->mainstack, value);
}

int pop_valueI(fgs_state * fgs)
{
	stacke * aux = (stacke *)malloc(sizeof(stacke));
	StackPopI(fgs->mainstack, aux);

	int result = aux->value.literalI;
	
	free(aux);
	return result;
}

float pop_valueF(fgs_state * fgs)
{
	stacke * aux = (stacke *)malloc(sizeof(stacke));
	StackPopF(fgs->mainstack, aux);

	float result = aux->value.literalF;
	
	free(aux);
	return result;
}

void pop_valueS(fgs_state * fgs, char ** destination)
{
	stacke * aux = (stacke *)malloc(sizeof(stacke));
	StackPopS(fgs->mainstack, aux);

	strcpy(*destination, aux->value.literalS);

	free(aux);
}

void register_function(int (*function)(fgs_state *), char * name);

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

function *findFunctionByName(char * name, functions *list)
{
	char found = 0;
	while(list && !found)
	{
		if(list->value.value != NULL && !strcmp(list->value.value->name, name))
		{
			found = 1;
			return list->value.value;
		}
		list = list->next;
	}
	return NULL;
}

int runFunction(frame *actualFrame)
{
	unsigned char * op = actualFrame->func->start;
	char * auxText;
	
	var auxvar;
	
	while(op[(int)actualFrame->pc] != 0 && op[(int)actualFrame->pc] != 1)
	{
		if(debug)
			fprintf(stdout, "--debugFunction-- Now at op %X.\n", actualFrame->pc);
		switch(op[(int)actualFrame->pc])
		{
			case BYT_CALL:
				printd("--debugFunction-- Found call\n");
				actualFrame->pc+=readStringBytes((op+(actualFrame->pc)+1), &auxText)+1;
				if(!fgs_call_function(actualFrame->state, auxText))
				{
					printf("--runFunction-- Call to %s: undefined function.", auxText);
				}
				free(auxText);
				break;
			case BYT_GOTO:
				printd("--debugFunction-- Found goto\n");
				actualFrame->pc = op[(actualFrame->pc)+1];
				break;
			case BYT_HALR:
				printd("--debugFunction-- Found return\n");
				auxvar = findVariable(actualFrame, op[(actualFrame->pc)+1]);
				pushvar(actualFrame->datastack, auxvar);
				op = actualFrame->func->end;
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
				actualFrame->pc+=readStringBytes((op+(actualFrame->pc)+1), &auxText)+1;
				pushs(actualFrame->datastack, auxText);
				free(auxText);
				auxText = NULL;
				break;
			case BYT_PUSHVAR:
				printd("--debugFunction-- Found pushvar\n");
				auxvar = findVariable(actualFrame, op[(actualFrame->pc)+1]);
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
				popvar(actualFrame, actualFrame->datastack, op[(actualFrame->pc)+1]);
				actualFrame->pc = (actualFrame->pc)+2;
				break;
			default:
				printd("--debugFunction-- Found unknown op\n");
				actualFrame->pc = (actualFrame->pc)+1;
		}
		if(debug)
			printStatus(actualFrame);
	}
	if(debug)
		fprintf(stdout, "--debugFunction-- Now at op %X.\n", actualFrame->pc);

	if(op[(int)actualFrame->pc] == 1)
	{
		printd("--debugFunction-- Found HALR!\n");
		auxvar = findVariable(actualFrame, op[(actualFrame->pc)+1]);
		pushvar(actualFrame->datastack, auxvar);
	}
	else {
		printd("--debugFunction-- Found HALT!\n");
	}
	print("--runFunction-- No problems found during execution.\n");

	return 1;
}

frame * createFrame(fgs_state * fgs, char * function)
{
	frame * result = (frame *)malloc(sizeof(frame));
	int i;
	
	print("--createFrame-- Allocating memory...\n");
	
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
		result->variables[i].id = i+1;
	
		if(verbose)
			fprintf(stdout, "--createFrame-- Added variable %d.\n", i+1);
	}
	
	result->datastack = fgs->mainstack;
	print("--createFrame-- Stack reserved!\n");
	
	return result;
}

var findVariable(frame * context, unsigned char id)
{
	return context->variables[id-1];
}

void freeString(frame * context, unsigned char id)
{
	if(context->variables[id-1].type == 2)
	{
		if(context->variables[id-1].value.literalS != NULL)
		{
			free(context->variables[id-1].value.literalS);
			context->variables[id-1].value.literalS = NULL;
		}
	}
}

void setVariableI(frame * context, unsigned char id, int value)
{
	freeString(context, id);
	context->variables[id-1].value.literalI = value;
	context->variables[id-1].type = 0;
}

void setVariableF(frame * context, unsigned char id, float value)
{
	freeString(context, id);
	context->variables[id-1].value.literalF = value;
	context->variables[id-1].type = 1;
}

void setVariableS(frame * context, unsigned char id, char * value)
{
	freeString(context, id);
	context->variables[id-1].value.literalS = (char *)malloc(strlen(value)+1);
	strcpy(context->variables[id-1].value.literalS, value);
	context->variables[id-1].type = 2;
}

/* var *findVariable(var * variables, unsigned char id)
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
} */

int readStringBytes(unsigned char * source, char **destination)
{
	int length = (*source);
	
	if(verbose) printf("--readStringBytes-- Allocating %d bytes...\n", length+1);
	
	*destination = (char *)malloc(sizeof(char)*length + 1);
	
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