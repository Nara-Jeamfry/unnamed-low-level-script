#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "fgs.h"

int main(int argc, char **argv)
{
	if(verbose)
		fprintf(stdout, "Benvingut a l'intèrpret de FastGameScript!\n\n");
	
	char * name = "example_fibonacci_complexe.fgs", * byteCode;
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
	
	
	FILE * file;
	frame * basicFrame;
	var * input;
	
	for(i=0; i<1000; i++)
	{
		print("--------------\n");
		openFile(name);
		
		file = open_file("example_fibonacci_complexe.bfgs");
		
		if(file==NULL)
		{
			fprintf(stdout, "Error al llegir caca pipi :( \n");
			exit(1);
		}
		
		print("Reading file...\n");
		byteCode = parse_file(file);
		globalFunctions = read_file(byteCode);
		
		fclose(file);
		
		print("Closing the file...\n");
		
		print("Now, we're gonna try to load fibonacci function\n");
		basicFrame = createFrame("fibonacci");
		
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
		free(byteCode);
	}
	
	fprintf(stdout, "Well that worked fine!\n");
	return 0;
}
