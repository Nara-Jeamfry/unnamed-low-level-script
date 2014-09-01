#include <stdlib.h>
#include "fgs.h"

void addExtensionIfNeeded(char * name)
{
	char *extension, *auxName;
	extension = strrchr(name, '.');
	if(extension && !strcmp(extension, ".fgs"))
	{
		auxName = malloc((extension-name) + 5);
		if(!auxName)
		{
			printf("WOW WO WOW\n");
			exit(3);
		}
		strcpy(auxName, name);
		extension = (auxName + (extension-name)+1);
		extension[0] = 'b';
		extension[1] = 'f';
		extension[2] = 'g';
		extension[3] = 's';
		extension[4] = '\0';
		
		/* free(name); */
		name = auxName;
	}
	else if(!extension)
	{
		auxName = malloc(strlen(name)+5);
		strcpy(auxName, name);
		strcat(auxName, ".fgs");
		/* free(name);  */
		name = auxName;
	}
}

FILE * open_file(char * name)
{
	
	FILE * file;
	
	file = fopen(name, "rb");
	
	return file;
}

void openFile(char * name)
{
	FILE * source;
	char * pch, *output;

	addExtensionIfNeeded(name);
	
	source = fopen(name, "r");
	
	if(verbose)
		fprintf(stdout, "--openFile-- Trying to open \"%s\"\n", name);
	
	if(!source)
	{
		printf("couldn't open file \"%s\" for reading\n", name);
		exit(1);
	}
	
	pch = strrchr(name, '.');
	output = malloc(sizeof(char) * (pch-name+1+5));
	strcpy(output, name);
	pch = strrchr(output, '.');
	pch[1] = 'b';
	pch[2] = 'f';
	pch[3] = 'g';
	pch[4] = 's';
	pch[5] = '\0';
	
	if(verbose)
		fprintf(stdout, "--openFile-- Trying to save on \"%s\"\n", output);
	
	parseFile(source, output);
	
	fclose(source);
}

int fileModifiedAfterCompilation(char * name)
{
	
	
	addExtensionIfNeeded(name);
	
	
}