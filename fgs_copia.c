#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "fgs.h"

int main(int argc, char **argv)
{
	if(verbose)
		fprintf(stdout, "Benvingut a l'intèrpret de FastGameScript!\n\n");
	
	char * name = "example_fibonacci_complexe.fgs";
	int i;
	char c;
	
	while((c = getopt(argc, argv, "vgsd")) != -1)
	{
		if(verbose)
			fprintf(stdout, "Found option %c\n", c);
		switch(c)
		{
			case 'v':
				verbose = 1;
				break;
			case 'g':
				bisonverbose = 1;
				break;
			case 's':
				stackverbose = 1;
				break;
			case 'd':
				debug = 1;
				break;
			case '?':
				printf("Unknown option %c.", c);
				exit(3);
				break;
			default: 
				printf("This shouldn't happen?");
				exit(99);
				break;
		}
	}
	
	if(verbose)
		fprintf(stdout, "Intentarem llegir el codi de l'arxiu \"%s\"!\n", name);
	
	fgs_state *FGS;
	
	FGS = start_context();
	
	FILE * file;
	frame * basicFrame;
	var * input;
	
	for(i=0; i<10000; i++)
	{
		print("--------------\n");
		/* code on add_file_to_state was here */
		
		add_file_to_state(FGS, name);
		add_file_to_state(FGS, "wowo.fgs");
		
		print("Now, we're gonna try to load fibonacci function\n");
		basicFrame = createFrame(FGS, "fibonacci");
		
		if(basicFrame == NULL)
		{
			printf("Didn't find function.");
			exit(9);
		}
		
		print("Selecting manually the input var for fibonacci\n");
		input = findVariable(basicFrame->variables, 1);
		input->type = 0;
		input->value.literalI = 30;
		
		if(verbose)
			fprintf(stdout, "Now var n is: %d\n", basicFrame->variables->value);
		
		print("HERE WE GO!\n");
		runFunction(basicFrame);
	
		if(verbose)
			fprintf(stdout, "Fibonacci number on %dth position is: %d\n", findVariable(basicFrame->variables, 1)->value.literalI, findVariable(basicFrame->variables, 4)->value.literalI);
			
		if(findVariable(basicFrame->variables, 4)->value.literalI != 514229)
		{
			fprintf(stdout, "Cannot verify answer %d.\n", i);
			exit(4);
		}
		print("--------------\n");
	}
	
	fprintf(stdout, "Well that worked fine!\n");
	
	destroy_context(FGS);
	return 0;
}
