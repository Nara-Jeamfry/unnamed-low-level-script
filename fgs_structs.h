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
	
	unsigned char * start;
	unsigned char * end;
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
	
	unsigned char * code;
	
	struct loaded_files * next;
} bfgsfile;

typedef struct fgs_state fgs_state;
#endif