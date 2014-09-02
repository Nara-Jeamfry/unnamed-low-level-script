#include <stdlib.h>
#include <string.h>

#include "fgs.h"
#include "fgs_internals.h"

int read_file(fgs_state * fgs, unsigned char * bytecode)
{
	printf("OJO\n");
	/* Check the header */
	char header[13] = { 'g', 'a', 'm', 'e', '_', 's', 'c', 'r', 'i', 'p', 't', 3, 0 };
	if(memcmp(bytecode,header, 13))
	{	
		print("--read_file-- Incorrect header (expected \"game_script\"\n");
		return 0;
	}
	
	/* Header was correct! */
	print("00: Found game_script at header\n");
	
	int offset = 13, i, j, auxNumber, line;
	int function_count, type_count, var_count;
	unsigned char op;
	
	function *actual;
	function *aux;
	functions * func_container = NULL;
	
	type * types = NULL, *auxtype = NULL;
	char * auxString;
	
	function_count = bytecode[offset++];
	
	char * function_names[255];
	
	if(verbose)
		fprintf(stdout, "%.2X: N. de funcions: %d\n", offset-1, function_count);
	
	/* Let's check the function headers */
	
	for(i=0; i<function_count; i++)
	{
		actual = malloc(sizeof(function));
		
		/* Let's retrieve the name */
		if(verbose)
			fprintf(stdout, "-- Funcio %d\n", i+1);
		auxNumber = readStringBytes((char *)(bytecode+offset), &(actual->name));
		if(verbose)
			printf("%.2X: Name and lenght occupy %d bytes\n",offset, auxNumber); 
		offset+=auxNumber;
		
		/* Done! Let's retrieve the types... */
		
		type_count = bytecode[offset++];
		if(verbose)
			printf("%.2X: Function %s has %d types.\n", offset-1, actual->name, type_count);
		actual->type_count = type_count;
		
		/* This reads all the types names */
		for(j=0; j<type_count; j++)
		{
			types = malloc(sizeof(type));
			if(auxtype)
			{
				auxtype->next = types;
			}
			auxNumber=readStringBytes((char *)(bytecode+offset), &(types->name));
			if(verbose)
					fprintf(stdout, "%.2X: Type %s\n", offset, types->name);
			offset+=auxNumber;
			auxtype = types;
		}
		
		actual->types = types;
		types = NULL;
		
		/* This will read the var count, still unimplemented */
		actual->var_count = 7;
		
		
		actual->id = bytecode[offset++];
		/* And this reads the Function ID */
		if(verbose)
			fprintf(stdout, "%.2X: Funcio %d: %s\n", offset-1, actual->id, actual->name);
		function_names[actual->id-1] = actual->name;
		
		func_container = malloc(sizeof(functions));
		func_container->value = actual;
		func_container->next = NULL;
		
		add_function(fgs, func_container);
		
		actual = NULL;
		func_container = NULL;
	}
	
	line = 0;
	
	for(i=0; i<function_count; i++)
	{
		line = offset;
		op = bytecode[offset++];
		actual = findFunctionByName(function_names[op-1], fgs_get_list(fgs));
		actual->start = bytecode+offset;
		actual->offset = offset-2-line;
		if(verbose)
			fprintf(stdout, "Code for function %s, starting at %X:\n\n", actual->name, (unsigned char)actual->offset);
			
		while(op != 0)
		{
			op = bytecode[offset++];
			switch(op)
			{
				case BYT_GOTO:
					if(verbose)
						fprintf(stdout, "%X: goto %X\n", offset-3-line, bytecode[offset++]);
					else
						offset++;
					break;
				case BYT_PUSHVAR:
					if(verbose)
						fprintf(stdout, "%X: pushvar %d\n", offset-3-line, bytecode[offset++]);
					else
						offset++;
					break;
				case BYT_PUSHI:
					if(verbose)
						fprintf(stdout, "%X: pushi %d\n", offset-3-line, *(int *)&bytecode[offset++]);
					else
						offset++;
					offset+=3;
					break;
				case BYT_PUSHF:
					if(verbose)
						fprintf(stdout, "%X: pushf %f\n", offset-3-line, *(float *)&bytecode[offset++]);
					else
						offset++;
					offset+=3;
					break;
				case BYT_PUSHS:
					offset+=readStringBytes((char *)(bytecode+offset), &(auxString))-1;
					if(verbose)
					{
						fprintf(stdout, "%X: pushs \"%s\"\n", offset-3-line, auxString);
					}
					free(auxString);
					auxString=NULL;
					break;
				case BYT_POPVAR:
					if(verbose)
						fprintf(stdout, "%X: pop %d\n", offset-3-line, bytecode[offset++]);
					else
						offset++;
					break;
				case BYT_I2S:
					if(verbose)
						fprintf(stdout, "%X: i2s\n", offset-3-line);
					break;
				case BYT_ADDI:
					if(verbose)
						fprintf(stdout, "%X: addi\n", offset-3-line);
					break;
				case BYT_SUBI:
					if(verbose)
						fprintf(stdout, "%X: subi\n", offset-3-line);
					break;
				case BYT_MULI:
					if(verbose)
						fprintf(stdout, "%X: muli\n", offset-3-line);
					break;
				case BYT_DIVI:
					if(verbose)
						fprintf(stdout, "%X: divi\n", offset-3-line);
					break;
				case BYT_ADDF:
					if(verbose)
						fprintf(stdout, "%X: addf\n", offset-3-line);
					break;
				case BYT_SUBF:
					if(verbose)
						fprintf(stdout, "%X: subf\n", offset-3-line);
					break;
				case BYT_MULF:
					if(verbose)
						fprintf(stdout, "%X: mulf\n", offset-3-line);
					break;
				case BYT_DIVF:
					if(verbose)
						fprintf(stdout, "%X: divf\n", offset-3-line);
					break;
				case BYT_ADDS:
					if(verbose)
						fprintf(stdout, "%X: adds\n", offset-3-line);
					break;
				case BYT_HALT:
					if(verbose)
						fprintf(stdout, "%X: return\n", offset-3-line);
					break;
				case BYT_EQ:
					if(verbose)
						fprintf(stdout, "%X: eq\n", offset-3-line);
					break;
				case BYT_NEQ:
					if(verbose)
						fprintf(stdout, "%X: neq\n", offset-3-line);
					break;
				case BYT_LTI:
					if(verbose)
						fprintf(stdout, "%X: lti\n", offset-3-line);
					break;
				case BYT_LEI:
					if(verbose)
						fprintf(stdout, "%X: lei\n", offset-3-line);
					break;
				case BYT_GTI:
					if(verbose)
						fprintf(stdout, "%X: gti\n", offset-3-line);
					break;
				case BYT_GEI:
					if(verbose)
						fprintf(stdout, "%X: gei\n", offset-3-line);
					break;
				default:
					if(verbose)
						fprintf(stdout, "%X: Unknown op %X\n", offset-2-line, op);
			}
		}
	}
	
	
}