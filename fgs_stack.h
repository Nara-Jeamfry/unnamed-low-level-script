
typedef struct varia {
	char type; /* 0 for int, 1 for float, 2 for string */
	
	union var_values {
		int literalI;
		float literalF;
		char *literalS;
	} value;
	
	unsigned char id;
	struct varia * next;
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

stack * StackInit(int);

void StackPush(stack *, stacke *);
stacke * StackPop(stack *);
char StackEmpty(stack *);
char StackFull(stack *);