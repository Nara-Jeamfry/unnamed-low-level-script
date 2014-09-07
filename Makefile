#General defines
CC = gcc
PROF = gprof
LEX = flex
YACC = bison
LIB = -lc -lfl
APP = fgs
SOURCE_FOLDER = src/
COMPILER = $(SOURCE_FOLDER)$(APP)_comp
IN_LEX = $(SOURCE_FOLDER)$(COMPILER).l
IN_YACC = $(SOURCE_FOLDER)$(COMPILER).y

OBJ = $(COMPILER).o $(COMPILER)l.o $(COMPILER)y.o
SRC = $(COMPILER).c
SRCL = $(COMPILER)l.tmp.c
SRCY = $(COMPILER)y.tmp.c
SRCH = $(COMPILER).h
SRCSYM = $(COMPILER)_symtab.c
YHEADER = $(COMPILER)y.h
LIBS = fgs_*.c 

INTC = fgs.c
INTH = fgs.h

INTTESTC = test.c
INTHCOPY = test.h

BIN = $(APP).exe
INTTEST = test.exe
INTTESTP = test_prof.exe

PROFFLAGS = -b 

LFLAGS = -n -o $(SRCL)
YFLAGS = -d -v -o $(SRCY) --defines=$(YHEADER)
CFLAGS = -ansi -g -Wall
OTHERS = prac3y.h fgs_compy.tmp.output log.txt code.c3a output.byt *.stackdump *.bfgs

all : compile

test : compile
	@echo Compilant...
	@echo
	./$(INTTEST) -t
	
compile : $(SRCL) $(SRCY)
	$(CC) -o $(INTTEST) $(CFLAGS) $(INTC) $(INTTESTC) $(LIBS)
	
profiling : $(SRCL) $(SRCY)
	$(CC) -o $(INTTESTP) $(CFLAGS) -pg $(INTC) $(INTTESTC) $(LIBS)
	./$(INTTESTP)
	$(PROF) $(INTTESTP) $(PROFFLAGS)
	
valgrind : compile
	valgrind --tool=memcheck --leak-check=yes ./$(INTTEST)

$(SRCL) : $(IN_LEX)
	$(LEX) $(LFLAGS) $<

$(SRCY) : $(IN_YACC)
	$(YACC) $(YFLAGS) $<

clean : 
	rm -f *~ $(BIN)* $(INTTEST) $(INTTESTP) $(OTHERS) $(SRCL) $(SRCY) $(INTBINCOPY) $(INTBIN) output/*
