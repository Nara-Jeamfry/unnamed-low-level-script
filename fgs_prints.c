#include "fgs.h"

void print(char * text)
{
	if(verbose)
		fprintf(stdout, text);
}

void printd(char * text)
{
	if(debug)
		fprintf(stdout, text);
}

void printStatus(frame * fr)
{
	fprintf(stdout, "Actual status: %d elems on stack.\n\n", fr->datastack->top+1);
}