#include <stdio.h>

#include "ops.h"
#include "prac3.h"
#include "fgs_stack.h"

typedef struct type_container {
	char * name;
	
	struct type_container* next;
} type;

typedef struct function_container {

	char id;
	
	char * name;

	int type_count;
	int var_count;
	
	type *types;
	
	char * start;
	unsigned char offset;

} function;

typedef struct framerl {
	var * variables;
	
	char pc;
	
	function * func;
	
	stack * datastack;
	
	char * ops;
} frame;

typedef struct function_list {
	function *value;
	struct function_list *next;
} functions;

#ifndef VERBOSE
#define VERBOSE
char verbose;
#endif

functions * globalFunctions;

function *findFunction(char, functions *);
function *findFunctionByName(char *, functions *);
var *findVariable(var *, unsigned char);

frame * createFrame(char *);

void * debugFunction(frame *);
void printStatus(frame *);

void * runFunction(frame *);

char *readStringBytes(int *, char *);

void print(char *);

functions * read_file(char *);
char * parse_file(FILE *);
void call_function();