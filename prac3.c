#include "prac3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symtab.h"

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

int codeOffset = 0;
int localOffset = 1;

int nextQuad()
{
	return codeOffset;
}

C3A_value *tempLocation()
{
	C3A_value *aux = malloc(sizeof(C3A_value));
	aux->type = 0;
	aux->value.tempID = dataOffset++;
	
	C3A_value_container *existing_var = checkNewVar(aux, firstLocal);
	
	if(!existing_var)
	{
		fprintf(getDebugFile(), "Nova variable\n");
		C3A_value_container *new = malloc(sizeof(C3A_value_container));
		new->value = aux;
		new->id = localOffset++;
		char *auxName = malloc(sizeof(char)*14);
		sprintf(auxName, "$t%d", aux->value.tempID);
		new->name = auxName;
		
		if(firstLocal == NULL)
		{
			firstLocal = new;
			lastLocal = new;
		}
		else
		{
			lastLocal->next = new;
			lastLocal = new;
		}
		
		aux->container = new;
	}
	else
	{
		aux->container = existing_var;
	}
	 
	return aux;
}

C3A_value *varLocation(char * identifier)
{
	C3A_value *aux = malloc(sizeof(C3A_value));
	aux->value.varName = identifier;
	aux->type = 1;
	
	C3A_value_container *existing_var = checkNewVar(aux, firstLocal);
	
	if(!existing_var)
	{
		fprintf(getDebugFile(), "Nova variable\n");
		C3A_value_container *new = malloc(sizeof(C3A_value_container));
		new->value = aux;
		new->id = localOffset++;
		new->name = identifier;
		
		if(firstLocal == NULL)
		{
			firstLocal = new;
			lastLocal = new;
		}
		else
		{
			lastLocal->next = new;
			lastLocal = new;
		}
		
		aux->container = new;
	}
	else
	{
		aux->container = existing_var;
	}
	
	return aux;
}

C3A_value *litLocationInt(int i)
{
	C3A_value *aux = malloc(sizeof(C3A_value));
	aux->value.literalI = i;
	aux->type = 2;
	return aux;
}

C3A_value *litLocationFloat(float f)
{
	C3A_value *aux = malloc(sizeof(C3A_value));
	aux->value.literalF = f;
	aux->type = 3;
	return aux;
}

C3A_value *litLocationString(char *word)
{
	C3A_value *aux = malloc(sizeof(C3A_value));
	aux->value.literalS = word;
	aux->type = 4;
	return aux;
}

bytecode_entry *gen_code()
{
	bytecode_entry* newQuad = malloc(sizeof(bytecode_entry));
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
	bytecode_entry* newQuad = malloc(sizeof(bytecode_entry));
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
			codeOffset+=2;
			break;
		case IF_OP:
			codeOffset+=3;
			break;
		case CALL:
			codeOffset+=2;
			break;
		default:
			codeOffset++;
			break;
	}
	return newQuad;
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
	
	codeStart = NULL;
	codeEnd = NULL;
	firstLocal = NULL;
	lastLocal = NULL;
	codeOffset = 0;
	localOffset = 1;

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
}

void openCodeFile()
{
	codeFile = fopen("code.c3a", "w");
}

void printCode(FILE * fi)
{
	bytecode_entry *line = NULL;
	function_entry *section = firstFunction;
	C3A_value_container *var = NULL;
	
	int lineNumber = 0, res;
	
	headerLength = 0;
	int codeLength = 0;
	
	if(fprintf(fi, "Bytecode---\n") <= 0)
	{
		printError("Cannot write to file\n", "");
		
		return;
	}
	
	fprintf(stdout, "Printant programa.");
	
	while(section)
	{
		headerLength += 1;
		headerLength += section->localLength;
		section = section->next;
	}
	
	fprintf(fi, "%d: Header length: %d\n", lineNumber++, ++headerLength);
	section = firstFunction;
	
	while(section)
	{
		res = fprintf(fi, "%d: Function %s at @%d\n", lineNumber++, section->identifier, headerLength+codeLength);
		codeLength+=section->length;
		var = section->locals;
		
		while(var)
		{
			res = fprintf(fi, "%d: Variable %s as #%d\n", lineNumber++, var->name, var->id);
		
			var = var->next;
		}
	
		section = section->next;
	}
	
	section = firstFunction;
	
	while(section)
	{
		line = section->first_code;
		
		while(line)
		{
			res = fprintf(fi, "%s\n", printOp(line, &lineNumber));
			
			if(res <=0)
			{
				printError("Cannot write to file\n","");
				
				return;
			}
			
			line = line->next;
			/* lineNumber++; */
		}
		
		section = section->next;
	}
}

char *printOp(bytecode_entry *op, int *lineNumber)
{
	char * aux;
	char * result;
	
	switch(op->op)
	{
		case IF_OP:
			result = malloc(sizeof(char)*(14 + 100)+4);
			sprintf(result, "%d: %s %s %s\n%d: GOTO\n%d: #%d", (*lineNumber),
											printRelOp(op->oprel),
											printC3AVal(op->val1),
											printC3AVal(op->val2),
											(*lineNumber)+1,
											(*lineNumber)+2,
											op->gotoL+headerLength);
			(*lineNumber)+=3;
			return result;
		break;
		case GOTO:
			result = malloc(sizeof(char)*(5+11)+4);
			sprintf(result, "%d: GOTO\n%d: #%d", (*lineNumber), 
											(*lineNumber)+1,
											op->gotoL+headerLength);
			(*lineNumber)+=2;
			return result;
		break;
		case ASSIGNMENT:
			result = malloc(sizeof(char)*100+4);
			sprintf(result, "%d: %s := %s", (*lineNumber), 
											printC3AVal(op->val1), 
											printC3AVal(op->val2));
			(*lineNumber)++;
			return result;
		break;
		case ASSIGNMENT_OP:
			result = malloc(sizeof(char)*100+4);
			sprintf(result, "%d: %s := %s %s %s", (*lineNumber), 
											printC3AVal(op->val1), 
											printC3AVal(op->val2),
											printRelOp(op->oprel),
											printC3AVal(op->val3));
			(*lineNumber)++;
			return result;
		break;
		case ASSIGNMENT_UN:
			result = malloc(sizeof(char)*100+4);
			sprintf(result, "%d: %s := %s %s", (*lineNumber), printC3AVal(op->val1),
											printRelOp(op->oprel),
											printC3AVal(op->val2));
			(*lineNumber)++;
			return result;
		break;
		case PARAM:
			aux = printC3AVal(op->val1);
			result = malloc(sizeof(char)*7+sizeof(aux)+4);
			sprintf(result, "%d: PARAM %s", (*lineNumber), 
											aux);
			(*lineNumber)++;
			return result;
		break;
		case CALL:
			result = malloc(sizeof(char)*10+11+4);
			sprintf(result, "%d: CALL\n%d: @%d", (*lineNumber), 
											(*lineNumber)+1, 
											op->gotoL);
			(*lineNumber)+=2;
			return result;
		break;
		case HALT:
			result = malloc(sizeof(char)*14);
			sprintf(result, "%d: HALT", (*lineNumber));
			(*lineNumber)++;
			return result;
		break;
		default:
			return NULL;
		break;
	}
	return "HAHAHA";
}

char *printC3AVal(C3A_value *value)
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
			sprintf(aux, "$t%02d", value->value.tempID);
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
			return aux;
		break;
		case 3:
			aux = malloc(sizeof(char) * 100);
			sprintf(aux, "%.2f", value->value.literalF);
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
		case F2I:
			return "I2F";
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
		case PUTI:
			return "PUTI";
		break;
		case PUTF:
			return "PUTF";
		break;
		default:
			return NULL;
		break;
	}
	return "HIHIHI";
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