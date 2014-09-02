#include <stdio.h>
#include <time.h>

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

#ifndef DEBUGVERBOSE
#define DEBUGVERBOSE
char debug;
#endif

/**
 *	This global var saves all the functions loaded by the parser.
 */
functions * globalFunctions;

fgs_state *start_context();
void destroy_context(fgs_state *);

function *findFunction(char, functions *);
function *findFunctionByName(char *, functions *);
var *findVariable(var *, unsigned char);

frame * createFrame(char *);

void * debugFunction(frame *);
void printStatus(frame *);

void * runFunction(frame *);

/* Returns string length as to skip it from the code (counting THE BYTE FOR THE LENGTH too).

   Keep in mind that this function allocates memory that should be deallocated afterwards. */
int readStringBytes(char * source, char **destination);

void print(char *);
void printd(char *);

void addExtensionIfNeeded(char *);
FILE * open_file(char *);
functions * read_file(unsigned char *);
void call_function();