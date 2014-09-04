#General defines
CC = gcc
PROF = gprof
LEX = flex
YACC = bison
LIB = -lc -lfl
IN_LEX = fgs_comp.l
IN_YACC = fgs_comp.y

OBJ = fgs_comp.o fgs_compl.o fgs_compy.o
SRC = fgs_comp.c
SRCL = fgs_compl.tmp.c
SRCY = fgs_compy.tmp.c
SRCH = fgs_comp.h
SRCSYM = symtab.c
YHEADER = fgs_compy.h
LIBS = fgs_*.c 

INTC = fgs.c
INTH = fgs.h

INTTESTC = test.c
INTHCOPY = test.h

BIN = prac3.exe
INTTEST = test.exe
INTTESTP = test_prof.exe

PROFFLAGS = -b 

LFLAGS = -n -o $(SRCL)
YFLAGS = -d -v -o $(SRCY) --defines=$(YHEADER)
CFLAGS = -ansi -g -Wall
OTHERS = prac3y.h prac3y.tmp.output log.txt code.c3a output.byt *.stackdump *.bfgs

all : compile

test : compile
	@echo Compilant...
	@echo
	./$(INTTEST) -t
	
compile : $(SRCL) $(SRCY)
	$(CC) -o $(INTTEST) $(CFLAGS) $(SRCSYM) $(INTC) $(INTTESTC) $(LIBS)
	
profiling : $(SRCL) $(SRCY)
	$(CC) -o $(INTTESTP) $(CFLAGS) -pg $(SRCSYM) $(INTC) $(INTTESTC) $(LIBS)
	./$(INTTESTP)
	$(PROF) $(INTTESTP) $(PROFFLAGS)
	
valgrind : compile
	valgrind --tool=memcheck --leak-check=yes ./$(INTTEST)

$(SRCL) : $(IN_LEX)
	$(LEX) $(LFLAGS) $<

$(SRCY) : $(IN_YACC)
	$(YACC) $(YFLAGS) $<

clean : 
	rm -f *~ $(BIN)* $(OTHERS) $(SRCL) $(SRCY) $(INTBINCOPY) $(INTBIN) output/*
