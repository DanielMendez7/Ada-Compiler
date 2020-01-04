/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IS = 258,
     BEG = 259,
     END = 260,
     PROCEDURE = 261,
     ID = 262,
     NUMBER = 263,
     TYPE = 264,
     ARRAY = 265,
     RAISE = 266,
     OTHERS = 267,
     RECORD = 268,
     IN = 269,
     OUT = 270,
     RANGE = 271,
     CONSTANT = 272,
     ASSIGN = 273,
     EXCEPTION = 274,
     NULLWORD = 275,
     LOOP = 276,
     IF = 277,
     THEN = 278,
     ELSEIF = 279,
     ELSE = 280,
     EXIT = 281,
     WHEN = 282,
     AND = 283,
     OR = 284,
     EQ = 285,
     NEQ = 286,
     LT = 287,
     GT = 288,
     GTE = 289,
     LTE = 290,
     TICK = 291,
     NOT = 292,
     EXP = 293,
     ARROW = 294,
     OF = 295,
     DOTDOT = 296,
     ENDIF = 297,
     ENDREC = 298,
     ENDLOOP = 299,
     EXITWHEN = 300,
     CASE = 301,
     ENDCASE = 302
   };
#endif
/* Tokens.  */
#define IS 258
#define BEG 259
#define END 260
#define PROCEDURE 261
#define ID 262
#define NUMBER 263
#define TYPE 264
#define ARRAY 265
#define RAISE 266
#define OTHERS 267
#define RECORD 268
#define IN 269
#define OUT 270
#define RANGE 271
#define CONSTANT 272
#define ASSIGN 273
#define EXCEPTION 274
#define NULLWORD 275
#define LOOP 276
#define IF 277
#define THEN 278
#define ELSEIF 279
#define ELSE 280
#define EXIT 281
#define WHEN 282
#define AND 283
#define OR 284
#define EQ 285
#define NEQ 286
#define LT 287
#define GT 288
#define GTE 289
#define LTE 290
#define TICK 291
#define NOT 292
#define EXP 293
#define ARROW 294
#define OF 295
#define DOTDOT 296
#define ENDIF 297
#define ENDREC 298
#define ENDLOOP 299
#define EXITWHEN 300
#define CASE 301
#define ENDCASE 302




/* Copy the first part of user declarations.  */
#line 6 "ada.y"

int yylex();
int yyerror(char*);
#include <stdio.h>
#include <string.h>
 
int MAXSIZE = 20;
int top = -1;

#include "../Data_Structures/listOfStructs.c" 
#include "../Data_Structures/stack.c"
#include "../Data_Structures/binaryTree.c"
#include "../Data_Structures/record.c"
#include "../Data_Structures/patchDataStructures.c"
 
// GLOBAL VARIABLES
TreeELEM stackOfTrees[50]; // Handles up to 50 Ada procedures in a single file
struct GlobalRecord globalRecord;
 
// Needed for Ada Loops, Ada Case statements, and Ada if, else if, else statements
ListELEM stackOfLL[300]; 

// Needed for Ada Exceptions
ExceptionListELEM stackOfLLExcep[300];
int jump_table[300]; 
 
// Needed for Ada Loops, Ada Case statements, Ada if, else if, else statements, and Ada Exceptions
ListNodePtr patchList;   // Patch List

// Needed for Ada Case Statements
RegisterStack stackOfReg[200];

 
FILE *output;           // Write Abstract Machine Instructions into the newly created file
extern int lineno; 


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 57 "ada.y"
{
    int integer;
    char *var;
    struct idnode* listPointer; //pointer for the list of Ids
    struct node* nodePtr;
    struct Record* ptrToRecord;
    struct RecordNode* ptrToRecordNode; //Used to handle read and write with multiple expression lists
    struct RecordList* adaRecordsInfo;  //Used to handle Ada record types
    struct  numListNode* ptrToNumNode;
}
/* Line 193 of yacc.c.  */
#line 238 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 251 "y.tab.c"

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
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   202

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  71
/* YYNRULES -- Number of rules.  */
#define YYNRULES  133
/* YYNRULES -- Number of states.  */
#define YYNSTATES  232

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   302

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      49,    50,    57,    56,    52,    55,    53,    58,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    51,    48,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    54,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,    14,    16,    19,    28,    30,    33,
      36,    40,    41,    48,    53,    55,    57,    60,    61,    65,
      67,    69,    73,    77,    81,    83,    86,    87,    99,   106,
     114,   118,   121,   125,   127,   131,   137,   139,   141,   143,
     147,   151,   152,   156,   160,   161,   163,   167,   170,   176,
     179,   180,   182,   184,   186,   188,   190,   192,   195,   197,
     201,   203,   207,   210,   212,   214,   217,   219,   225,   227,
     229,   232,   234,   238,   240,   243,   247,   249,   251,   253,
     261,   263,   265,   266,   269,   271,   276,   278,   281,   282,
     284,   286,   288,   292,   294,   296,   300,   302,   306,   308,
     311,   315,   317,   321,   323,   327,   330,   332,   334,   338,
     343,   348,   352,   353,   355,   357,   359,   361,   363,   365,
     367,   369,   371,   373,   375,   377,   380,   381,   383,   386,
     388,   393,   397,   399
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      60,     0,    -1,    61,    -1,    63,     3,    73,    62,    82,
     125,     5,    48,    -1,     4,    -1,     6,     7,    -1,    66,
       3,    73,    65,    82,   125,     5,    48,    -1,     4,    -1,
      67,    68,    -1,     6,     7,    -1,    49,    69,    50,    -1,
      -1,    71,    51,    70,    72,    48,    69,    -1,    71,    51,
      70,    72,    -1,    14,    -1,    15,    -1,    14,    15,    -1,
      -1,     7,    52,    71,    -1,     7,    -1,     7,    -1,    78,
      48,    73,    -1,    75,    48,    73,    -1,    81,    48,    73,
      -1,    74,    -1,    64,    74,    -1,    -1,     9,     7,     3,
      10,    49,    79,    41,    79,    50,    40,    72,    -1,     9,
       7,     3,    13,    76,    43,    -1,     9,     7,     3,    16,
      79,    41,    79,    -1,    77,    48,    76,    -1,    77,    48,
      -1,    71,    51,    72,    -1,    20,    -1,    71,    51,    72,
      -1,    71,    51,    17,    18,    80,    -1,     7,    -1,     8,
      -1,   114,    -1,    71,    51,    19,    -1,    87,    48,    82,
      -1,    -1,     7,    84,    86,    -1,    49,   113,    50,    -1,
      -1,    85,    -1,    85,    53,     7,    -1,    53,     7,    -1,
      53,     7,    49,   114,    50,    -1,    18,   114,    -1,    -1,
      20,    -1,    83,    -1,    89,    -1,   103,    -1,    94,    -1,
      88,    -1,    11,     7,    -1,    11,    -1,    90,    91,    44,
      -1,    21,    -1,    92,    48,    91,    -1,    92,    48,    -1,
      87,    -1,    93,    -1,    45,   112,    -1,    26,    -1,    95,
      96,     3,    97,    47,    -1,    46,    -1,   114,    -1,    97,
      98,    -1,    98,    -1,    99,   100,    82,    -1,    27,    -1,
     101,    39,    -1,   102,    54,   101,    -1,   102,    -1,   114,
      -1,    12,    -1,   104,   111,    23,    82,   105,   109,    42,
      -1,    22,    -1,   106,    -1,    -1,   107,   106,    -1,   107,
      -1,   108,   111,    23,    82,    -1,    24,    -1,   110,    82,
      -1,    -1,    25,    -1,   112,    -1,   114,    -1,   114,    52,
     113,    -1,   114,    -1,   115,    -1,   114,   121,   115,    -1,
     116,    -1,   115,   122,   116,    -1,   117,    -1,    55,   117,
      -1,   116,   123,   117,    -1,   118,    -1,   117,   124,   118,
      -1,   119,    -1,   119,    38,   119,    -1,    37,   119,    -1,
       8,    -1,     7,    -1,    49,   114,    50,    -1,     7,    49,
     114,    50,    -1,   119,    53,     7,   120,    -1,    49,   114,
      50,    -1,    -1,    28,    -1,    29,    -1,    30,    -1,    31,
      -1,    32,    -1,    33,    -1,    34,    -1,    35,    -1,    56,
      -1,    55,    -1,    57,    -1,    58,    -1,   126,   127,    -1,
      -1,    19,    -1,   127,   128,    -1,   128,    -1,    27,   129,
      39,    82,    -1,   129,    54,     7,    -1,     7,    -1,    12,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    69,    69,    73,   128,   131,   161,   231,   234,   304,
     319,   320,   323,   367,   401,   402,   403,   404,   407,   408,
     411,   415,   416,   417,   418,   422,   423,   426,   456,   482,
     508,   509,   512,   587,   590,   689,   692,   693,   696,   699,
     732,   733,   737,  1196,  1197,  1198,  1202,  1203,  1216,  1233,
    1238,  1243,  1245,  1246,  1247,  1248,  1249,  1253,  1263,  1274,
    1297,  1304,  1306,  1308,  1309,  1311,  1317,  1327,  1342,  1345,
    1360,  1361,  1364,  1401,  1404,  1422,  1428,  1431,  1445,  1449,
    1501,  1504,  1505,  1508,  1509,  1512,  1516,  1535,  1536,  1539,
    1558,  1568,  1573,  1574,  1577,  1578,  1618,  1619,  1672,  1673,
    1696,  1765,  1766,  1835,  1840,  1892,  1917,  1936,  2007,  2009,
    2083,  2137,  2138,  2141,  2142,  2145,  2146,  2147,  2148,  2149,
    2150,  2153,  2154,  2157,  2158,  2163,  2189,  2199,  2223,  2224,
    2227,  2239,  2240,  2246
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IS", "BEG", "END", "PROCEDURE", "ID",
  "NUMBER", "TYPE", "ARRAY", "RAISE", "OTHERS", "RECORD", "IN", "OUT",
  "RANGE", "CONSTANT", "ASSIGN", "EXCEPTION", "NULLWORD", "LOOP", "IF",
  "THEN", "ELSEIF", "ELSE", "EXIT", "WHEN", "AND", "OR", "EQ", "NEQ", "LT",
  "GT", "GTE", "LTE", "TICK", "NOT", "EXP", "ARROW", "OF", "DOTDOT",
  "ENDIF", "ENDREC", "ENDLOOP", "EXITWHEN", "CASE", "ENDCASE", "';'",
  "'('", "')'", "':'", "','", "'.'", "'|'", "'-'", "'+'", "'*'", "'/'",
  "$accept", "program", "main_body", "main_begin", "main_specification",
  "procedure_body", "procedure_begin", "procedure_body_prime",
  "procedure_specification", "formal_parameter_part", "parameters", "mode",
  "identifier_list", "type_name", "declarative_part",
  "declarative_part_prime", "types", "component_list", "record_object",
  "objects", "constant", "constant_expression", "exceptions",
  "sequence_of_statements", "proc_read_write_arrays_assign",
  "optional_parameters", "nested_record", "optional_assign",
  "statement_sequence_prime", "raise_statement", "loop_part", "loop_start",
  "loop_stmt_list", "loop_stmt", "when_condition", "case_statement",
  "case_start", "case_expression", "case_list", "case_handler",
  "when_start", "when_check", "when_expression_sequence",
  "when_expression", "if_statement", "if_start", "optional_else_if",
  "else_if_section", "else_if_stmt", "else_if_start", "optional_else",
  "else_start", "initial", "condition", "expression_list", "expression",
  "relation", "simple_expression", "term", "factor", "primary",
  "optional_array", "boolean_operation", "relational_operation",
  "adding_operation", "multiplying_operation", "exception_part",
  "exception_start", "exceptionList", "exceptHand", "choice_sequence", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,    59,    40,
      41,    58,    44,    46,   124,    45,    43,    42,    47
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    68,    69,    69,    70,    70,    70,    70,    71,    71,
      72,    73,    73,    73,    73,    74,    74,    75,    75,    75,
      76,    76,    77,    77,    78,    78,    79,    79,    80,    81,
      82,    82,    83,    84,    84,    84,    85,    85,    85,    86,
      86,    87,    87,    87,    87,    87,    87,    88,    88,    89,
      90,    91,    91,    92,    92,    93,    93,    94,    95,    96,
      97,    97,    98,    99,   100,   101,   101,   102,   102,   103,
     104,   105,   105,   106,   106,   107,   108,   109,   109,   110,
     111,   112,   113,   113,   114,   114,   115,   115,   116,   116,
     116,   117,   117,   118,   118,   118,   119,   119,   119,   119,
     119,   120,   120,   121,   121,   122,   122,   122,   122,   122,
     122,   123,   123,   124,   124,   125,   125,   126,   127,   127,
     128,   129,   129,   129
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     8,     1,     2,     8,     1,     2,     2,
       3,     0,     6,     4,     1,     1,     2,     0,     3,     1,
       1,     3,     3,     3,     1,     2,     0,    11,     6,     7,
       3,     2,     3,     1,     3,     5,     1,     1,     1,     3,
       3,     0,     3,     3,     0,     1,     3,     2,     5,     2,
       0,     1,     1,     1,     1,     1,     1,     2,     1,     3,
       1,     3,     2,     1,     1,     2,     1,     5,     1,     1,
       2,     1,     3,     1,     2,     3,     1,     1,     1,     7,
       1,     1,     0,     2,     1,     4,     1,     2,     0,     1,
       1,     1,     3,     1,     1,     3,     1,     3,     1,     2,
       3,     1,     3,     1,     3,     2,     1,     1,     3,     4,
       4,     3,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     0,     1,     2,     1,
       4,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     2,     0,     5,     1,    26,     0,    19,
       0,    26,     0,    11,     0,     0,    24,     0,     0,     0,
       9,     0,     0,    25,    26,     0,     8,     0,     4,    41,
      26,    26,    26,    18,     0,     0,     0,     0,    20,     0,
      39,    34,    44,    58,    51,    60,    80,    68,   126,    52,
       0,    56,    53,     0,    55,     0,    54,     0,    22,    21,
      23,     0,     0,     0,     7,    41,    10,    17,     0,     0,
       0,    50,    45,    57,   127,     0,     0,    41,    66,     0,
      63,     0,     0,    64,   107,   106,     0,     0,     0,     0,
      69,    94,    96,    98,   101,   103,     0,    90,    91,     0,
      33,     0,     0,     0,    36,    37,     0,   126,    14,    15,
       0,    35,    38,     0,    93,    47,     0,    42,     0,     0,
       0,   125,   129,    40,    65,    59,    62,     0,   105,     0,
      99,     0,   113,   114,     0,   115,   116,   117,   118,   119,
     120,     0,   122,   121,     0,   123,   124,     0,     0,     0,
      41,     0,     0,    28,    31,     0,     0,    16,    13,    43,
       0,     0,    49,    46,     3,   132,   133,     0,   128,    61,
       0,   108,    73,     0,    71,     0,    95,    97,   100,   102,
     104,   112,    82,     0,    32,    30,    29,     0,     0,    92,
       0,    41,     0,   109,    67,    70,    78,    41,     0,    76,
      77,     0,   110,    86,    88,    81,    84,     0,     0,     6,
      12,    48,   130,   131,    72,    74,     0,     0,    89,     0,
      41,    83,     0,     0,    75,   111,    79,    87,    41,     0,
      85,    27
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    29,     4,    11,    65,    12,    13,    26,
      36,   110,    14,    41,    15,    16,    17,   102,   103,    18,
     106,   111,    19,    48,    49,    71,    72,   117,    50,    51,
      52,    53,    81,    82,    83,    54,    55,    89,   173,   174,
     175,   197,   198,   199,    56,    57,   204,   205,   206,   207,
     219,   220,    96,    97,   113,    98,    91,    92,    93,    94,
      95,   202,   134,   141,   144,   147,    75,    76,   121,   122,
     167
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -110
static const yytype_int16 yypact[] =
{
       9,    21,    55,  -110,    65,  -110,  -110,    77,    78,    24,
      86,   101,   102,    80,    68,   111,  -110,    79,    82,    83,
    -110,   119,   129,  -110,    77,   119,  -110,    63,  -110,    70,
      77,    77,    77,  -110,    41,   131,    87,    85,  -110,   120,
    -110,  -110,    57,   132,  -110,  -110,  -110,  -110,   121,  -110,
      93,  -110,  -110,    52,  -110,    16,  -110,    16,  -110,  -110,
    -110,    94,    20,   104,  -110,    70,  -110,    99,    16,    16,
     135,   126,    92,  -110,  -110,   141,   123,    70,  -110,    16,
    -110,   103,   100,  -110,   105,  -110,    13,    16,    11,   148,
      89,    69,    66,    67,  -110,    -9,   130,  -110,    89,   104,
    -110,   107,   109,   108,  -110,  -110,   114,   121,   144,  -110,
     153,  -110,    89,   112,    -3,   117,    16,  -110,   154,   115,
      27,   123,  -110,  -110,  -110,  -110,    52,    16,   116,   -17,
      67,   143,  -110,  -110,    16,  -110,  -110,  -110,  -110,  -110,
    -110,    16,  -110,  -110,    11,  -110,  -110,    11,    13,   161,
      70,   133,   153,  -110,    20,   104,   166,  -110,   124,  -110,
      16,    16,    89,  -110,  -110,  -110,  -110,    -7,  -110,  -110,
       2,  -110,  -110,    -5,  -110,     1,    69,    66,    67,  -110,
     116,   127,   149,   104,  -110,  -110,  -110,   134,   119,  -110,
       8,    70,   168,  -110,  -110,  -110,  -110,    70,   138,   125,
      89,    16,  -110,  -110,   155,  -110,   149,    16,   128,  -110,
    -110,  -110,  -110,  -110,  -110,  -110,     1,    17,  -110,   139,
      70,  -110,   160,   145,  -110,  -110,  -110,  -110,    70,   153,
    -110,  -110
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,  -110,
      -4,  -110,   -21,  -109,    64,   175,  -110,    33,  -110,  -110,
     -94,  -110,  -110,   -63,  -110,  -110,  -110,  -110,   -47,  -110,
    -110,  -110,    62,  -110,  -110,  -110,  -110,  -110,  -110,    18,
    -110,  -110,   -27,  -110,  -110,  -110,  -110,   -16,  -110,  -110,
    -110,  -110,   -15,   118,    34,   -52,    59,    54,   -78,    49,
     -79,  -110,  -110,  -110,  -110,  -110,    91,  -110,  -110,    81,
    -110
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      33,   158,   107,    90,    37,   151,    80,   128,    84,    85,
     130,   132,   133,   196,   123,     1,   112,   114,    84,    85,
      84,    85,   172,    84,    85,   132,   133,     9,     5,   148,
     132,   133,   191,   171,   165,   129,   132,   133,    86,   166,
     100,   101,   194,   184,   149,   132,   133,   192,    86,   160,
      87,    61,   193,    86,    62,     6,    88,    63,   211,    42,
      87,   186,    87,    43,   162,    87,   178,   225,     7,   180,
      38,    88,    44,    45,    46,   170,    21,    42,    78,    80,
      39,    43,    40,     8,     9,    20,    10,   182,    35,   208,
      44,    45,    46,    22,    58,    59,    60,    79,    47,   135,
     136,   137,   138,   139,   140,    24,    69,     8,   114,   190,
      70,   104,   105,   108,   109,    28,    47,   132,   133,    27,
     231,   142,   143,   200,   145,   146,     9,    30,   212,    25,
      31,    32,    34,   101,   214,    64,    67,    66,    68,    73,
      74,    77,   115,    99,   116,   118,   119,   125,   126,   217,
     120,   131,   153,   150,   127,   155,   154,   227,   152,   157,
      38,   163,   159,   164,   200,   230,   161,    37,   181,   149,
     172,   187,   188,   203,   183,   213,   201,   215,   223,   216,
     218,   226,   209,   228,   210,   229,    23,   185,   169,   224,
     221,   195,   222,   176,   189,   177,   179,   124,   156,     0,
       0,     0,   168
};

static const yytype_int16 yycheck[] =
{
      21,   110,    65,    55,    25,    99,    53,    86,     7,     8,
      88,    28,    29,    12,    77,     6,    68,    69,     7,     8,
       7,     8,    27,     7,     8,    28,    29,     7,     7,    38,
      28,    29,    39,    50,     7,    87,    28,    29,    37,    12,
      20,    62,    47,   152,    53,    28,    29,    54,    37,    52,
      49,    10,    50,    37,    13,     0,    55,    16,    50,     7,
      49,   155,    49,    11,   116,    49,   144,    50,     3,   148,
       7,    55,    20,    21,    22,   127,    52,     7,    26,   126,
      17,    11,    19,     6,     7,     7,     9,   150,    24,   183,
      20,    21,    22,     7,    30,    31,    32,    45,    46,    30,
      31,    32,    33,    34,    35,     3,    49,     6,   160,   161,
      53,     7,     8,    14,    15,     4,    46,    28,    29,    51,
     229,    55,    56,   175,    57,    58,     7,    48,   191,    49,
      48,    48,     3,   154,   197,     4,    51,    50,    18,     7,
      19,    48,     7,    49,    18,    53,     5,    44,    48,   201,
      27,     3,    43,    23,    49,    41,    48,   220,    51,    15,
       7,     7,    50,    48,   216,   228,    49,   188,     7,    53,
      27,     5,    48,    24,    41,     7,    49,    39,    50,    54,
      25,    42,    48,    23,   188,    40,    11,   154,   126,   216,
     206,   173,   207,   134,   160,   141,   147,    79,   107,    -1,
      -1,    -1,   121
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,    60,    61,    63,     7,     0,     3,     6,     7,
       9,    64,    66,    67,    71,    73,    74,    75,    78,    81,
       7,    52,     7,    74,     3,    49,    68,    51,     4,    62,
      48,    48,    48,    71,     3,    73,    69,    71,     7,    17,
      19,    72,     7,    11,    20,    21,    22,    46,    82,    83,
      87,    88,    89,    90,    94,    95,   103,   104,    73,    73,
      73,    10,    13,    16,     4,    65,    50,    51,    18,    49,
      53,    84,    85,     7,    19,   125,   126,    48,    26,    45,
      87,    91,    92,    93,     7,     8,    37,    49,    55,    96,
     114,   115,   116,   117,   118,   119,   111,   112,   114,    49,
      20,    71,    76,    77,     7,     8,    79,    82,    14,    15,
      70,    80,   114,   113,   114,     7,    18,    86,    53,     5,
      27,   127,   128,    82,   112,    44,    48,    49,   119,   114,
     117,     3,    28,    29,   121,    30,    31,    32,    33,    34,
      35,   122,    55,    56,   123,    57,    58,   124,    38,    53,
      23,    79,    51,    43,    48,    41,   125,    15,    72,    50,
      52,    49,   114,     7,    48,     7,    12,   129,   128,    91,
     114,    50,    27,    97,    98,    99,   115,   116,   117,   118,
     119,     7,    82,    41,    72,    76,    79,     5,    48,   113,
     114,    39,    54,    50,    47,    98,    12,   100,   101,   102,
     114,    49,   120,    24,   105,   106,   107,   108,    79,    48,
      69,    50,    82,     7,    82,    39,    54,   114,    25,   109,
     110,   106,   111,    50,   101,    50,    42,    82,    23,    40,
      82,    72
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
#line 70 "ada.y"
    {  printf ("\n*******\nDONE.\n*******\n");  }
    break;

  case 3:
#line 77 "ada.y"
    {
                                        // POP: Procedure if finished so don't need this Binary Tree anymore
                                        printf("\nPopping scope for main, so print tree\n");
                                        printDFS(stackOfTrees[top].rootPointer);
                                        pop(stackOfTrees); 

                                        // EPILOGUE for the main procedure
                                        // 1)get return adress 2)get dynamic link and 3)update pc count
                                        fprintf(output, "%d: r%d := contents b, 1\n", globalRecord.pc++, globalRecord.registerNumber);
                                        fprintf(output, "%d: b := contents b, 3\n", globalRecord.pc++);
                                        fprintf(output, "%d: pc := r%d\n", globalRecord.pc++, globalRecord.registerNumber++);
                                        
                                        
                                        // NEW (MAIN PATCHLIST) update Patch List by including the pc count here
                                        ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                        
                                        // returnOffSet  gives size of main (i.e. 4 bookeeping plus any declared variables)
                                        // $4            is the pc line number when you see the keyword begin
                                        // gR.pc         is the start of mains AR (i.e. the pc number after the last AMI that currently prints out)

                                        // GOOD LINE TO HAVE FOR DEBUGING!
                                        // fprintf(output, "******** MAIN SIZE: %d,  BEGIN SEQUENCE OF STATEMENTS AT: %d,  MAINS AR: %d ********\n",
                                        // returnOffSet(stackOffSet), $4, globalRecord.pc);
                                        
                                        
                                        
                                        // Order of these lines of code MATTERS because linked list was inserting into the FRONT
                                        // Ex. Patchline: 4, JumpNumber: 6
                                        patchList = appendToList(patchList, tempHead->patchLine, (yyvsp[(4) - (8)].integer));
                                        tempHead = tempHead->next;
                                        
                                        // Ex. PatchLine: 1, JumpNumber: 32
                                        patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc + returnOffSet(stackOffSet)); 
                                        tempHead = tempHead->next;
                                        
                                        // Ex. PatchLine: 0, JumpNumber: 26
                                        patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc);
                                        tempHead = tempHead->next; // tempHead should be NULL after this line

                                        // Print out the ENITRE patch List from this whole program
                                        printf("Here is the updated patch list for main after its completely executed: \n");
                                        bubbleSort(patchList);
                                        printAllNodes(patchList);

                                        popList(stackOfLL);     // Pop mains toPatch linked list
                                        excepPopList(stackOfLLExcep); // Pop mains exception toPatch linked list
                                        popOffSet(stackOffSet); // Pop: Procedure is finished so don't need this offset anymore                                                                        
                                                    
}
    break;

  case 4:
#line 128 "ada.y"
    { (yyval.integer) = globalRecord.pc; }
    break;

  case 5:
#line 132 "ada.y"
    {

                                        push(stackOfTrees, (yyvsp[(2) - (2)].var));  // PUSH new binaryTree onto stack
                                        pushOffSet(stackOffSet); // PUSH new offset onto stack because of new procedure
                                        pushList(stackOfLL);     // PUSH new linkedList of patches onto stack (MAIN PATCH) 
                                        excepPushList(stackOfLLExcep);  // PUSH new linkedList of patches onto stack (MAIN PATCH)
                                        
                                        
                                        // ABSTRACT MACHINE INSTRUCTIONS
                                        // Order of putInToList matters! Linked List inserts to front
                                        putInToList(stackOfLL, globalRecord.pc); // Patch this program counter line number (MAIN PATCH) 
                                        fprintf(output, "%d: b := ?\n", globalRecord.pc++);

                                        putInToList(stackOfLL, globalRecord.pc); // Patch this program counter line number (MAIN PATCH)
                                        fprintf(output, "%d: contents b, 0 := ?\n", globalRecord.pc++);
                                        fprintf(output, "%d: contents b, 1 := 5\n", globalRecord.pc++);
                                        
                                        fprintf(output, "%d: r1 := 0\n", globalRecord.pc++);
                                        
                                        putInToList(stackOfLL, globalRecord.pc); // Patch this program counter line number (MAIN PATCH)
                                        fprintf(output, "%d: pc := ?\n", globalRecord.pc++);
                                        fprintf(output, "%d: halt\n", globalRecord.pc++);

                                        // GOOD TO HAVE THIS LINE FOR DEBUGGING!
                                        //fprintf(output, "******* End of Prologue for Main ******\n");

}
    break;

  case 6:
#line 165 "ada.y"
    {
                                        struct node* ptrToProcedureNode = (yyvsp[(1) - (8)].nodePtr);

                                        // After all the declarations, this procedure has a pc line number at the keyword "begin"
                                        ptrToProcedureNode->procStart = (yyvsp[(4) - (8)].integer);

                                        /***********/
                                        // PART 5 Get actual variable address and copy formal parameter address to a
                                        
                                        // GOOD TO HAVE THIS LINE FOR DEBUGGING!
                                        //fprintf(output, "Check procedure_body production. Get actual addr and copy x's value to a\n");
                                        struct node* parameterList = ptrToProcedureNode->next;
                                        Node* formalParamTreeNode = NULL;
                                        
                                        while (parameterList != NULL) {
                                            formalParamTreeNode = localSearch(stackOfTrees[top].rootPointer, parameterList->symbol);

                                            //fprintf(output, "***%s \n", parameterList->symbol);
                                            
                                            if ((strcmp(formalParamTreeNode->mode, "in out") == 0) ||
                                                (strcmp(formalParamTreeNode->mode, "out") == 0)) {
                                                
                                                fprintf(output, "%d: r%d := contents b, %d\n",
                                                        globalRecord.pc++, globalRecord.registerNumber, formalParamTreeNode->offset+1);
                                                
                                                fprintf(output, "%d: contents r%d := contents b, %d\n",
                                                        globalRecord.pc++, globalRecord.registerNumber++, formalParamTreeNode->offset);
                                            }

                                            //Put actual values list into the copy list because actual values list will get lost after popping the procedure 
                                            parameterList->offset = formalParamTreeNode->offset;
                                            parameterList->registerNumber = formalParamTreeNode->registerNumber;
                                            
                                            parameterList = parameterList->next;
                                        }
                                        /***********/
                                        
                                        // POP: Procedure is finished so don't need this Binary Tree anymore
                                        printf("\nPopping scope for %s, so print tree\n", ptrToProcedureNode->symbol);
                                        printDFS(stackOfTrees[top].rootPointer);
                                        pop(stackOfTrees);  

                                        // NEED For AMI to calculate size of procedure //i.e. $3 is 4 bookeeping plus any other variables
                                        ptrToProcedureNode->offset = (yyvsp[(3) - (8)].integer);                                                                          
                                        
                                        
                                        // EPLIOGUE for procedures in main 
                                        // 1)get return adress 2)get dynamic link and 3)update pc count
                                        fprintf(output, "%d: r%d := contents b, 1\n", globalRecord.pc++, globalRecord.registerNumber);
                                        fprintf(output, "%d: b := contents b, 3\n", globalRecord.pc++);
                                        fprintf(output, "%d: pc := r%d\n", globalRecord.pc++, globalRecord.registerNumber++);

                                        // GOOD TO HAVE THIS LINE FOR DEBUGGING!
                                        // For printing out the information for the current procedure
                                        //fprintf(output, "******** END OF PROCEDURE: %s,  SIZE: %d,  BEGIN SEQUENCE OF STATEMENTS AT: %d ********\n",
                                        //ptrToProcedureNode->symbol, returnOffSet(stackOffSet), $4);
                                        
                                        popOffSet(stackOffSet);       // POP: Procedure is finished so don't need this offset anymore
                                        excepPopList(stackOfLLExcep); // POP: Procedure is finished so don't need this linked list anymore

                                        // Start of next procedures AMI, so print line
                                        //fprintf(output, "******** START OF AMI for PROCEDURE *******\n");

}
    break;

  case 7:
#line 231 "ada.y"
    { (yyval.integer) = globalRecord.pc; }
    break;

  case 8:
#line 235 "ada.y"
    {
                                        // Updated version accounts for duplicates and connects precedure node to the formal parameters in the next binary tree
                                        struct node* treeNodeList = (yyvsp[(2) - (2)].nodePtr);          // treeNodeList is not in the binary tree, its a copy    
                                        struct node* ptrToProcedureNode = (yyvsp[(1) - (2)].nodePtr);
                                        ptrToProcedureNode->next = treeNodeList; // Connect Y1's next pointer to first formal parameter of the copy list
                                        ptrToProcedureNode->kind = procedure;    // kind is a procedure so enum value is 2
                                            
                                        struct node* currentNode;
                                        while (treeNodeList != NULL){
                                            
                                            //Duplicate Found so don't add to topmost stack
                                            if (localSearch(stackOfTrees[top].rootPointer, treeNodeList->symbol) != NULL) { //A
                                                printf("ERROR: Duplicate IDs name: %s, parent_type: %s, component_type: %s was not inserted into the symbol table\n",
                                                        treeNodeList->symbol, treeNodeList->parent_type->symbol, treeNodeList->component_type->symbol);

                                            }
                                            else {
                                            add(stackOfTrees, 0, treeNodeList->symbol);
                                            currentNode = localSearch(stackOfTrees[top].rootPointer, treeNodeList->symbol);
                                            currentNode->mode = (char*) malloc(sizeof(treeNodeList->symbol) + 1);   //allocate space for mode which is of type char* 
                                            strcpy(currentNode->mode, treeNodeList->symbol);
                                            currentNode->parent_type = treeNodeList->parent_type;
                                            currentNode->kind = treeNodeList->kind;        //These are all of kind variable so enum is 3
                                            // currentNode->next = treeNodeList->next;      //Don't need since I have the copy of list
                                            }

                                            treeNodeList = treeNodeList->next;
                                            
                                        }
                                        
                                        detachDuplicates(ptrToProcedureNode->next);    // Get rid of any duplicates found in the copy list of Binary Nodes
                                        printBTNodesNextDFS(ptrToProcedureNode->next); // Look at what nodes are still inside of your list of nodes


                                        /***********/
                                        // PART 5 Procedures with parameters
                                        // Traverse through all the formal parameters and make the appropriate space
                                        struct node* parameterList = ptrToProcedureNode->next;
                                        Node* formalParamTreeNode;

                                        while (parameterList != NULL) {
                                            //fprintf(output, "***%s \n", parameterList->symbol);
                                            
                                            formalParamTreeNode = localSearch(stackOfTrees[top].rootPointer, parameterList->symbol);
                                            formalParamTreeNode->offset = returnOffSet(stackOffSet); // Store current offset into the next node
                                            strcpy(formalParamTreeNode->mode, parameterList->mode);  // Enforce that this is a formal parameter!
                                            //formalParamTreeNode->registerNumber = globalRecord.registerNumber++;
                                            
                                            if ((strcmp(parameterList->mode, "in out") == 0) ||
                                                (strcmp(parameterList->mode, "out") == 0)) {
                                                raiseOffSet(stackOffSet, 2);                       // Accounts for copy out location
                                            }
                                            else if (strcmp(parameterList->mode, "in") == 0) {
                                                
                                                raiseOffSet(stackOffSet, 1);
                                            }
                                            
                                            
                                            parameterList = parameterList->next;
                                        } 
                                        /***********/

                                        
                                        (yyval.nodePtr) = ptrToProcedureNode; 
                                        ptrToProcedureNode = NULL; // Don't need this pointer to reference the procedure node anymore so make NULL
                                                    
}
    break;

  case 9:
#line 305 "ada.y"
    {
                                        add(stackOfTrees, 0, (yyvsp[(2) - (2)].var)); 
                                        (yyval.nodePtr) = localSearch(stackOfTrees[top].rootPointer, (yyvsp[(2) - (2)].var)); 
                                        push(stackOfTrees, (yyvsp[(2) - (2)].var));         // PUSH new binaryTree onto stack
                                        pushOffSet(stackOffSet);        // PUSH new offset onto stack because of new procedure
                                        excepPushList(stackOfLLExcep);  // PUSH (Procedures Patch for exceptions)
                                    
                                        // NEED for Abstact Machine Instructions 
                                        // Places current pc number into procedure Node in order to jump to it later
                                        struct node* procNodeInTree = globalSearch(stackOfTrees, (yyvsp[(2) - (2)].var));

}
    break;

  case 10:
#line 319 "ada.y"
    { (yyval.nodePtr) = (yyvsp[(2) - (3)].nodePtr); }
    break;

  case 11:
#line 320 "ada.y"
    { (yyval.nodePtr) = NULL; }
    break;

  case 12:
#line 324 "ada.y"
    {
                                        // SAME EXACT CODE AS THE PREVIOUS PRODUCTION WITH A FEW NEW THiNGS
                                        // 1) Make a list to create all the nodes
                                        struct idnode* linkedList = (yyvsp[(1) - (6)].listPointer); // Linked List to traverse
                                        struct node* listToPassUp;      // list of binary Nodes to pass up
                                        
                                        struct node* currentNode = createNode(0, linkedList->name);// Currently created node
                                        currentNode->mode = (char*) malloc(sizeof((yyvsp[(3) - (6)].var)) + 1);        // Allocate space for mode which is of type char* 
                                        strcpy(currentNode->mode, (yyvsp[(3) - (6)].var));
                                        currentNode->parent_type = globalSearch(stackOfTrees, (yyvsp[(4) - (6)].var)); // w is the parent_type
                                        currentNode->kind = variable;                              // kind is variable, so enum is 3

                                        struct node* ptrToLastNode = currentNode;   // Connects the next pointer of the last node to point to the front node of 
                                        listToPassUp = currentNode;                                // Now I can have currentNode point to something else
                                        linkedList = linkedList->next;                             // if Null then currentNode->next = NULL
                                        
                                        while (linkedList != NULL){
                                            // Have the next of the previous node point to the newly created node
                                            currentNode->next = createNode(0, linkedList->name);
                                            ptrToLastNode = currentNode->next;                     // Will point to the last node of the first half of nodes
                                            currentNode = currentNode->next;                       // Update pointer of currentNode

                                            
                                            currentNode->mode = (char*) malloc(sizeof((yyvsp[(3) - (6)].var)) + 1);
                                            strcpy(currentNode->mode, (yyvsp[(3) - (6)].var));
                                            currentNode->parent_type = globalSearch(stackOfTrees, (yyvsp[(4) - (6)].var)); // w is the parent_type
                                            currentNode->kind = variable;                              // kind is variable, so enum is 3
                                            
                                            linkedList = linkedList->next;  // Go to the next node in the linked list
                                                
                                            }

                                        // 2) Connect the end of the current list to the front of $6
                                        ptrToLastNode->next = (yyvsp[(6) - (6)].nodePtr);
                                        ptrToLastNode = NULL; //This prevents dangling pointers

                                        
                                        //Print out the current list of binary nodes
                                        //printBTNodesNextDFS(listToPassUp);
                                        (yyval.nodePtr) = listToPassUp;

}
    break;

  case 13:
#line 368 "ada.y"
    {
                                        struct idnode* linkedList = (yyvsp[(1) - (4)].listPointer); // Linked List to traverse
                                        struct node* listToPassUp;      // List of Binary Tree Nodes to pass up
                                        
                                        struct node* currentNode = createNode(0, linkedList->name); // Currently created node
                                        currentNode->mode = (char*) malloc(sizeof((yyvsp[(3) - (4)].var)) + 1);         // Allocate space for mode which is of type char* 
                                        strcpy(currentNode->mode, (yyvsp[(3) - (4)].var));
                                        currentNode->parent_type = globalSearch(stackOfTrees, (yyvsp[(4) - (4)].var)); //w is the parent_type
                                        currentNode->kind = variable;                              //kind is variable, so enum is 3

                                        listToPassUp = currentNode;                                // Now I can have currentNode point to something else
                                        linkedList = linkedList->next;                             // if Null then currentNode->next = NULL
                                        
                                        while (linkedList != NULL){
                                            //Have the next of the previous node point to the newly created node
                                            currentNode->next = createNode(0, linkedList->name);       
                                            currentNode = currentNode->next;                           // Update pointer of currentNode
                                            currentNode->mode = (char*) malloc(sizeof((yyvsp[(3) - (4)].var)) + 1);
                                            strcpy(currentNode->mode, (yyvsp[(3) - (4)].var));
                                            currentNode->parent_type = globalSearch(stackOfTrees, (yyvsp[(4) - (4)].var)); // w is the parent_type
                                            currentNode->kind = variable;                              // kind is variable, so enum is 3 
                                            
                                            linkedList = linkedList->next;  // Go to the next node in the linked list
                                                
                                            }

                                        // Print out the current list of binary nodes
                                        //printBTNodesNextDFS(listToPassUp);
                                        (yyval.nodePtr) = listToPassUp;

}
    break;

  case 14:
#line 401 "ada.y"
    {(yyval.var) = "in";}
    break;

  case 15:
#line 402 "ada.y"
    {(yyval.var) = "out";}
    break;

  case 16:
#line 403 "ada.y"
    {(yyval.var) = "in out";}
    break;

  case 17:
#line 404 "ada.y"
    {(yyval.var) = "in";}
    break;

  case 18:
#line 407 "ada.y"
    { (yyval.listPointer) = addToList((yyvsp[(3) - (3)].listPointer), (yyvsp[(1) - (3)].var)); }
    break;

  case 19:
#line 408 "ada.y"
    { struct idnode* theList = initialize((yyvsp[(1) - (1)].var)); (yyval.listPointer) = theList; }
    break;

  case 20:
#line 411 "ada.y"
    { (yyval.var) = (yyvsp[(1) - (1)].var); }
    break;

  case 21:
#line 415 "ada.y"
    { (yyval.integer) = returnOffSet(stackOffSet); }
    break;

  case 22:
#line 416 "ada.y"
    { (yyval.integer) = returnOffSet(stackOffSet); }
    break;

  case 23:
#line 417 "ada.y"
    { (yyval.integer) = returnOffSet(stackOffSet); }
    break;

  case 24:
#line 418 "ada.y"
    { (yyval.integer) = (yyvsp[(1) - (1)].integer); }
    break;

  case 25:
#line 422 "ada.y"
    { (yyval.integer) = returnOffSet(stackOffSet); }
    break;

  case 26:
#line 423 "ada.y"
    { (yyval.integer) = returnOffSet(stackOffSet); }
    break;

  case 27:
#line 427 "ada.y"
    {    
                                        // Duplicates in the current tree
                                        if (localSearch(stackOfTrees[top].rootPointer, (yyvsp[(2) - (11)].var)) != NULL) {
                                            printf("ERROR: Duplicate IDs\n");
                                        }
                                        else {
                                            // Found variable type in the outer context so insert into topmost binary tree
                                            Node* nodeType  = globalSearch(stackOfTrees, (yyvsp[(11) - (11)].var));
                                            if (nodeType != NULL) {
                                                
                                                // Add the ID (array) to the stack
                                                add(stackOfTrees, 0, (yyvsp[(2) - (11)].var));
                                                Node* first = localSearch(stackOfTrees[top].rootPointer, (yyvsp[(2) - (11)].var));

                                                // Make the c_t be a pointer to the type_name
                                                first->component_type = nodeType;
                                                first->kind = type;  //kind is type so enum is 4
                                                
                                                // Number of elements in array is $8 - $6
                                                first->lower = (yyvsp[(6) - (11)].integer);
                                                first->upper = (yyvsp[(8) - (11)].integer);

                                            }
                                            else
                                                printf("Could not find type %s in the outer context\n", (yyvsp[(11) - (11)].var));
                                        }
                        
}
    break;

  case 28:
#line 457 "ada.y"
    {                                                                                 
                                        // Duplicates in the current tree
                                        if (localSearch(stackOfTrees[top].rootPointer, (yyvsp[(2) - (6)].var)) != NULL) {
                                            printf("ERROR: Duplicate IDs\n");
                                        }
                                        else {
                                            // Dont need to find variable type in the outer context because record is not predefined
                                            // nor does it have a type_name like integer or boolean
                                            add(stackOfTrees, 0, (yyvsp[(2) - (6)].var));
                                            Node* first = localSearch(stackOfTrees[top].rootPointer, (yyvsp[(2) - (6)].var));

                                            // Record in Ada does not have a component_type or a parent_type
                                            first->kind = type;          // kind is type so enum is 9

                                            printf("This is printing out in the TYPE ID IS RECORD component_list ENDREC.\n");
                                            printSubVariables((yyvsp[(5) - (6)].adaRecordsInfo));
                                            printf("\n");
                                            
                                            first->listOfVariables = (yyvsp[(5) - (6)].adaRecordsInfo); // Contains all the variables inside of a record
                                            first->memorySpace = returnMemSpace(first->listOfVariables); // Total memory Space occupied by record

                                        }                            
                                                        
}
    break;

  case 29:
#line 483 "ada.y"
    {
                                        // Duplicates in the current tree
                                        if (localSearch(stackOfTrees[top].rootPointer, (yyvsp[(2) - (7)].var)) != NULL) {
                                            printf("ERROR: Duplicate IDs\n");
                                        }
                                        else {
                                            // Found variable type in the outer context so insert into topmost binary tree
                                            if (globalSearch(stackOfTrees, "integer") != NULL) {
                                                                                    
                                                    // Add range (ID) to the stack (example w)
                                                    add(stackOfTrees, 0, (yyvsp[(2) - (7)].var));
                                                    Node* first = localSearch(stackOfTrees[top].rootPointer, (yyvsp[(2) - (7)].var));

                                                    // QUESTION: Do I make the p_t, c_t or both be a pointer to the type_name? // ANSWER: Just c_t
                                                    // QUESTION: Can the range also go from a to z and not just 1 to 10, etc?  // ANSWER: ?
                                                    first->component_type = globalSearch(stackOfTrees, "integer");
                                                    first->kind = type;  // kind is type so enum is 4
                                                    first->lower = (yyvsp[(5) - (7)].integer);
                                                    first->upper = (yyvsp[(7) - (7)].integer);
                                            }
                                        }

}
    break;

  case 30:
#line 508 "ada.y"
    { (yyval.adaRecordsInfo) = combineRecordLists((yyvsp[(1) - (3)].adaRecordsInfo), (yyvsp[(3) - (3)].adaRecordsInfo)); }
    break;

  case 31:
#line 509 "ada.y"
    { (yyval.adaRecordsInfo) = (yyvsp[(1) - (2)].adaRecordsInfo); }
    break;

  case 32:
#line 513 "ada.y"
    {
                                        //printRoutine($1);
                                        printf("\n");
                                        idnodeptr traverseList = (yyvsp[(1) - (3)].listPointer); //List of variables that were declared

                                        // Offset, kind, memory space are extra pieces of information that need to be passed up to component_list 
                                        RecordListPtr recordListHead = NULL;

                                        // Search for the type_name in the outer context (ex. integer or boolean) or in the tree array or record type
                                        Node* varNodeType = globalSearch(stackOfTrees, (yyvsp[(3) - (3)].var));

                                        RecordListPtr currentRecord = NULL;

                                        // Parent type is found!
                                        if (varNodeType != NULL) {
                                            
                                        // Traverse through the whole list of declared variables of same type
                                        // Ex. a, b, c, : integer
                                            // For now assume that you dont' have duplicates, but will have to check that at some point
                                            while (traverseList != NULL) {

                                                // Create the record with all the information needed
                                                currentRecord = initializeRecord(traverseList->name);

                                                //printf("Found type? %s\n", strcmp(varNodeType->symbol, "integer") == 0 ? "true" : "false");
                                                // Used for simple types stored in records (ex. integer or boolean)
                                                if (strcmp(varNodeType->symbol, "integer") == 0 ||
                                                    strcmp(varNodeType->symbol, "boolean") == 0) {
                                                    
                                                    // Create the record with all the information needed
                                                    currentRecord->kind = variable;
                                                    currentRecord->parent_type = varNodeType;

                                                    //printf(" In if statement: %s,  %d    \n", currentRecord->variableName, currentRecord->kind);

                                                    // May need to do a for loop to go to the parent type and get its size
                                                    currentRecord->memSpace = currentRecord->parent_type->memorySpace; // Note: Changed from offset to memorySpace
                                                }

                                                // ARRAYS declared inside of RECORDS //FOR PART 2aii
                                                    else if (varNodeType->component_type != NULL) {
                                                        // This is to do the left_hand side of an assignment which is an array variable
                                                        currentRecord->kind = array_type;       // kind is array_type variable so enum is 9
                                                        currentRecord->parent_type = varNodeType;
                                                        
                                                        // Find size of array to by multiplying the number of elements with the size of each element
                                                        int sizeOfArray = ((currentRecord->parent_type->upper - currentRecord->parent_type->lower) + 1) * currentRecord->parent_type->component_type->memorySpace;

                                                        // Need for arrays declared inside of records
                                                        currentRecord->memSpace = sizeOfArray; 
                                                            
                                                        //printf("*** current offset: %d *** \n", returnOffSet(stackOffSet));
                                                        
                                                    }

                                                
                                                // TODO: records declared inside of records //FOR PART 2bii

                                                //printSubVariables(newHead);
                                                
                                                recordListHead = combineRecordLists(recordListHead, currentRecord);
                                            
                                                traverseList = traverseList->next;
                                            }
                                        }
                                        else printf("VarNodeType is NULL. This is printing out in the record_object production!\n");

                                        varNodeType = NULL; // Not using anymore

                                        // printSubVariables(recordListHead);

                                        (yyval.adaRecordsInfo) = recordListHead;

}
    break;

  case 33:
#line 587 "ada.y"
    {  (yyval.adaRecordsInfo) = NULL;  }
    break;

  case 34:
#line 591 "ada.y"
    { 
                                        printf("line#:  %d - ", lineno);
                                        printRoutine((yyvsp[(1) - (3)].listPointer));
                                        idnodeptr traverseList = (yyvsp[(1) - (3)].listPointer);
                                        printf(": %s\n", (yyvsp[(3) - (3)].var));


                                        while (traverseList != NULL) {
                                            
                                            // Duplicates in the current tree
                                            if (localSearch(stackOfTrees[top].rootPointer, traverseList->name) != NULL) {
                                                printf("ERROR: Duplicate IDs\n");
                                            }
                                            else {
                                                Node* varNodeType = globalSearch(stackOfTrees, (yyvsp[(3) - (3)].var));
                                                
                                                // Found variable type in stack so insert variable node into topmost binary tree
                                                // Example  a : integer or x:boolean in outer context (offset of 1) OR
                                                // Example  type w is array(0..2) of integer;   d : w
                                                // Example  type R1 is record    first : integer;second : boolean;   end record
                                                if (varNodeType != NULL) {
                                                    // Add the variable to the stack (example a)
                                                    add(stackOfTrees, 0, traverseList->name);
                                                    Node* first = localSearch(stackOfTrees[top].rootPointer, traverseList->name);

                                                    // Update variables from node struct
                                                    first->parent_type = varNodeType;

                                                    // For a : integer or b : boolean
                                                    // integer and boolean are in the outer context and do not have a component type
                                                    if (strcmp(first->parent_type->symbol, "integer") == 0 ||
                                                        strcmp(first->parent_type->symbol, "boolean") == 0) {

                                                        first->kind = variable;             // kind is variable so enum is 3
                                                        
                                                        // For read_integer or read_boolean
                                                        if (strcmp((yyvsp[(3) - (3)].var), "integer") == 0)
                                                            first->variableType = integer;  //enum of 0
                                                    
                                                        else if (strcmp((yyvsp[(3) - (3)].var), "boolean") == 0)
                                                            first->variableType = boolean;  //enum is 1
                                                        //else
                                                        //fprintf(output, "Error: check in production object -> identifier_list type_name\n");
                                                    
                                                        // Set outcome->offset equal to the current offset
                                                        first->offset = returnOffSet(stackOffSet);
                                                        //Increment globalOffSet by first->parent_type->offset
                                                        raiseOffSet(stackOffSet, first->parent_type->offset); //integer and boolean offset is 1
                                                    }

                                                    
                                                    // For d : w where w is an array
                                                    // w will have a component type
                                                    else if (first->parent_type->component_type != NULL) {
                                                        // This is to do the left_hand side of an assignment which is an array variable
                                                        first->kind = array_type;       // kind is array_type variable so enum is 9
                                                        
                                                        // Find the phantom offset of the variable relative to curren AR, if have something like w is array(4..7)
                                                        first->offset = returnOffSet(stackOffSet) - first->parent_type->lower;
                                                        //printf("**** Name: %s,  Offset: %d ****\n", first->symbol, first->offset);
                                                        
                                                        // Find size of array to by multiplying the number of elements with the size of each element
                                                        int sizeOfArray = ((first->parent_type->upper - first->parent_type->lower) + 1) * first->parent_type->component_type->memorySpace;

                                                        // Need for arrays of arrays or array of records or record inside of array
                                                        first->memorySpace = sizeOfArray; 
                                                            
                                                        raiseOffSet(stackOffSet, sizeOfArray);
                                                        //printf("*** current offset: %d *** \n", returnOffSet(stackOffSet));
                                                        
                                                    }

                                                    
                                                    // For e : y where y is a record
                                                    // y will NOT have a component type
                                                    else if (first->parent_type->component_type == NULL) {
                                                        
                                                        first->kind = record_type;     // kind is record_type variable so enum is 10
                                                        
                                                        // Print variables within a record
                                                        printSubVariables(varNodeType->listOfVariables);
                                                            
                                                        first->listOfVariables = varNodeType->listOfVariables;
                                                        first->offset = returnOffSet(stackOffSet);

                                                        // Records take up a varying amount of memory space
                                                        raiseOffSet(stackOffSet, first->parent_type->memorySpace);
                                                        
                                                    }
                                                    
                                                }
                                            } //end of else statement

                                            traverseList = traverseList->next;
                                        }
                                                
}
    break;

  case 36:
#line 692 "ada.y"
    {(yyval.integer) = 0;}
    break;

  case 37:
#line 693 "ada.y"
    {(yyval.integer) = (yyvsp[(1) - (1)].integer);}
    break;

  case 39:
#line 700 "ada.y"
    {                                       
                                        // DO NOT add exception to the outer context
                                        printf("line#:  %d - ", lineno);
                                        printRoutine((yyvsp[(1) - (3)].listPointer));
                                        printf(": exception\n");
                                        idnodeptr traverseList = (yyvsp[(1) - (3)].listPointer);


                                        while (traverseList != NULL){
                                            
                                            // Duplicates in the current tree
                                            if (localSearch(stackOfTrees[top].rootPointer, traverseList->name) != NULL) {
                                                printf("ERROR: Duplicate IDs\n");
                                            }
                                            // Exception type is a special type that is not found in outer context
                                            else{
                                                    // Add the variable to the stack (example bad)
                                                    add(stackOfTrees, 0, traverseList->name);
                                                    Node* first = localSearch(stackOfTrees[top].rootPointer, traverseList->name);

                                                    first->kind = exception;   //kind is exception so enum is 6
                                                    first->exceptionNumber = globalRecord.exceptionNumber++;
                                                    
                                                    //printf("kind %d\n", (int)first->kind);
                                            }

                                            traverseList = traverseList->next;
                                        }

}
    break;

  case 42:
#line 738 "ada.y"
    {
                                            struct node* variableInTree = globalSearch(stackOfTrees, (yyvsp[(1) - (3)].var));

                                            // KIND IS VARIABLE(enum 3):  An assignment statement with integer or boolean on the lefthand side
                                            if (variableInTree->kind == variable) {                              
                                                int walkBackCount = countGlobalSearch(stackOfTrees, (yyvsp[(1) - (3)].var));
                                        
                                                // Handles LOCAL variables in the LEFT-HAND side of an ASSIGNMENT
                                                if (walkBackCount == 0) {
                                                    fprintf(output, "%d: contents b, %d := ", globalRecord.pc++, variableInTree->offset);
                                                }

                                        
                                                // Handles NON-LOCAL variables in the LEFT_HAND side of an ASSIGNMENT
                                                else {
                                                    struct node* nodeInTree = globalSearch(stackOfTrees, (yyvsp[(1) - (3)].var));
                                                    if (nodeInTree != NULL) {

                                                        // r2 := b
                                                        fprintf(output, "%d: r%d := b\n", globalRecord.pc++, globalRecord.registerNumber);
                                                
                                                        // Loop updates the register and static link  Ex. r2 := contents r2, 2
                                                        while (walkBackCount != 0){
                                                            fprintf(output, "%d: r%d := contents r%d, 2\n",
                                                                    globalRecord.pc++, globalRecord.registerNumber, globalRecord.registerNumber);
                                                            walkBackCount--;
                                                        }

                                                        // Ex. contents r2, 5 := contents b, 4  or contents r3, 5 := contents r2, 6
                                                        fprintf(output, "%d: contents r%d, %d := ",
                                                                globalRecord.pc++, globalRecord.registerNumber++, nodeInTree->offset);
                                                    }
                                                    else
                                                        printf("Error: Check your statement_sequence_prime -> ID ASSIGN expression production");
                                                }



                                                // For the RIGHT HAND side of an ASSIGNMENT
                                                // For global variables (true && true) on right hand side
                                                if ((yyvsp[(3) - (3)].ptrToRecord) != NULL){
                                                    if ((yyvsp[(3) - (3)].ptrToRecord)->isRegister && (yyvsp[(3) - (3)].ptrToRecord)->isMemAddress)
                                                        fprintf(output, "contents r%d, %d\n",
                                                                (yyvsp[(3) - (3)].ptrToRecord)->registerNumber, ((yyvsp[(3) - (3)].ptrToRecord)->variableType == array)? (yyvsp[(3) - (3)].ptrToRecord)->phantomOffSet : (yyvsp[(3) - (3)].ptrToRecord)->offset);
                                                    
                                                    // For local variables (false && true) on right hand side
                                                    else if (!(yyvsp[(3) - (3)].ptrToRecord)->isRegister && (yyvsp[(3) - (3)].ptrToRecord)->isMemAddress) {
                                                        if ((yyvsp[(3) - (3)].ptrToRecord)->variableType == array)
                                                            fprintf(output, "contents b, r%d, %d\n", (yyvsp[(3) - (3)].ptrToRecord)->registerNumber, (yyvsp[(3) - (3)].ptrToRecord)->phantomOffSet);
                                                        else //If its an integer or a boolean
                                                            fprintf(output, "contents b, %d\n", (yyvsp[(3) - (3)].ptrToRecord)->offset);
                                                            
                                                    }
                                                    // For number and boolean literals (true && false) on the right hand side
                                                    else if ((yyvsp[(3) - (3)].ptrToRecord)->isRegister && !(yyvsp[(3) - (3)].ptrToRecord)->isMemAddress) 
                                                        fprintf(output, "r%d\n", (yyvsp[(3) - (3)].ptrToRecord)->registerNumber);
                                                }

                                                
                                            } //end of variable case

                                            
                                            /*********************************************************************************************/
                                            //KIND IS array_type(enum 4): An assignment statement with array  on the lefthand side
                                            else if (variableInTree->kind == array_type) {
                                                int walkBackCount = countGlobalSearch(stackOfTrees, (yyvsp[(1) - (3)].var));

                                                // Need if the expression inside an array is a variable
                                                int registerOfExpr = (yyvsp[(2) - (3)].ptrToRecordNode)->record->registerNumber;
                                                if ((yyvsp[(2) - (3)].ptrToRecordNode)->record->isMemAddress) {
                                                    registerOfExpr = globalRecord.registerNumber++;

                                                    fprintf(output, "%d: r%d := contents b, r%d\n",
                                                            globalRecord.pc++, registerOfExpr, (yyvsp[(2) - (3)].ptrToRecordNode)->record->offset);
                                                }


                                                // Handles LOCAL variables in the LEFT-HAND side of an ASSIGNMENT
                                                if (walkBackCount == 0) {
                                                    fprintf(output, "%d: contents b, r%d, %d := ",
                                                            globalRecord.pc++, registerOfExpr, variableInTree->offset);
                                                }

                                        
                                                // Handles NON-LOCAL variables in the LEFT_HAND side of an ASSIGNMENT
                                                else {
                                                    struct node* nodeInTree = globalSearch(stackOfTrees, (yyvsp[(1) - (3)].var));
                                                    if (nodeInTree != NULL) {

                                                        // r2 := b
                                                        fprintf(output, "%d: r%d := b\n", globalRecord.pc++, globalRecord.registerNumber);
                                                
                                                        // Loop updates the register and static link  Ex. r2 := contents r2, 2
                                                        while (walkBackCount != 0) {
                                                            fprintf(output, "%d: r%d := contents r%d, 2\n",
                                                                    globalRecord.pc++, globalRecord.registerNumber, globalRecord.registerNumber);
                                                            walkBackCount--;
                                                        }

                                                        // Add the base address of current variable with offset of expression inside of the array
                                                        fprintf(output, "%d: r%d := r%d + r%d\n",
                                                                globalRecord.pc++, globalRecord.registerNumber, globalRecord.registerNumber, registerOfExpr);
                                                        
                                                        // Ex. contents r2, 5 := contents b, 4  or contents r3, 5 := contents r2, 6
                                                        fprintf(output, "%d: contents r%d, %d := ",
                                                                globalRecord.pc++, globalRecord.registerNumber++, nodeInTree->offset);
                                                    }
                                                    else
                                                        printf("Error: Check your statement_sequence_prime -> ID ASSIGN expression production");
                                                }
                                                
                                                

                                                // For the RIGHT HAND side of an ASSIGNMENT
                                                // For global variables (true && true) on right hand side
                                                if ((yyvsp[(3) - (3)].ptrToRecord) != NULL){
                                                    if ((yyvsp[(3) - (3)].ptrToRecord)->isRegister && (yyvsp[(3) - (3)].ptrToRecord)->isMemAddress)
                                                        fprintf(output, "contents r%d, %d\n",
                                                                (yyvsp[(3) - (3)].ptrToRecord)->registerNumber, ((yyvsp[(3) - (3)].ptrToRecord)->variableType == array)? (yyvsp[(3) - (3)].ptrToRecord)->phantomOffSet : (yyvsp[(3) - (3)].ptrToRecord)->offset);
                                                    
                                                    // For local variables (false && true) on right hand side
                                                    else if (!(yyvsp[(3) - (3)].ptrToRecord)->isRegister && (yyvsp[(3) - (3)].ptrToRecord)->isMemAddress) {
                                                        if ((yyvsp[(3) - (3)].ptrToRecord)->variableType == array)
                                                            fprintf(output, "contents b, r%d, %d\n", (yyvsp[(3) - (3)].ptrToRecord)->registerNumber, (yyvsp[(3) - (3)].ptrToRecord)->phantomOffSet);
                                                        else // If its an integer or a boolean
                                                            fprintf(output, "contents b, %d\n", (yyvsp[(3) - (3)].ptrToRecord)->offset);
                                                    }
                                                    
                                                    // For number and boolean literals (true && false) on the right hand side
                                                    else if ((yyvsp[(3) - (3)].ptrToRecord)->isRegister && !(yyvsp[(3) - (3)].ptrToRecord)->isMemAddress) 
                                                        fprintf(output, "r%d\n", (yyvsp[(3) - (3)].ptrToRecord)->registerNumber);
                                                }

                                            } // end of array_type


                                            
                                            /*************************************************************************************************************/
                                            // KIND IS record_type(enum 10): An assignment statement with record on the lefthand side
                                            else if (variableInTree->kind == record_type) {
                                                fprintf(output, "THIS IS A RECORD TYPE\n");
                                                
                                                recordptr subVariableInfo = createRecord();
                                                
                                                // If the LEFT-HAND side of an ASSIGNMENT is accessing a variable from a record!
                                                recordptr variableInfo = (yyvsp[(2) - (3)].ptrToRecordNode)->record; //This is the generic variable of Ada record type Ex.

                                                // fprintf(output, "Searching for: %s\n", $2->record->variableName);
                                                
                                                struct node* nodeInTree = globalSearch(stackOfTrees, (yyvsp[(1) - (3)].var)); //Find node of Ada record type in binary Tree
                                                
                                                // Find the sub-variable inside of the Ada record type and calculate its offset
                                                int subVariableOffSet = 0;
                                                RecordListPtr traverseList = nodeInTree->listOfVariables;

                                                
                                                while( (traverseList != NULL) && !(strcmp(traverseList->variableName, variableInfo->variableName) == 0) ) {
                                                    subVariableOffSet = subVariableOffSet + traverseList->memSpace;
                                                    // printf("In primary production %s\n", traverseList->variableName); //TODO: Fix this error!
                                        
                                                    traverseList = traverseList->next; 
                                                }

                                                subVariableOffSet = nodeInTree->offset + subVariableOffSet;
                                    
                                                // Found sub-variable inside of the Ada record type so continue
                                                if (traverseList != NULL) {
                                                    // Add on the base offset of variable of type Ada record
                                                    subVariableInfo->offset = subVariableOffSet;

                                                    if (traverseList->kind == array_type){
                                                        subVariableInfo->variableType = array;
                                                    }
                                                    else
                                                        subVariableInfo->kind = traverseList->kind;
                                                            
                                                    // subVariable->parent_type = traverseList->record->parent_type //May not need this line
                                                    subVariableInfo->isRegister = false;    // local variables are NOT stored in a register
                                                    subVariableInfo->isMemAddress = true;   // MUST DISPLAY contents b, 4 etc. for local variables

                                                }
                                                else 
                                                    printf("Could not find the variable of this Ada record type! This is printing out in the ID opt_param opt_assign production.\n");


                                                // Start printing out AMI!!!
                                                int walkBackCount = countGlobalSearch(stackOfTrees, (yyvsp[(1) - (3)].var));
                                        
                                                // Handles LOCAL variables in the LEFT-HAND side of an ASSIGNMENT
                                                if (walkBackCount == 0) {
                                                    fprintf(output, "%d: contents b, %d := ", globalRecord.pc++, subVariableInfo->offset);
                                                }

                                                
                                                // Handles NON-LOCAL variables in the LEFT_HAND side of an ASSIGNMENT
                                                else {
                                                    struct node* nodeInTree = globalSearch(stackOfTrees, (yyvsp[(1) - (3)].var));
                                                    if (nodeInTree != NULL) {

                                                        // r2 := b
                                                        fprintf(output, "%d: r%d := b\n", globalRecord.pc++, globalRecord.registerNumber);
                                                
                                                        // Loop updates the register and static link  Ex. r2 := contents r2, 2
                                                        while (walkBackCount != 0){
                                                            fprintf(output, "%d: r%d := contents r%d, 2\n",
                                                                    globalRecord.pc++, globalRecord.registerNumber, globalRecord.registerNumber);
                                                            walkBackCount--;
                                                        }


                                                        // Add the base address of current variable with offset of expression inside of the array
                                                        if (subVariableInfo->variableType == array) {
                                                            fprintf(output, "%d: r%d := r%d + r%d\n",
                                                                    globalRecord.pc++, globalRecord.registerNumber, globalRecord.registerNumber, (yyvsp[(2) - (3)].ptrToRecordNode)->record->registerNumber);
                                                        }

                                                        
                                                        // Ex. contents r2, 5 := contents b, 4  or contents r3, 5 := contents r2, 6
                                                        fprintf(output, "%d: contents r%d, %d := ",
                                                                globalRecord.pc++, globalRecord.registerNumber++, subVariableInfo->offset);
                                                    }
                                                    else
                                                        printf("Error: Check your statement_sequence_prime -> ID ASSIGN expression production");
                                                }
                                                



                                                // For the RIGHT HAND side of an ASSIGNMENT
                                                // For global variables (true && true) on right hand side
                                                if ((yyvsp[(3) - (3)].ptrToRecord) != NULL){
                                                    if ((yyvsp[(3) - (3)].ptrToRecord)->isRegister && (yyvsp[(3) - (3)].ptrToRecord)->isMemAddress) {
                                                        if ((yyvsp[(3) - (3)].ptrToRecord)->variableType == array)
                                                            fprintf(output, "contents r%d, %d\n", (yyvsp[(3) - (3)].ptrToRecord)->registerNumber, (yyvsp[(3) - (3)].ptrToRecord)->phantomOffSet);
                                                        else
                                                            fprintf(output, "contents r%d, %d\n", (yyvsp[(3) - (3)].ptrToRecord)->registerNumber, (yyvsp[(3) - (3)].ptrToRecord)->offset);
                                                    }
                                                    // For local variables (false && true) on right hand side
                                                    else if (!(yyvsp[(3) - (3)].ptrToRecord)->isRegister && (yyvsp[(3) - (3)].ptrToRecord)->isMemAddress) {
                                                        if ((yyvsp[(3) - (3)].ptrToRecord)->variableType == array)
                                                            fprintf(output, "contents b, r%d, %d\n", (yyvsp[(3) - (3)].ptrToRecord)->registerNumber, (yyvsp[(3) - (3)].ptrToRecord)->phantomOffSet);
                                                        else // If its an integer or a boolean
                                                            fprintf(output, "contents b, %d\n", (yyvsp[(3) - (3)].ptrToRecord)->offset);
                                                    }
                                                    // For number and boolean literals (true && false) on the right hand side
                                                    else if ((yyvsp[(3) - (3)].ptrToRecord)->isRegister && !(yyvsp[(3) - (3)].ptrToRecord)->isMemAddress) 
                                                        fprintf(output, "r%d\n", (yyvsp[(3) - (3)].ptrToRecord)->registerNumber);
                                                }
                                                
                                                
                                            } //end of record_type




                                            
                                            /*************************************************************************************************************/
                                            // KIND IS READ_ROUTINE(enum 7):
                                            else if (variableInTree->kind == read_routine) {
                                                RecordNodePtr traverseList = (yyvsp[(2) - (3)].ptrToRecordNode);

                                                // QUESTION: is read(a, g, h) possible? If not then replace while loop with if statement
                                                while (traverseList != NULL) {
                                                    fprintf(output, "%d: ", globalRecord.pc++);
                                                    
                                                    if (traverseList->record->variableType == integer) //enum value of 0
                                                        fprintf(output, "read_integer ");
                                                    else if(traverseList->record->variableType == boolean) //enum value of 1
                                                            fprintf(output, "read_boolean ");
                                                    else
                                                        fprintf(output, "Error:variable type not found! Check production, proc_read_write_arrays_assign\n");

                                                    // Make sure whatevers in read is a variable and not a literal!
                                                    if (traverseList->record->isMemAddress) {
                                                        if (!traverseList->record->isRegister) //For Local Variables
                                                            fprintf(output, "contents b, %d\n", traverseList->record->offset);
                                                        else                                   //For Non-Local Variables
                                                            fprintf(output, "contents r%d, %d\n", traverseList->record->registerNumber, traverseList->record->offset);
                                                    }
                                                    else
                                                        fprintf(output, "Error: A literal made its way into read(literal). Check production, proc_read_write_arrays_assign ");
                                                                                                                            
                                                    traverseList = traverseList->next;
                                                    
                                                }
                                            } // end of read case


                                            /*************************************************************************************************************/
                                            // KIND IS WRITE_ROUTINE(enum 8)
                                            else if (variableInTree->kind == write_routine) {
                                                RecordNodePtr traverseList = (yyvsp[(2) - (3)].ptrToRecordNode);
                                                
                                                while (traverseList != NULL) {
                                                    fprintf(output, "%d: write ", globalRecord.pc++);

                                                    if (traverseList->record->isMemAddress) {
                                                        if (!traverseList->record->isRegister) //For Local Variables
                                                            fprintf(output, "contents b, %d\n", traverseList->record->offset);
                                                        else                                   //For Non-Local Variables
                                                            fprintf(output, "contents r%d, %d\n", traverseList->record->registerNumber, traverseList->record->offset);
                                                    }
                                                    else {
                                                        //literals
                                                        if (traverseList->record->isRegister) {                                                                                 
                                                            fprintf(output, "r%d\n", traverseList->record->registerNumber);

                                                        }
                                                    }
                                                                                                                            
                                                    traverseList = traverseList->next;
                                                    
                                                }
                                            }// end of write case

                                            
                                            /*************************************************************************************************************/
                                            // KIND IS PROCEDURE(enum 2): a procedure so calculate static, dynamic, next base, and return address
                                            else if (variableInTree->kind == procedure) {


                                                int procedureARBase = globalRecord.registerNumber; // TODO: Need for Part 5
                                                
                                                // Jump to start of current Procedure AR to place in values for DL, SL,etc.
                                                fprintf(output, "%d: r%d := b\n", globalRecord.pc++, globalRecord.registerNumber);
                                                fprintf(output, "%d: b := contents r%d, 0 \n", globalRecord.pc++, globalRecord.registerNumber);

                                                // Dynamic Link
                                                fprintf(output, "%d: contents b, 3 := r%d\n", globalRecord.pc++, globalRecord.registerNumber);

                                            
                                                // Static Link // MUST DO AN IF STATEMENT THAT CHECKS THE STATIC LINK OF THE PROCEDURE
                                                int walkBackCount = countGlobalSearch(stackOfTrees, (yyvsp[(1) - (3)].var));
                                                if (walkBackCount == 0) {
                                                    //fprintf(output, "%d: contents b, 2 := r%d\n", globalRecord.pc++, globalRecord.registerNumber++);
                                                }
                                                else {
                                                    int registerHolder = globalRecord.registerNumber++;  //r4
                                                    fprintf(output, "%d: r%d := contents r%d, 2\n",
                                                            globalRecord.pc++, globalRecord.registerNumber, registerHolder);
                                                    walkBackCount--;
                                                
                                                    while (walkBackCount != 0){
                                                        fprintf(output, "%d: r%d := contents r%d, 2\n",
                                                                globalRecord.pc++, globalRecord.registerNumber, globalRecord.registerNumber);
                                                        walkBackCount--;
                                                    }

                                                }
                                                fprintf(output, "%d: contents b, 2 := r%d\n", globalRecord.pc++, globalRecord.registerNumber++);

                                            
                                                // Calculate next base of AR //Figure out the offset of the next procedure
                                                fprintf(output, "%d: r%d := %d\n", globalRecord.pc++, globalRecord.registerNumber, variableInTree->offset);
                                                fprintf(output, "%d: contents b, 0 := b + r%d\n", globalRecord.pc++, globalRecord.registerNumber++);


                                                /***************************/
                                                // Part 5 Fix in/in out parameters  Fix procedure call with parameters
                                                // GOOD TO HAVE THIS LINE FOR DEBUGGING
                                                //fprintf(output, "Check production proc_read_write_arrays_assign.   Fix in/in out parameters right here.\n");
                                                RecordNodePtr argumentParamList = (yyvsp[(2) - (3)].ptrToRecordNode); //Ex. inner(a, 5 + 4) where a and 5 + 4 are the argumentParameters
                                                Node* parameterList = variableInTree->next;  // inner(x : in out integer, y : in integer)
                                                
                                                //Node* formalParamTreeNode = NULL;  //USED FOR TESTING
                                                // Need to figure out if, a in inner(a), is a global or local variable in a parameter
                                                int formalParamWalk = 0;  
                                                int walkBackRegister = 0;
                                                int changeProcedureAR = procedureARBase;
                                                
                                                
                                                while (argumentParamList != NULL) {                                                             
                                                    // USED FOR TESTING             
                                                    //formalParamTreeNode = globalSearch(stackOfTrees, argumentParamList->record->variableName);
                                                    //printf("Procedure Name: %s,  Formal Parameters: %s\n",
                                                    //variableInTree->symbol, argumentParamList->record->variableName);

                                                    // If true then procedure has an expression as a formal parameter (ex. eee (x + 2)), 
                                                    // if false then procedure has a variable as a formal parameter (ex. ddd (a) where a is a variable)
                                                    formalParamWalk = strcmp(argumentParamList->record->variableName, "") == 0 ? 0 : countGlobalSearch(stackOfTrees, argumentParamList->record->variableName);

                                                    
                                                    //Argument Parameter, x, is CASE 1: "in out" or Case 3: "out"
                                                    if ((strcmp(parameterList->mode, "in out") == 0) || (strcmp(parameterList->mode, "out") == 0)) { 
                                                        // Do walk back to a's base
                                                        // Formal Parameter is a global variable

                                                        // GOOD TO HAVE THIS LINE FOR DEBUGGING PROCEDURES WITH FORMAL PARAMETERS
                                                        //fprintf(output, "-----------%s with offset: %d----------\n",
                                                        //argumentParamList->record->variableName, argumentParamList->record->offset);

                                                        // CASE 1 and CASE 3
                                                        if (formalParamWalk != 0) {
                                                            
                                                            fprintf(output, "%d: r%d := contents r%d, 2\n", 
                                                                    globalRecord.pc++, globalRecord.registerNumber, changeProcedureAR);
                                                            formalParamWalk--;
                                                            
                                                            while (formalParamWalk != 0) {
                                                                fprintf(output, "%d: r%d := contents r%d, 2\n",
                                                                        globalRecord.pc++, globalRecord.registerNumber, globalRecord.registerNumber);
                                                                formalParamWalk--;
                                                            }
                                                            changeProcedureAR = globalRecord.registerNumber++;
                                                        }

                                                        // CASE 1 "in out"
                                                        if (strcmp(parameterList->mode, "in out") == 0) {
                                                            //Formal Parameter is a local variable
                                                            fprintf(output, "%d: contents b, %d := contents r%d, %d\n",
                                                                    globalRecord.pc++, parameterList->offset, changeProcedureAR, argumentParamList->record->offset);
                                                        }

                                                        
                                                        // CASE 1 "in out" & CASE 3 "out"
                                                        int saveOffSet = globalRecord.registerNumber++;
                                                        fprintf(output, "%d: r%d := %d\n",
                                                                globalRecord.pc++, saveOffSet, argumentParamList->record->offset);
                                                    
                                                        fprintf(output, "%d: r%d := r%d + r%d\n",
                                                                globalRecord.pc++, globalRecord.registerNumber, changeProcedureAR, saveOffSet );

                                                        fprintf(output, "%d: contents b, %d := r%d\n",
                                                                globalRecord.pc++, parameterList->offset + 1, globalRecord.registerNumber++);
                                                    }
                                                    
                                                    
                                                    // CASE 2: x is "in"
                                                    else if (strcmp(parameterList->mode, "in") == 0) {
                                                        fprintf(output, "%d: contents b, %d := r%d\n",
                                                                globalRecord.pc++, parameterList->offset, argumentParamList->record->registerNumber);
                                                    }

                                                    parameterList = parameterList->next;         // Traverse through the formal paramters
                                                    argumentParamList = argumentParamList->next; // Traverse through the argument paramters
                                                    
                                                    changeProcedureAR = procedureARBase;         // The next formal parameter may or may not need a walkback so get original base
                                                }
                                                /****************************/

                                                
                                                // Return Address // Jump to pc count
                                                fprintf(output, "%d: r%d := %d\n", globalRecord.pc++, globalRecord.registerNumber, globalRecord.pc + 3);
                                                fprintf(output, "%d: contents b, 1 := r%d\n", globalRecord.pc++, globalRecord.registerNumber++);
                                            
                                                // Call to Nest // Place the offset of procedure inside of symbol Table node
                                                fprintf(output, "%d: pc := %d \n", globalRecord.pc++, variableInTree->procStart);

                                                
                                                // This is for exceptions in ada. A jump to jump to exception table if r1 != 0
                                                excepPutInToList(stackOfLLExcep, globalRecord.pc);
                                                fprintf(output, "%d: pc := ? if r1\n", globalRecord.pc++);
                                            } // end of else if (procNodeInTree->kind == procedure)

                                                  
}
    break;

  case 43:
#line 1196 "ada.y"
    { (yyval.ptrToRecordNode) = (yyvsp[(2) - (3)].ptrToRecordNode);   }
    break;

  case 44:
#line 1197 "ada.y"
    { (yyval.ptrToRecordNode) = NULL; }
    break;

  case 45:
#line 1198 "ada.y"
    { (yyval.ptrToRecordNode) = (yyvsp[(1) - (1)].ptrToRecordNode);   }
    break;

  case 46:
#line 1202 "ada.y"
    { (yyval.ptrToRecordNode) = NULL; }
    break;

  case 47:
#line 1204 "ada.y"
    {
                                            recordptr temp = createRecord();
                                            strcpy(temp->variableName, (yyvsp[(2) - (2)].var));

                                            //fprintf(output, "BEFORE Searching for: %s\n", temp->variableName);
                                            RecordNodePtr subVariable = createRecordNode(temp);
                                            //fprintf(output, "AFTER Searching for: %s\n", subVariable->record->variableName);

                                            (yyval.ptrToRecordNode) = subVariable;
                                            
}
    break;

  case 48:
#line 1217 "ada.y"
    {
                                            recordptr temp = createRecord();
                                            strcpy(temp->variableName, (yyvsp[(2) - (5)].var));
                                            temp->offset = (yyvsp[(4) - (5)].ptrToRecord)->offset;
                                            temp->phantomOffSet = (yyvsp[(4) - (5)].ptrToRecord)->phantomOffSet;
                                            temp->registerNumber = (yyvsp[(4) - (5)].ptrToRecord)->registerNumber;

                                            //fprintf(output, "BEFORE Searching for: %s\n", temp->variableName);
                                            RecordNodePtr subVariable = createRecordNode(temp);
                                            //fprintf(output, "AFTER Searching for: %s\n", subVariable->record->variableName);

                                            (yyval.ptrToRecordNode) = subVariable;

}
    break;

  case 49:
#line 1234 "ada.y"
    { 
                                            // expression can derive a literal, an Id, an ( expression ) or an array index or a combination of all of them
                                            (yyval.ptrToRecord) = (yyvsp[(2) - (2)].ptrToRecord); // Type is a recordptr
}
    break;

  case 50:
#line 1238 "ada.y"
    {  (yyval.ptrToRecord) = NULL; }
    break;

  case 57:
#line 1254 "ada.y"
    {
                                        struct node* variableInTree = globalSearch(stackOfTrees, (yyvsp[(2) - (2)].var));
                                        
                                        fprintf(output, "%d: r1 := %d\n", globalRecord.pc++, variableInTree->exceptionNumber);

                                        excepPutInToList(stackOfLLExcep, globalRecord.pc);
                                        fprintf(output, "%d: pc := ?\n", globalRecord.pc++);

}
    break;

  case 58:
#line 1264 "ada.y"
    {
                                        excepPutInToList(stackOfLLExcep, globalRecord.pc);
                                        fprintf(output, "%d: pc := ?\n", globalRecord.pc++ );
}
    break;

  case 59:
#line 1275 "ada.y"
    {
                                        // UPDATE patch list by apending the patchlines from the topmost linked list AND the current pc
                                        printf("Here is the updated patch list (LOOP PRODUCTION) for this procedure: \n");
                                        ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                        while (tempHead != NULL) {
                                            patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc+1);
                                            tempHead = tempHead->next;
                                        }
                                        printAllNodes(patchList);

                                        
                                        //printf("Here is the patch list for this procedure: \n");
                                        //printAllNodes(stackOfLL[patchTopIndex].leaveAddressPtr);
                                        printf("\n\n");


                                        fprintf(output, "%d: pc := %d\n", globalRecord.pc++, (yyvsp[(1) - (3)].integer));
                                        // POP: After patching all the forward references when leaving the loop
                                        popList(stackOfLL);
                                        
}
    break;

  case 60:
#line 1298 "ada.y"
    {  
                                        pushList(stackOfLL);  // Push a new linked list onto stack
                                        (yyval.integer) = globalRecord.pc; // Remembers the pc number to jump back to the beginning of the loop
                                        
}
    break;

  case 65:
#line 1312 "ada.y"
    {
                                        // Print out the instruction line to jump to
                                        fprintf(output, "%d: pc := ? if r%d\n", globalRecord.pc, (yyvsp[(2) - (2)].ptrToRecord)->registerNumber);
                                        putInToList(stackOfLL, globalRecord.pc++); // Put program counter into stack of linked list
}
    break;

  case 66:
#line 1318 "ada.y"
    {
                                        // Print out the instruction line to jump to
                                        fprintf(output, "%d: pc := ?\n", globalRecord.pc);
                                        putInToList(stackOfLL, globalRecord.pc++);
}
    break;

  case 67:
#line 1328 "ada.y"
    {
                                        ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                        while (tempHead != NULL){
                                            patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc);
                                            tempHead = tempHead->next;
                                        }
                                        
                                        //printAllNodes(patchList);
                                        popList(stackOfLL);
                                        popRegNum(stackOfReg); // Subtract the registerCounter stack!

}
    break;

  case 69:
#line 1346 "ada.y"
    { 
                                        pushList(stackOfLL);      //Next stack is for the When condition
                                        if (!(yyvsp[(1) - (1)].ptrToRecord)->isRegister) {
                                            fprintf(output, "%d: r%d := contents b, %d\n", globalRecord.pc++, globalRecord.registerNumber, (yyvsp[(1) - (1)].ptrToRecord)->offset);
                                            pushRegNum(stackOfReg, globalRecord.registerNumber++);
                                        }
                                        else if ((yyvsp[(1) - (1)].ptrToRecord)->isRegister) {
                                            pushRegNum(stackOfReg, (yyvsp[(1) - (1)].ptrToRecord)->registerNumber);
                                        }

}
    break;

  case 72:
#line 1365 "ada.y"
    {
                                        
                                        ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                        //printf("patchLine: %d, jumpNumber: %d\n", tempHead->patchLine, tempHead->patchLine + 2);

                                        // If when clause only has a single expression 
                                        if (tempHead->next == NULL) {
                                            patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc + 1);
                                            //printf("patchLine: %d, jumpNumber: %d\n", tempHead->patchLine, globalRecord.pc + 1);

                                        }
                                        // If when has multiple expressions to check. '|'   '|'
                                        else {
                                            //printf("patchLine: %d, jumpNumber: %d\n", tempHead->patchLine, globalRecord.pc+1);
                                            patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc+1);
                                        }

                                        tempHead = tempHead->next; 
                                        
                                        while (tempHead != NULL){
                                            //printf("patchLine: %d, jumpNumber: %d\n", tempHead->patchLine, tempHead->patchLine + 2);
                                            patchList = appendToList(patchList, tempHead->patchLine, tempHead->patchLine + 2);
                                            tempHead = tempHead->next;
                                        }

                                        
                                        popList(stackOfLL);
                                        // FOR DEBUGGING
                                        //fprintf(output, "------ %d------\n", globalRecord.pc);
                                        fprintf(output, "%d: pc := ?\n", globalRecord.pc);

                                        putInToList(stackOfLL, globalRecord.pc++); // Need to patch the first when statement
                                        
}
    break;

  case 73:
#line 1401 "ada.y"
    { pushList(stackOfLL); }
    break;

  case 74:
#line 1405 "ada.y"
    {
                                        NumListNodePtr temp = (yyvsp[(1) - (2)].ptrToNumNode);
                                        //printf("patchLine: %d, jumpNumber: %d\n", temp->value, globalRecord.pc);

                                        while (temp->next != NULL) {
                                            printf("patchLine: %d, jumpNumber: %d\n", temp->value, globalRecord.pc);

                                            patchList = appendToList(patchList, temp->value, globalRecord.pc);
                                            temp = temp->next;
                                        }
                                        
                                        patchList = appendToList(patchList, temp->value, globalRecord.pc);

}
    break;

  case 75:
#line 1423 "ada.y"
    {
                                        NumListNodePtr temp =  addNumToList((yyvsp[(1) - (3)].ptrToNumNode), (yyvsp[(3) - (3)].ptrToNumNode));
                                        (yyval.ptrToNumNode) = temp;
}
    break;

  case 77:
#line 1432 "ada.y"
    {
                                        fprintf(output, "%d: r%d := r%d = r%d\n",
                                                globalRecord.pc++, globalRecord.registerNumber, (yyvsp[(1) - (1)].ptrToRecord)->registerNumber, stackOfReg[regTopIndex].registerNumber);
                                        
                                        fprintf(output, "%d: pc := ? if not r%d\n", globalRecord.pc, globalRecord.registerNumber++);

                                        putInToList(stackOfLL, globalRecord.pc++);


                                        fprintf(output, "%d: pc := ?\n", globalRecord.pc);                                        
                                        (yyval.ptrToNumNode) = initNumNode(globalRecord.pc++);  

}
    break;

  case 78:
#line 1445 "ada.y"
    {  putInToList(stackOfLL, globalRecord.pc);  }
    break;

  case 79:
#line 1450 "ada.y"
    {
                                        // There is an else if clause
                                        if ((yyvsp[(5) - (7)].integer) != -1) {
                                            
                                            ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                            while (tempHead != NULL) {
                                                patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc);
                                                tempHead = tempHead->next;
                                            }

                                            // If there is an else if clause, but NO else clause
                                            popList(stackOfLL);

                                            // If there is an else if and else clause
                                            if ((yyvsp[(5) - (7)].integer) != -1 && (yyvsp[(6) - (7)].integer) == -1) {
                                                ListNodePtr tempHead2 = stackOfLL[patchTopIndex].leaveAddressPtr;
                                                while (tempHead2 != NULL) {
                                                    patchList = appendToList(patchList, tempHead2->patchLine, globalRecord.pc);
                                                    tempHead2 = tempHead2->next;
                                                }
                                                popList(stackOfLL);
                                            }

                                            
                                        }
                                        // There is no else if clause but there is an else clause
                                        else if ((yyvsp[(6) - (7)].integer) != -1) {
                                            ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                            if (tempHead != NULL){
                                                patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc );
                                                //tempHead = tempHead->next;
                                            }
                                            
                                            popList(stackOfLL);
                                        }
                                        
                                        // Must have in case optional-else_if and optional_else are both empty (i.e. ($5 == -1 && $6 == -1))
                                        else {
                                            ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                            if (tempHead != NULL){
                                                patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc);
                                            }

                                            popList(stackOfLL); // Must use if file only contains a single if statement
                                            popList(stackOfLL);
                                        }
                                        
}
    break;

  case 80:
#line 1501 "ada.y"
    { pushList(stackOfLL);  (yyval.integer) = globalRecord.pc; }
    break;

  case 81:
#line 1504 "ada.y"
    { (yyval.integer) = (yyvsp[(1) - (1)].integer); }
    break;

  case 82:
#line 1505 "ada.y"
    { (yyval.integer) = -1; }
    break;

  case 83:
#line 1508 "ada.y"
    { (yyval.integer) = (yyvsp[(1) - (2)].integer); }
    break;

  case 84:
#line 1509 "ada.y"
    { (yyval.integer) = (yyvsp[(1) - (1)].integer); }
    break;

  case 85:
#line 1513 "ada.y"
    { (yyval.integer) = (yyvsp[(1) - (4)].integer); }
    break;

  case 86:
#line 1517 "ada.y"
    {
                                        // This is to patch the cond jumps
                                        ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                            if (tempHead != NULL){
                                            patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc + 1);
                                            }
                                        popList(stackOfLL);
                                        
                                                                                    
                                        putInToList(stackOfLL, globalRecord.pc);
                                        fprintf(output, "%d: pc := ?\n", globalRecord.pc++);
                                        //fprintf(output, "ELSEIF   "); 
                                        (yyval.integer) = globalRecord.pc;   

}
    break;

  case 87:
#line 1535 "ada.y"
    { (yyval.integer) = (yyvsp[(1) - (2)].integer); }
    break;

  case 88:
#line 1536 "ada.y"
    { (yyval.integer) = -1; }
    break;

  case 89:
#line 1540 "ada.y"
    {
                                        // This is to patch the pc jumps
                                        ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                        if (tempHead != NULL){
                                            patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc + 1);
                                        }
                                        popList(stackOfLL);
                                        
                                                                                    
                                        putInToList(stackOfLL, globalRecord.pc);
                                        fprintf(output, "%d: pc := ?\n", globalRecord.pc++);
                                        //fprintf(output, "ELSE   ");
                                        (yyval.integer) = globalRecord.pc;

}
    break;

  case 90:
#line 1559 "ada.y"
    {
                                        pushList(stackOfLL);
                                        putInToList(stackOfLL, globalRecord.pc); // Need to patch the previous line
                                        
                                        fprintf(output, "%d: pc := ? if not r%d\n", globalRecord.pc++, (yyvsp[(1) - (1)].ptrToRecord)->registerNumber);
                                        (yyval.integer) = globalRecord.pc - 1;
}
    break;

  case 91:
#line 1568 "ada.y"
    {  (yyval.ptrToRecord) = (yyvsp[(1) - (1)].ptrToRecord);  }
    break;

  case 92:
#line 1573 "ada.y"
    { RecordNodePtr newListHead = createRecordNode((yyvsp[(1) - (3)].ptrToRecord));  (yyval.ptrToRecordNode) = addToRecordList(newListHead, (yyvsp[(3) - (3)].ptrToRecordNode)); }
    break;

  case 93:
#line 1574 "ada.y"
    { RecordNodePtr recordListHead = createRecordNode((yyvsp[(1) - (1)].ptrToRecord)); (yyval.ptrToRecordNode) = recordListHead; }
    break;

  case 94:
#line 1577 "ada.y"
    { (yyval.ptrToRecord) = (yyvsp[(1) - (1)].ptrToRecord); }
    break;

  case 95:
#line 1579 "ada.y"
    { 
                                        // Emit an argument arithmetic instruction  
                                        recordptr resultInfo = createRecord();

                                        // Want to push this register number up
                                        // Its the right hand side so must assign it to something
                                        resultInfo->registerNumber = globalRecord.registerNumber++;
                                        resultInfo->isRegister = true;
                                        resultInfo->isMemAddress = false;
                                        fprintf(output, "%d: r%d := ", globalRecord.pc++, resultInfo->registerNumber);

                                        // Handles left hand side of operation
                                        if ((yyvsp[(1) - (3)].ptrToRecord)->isMemAddress) {   // Can either be a local or a global variable
                                            if ((yyvsp[(1) - (3)].ptrToRecord)->isRegister)   fprintf(output, "contents r%d, %d ", (yyvsp[(1) - (3)].ptrToRecord)->registerNumber, (yyvsp[(1) - (3)].ptrToRecord)->offset); // Gloabl Variables
                                            else                  fprintf(output, "contents b, %d ", (yyvsp[(1) - (3)].ptrToRecord)->offset);                       // Local Variables
                                        }
                                        else {
                                            if ((yyvsp[(1) - (3)].ptrToRecord)->isRegister)    fprintf(output, "r%d ", (yyvsp[(1) - (3)].ptrToRecord)->registerNumber); // Literals (boolean or ints etc.)
                                            else                   fprintf(output, "ERROR in ada.y, expr : expr  b_o  rel\n");
                                        }     
                                
                                        // Prints out a AND or OR
                                        fprintf(output, "%s ", (yyvsp[(2) - (3)].var));
                                
                                        // Handles righthand side of operation
                                        if ((yyvsp[(3) - (3)].ptrToRecord)->isMemAddress) {   // Can either be a local or a global variable
                                            if ((yyvsp[(3) - (3)].ptrToRecord)->isRegister)   fprintf(output, "contents r%d, %d\n", (yyvsp[(3) - (3)].ptrToRecord)->registerNumber, (yyvsp[(3) - (3)].ptrToRecord)->offset); //Global Variables
                                            else                  fprintf(output, "contents b, %d\n", (yyvsp[(3) - (3)].ptrToRecord)->offset);                       //Local Variables
                                        }
                                        else {
                                            if ((yyvsp[(3) - (3)].ptrToRecord)->isRegister)    fprintf(output, "r%d\n", (yyvsp[(3) - (3)].ptrToRecord)->registerNumber); // Literals (boolean or ints etc.)
                                            else                   fprintf(output, "ERROR in ada.y, expr : expr  b_o  rel\n");
                                        }

                                        (yyval.ptrToRecord) = resultInfo;

}
    break;

  case 96:
#line 1618 "ada.y"
    { (yyval.ptrToRecord) = (yyvsp[(1) - (1)].ptrToRecord); }
    break;

  case 97:
#line 1620 "ada.y"
    { 
                                        // Emit an ALU arithmetic instruction
                                        recordptr resultInfo = createRecord();
                                        resultInfo->isRegister = true;
                                        resultInfo->isMemAddress = false;
                                    
                                        //fprintf(output, "left: %d,   right: %d\n\n", $1->registerNumber, $3->registerNumber);
                                        // Must put $1 into register to do relational operations in AMI
                                        int firstReg = (yyvsp[(1) - (3)].ptrToRecord)->registerNumber; 
                                        if ((yyvsp[(1) - (3)].ptrToRecord)->isMemAddress) {
                                            if (firstReg == 0) // If variable assignment does not exist then give a new registerNumber
                                                firstReg = globalRecord.registerNumber++;
                                            
                                            fprintf(output, "%d: r%d := ", globalRecord.pc++, firstReg);
                                            
                                            if ((yyvsp[(1) - (3)].ptrToRecord)->isRegister)  fprintf(output, "contents r%d, %d \n", firstReg, (yyvsp[(1) - (3)].ptrToRecord)->offset); // Global Variables
                                            else                 fprintf(output, "contents b, %d \n", (yyvsp[(1) - (3)].ptrToRecord)->offset);             // Local Variables
                                        }
                                        
                                        // Must put $3 into register to do relational operations in AMI
                                        int secondReg = (yyvsp[(3) - (3)].ptrToRecord)->registerNumber; 
                                        if ((yyvsp[(3) - (3)].ptrToRecord)->isMemAddress) {
                                            if (secondReg == 0) // If variable assignment does not exist then give a new registerNumber
                                                secondReg = globalRecord.registerNumber++;
                                            
                                            fprintf(output, "%d: r%d := ", globalRecord.pc++, secondReg);
                                            
                                            if ((yyvsp[(3) - (3)].ptrToRecord)->isRegister)  fprintf(output, "contents r%d, %d \n", secondReg, (yyvsp[(3) - (3)].ptrToRecord)->offset); // Global Variables
                                            else                 fprintf(output, "contents b, %d \n", (yyvsp[(3) - (3)].ptrToRecord)->offset);              // Local Variables
                                        }

                                        
                                        // Left Hand Side of AMI
                                        resultInfo->registerNumber = globalRecord.registerNumber++;
                                        fprintf(output, "%d: r%d := ",  globalRecord.pc++, resultInfo->registerNumber);

                                        // Right Hand Side of AMI
                                        if (strcmp((yyvsp[(2) - (3)].var), ">") == 0)
                                            fprintf(output, "r%d < r%d\n", secondReg, firstReg);

                                        else if (strcmp((yyvsp[(2) - (3)].var), ">=") == 0) 
                                            fprintf(output, "r%d <= r%d\n", secondReg, firstReg);
                                        
                                        else                         
                                            fprintf(output, "r%d %s r%d\n", firstReg, (yyvsp[(2) - (3)].var), secondReg);
                                        
                                        
                                        (yyval.ptrToRecord) = resultInfo;

}
    break;

  case 98:
#line 1672 "ada.y"
    { (yyval.ptrToRecord) = (yyvsp[(1) - (1)].ptrToRecord); }
    break;

  case 99:
#line 1674 "ada.y"
    { 
                                        // Emit an argument arithmetic instruction
                                        recordptr resultInfo = createRecord();
                                        resultInfo->registerNumber = globalRecord.registerNumber++;
                                        resultInfo->isRegister = true;
                                        resultInfo->isMemAddress = false;
                                        
                                        fprintf(output, "%d: r%d := - ", globalRecord.pc++, resultInfo->registerNumber);
                                        
                                        // Right Hand side of AMI, either a Non-Local, Local or literal
                                            if ((yyvsp[(2) - (2)].ptrToRecord)->isMemAddress) {   // Can either be a local or a global variable
                                                if ((yyvsp[(2) - (2)].ptrToRecord)->isRegister)   fprintf(output, "contents r%d, %d\n", (yyvsp[(2) - (2)].ptrToRecord)->registerNumber, (yyvsp[(2) - (2)].ptrToRecord)->offset); //Non-Local Variable
                                                else                  fprintf(output, "contents b, %d\n", (yyvsp[(2) - (2)].ptrToRecord)->offset);                       //Local Variable
                                            }
                                            else {
                                                if ((yyvsp[(2) - (2)].ptrToRecord)->isRegister)   fprintf(output, "r%d\n", (yyvsp[(2) - (2)].ptrToRecord)->registerNumber); // Literals (boolean or ints etc.)
                                                else                  fprintf(output, "ERROR in ada.y, s_e : - term\n");
                                            }

                                        (yyval.ptrToRecord) = resultInfo;

}
    break;

  case 100:
#line 1697 "ada.y"
    {
                                        recordptr resultInfo = createRecord();

                                        // Abstract Machine Instructions do not allow for a value at a memory address to be added with 
                                        // a register. If the value at a memory address is added with a register (or vice versa) then 
                                        // this code stores the value at the memory address into a register so that the AMI can be performed

                                        bool hold1 = (yyvsp[(1) - (3)].ptrToRecord)->isMemAddress && !(yyvsp[(3) - (3)].ptrToRecord)->isMemAddress;
                                        int holdRegister1 = 0;
                                        bool hold2 = !(yyvsp[(1) - (3)].ptrToRecord)->isMemAddress && (yyvsp[(3) - (3)].ptrToRecord)->isMemAddress;
                                        int holdRegister2 = 0;
                                        
                                        if (hold1) {
                                            holdRegister1 = globalRecord.registerNumber++;
                                            fprintf(output, "%d: r%d := contents b, %d\n", globalRecord.pc++, holdRegister1, (yyvsp[(1) - (3)].ptrToRecord)->offset);
                                        }
                                        if (hold2) {
                                            holdRegister2 = globalRecord.registerNumber++;
                                            fprintf(output, "%d: r%d := contents b, %d\n", globalRecord.pc++, holdRegister2, (yyvsp[(3) - (3)].ptrToRecord)->offset);

                                        }
                                        
                                        // Want to push this register number up
                                        // Its the right hand side so must assign it to something
                                        resultInfo->registerNumber = globalRecord.registerNumber++;
                                        resultInfo->isRegister = true;
                                        resultInfo->isMemAddress = false;
                                        fprintf(output, "%d: r%d := ", globalRecord.pc++, resultInfo->registerNumber);

                                        // Handles left hand side of operation
                                        if ((yyvsp[(1) - (3)].ptrToRecord)->isMemAddress) { // Can either be a Non-Local or a Local variable
                                            if (!hold1) {
                                                if ((yyvsp[(1) - (3)].ptrToRecord)->isRegister)   fprintf(output, "contents r%d, %d ", (yyvsp[(1) - (3)].ptrToRecord)->registerNumber, (yyvsp[(1) - (3)].ptrToRecord)->offset); // Non-Local Variable
                                                else                  fprintf(output, "contents b, %d ", (yyvsp[(1) - (3)].ptrToRecord)->offset);                       // Local Variable
                                            }
                                            else
                                                fprintf(output, "r%d ", holdRegister1); 
                                        
                                        }
                                        else {
                                            if ((yyvsp[(1) - (3)].ptrToRecord)->isRegister)    fprintf(output, "r%d ", (yyvsp[(1) - (3)].ptrToRecord)->registerNumber); // Literals (boolean or ints etc.)
                                            else                   fprintf(output, "ERROR in ada.y, s_e : s_e a_o term factor\n");
                                        }     

                                                                                                                
                                        
                                        // Prints out a + or a -
                                        fprintf(output, "%s ", (yyvsp[(2) - (3)].var));
                                        
                                        // Handles righthand side of operation
                                        if ((yyvsp[(3) - (3)].ptrToRecord)->isMemAddress) { // Can either be a Non-Local or a Local variable
                                            if (!hold2) {
                                                if ((yyvsp[(3) - (3)].ptrToRecord)->isRegister)   fprintf(output, "contents r%d, %d\n", (yyvsp[(3) - (3)].ptrToRecord)->registerNumber, (yyvsp[(3) - (3)].ptrToRecord)->offset); //Non-Local Variable
                                                else                  fprintf(output, "contents b, %d\n", (yyvsp[(3) - (3)].ptrToRecord)->offset);                       //Local Variable
                                            }
                                            else
                                                fprintf(output, "r%d\n", holdRegister2); 
                                        }
                                        else {
                                            if ((yyvsp[(3) - (3)].ptrToRecord)->isRegister)    fprintf(output, "r%d\n", (yyvsp[(3) - (3)].ptrToRecord)->registerNumber); // Literals (boolean or ints etc.)
                                            else                   fprintf(output, "ERROR in ada.y, s_e : s_e a_o term factor\n");
                                        }
                                        
                                        (yyval.ptrToRecord) = resultInfo;
                                        
}
    break;

  case 101:
#line 1765 "ada.y"
    { (yyval.ptrToRecord) = (yyvsp[(1) - (1)].ptrToRecord); }
    break;

  case 102:
#line 1767 "ada.y"
    {
                                        recordptr resultInfo = createRecord();

                                        // Abstract Machine Instructions do not allow for a value at a memory address to be added with 
                                        // a register. If the value at a memory address is added with a register (or vice versa) then 
                                        // this code stores the value at the memory address into a register so that the AMI can be performed

                                        bool hold1 = (yyvsp[(1) - (3)].ptrToRecord)->isMemAddress && !(yyvsp[(3) - (3)].ptrToRecord)->isMemAddress;
                                        int holdRegister1 = 0;
                                        bool hold2 = !(yyvsp[(1) - (3)].ptrToRecord)->isMemAddress && (yyvsp[(3) - (3)].ptrToRecord)->isMemAddress;
                                        int holdRegister2 = 0;
                                        
                                        if (hold1) {
                                            holdRegister1 = globalRecord.registerNumber++;
                                            fprintf(output, "%d: r%d := contents b, %d\n", globalRecord.pc++, holdRegister1, (yyvsp[(1) - (3)].ptrToRecord)->offset);
                                        }
                                        if (hold2) {
                                            holdRegister2 = globalRecord.registerNumber++;
                                            fprintf(output, "%d: r%d := contents b, %d\n", globalRecord.pc++, holdRegister2, (yyvsp[(3) - (3)].ptrToRecord)->offset);

                                        }
                                        
                                        // Want to push this register number up
                                        // Its the right hand side so must assign it to something
                                        resultInfo->registerNumber = globalRecord.registerNumber++;
                                        resultInfo->isRegister = true;
                                        resultInfo->isMemAddress = false;
                                        fprintf(output, "%d: r%d := ", globalRecord.pc++, resultInfo->registerNumber);

                                        // Handles left hand side of operation
                                        if ((yyvsp[(1) - (3)].ptrToRecord)->isMemAddress) { // Can either be a Non-Local or a Local variable
                                            if (!hold1) {
                                                if ((yyvsp[(1) - (3)].ptrToRecord)->isRegister)   fprintf(output, "contents r%d, %d ", (yyvsp[(1) - (3)].ptrToRecord)->registerNumber, (yyvsp[(1) - (3)].ptrToRecord)->offset); // Non-Local Variable
                                                else                  fprintf(output, "contents b, %d ", (yyvsp[(1) - (3)].ptrToRecord)->offset);                       // Local Variable
                                            }
                                            else
                                                fprintf(output, "r%d ", holdRegister1); 
                                        
                                        }
                                        else {
                                            if ((yyvsp[(1) - (3)].ptrToRecord)->isRegister)    fprintf(output, "r%d ", (yyvsp[(1) - (3)].ptrToRecord)->registerNumber); // Literals (boolean or ints etc.)
                                            else                   fprintf(output, "ERROR in ada.y, term : term  m_o  factor\n");
                                        }     

                                                                                                                
                                        
                                        // Prints out a * or a /
                                        fprintf(output, "%s ", (yyvsp[(2) - (3)].var));
                                        
                                        // Handles righthand side of operation
                                        if ((yyvsp[(3) - (3)].ptrToRecord)->isMemAddress) { // Can either be a Non-Local or a Local variable
                                            if (!hold2) {
                                                if ((yyvsp[(3) - (3)].ptrToRecord)->isRegister)   fprintf(output, "contents r%d, %d\n", (yyvsp[(3) - (3)].ptrToRecord)->registerNumber, (yyvsp[(3) - (3)].ptrToRecord)->offset); //Non-Local Variable
                                                else                  fprintf(output, "contents b, %d\n", (yyvsp[(3) - (3)].ptrToRecord)->offset);                       //Local Variable
                                            }
                                            else
                                                fprintf(output, "r%d\n", holdRegister2); 
                                        }
                                        else {
                                            if ((yyvsp[(3) - (3)].ptrToRecord)->isRegister)    fprintf(output, "r%d\n", (yyvsp[(3) - (3)].ptrToRecord)->registerNumber); // Literals (boolean or ints etc.)
                                            else                   fprintf(output, "ERROR in ada.y, s_e : s_e a_o term factor\n");
                                        }
                                        
                                        (yyval.ptrToRecord) = resultInfo;

}
    break;

  case 103:
#line 1836 "ada.y"
    {   
                                        (yyval.ptrToRecord) = (yyvsp[(1) - (1)].ptrToRecord);   
                                        //printf("register number:%d, register offset:%d\n", $1->registerNumber, $1->offset);
}
    break;

  case 104:
#line 1841 "ada.y"
    {
                                        // Emit several Argument Arithmetic instructions
                                        recordptr resultInfo = createRecord();
                                        resultInfo->isRegister = true;
                                        resultInfo->isMemAddress = false;
                                                            
                                        //fprintf(output, "left: %d,   right: %d\n\n", $1->registerNumber, $3->registerNumber);
                                        // Must put $1 into register to do relational operations in AMI
                                        int firstReg = (yyvsp[(1) - (3)].ptrToRecord)->registerNumber; 
                                        if ((yyvsp[(1) - (3)].ptrToRecord)->isMemAddress) {
                                            if (firstReg == 0) // If variable assignment does not exist then give a new registerNumber
                                                firstReg = globalRecord.registerNumber++;
                                                                    
                                            fprintf(output, "%d: r%d := ", globalRecord.pc++, firstReg);
                                                                    
                                            if ((yyvsp[(1) - (3)].ptrToRecord)->isRegister)  fprintf(output, "contents r%d, %d \n", firstReg, (yyvsp[(1) - (3)].ptrToRecord)->offset); // Global Variables
                                            else                 fprintf(output, "contents b, %d \n", (yyvsp[(1) - (3)].ptrToRecord)->offset);             // Local Variables
                                        }
                                                                
                                        // Must put $3 into register to do relational operations in AMI
                                        int secondReg = (yyvsp[(3) - (3)].ptrToRecord)->registerNumber; 
                                        if ((yyvsp[(3) - (3)].ptrToRecord)->isMemAddress) {
                                            if (secondReg == 0) // If variable assignment does not exist then give a new registerNumber
                                                secondReg = globalRecord.registerNumber++;
                                                                    
                                            fprintf(output, "%d: r%d := ", globalRecord.pc++, secondReg);
                                                                    
                                            if ((yyvsp[(3) - (3)].ptrToRecord)->isRegister)  fprintf(output, "contents r%d, %d \n", secondReg, (yyvsp[(3) - (3)].ptrToRecord)->offset); // Global Variables
                                            else                 fprintf(output, "contents b, %d \n", (yyvsp[(3) - (3)].ptrToRecord)->offset);              // Local Variables
                                        }

                                        int productReg = globalRecord.registerNumber++;
                                        resultInfo->registerNumber = productReg;
                                        fprintf(output, "%d: r%d := 1\n", globalRecord.pc++, productReg);

                                        int decrementReg = globalRecord.registerNumber++;
                                        fprintf(output, "%d: r%d := 1\n", globalRecord.pc++, decrementReg);

                                        int pcJumpLine = globalRecord.pc++;
                                        fprintf(output, "%d: r%d := r%d * r%d\n", pcJumpLine, productReg, productReg, firstReg);

                                        int compareReg = globalRecord.registerNumber++;
                                        fprintf(output, "%d: r%d := r%d = r%d\n", globalRecord.pc++, compareReg, secondReg, decrementReg);

                                        fprintf(output, "%d: r%d := r%d - r%d\n", globalRecord.pc++, secondReg, secondReg, decrementReg);

                                        fprintf(output, "%d: pc := %d if not r%d\n", globalRecord.pc++, pcJumpLine, compareReg);
                                    
                                        (yyval.ptrToRecord) = resultInfo;

}
    break;

  case 105:
#line 1893 "ada.y"
    {
                                        recordptr resultInfo = createRecord();
                                        resultInfo->registerNumber = globalRecord.registerNumber++;
                                        resultInfo->isRegister = true;
                                        resultInfo->isMemAddress = false;
                                                            
                                        fprintf(output, "%d: r%d := not ", globalRecord.pc++, resultInfo->registerNumber);
                                                            
                                        // Right Hand side of an operation, either a Non-Local, Local variable or a literal
                                        if ((yyvsp[(2) - (2)].ptrToRecord)->isMemAddress) { //can either be a Non-Local or a Local variable
                                            if ((yyvsp[(2) - (2)].ptrToRecord)->isRegister)   fprintf(output, "contents r%d, %d\n", (yyvsp[(2) - (2)].ptrToRecord)->registerNumber, (yyvsp[(2) - (2)].ptrToRecord)->offset); // Non-Local Variable
                                            else                  fprintf(output, "contents b, %d\n", (yyvsp[(2) - (2)].ptrToRecord)->offset);                       // Local Variable
                                        }
                                        else {
                                            if ((yyvsp[(2) - (2)].ptrToRecord)->isRegister)    fprintf(output, "r%d\n", (yyvsp[(2) - (2)].ptrToRecord)->registerNumber); // Literals (boolean or ints etc.)
                                            else                   fprintf(output, "ERROR in ada.y, factor : NOT primary\n");
                                        }
                                            

                                        (yyval.ptrToRecord) = resultInfo;
                                    
}
    break;

  case 106:
#line 1918 "ada.y"
    {
                                        //fprintf(output, "************* name: %s *************", $1);
                                        recordptr variableInfo = createRecord();
                                        
                                        // boolean is a literal that is not_declarable, default enum value is -1
                                        // integer literals do not have an offset, BUT ONLY USE If number is used for INDEXING an array
                                        variableInfo->offset = (yyvsp[(1) - (1)].integer); 
                                        variableInfo->registerNumber = globalRecord.registerNumber++;
                                        variableInfo->isRegister = true;               // is a register so its a literal
                                        variableInfo->isMemAddress = false;            // A literal so not a memory address  //NOt contents b, 4
                                        
                                        fprintf(output, "%d: r%d := %d\n", globalRecord.pc++, variableInfo->registerNumber, (yyvsp[(1) - (1)].integer));
                    
                                        (yyval.ptrToRecord) = variableInfo;

}
    break;

  case 107:
#line 1937 "ada.y"
    {
                                        recordptr variableInfo = createRecord();
                                        struct node* nodeInTree = globalSearch(stackOfTrees, (yyvsp[(1) - (1)].var));
                                        //printf("%s has a value of %d\n", nodeInTree->symbol, nodeInTree->val);

                                        int walkBackCount = countGlobalSearch(stackOfTrees, (yyvsp[(1) - (1)].var));

                                        // Enumeration type IN YOUR RECORDS distinguishes between boolean and integers
                                        // Handles true and false literals
                                        if (nodeInTree->kind == value) {             // value is an enum 5
                                            strcpy(variableInfo->variableName, (yyvsp[(1) - (1)].var));  // Need this if putting true into procedure with formal parameters example: inner(true)
                                            // boolean is a literal that is not_declarable, default enum value is -1
                                            // true and false do not have offset
                                            variableInfo->registerNumber = globalRecord.registerNumber++; // Need in order to put true into a register
                                            variableInfo->isRegister = true;
                                            variableInfo->isMemAddress = false;
                                            
                                            fprintf(output, "%d: r%d := ", globalRecord.pc++, variableInfo->registerNumber);
                                            
                                            // Accounts for true and false if statements in tree
                                            if (strcmp(nodeInTree->symbol, "true") == 0)
                                                fprintf(output, "true\n");  
                                            else if (strcmp(nodeInTree->symbol, "false") == 0)
                                                fprintf(output, "false\n");
                                            else
                                                fprintf(output, "This is for maxint case with enum value");
                                        }                                                      
                                        
                                        // Handles LOCAL variables in the right hand side of an assignment
                                        else if (walkBackCount == 0) {
                                            //fprintf(output, "************ name: %s,   variableType: %d **********\n", nodeInTree->symbol, nodeInTree->variableType);

                                            // Put name into record. Need this for Ada records!
                                            strcpy(variableInfo->variableName, (yyvsp[(1) - (1)].var));                // Need for Ada records and procedures with formal parameters 
                                            variableInfo->variableType = nodeInTree->variableType; // Need for read_boolean or read_integer
                                            variableInfo->offset = nodeInTree->offset;
                                            // Local variables are not stored in a register
                                            variableInfo->isRegister = false;                      // Local variables are NOT stored in a register
                                            variableInfo->isMemAddress = true;                     // MUST DISPLAY contents b, 4 etc. for local variables
                                        }
                                        // Handles GLOBAL variables in the right hand side of an assignment
                                        else {
                                                strcpy(variableInfo->variableName, (yyvsp[(1) - (1)].var));                // Need for procedures with formal parameters, production optional_parameters inner(a)
                                                variableInfo->variableType = nodeInTree->variableType; // Need for read_boolean or read_integer
                                                variableInfo->offset = nodeInTree->offset;
                                                variableInfo->registerNumber = globalRecord.registerNumber;
                                                variableInfo->isRegister = true;                       // Want to walk back using a register  r2 := b then r2 := contents r2, 2
                                                variableInfo->isMemAddress = true;                     // THIS WILL BE STORED IN A REGISTER BECAUSE OF REQUIRED WALK BACK
                                                
                                                //fprintf(output, "**** name: %s **** offset: %d **** registerNumber: %d *****\n",
                                                //nodeInTree->symbol, variableInfo->offset, variableInfo->registerNumber);

                                                // r2 := b
                                                fprintf(output, "%d: r%d := b\n", globalRecord.pc++, variableInfo->registerNumber);
                                                            
                                                // Loop updates the register and static link  Ex. r2 := contents r2, 2
                                                while (walkBackCount != 0) {
                                                fprintf(output, "%d: r%d := contents r%d, 2\n", globalRecord.pc++, variableInfo->registerNumber, variableInfo->registerNumber);
                                                    walkBackCount--;
                                                }
                                                
                                                globalRecord.registerNumber++;   // Update current register
                                                
                                        }
                                        
                                        (yyval.ptrToRecord) = variableInfo;
                                    
}
    break;

  case 108:
#line 2007 "ada.y"
    {  (yyval.ptrToRecord) = (yyvsp[(2) - (3)].ptrToRecord);  }
    break;

  case 109:
#line 2010 "ada.y"
    {
                                        // If the RIGHT-HAND side of an ASSIGNMENT has an array reference!
                                        recordptr variableInfo = createRecord();
                                        struct node* nodeInTree = globalSearch(stackOfTrees, (yyvsp[(1) - (4)].var));

                                        if (nodeInTree != NULL) {
                                            int walkBackCount = countGlobalSearch(stackOfTrees, (yyvsp[(1) - (4)].var));

                                            
                                            // Need if the expression inside an array is a local or non-local variable
                                            int registerOfExpr = (yyvsp[(3) - (4)].ptrToRecord)->registerNumber;
                                            if ((yyvsp[(3) - (4)].ptrToRecord)->isMemAddress) {
                                                registerOfExpr = globalRecord.registerNumber++;

                                                fprintf(output, "%d: r%d := contents b, %d\n",
                                                        globalRecord.pc++, registerOfExpr, (yyvsp[(3) - (4)].ptrToRecord)->offset);
                                            }

                                            
                                            
                                            if (walkBackCount == 0) {
                                                //fprintf(output, "************ name: %s,   variableType: %d **********\n", nodeInTree->symbol, nodeInTree->variableType);
                                                
                                                // Put name into record. Need this for Ada records! Ex.   := arr(4).first 
                                                strcpy(variableInfo->variableName, (yyvsp[(1) - (4)].var));   
                                                
                                                variableInfo->variableType = array;                        // This is an array so enum is 2 
                                                variableInfo->offset = nodeInTree->offset + (yyvsp[(3) - (4)].ptrToRecord)->offset;    // Ex: Index is from 4..7, so for c(7) its phantomoffset + 7 = 12
                                                // Local variables are not stored in a register
                                                variableInfo->registerNumber = registerOfExpr;
                                                variableInfo->isRegister = false;                          // local variables are NOT stored in a register
                                                variableInfo->isMemAddress = true;                         // MUST DISPLAY contents b, 4 etc. for local variables
                                                variableInfo->phantomOffSet = nodeInTree->offset; 
                                            }
                                            // Handles GLOBAL variables in the right hand side of an assignment
                                            else {
                                                variableInfo->variableType = array;                        // This is an array so enum is 2 
                                                variableInfo->offset = nodeInTree->offset + (yyvsp[(3) - (4)].ptrToRecord)->offset;    //Ex: Index is from 4..7, so for c(7) its phantomoffset + 7 = 12
                                                variableInfo->registerNumber = globalRecord.registerNumber;
                                                variableInfo->isRegister = true;                           // Walk back using a register  r2 := b then r2 := contents r2, 2
                                                variableInfo->isMemAddress = true;                         // Stored in register because of required walkback
                                                variableInfo->phantomOffSet = nodeInTree->offset;

                                                //GOOD TO HAVE THIS LINE FOR CHECKING OFFSET OF VARIABLE
                                                //fprintf(output, "**** name: %s **** offset: %d **** registerNumber: %d *****\n",
                                                //      nodeInTree->symbol, variableInfo->offset, variableInfo->registerNumber);

                                                // r2 := b
                                                fprintf(output, "%d: r%d := b\n", globalRecord.pc++, variableInfo->registerNumber);
                                                
                                                // Loop updates the register and static link  Ex. r2 := contents r2, 2
                                                while (walkBackCount != 0) {
                                                    fprintf(output, "%d: r%d := contents r%d, 2\n",
                                                            globalRecord.pc++, variableInfo->registerNumber, variableInfo->registerNumber);
                                                    walkBackCount--;
                                                }

                                                        
                                                // Add the base address of current variable with offset of expression inside of the array
                                                fprintf(output, "%d: r%d := r%d + r%d\n",
                                                        globalRecord.pc++, variableInfo->registerNumber, variableInfo->registerNumber, registerOfExpr);
                                                
                                                // Update current register
                                                globalRecord.registerNumber++;
                                        
                                            }
                                        }
                                        else fprintf(output, "Error: Could not find variable. Check production: primary -> ID '(' expression ')' \n");
                                    
                                        (yyval.ptrToRecord) = variableInfo;
                                        
}
    break;

  case 110:
#line 2084 "ada.y"
    {
                                        // This is the specific sub-variable inside of an Ada record type
                                        // Ex. The specific sub-variable for one of many possible record instances
                                        // Pass up information from already declared record into here!
                                        recordptr subVariableInfo = createRecord();
                                        
                                        // If the RIGHT-HAND side of an ASSIGNMENT is accessing a variable from a record!
                                        recordptr variableInfo = (yyvsp[(1) - (4)].ptrToRecord);                                                      //This is the generic variable of Ada record type 
                                        struct node* nodeInTree = globalSearch(stackOfTrees, variableInfo->variableName); //Find node of Ada record type in binary Tree

                                        // Find the sub-variable inside of the Ada record type and calculate its offset
                                        int subVariableOffSet = 0;
                                        RecordListPtr traverseList = nodeInTree->listOfVariables;

                                        printf("Searching for: %s\n", (yyvsp[(3) - (4)].var));
                                        
                                        while( (traverseList != NULL) &&  !(strcmp(traverseList->variableName, (yyvsp[(3) - (4)].var)) == 0) ) {
                                            subVariableOffSet = subVariableOffSet + traverseList->memSpace;
                                            //fprintf(output, "In primary production %s\n", traverseList->variableName); //TODO: Fix this error!
                                            
                                            traverseList = traverseList->next; 
                                        }

                                        subVariableOffSet = nodeInTree->offset + subVariableOffSet;
                                        
                                        // Found sub-variable inside of the Ada record type so continue
                                        if (traverseList != NULL) {

                                            subVariableInfo->kind = traverseList->kind;  // May be a variable array_type or record_type
                                            subVariableInfo->isRegister = false;         // Local variables are NOT stored in a register
                                            subVariableInfo->isMemAddress = true;        // MUST DISPLAY contents b, 4 etc. for local variables
                                            
                                        // Add on the base offset of variable of type Ada record
                                            if ((yyvsp[(4) - (4)].ptrToRecord) == NULL)  // Not an array subVariable
                                                subVariableInfo->offset = subVariableOffSet;
                                            else {            // Is an array subVariable
                                                subVariableOffSet = subVariableOffSet - traverseList->parent_type->lower; //Calculate phantom offset
                                                subVariableInfo->offset = subVariableOffSet + (yyvsp[(4) - (4)].ptrToRecord)->offset;
                                                subVariableInfo->phantomOffSet = subVariableOffSet;
                                                subVariableInfo->variableType = array;
                                                subVariableInfo->registerNumber = (yyvsp[(4) - (4)].ptrToRecord)->registerNumber;
                                            }

                                        }
                                        else 
                                            printf("Could not find the variable of this Ada record type! This is printing out in the primary production.\n");

                                        (yyval.ptrToRecord) = subVariableInfo;

}
    break;

  case 111:
#line 2137 "ada.y"
    { (yyval.ptrToRecord) = (yyvsp[(2) - (3)].ptrToRecord); }
    break;

  case 112:
#line 2138 "ada.y"
    { (yyval.ptrToRecord) = NULL; }
    break;

  case 113:
#line 2141 "ada.y"
    { (yyval.var) = "and"; }
    break;

  case 114:
#line 2142 "ada.y"
    { (yyval.var) = "or"; }
    break;

  case 115:
#line 2145 "ada.y"
    { (yyval.var) = "="; }
    break;

  case 116:
#line 2146 "ada.y"
    { (yyval.var) = "/="; }
    break;

  case 117:
#line 2147 "ada.y"
    { (yyval.var) = "<"; }
    break;

  case 118:
#line 2148 "ada.y"
    { (yyval.var) = ">"; }
    break;

  case 119:
#line 2149 "ada.y"
    { (yyval.var) = ">="; }
    break;

  case 120:
#line 2150 "ada.y"
    { (yyval.var) = "<="; }
    break;

  case 121:
#line 2153 "ada.y"
    { (yyval.var) = "+"; }
    break;

  case 122:
#line 2154 "ada.y"
    { (yyval.var) = "-"; }
    break;

  case 123:
#line 2157 "ada.y"
    { (yyval.var) = "*"; }
    break;

  case 124:
#line 2158 "ada.y"
    { (yyval.var) = "/"; }
    break;

  case 125:
#line 2164 "ada.y"
    {
                                        patchList = appendToList(patchList, (yyvsp[(1) - (2)].integer), globalRecord.pc-1);
                                        
                                        //Set all without index to 23 so jump_table[1] = .....
                                        for (int i = 1; i < globalRecord.exceptionNumber; i++) {
                                            if (jump_table[i] == 0)
                                                jump_table[i] = globalRecord.pc + globalRecord.exceptionNumber - 1;
                                        }
                                        
                                        
                                        for (int i = 1; i < globalRecord.exceptionNumber; i++) {
                                            fprintf(output, "%d: pc := %d\n", globalRecord.pc++, jump_table[i]);
                                        }

                                        
                                        ListNodePtr tempHead = stackOfLLExcep[excepTopIndex].leaveAddressPtr;
                                        //tempHead = tempHead->next;
                                        while (tempHead != NULL) {
                                            patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc);
                                            tempHead= tempHead->next;
                                        }
                                        //excepPopList(stackOfLLExcep); // This is already taken care of at the end of procedure
                                                 
}
    break;

  case 126:
#line 2189 "ada.y"
    {
                                        ListNodePtr tempHead = stackOfLLExcep[excepTopIndex].leaveAddressPtr;
                                        if (tempHead != NULL) {
                                            patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc);
                                        }
                                        
                                        //fprintf(output, "%d: \n", globalRecord.pc++);
}
    break;

  case 127:
#line 2200 "ada.y"
    {
                                        // Initialze all values to 0 for a new exception statement
                                        for (int i = 0; i < globalRecord.exceptionNumber; i++)
                                            jump_table[i] = 0;

                                        
                                        // Goes to Jump Table pc line
                                        ListNodePtr tempHead = stackOfLLExcep[excepTopIndex].leaveAddressPtr;
                                        if (tempHead != NULL) {
                                            patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc + 1);
                                        }
                                        excepPopList(stackOfLLExcep);
                                        
                                        excepPushList(stackOfLLExcep);
                                        excepPutInToList(stackOfLLExcep, globalRecord.pc);
                                        fprintf(output, "%d: pc := ?\n", globalRecord.pc++);
                                        
                                        fprintf(output, "%d: pc := r1, ?\n", globalRecord.pc);
                                        (yyval.integer) = globalRecord.pc++;

}
    break;

  case 130:
#line 2228 "ada.y"
    {
                                        // Set jump table to[exception_number]
                                        fprintf(output, "%d: r1 := 0\n", globalRecord.pc++);


                                            excepPutInToList(stackOfLLExcep, globalRecord.pc);
                                        fprintf(output, "%d: pc := ?\n", globalRecord.pc++);

}
    break;

  case 132:
#line 2241 "ada.y"
    {
                                        // Set jump table to[exception_number]
                                        struct node* nodeInTree = globalSearch(stackOfTrees, (yyvsp[(1) - (1)].var));
                                        jump_table[nodeInTree->exceptionNumber] = globalRecord.pc;
}
    break;

  case 133:
#line 2247 "ada.y"
    {
                                        // Set jump table to[exception_number]
                                        for (int i = 0; i < globalRecord.exceptionNumber; i++) {
                                            if (jump_table[i] == 0)
                                                jump_table[i] = globalRecord.pc;
                                        }                
                                                               
}
    break;


/* Line 1267 of yacc.c.  */
#line 4057 "y.tab.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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


#line 2256 "ada.y"

int main()
{

    // ADD NODES INTO OUTER CONTEXT WHICH IS AT THE BASE OF THE STACK OF BINARY TREES
    // stackOfTrees variable is initialized and declared at the top of this file
    push(stackOfTrees, "O-C");
    add(stackOfTrees, 1, "integer");       //predefined
    add(stackOfTrees, 2, "boolean");       //predefined
    add(stackOfTrees, 3, "true");          //constant
    add(stackOfTrees, 4, "false");         //constant
    add(stackOfTrees, 5, "maxint");        //constant
    add(stackOfTrees, 6, "read");  //predefined (standard)
    add(stackOfTrees, 7, "write"); //predefined (standard)
    add(stackOfTrees, 8, "constraint_error");  //Predeclared
    add(stackOfTrees, 9, "numeric_error");     //Predeclared


    // NEED IN ORDER TO MODIFY THE CONTENTS OF NODES IN THE OUTER CONTEXT
    Node* intNode = localSearch(stackOfTrees[top].rootPointer, "integer");
    Node* boolNode = localSearch(stackOfTrees[top].rootPointer, "boolean");
    Node* trueNode = localSearch(stackOfTrees[top].rootPointer, "true");
    Node* falseNode = localSearch(stackOfTrees[top].rootPointer, "false");
    Node* maxintNode = localSearch(stackOfTrees[top].rootPointer, "maxint");
    Node* readRoutineNode = localSearch(stackOfTrees[top].rootPointer, "read");
    Node* writeRoutineNode = localSearch(stackOfTrees[top].rootPointer, "write");
    Node* constraintErrorNode = localSearch(stackOfTrees[top].rootPointer, "constraint_error");  
    Node* numericErrorNode = localSearch(stackOfTrees[top].rootPointer, "numeric_error"); 


    // BINARY TREE NODE KIND
    intNode->kind =   type;   // enum 4
    boolNode->kind =  type;   // enum 4
    trueNode->kind =  value;  // enum 5 
    falseNode->kind = value;  // enum 5
    maxintNode->kind = value; // enum 5
    readRoutineNode->kind =  read_routine;  // enum 7
    writeRoutineNode->kind = write_routine; // enum 8
    constraintErrorNode->kind = exception;  // enum 6
    numericErrorNode->kind = exception;     // enum 6
    

    // OCCUPIED AMOUNT OF SPACE ON STACK.
    intNode->offset = 1;     //integer takes up 1 piece of memory
    boolNode->offset = 1;    //boolean takes up 1 piece of memory
    intNode->memorySpace = 1;
    boolNode->memorySpace = 1;
    
    trueNode->offset = 1;             // default
    falseNode->offset = 1;            // default
    maxintNode->offset = 1;           // default
    readRoutineNode->offset = 1;      // default
    writeRoutineNode->offset = 1;     // default
    constraintErrorNode->offset = 1;  // default
    numericErrorNode->offset = 1;     // default


    // EXCEPTION NUMBER OF A NODE WITH EXCEPTION KIND
    constraintErrorNode->exceptionNumber = 1;   // in Outer Context
    numericErrorNode->exceptionNumber = 2;      // in Outer Context

    
    // PRINT CURRENT NODES IN OUTER CONTEXT 
    printf("Outer Context\nboolean - %s\n", returnKind(boolNode));
    printf("integer - %s\n", returnKind(intNode));
    printf("false - %s\n", returnKind(falseNode));
    printf("maxint - %s\n", returnKind(maxintNode));
    printf("true - %s\n", returnKind(trueNode));
    printf("read - %s\n", returnKind(readRoutineNode));
    printf("write - %s\n", returnKind(writeRoutineNode));
    printf("constraint_error - %s\n", returnKind(constraintErrorNode)); // exception
    printf("numeric_error - %s\n", returnKind(numericErrorNode));       // exception 

    
    // GLOBAL RECORD TO KEEP TRACK OF CURRENT PROGRAM COUNTER, OFFSET AND EXCEPTION NUMBERS
    // globalRecord variable is initialized and declared at the top of this file
    globalRecord.pc = 0;               // Program counter of Abstract Machine Instruction
    globalRecord.registerNumber = 2;   // start at r2 because r1 is used for excpetions
    globalRecord.exceptionNumber = 3;  // 1 is for contraint_error, 2 is for numeric_error, 3 is for the user defined exception variable


    // READY TO WRITE COMPILED CODE INTO THIS FILE (FILE WLL NOT BE PATCHED)
    // output variable is declared at the top of this file
    output = fopen("AMI_Output.out", "w+");
    if (output == NULL) {
        printf("cannot open AMI_Output.out\n");
        return 1;
    }

    // PARSE THE GRAMMAR
    yyparse(); 


    // FOLLOWING CODE TRANSFERS ALL COMPILED CODE FROM AMI_Output.out FILE INTO AMI_Output_Patched.out FILE
    // AMI_Output_Patched.out FILE WILL CONTAIN THE PATCHED PROGRAM COUNTER LINE NUMBERS
    FILE *outputPatched;
    outputPatched = fopen("AMI_Output_Patched.out", "w+");
    if (outputPatched == NULL) {
        printf("cannot open AMI_Output_Patched.out\n");
        return 1;
    }

    rewind(output);           // Set the position indicator associated with the output.out file stream at the beginning
    char readLine [75] = "";  // Stores the current line in the file
    char pcLine [6];          // maximum program counter line that can be represented is: 100000 - 1
    char sentinelOne[] = ":"; 
    size_t length = 0;
    int pcNumber = 0;

    // Need for replcaing the char, ?, with the appropriate jumpNumber from the patchList
    ListNodePtr traversePatchList = patchList;
    char sentinelTwo[] = "?";
    size_t lengthTwo = 0;
     
    //Need for converting string into a number
    size_t lengthThree = 0; 

        while ( feof(output) == 0 &&  fgets (readLine , 75 , output) != NULL ) {
            // Step 1: Grab the current pc number from the abstract machine instructions
            length = strcspn(readLine, sentinelOne); // Get length of pc number
            strncpy(pcLine, readLine, length);       // Grab that pc Line
            pcNumber = atoi(pcLine);                 // Convert pc line into an integer
            //printf("---%d---\n", pcNumber);        // Debugging

            //Step 2: Compare this pc number with the current patchLine in the patchList
            if (traversePatchList != NULL && pcNumber == traversePatchList->patchLine) {
                // Firstly, Replace the char ? with the jumpNumber
                char readLinePatched[75] = "";
                lengthTwo = strcspn(readLine, sentinelTwo);       // Get the length up until the char, ?
                strncpy(readLinePatched, readLine, lengthTwo);    // Grab everything up until the char, ?

                // Secondly, Convert jumpNumber of type int into a string
                int lengthThree = snprintf( NULL, 0, "%d", traversePatchList->jumpNumber);
                char* str = malloc( lengthThree + 1 );
                snprintf( str, lengthThree + 1, "%d", traversePatchList->jumpNumber);
                strncat(readLinePatched, str, 6);                 // 5 means the maximum program counter line that can be represented is: 100000 - 1
                //printf("(%zu, %zu)\n", strlen(readLine), lengthTwo+1); // Debugging

                // Thirdly, If the last character in the readLine string is, ?, then don't have to append the rest of the compiled code from readLine string
                if (strlen(readLine) == (lengthTwo + 2)) { 
                    strncat(readLinePatched, "\0", 2);
                    strncat(readLinePatched, "\n", 2);
                }
                else {
                    strncat(readLinePatched, " ", 2);
                    strncat(readLinePatched, readLine + lengthTwo + 2, 75);
                }

                fputs (readLinePatched, outputPatched);
                traversePatchList = traversePatchList->next;
                free(str);
            }
            // Current compiled code line did not need patching
            else {
                fputs (readLine, outputPatched);
            }

            //printf("%s%s%zu\n\n", readLine, readLinePatched, lengthTwo); //Debugging
        }

    
    fclose(outputPatched); // Close patched file
    fclose(output);        // Close unpatched file
}

