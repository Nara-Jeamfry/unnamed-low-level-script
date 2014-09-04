#include <stdio.h>
#include <time.h>

#include "ops.h"
#include "prac3.h"
#include "fgs_stack.h"
#include "fgs_interpreter_ops.h"
#include "fgs_structs.h"

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

fgs_state *start_context();
void destroy_context(fgs_state *);
int add_file_to_state(fgs_state *, char *);
int fileAlreadyLoaded(bfgsfile *filestruct, char * name);
void add_loaded_file(fgs_state * fgs, char * name, unsigned char * code);


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
int readStringBytes(unsigned char * source, char **destination);

void print(char *);
void printd(char *);

FILE * open_file(char *);
int read_file(fgs_state *, unsigned char *);
void call_function();
#endif