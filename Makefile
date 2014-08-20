#General defines
CC = gcc
LEX = flex
YACC = bison
LIB = -lc -lfl
IN_LEX = prac3.l
IN_YACC = prac3.y

OBJ = prac3.o prac3l.o prac3y.o
SRC = prac3.c
SRCL = prac3l.tmp.c
SRCY = prac3y.tmp.c
SRCH = prac3.h
SRCSYM = symtab.c
YHEADER = prac3y.h

BIN = prac3.exe

LFLAGS = -n -o $(SRCL)
YFLAGS = -d -o $(SRCY) --defines=$(YHEADER)
CFLAGS = -ansi -g
OTHERS = prac3y.h prac3y.output

FIBON = example_fibonacci_complexe.txt

EXEMPLE = <prova_exemple.txt >output/output_exemple.txt
EXEMPLE2 = <prova_exemple_2.txt >output/output_exemple_2.txt
EXEMPLE_EXTRES = <prova_funcions_extres.txt >output/output_extres.txt
EXEMPLE_ERRORS_OP = <prova_errors_operacions.txt >output/output_exemple_errors_op.txt
EXEMPLE_ERRORS_FL = <prova_errors_fluxe.txt >output/output_exemple_errors_fl.txt

all : compile

testf : compile
	./$(BIN) <$(FIBON)

compile : $(SRCL) $(SRCY)
	$(CC) -o $(BIN) $(CFLAGS) $(SRC) $(SRCL) $(SRCY) $(SRCSYM) $(LIB)
	
$(SRCL) : $(IN_LEX)
	$(LEX) $(LFLAGS) $<

$(SRCY) : $(IN_YACC)
	$(YACC) $(YFLAGS) $<

clean : 
	rm -f *~ $(BIN)* $(OTHERS) $(SRCL) $(SRCY) output/*