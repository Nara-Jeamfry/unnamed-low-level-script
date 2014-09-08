/**	\file fgs.h
	Declares all the functions available to host applications of the FGS API.
	
	This file declares all the functions and data needed by a host application that is going to use
	FGS to compile and execute scripts. The private functions are stored on the fgs_internals.h header file.

	\author Marc López Baz
	\version 0.6 
	\date 04/09/2014
*/ 
#include <stdio.h>
#include <time.h>

#include "ops.h"
#include "fgs_comp.h"
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

/* ----------- EXTERNAL API ------------ */
/**
	\brief Initializes the FGS context, enabling all the functions.
	\post The function fgs_destroy_context(fgs_state *) MUST be called before the program end and after a fgs_start_context call.
*/
fgs_state *fgs_start_context();
/**
	\brief Destroys a FGS context, freeing all the used memory.
	\pre A call to fgs_start_context must have been made on this fgs_state before this call.
*/
void destroy_context(fgs_state *);
/**
	\brief Adds the functions on a file to the context.
*/
int fgs_load_script(fgs_state *, char *);

/**
	\brief Allows the host application to call a function (script or C-declared).
	\pre The fgs_state must be initialized. The function can be declared or not (this function is fail-safe).
	\return 0 if errors were found, !0 otherwise.
*/
int fgs_call_function(fgs_state * fgs, char * function_name);

void push_valueI(fgs_state *, int);
void push_valueF(fgs_state *, float);
void push_valueS(fgs_state *, char *);

int pop_valueI(fgs_state *);
float pop_valueF(fgs_state *);
void pop_valueS(fgs_state *, char **);

void register_function(int (*function)(fgs_state *), char * name);

/* ------------- INTERNAL API ------------ */


/* Returns string length as to skip it from the code (counting THE BYTE FOR THE LENGTH too).

   Keep in mind that this function allocates memory that should be deallocated afterwards. */
int readStringBytes(unsigned char * source, char **destination);
#endif