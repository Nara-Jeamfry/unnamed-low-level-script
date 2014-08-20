/* A Bison parser, made by GNU Bison 2.7.1.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PRAC3Y_H_INCLUDED
# define YY_YY_PRAC3Y_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     LITERAL_INT = 259,
     LITERAL_FLOAT = 260,
     LITERAL_STRING = 261,
     LITERAL_BOOL = 262,
     ASSIGN = 263,
     ADD = 264,
     SUB = 265,
     MUL = 266,
     DIV = 267,
     OPEN_PARENTH = 268,
     CLOSE_PARENTH = 269,
     OPEN_CLAUD = 270,
     CLOSE_CLAUD = 271,
     SEPARATOR = 272,
     GT = 273,
     GE = 274,
     LT = 275,
     LE = 276,
     EQ = 277,
     NE = 278,
     AND = 279,
     OR = 280,
     NOT = 281,
     CALC = 282,
     ON = 283,
     OFF = 284,
     FOR = 285,
     IN = 286,
     FOR_RANGE = 287,
     WHILE = 288,
     DO = 289,
     DONE = 290,
     IF = 291,
     THEN = 292,
     ELSE = 293,
     FI = 294,
     ERROR = 295
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PRAC3Y_H_INCLUDED  */
