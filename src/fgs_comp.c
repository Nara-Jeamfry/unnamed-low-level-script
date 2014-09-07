#include "fgs_comp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fgs_comp_symtab.h"

char * typeToString(int type)
{
	switch(type)
	{
		case STRINGT:
			return "string";
			break;
		case INTT:
			return "integer";
			break;
		case FLOATT:
			return "float-point";
			break;
		case BOOLT:
			return "boolean";
			break;
		default:
			return "unknown type";
			break;
	}
}

bytecode_entry *codeStart = NULL;
bytecode_entry *codeEnd = NULL;

function_entry *firstFunction = NULL;
function_entry *lastFunction = NULL;

C3A_value_container *firstLocal = NULL;
C3A_value_container *lastLocal = NULL;

C3A_value_container *firstType = NULL;
C3A_value_container *lastType = NULL;

unsigned int codeOffset = 0;
unsigned int localOffset = 1;
unsigned int typeOffset = 0;
unsigned char functionCount = 0;
unsigned int byteNumber;

int nextQuad()
{
	return codeOffset;
}

void cleanOp(bytecode_entry * byt)
{
	free(byt->val1);
	free(byt->val2);
	free(byt->val3);
	free(byt);
}

void cleanFunctions()
{
	function_entry * aux;
	printf("HOLAAAAAA?¿????\n");
	while(firstFunction)
	{
		printf("Cleaning function %s", firstFunction->identifier);
		bytecode_entry * auxbytec;
		while(firstFunction->first_code)
		{
			printf("Cleaning op %d", firstFunction->first_code->op);
			auxbytec = firstFunction->first_code->next;
			cleanOp(firstFunction->first_code);
			firstFunction->first_code = auxbytec;
		}
		aux = firstFunction->next;
		free(firstFunction);
		firstFunction = aux;
	}
}

void cleanMemory()
{	
	/*	cleanFunctions(); */

	codeStart = NULL;
	codeEnd = NULL;

	firstFunction = NULL;
	lastFunction = NULL;

	firstLocal = NULL;
	lastLocal = NULL;

	firstType = NULL;
	lastType = NULL;

	codeOffset = 0;
	localOffset = 1;
	typeOffset = 0;
	functionCount = 0;

}

C3A_value *tempLocation()
{
	C3A_value *aux = (C3A_value *)malloc(sizeof(C3A_value));
	aux->type = 0;
	aux->value.tempID = dataOffset++;
	
	C3A_value_container *existing_var = checkNewVar(aux, firstLocal);
	
	if(!existing_var)
	{
		fprintf(getDebugFile(), "Nova variable\n");
		C3A_value_container *newVar = (C3A_value_container *)malloc(sizeof(C3A_value_container));
		newVar->value = aux;
		newVar->id = localOffset++;
		char *auxName = (char *)malloc(sizeof(char)*14);
		sprintf(auxName, "$t%d", aux->value.tempID);
		newVar->name = auxName;
		newVar->next = NULL;
		
		if(firstLocal == NULL)
		{
			firstLocal = newVar;
			lastLocal = newVar;
		}
		else
		{
			lastLocal->next = newVar;
			lastLocal = newVar;
		}
		
		aux->container = newVar;
	}
	else
	{
		aux->container = existing_var;
	}
	 
	return aux;
}

C3A_value *varLocation(char * identifier)
{
	C3A_value *aux = (C3A_value *)malloc(sizeof(C3A_value));
	aux->value.varName = identifier;
	aux->type = 1;
		
	C3A_value_container *existing_var = checkNewVar(aux, firstLocal);
	
	if(!existing_var)
	{
		fprintf(getDebugFile(), "Nova variable\n");
		C3A_value_container *newVar = (C3A_value_container *)malloc(sizeof(C3A_value_container));
		newVar->value = aux;
		newVar->id = localOffset++;
		newVar->name = identifier;
		newVar->next = NULL;
		
		if(firstLocal == NULL)
		{
			firstLocal = newVar;
			lastLocal = newVar;
		}
		else
		{
			lastLocal->next = newVar;
			lastLocal = newVar;
		}
		
		aux->container = newVar;
	}
	else
	{
		aux->container = existing_var;
	}
	
	return aux;
}

C3A_value *litLocationInt(int i)
{
	C3A_value *aux = (C3A_value *)malloc(sizeof(C3A_value));
	aux->value.literalI = i;
	aux->type = 2;
	codeOffset+=3;
	return aux;
}

C3A_value *litLocationFloat(float f)
{
	C3A_value *aux = (C3A_value *)malloc(sizeof(C3A_value));
	aux->value.literalF = f;
	aux->type = 3;
	codeOffset+=3;
	return aux;
}

C3A_value *litLocationString(char *word)
{
	C3A_value *aux = (C3A_value *)malloc(sizeof(C3A_value));
	aux->value.literalS = (char *)malloc(strlen(word));
	strcpy(aux->value.literalS, word);
	aux->type = 4;
	codeOffset+=strlen(aux->value.literalS);
	return aux;
}

void addType(char * typeName)
{
	C3A_value *type = (C3A_value *)malloc(sizeof(C3A_value));
	type->value.type = typeName;
	type->type = 5;
	
	C3A_value_container *existing_type = checkNewVar(type, firstType);
	
	if(!existing_type)
	{
		fprintf(getDebugFile(), "Nova variable\n");
		C3A_value_container *newVar = (C3A_value_container *)malloc(sizeof(C3A_value_container));
		newVar->value = type;
		typeOffset++;
		newVar->name = typeName;
		newVar->next = NULL;
		
		if(firstType == NULL)
		{
			firstType = newVar;
			lastType = newVar;
		}
		else
		{
			lastType->next = newVar;
			lastType = newVar;
		}
		
		type->container = newVar;
	}
	else
	{
		type->container = existing_type;
	}
}

bytecode_entry *gen_code()
{
	bytecode_entry* newQuad = (bytecode_entry *)malloc(sizeof(bytecode_entry));
	newQuad->gotoL = -1;
	newQuad->next = NULL;
	if(codeStart == NULL)
	{
		codeStart = newQuad;
		codeEnd = newQuad;
	}
	else
	{
		codeEnd->next = newQuad;
		codeEnd = newQuad;
	}
	codeOffset++;
	return newQuad;
}

bytecode_entry *gen_code_op(INST_SET op)
{
	bytecode_entry* newQuad = (bytecode_entry *)malloc(sizeof(bytecode_entry));
	newQuad->op = op;
	newQuad->gotoL = -1;
	newQuad->next = NULL;
	
	if(codeStart == NULL)
	{
		codeStart = newQuad;
		codeEnd = newQuad;
	}
	else
	{
		codeEnd->next = newQuad;
		codeEnd = newQuad;
	}
	
	switch(op)
	{
		case GOTO:
			fprintf(getDebugFile(), "Added goto at code_offset %d\n", codeOffset);
			codeOffset+=GOTO_OFFSET;
			break;
		case IF_OP:
			fprintf(getDebugFile(), "Added if at code_offset %d\n", codeOffset);
			codeOffset+=IF_OP_OFFSET;
			break;
		case CALL:
			fprintf(getDebugFile(), "Added call at code_offset %d\n", codeOffset);
			codeOffset+=CALL_OFFSET;
			break;
		case INPUT_PARAM:
			fprintf(getDebugFile(), "Added input_param at code_offset %d\n", codeOffset);
			codeOffset+=INPUT_PARAM_OFFSET;
			break;
		case ASSIGNMENT:
			fprintf(getDebugFile(), "Added assignment at code_offset %d\n", codeOffset);
			codeOffset+=ASSIGNMENT_OFFSET;
			break;
		case ASSIGNMENT_UN:
			fprintf(getDebugFile(), "Added unary assignment at code_offset %d\n", codeOffset);
			codeOffset+=ASSIGNMENTUN_OFFSET;
			break;
		case ASSIGNMENT_OP:
			fprintf(getDebugFile(), "Added operated assignment at code_offset %d\n", codeOffset);
			codeOffset+=ASSIGNMENTOP_OFFSET;
			break;
		case RETURN_OP:
			fprintf(getDebugFile(), "Added return at code_offset %d\n", codeOffset);
			codeOffset+=RETURN_OFFSET;
			break;
		case HALT:
			fprintf(getDebugFile(), "Added halt at code_offset %d\n", codeOffset);
			codeOffset+=HALT_OFFSET;
			break;
		default:
			fprintf(getDebugFile(), "Added op at code_offset %d\n", codeOffset);
			codeOffset++;
			break;
	}
	return newQuad;
}

void copyValue(C3A_value * source, C3A_value * dest)
{
	if(source == NULL || dest == NULL)
	{
		printf("Cannot copy variable value.");
		dest = NULL;
		exit(5);
	}
	dest->type = source->type;
	

	switch(dest->type)
	{
		case 0:
			dest->value.tempID = source->value.tempID;
			break;
		case 1:
			dest->value.varName = malloc(strlen(source->value.varName));
			if(dest->value.varName == NULL)
			{
				exit(5);
			}
			strcpy(source->value.varName, dest->value.varName);
			break;
		case 2:
			dest->value.literalI = source->value.literalI;
			break;
		case 3:
			dest->value.literalF = source->value.literalF;
			break;
		case 4:
			dest->value.literalS = malloc(strlen(source->value.literalS));
			if(dest->value.literalS == NULL)
			{
				exit(5);
			}
			strcpy(source->value.literalS, dest->value.literalS);
			break;
		case 5:
			dest->value.type = malloc(strlen(source->value.type));
			if(dest->value.type == NULL)
			{
				exit(5);
			}
			strcpy(source->value.type, dest->value.type);
			break;
			
	}
	
	dest->container = source->container;
}

C3A_value * duplicate_entry(C3A_value * var)
{
	C3A_value * result = malloc(sizeof(C3A_value));
	
	copyValue(var, result);
	
	return result;
}

void backpatch(BP_list* list, int gotoL)
{
	if(list != NULL)
	{
		BP_list* temp;
		while(list)
		{
			if(list->entry != NULL)
			{
				list->entry->gotoL = gotoL;
			}
			temp = list;
			list = list->next;
			free(temp);
		}
	}
}

BP_list* mergeLists(BP_list* a, BP_list* b)
{
	if(a != NULL && b != NULL)
	{
		BP_list *temp = a;
		while(a->next)
		{
			a = a->next;
		}
		a->next = b;
		return temp;
	}
	else if(a != NULL)
	{
		return a;
	}
	else if(b != NULL)
	{
		return b;
	}
	else
		return NULL;
}

BP_list* addToList(BP_list* list, bytecode_entry* entry)
{
	if(entry == NULL)
		return list;
	
	if(list == NULL)
	{
		BP_list* newList = malloc(sizeof(BP_list));
		newList->entry = entry;
		newList->next = NULL;
		return newList;
	}
	else
	{
		BP_list* newListEntry = malloc(sizeof(BP_list)), *temp = list;
		newListEntry->entry = entry;
		newListEntry->next=NULL;
		while(list->next)
		{
			list = list->next;
		}
		list->next = newListEntry;
		return temp;
	}
}

void saveFunction(char * identifier)
{
	function_entry *new = malloc(sizeof(function_entry));
	
	new->identifier = identifier;
	new->first_code = codeStart;
	new->last_code = codeEnd;
	new->length = codeOffset;
	new->locals = firstLocal;
	new->localLength = localOffset-1;
	new->typeLength = typeOffset;
	new->types = firstType;
	new->next = NULL;
	
	codeStart = NULL;
	codeEnd = NULL;
	firstLocal = NULL;
	lastLocal = NULL;
	firstType = NULL;
	lastType = NULL;
	codeOffset = 0;
	localOffset = 1;
	typeOffset = 0;
	functionCount++;

	if(firstFunction == NULL)
	{
		firstFunction = new;
		lastFunction = new;
	}
	else
	{
		lastFunction->next = new;
		lastFunction = new;
	}
}
	
FILE *getCodeFile()
{
	if(codeFile == 0)
	{
		openCodeFile();
	}
	return codeFile;
}

FILE *getByteCodeFile()
{
	if(byteCodeFile == 0)
	{
		openByteCodeFile();
	}
	return byteCodeFile;
}

FILE *getDebugFile()
{
	if(debugFile == 0)
	{
		openDebugFile();
	}
	return debugFile;
}

void openDebugFile()
{
	debugFile = fopen("log.txt", "w");
	if(debugFile == NULL)
	{
		fprintf(stdout, "Cannot open log file!\n");
		exit(2);
	}
}

void openByteCodeFile()
{
	byteCodeFile = fopen(byteCodeName, "wb");
	if(byteCodeFile == NULL)
	{
		fprintf(stdout, "Cannot open ByteCode file!\n");
		exit(2);
	}
}

void openCodeFile()
{
	codeFile = fopen("code.c3a", "w");
	if(codeFile == NULL)
	{
		fprintf(stdout, "Cannot open code file!\n");
		exit(2);
	}
}

void closeFiles()
{
	if(codeFile != NULL)
	if(fclose(codeFile)==EOF)
	{
		printf("Strange error ocurred while closing Code File.\n");
	}
	if(debugFile != NULL)
	if(fclose(debugFile)==EOF)
	{
		printf("Strange error ocurred while closing Debug File.\n");
	}
	if(byteCodeFile != NULL)
	if(fclose(byteCodeFile)==EOF)
	{
		printf("Strange error ocurred while closing ByteCode File.\n");
	}
	codeFile = NULL;
	debugFile = NULL;
	byteCodeFile = NULL;
}

void writeByte(FILE * fi, char text)
{
	fprintf(getDebugFile(), "Wrote byte #%X with content %X (%c).\n", byteNumber++,text,text);
	fwrite(&text, 1, 1, fi);
}

void writeByteInt(FILE * fi, int i)
{
	fprintf(getDebugFile(), "Wrote bytes #%X-%X with content %X (int %d).\n", byteNumber, byteNumber+3, i, i);
	byteNumber+=4;
	fwrite(&i, 4, 1, fi);
}

void writeByteFloat(FILE * fi, float f)
{
	fprintf(getDebugFile(), "Wrote bytes #%X-%X with content %X (float %f).\n", byteNumber, byteNumber+3, *(unsigned int*)&f, f);
	byteNumber+=4;
	fwrite(&f, 4, 1, fi);
}

void writeStringBytes(FILE * fi, char * text)
{
	if(text == NULL)
		return;

	char length = strlen(text);
	
	int i = 0;
	writeByte(fi, length);
	while(i<length)
	{
		writeByte(fi, text[i]);
		i++;
	}
}

void printHeaderByteCode(FILE * fi)
{
	writeByte(fi, 'g');
	writeByte(fi, 'a');
	writeByte(fi, 'm');
	writeByte(fi, 'e');
	writeByte(fi, '_');
	writeByte(fi, 's');
	writeByte(fi, 'c');
	writeByte(fi, 'r');
	writeByte(fi, 'i');
	writeByte(fi, 'p');
	writeByte(fi, 't');
	
	char major_version = 0, minor_version = 3;
	writeByte(fi, minor_version);
	writeByte(fi, major_version);
}

void printByteCode(FILE * fi)
{
	fprintf(getDebugFile(), "\n\n--- Printing ByteCode file... ---\n");

	printHeaderByteCode(fi);
	
	bytecode_entry *line = NULL;
	function_entry *section = firstFunction;
	C3A_value_container *var = NULL;
	char typeCount = 0;
	headerLength = 13;
	opsLength = 0;
	
	char functionID = 0;
	fprintf(getDebugFile(), "Header: %d\n", headerLength);
	
	headerLength++;
	writeByte(fi, functionCount);
	fprintf(getDebugFile(), "Function Count: %d\n", headerLength);
	
	while(section)
	{
		headerLength += 1;
		fprintf(getDebugFile(), "Function name char count: %d\n", headerLength);
		headerLength += strlen(section->identifier);
		fprintf(getDebugFile(), "Function name: %d\n", headerLength);
		
		
		var = section->types;
		headerLength++;
		fprintf(getDebugFile(), "Type Count: %d\n", headerLength);
		
		while(var)
		{
			typeCount++;
			headerLength+= 1 + strlen(var->name);
			fprintf(getDebugFile(), "Type name: %d\n", headerLength);
			
			var = var->next;
		}
		
		headerLength++;
		fprintf(getDebugFile(), "Function count: %d\n", headerLength);
		
		headerLength++;
		fprintf(getDebugFile(), "Function ID: %d\n", headerLength);
		
		section = section->next;
	}
	
	section = firstFunction;
	fprintf(getDebugFile(), "Header: %d\n", headerLength);
	
	while(section)
	{
		writeStringBytes(fi, section->identifier);
		
		writeByte(fi, (char)section->typeLength);
		var = section->types;
		while(var)
		{
			writeStringBytes(fi, var->name);
			
			var = var->next;
		} 
		
		writeByte(fi, section->localLength);
		
		writeByte(fi, ++functionID);
		
		section = section->next;
	}
	
	if(bisonverbose)
		fprintf(stdout, "Total header space: %d\n", headerLength);
	fprintf(getDebugFile(), "Total header space: %d\n", headerLength);
	
	functionID = 0;
	
	section = firstFunction;
	
	while(section)
	{
		line = section->first_code;
		
		writeByte(fi, ++functionID);
		
		while(line)
		{
			printByteCodeOp(fi, line, headerLength);
			
			line = line->next;
			/* lineNumber++; */
		}
		
		opsLength+=section->length+1;
		
		section = section->next;
	}
}

void printByteCodeOp(FILE * fi, bytecode_entry *line, char length)
{
	switch(line->op)
	{
		case INPUT_PARAM:
			printPopVar(fi, line->val1);
			break;
		case HALT:
			writeByte(fi, BYT_HALT);
			break;
		case CALL:
			writeByte(fi, BYT_CALL);
			writeStringBytes(fi, line->val1->value.literalS);
			break;
		case PARAM:
			printPushVar(fi, line->val1);
			break;
		case RETURN_OP:
			writeByte(fi, BYT_HALR);
			printByteCodeVar(fi, line->val1);
			break;
		case IF_OP:
			printPushVar(fi, line->val1);
			printPushVar(fi, line->val2);
			printIfByteCode(fi, line);
			printGoto(fi, line);
			break;
		case ASSIGNMENT:
			printPushVar(fi, line->val2);
			printPopVar(fi, line->val1);
			break;
		case ASSIGNMENT_UN:
			printByteCodeOpRel(fi, line);
			printPopVar(fi, line->val1);
			break;
		case ASSIGNMENT_OP:
			printByteCodeOpRel(fi, line);
			printPopVar(fi, line->val1);
			break;
		case GOTO:
			printGoto(fi, line);
			break;
		default:
			writeByte(fi, 255);
	}
}

void printByteCodeOpRel(FILE * fi, bytecode_entry *op)
{
	switch(op->oprel)
	{
		case ADDI:
			printPushVar(fi, op->val2);
			printPushVar(fi, op->val3);
			writeByte(fi, BYT_ADDI);
			break;
		case ADDF:
			printPushVar(fi, op->val2);
			printPushVar(fi, op->val3);
			writeByte(fi, BYT_ADDF);
			break;
		case ADDS:
			printPushVar(fi, op->val2);
			printPushVar(fi, op->val3);
			writeByte(fi, BYT_ADDS);
			break;
		case SUBI:
			printPushVar(fi, op->val2);
			printPushVar(fi, op->val3);
			writeByte(fi, BYT_SUBI);
			break;
		case SUBF:
			printPushVar(fi, op->val2);
			printPushVar(fi, op->val3);
			writeByte(fi, BYT_SUBF);
			break;
		case MULI:
			printPushVar(fi, op->val2);
			printPushVar(fi, op->val3);
			writeByte(fi, BYT_MULI);
			break;
		case MULF:
			printPushVar(fi, op->val2);
			printPushVar(fi, op->val3);
			writeByte(fi, BYT_MULF);
			break;
		case DIVI:
			printPushVar(fi, op->val2);
			printPushVar(fi, op->val3);
			writeByte(fi, BYT_DIVI);
			break;
		case DIVF:
			printPushVar(fi, op->val2);
			printPushVar(fi, op->val3);
			writeByte(fi, BYT_DIVF);
			break;
		case I2F:
			printPushVar(fi, op->val2);
			writeByte(fi, BYT_I2F);
			break;
		case I2S:
			printPushVar(fi, op->val2);
			writeByte(fi, BYT_I2S);
			break;
		case F2I:
			printPushVar(fi, op->val2);
			writeByte(fi, BYT_F2I);
			break;
		case F2S:
			printPushVar(fi, op->val2);
			writeByte(fi, BYT_F2S);
			break;
		default:
			return;
	}
}

void printPopVar(FILE * fi, C3A_value *var)
{	
	if(var == NULL)
	{
		return;
	}
	switch(var->type)
	{
		case VAL_TEMP:
			writeByte(fi, BYT_POPVAR);
			writeByte(fi, var->container->id);
			break;
		case VAL_SYMTAB:
			writeByte(fi, BYT_POPVAR);
			writeByte(fi, var->container->id);
			break;
		default:
			break;
	}
}

void printPushVar(FILE * fi, C3A_value *var)
{
	if(var == NULL)
	{
		return;
	}
	switch(var->type)
	{
		case VAL_TEMP:
			writeByte(fi, BYT_PUSHVAR);
			writeByte(fi, var->container->id);
			break;
		case VAL_SYMTAB:
			writeByte(fi, BYT_PUSHVAR);
			writeByte(fi, var->container->id);
			break;
		case VAL_INTL:
			writeByte(fi, BYT_PUSHI);
			writeByteInt(fi, var->value.literalI);
			break;
		case VAL_FLOATL:
			writeByte(fi, BYT_PUSHF);
			writeByteFloat(fi, var->value.literalF);
			break;
		case VAL_STRINGL:
			writeByte(fi, BYT_PUSHS);
			writeStringBytes(fi, var->value.literalS);
			break;
		case VAL_TYPE:
			break;
		default:
			break;
	}
}

void printByteCodeVar(FILE * fi, C3A_value *var)
{	
	if(var == NULL)
	{
		return;
	}
	switch(var->type)
	{
		case VAL_TEMP:
			writeByte(fi, var->container->id);
			break;
		case VAL_SYMTAB:
			writeByte(fi, var->container->id);
			break;
		case VAL_INTL:
			writeByteInt(fi, var->value.literalI);
			break;
		case VAL_FLOATL:
			writeByteFloat(fi, var->value.literalF);
			break;
		case VAL_STRINGL:
			writeStringBytes(fi, var->value.literalS);
			break;
		case VAL_TYPE:
			break;
		default:
			break;
	}
}

void printGoto(FILE * fi, bytecode_entry *op)
{
	writeByte(fi, BYT_GOTO);
	writeByte(fi, (char)op->gotoL/* +headerLength+opsLength */);
}

void printIfByteCode(FILE * fi, bytecode_entry *op)
{
	

	switch(op->oprel)
	{
		case LTI:
			writeByte(fi, BYT_LTI);
			break;
		case LEI:
			writeByte(fi, BYT_LEI);
			break;
		case GTI:
			writeByte(fi, BYT_GTI);
			break;
		case GEI:
			writeByte(fi, BYT_GEI);
			break;
		case LTF:
			writeByte(fi, BYT_LTF);
			break;
		case LEF:
			writeByte(fi, BYT_LEF);
			break;
		case GTF:
			writeByte(fi, BYT_GTF);
			break;
		case GEF:
			writeByte(fi, BYT_GEF);
			break;
		case EQ_OP:
			writeByte(fi, BYT_EQ);
			break;
		case NE_OP:
			writeByte(fi, BYT_NEQ);
			break;
		default:
		return;
	}
}

void printCode(FILE * fi)
{
	bytecode_entry *line = NULL;
	function_entry *section = firstFunction;
	C3A_value_container *var = NULL;
	char * auxtext;
	
	int lineNumber = 0, res;
	
	headerLength = opsLength = 0;
	int codeLength = 0;
	
	if(fprintf(fi, "Bytecode---\n") < 0)
	{
		perror("An error ocurred:");
		return;
	}
	
	while(section)
	{
		headerLength += 1;
		headerLength += section->localLength + section->typeLength;
		section = section->next;
	}
	
	fprintf(fi, "%d: Header length: %d\n", lineNumber++, ++headerLength);
	section = firstFunction;
	
	while(section)
	{
		res = fprintf(fi, "%d: Function %s at @%d\n", lineNumber++, section->identifier, headerLength+codeLength);
		codeLength+=section->length;
		
		var = section->types;
		while(var)
		{
			res = fprintf(fi, "%d: Argument of type %s\n", lineNumber++, var->name);
			
			var = var->next;
		}
		
		var = section->locals;
		
		while(var)
		{
			res = fprintf(fi, "%d: Variable %s as #%d\n", lineNumber++, var->name, var->id);
		
			var = var->next;
		}
	
		section = section->next;
	}
	
	section = firstFunction;
	
	lineNumber = 45;
	headerLength = 45;
	
	while(section)
	{
		line = section->first_code;
		
		while(line)
		{
			auxtext = malloc(sizeof(char)*100);

			printOp(line, &lineNumber, auxtext);

			res = fprintf(fi, "%s\n", auxtext);
			
			free(auxtext);
	
			if(res <0)
			{
				perror("An error ocurred:");
				
				return;
			}
			
			line = line->next;
			/* lineNumber++; */
		}
		
		opsLength += section->length;
		section = section->next;
	}
}

char *printOp(bytecode_entry *op, int *lineNumber, char * result)
{
	char * aux;
	int auxlines = 0;
	
	switch(op->op)
	{
		case IF_OP:
			sprintf(result, "-%X: %s\n-%X: %s\n-%X: %s \n-%X: %s \n-%X: %s\n-%X: GOTO\n-%X: #%X", (*lineNumber),
											"push",
											(*lineNumber)+1,
											printC3AVal(op->val1, &auxlines),
											(*lineNumber)+2,
											"push",
											(*lineNumber)+3,
											printC3AVal(op->val2, &auxlines),
											(*lineNumber)+4,
											printRelOp(op->oprel),
											(*lineNumber)+5,
											(*lineNumber)+6,
											op->gotoL+headerLength+opsLength);
			(*lineNumber)+=IF_OP_OFFSET + auxlines;
			return result;
		break;
		case GOTO:
			sprintf(result, "-%X: GOTO\n-%X: #%X", (*lineNumber), 
											(*lineNumber)+1,
											op->gotoL+headerLength+opsLength);
			(*lineNumber)+=GOTO_OFFSET;
			return result;
		break;
		case INPUT_PARAM:
			sprintf(result, "%X: INPUT_PARAM\n%X: #%s", (*lineNumber),
											(*lineNumber)+1,
											printC3AVal(op->val1, &auxlines));
			(*lineNumber)+=INPUT_PARAM_OFFSET;
			return result;
		break;
		case RETURN_OP:
			sprintf(result, "%X: RETURN\n%X: #%s", (*lineNumber), *lineNumber+1, printC3AVal(op->val1, &auxlines));
			(*lineNumber)+=RETURN_OFFSET + auxlines;
			return result;
		break;
		case ASSIGNMENT:
			sprintf(result, "%X: %s := %s", (*lineNumber), 
											printC3AVal(op->val1, &auxlines), 
											printC3AVal(op->val2, &auxlines));
			(*lineNumber)+=ASSIGNMENT_OFFSET + auxlines;
			return result;
		break;
		case ASSIGNMENT_OP:
			sprintf(result, "%X: %s := %s %s %s", (*lineNumber), 
											printC3AVal(op->val1, &auxlines), 
											printC3AVal(op->val2, &auxlines),
											printRelOp(op->oprel),
											printC3AVal(op->val3, &auxlines));
			(*lineNumber)+=ASSIGNMENTOP_OFFSET + auxlines;
			return result;
		break;
		case ASSIGNMENT_UN:
			sprintf(result, "%X: %s := %s %s", (*lineNumber), printC3AVal(op->val1, &auxlines),
											printRelOp(op->oprel),
											printC3AVal(op->val2, &auxlines));
			(*lineNumber)+=ASSIGNMENTUN_OFFSET + auxlines;
			return result;
		break;
		case PARAM:
			aux = printC3AVal(op->val1, &auxlines);
			sprintf(result, "%X: PARAM %s", (*lineNumber), 
											aux);
			(*lineNumber)+=1 + auxlines;
			return result;
		break;
		case CALL:
			sprintf(result, "%X: CALL\n%X: @%s", (*lineNumber), 
											(*lineNumber)+1, 
											printC3AVal(op->val1, &auxlines));
			(*lineNumber)+=CALL_OFFSET + auxlines;
			return result;
		break;
		case HALT:
			sprintf(result, "-%X: HALT", (*lineNumber));
			(*lineNumber)+=HALT_OFFSET;
			return result;
		break;
		default:
			return NULL;
		break;
	}
	return "HAHAHA";
}

char *printC3AVal(C3A_value *value, int *lineNumber)
{
	char *aux;
	if(value == NULL)
	{
		return NULL;
	}
	switch(value->type)
	{
		case 0:
			aux = malloc(sizeof(char)*7);
			sprintf(aux, "#%d", value->container->id);
			/* sprintf(aux, "$t%02d", value->value.tempID); */
			return aux;
		break;
		case 1:
			aux = malloc(sizeof(char) * 11);
			sprintf(aux, "#%d", value->container->id);
			return aux;
		break;
		case 2:
			aux = malloc(sizeof(char) * 11);
			sprintf(aux, "%d", value->value.literalI);
			(*lineNumber)+=3;
			return aux;
		break;
		case 3:
			aux = malloc(sizeof(char) * 100);
			sprintf(aux, "%.2f", value->value.literalF);
			(*lineNumber)+=3;
			return aux;
		break;
		case 4:
			aux = malloc(sizeof(char) * strlen(value->value.literalS)+4);
			sprintf(aux, "\"%s\"", value->value.literalS);
			if(value->value.literalS == NULL)
			{
				return NULL;
			}
			(*lineNumber)+=strlen(value->value.literalS)+1;
			return aux;
		break;
		default:
			return NULL;
		break;
	}
	return "HEHEHE";
}

C3A_value_container *checkNewVar(C3A_value *var, C3A_value_container *locals) /* 0 if new var, container pointer otherwise */
{
	C3A_value_container *aux_locals = locals;
	C3A_value_container *found = NULL;

	fprintf(getDebugFile(), "Checking new variable\n");
	while(aux_locals && !found)
	{
		if(var->type == 1)
		{
			fprintf(getDebugFile(), "Comparing names: %s and %s\n", var->value.varName, aux_locals->name);
			if(!strcmp(var->value.varName, aux_locals->name))
			{
				found = aux_locals;
			}
		}
		else if(var->type == 0)
		{
			char* aux = malloc(sizeof(char)*12);
			sprintf(aux, "$t%d", var->value.tempID);
			fprintf(getDebugFile(), "Comparing temps: %s and %s\n", aux, aux_locals->name);
			if(!strcmp(aux, aux_locals->name))
			{
				found = aux_locals;
			}
		}
		aux_locals = aux_locals->next;
	}
	
	return found;
}

char *printRelOp(REL_INST_SET relop)
{
	switch(relop)
	{
		case CHSI:
			return "CHSI";
		break;
		case CHSF:
			return "CHSF";
		break;
		case I2F:
			return "I2F";
		break;
		case I2S:
			return "I2S";
			break;
		case F2I:
			return "I2F";
		break;
		case F2S:
			return "F2S";
			break;
		case ADDI:
			return "ADDI";
		break;
		case SUBI:
			return "SUBI";
		break;
		case MULI:
			return "MULI";
		break;
		case DIVI:
			return "DIVI";
		break;
		case ADDF:
			return "ADDF";
		break;
		case SUBF:
			return "SUBF";
		break;
		case MULF:
			return "MULF";
		break;
		case DIVF:
			return "DIVF";
		break;
		case ADDS:
			return "ADDS";
			break;
		case EQ_OP:
			return "EQ";
		break;
		case NE_OP:
			return "NE";
		break;
		case LTI:
			return "LTI";
		break;
		case LEI:
			return "LEI";
		break;
		case GTI:
			return "GTI";
		break;
		case GEI:
			return "GEI";
		break;
		case LTF:
			return "LTF";
		break;
		case LEF:
			return "LEF";
		break;
		case GTF:
			return "GTF";
		break;
		case GEF:
			return "GEF";
		break;
		default:
			return NULL;
		break;
	}
	return "HIHIHI";
}

void printDebug(const char *errlog)
{
	if(bisonverbose)
		printf(errlog);
}

void printError(const char * formatted_message, char * error_text)
{
	char * errlog;
	errlog = malloc(sizeof(char) * (strlen(formatted_message)+strlen(error_text)));
	sprintf(errlog, formatted_message, error_text);
	yyerror(errlog);
}

void printError2(const char * formatted_message, char * error_text, char * error_text_2)
{
	char * errlog;
	errlog = malloc(sizeof(char) * (strlen(formatted_message)+strlen(error_text)+strlen(error_text_2)));
	sprintf(errlog, formatted_message, error_text, error_text_2);
	yyerror(errlog);
}

char * printInmediateType(struct liter data)
{
	char * text = typeToString(data.type);
	char * result = malloc(sizeof(char)*strlen(text));
	strcpy(result, text);
	return result;
}

char * printValue(struct liter data)
{
	char * result;
	if(data.type == STRINGT)
	{
		result = malloc(sizeof(char) * (strlen(data.value.string_value)+2));
		strcpy(result, "\"");
		strcat(result, data.value.string_value);
		strcat(result, "\"");
		return result;
	}
	else if(data.type == INTT)
	{
		result = malloc(sizeof(char) * 11);
		sprintf(result, "%d", data.value.int_value);
	}
	else if(data.type == FLOATT)
	{
		result = malloc(sizeof(char) * 100);
		sprintf(result, "%.2f", data.value.float_value);
	}
	else if(data.type == BOOLT)
	{
		result = malloc(sizeof(char) * 5);
		if(data.value.bool_value == 0)
			sprintf(result, "false");
		else
			sprintf(result, "true");
	}
	else
	{
		return "ERROR_VALUE";
	}
	return result;
}

char * printVariableType(struct varia data)
{
	char * text = typeToString(data.type);
	char * result = malloc(sizeof(char)*strlen(text));
	strcpy(result, text);
	return result;
}

char * printVariableValue(struct varia data)
{
	char * result;
	if(data.type == STRINGT)
	{
		result = malloc(sizeof(char) * (strlen(data.value.string_value)+2));
		strcpy(result, "\"");
		strcat(result, data.value.string_value);
		strcat(result, "\"");
		return result;
	}
	else if(data.type == INTT)
	{
		result = malloc(sizeof(char) * 11);
		sprintf(result, "%d", data.value.int_value);
	}
	else if(data.type == FLOATT)
	{
		result = malloc(sizeof(char) * 100);
		sprintf(result, "%.2f", data.value.float_value);
	}
	else if(data.type == BOOLT)
	{
		result = malloc(sizeof(char) * 5);
		if(data.value.bool_value == 0)
			sprintf(result, "false");
		else
			sprintf(result, "true");
	}
	else
	{
		return "ERROR_VALUE";
	}
	return result;
}

int canIOperateThem(struct liter a, struct liter b, int op)
{

	if((a.type == STRINGT) || (b.type == STRINGT))
	{
		if(op!=SUMA)
			return -1;
		else
			return STRINGT;
	}
	if((a.type == INTT) || (b.type == INTT))
	{
		if((a.type == FLOATT && b.type == INTT) || (b.type == FLOATT && a.type == INTT))
			return FLOATT;
		else if((a.type == BOOLT) || (b.type == BOOLT))
			return -1;
		else
			return INTT;
	}
	if((a.type == FLOATT) && (b.type==FLOATT))
	{
		return FLOATT;
	}
	if((a.type == BOOLT) && (b.type == BOOLT))
	{
		if(op == ANDOP || op == OROP)
		{
			return BOOLT;
		}
	}
	return -1;
}

int compareValues(struct liter a, struct liter b)
{
	int result = INCOMPAT;
	
	if((a.type == INTT || a.type == FLOATT) && (b.type == INTT || b.type == FLOATT))
	{
		float aval, bval;
		if(a.type == INTT)
			aval = (float)a.value.int_value;
		else
			aval = a.value.float_value;
			
		if(b.type == INTT)
			bval = (float)b.value.int_value;
		else
			bval = b.value.float_value;
		
		if(aval < bval)
			result = LESS;
		else if(aval == bval)
			result = EQUAL;
		else
			result = GREAT;
	}
	
	return result;
}

struct liter operateValues(struct liter a, struct liter b, int op)
{
	struct liter result;
	int endtype = canIOperateThem(a, b, op);
	result.type = endtype;
	if(endtype == STRINGT)
	{
		if(a.type == STRINGT)
		{
			char * append;
			if(b.type == INTT)
			{
				append = malloc(sizeof(char) * 11);
				sprintf(append, "%d", b.value.int_value);
			}
			else if(b.type == FLOATT)
			{
				append = malloc(sizeof(char) * 100);
				sprintf(append, "%.2f", b.value.float_value);
			}
			else if(b.type == BOOLT)
			{
				append = malloc(sizeof(char) * 5);
				sprintf(append, "%s", (b.value.bool_value == 0) ? "false" : "true");
			}
			else
			{
				append = b.value.string_value;
			}
			result.value.string_value = malloc(sizeof(char) * (strlen(a.value.string_value) + strlen(append)));
			strcpy(result.value.string_value, a.value.string_value);
			strcat(result.value.string_value, append);
		}
		else
		{
			char * append;
			if(a.type == INTT)
			{
				append = malloc(sizeof(char) * 11);
				sprintf(append, "%d", a.value.int_value);
			}
			else if(a.type == FLOATT)
			{
				append = malloc(sizeof(char) * 100);
				sprintf(append, "%.2f",a.value.float_value);
			}
			else if(a.type == BOOLT)
			{
				append = malloc(sizeof(char) * 5);
				sprintf(append, "%s", (a.value.bool_value == 0) ? "false" : "true");
			}
			else
			{
				append = a.value.string_value;
			}
			result.value.string_value = malloc(sizeof(char) * (strlen(b.value.string_value) + strlen(append)));
			strcpy(result.value.string_value, append);
			strcat(result.value.string_value, b.value.string_value);
		}
	}
	else if(endtype == INTT)
	{
		switch(op)
		{
			case SUMA:
				result.value.int_value = a.value.int_value + b.value.int_value;
				break;
			case REST:
				result.value.int_value = a.value.int_value - b.value.int_value;
				break;
			case MULT:
				result.value.int_value = a.value.int_value * b.value.int_value;
				break;
			case DIVIS:
				result.value.int_value = a.value.int_value / b.value.int_value;
				break;
			default:
				result.value.int_value = a.value.int_value + b.value.int_value;
				break;
		}
	}
	else if(endtype == FLOATT)
	{
		float aval, bval;
		if(a.type == INTT)
		{
			aval = (float)a.value.int_value;
			bval = b.value.float_value;
		}
		else if (b.type == INTT)
		{
			bval = (float)b.value.int_value;
			aval = a.value.float_value;
		}
		else
		{
			aval = a.value.float_value;
			bval = b.value.float_value;
		}

		switch(op)
		{
			case SUMA:
				result.value.float_value = aval + bval;
				break;
			case REST:
				result.value.float_value = aval - bval;
				break;
			case MULT:
				result.value.float_value = aval * bval;
				break;
			case DIVIS:
				result.value.float_value = aval / bval;
				break;
			default:
				result.value.float_value = aval + bval;
				break;
		}
	}
	return result;
}

struct liter fromVarToLit(struct varia data)
{
	struct liter result;
	
	result.type = data.type;
	switch(data.type)
	{
		case INTT:
			result.value.int_value = data.value.int_value;
			break;
		case FLOATT:
			result.value.float_value = data.value.float_value;
			break;
		case STRINGT:
			result.value.string_value = malloc(sizeof(char) * strlen(data.value.string_value));
			strcpy(result.value.string_value,data.value.string_value);
			break;
		case BOOLT:
			result.value.bool_value = data.value.bool_value;
			break;
		default:
			break;
	}
	
	return result;
}

struct varia fromLitToVar(struct liter data, char * id)
{
	struct varia result;
	
	result.identifier = malloc(sizeof(char) * strlen(id));
	strcpy(result.identifier,id);
	result.type = data.type;
	switch(data.type)
	{
		case INTT:
			result.value.int_value = data.value.int_value;
			break;
		case FLOATT:
			result.value.float_value = data.value.float_value;
			break;
		case STRINGT:
			result.value.string_value = malloc(sizeof(char) * strlen(data.value.string_value));
			strcpy(result.value.string_value,data.value.string_value);
			break;
		case BOOLT:
			result.value.bool_value = data.value.bool_value;
			break;
		default:
			break;
	}

	return result;	
}

sym_value_type fromVarToSym(struct varia data)
{
	sym_value_type result;
	
	result.type = data.type;
	switch(data.type)
	{
		case INTT:
			result.value.int_value = data.value.int_value;
			break;
		case FLOATT:
			result.value.float_value = data.value.float_value;
			break;
		case STRINGT:
			result.value.string_value = data.value.string_value;
			break;
		case BOOLT:
			result.value.bool_value = data.value.bool_value;
			break;
		default:
			break;
	}
	
	return result;
}

struct liter fromSymToLit(sym_value_type data)
{
	struct liter result;
	
	result.type = data.type;
	switch(data.type)
	{
		case INTT:
			result.value.int_value = data.value.int_value;
			break;
		case FLOATT:
			result.value.float_value = data.value.float_value;
			break;
		case STRINGT:
			result.value.string_value = data.value.string_value;
			break;
		case BOOLT:
			result.value.bool_value = data.value.bool_value;
			break;
		default:
			break;
	}
	
	return result;
}

void storeSym(struct varia data)
{
	sym_value_type value;
	sym_name_type name;
	
	value = fromVarToSym(data);
	name = data.identifier;
	
	sym_enter(name, &value);
}

int loadSym(struct varia id, struct liter *result)
{
	sym_value_type aux;
	int error;
	
	error = sym_lookup(id.identifier, &aux);
	
	*(result) = fromSymToLit(aux);
	
	return error;
}

int isSymChosen(struct varia id)
{
	sym_value_type aux;
	int error;
	
	error = sym_lookup(id.identifier, &aux);
	
	return error;
}
