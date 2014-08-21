#include <stdio.h>

typedef struct type_container {
	char * name;
	
	struct type_container* next;
} type;

typedef struct function_container {

	int id;
	
	char * name;

	int type_count;
	int var_count;
	
	type *types;

} function;

typedef struct function_list {
	function *value;
	struct function_list *next;
} functions;

functions * read_file(char *);
char * parse_file(FILE *);
void call_function();