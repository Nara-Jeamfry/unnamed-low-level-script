
#include <string.h>

#ifndef STACK_STRUCTS
#define STACK_STRUCTS
typedef struct variablerl {
	char type; /* 0 for int, 1 for float, 2 for string */
	
	union var_values {
		int literalI;
		float literalF;
		char *literalS;
	} value;
	
	unsigned char id;
	struct variablerl * next;
} var;

typedef struct stack_elem {
	char type; /* 0 for int, 1 for float, 2 for string */
	
	union elemvalue {
		int literalI;
		float literalF;
		char *literalS;
	} value;
	
	struct stack_elem * last;
} stacke;

typedef struct stack_struct {
	stacke * contents;
	int top;
	int maxSize;
} stack;
#endif

#ifndef STACKVERBOSE
#define STACKVERBOSE
char stackverbose;
#endif

#ifndef STACK_METHODS
#define STACK_METHODS
stack * StackInit(int);

/* StackPushX and StackPopX return 0 if all works correctly, !0 otherwise. */
int StackPushI(stack *, stacke *);
int StackPushF(stack *, stacke *);
int StackPushS(stack *, stacke *);
int StackPopI(stack *, stacke *);
int StackPopF(stack *, stacke *);
int StackPopS(stack *, stacke *);
char StackEmpty(stack *);
char StackFull(stack *);
#endif