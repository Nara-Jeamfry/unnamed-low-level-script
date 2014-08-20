/* A Bison parser, made by GNU Bison 2.7.1.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "prac3.y"


#include "prac3.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symtab.h"

extern int yylineno;
extern int yylex();

int errors_found = 0;

typedef char * errortype;
bytecode_entry * aux;


/* Line 371 of yacc.c  */
#line 86 "prac3y.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "prac3y.h".  */
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 191 "prac3y.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   165

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  72
/* YYNRULES -- Number of states.  */
#define YYNSTATES  132

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     6,     8,    14,    17,    19,    23,    26,
      28,    30,    32,    34,    36,    38,    42,    47,    50,    52,
      58,    60,    61,    65,    75,    77,    82,    91,    93,    95,
     100,   105,   109,   113,   116,   119,   123,   125,   127,   129,
     131,   133,   135,   139,   141,   143,   147,   149,   152,   154,
     156,   158,   162,   166,   169,   172,   174,   176,   180,   184,
     186,   190,   194,   198,   202,   206,   210,   214,   216,   218,
     220,   224,   227
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      42,     0,    -1,    42,    43,    -1,    43,    -1,     3,    44,
      15,    46,    16,    -1,    13,    14,    -1,    17,    -1,    47,
      45,    46,    -1,    47,    45,    -1,    47,    -1,    60,    -1,
      64,    -1,    53,    -1,    59,    -1,    48,    -1,     3,    13,
      14,    -1,     3,    13,    49,    14,    -1,    49,     3,    -1,
       3,    -1,    36,    13,    64,    14,    37,    -1,    38,    -1,
      -1,    50,    46,    39,    -1,    50,    15,    46,    16,    51,
      52,    15,    46,    16,    -1,    33,    -1,    54,    13,    64,
      14,    -1,    30,    13,    62,    31,    70,    32,    70,    14,
      -1,    16,    -1,    15,    -1,    55,    58,    46,    57,    -1,
      56,    58,    46,    57,    -1,    62,     8,    64,    -1,    62,
      61,    64,    -1,    76,     8,    -1,     8,    76,    -1,    76,
       8,    76,    -1,     3,    -1,     6,    -1,     4,    -1,     5,
      -1,    66,    -1,    25,    -1,    66,    65,    68,    -1,    68,
      -1,    24,    -1,    68,    67,    69,    -1,    69,    -1,    26,
      69,    -1,    70,    -1,    74,    -1,    71,    -1,    71,     9,
      72,    -1,    71,    10,    72,    -1,     9,    72,    -1,    10,
      72,    -1,    72,    -1,    73,    -1,    72,    11,    75,    -1,
      72,    12,    75,    -1,    75,    -1,    73,    76,    75,    -1,
      70,    18,    70,    -1,    70,    19,    70,    -1,    70,    20,
      70,    -1,    70,    21,    70,    -1,    70,    22,    70,    -1,
      70,    23,    70,    -1,     7,    -1,    63,    -1,    62,    -1,
      13,    64,    14,    -1,    40,    76,    -1,    40,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    46,    46,    48,    52,    74,    82,    87,    91,    92,
      95,    98,   124,   125,   126,   131,   137,   143,   147,   153,
     165,   173,   178,   183,   192,   197,   209,   249,   257,   262,
     269,   278,   291,   296,   298,   300,   304,   309,   313,   317,
     323,   326,   333,   347,   350,   357,   371,   374,   388,   389,
     394,   403,   449,   498,   505,   538,   541,   542,   589,   643,
     644,   650,   699,   753,   804,   855,   877,   900,   908,   916,
     928,   933,   938
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "LITERAL_INT", "LITERAL_FLOAT",
  "LITERAL_STRING", "LITERAL_BOOL", "ASSIGN", "ADD", "SUB", "MUL", "DIV",
  "OPEN_PARENTH", "CLOSE_PARENTH", "OPEN_CLAUD", "CLOSE_CLAUD",
  "SEPARATOR", "GT", "GE", "LT", "LE", "EQ", "NE", "AND", "OR", "NOT",
  "CALC", "ON", "OFF", "FOR", "IN", "FOR_RANGE", "WHILE", "DO", "DONE",
  "IF", "THEN", "ELSE", "FI", "ERROR", "$accept", "all", "function",
  "params", "separator", "programa", "ordre", "function_call",
  "input_params", "if_expr", "else", "start_else", "conditional", "while",
  "while_expr", "for_expr", "done", "do", "loop", "assign", "error_assign",
  "name", "expression", "boolean_expr", "or", "or_expr", "and", "and_expr",
  "not_expr", "arithm_expr", "addition_expr", "multiplication_expr",
  "error_expression", "boolean", "generic_expression", "long_error", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    42,    43,    44,    45,    46,    46,    46,
      47,    47,    47,    47,    47,    48,    48,    49,    49,    50,
      51,    52,    53,    53,    54,    55,    56,    57,    58,    59,
      59,    60,    60,    61,    61,    61,    62,    63,    63,    63,
      64,    65,    66,    66,    67,    68,    68,    69,    69,    69,
      70,    71,    71,    71,    71,    71,    72,    72,    72,    73,
      73,    74,    74,    74,    74,    74,    74,    74,    75,    75,
      75,    76,    76
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     5,     2,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     4,     2,     1,     5,
       1,     0,     3,     9,     1,     4,     8,     1,     1,     4,
       4,     3,     3,     2,     2,     3,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     3,     1,     2,     1,     1,
       1,     3,     3,     2,     2,     1,     1,     3,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       3,     2,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     3,     0,     0,     1,     2,     5,     0,
      36,    38,    39,    37,    67,     0,     0,     0,     0,     0,
      24,     0,     0,     9,    14,     0,    12,     0,     0,     0,
      13,    10,    69,    68,    11,    40,    43,    46,    48,    50,
      55,    56,    49,    59,     0,    36,    69,    53,    54,     0,
      47,     0,     0,     4,     6,     8,     0,     0,     0,    28,
       0,     0,     0,    72,     0,     0,    41,     0,    44,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    18,    15,     0,    70,     0,     0,     7,     0,    22,
       0,     0,     0,    31,    34,    71,    32,    33,    42,    45,
      61,    62,    63,    64,    65,    66,    51,    52,    57,    58,
      60,    17,    16,     0,     0,     0,    25,    27,    29,    30,
      35,     0,    19,    20,    21,     0,     0,     0,     0,    26,
       0,    23
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     5,    55,    22,    23,    24,    83,    25,
     124,   126,    26,    27,    28,    29,   118,    60,    30,    31,
      64,    46,    33,    34,    67,    35,    69,    36,    37,    38,
      39,    40,    41,    42,    43,    65
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -65
static const yytype_int16 yypact[] =
{
       2,    11,    15,   -65,     8,    12,   -65,   -65,   -65,   117,
      30,   -65,   -65,   -65,   -65,    35,    35,   128,   128,    31,
     -65,    37,    38,    36,   -65,    81,   -65,    42,    43,    43,
     -65,   -65,     5,   -65,   -65,    32,    50,   -65,    79,    10,
      18,    19,   -65,   -65,     9,   -65,   -65,    18,    18,    53,
     -65,    74,   128,   -65,   -65,   117,   117,    39,   128,   -65,
     117,   117,    66,    19,   128,    72,   -65,   128,   -65,   128,
     152,   152,   152,   152,   152,   152,    35,    35,    35,    35,
      35,   -65,   -65,    14,   -65,    51,    67,   -65,    73,   -65,
      69,    77,    77,   -65,   -65,   -65,   -65,    19,    50,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,    18,    18,   -65,   -65,
     -65,   -65,   -65,   152,    58,    65,   -65,   -65,   -65,   -65,
     -65,    76,   -65,   -65,   -65,   152,    90,    95,   117,   -65,
      94,   -65
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -65,   -65,   110,   -65,   -65,   -24,   -65,   -65,   -65,   -65,
     -65,   -65,   -65,   -65,   -65,   -65,    21,    86,   -65,   -65,
     -65,    -9,   -65,     4,   -65,   -65,   -65,    49,    -4,   -64,
     -65,   -13,   -65,   -65,   -45,   -37
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      32,    57,    47,    48,    80,     1,   100,   101,   102,   103,
     104,   105,    81,    62,    50,     6,    32,   111,     1,    76,
      77,    49,     8,    82,     4,    94,    95,     9,   112,    78,
      79,    87,    88,   108,   109,   110,    91,    92,    45,    11,
      12,    13,    85,    44,    51,    63,    32,    32,    17,   121,
      52,    32,    32,    54,    53,    58,    86,    66,    59,    63,
     120,   127,    90,   106,   107,    99,    93,    84,    96,    45,
      11,    12,    13,    14,    68,    15,    16,    45,    89,    17,
      97,   114,   113,   116,    10,    11,    12,    13,    14,   115,
      15,    16,    18,   117,    17,   122,    56,    70,    71,    72,
      73,    74,    75,   123,   130,   128,    63,    18,   125,   129,
     131,    19,     7,   119,    20,    61,    98,    21,     0,    32,
      10,    11,    12,    13,    14,     0,    15,    16,     0,     0,
      17,    45,    11,    12,    13,    14,     0,    15,    16,     0,
       0,    17,     0,    18,     0,     0,     0,    19,     0,     0,
      20,     0,     0,    21,    18,    45,    11,    12,    13,     0,
       0,    15,    16,     0,     0,    17
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-65)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       9,    25,    15,    16,    41,     3,    70,    71,    72,    73,
      74,    75,     3,     8,    18,     0,    25,     3,     3,     9,
      10,    17,    14,    14,    13,    62,    63,    15,    14,    11,
      12,    55,    56,    78,    79,    80,    60,    61,     3,     4,
       5,     6,    51,    13,    13,    40,    55,    56,    13,   113,
      13,    60,    61,    17,    16,    13,    52,    25,    15,    40,
      97,   125,    58,    76,    77,    69,    62,    14,    64,     3,
       4,     5,     6,     7,    24,     9,    10,     3,    39,    13,
       8,    14,    31,    14,     3,     4,     5,     6,     7,    16,
       9,    10,    26,    16,    13,    37,    15,    18,    19,    20,
      21,    22,    23,    38,   128,    15,    40,    26,    32,    14,
      16,    30,     2,    92,    33,    29,    67,    36,    -1,   128,
       3,     4,     5,     6,     7,    -1,     9,    10,    -1,    -1,
      13,     3,     4,     5,     6,     7,    -1,     9,    10,    -1,
      -1,    13,    -1,    26,    -1,    -1,    -1,    30,    -1,    -1,
      33,    -1,    -1,    36,    26,     3,     4,     5,     6,    -1,
      -1,     9,    10,    -1,    -1,    13
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    42,    43,    13,    44,     0,    43,    14,    15,
       3,     4,     5,     6,     7,     9,    10,    13,    26,    30,
      33,    36,    46,    47,    48,    50,    53,    54,    55,    56,
      59,    60,    62,    63,    64,    66,    68,    69,    70,    71,
      72,    73,    74,    75,    13,     3,    62,    72,    72,    64,
      69,    13,    13,    16,    17,    45,    15,    46,    13,    15,
      58,    58,     8,    40,    61,    76,    25,    65,    24,    67,
      18,    19,    20,    21,    22,    23,     9,    10,    11,    12,
      76,     3,    14,    49,    14,    62,    64,    46,    46,    39,
      64,    46,    46,    64,    76,    76,    64,     8,    68,    69,
      70,    70,    70,    70,    70,    70,    72,    72,    75,    75,
      75,     3,    14,    31,    14,    16,    14,    16,    57,    57,
      76,    70,    37,    38,    51,    32,    52,    70,    15,    14,
      46,    16
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1787 of yacc.c  */
#line 46 "prac3.y"
    {
	}
    break;

  case 3:
/* Line 1787 of yacc.c  */
#line 48 "prac3.y"
    {
	}
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 52 "prac3.y"
    {
		/*if(calc==1)
			fprintf(stdout, "Execucio finalitzada%s!", (errors_found == 0) ? "" : " amb errors" );
		else
		{*/
			int a = nextQuad();
			op = HALT;
			aux = gen_code_op(op);
			backpatch((yyvsp[(4) - (5)].statement), a);
			saveFunction((yyvsp[(1) - (5)].variable).identifier);
		/* } */
	}
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 74 "prac3.y"
    {
	
	}
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 82 "prac3.y"
    {
		(yyval.marker).quadtupla = nextQuad();
		fprintf(getDebugFile(), "Line %d: Found ; separator.\n", yylineno);
	}
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 87 "prac3.y"
    {
		backpatch((yyvsp[(1) - (3)].statement), (yyvsp[(2) - (3)].marker).quadtupla);
		(yyval.statement) = (yyvsp[(3) - (3)].statement);
	}
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 95 "prac3.y"
    {
		(yyval.statement) = NULL;
	}
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 98 "prac3.y"
    {
		if(errors_found == 0)
		{
			if((yyvsp[(1) - (1)].literal).type == INTT)
			{
				op = PARAM;
				aux = gen_code_op(op);
				aux->val1 = (yyvsp[(1) - (1)].literal).variable;
				op = CALL;
				aux = gen_code_op(op);
				aux->oprel = PUTI;
				aux->val1 = litLocationInt(1);
			}
			else if((yyvsp[(1) - (1)].literal).type == FLOATT)
			{
				op = PARAM;
				aux = gen_code_op(op);
				aux->val1 = (yyvsp[(1) - (1)].literal).variable;
				op = CALL;
				aux = gen_code_op(op);
				aux->oprel = PUTF;
				aux->val1 = litLocationInt(1);
			}
			(yyval.statement) = NULL;
		}
	}
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 126 "prac3.y"
    {
		(yyval.statement) = NULL;
	}
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 131 "prac3.y"
    {
		fprintf(getDebugFile(), "Line %d: Function call without params.\n", yylineno);
		op = CALL;
		aux = gen_code_op(op);
		aux->gotoL = 1;
	}
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 137 "prac3.y"
    {
		 /*Load input params into stack */
		fprintf(getDebugFile(), "\nLine %d: Function call with params.\n", yylineno);
	}
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 143 "prac3.y"
    {
		fprintf(getDebugFile(), ", %s", (yyvsp[(2) - (2)].variable).identifier);
		
	}
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 147 "prac3.y"
    {
		fprintf(getDebugFile(), "Line %d: Params list: %s", yylineno, (yyvsp[(1) - (1)].variable).identifier);
		
	}
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 153 "prac3.y"
    {
		fprintf(getDebugFile(), "Line %d:  IF header found.\n", yylineno);
		if((yyvsp[(3) - (5)].literal).type != BOOLT)
		{
			printError("Semantic Error: If expression must be boolean instead of %s.", typeToString((yyvsp[(3) - (5)].literal).type));
		}
		(yyval.marker).quadtupla = nextQuad();
		(yyval.marker).trueList = (yyvsp[(3) - (5)].literal).trueList;
		(yyval.marker).falseList = (yyvsp[(3) - (5)].literal).falseList;
}
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 165 "prac3.y"
    {
		(yyval.marker).quadtupla = nextQuad();
		op = GOTO;
		aux = gen_code_op(op);
		(yyval.marker).nextList = addToList(NULL, aux);
	}
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 173 "prac3.y"
    {
		(yyval.marker).quadtupla = nextQuad();
	}
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 178 "prac3.y"
    {
		fprintf(getDebugFile(), "Line %d:  If without else-clause finished.\n", yylineno);
		backpatch((yyvsp[(1) - (3)].marker).trueList, (yyvsp[(1) - (3)].marker).quadtupla);
		(yyval.statement) = mergeLists((yyvsp[(1) - (3)].marker).falseList, (yyvsp[(3) - (3)].non_defined));
	}
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 183 "prac3.y"
    {
		fprintf(getDebugFile(), "Line %d:  If with else-clause finished.\n", yylineno);
		backpatch((yyvsp[(1) - (9)].marker).trueList, (yyvsp[(1) - (9)].marker).quadtupla);
		backpatch((yyvsp[(1) - (9)].marker).falseList, (yyvsp[(6) - (9)].marker).quadtupla);
		(yyval.statement) = mergeLists((yyvsp[(5) - (9)].marker).nextList, (yyvsp[(8) - (9)].statement));
		(yyval.statement) = mergeLists((yyval.statement), (yyvsp[(3) - (9)].statement));
	}
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 192 "prac3.y"
    {
		(yyval.marker).quadtupla = nextQuad();
	}
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 197 "prac3.y"
    {
		fprintf(getDebugFile(), "Line %d:  While header found.\n", yylineno);
		if((yyvsp[(3) - (4)].literal).type != BOOLT)
		{
			printError("Semantic Error: While expression must be boolean instead of %s.", typeToString((yyvsp[(3) - (4)].literal).type));
		}
		(yyval.marker).quadtupla = (yyvsp[(1) - (4)].marker).quadtupla;
		(yyval.marker).trueList = (yyvsp[(3) - (4)].literal).trueList;
		(yyval.marker).falseList = (yyvsp[(3) - (4)].literal).falseList;
	}
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 209 "prac3.y"
    {
		fprintf(getDebugFile(), "Line %d:  For header found.\n", yylineno);
		fprintf(getDebugFile(), "Line %d:  Range on for found between %s and %s.\n", yylineno, typeToString((yyvsp[(5) - (8)].literal).type), typeToString((yyvsp[(7) - (8)].literal).type));
		if((yyvsp[(5) - (8)].literal).type != INTT)
		{
			fprintf(stdout, "Semantic Error on line %d: Invalid range: first operand must be an integer (instead of %s).\n", yylineno, typeToString((yyvsp[(5) - (8)].literal).type));
		}
		if((yyvsp[(7) - (8)].literal).type != INTT)
		{
			fprintf(stdout, "Semantic Error on line %d: Invalid range: second operand must be an integer (instead of %s).\n", yylineno, typeToString((yyvsp[(7) - (8)].literal).type));
		}
		if(isSymChosen((yyvsp[(3) - (8)].variable)) != SYMTAB_NOT_FOUND)
		{
			printError("Semantic Error: Variable %s already exists (must be fresh new variable!).\n", (yyvsp[(3) - (8)].variable).identifier);
		}
		op = ASSIGNMENT_OP;
		aux = gen_code_op(op);
		aux->oprel = SUBI;
		aux->val1 = varLocation((yyvsp[(3) - (8)].variable).identifier);
		aux->val2 = (yyvsp[(5) - (8)].literal).variable;
		aux->val3 = litLocationInt(1);
		(yyval.marker).quadtupla = nextQuad();
		op = ASSIGNMENT_OP;
		aux = gen_code_op(op);
		aux->oprel = ADDI;
		aux->val1 = varLocation((yyvsp[(3) - (8)].variable).identifier);
		aux->val2 = varLocation((yyvsp[(3) - (8)].variable).identifier);
		aux->val3 = litLocationInt(1);
		op = IF_OP;
		aux = gen_code_op(op);
		aux->oprel = LTI;
		aux->val1 = varLocation((yyvsp[(3) - (8)].variable).identifier);
		aux->val2 = (yyvsp[(7) - (8)].literal).variable;
		(yyval.marker).trueList = addToList(NULL, aux);
		op = GOTO;
		aux = gen_code_op(op);
		(yyval.marker).falseList = addToList(NULL, aux);
	}
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 249 "prac3.y"
    {
		(yyval.marker).quadtupla = nextQuad();
			op = GOTO;
			aux = gen_code_op(op);
			(yyval.marker).nextList = addToList(NULL, aux);
	}
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 257 "prac3.y"
    {
		(yyval.marker).quadtupla = nextQuad();
	}
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 262 "prac3.y"
    {
		fprintf(getDebugFile(), "Line %d:  Loop finished.\n", yylineno);
		backpatch((yyvsp[(1) - (4)].marker).trueList, (yyvsp[(2) - (4)].marker).quadtupla); 
			(yyval.statement) = (yyvsp[(1) - (4)].marker).falseList;
			backpatch((yyvsp[(3) - (4)].statement), (yyvsp[(1) - (4)].marker).quadtupla);
			backpatch((yyvsp[(4) - (4)].marker).nextList, (yyvsp[(1) - (4)].marker).quadtupla);
	}
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 269 "prac3.y"
    {
		fprintf(getDebugFile(), "Line %d:  Loop finished.\n", yylineno);
		backpatch((yyvsp[(1) - (4)].marker).trueList, (yyvsp[(2) - (4)].marker).quadtupla); 
			(yyval.statement) = (yyvsp[(1) - (4)].marker).falseList;
			backpatch((yyvsp[(3) - (4)].statement), (yyvsp[(1) - (4)].marker).quadtupla);
			backpatch((yyvsp[(4) - (4)].marker).nextList, (yyvsp[(1) - (4)].marker).quadtupla);
	}
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 278 "prac3.y"
    {
		fprintf(getDebugFile(), "Line %d:  Assigning on variable %s type %s.\n", yylineno, (yyvsp[(1) - (3)].variable).identifier, typeToString((yyvsp[(3) - (3)].literal).type));
		if((yyvsp[(3) - (3)].literal).type >=0 && (yyvsp[(3) - (3)].literal).type <4 && errors_found == 0){
			(yyvsp[(1) - (3)].variable) = fromLitToVar((yyvsp[(3) - (3)].literal), (yyvsp[(1) - (3)].variable).identifier);
			op = ASSIGNMENT;
			aux = gen_code_op(op);
			aux->val1 = varLocation((yyvsp[(1) - (3)].variable).identifier);
			aux->val2 = (yyvsp[(3) - (3)].literal).variable;
			(yyval.error)=NULL;
				
			storeSym((yyvsp[(1) - (3)].variable));
		}
	}
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 291 "prac3.y"
    {
		printError("Syntax error: unexpected symbol encountered.", "");
	}
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 296 "prac3.y"
    {
	}
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 298 "prac3.y"
    {
	}
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 300 "prac3.y"
    {
	}
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 304 "prac3.y"
    {
		(yyval.variable).identifier = (yyvsp[(1) - (1)].variable).identifier;
	}
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 309 "prac3.y"
    {
		(yyval.literal) = (yyvsp[(1) - (1)].literal);
		(yyval.literal).variable = litLocationString((yyvsp[(1) - (1)].literal).value.string_value);
	}
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 313 "prac3.y"
    {
		(yyval.literal) = (yyvsp[(1) - (1)].literal);
		(yyval.literal).variable = litLocationInt((yyvsp[(1) - (1)].literal).value.int_value);
	}
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 317 "prac3.y"
    {
		(yyval.literal) = (yyvsp[(1) - (1)].literal);
		(yyval.literal).variable = litLocationFloat((yyvsp[(1) - (1)].literal).value.float_value);
	}
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 326 "prac3.y"
    {
		
			(yyval.marker).quadtupla = nextQuad();
		
	}
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 333 "prac3.y"
    {
		fprintf(getDebugFile(), "Line %d:  Performed an OR operation between %s and %s.\n", yylineno, typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
		(yyval.literal).type = BOOLT;
		if((yyvsp[(1) - (3)].literal).type != BOOLT || (yyvsp[(3) - (3)].literal).type != BOOLT)
		{
			printError2("Semantic Error: Cannot operate OR between %s and %s.", typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
		}
		
			(yyval.literal).trueList = mergeLists((yyvsp[(1) - (3)].literal).trueList, (yyvsp[(3) - (3)].literal).trueList);
			backpatch((yyvsp[(1) - (3)].literal).falseList, (yyvsp[(2) - (3)].marker).quadtupla);
			(yyval.literal).falseList = (yyvsp[(3) - (3)].literal).falseList;
		
		(yyval.literal).value.bool_value = (yyvsp[(1) - (3)].literal).value.bool_value || (yyvsp[(3) - (3)].literal).value.bool_value;
	}
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 350 "prac3.y"
    {
		
			(yyval.marker).quadtupla = nextQuad();
		
	}
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 357 "prac3.y"
    {
		fprintf(getDebugFile(), "Line %d:  Performed an AND operation between %s and %s.\n", yylineno, typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
		(yyval.literal).type = BOOLT;
		if((yyvsp[(1) - (3)].literal).type != BOOLT || (yyvsp[(3) - (3)].literal).type != BOOLT)
		{
			printError2("Semantic Error: Cannot operate AND between %s and %s.", typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
		}
		
			(yyval.literal).falseList = mergeLists((yyvsp[(1) - (3)].literal).falseList, (yyvsp[(3) - (3)].literal).falseList);
			backpatch((yyvsp[(1) - (3)].literal).trueList, (yyvsp[(2) - (3)].marker).quadtupla);
			(yyval.literal).trueList = (yyvsp[(3) - (3)].literal).trueList;
		
		(yyval.literal).value.bool_value = (yyvsp[(1) - (3)].literal).value.bool_value && (yyvsp[(3) - (3)].literal).value.bool_value;
	}
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 374 "prac3.y"
    {
		if((yyvsp[(2) - (2)].literal).type != BOOLT)
		{
			printError("Semantic Error: Unexpected type expression (type: %s)", typeToString((yyvsp[(2) - (2)].literal).type));
		}
		else
		{
			(yyval.literal).value.bool_value = !(yyvsp[(2) - (2)].literal).value.bool_value;
		}
		(yyval.literal).trueList = (yyvsp[(2) - (2)].literal).falseList;
		(yyval.literal).falseList = (yyvsp[(2) - (2)].literal).trueList;
		(yyval.literal).type = BOOLT;
		fprintf(getDebugFile(), "Line %d:  Performed NOT operation on %s.\n", yylineno, typeToString((yyvsp[(2) - (2)].literal).type));
	}
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 389 "prac3.y"
    {
		fprintf(getDebugFile(), "Line %d:  Reading boolean literal or comparation.\n", yylineno);
	}
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 394 "prac3.y"
    {
		if((yyvsp[(1) - (1)].literal).type <0 || (yyvsp[(1) - (1)].literal).type >3)
		{
			printError("Semantic Error: Unexpected type expression (type: %s)", typeToString((yyvsp[(1) - (1)].literal).type));
		}
		(yyval.literal) = (yyvsp[(1) - (1)].literal);
	}
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 403 "prac3.y"
    {
		int opresult = canIOperateThem((yyvsp[(1) - (3)].literal), (yyvsp[(3) - (3)].literal), SUMA);
		fprintf(getDebugFile(), "Line %d:  Performed ADD operation between %s and %s.\n", yylineno, typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
		if(opresult == -1)
			printError2("Semantic Error: Cannot add types %s and %s.", typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
		(yyval.literal) = operateValues((yyvsp[(1) - (3)].literal), (yyvsp[(3) - (3)].literal), SUMA);
		if((opresult == INTT || opresult == FLOATT))
		{
			if(opresult != INTT)
			{
				op2 = ASSIGNMENT_UN;
				aux = gen_code_op(op2);
				if((yyvsp[(1) - (3)].literal).type == INTT)
				{
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(1) - (3)].literal).variable;
					(yyvsp[(1) - (3)].literal).variable = aux->val1;
				}
				if((yyvsp[(3) - (3)].literal).type == INTT)
				{
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(3) - (3)].literal).variable;
					(yyvsp[(3) - (3)].literal).variable = aux->val1;
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
			aux->val2 = (yyvsp[(1) - (3)].literal).variable;
			aux->val3 = (yyvsp[(3) - (3)].literal).variable;
			(yyval.literal).variable = aux->val1;
		}
	}
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 449 "prac3.y"
    {
		int opresult = canIOperateThem((yyvsp[(1) - (3)].literal), (yyvsp[(3) - (3)].literal), REST);
		fprintf(getDebugFile(), "Line %d: Performed SUB operation between %s and %s.\n", yylineno, typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
		if(opresult == -1)
		{
			printError2("Semantic Error: Operation - not allowed on types %s and %s.", typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
		}
		(yyval.literal) = operateValues((yyvsp[(1) - (3)].literal), (yyvsp[(3) - (3)].literal), REST);
		if((opresult == INTT || opresult == FLOATT))
		{
			if(opresult != INTT)
			{
				if((yyvsp[(1) - (3)].literal).type == INTT)
				{
					op2 = ASSIGNMENT_UN;
					aux = gen_code_op(op2);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(1) - (3)].literal).variable;
					(yyvsp[(1) - (3)].literal).variable = aux->val1;
				}
				if((yyvsp[(3) - (3)].literal).type == INTT)
				{
					op2 = ASSIGNMENT_UN;
					aux = gen_code_op(op2);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(3) - (3)].literal).variable;
					(yyvsp[(3) - (3)].literal).variable = aux->val1;
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
			aux->val2 = (yyvsp[(1) - (3)].literal).variable;
			aux->val3 = (yyvsp[(3) - (3)].literal).variable;
			(yyval.literal).variable = aux->val1;
		}
	}
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 498 "prac3.y"
    {
		fprintf(getDebugFile(), "Line %d: Performed unary ADD operation on %s.\n", yylineno, typeToString((yyvsp[(2) - (2)].literal).type));
		if((yyvsp[(2) - (2)].literal).type != STRINGT && (yyvsp[(2) - (2)].literal).type != BOOLT)
			(yyval.literal) = (yyvsp[(2) - (2)].literal);
		else
			printError("Semantic Error: Unary operator + not allowed on type %s.", typeToString((yyvsp[(2) - (2)].literal).type));
	}
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 505 "prac3.y"
    {
		fprintf(getDebugFile(), "Line %d: Performed unary SUB operation on %s.\n", yylineno, typeToString((yyvsp[(2) - (2)].literal).type));
		if((yyvsp[(2) - (2)].literal).type != STRINGT && (yyvsp[(2) - (2)].literal).type != BOOLT)
		{
			(yyval.literal) = (yyvsp[(2) - (2)].literal);
			if((yyval.literal).type == INTT)
			{
				(yyval.literal).value.int_value = -(yyval.literal).value.int_value;
				
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(2) - (2)].literal).variable;
					aux->oprel = CHSI;
					(yyval.literal).variable = aux->val1;
				
			}
			if((yyval.literal).type == FLOATT)
			{
				(yyval.literal).value.float_value = -(yyval.literal).value.float_value;
				
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(2) - (2)].literal).variable;
					aux->oprel = CHSF;
					(yyval.literal).variable = aux->val1;
				
			}
		}
		else
			printError("Semantic Error: Unary operator - not allowed on type %s.", typeToString((yyvsp[(2) - (2)].literal).type));
	}
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 542 "prac3.y"
    {
		int opresult = canIOperateThem((yyvsp[(1) - (3)].literal), (yyvsp[(3) - (3)].literal), MULT);
		fprintf(getDebugFile(), "Line %d: Performed MUL operation between %s and %s.\n", yylineno, typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
		if(opresult == -1)
		{
			printError2("Semantic Error: Operation * not allowed on types %s and %s.", typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
		}
		(yyval.literal) = operateValues((yyvsp[(1) - (3)].literal), (yyvsp[(3) - (3)].literal), MULT);
		if((opresult == INTT || opresult == FLOATT))
		{
			if(opresult!=INTT)
			{
				if((yyvsp[(1) - (3)].literal).type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(1) - (3)].literal).variable;
					(yyvsp[(1) - (3)].literal).variable = aux->val1;
				}
				if((yyvsp[(3) - (3)].literal).type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(3) - (3)].literal).variable;
					(yyvsp[(3) - (3)].literal).variable = aux->val1;
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
			aux->val2 = (yyvsp[(1) - (3)].literal).variable;
			aux->val3 = (yyvsp[(3) - (3)].literal).variable;
			(yyval.literal).variable = aux->val1;
		}
	}
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 589 "prac3.y"
    {
		int opresult = canIOperateThem((yyvsp[(1) - (3)].literal), (yyvsp[(3) - (3)].literal), DIVIS);
		fprintf(getDebugFile(), "Line %d: Performed MUL operation between %s and %s.\n", yylineno, typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
		if(opresult == -1)
		{
			printError2("Semantic Error: Operation * not allowed on types %s and %s.", typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
		}
		(yyval.literal) = operateValues((yyvsp[(1) - (3)].literal), (yyvsp[(3) - (3)].literal), MULT);
		if((opresult == INTT || opresult == FLOATT))
		{
			if(opresult != INTT)
			{
				if((yyvsp[(1) - (3)].literal).type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(1) - (3)].literal).variable;
					(yyvsp[(1) - (3)].literal).variable = aux->val1;
				}
				if((yyvsp[(3) - (3)].literal).type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(3) - (3)].literal).variable;
					(yyvsp[(3) - (3)].literal).variable = aux->val1;
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
			aux->val2 = (yyvsp[(1) - (3)].literal).variable;
			aux->val3 = (yyvsp[(3) - (3)].literal).variable;
			(yyval.literal).variable = aux->val1;
		}
		fprintf(getDebugFile(), "Line %d: Performed DIV operation between %s and %s.\n", yylineno, typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
		(yyval.literal) = operateValues((yyvsp[(1) - (3)].literal), (yyvsp[(3) - (3)].literal), DIVIS);
	}
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 644 "prac3.y"
    {
		(yyval.literal) = operateValues((yyvsp[(1) - (3)].literal), (yyvsp[(3) - (3)].literal), SUMA);
		printError("Semantic Error: Unexpected operator %s on expression. (Default operator: sum)", (yyvsp[(2) - (3)].error));
	}
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 650 "prac3.y"
    {
		int auxC = compareValues((yyvsp[(1) - (3)].literal), (yyvsp[(3) - (3)].literal));
		
		(yyval.literal).type = BOOLT;
		if(auxC == GREAT)
			(yyval.literal).value.bool_value = 1;
		else if(auxC != INCOMPAT)
			(yyval.literal).value.bool_value = 0;
		else
			printError2("Semantic Error: Cannot compare %s and %s.", typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
			if((yyvsp[(1) - (3)].literal).type != INTT || (yyvsp[(3) - (3)].literal).type != INTT)
			{
				if((yyvsp[(1) - (3)].literal).type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(1) - (3)].literal).variable;
					(yyvsp[(1) - (3)].literal).variable = aux->val1;
				}
				if((yyvsp[(3) - (3)].literal).type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(3) - (3)].literal).variable;
					(yyvsp[(3) - (3)].literal).variable = aux->val1;
				}
			}
			op = IF_OP;
			aux = gen_code_op(op);
			if((yyvsp[(1) - (3)].literal).type == INTT && (yyvsp[(3) - (3)].literal).type == INTT)
			{
				aux->oprel = GTI;
			}
			else
			{
				aux->oprel = GTF;
			}
			aux->val1 = (yyvsp[(1) - (3)].literal).variable;
			aux->val2 = (yyvsp[(3) - (3)].literal).variable;
			(yyval.literal).trueList = addToList(NULL, aux);
			op = GOTO;
			aux = gen_code_op(op);
			(yyval.literal).falseList = addToList(NULL, aux);
		
	}
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 699 "prac3.y"
    {
		int auxC = compareValues((yyvsp[(1) - (3)].literal), (yyvsp[(3) - (3)].literal));
		
		(yyval.literal).type = BOOLT;
		if(auxC == EQUAL || auxC == GREAT)
			(yyval.literal).value.bool_value = 1;
		else if(auxC != INCOMPAT)
			(yyval.literal).value.bool_value = 0;
		else
			printError2("Semantic Error: Cannot compare %s and %s.", typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
			
			if((yyvsp[(1) - (3)].literal).type != INTT || (yyvsp[(3) - (3)].literal).type != INTT)
			{
				if((yyvsp[(1) - (3)].literal).type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(1) - (3)].literal).variable;
					(yyvsp[(1) - (3)].literal).variable = aux->val1;
				}
				if((yyvsp[(3) - (3)].literal).type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(3) - (3)].literal).variable;
					(yyvsp[(3) - (3)].literal).variable = aux->val1;
				}
			}
			
			op = IF_OP;
			aux = gen_code_op(op);
			
			if((yyvsp[(1) - (3)].literal).type == INTT && (yyvsp[(3) - (3)].literal).type == INTT)
			{
				aux->oprel = GEI;
			}
			else
			{
				
				aux->oprel = GEF;
			}
			
			aux->val1 = (yyvsp[(1) - (3)].literal).variable;
			aux->val2 = (yyvsp[(3) - (3)].literal).variable;
			(yyval.literal).trueList = addToList(NULL, aux);
			op = GOTO;
			aux = gen_code_op(op);
			(yyval.literal).falseList = addToList(NULL, aux);
		
	}
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 753 "prac3.y"
    {
		int auxC = compareValues((yyvsp[(1) - (3)].literal), (yyvsp[(3) - (3)].literal));
		
		(yyval.literal).type = BOOLT;
		if(auxC == LESS)
			(yyval.literal).value.bool_value = 1;
		else if(auxC != INCOMPAT)
			(yyval.literal).value.bool_value = 0;
		else
			printError2("Semantic Error: Cannot compare %s and %s.", typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
		
			if((yyvsp[(1) - (3)].literal).type != INTT || (yyvsp[(3) - (3)].literal).type != INTT)
			{
				if((yyvsp[(1) - (3)].literal).type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(1) - (3)].literal).variable;
					(yyvsp[(1) - (3)].literal).variable = aux->val1;
				}
				if((yyvsp[(3) - (3)].literal).type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(3) - (3)].literal).variable;
					(yyvsp[(3) - (3)].literal).variable = aux->val1;
				}
			}
		
			op = IF_OP;
			aux = gen_code_op(op);
			if((yyvsp[(1) - (3)].literal).type == INTT && (yyvsp[(3) - (3)].literal).type == INTT)
			{
				aux->oprel = LTI;
			}
			else
			{
				aux->oprel = LTF;
			}
			aux->val1 = (yyvsp[(1) - (3)].literal).variable;
			aux->val2 = (yyvsp[(3) - (3)].literal).variable;
			(yyval.literal).trueList = addToList(NULL, aux);
			op = GOTO;
			aux = gen_code_op(op);
			(yyval.literal).falseList = addToList(NULL, aux);
		
	}
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 804 "prac3.y"
    {
		int auxC = compareValues((yyvsp[(1) - (3)].literal), (yyvsp[(3) - (3)].literal));
		
		(yyval.literal).type = BOOLT;
		if(auxC == LESS || auxC == EQUAL)
			(yyval.literal).value.bool_value = 1;
		else if(auxC != INCOMPAT)
			(yyval.literal).value.bool_value = 0;
		else
			printError2("Semantic Error: Cannot compare %s and %s.", typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
		
			if((yyvsp[(1) - (3)].literal).type != INTT || (yyvsp[(3) - (3)].literal).type != INTT)
			{
				if((yyvsp[(1) - (3)].literal).type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(1) - (3)].literal).variable;
					(yyvsp[(1) - (3)].literal).variable = aux->val1;
				}
				if((yyvsp[(3) - (3)].literal).type == INTT)
				{
					op = ASSIGNMENT_UN;
					aux = gen_code_op(op);
					aux->oprel = I2F;
					aux->val1 = tempLocation();
					aux->val2 = (yyvsp[(3) - (3)].literal).variable;
					(yyvsp[(3) - (3)].literal).variable = aux->val1;
				}
			}
		
			op = IF_OP;
			aux = gen_code_op(op);
			if((yyvsp[(1) - (3)].literal).type == INTT && (yyvsp[(3) - (3)].literal).type == INTT)
			{
				aux->oprel = LEI;
			}
			else
			{
				aux->oprel = LEF;
			}
			aux->val1 = (yyvsp[(1) - (3)].literal).variable;
			aux->val2 = (yyvsp[(3) - (3)].literal).variable;
			(yyval.literal).trueList = addToList(NULL, aux);
			op = GOTO;
			aux = gen_code_op(op);
			(yyval.literal).falseList = addToList(NULL, aux);
		
	}
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 855 "prac3.y"
    {
		int auxC = compareValues((yyvsp[(1) - (3)].literal), (yyvsp[(3) - (3)].literal));
		
		(yyval.literal).type = BOOLT;
		if(auxC == EQUAL)
			(yyval.literal).value.bool_value = 1;
		else if(auxC != INCOMPAT)
			(yyval.literal).value.bool_value = 0;
		else
			printError2("Semantic Error: Cannot compare %s and %s.", typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
		
			op = IF_OP;
			aux = gen_code_op(op);
			aux->oprel = EQ_OP;
			aux->val1 = (yyvsp[(1) - (3)].literal).variable;
			aux->val2 = (yyvsp[(3) - (3)].literal).variable;
			(yyval.literal).trueList = addToList(NULL, aux);
			op = GOTO;
			aux = gen_code_op(op);
			(yyval.literal).falseList = addToList(NULL, aux);
		
	}
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 877 "prac3.y"
    {
		int auxC = compareValues((yyvsp[(1) - (3)].literal), (yyvsp[(3) - (3)].literal));
		
		(yyval.literal).type = BOOLT;
		if(auxC == EQUAL)
			(yyval.literal).value.bool_value = 0;
		else if(auxC != INCOMPAT)
			(yyval.literal).value.bool_value = 1;
		else
			printError2("Semantic Error: Cannot compare %s and %s.", typeToString((yyvsp[(1) - (3)].literal).type), typeToString((yyvsp[(3) - (3)].literal).type));
			
		
			op = IF_OP;
			aux = gen_code_op(op);
			aux->oprel = NE_OP;
			aux->val1 = (yyvsp[(1) - (3)].literal).variable;
			aux->val2 = (yyvsp[(3) - (3)].literal).variable;
			(yyval.literal).trueList = addToList(NULL, aux);
			op = GOTO;
			aux = gen_code_op(op);
			(yyval.literal).falseList = addToList(NULL, aux);
		
	}
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 900 "prac3.y"
    {
		
			(yyval.literal).trueList = NULL;
			(yyval.literal).falseList = NULL;
		
	}
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 908 "prac3.y"
    {
		fprintf(getDebugFile(), "Line %d: Reading literal (not bool).\n", yylineno);
		(yyval.literal) = (yyvsp[(1) - (1)].literal);
		
			(yyval.literal).trueList = NULL;
			(yyval.literal).falseList = NULL;
		
	}
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 916 "prac3.y"
    {
		if(loadSym((yyvsp[(1) - (1)].variable), &(yyval.literal)) == SYMTAB_NOT_FOUND)
		{
			printError("Semantic Error: Variable %s does not exist", (yyvsp[(1) - (1)].variable).identifier);
		}
		(yyval.literal).variable = varLocation((yyvsp[(1) - (1)].variable).identifier);
		
			(yyval.literal).trueList = NULL;
			(yyval.literal).falseList = NULL;
		
		fprintf(getDebugFile(), "Line %d: Loading variable %s from type %s.\n", yylineno, (yyvsp[(1) - (1)].variable).identifier, typeToString((yyval.literal).type));
	}
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 928 "prac3.y"
    {
		(yyval.literal) = (yyvsp[(2) - (3)].literal);
	}
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 933 "prac3.y"
    {
		(yyval.error) = malloc(sizeof(char) * (strlen((yyvsp[(2) - (2)].error)) + strlen((yyvsp[(1) - (2)].error))));
		strcpy((yyval.error), (yyvsp[(1) - (2)].error));
		strcat((yyval.error), (yyvsp[(2) - (2)].error));
	}
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 938 "prac3.y"
    {
		(yyval.error) = (yyvsp[(1) - (1)].error);
	}
    break;


/* Line 1787 of yacc.c  */
#line 2617 "prac3y.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 942 "prac3.y"


int main()
{
	yylineno = 1;
	yyparse();
	if(errors_found == 0)
		printCode(getCodeFile());
	fprintf(stdout, "Fi!");
	return 0;
}

void yyerror (const char *s) {
	errors_found = 1;
	fprintf(stdout, "Error found on line %d: ", yylineno);
	fprintf(stdout, "%s\n", s);
}
