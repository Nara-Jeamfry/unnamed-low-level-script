#include <stdio.h>

#ifndef commonConstants
#define commonConstants

#define STRINGT 0
#define INTT 1
#define FLOATT 2
#define BOOLT 3

#define TCOUNT 3

#define SUMA 0
#define REST 1
#define MULT 2
#define DIVIS 3
#define ANDOP 4
#define OROP 5

#define EQUAL 0
#define GREAT 1
#define LESS 2
#define INCOMPAT 3

typedef struct C3A_val {
	int type; /* 0 if temporal value, 1 if variable on symtab, 2 if intlit, 3 if floatlit, 4 if stringlit */
	
	union C3A_values {
		int tempID;
		char *varName;
		int literalI;
		float literalF;
		char *literalS;
	} value;
	
	struct C3A_container *container;
} C3A_value;

typedef enum {
	IF_OP,
	GOTO,
	ASSIGNMENT,
	ASSIGNMENT_OP,
	ASSIGNMENT_UN,
	PARAM,
	CALL,
	HALT
} INST_SET;

typedef enum {
	CHSI,
	CHSF,
	I2F,
	F2I,
	ADDI,
	SUBI,
	MULI,
	DIVI,
	ADDF,
	SUBF,
	MULF,
	DIVF,
	EQ_OP,
	NE_OP,
	LTI,
	LEI,
	GTI,
	GEI,
	LTF,
	LEF,
	GTF,
	GEF,
	PUTI,
	PUTF
} REL_INST_SET;

typedef struct bytecode {
	INST_SET op;
	
	REL_INST_SET oprel;
	
	C3A_value *val1;
	C3A_value *val2;
	C3A_value *val3;
	
	int gotoL;
	
	struct bytecode *next;
}  bytecode_entry;

typedef struct C3A_container {
	C3A_value *value;
	
	int id;
	
	struct C3A_container *next;
} C3A_value_container;

typedef struct function {
	char *identifier;
	int length;
	
	bytecode_entry *first_code;
	bytecode_entry *last_code;
	
	C3A_value_container *locals;
	int localLength;
	
	struct function *next;
} function_entry;

typedef struct BP {
	bytecode_entry *entry;
	
	struct BP *next;
	
} BP_list;

typedef union yytype {
	struct varia {
		char * identifier;
		int type;
		union var_value {
			int int_value;
			float float_value;
			char *string_value;
			int bool_value;
		} value;
		int number;
	} variable;
	
	struct liter {
		int type;
		union lit_value {
			int int_value;
			float float_value;
			char *string_value;
			int bool_value;
		} value;
		C3A_value *variable;
		BP_list *trueList;
		BP_list *falseList;
	} literal;
	
	struct mark {
		int quadtupla;
		BP_list *trueList;
		BP_list *falseList;
		BP_list *nextList;
	} marker;
	
	BP_list *statement;
	
	char *error;
	
	void *non_defined;
} YYSTYPE;

/* 0 if Calculator mode, 1 if Program mode */
int calc;
INST_SET op, op2;

int dataOffset;
int headerLength;

#endif

int nextQuad();

C3A_value *tempLocation();
C3A_value *varLocation(char *);
C3A_value *litLocationString(char *);
C3A_value *litLocationInt(int);
C3A_value *litLocationFloat(float);

bytecode_entry *gen_code();
bytecode_entry *gen_code_op(INST_SET);
void backpatch(BP_list*, int);
BP_list* mergeLists(BP_list*, BP_list*);
BP_list* addToList(BP_list*, bytecode_entry*);

FILE *codeFile;
FILE *debugFile;

FILE *getCodeFile();
FILE *getDebugFile();

void openCodeFile();
void openDebugFile();

void printCode(FILE *);
char *printOp(bytecode_entry *, int *);
char *printC3AVal(C3A_value *);
char *printRelOp(REL_INST_SET);

C3A_value_container *checkNewVar(C3A_value *, C3A_value_container *);

void yyerror(const char *);

void printError(const char *, char *);
void printError2(const char*, char *, char *);

char * typeToString(int type);
char * printInmediateType(struct liter data);
char * printVariableType(struct varia data);
int canIOperateThem(struct liter, struct liter, int);
int compareValues(struct liter, struct liter);
struct liter operateValues(struct liter, struct liter, int);
char * printValue(struct liter);
char * printVariableValue(struct varia data);

struct liter fromVarToLit(struct varia);
struct varia fromLitToVar(struct liter, char *);

void storeSym(struct varia);
int loadSym(struct varia, struct liter *);
int isSymChosen(struct varia);