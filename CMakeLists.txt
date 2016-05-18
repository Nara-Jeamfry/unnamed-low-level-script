cmake_minimum_required(VERSION 3.5)
project(FastGameScript)

set(FastGameScript_VERSION_MAJOR 0)
set(FastGameScript_VERSION_MINOR 2)

set(CC "gcc")
set(PROF "gprof")
set(LEX "flex")
set(YACC "bison")
set(MEMCHECK "valgrind")
set(SRC_FOLDER "src/")

set(BASEDIR "${CURDIR}")

set(APP_NAME "fgs")
set(COMPILER "${APP_NAME}_comp")
set(INTERPRETER "${APP_NAME}_int")

set(PROF_CCFLAGS "-pg")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -Wall")
set(TEST_FLAGS "${TEST_FLAGS} -t")

set(HEADERS_FLAGS "-Isrc/headers")
set(COMPILER_HEADER "fgs_comp.h")
set(OPERATIONS "ops.h")

# LEX and YACC files and products
set(SRCL "${COMPILER}.l")
set(CL "${COMPILER}_l.c")
set(OBJL "$(COMPILER)_l.o")

set(SRCY "$(COMPILER).y")
set(CY "$(COMPILER)_y.c")
set(OBJY "$(COMPILER)_y.o")

file(GLOB FGS_COMP_AUX src/fgs_comp*.c)

include_directories("src/headers")

set(COMPILER_FILES
        tmp/${CL}
        tmp/${CY}
        build/)

file(GLOB FGS_INTERPRETER_FILES src/fgs*.c)

add_library(${COMPILER} src/fgs_comp_symtab.c src/fgs_comp.c ${FGS_COMP_AUX})

add_library(${INTERPRETER} ${FGS_INTERPRETER_FILES})

add_executable(test_interpreter src/test.c)