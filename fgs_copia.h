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
	
	unsigned char * start;
	unsigned char offset;

} function;

typedef struct framerl {
	var * variables;
	
	unsigned char pc;
	
	function * func;
	
	stack * datastack;
	
	unsigned char * ops;
} frame;

typedef struct function_list {
	function *value;
	struct function_list *next;
} functions;

#ifndef VERBOSE
#define VERBOSE
char verbose;
#endif

#ifndef DEBUGVERBOSE
#define DEBUGVERBOSE
char debug;
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
void printd(char *);

functions * read_file(unsigned char *);
unsigned char * parse_file(FILE *);
void call_function();