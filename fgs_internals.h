/** \file fgs_internals.h
	Declares all the functions for the internal part of the API.

	This header file contains all the functions that are needed on the private part of the FGS api.
	The external functions used by host applications will be defined on the fgs.h header file.
	
	\author Marc López Baz
	\version 0.6 
	\date 01/09/2014
*/

#include "fgs.h"

#ifndef FGS_INTERNALS
#define FGS_INTERNALS

/* ------------------------------------------ */
/* --------- State Getters/Setters ---------- */
/* ------------------------------------------ */

fgsfile * fgs_get_files(fgs_state *);
void fgs_set_file(fgs_state *, fgsfile *);

bfgsfile * fgs_get_codes(fgs_state *);
void fgs_set_code(fgs_state *, bfgsfile *);

functions * fgs_get_list(fgs_state *);

function *findFunctionByName(char *, functions *);


/* ------------------------------------------ */
/* ------------ State Management ------------ */
/* ------------------------------------------ */

/**
	\brief Initializes the data on the state to NULL.
	\pre The fgs_state must be allocated.
*/
void initialize_state(fgs_state *);

/**
	\brief Adds a batch of FGS functions to the state (overriding already existing functions).
*/
void add_function(fgs_state *, functions *);



/* ------------------------------------------ */
/* ------------- File Treatment ------------- */
/* ------------------------------------------ */

/*--- Compilation */
/**
	\brief Adds info about compilation of a file to the state.
	\pre The fgs_state must be initialized.
*/
void add_compiled_file(fgs_state * fgs, char * filename);

/**
	\brief Checks if the file is up-to-date in the state.
*/
int fileAlreadyCompiled(fgsfile *, char * filename);

void compileFile(fgs_state *, char * filename);

/*--- Interpretation */

void add_loaded_file(fgs_state * fgs, char * name, unsigned char * code);
int fileAlreadyLoaded(bfgsfile *filestruct, char * name);
unsigned char * parse_file(fgs_state *, char *);

/*--- Generic */
FILE * open_file(char *);
int read_file(fgs_state *, unsigned char *);
void changeSourceToByteName(char ** dest, char * name);


/* ------------------------------------------ */
/* ------------ Frame Management ------------ */
/* ------------------------------------------ */

frame * createFrame(fgs_state *, char *);

void freeString(frame * context, unsigned char id);

void setVariableI(frame *, unsigned char id, int value);
void setVariableF(frame *, unsigned char id, float value);
void setVariableS(frame *, unsigned char id, char * value);
var findVariable(frame *, unsigned char);


/* ------------------------------------------ */
/* ------------ Debugging/Prints ------------ */
/* ------------------------------------------ */

void print(char *);
void printd(char *);
void printStatus(frame *);


/* ------------------------------------------ */
/* --------------- Execution ---------------- */
/* ------------------------------------------ */

void * debugFunction(frame *);
int runFunction(frame *);

#endif