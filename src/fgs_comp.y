%{

#include "fgs_comp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fgs_comp_symtab.h"

extern int yylineno;
extern int yylex();

int errors_found = 0;

typedef char * errortype;
bytecode_entry * aux;

%}

%expect 1

%token <variable> ID
%token <literal> LITERAL_INT
%token <literal> LITERAL_FLOAT
%token <literal> LITERAL_STRING
%token <literal> LITERAL_BOOL
%token <type> INTEGER FLOAT STRING

%token <non_defined> ASSIGN ADD SUB MUL DIV
%token <non_defined> OPEN_PARENTH CLOSE_PARENTH OPEN_CLAUD CLOSE_CLAUD SEPARATOR RETURN
%token <non_defined> GT GE LT LE EQ NE
%token <non_defined> AND OR NOT 

%token <non_defined> FOR IN FOR_RANGE WHILE DO DONE IF THEN ELSE FI
%token <error> ERROR

%type <literal> arithm_expr addition_expr multiplication_expr expression generic_expression error_expression
%type <literal> boolean_expr or_expr and_expr not_expr boolean
%type <variable> name
%type <marker> if_expr for_expr while_expr or and while do done separator start_else else
%type <statement> programa conditional ordre loop function_call params param_list block parameter_spec
%type <error>  assign error_assign

%%

all 
	: all function {
		printDebug("Next function.");
	}
	| function {
		printDebug("Last function.");
	}

function 
	: ID params block  {
		
			int a = nextQuad();
			op = HALT;
			aux = gen_code_op(op);
			backpatch($3, a);
			saveFunction($1.identifier);
	}
	
params : OPEN_PARENTH CLOSE_PARENTH {
	
	}
	| OPEN_PARENTH param_list CLOSE_PARENTH {
		
	}
	| OPEN_PARENTH error CLOSE_PARENTH {
		yyerror("Unexpected parameter list.");
	}

parameter_spec
	: ID name {
		addType($1.identifier);
		
		op = INPUT_PARAM;
		aux = gen_code_op(op);
		aux->val1 = varLocation($2.identifier);
		aux->val1->type = 4;
				
		storeSym($2);
		
		fprintf(getDebugFile(), "Line %d: Loading variable %s from type %s.\n", yylineno, $2.identifier, $1.identifier);
	
	}
	| INTEGER name {
		op = INPUT_PARAM;
		aux = gen_code_op(op);
		aux->val1 = varLocation($2.identifier);
		aux->val1->type = INTT;
		
		$2.type = INTT;
		storeSym($2);
		
		fprintf(getDebugFile(), "Line %d: Loading variable %s from type integer.\n", yylineno, $2.identifier);
	
	}
	| FLOAT name {
		op = INPUT_PARAM;
		aux = gen_code_op(op);
		aux->val1 = varLocation($2.identifier);
		aux->val1->type = FLOATT;
				
		$2.type = FLOATT;
		storeSym($2);
		
		fprintf(getDebugFile(), "Line %d: Loading variable %s from type float.\n", yylineno, $2.identifier);
	
	}
	| STRING name {
		op = INPUT_PARAM;
		aux = gen_code_op(op);
		aux->val1 = varLocation($2.identifier);
		aux->val1->type = STRINGT;
				
		$2.type = STRINGT;
		storeSym($2);
		
		fprintf(getDebugFile(), "Line %d: Loading variable %s from type string.\n", yylineno, $2.identifier);
	
	}

param_list
	: param_list SEPARATOR parameter_spec {
		$$=NULL;
	}
	| parameter_spec {
		$$=NULL;
	}
	
separator
	: {
		$$.quadtupla = nextQuad();
	}
	
block
	: OPEN_CLAUD programa CLOSE_CLAUD {
		$$ = $2;
	}
	| ordre
	
programa : ordre separator programa {
		backpatch($1, $2.quadtupla);
		$$ = $3;
	}
	| ordre
	

ordre : assign SEPARATOR {
		$$ = NULL;
	}
	/* | boolean_expr {
		if(errors_found == 0)
		{
			if($1.type == INTT)
			{
				op = PARAM;
				aux = gen_code_op(op);
				aux->val1 = $1.variable;
				op = CALL;
				aux = gen_code_op(op);
				aux->oprel = PUTI;
				aux->val1 = litLocationInt(1);
			}
			else if($1.type == FLOATT)
			{
				op = PARAM;
				aux = gen_code_op(op);
				aux->val1 = $1.variable;
				op = CALL;
				aux = gen_code_op(op);
				aux->oprel = PUTF;
				aux->val1 = litLocationInt(1);
			}
			$$ = NULL;
		}
	} */
	| conditional
	| loop
	| function_call SEPARATOR {
		$$ = NULL;
	}
	| RETURN boolean_expr SEPARATOR {
		op = RETURN_OP;
		aux = gen_code_op(op);
		aux->val1 = duplicate_entry($2.variable);
		$$ = NULL;
	}

function_call
	: ID OPEN_PARENTH CLOSE_PARENTH {
		fprintf(getDebugFile(), "Line %d: Function call without params.\n", yylineno);
		op = CALL;
		aux = gen_code_op(op);
		aux->val1 = varLocation($1.identifier);
	}
	| ID OPEN_PARENTH input_params CLOSE_PARENTH {
		/*Load input params into stack */
		fprintf(getDebugFile(), "\nLine %d: Function call with params.\n", yylineno);
		op = CALL;
		aux = gen_code_op(op);
		aux->val1 = varLocation($1.identifier);
	}
	
input_params
	: input_params ID {
		fprintf(getDebugFile(), ", %s", $2.identifier);
		op = PARAM;
		aux = gen_code_op(op);
		aux->val1 = varLocation($2.identifier);
	}
	| ID {
		fprintf(getDebugFile(), "Line %d: Params list: %s", yylineno, $1.identifier);
		op = PARAM;
		aux = gen_code_op(op);
		aux->val1 = varLocation($1.identifier);
		
	}
	
if_expr
	: IF OPEN_PARENTH boolean_expr CLOSE_PARENTH {
		fprintf(getDebugFile(), "Line %d:  IF header found.\n", yylineno);
		if($3.type != BOOLT)
		{
			printError("Semantic Error: If expression must be boolean instead of %s.", typeToString($3.type));
		}
		$$.quadtupla = nextQuad();
		$$.trueList = $3.trueList;
		$$.falseList = $3.falseList;
}
	
else
	: ELSE {
		$$.quadtupla = nextQuad();
		op = GOTO;
		aux = gen_code_op(op);
		$$.nextList = addToList(NULL, aux);
	}
	
start_else
	: {
		$$.quadtupla = nextQuad();
	}
	
conditional 
	: if_expr block {
		fprintf(getDebugFile(), "Line %d:  If without else-clause finished.\n", yylineno);
		backpatch($1.trueList, $1.quadtupla);
		$$ = mergeLists($1.falseList, $2);
	}
	| if_expr block else start_else block {
		fprintf(getDebugFile(), "Line %d:  If with else-clause finished.\n", yylineno);
		backpatch($1.trueList, $1.quadtupla);
		backpatch($1.falseList, $4.quadtupla);
		$$ = mergeLists($3.nextList, $5);
		$$ = mergeLists($$, $2);
	}
	
while
	: WHILE {
		$$.quadtupla = nextQuad();
	}
	
while_expr
	: while OPEN_PARENTH boolean_expr CLOSE_PARENTH {
		fprintf(getDebugFile(), "Line %d:  While header found.\n", yylineno);
		if($3.type != BOOLT)
		{
			printError("Semantic Error: While expression must be boolean instead of %s.", typeToString($3.type));
		}
		$$.quadtupla = $1.quadtupla;
		$$.trueList = $3.trueList;
		$$.falseList = $3.falseList;
	}

for_expr	
	: FOR OPEN_PARENTH name IN arithm_expr FOR_RANGE arithm_expr CLOSE_PARENTH {
		fprintf(getDebugFile(), "Line %d:  For header found.\n", yylineno);
		fprintf(getDebugFile(), "Line %d:  Range on for found between %s and %s.\n", yylineno, typeToString($5.type), typeToString($7.type));
		if($5.type != INTT)
		{
			fprintf(stdout, "Semantic Error on line %d: Invalid range: first operand must be an integer (instead of %s).\n", yylineno, typeToString($5.type));
		}
		if($7.type != INTT)
		{
			fprintf(stdout, "Semantic Error on line %d: Invalid range: second operand must be an integer (instead of %s).\n", yylineno, typeToString($7.type));
		}
		if(isSymChosen($3) != SYMTAB_NOT_FOUND)
		{
			printError("Semantic Error: Variable %s already exists (must be fresh new variable!).\n", $3.identifier);
		}
		op = ASSIGNMENT_OP;
		aux = gen_code_op(op);
		aux->oprel = SUBI;
		aux->val1 = varLocation($3.identifier);
		aux->val2 = duplicate_entry($5.variable);
		aux->val3 = litLocationInt(1);
		$$.quadtupla = nextQuad();
		op = ASSIGNMENT_OP;
		aux = gen_code_op(op);
		aux->oprel = ADDI;
		aux->val1 = varLocation($3.identifier);
		aux->val2 = varLocation($3.identifier);
		aux->val3 = litLocationInt(1);
		op = IF_OP;
		aux = gen_code_op(op);
		aux->oprel = LTI;
		aux->val1 = varLocation($3.identifier);
		aux->val2 = duplicate_entry($7.variable);
		$$.trueList = addToList(NULL, aux);
		op = GOTO;
		aux = gen_code_op(op);
		$$.falseList = addToList(NULL, aux);
	}
	
done
	: CLOSE_CLAUD {
		$$.quadtupla = nextQuad();
			op = GOTO;
			aux = gen_code_op(op);
			$$.nextList = addToList(NULL, aux);
	} 

do
	: OPEN_CLAUD {
		$$.quadtupla = nextQuad();
	} 
	
loop
	: while_expr do programa done {
		fprintf(getDebugFile(), "Line %d:  Loop finished.\n", yylineno);
		backpatch($1.trueList, $2.quadtupla); 
			$$ = $1.falseList;
			backpatch($3, $1.quadtupla);
			backpatch($4.nextList, $1.quadtupla);
	}
	| for_expr do programa done {
		fprintf(getDebugFile(), "Line %d:  Loop finished.\n", yylineno);
		backpatch($1.trueList, $2.quadtupla); 
			$$ = $1.falseList;
			backpatch($3, $1.quadtupla);
			backpatch($4.nextList, $1.quadtupla);
	}
	
assign 
	: name ASSIGN boolean_expr {
		fprintf(getDebugFile(), "Line %d:  Assigning on variable %s type %s.\n", yylineno, $1.identifier, typeToString($3.type));
		if($3.type >=0 && $3.type <4){
			$1 = fromLitToVar($3, $1.identifier);
			op = ASSIGNMENT;
			aux = gen_code_op(op);
			aux->val1 = varLocation($1.identifier);
			aux->val2 = duplicate_entry($3.variable);
			$$=NULL;
				
			storeSym($1);
		}
	}
	| name ASSIGN function_call {
		
	}
	| name error_assign boolean_expr {
		yyerror("Syntax error: unexpected symbol encountered.");
	}

error_assign
	: error ASSIGN {
		yyerror("Encountered an error before the assign symbol.");
	}
	| ASSIGN error {
	}
	| error ASSIGN error {
	}
	
name 
	: ID {
		$$.identifier = $1.identifier;
	}

expression 
	: LITERAL_STRING {
		$$ = $1;
		$$.variable = litLocationString($1.value.string_value);
	}
	| LITERAL_INT {
		$$ = $1;
		$$.variable = litLocationInt($1.value.int_value);
	}
	| LITERAL_FLOAT {
		$$ = $1;
		$$.variable = litLocationFloat($1.value.float_value);
	}
	
boolean_expr
	: or_expr

or
	: OR {
		
			$$.quadtupla = nextQuad();
		
	}
	
or_expr
	: or_expr or and_expr {
		fprintf(getDebugFile(), "Line %d:  Performed an OR operation between %s and %s.\n", yylineno, typeToString($1.type), typeToString($3.type));
		$$.type = BOOLT;
		if($1.type != BOOLT || $3.type != BOOLT)
		{
			printError2("Semantic Error: Cannot operate OR between %s and %s.", typeToString($1.type), typeToString($3.type));
		}
		
			$$.trueList = mergeLists($1.trueList, $3.trueList);
			backpatch($1.falseList, $2.quadtupla);
			$$.falseList = $3.falseList;
		
		$$.value.bool_value = $1.value.bool_value || $3.value.bool_value;
	}
	| and_expr 
	
and
	: AND {
		
			$$.quadtupla = nextQuad();
		
	}
	
and_expr
	: and_expr and not_expr {
		fprintf(getDebugFile(), "Line %d:  Performed an AND operation between %s and %s.\n", yylineno, typeToString($1.type), typeToString($3.type));
		$$.type = BOOLT;
		if($1.type != BOOLT || $3.type != BOOLT)
		{
			printError2("Semantic Error: Cannot operate AND between %s and %s.", typeToString($1.type), typeToString($3.type));
		}
		
			$$.falseList = mergeLists($1.falseList, $3.falseList);
			backpatch($1.trueList, $2.quadtupla);
			$$.trueList = $3.trueList;
		
		$$.value.bool_value = $1.value.bool_value && $3.value.bool_value;
	}
	| not_expr 
	
not_expr
	: NOT not_expr {
		if($2.type != BOOLT)
		{
			printError("Semantic Error: Unexpected type expression (type: %s)", typeToString($2.type));
		}
		else
		{
			$$.value.bool_value = !$2.value.bool_value;
		}
		$$.trueList = $2.falseList;
		$$.falseList = $2.trueList;
		$$.type = BOOLT;
		fprintf(getDebugFile(), "Line %d:  Performed NOT operation on %s.\n", yylineno, typeToString($2.type));
	}
	| arithm_expr 
	| boolean {
		fprintf(getDebugFile(), "Line %d:  Reading boolean literal or comparation.\n", yylineno);
	}
	
arithm_expr 
	: addition_expr {
		if($1.type <0 || $1.type >3)
		{
			printError("Semantic Error: Unexpected type expression (type: %s)", typeToString($1.type));
		}
		$$ = $1;
	}

addition_expr 
	: addition_expr ADD multiplication_expr {
		int opresult = canIOperateThem($1, $3, SUMA);
		fprintf(getDebugFile(), "Line %d:  Performed ADD operation between %s and %s.\n", yylineno, typeToString($1.type), typeToString($3.type));
		if(opresult == -1)
			printError2("Semantic Error: Cannot add types %s and %s.", typeToString($1.type), typeToString($3.type));
		$$ = operateValues($1, $3, SUMA);
		if((opresult == INTT || opresult == FLOATT))
		{
			if(opresult != INTT)
			{
				op2 = ASSIGNMENT_UN;
				aux = gen_code_op(op2);
				if($1.type == INTT)
				{
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = duplicate_entry($1.variable);
					$1.variable = aux->val1;
				}
				if($3.type == INTT)
				{
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = duplicate_entry($3.variable);
					$3.variable = aux->val1;
				}
			}
			
			op = ASSIGNMENT_OP;
			aux = gen_code_op(op);
			
			if(opresult == INTT)
			{
				aux->oprel = ADDI;
			}
			else
			{
				aux->oprel = ADDF;
			}
			
			aux->val1 = tempLocation();
			aux->val2 = duplicate_entry($1.variable);
			aux->val3 = duplicate_entry($3.variable);
			$$.variable = aux->val1;
		}
		if(opresult == STRINGT)
		{
			if($1.type != STRINGT || $3.type != STRINGT)
			{
				op = ASSIGNMENT_UN;
				aux = gen_code_op(op);
				if($1.type != STRINGT)
				{
					if($1.type == INTT)
					{
						aux->oprel=I2S;
					}
					else if($1.type == FLOATT)
					{
						aux->oprel=F2S;
					}
					aux->val1 = tempLocation();
					aux->val2 = duplicate_entry($1.variable);
					$1.variable = aux->val1;
				}
				if($3.type != STRINGT)
				{
					if($3.type == INTT)
					{
						aux->oprel=I2S;
					}
					else if($3.type == FLOATT)
					{
						aux->oprel=F2S;
					}
					aux->val1 = tempLocation();
					aux->val2 = duplicate_entry($3.variable);
					$3.variable = aux->val1;
				}
			}
			op = ASSIGNMENT_OP;
			aux=gen_code_op(op);
			aux->oprel = ADDS;
			aux->val1 = tempLocation();
			aux->val2 = duplicate_entry($1.variable);
			aux->val3 = duplicate_entry($3.variable);
			$$.variable = aux->val1;
		}
	}
	| addition_expr SUB multiplication_expr {
		int opresult = canIOperateThem($1, $3, REST);
		fprintf(getDebugFile(), "Line %d: Performed SUB operation between %s and %s.\n", yylineno, typeToString($1.type), typeToString($3.type));
		if(opresult == -1)
		{
			printError2("Semantic Error: Operation - not allowed on types %s and %s.", typeToString($1.type), typeToString($3.type));
		}
		$$ = operateValues($1, $3, REST);
		if((opresult == INTT || opresult == FLOATT))
		{
			if(opresult != INTT)
			{
				if($1.type == INTT)
				{
					op2 = ASSIGNMENT_UN;
					aux = gen_code_op(op2);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = duplicate_entry($1.variable);
					$1.variable = aux->val1;
				}
				if($3.type == INTT)
				{
					op2 = ASSIGNMENT_UN;
					aux = gen_code_op(op2);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = duplicate_entry($3.variable);
					$3.variable = aux->val1;
				}
			}
			
			op = ASSIGNMENT_OP;
			aux = gen_code_op(op);
			if(opresult == INTT)
			{
				aux->oprel = SUBI;
			}
			else
			{
				aux->oprel = SUBF;
			}
			
			aux->val1 = tempLocation();
			aux->val2 = duplicate_entry($1.variable);
			aux->val3 = duplicate_entry($3.variable);
			$$.variable = aux->val1;
		}
	}
	| ADD multiplication_expr {
		fprintf(getDebugFile(), "Line %d: Performed unary ADD operation on %s.\n", yylineno, typeToString($2.type));
		if($2.type != STRINGT && $2.type != BOOLT)
			$$ = $2;
		else
			printError("Semantic Error: Unary operator + not allowed on type %s.", typeToString($2.type));
	}
	| SUB multiplication_expr {
		fprintf(getDebugFile(), "Line %d: Performed unary SUB operation on %s.\n", yylineno, typeToString($2.type));
		if($2.type != STRINGT && $2.type != BOOLT)
		{
			$$ = $2;
			if($$.type == INTT)
			{
				$$.value.int_value = -$$.value.int_value;
				
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->val1 = tempLocation();
					aux->val2 = duplicate_entry($2.variable);
					aux->oprel = CHSI;
					$$.variable = aux->val1;
				
			}
			if($$.type == FLOATT)
			{
				$$.value.float_value = -$$.value.float_value;
				
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->val1 = tempLocation();
					aux->val2 = duplicate_entry($2.variable);
					aux->oprel = CHSF;
					$$.variable = aux->val1;
				
			}
		}
		else
			printError("Semantic Error: Unary operator - not allowed on type %s.", typeToString($2.type));
	}
	| multiplication_expr

multiplication_expr 
	: error_expression
	| multiplication_expr MUL generic_expression {
		int opresult = canIOperateThem($1, $3, MULT);
		fprintf(getDebugFile(), "Line %d: Performed MUL operation between %s and %s.\n", yylineno, typeToString($1.type), typeToString($3.type));
		if(opresult == -1)
		{
			printError2("Semantic Error: Operation * not allowed on types %s and %s.", typeToString($1.type), typeToString($3.type));
		}
		$$ = operateValues($1, $3, MULT);
		if((opresult == INTT || opresult == FLOATT))
		{
			if(opresult!=INTT)
			{
				if($1.type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = duplicate_entry($1.variable);
					$1.variable = aux->val1;
				}
				if($3.type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = duplicate_entry($3.variable);
					$3.variable = aux->val1;
				}
			}
			op = ASSIGNMENT_OP;
			aux = gen_code_op(op);
			if(opresult == INTT)
			{
				aux->oprel = MULI;
			}
			else
			{
				aux->oprel = MULF;
			}
			aux->val1 = tempLocation();
			aux->val2 = duplicate_entry($1.variable);
			aux->val3 = duplicate_entry($3.variable);
			$$.variable = aux->val1;
		}
	}
	| multiplication_expr DIV generic_expression {
		int opresult = canIOperateThem($1, $3, DIVIS);
		fprintf(getDebugFile(), "Line %d: Performed DIV operation between %s and %s.\n", yylineno, typeToString($1.type), typeToString($3.type));
		if(opresult == -1)
		{
			printError2("Semantic Error: Operation / not allowed on types %s and %s.", typeToString($1.type), typeToString($3.type));
		}
		$$ = operateValues($1, $3, DIVIS);
		if((opresult == INTT || opresult == FLOATT))
		{
			if(opresult != INTT)
			{
				if($1.type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = $1.variable;
					$1.variable = aux->val1;
				}
				if($3.type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = $3.variable;
					$3.variable = aux->val1;
				}
			}
			
			op = ASSIGNMENT_OP;
			aux = gen_code_op(op);
			
			if(opresult == INTT)
			{
				aux->oprel = DIVI;
			}
			else
			{
				aux->oprel = DIVF;
			}
			
			aux->val1 = tempLocation();
			aux->val2 = duplicate_entry($1.variable);
			aux->val3 = duplicate_entry($3.variable);
			$$.variable = aux->val1;
		}
	}

error_expression
	: generic_expression
	| error_expression error generic_expression {
		$$ = operateValues($1, $3, SUMA);
		yyerror("Semantic Error: Unexpected operator on expression. (Default operator: sum)");
	}
	
boolean
	: arithm_expr GT arithm_expr {
		int auxC = compareValues($1, $3);
		
		$$.type = BOOLT;
		if(auxC == GREAT)
			$$.value.bool_value = 1;
		else if(auxC != INCOMPAT)
			$$.value.bool_value = 0;
		else
			printError2("Semantic Error: Cannot compare %s and %s.", typeToString($1.type), typeToString($3.type));
			if($1.type != INTT || $3.type != INTT)
			{
				if($1.type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = $1.variable;
					$1.variable = aux->val1;
				}
				if($3.type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = $3.variable;
					$3.variable = aux->val1;
				}
			}
			op = IF_OP;
			aux = gen_code_op(op);
			if($1.type == INTT && $3.type == INTT)
			{
				aux->oprel = GTI;
			}
			else
			{
				aux->oprel = GTF;
			}
			aux->val1 = $1.variable;
			aux->val2 = $3.variable;
			$$.trueList = addToList(NULL, aux);
			op = GOTO;
			aux = gen_code_op(op);
			$$.falseList = addToList(NULL, aux);
		
	}
	| arithm_expr GE arithm_expr {
		int auxC = compareValues($1, $3);
		
		$$.type = BOOLT;
		if(auxC == EQUAL || auxC == GREAT)
			$$.value.bool_value = 1;
		else if(auxC != INCOMPAT)
			$$.value.bool_value = 0;
		else
			printError2("Semantic Error: Cannot compare %s and %s.", typeToString($1.type), typeToString($3.type));
			
			if($1.type != INTT || $3.type != INTT)
			{
				if($1.type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = $1.variable;
					$1.variable = aux->val1;
				}
				if($3.type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = $3.variable;
					$3.variable = aux->val1;
				}
			}
			
			op = IF_OP;
			aux = gen_code_op(op);
			
			if($1.type == INTT && $3.type == INTT)
			{
				aux->oprel = GEI;
			}
			else
			{
				
				aux->oprel = GEF;
			}
			
			aux->val1 = $1.variable;
			aux->val2 = $3.variable;
			$$.trueList = addToList(NULL, aux);
			op = GOTO;
			aux = gen_code_op(op);
			$$.falseList = addToList(NULL, aux);
		
	}
	| arithm_expr LT arithm_expr {
		int auxC = compareValues($1, $3);
		
		$$.type = BOOLT;
		if(auxC == LESS)
			$$.value.bool_value = 1;
		else if(auxC != INCOMPAT)
			$$.value.bool_value = 0;
		else
			printError2("Semantic Error: Cannot compare %s and %s.", typeToString($1.type), typeToString($3.type));
		
			if($1.type != INTT || $3.type != INTT)
			{
				if($1.type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = duplicate_entry($1.variable);
					$1.variable = aux->val1;
				}
				if($3.type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = duplicate_entry($3.variable);
					$3.variable = aux->val1;
				}
			}
		
			op = IF_OP;
			aux = gen_code_op(op);
			if($1.type == INTT && $3.type == INTT)
			{
				aux->oprel = LTI;
			}
			else
			{
				aux->oprel = LTF;
			}
			aux->val1 = duplicate_entry($1.variable);
			aux->val2 = duplicate_entry($3.variable);
			$$.trueList = addToList(NULL, aux);
			op = GOTO;
			aux = gen_code_op(op);
			$$.falseList = addToList(NULL, aux);
		
	}
	| arithm_expr LE arithm_expr {
		int auxC = compareValues($1, $3);
		
		$$.type = BOOLT;
		if(auxC == LESS || auxC == EQUAL)
			$$.value.bool_value = 1;
		else if(auxC != INCOMPAT)
			$$.value.bool_value = 0;
		else
			printError2("Semantic Error: Cannot compare %s and %s.", typeToString($1.type), typeToString($3.type));
		
			if($1.type != INTT || $3.type != INTT)
			{
				if($1.type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = $1.variable;
					$1.variable = aux->val1;
				}
				if($3.type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = $3.variable;
					$3.variable = aux->val1;
				}
			}
		
			op = IF_OP;
			aux = gen_code_op(op);
			if($1.type == INTT && $3.type == INTT)
			{
				aux->oprel = LEI;
			}
			else
			{
				aux->oprel = LEF;
			}
			aux->val1 = $1.variable;
			aux->val2 = $3.variable;
			$$.trueList = addToList(NULL, aux);
			op = GOTO;
			aux = gen_code_op(op);
			$$.falseList = addToList(NULL, aux);
		
	}
	| arithm_expr EQ arithm_expr {
		int auxC = compareValues($1, $3);
		
		$$.type = BOOLT;
		if(auxC == EQUAL)
			$$.value.bool_value = 1;
		else if(auxC != INCOMPAT)
			$$.value.bool_value = 0;
		else
			printError2("Semantic Error: Cannot compare %s and %s.", typeToString($1.type), typeToString($3.type));
		
			op = IF_OP;
			aux = gen_code_op(op);
			aux->oprel = EQ_OP;
			aux->val1 = $1.variable;
			aux->val2 = $3.variable;
			$$.trueList = addToList(NULL, aux);
			op = GOTO;
			aux = gen_code_op(op);
			$$.falseList = addToList(NULL, aux);
		
	}
	| arithm_expr NE arithm_expr {
		int auxC = compareValues($1, $3);
		
		$$.type = BOOLT;
		if(auxC == EQUAL)
			$$.value.bool_value = 0;
		else if(auxC != INCOMPAT)
			$$.value.bool_value = 1;
		else
			printError2("Semantic Error: Cannot compare %s and %s.", typeToString($1.type), typeToString($3.type));
			
		
			op = IF_OP;
			aux = gen_code_op(op);
			aux->oprel = NE_OP;
			aux->val1 = $1.variable;
			aux->val2 = $3.variable;
			$$.trueList = addToList(NULL, aux);
			op = GOTO;
			aux = gen_code_op(op);
			$$.falseList = addToList(NULL, aux);
		
	}
	| LITERAL_BOOL	{
		
			$$.trueList = NULL;
			$$.falseList = NULL;
		
	}

generic_expression 
	: expression {
		fprintf(getDebugFile(), "Line %d: Reading literal (not bool).\n", yylineno);
		$$ = $1;
		
			$$.trueList = NULL;
			$$.falseList = NULL;
		
	}
	| name {
		if(loadSym($1, &$$) == SYMTAB_NOT_FOUND)
		{
			printError("Semantic Error: Variable %s does not exist", $1.identifier);
		}
		$$.variable = varLocation($1.identifier);
		
			$$.trueList = NULL;
			$$.falseList = NULL;
		
		fprintf(getDebugFile(), "Line %d: Loading variable %s from type %s.\n", yylineno, $1.identifier, typeToString($$.type));
	}
	| OPEN_PARENTH boolean_expr CLOSE_PARENTH {
		$$ = $2;
	}
	
%%

int parseFile(FILE * file, char * output_name)
{
	yylineno = 1;
	yyin = file;
	byteCodeName = output_name;
	if(bisonverbose)
			fprintf(stdout, "Starting parse!\n");
	yyparse();
	if(errors_found == 0)
	{
		if(bisonverbose)
			fprintf(stdout, "Printing code!\n");
		printCode(getCodeFile());
		if(bisonverbose)
			fprintf(stdout, "Writing ByteCode file!\n");
		printByteCode(getByteCodeFile());
	}
	else
		fprintf(stdout, "Cannot compile!\n");
	if(bisonverbose)
		fprintf(stdout, "Cleaning memory...\n");
	cleanMemory(); 
	if(bisonverbose)
			fprintf(stdout, "Fi!\n");
	closeFiles();
	return 0;
}

void yyerror (const char *s) {
	errors_found = 1;
	fprintf(stdout, "Error found on line %d: %s\n", yylineno, s);
}
