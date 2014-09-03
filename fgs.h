#include <stdio.h>
#include <time.h>

#include "ops.h"
#include "prac3.h"
#include "fgs_stack.h"

#ifndef STRUCTS
#define STRUCTS
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
	var variables[255];
	
	char pc;
	
	function * func;
	
	stack * datastack;
	
	char * ops;
} frame;

typedef struct function_list {
	function *value;
	struct function_list *next;
} functions;

typedef struct compiled_files {
	time_t compilation_time;
	char * name;

	struct compiled_files * next;
} fgsfile;

typedef struct loaded_files {
	time_t load_time;
	char * name;
	
	char * code;
	
	struct loaded_files * next;
} bfgsfile;

typedef struct fgs_state fgs_state;
#endif

#ifndef VERBOSE
#define VERBOSE
char verbose;
#endif

#ifndef DEBUGVERBOSE
#define DEBUGVERBOSE
char debug;
#endif

#ifndef FGS_API
#define FGS_API
/**
 *	This global var saves all the functions loaded by the parser.
 */
functions * globalFunctions;

fgs_state *start_context();
void destroy_context(fgs_state *);

function *findFunction(char, functions *);
function *findFunctionByName(char *, functions *);

void setVariableI(frame *, unsigned char id, int value);
void setVariableF(frame *, unsigned char id, float value);
void setVariableS(frame *, unsigned char id, char * value);
var findVariable(frame *, unsigned char);

frame * createFrame(fgs_state *, char *);

void * debugFunction(frame *);
void printStatus(frame *);

void * runFunction(frame *);

/* Returns string length as to skip it from the code (counting THE BYTE FOR THE LENGTH too).

   Keep in mind that this function allocates memory that should be deallocated afterwards. */
int readStringBytes(char * source, char **destination);

void print(char *);
void printd(char *);

FILE * open_file(char *);
int read_file(fgs_state *, unsigned char *);
void call_function();
#endif