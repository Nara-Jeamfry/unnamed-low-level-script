#ifndef FGS_STRUCTS
#define FGS_STRUCTS

typedef struct fgs_state fgs_state;

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

	fgs_state * state;
} frame;

typedef struct cfunction_container
{
	char * name;

	int (* pointer)(fgs_state *);
} cfunction;

typedef struct function_list {
	/** 
		0 for a FGS function, 1 for a C function.
	*/
	int type;
	union function_union {
		function *value;
		cfunction *cvalue;
	} value;
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

#endif