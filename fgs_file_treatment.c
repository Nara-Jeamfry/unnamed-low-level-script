#include <stdlib.h>
#include "fgs.h"
#include "fgs_internals.h"

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
	
	if(file==NULL)
	{
		fprintf(stdout, "Error while opening file %s\n", name);
		exit(1);
	}
	
	return file;
}

unsigned char * parse_file(fgs_state * fgs, char * filename)
{
	int lSize;
	unsigned char * result;
	
	FILE * fi;
	
	fi = open_file(filename);
	
	fseek(fi, 0, SEEK_END);
	lSize = ftell(fi);
	rewind(fi);
	
	result = malloc(sizeof(char)*lSize);
	if(result==NULL)
	{
		fprintf(stdout, "--parse_file-- Could not allocate this much memory.\n");
		exit(3);
	}
	
	int i = fread(result, 1, lSize, fi);
	if(i!=lSize)
	{
		if(verbose)
		fprintf(stdout, "--parse_file-- I have read the same number of bytes that the file has but something went wrong.\n");
	}
	
	fclose(fi);
	
	return result;
}
void compileFile(fgs_state *fgs, char * name)
{
	FILE * source;
	char * pch, *output;

	addExtensionIfNeeded(name);
	
	source = fopen(name, "r");
	
	if(verbose)
		fprintf(stdout, "--compileFile-- Trying to open \"%s\"\n", name);
	
	source = fopen(name, "r");
	
	if(!source)
	{
		printf("couldn't open file \"%s\" for reading\n", name);
		exit(1);
	}
	
	changeSourceToByteName(&output, name);
	
	if(verbose)
		fprintf(stdout, "--compileFile-- Trying to save on \"%s\"\n", output);
	
	parseFile(source, output);
	
	fclose(source);
}

int fileModifiedAfterCompilation(char * name)
{
	
	
	addExtensionIfNeeded(name);
	
	
}