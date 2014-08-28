#include <stdio.h>

#include "ops.h"
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
	
	char start;

} function;

typedef struct function_list {
	function *value;
	struct function_list *next;
} functions;


function *findFunction(char , functions *);
char *readStringBytes(int *, char *);

functions * read_file(char *);
char * parse_file(FILE *);
void call_function();