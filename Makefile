#General defines
CC = gcc
PROF = gprof
LEX = flex
YACC = bison
MEMCHECK = valgrind
SRC_FOLDER = src/
COMPILER_FOLDER = $(SRC_FOLDER)compiler/

BASEDIR = $(CURDIR)

#Specific defines
APP_NAME = fgs
COMPILER = $(APP_NAME)_comp

#Options and flags
PROF_CCFLAGS = -pg
CCFLAGS = -ansi
DEBUG_CCFLAGS = -g -Wall
TEST_FLAGS = -t

HEADERS_FLAG = -Isrc/headers

#Deliverables
COMPILER_HEADER = fgs_comp.h
OPERATIONS = ops.h

SRCL = $(COMPILER).l
CL = $(COMPILER)_l.c
OBJL = $(COMPILER)_l.o

SRCY = $(COMPILER).y
CY = $(COMPILER)_y.c
OBJY = $(COMPILER)_y.o



#Target rules
all : test_compile
	@echo Finished compilation of test!
	
test : test.exe
	@echo Executing test with -t
	./test.exe -t

testv : test.exe
	@echo Executing test with -tv
	./test.exe -vt

test.exe : test_compile
	

test_compile : interpreter
	$(CC) $(HEADERS_FLAG) -ansi -o test.exe src/test.c build/*.o

debug_compile : tmp/$(CL) tmp/$(CY) build/
	$(CC) -ansi $(HEADERS_FLAG) -g -o testd.exe src/fgs*.c src/test.c tmp/fgs*.c

interpreter : compiler
	$(CC) -c $(HEADERS_FLAG) $(CCFLAGS) src/fgs*.c
	mv fgs*.o build/
#	rm build/$(APP_NAME).a
#	ar -cvq build/$(APP_NAME).a build/*.o


profiling : interpreter
	

valgrind : compiler
	$(MEMCHECK) --tool=memcheck --leak-check=yes ./$(TEST) $(TEST_FLAGS)

compiler : tmp/$(CL) tmp/$(CY) build/
	$(CC) -ansi $(HEADERS_FLAG) -g -c src/fgs_comp_symtab.c src/fgs_comp.c tmp/fgs_comp*.c 
	mv fgs_comp*.o build/

tmp/$(CL) : tmp/
	flex -n -o tmp/$(CL) src/$(SRCL)

tmp/$(CY) : tmp/
	bison -d -o tmp/$(CY) src/$(SRCY)

build/ :
	mkdir build

tmp/ :
	mkdir tmp

clean :
	rm -r -f tmp
	rm -r -f build