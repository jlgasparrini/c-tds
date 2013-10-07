/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "yaccC-TDS.y"

#  include  <stdio.h>
#  include  <ctype.h>
#  include  <string.h>
#  include  <stdlib.h>
#  include  "../SymbolsTable/Attribute.h"
#  include  "../SymbolsTable/SymbolsTable.h"
#  include  "../SymbolsTable/StringStack.h"
#  include  "../SymbolsTable/Utils.h"
#  include  "../ErrorsQueue/ErrorsQueue.h"
#  include	"../Stack/stack.h"
#  include  "../Stack/label.h"
#  include  "../Code3D/gencode3d.h"
#  include   "../Code3D/codespecs.h"

extern FILE *yyin;
ErrorsQueue *errorQ;						/* Errors Queue definition */
SymbolsTable symbolTable;					/* <----Symbols Table Definition----- */
StringStack *paramsStack, *methodsIDStack;  /* StringStack containing the amount of parameters and lastCalledMethods in each level of method_call*/
unsigned char cantParams = 0, returns;		/* Amount of parameters and amount of returns that a method will have. */
PrimitiveType vaType;						/* Type of the variable or array */
ReturnType mType;							/* Return type of the method */
char *lastDefMethod, *lastCalledMethod = "";/* Name of the last defined method (lastDefMethod) and the last called method (lastCalledMethod) */

/*Variables used to code 3D*/

LCode3D *lcode3d;
char *labelID = "label_%d";
int  labelCount = 0;

Stack *labelsCYC;
Stack *labelsWhile;
Stack *labelsFor;

/*Create new Label*/
char* newLabel() {
        char *labelName = malloc(sizeof(char)*20);
        sprintf(labelName, labelID, labelCount);
        labelCount++;
        return labelName;
}


int yydebug = 1;

int yyerror (char *str)
{
		printErrorList(errorQ);
        deleteAllErrors(errorQ);
        if (strcmp(str, "syntax error") == 0)
			printf("%s\n",toString("Error GRAMATICO.","",""));
        else
			printf("%s\n",toString("Error DESCONOCIDO: \"",str,"\"."));
        return 0;
}
 
int yywrap()
{
	return 1;
} 
  
main( argc, argv )
    int argc;
    char **argv;
    {
        ++argv, --argc;	/* skip over program name */
        if ( argc > 0 )
                yyin = fopen( argv[0], "r" );
        else
                yyin = stdin;
                yyparse();
    }

finalizar() {
		printErrorList(errorQ);
        deleteAllErrors(errorQ);
        printf("------Se termino de parsear.----------\n");
		// show the list of code 3D
		//int cantCodes = cantCode(lcode3d);
        //int i;
        //for (i = 0; i < cantCodes; i++) {
        //        Code3D *code = get_code(lcode3d, i);
        //        toString(code);
        //}
}

out(char *msg) {
        printf("%s\n", msg);
}




/* Line 268 of yacc.c  */
#line 165 "y.tab.c"

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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     FLOAT = 258,
     INTEGER = 259,
     BOOLEAN = 260,
     INTW = 261,
     FLOATW = 262,
     BOOLEANW = 263,
     ID = 264,
     PLUSEQUAL = 265,
     MINUSEQUAL = 266,
     EQUAL = 267,
     DISTINCT = 268,
     GEQUAL = 269,
     LEQUAL = 270,
     OR = 271,
     AND = 272,
     BREAK = 273,
     IF = 274,
     CONTINUE = 275,
     ELSE = 276,
     RETURN = 277,
     WHILE = 278,
     CLASS = 279,
     FOR = 280,
     VOID = 281,
     EXTERNINVK = 282,
     STRING = 283
   };
#endif
/* Tokens.  */
#define FLOAT 258
#define INTEGER 259
#define BOOLEAN 260
#define INTW 261
#define FLOATW 262
#define BOOLEANW 263
#define ID 264
#define PLUSEQUAL 265
#define MINUSEQUAL 266
#define EQUAL 267
#define DISTINCT 268
#define GEQUAL 269
#define LEQUAL 270
#define OR 271
#define AND 272
#define BREAK 273
#define IF 274
#define CONTINUE 275
#define ELSE 276
#define RETURN 277
#define WHILE 278
#define CLASS 279
#define FOR 280
#define VOID 281
#define EXTERNINVK 282
#define STRING 283




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 95 "yaccC-TDS.y"

	char *stringValue;
	Attribute *at;



/* Line 293 of yacc.c  */
#line 264 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 276 "y.tab.c"

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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   217

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  56
/* YYNRULES -- Number of rules.  */
#define YYNRULES  115
/* YYNRULES -- Number of states.  */
#define YYNSTATES  196

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   283

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,     2,     2,    35,     2,     2,
      42,    43,    33,    31,    39,    32,     2,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    38,
      29,    44,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    40,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
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
      25,    26,    27,    28
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,     9,    10,    18,    21,    23,    25,
      29,    34,    36,    40,    42,    43,    49,    51,    53,    55,
      56,    62,    63,    70,    71,    77,    78,    85,    86,    90,
      91,    92,    98,   101,   102,   108,   111,   115,   118,   120,
     122,   124,   127,   129,   131,   134,   135,   138,   139,   141,
     143,   145,   148,   150,   152,   156,   158,   160,   162,   163,
     164,   165,   176,   177,   184,   185,   186,   192,   193,   194,
     195,   206,   208,   213,   217,   218,   224,   231,   240,   242,
     243,   248,   250,   252,   254,   258,   260,   262,   264,   268,
     270,   274,   276,   280,   282,   286,   288,   292,   296,   300,
     304,   306,   310,   314,   318,   322,   326,   328,   331,   334,
     336,   338,   340,   342,   347,   351
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    24,     9,    36,    37,    -1,    -1,    -1,
      24,     9,    36,    48,    50,    49,    37,    -1,    51,    56,
      -1,    51,    -1,    56,    -1,    55,    52,    38,    -1,    51,
      55,    52,    38,    -1,    53,    -1,    52,    39,    53,    -1,
       9,    -1,    -1,     9,    40,     4,    54,    41,    -1,     6,
      -1,     7,    -1,     8,    -1,    -1,    55,     9,    57,    61,
      67,    -1,    -1,    56,    55,     9,    58,    61,    67,    -1,
      -1,    26,     9,    59,    61,    67,    -1,    -1,    56,    26,
       9,    60,    61,    67,    -1,    -1,    42,    62,    43,    -1,
      -1,    -1,    42,    63,    65,    64,    43,    -1,    55,     9,
      -1,    -1,    55,     9,    66,    39,    65,    -1,    36,    37,
      -1,    36,    68,    37,    -1,    51,    69,    -1,    69,    -1,
      51,    -1,    70,    -1,    69,    70,    -1,    75,    -1,    80,
      -1,    72,    38,    -1,    -1,    71,    67,    -1,    -1,    18,
      -1,    20,    -1,    22,    -1,    22,    94,    -1,    73,    -1,
      87,    -1,    86,    74,    94,    -1,    44,    -1,    10,    -1,
      11,    -1,    -1,    -1,    -1,    19,    42,    94,    76,    43,
      67,    77,    21,    78,    67,    -1,    -1,    19,    42,    94,
      79,    43,    67,    -1,    -1,    -1,    23,    81,    94,    82,
      67,    -1,    -1,    -1,    -1,    25,    83,     9,    84,    44,
      94,    39,    94,    85,    67,    -1,     9,    -1,     9,    40,
      99,    41,    -1,     9,    42,    43,    -1,    -1,     9,    42,
      88,    89,    43,    -1,    27,    42,    28,    39,    91,    43,
      -1,    27,    42,    28,    39,    91,    39,    92,    43,    -1,
      94,    -1,    -1,    94,    90,    39,    89,    -1,    55,    -1,
      26,    -1,    93,    -1,    93,    39,    92,    -1,    94,    -1,
      28,    -1,    95,    -1,    94,    16,    95,    -1,    96,    -1,
      95,    17,    96,    -1,    97,    -1,    96,    13,    97,    -1,
      98,    -1,    98,    12,    98,    -1,    99,    -1,    99,    29,
      99,    -1,    99,    30,    99,    -1,    99,    14,    99,    -1,
      99,    15,    99,    -1,   100,    -1,    99,    31,   100,    -1,
      99,    32,   100,    -1,    99,    35,   100,    -1,    99,    34,
     100,    -1,    99,    33,   100,    -1,   101,    -1,    45,   100,
      -1,    32,   100,    -1,     4,    -1,     3,    -1,     5,    -1,
       9,    -1,     9,    40,    99,    41,    -1,    42,    94,    43,
      -1,    87,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   120,   120,   124,   135,   124,   142,   143,   144,   147,
     148,   151,   152,   155,   156,   156,   160,   161,   162,   165,
     165,   173,   173,   181,   181,   189,   189,   200,   200,   201,
     203,   201,   206,   208,   208,   212,   213,   216,   217,   218,
     221,   222,   229,   230,   231,   232,   232,   235,   236,   243,
     252,   260,   271,   272,   275,   303,   304,   305,   312,   323,
     326,   312,   335,   335,   351,   355,   351,   369,   373,   378,
     369,   400,   401,   404,   407,   407,   411,   412,   415,   416,
     416,   419,   420,   423,   424,   427,   428,   431,   432,   435,
     436,   439,   440,   443,   444,   447,   448,   449,   450,   451,
     454,   455,   456,   457,   458,   459,   462,   463,   464,   467,
     468,   469,   470,   471,   472,   473
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FLOAT", "INTEGER", "BOOLEAN", "INTW",
  "FLOATW", "BOOLEANW", "ID", "PLUSEQUAL", "MINUSEQUAL", "EQUAL",
  "DISTINCT", "GEQUAL", "LEQUAL", "OR", "AND", "BREAK", "IF", "CONTINUE",
  "ELSE", "RETURN", "WHILE", "CLASS", "FOR", "VOID", "EXTERNINVK",
  "STRING", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'{'", "'}'",
  "';'", "','", "'['", "']'", "'('", "')'", "'='", "'!'", "$accept",
  "program", "$@1", "$@2", "body", "fields_decls", "fields", "field",
  "$@3", "type", "method_decl", "$@4", "$@5", "$@6", "$@7", "param", "$@8",
  "$@9", "$@10", "parameters", "$@11", "block", "codeBlock", "statements",
  "statement", "$@12", "action", "asignation", "assig_op", "conditional",
  "$@13", "$@14", "$@15", "$@16", "iteration", "$@17", "$@18", "$@19",
  "$@20", "$@21", "location", "method_call", "$@22", "expression_aux",
  "$@23", "typevoid", "externinvk_arg", "arg", "expression", "conjunction",
  "inequality", "comparison", "relation", "term", "factor", "primary", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    60,
      62,    43,    45,    42,    47,    37,   123,   125,    59,    44,
      91,    93,    40,    41,    61,    33
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    48,    49,    47,    50,    50,    50,    51,
      51,    52,    52,    53,    54,    53,    55,    55,    55,    57,
      56,    58,    56,    59,    56,    60,    56,    62,    61,    63,
      64,    61,    65,    66,    65,    67,    67,    68,    68,    68,
      69,    69,    70,    70,    70,    71,    70,    72,    72,    72,
      72,    72,    72,    72,    73,    74,    74,    74,    76,    77,
      78,    75,    79,    75,    81,    82,    80,    83,    84,    85,
      80,    86,    86,    87,    88,    87,    87,    87,    89,    90,
      89,    91,    91,    92,    92,    93,    93,    94,    94,    95,
      95,    96,    96,    97,    97,    98,    98,    98,    98,    98,
      99,    99,    99,    99,    99,    99,   100,   100,   100,   101,
     101,   101,   101,   101,   101,   101
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     0,     0,     7,     2,     1,     1,     3,
       4,     1,     3,     1,     0,     5,     1,     1,     1,     0,
       5,     0,     6,     0,     5,     0,     6,     0,     3,     0,
       0,     5,     2,     0,     5,     2,     3,     2,     1,     1,
       1,     2,     1,     1,     2,     0,     2,     0,     1,     1,
       1,     2,     1,     1,     3,     1,     1,     1,     0,     0,
       0,    10,     0,     6,     0,     0,     5,     0,     0,     0,
      10,     1,     4,     3,     0,     5,     6,     8,     1,     0,
       4,     1,     1,     1,     3,     1,     1,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     3,     3,     3,     1,     2,     2,     1,
       1,     1,     1,     4,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     2,     0,    16,    17,
      18,     0,     4,     7,     0,     8,    23,     0,     0,     6,
      13,     0,    11,     0,     0,     0,     5,     0,     0,     0,
       9,     0,    25,    21,    29,     0,    10,    14,     0,    13,
      12,     0,     0,     0,     0,    45,    24,     0,    20,     0,
       0,    28,     0,    30,    71,    48,     0,    49,    50,    64,
      67,     0,    35,    39,     0,     0,    38,    40,     0,     0,
      52,    42,    43,     0,    53,    15,    26,    22,    32,     0,
       0,    74,     0,   110,   109,   111,   112,     0,     0,     0,
     115,    51,    87,    89,    91,    93,    95,   100,   106,     0,
       0,     0,     0,    37,    36,    41,    46,    44,    56,    57,
      55,     0,     0,    31,     0,    73,     0,    58,     0,   108,
       0,   107,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    68,     0,    54,     0,
      72,     0,    78,     0,     0,     0,   114,    88,    90,    92,
      94,    98,    99,    96,    97,   101,   102,   105,   104,   103,
       0,     0,     0,    34,    75,     0,     0,     0,   113,    66,
       0,    82,    81,     0,     0,    59,    63,     0,     0,    76,
      80,     0,     0,    86,     0,    83,    85,    60,    69,    77,
       0,     0,     0,    84,    61,    70
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,    17,    12,    13,    21,    22,    47,    24,
      15,    29,    42,    25,    41,    35,    43,    44,    79,    53,
     112,    46,    65,    66,    67,    68,    69,    70,   111,    71,
     143,   181,   191,   144,    72,    99,   160,   100,   161,   192,
      73,    90,   116,   141,   165,   173,   184,   185,   142,    92,
      93,    94,    95,    96,    97,    98
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -78
static const yytype_int16 yypact[] =
{
     -10,     9,    22,     4,   -78,    16,   -78,    85,   -78,   -78,
     -78,    34,   -78,    85,    52,    88,   -78,    21,    52,    88,
     -13,    38,   -78,    58,    62,    36,   -78,    71,    82,    36,
     -78,    89,   -78,   -78,    64,    69,   -78,   -78,    69,    73,
     -78,    36,    36,    74,   123,    81,   -78,    79,   -78,    69,
      69,   -78,   112,   -78,     6,   -78,    83,   -78,    70,   -78,
     -78,    84,   -78,   142,    89,    98,   154,   -78,    69,   106,
     -78,   -78,   -78,    -2,   -78,   -78,   -78,   -78,   107,   102,
      70,   104,    70,   -78,   -78,   -78,    28,    70,    70,    70,
     -78,   136,   137,   140,   -78,   144,   108,   -78,   -78,    70,
     148,   138,    89,   154,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,    70,   129,   -78,   162,   -78,    70,   136,    70,   -78,
      -4,   -78,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,   136,   -78,   131,   136,   123,
     -78,   128,    -6,   132,   143,   173,   -78,   137,   140,   -78,
     -78,    49,    49,    49,    49,   -78,   -78,   -78,   -78,   -78,
      69,   141,   176,   -78,   -78,   149,    69,    69,   -78,   -78,
      70,   -78,   -78,   -28,    70,   -78,   -78,     8,    27,   -78,
     -78,   166,    70,   -78,   146,   152,   136,   -78,   136,   -78,
      27,    69,    69,   -78,   -78,   -78
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -78,   -78,   -78,   -78,   -78,   153,   -17,   168,   -78,    -7,
     187,   -78,   -78,   -78,   -78,   -16,   -78,   -78,   -78,    72,
     -78,   -33,   -78,   147,   -59,   -78,   -78,   -78,   -78,   -78,
     -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,   -78,
     -78,   -43,   -78,    35,   -78,   -78,    11,   -78,   -54,    90,
      92,    93,    91,   -77,   -68,   -78
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -80
static const yytype_int16 yytable[] =
{
      14,    27,    74,   114,    91,    48,    18,   105,   108,   109,
     122,   178,   122,    38,     1,   179,    76,    77,     3,   119,
      74,   121,     4,    74,   122,    49,    50,    28,   117,   -19,
      83,    84,    85,   -79,   120,   106,    86,    52,    64,   146,
       5,   145,   110,    16,   105,   135,    80,   182,    81,   151,
     152,   153,   154,     6,    61,   183,   102,   138,    26,    87,
      74,    20,   155,   156,   157,   158,   159,    32,   118,    88,
      81,    33,    89,    83,    84,    85,    30,    31,    34,    86,
     130,   131,   132,   133,   134,    27,    37,     8,     9,    10,
      54,     8,     9,    10,     8,     9,    10,    61,    39,    55,
      56,    57,    87,    58,    59,    45,    60,   -27,    61,    36,
      31,    11,    88,    28,    23,    89,   177,    51,    62,   -47,
      75,    78,   126,   127,   186,    82,   101,   169,   188,     8,
       9,    10,    52,   175,   176,   104,   186,   128,   129,   130,
     131,   132,   133,   134,   107,   113,   -33,   115,     8,     9,
      10,    54,   122,   124,   123,   172,   125,   136,   194,   195,
      55,    56,    57,    54,    58,    59,   137,    60,   139,    61,
     162,   164,    55,    56,    57,   166,    58,    59,   -45,    60,
     -47,    61,     8,     9,    10,   170,   167,   187,   174,   189,
     -45,   190,   -47,   130,   131,   132,   133,   134,    63,    40,
      19,   193,   171,   140,   130,   131,   132,   133,   134,   180,
     103,   163,   147,     0,   168,   148,   150,   149
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-78))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       7,    18,    45,    80,    58,    38,    13,    66,    10,    11,
      16,    39,    16,    29,    24,    43,    49,    50,     9,    87,
      63,    89,     0,    66,    16,    41,    42,    40,    82,    42,
       3,     4,     5,    39,    88,    68,     9,    44,    45,    43,
      36,   118,    44,     9,   103,    99,    40,    39,    42,   126,
     127,   128,   129,    37,    27,    28,    63,   111,    37,    32,
     103,     9,   130,   131,   132,   133,   134,     9,    40,    42,
      42,     9,    45,     3,     4,     5,    38,    39,    42,     9,
      31,    32,    33,    34,    35,   102,     4,     6,     7,     8,
       9,     6,     7,     8,     6,     7,     8,    27,     9,    18,
      19,    20,    32,    22,    23,    36,    25,    43,    27,    38,
      39,    26,    42,    40,    26,    45,   170,    43,    37,    38,
      41,     9,    14,    15,   178,    42,    42,   160,   182,     6,
       7,     8,   139,   166,   167,    37,   190,    29,    30,    31,
      32,    33,    34,    35,    38,    43,    39,    43,     6,     7,
       8,     9,    16,    13,    17,   162,    12,     9,   191,   192,
      18,    19,    20,     9,    22,    23,    28,    25,    39,    27,
      39,    43,    18,    19,    20,    43,    22,    23,    36,    25,
      38,    27,     6,     7,     8,    44,    43,    21,    39,    43,
      36,    39,    38,    31,    32,    33,    34,    35,    45,    31,
      13,   190,    26,    41,    31,    32,    33,    34,    35,   174,
      63,   139,   122,    -1,    41,   123,   125,   124
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    47,     9,     0,    36,    37,    48,     6,     7,
       8,    26,    50,    51,    55,    56,     9,    49,    55,    56,
       9,    52,    53,    26,    55,    59,    37,    52,    40,    57,
      38,    39,     9,     9,    42,    61,    38,     4,    61,     9,
      53,    60,    58,    62,    63,    36,    67,    54,    67,    61,
      61,    43,    55,    65,     9,    18,    19,    20,    22,    23,
      25,    27,    37,    51,    55,    68,    69,    70,    71,    72,
      73,    75,    80,    86,    87,    41,    67,    67,     9,    64,
      40,    42,    42,     3,     4,     5,     9,    32,    42,    45,
      87,    94,    95,    96,    97,    98,    99,   100,   101,    81,
      83,    42,    55,    69,    37,    70,    67,    38,    10,    11,
      44,    74,    66,    43,    99,    43,    88,    94,    40,   100,
      94,   100,    16,    17,    13,    12,    14,    15,    29,    30,
      31,    32,    33,    34,    35,    94,     9,    28,    94,    39,
      41,    89,    94,    76,    79,    99,    43,    95,    96,    97,
      98,    99,    99,    99,    99,   100,   100,   100,   100,   100,
      82,    84,    39,    65,    43,    90,    43,    43,    41,    67,
      44,    26,    55,    91,    39,    67,    67,    94,    39,    43,
      89,    77,    39,    28,    92,    93,    94,    21,    94,    43,
      39,    78,    85,    92,    67,    67
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

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
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
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
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

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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

/* Line 1806 of yacc.c  */
#line 120 "yaccC-TDS.y"
    {
									errorQ=initializeQueue(); 
									finalizar();
					}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 124 "yaccC-TDS.y"
    {
									initializeSymbolsTable(&symbolTable); 
									pushLevel(&symbolTable);
									errorQ=initializeQueue();
									paramsStack=initializeSS(); 
									methodsIDStack=initializeSS();
									labelsCYC = newStack();
                                    labelsWhile = newStack();
									labelsFor = newStack();
									labelsMethod = newStack();
									lcode3d = initLCode3D();
					}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 135 "yaccC-TDS.y"
    {
								checkMain(errorQ,&symbolTable); 
								popLevel(&symbolTable); 
								finalizar();
					}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 155 "yaccC-TDS.y"
    {pushElement(errorQ, &symbolTable, createVariable((yyvsp[(1) - (1)].stringValue), vaType));}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 156 "yaccC-TDS.y"
    {if (atoi((yyvsp[(3) - (3)].stringValue)) <= 0) insertError(errorQ,toString("Error en definicion del arreglo \"",(yyvsp[(1) - (3)].stringValue),"\". El tamaño del arreglo debe ser un entero mayor que 0."));
										pushElement(errorQ, &symbolTable, createArray((yyvsp[(1) - (3)].stringValue), vaType, atoi((yyvsp[(3) - (3)].stringValue))));}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 160 "yaccC-TDS.y"
    {vaType = Int; mType = RetInt;}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 161 "yaccC-TDS.y"
    {vaType = Float; mType = RetFloat;}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 162 "yaccC-TDS.y"
    {vaType = Bool; mType = RetBool;}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 165 "yaccC-TDS.y"
    {
								lastDefMethod=(yyvsp[(2) - (2)].stringValue); 
								pushElement(errorQ,&symbolTable,createMethod((yyvsp[(2) - (2)].stringValue),mType,0)); 
								pushLevel(&symbolTable); returns=0;
					}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 169 "yaccC-TDS.y"
    {
								popLevel(&symbolTable); 
								if(returns==0) insertError(errorQ,toString("El metodo \"",(yyvsp[(2) - (5)].stringValue),"\" debe tener al menos un return."));
					}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 173 "yaccC-TDS.y"
    {
								lastDefMethod=(yyvsp[(3) - (3)].stringValue); 
								pushElement(errorQ,&symbolTable,createMethod((yyvsp[(3) - (3)].stringValue),mType,0)); 
								pushLevel(&symbolTable); returns=0;
					}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 177 "yaccC-TDS.y"
    {
								popLevel(&symbolTable); 
								if(returns==0) insertError(errorQ,toString("El metodo \"",(yyvsp[(3) - (6)].stringValue),"\" debe tener al menos un return."));
					}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 181 "yaccC-TDS.y"
    {
								lastDefMethod=(yyvsp[(2) - (2)].stringValue); 
								pushElement(errorQ,&symbolTable,createMethod((yyvsp[(2) - (2)].stringValue),RetVoid,0)); 
								pushLevel(&symbolTable); returns=0;
					}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 185 "yaccC-TDS.y"
    {
								popLevel(&symbolTable); 
								if(returns==0) insertError(errorQ,toString("El metodo \"",(yyvsp[(2) - (5)].stringValue),"\" debe tener al menos un return."));
					}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 189 "yaccC-TDS.y"
    {
								lastDefMethod=(yyvsp[(3) - (3)].stringValue); 
								pushElement(errorQ,&symbolTable,createMethod((yyvsp[(3) - (3)].stringValue),RetVoid,0)); 
								pushLevel(&symbolTable); 
								returns=0;
					}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 194 "yaccC-TDS.y"
    {
								popLevel(&symbolTable); 
								if(returns==0) insertError(errorQ,toString("El metodo \"",(yyvsp[(3) - (6)].stringValue),"\" debe tener al menos un return."));
					}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 200 "yaccC-TDS.y"
    {cantParams = 0; setAmountOfParameters(searchIdInSymbolsTable(errorQ,&symbolTable,lastDefMethod),0);}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 201 "yaccC-TDS.y"
    {if (strcmp(lastDefMethod,"main") == 0)
							insertError(errorQ,toString("El metodo \"main\" no debe contener parametros.","","")); cantParams = 0;}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 203 "yaccC-TDS.y"
    {setAmountOfParameters(searchIdInSymbolsTable(errorQ,&symbolTable,lastDefMethod),cantParams);}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 206 "yaccC-TDS.y"
    {Attribute *aux = createParameter(lastDefinedMethod(&symbolTable),cantParams,(yyvsp[(2) - (2)].stringValue),vaType);
								if (aux != NULL) {pushElement(errorQ,&symbolTable,aux); cantParams++;}}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 208 "yaccC-TDS.y"
    {Attribute *aux = createParameter(lastDefinedMethod(&symbolTable),cantParams,(yyvsp[(2) - (2)].stringValue),vaType);
								if (aux != NULL) {pushElement(errorQ,&symbolTable,aux); cantParams++;}}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 232 "yaccC-TDS.y"
    {pushLevel(&symbolTable);}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 232 "yaccC-TDS.y"
    {popLevel(&symbolTable);}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 236 "yaccC-TDS.y"
    {
							if (isEmpty(labelsWhile)|| isEmpty(labelsFor)) {
								insertError(errorQ,toString("Error. Solo se puede usar la sentencia \"break\" dentro de un ciclo.","",""));
							} else {
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), peek(labelWhile)->label); //Go to Label of End of While
							}
					}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 243 "yaccC-TDS.y"
    {
							if (isEmpty(labelsWhile)|| isEmpty(labelsFor)) {
                                insertError(errorQ,toString("Error. Solo se puede usar la sentencia \"continue\" dentro de un ciclo.","",""));
							} else {
                                Label *endOfWhile = pop(labelWhile); //Label of End of While
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), peek(labelWhile)->label); //Go to Label of Init of While
								push(labelWhile, endOfWhile->label, NULL);
							} 
					}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 252 "yaccC-TDS.y"
    {
							returns++; 
							checkReturn(errorQ,&symbolTable,lastDefMethod);
							Code3D *ret = newCode(COM_RETURN);
							setCode1D(ret, void);
							add_code(lcode3d, ret);
							// TODO
					}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 260 "yaccC-TDS.y"
    {
									returns++; 									
									if (checkReturnExpression(errorQ,&symbolTable,lastDefMethod,(yyvsp[(2) - (2)].at)) == 0) { //CHEK TIPE
										Code3D *loadToReturn = newCode(LOAD_MEM);
										setCode2D(loadToReturn, ((yyvsp[(2) - (2)].at)), retorno); //fijarse de como puedo obtener la variable de retorno
										add_code(lcode3d, loadToReturn);
										Code3D *ret = newCode(COM_RETURN);
										setCode1D(ret, retorno);
										add_code(lcode3d, ret);
									}
					}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 275 "yaccC-TDS.y"
    {
							controlAssignation(errorQ,(yyvsp[(1) - (3)].at),(yyvsp[(2) - (3)].stringValue),(yyvsp[(3) - (3)].at));
							if (strcmp((yyvsp[(2) - (3)].stringValue), PLUSEQUAL) == 0){
								if ((getAttributeType((yyvsp[(1) - (3)].at)) == Int) && (getAttributeType((yyvsp[(3) - (3)].at)) == Int)){
									Code3D *add = newCode(COM_ADD_INT);
								} 
								if ((getAttributeType((yyvsp[(1) - (3)].at)) == Float) && (getAttributeType((yyvsp[(3) - (3)].at)) == Float)){
									Code3D *add = newCode(COM_ADD_FLOAT);
								}
								setCode2D(add, ((yyvsp[(1) - (3)].at)), ((yyvsp[(3) - (3)].at)));
								add_code(lcode3d, add)
							} 
							if (strcmp((yyvsp[(2) - (3)].stringValue), MINUSEQUAL) == 0){
								if ((getAttributeType((yyvsp[(1) - (3)].at)) == Int) && (getAttributeType((yyvsp[(3) - (3)].at)) == Int)){
									Code3D *add = newCode(COM_MINUS_INT);
								} 
								if ((getAttributeType((yyvsp[(1) - (3)].at)) == Float) && (getAttributeType((yyvsp[(3) - (3)].at)) == Float)){
									Code3D *add = newCode(COM_MINUS_FLOAT);																				
								}
								setCode2D(add, ((yyvsp[(1) - (3)].at)), ((yyvsp[(3) - (3)].at)));
								add_code(lcode3d, add)
							}
							Code3D *asig = newCode(STORE_MEM);
							setCode2D(asig, ((yyvsp[(3) - (3)].at)), ((yyvsp[(1) - (3)].at)));
							add_code(lcode3d, asig)
					}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 303 "yaccC-TDS.y"
    {(yyval.stringValue) = "=";}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 304 "yaccC-TDS.y"
    {(yyval.stringValue) = (yyvsp[(1) - (1)].stringValue);}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 305 "yaccC-TDS.y"
    {(yyval.stringValue) = (yyvsp[(1) - (1)].stringValue);}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 312 "yaccC-TDS.y"
    { 
                                if (controlType(errorQ,(yyvsp[(3) - (3)].at),Bool) == 0) {
                                        char *ifLabel = newLabel();
                                        char *elseLabel = newLabel();
                                        char *endLabel = newLabel();
										add_CodeLabelCond(lcode3d, newCode(GOTOLABEL_COND), ((yyvsp[(3) - (3)].at)), ifLabel); //Go to Label of If
										add_CodeLabel(lcode3d, newCode(GOTOLABEL), elseLabel); //Go to Label of Else
                                        add_CodeLabel(lcode3d, newCode(COM_MARK), ifLabel); // Mark to Label of If
                                        push(labelsCYC, elseLabel, NULL);
                                        push(labelsCYC, endLabel, NULL);
								}
					}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 323 "yaccC-TDS.y"
    {
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), peek(labelsCYC)->label); //Go to Label of End
										
					}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 326 "yaccC-TDS.y"
    {
                                Label *markEnd = pop(labelsCYC);
								add_CodeLabel(lcode3d, newCode(COM_MARK), pop(labelsCYC)->label); // Mark to Label of Else
                                push(labelsCYC, markEnd->label, NULL);
                    }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 330 "yaccC-TDS.y"
    {
                                Label *markEnd = pop(labelsCYC);
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), markEnd->label); // Go to Label of End
								add_CodeLabel(lcode3d, newCode(COM_MARK), markEnd->label); // Mark to Label of End
                    }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 335 "yaccC-TDS.y"
    { 
                                if (controlType(errorQ,(yyvsp[(3) - (3)].at),Bool) == 0) {
                                        char *ifLabel = newLabel();
                                        char *endLabel = newLabel();
										add_CodeLabelCond(lcode3d, newCode(GOTOLABEL_COND), ((yyvsp[(3) - (3)].at)), ifLabel); //Go to Label of If
										add_CodeLabel(lcode3d, newCode(GOTOLABEL), endLabel); //Go to Label of End
                                        add_CodeLabel(lcode3d, newCode(COM_MARK), ifLabel); // Mark to Label of If
                                        push(labelsCYC, endLabel, NULL);
                                }
					}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 344 "yaccC-TDS.y"
    {
								Label *marcEnd = pop(labelsCYC);
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), markEnd->label); // Go to Label of End
								add_CodeLabel(lcode3d, newCode(COM_MARK), markEnd->label); // Mark to Label of End
					}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 351 "yaccC-TDS.y"
    {     
                            char *whileLabel = newLabel(); 
							push(labelsWhile,whileLabel,NULL);
							add_CodeLabel(lcode3d, newCode(COM_MARK), whileLabel); // Mark to Label of While
                    }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 355 "yaccC-TDS.y"
    {
							if (controlType(errorQ,(yyvsp[(3) - (3)].at),Bool) == 0) {
								char *endLabel = newLabel(); 
								push(labelsWhile, endLabel, NULL);
								char *expressionLabel = newLabel();
								add_CodeLabelCond(lcode3d, newCode(GOTOLABEL_COND),((yyvsp[(3) - (3)].at)), expressionLabel); // Go to Label of Expression
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), endLabel); // Go to Label of End
								add_CodeLabel(lcode3d, newCode(COM_MARK), expressionLabel); // Mark to Label of Expression           
                            }
					}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 364 "yaccC-TDS.y"
    {							
							Label *endOfCycle = pop(labelsWhile); 														
							add_CodeLabel(lcode3d, newCode(GOTOLABEL), pop(labelsWhile)->label); // Go to Label of While
							add_CodeLabel(lcode3d, newCode(COM_MARK), endOfCycle->label); // Mark to Label of End
					}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 369 "yaccC-TDS.y"
    {     
                        char *forLabel = newLabel(); 
						push(labelsFor,forLabel,NULL);
						add_CodeLabel(lcode3d, newCode(COM_MARK), forLabel); // Mark to Label of For
                    }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 373 "yaccC-TDS.y"
    {
						if (getAttributeType(getVariableAttribute(errorQ,&symbolTable,(yyvsp[(3) - (3)].stringValue))) != Int){
							insertError(errorQ,toString("El identificador \"", (yyvsp[(3) - (3)].stringValue), "\" no pertenece a una variable de tipo \"int\""));
						}
					}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 378 "yaccC-TDS.y"
    {
								if ((controlType(errorQ,(yyvsp[(6) - (8)].at),Int) == 0) && (controlType(errorQ,(yyvsp[(8) - (8)].at),Int)== 0)) {
									char *endLabel = newLabel();									 
									push(labelsFor, endLabel, NULL);
									char *expressionLabel = newLabel();
									Attribute *res = createVariable("", Bool);
									returnEqual(errorQ, lcode3d, (yyvsp[(6) - (8)].at), (yyvsp[(8) - (8)].at), res); //creo la comparacion la hago aca o lo hago en assembler?
									add_CodeLabelCond(lcode3d, newCode(GOTOLABEL_COND), res, expressionLabel); // Go to Label of Expression (falta hacer la comparacion)
									add_CodeLabel(lcode3d, newCode(GOTOLABEL), endLabel); // Go to Label of End
									add_CodeLabel(lcode3d, newCode(COM_MARK), expressionLabel); // Mark to Label of Expression           
								}
					}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 389 "yaccC-TDS.y"
    {
							Label *endOfCycle = pop(labelsFor); 							 							
							add_CodeLabel(lcode3d, newCode(GOTOLABEL), pop(labelsFor)->label); // Go to Label of For
							add_CodeLabel(lcode3d, newCode(COM_MARK), endOfCycle->label); // Mark to Label of End
					}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 400 "yaccC-TDS.y"
    {(yyval.at) = getVariableAttribute(errorQ, &symbolTable, (yyvsp[(1) - (1)].stringValue));}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 401 "yaccC-TDS.y"
    {(yyval.at) = checkArrayPos(errorQ,&symbolTable,(yyvsp[(1) - (4)].stringValue),(yyvsp[(3) - (4)].at));}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 404 "yaccC-TDS.y"
    {cantParams=0; insertString(paramsStack,intToString(cantParams));
								lastCalledMethod=(yyvsp[(1) - (3)].stringValue); (yyval.at)=getMethodAttribute(errorQ,&symbolTable,(yyvsp[(1) - (3)].stringValue),0);}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 407 "yaccC-TDS.y"
    {insertString(paramsStack,intToString(cantParams)); cantParams=0;
							insertString(methodsIDStack,lastCalledMethod); lastCalledMethod = (yyvsp[(1) - (2)].stringValue);}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 409 "yaccC-TDS.y"
    {(yyval.at) = getMethodAttribute(errorQ,&symbolTable,(yyvsp[(1) - (5)].stringValue),cantParams); cantParams=atoi(removeLastString(paramsStack));}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 411 "yaccC-TDS.y"
    {if (mType != RetVoid) (yyval.at)=createVariable("",mType);}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 412 "yaccC-TDS.y"
    {if (mType != RetVoid) (yyval.at)=createVariable("",mType);}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 415 "yaccC-TDS.y"
    {cantParams++; correctParamBC(errorQ,&symbolTable,(yyvsp[(1) - (1)].at),lastCalledMethod,cantParams);}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 416 "yaccC-TDS.y"
    {cantParams++; correctParamIC(errorQ,&symbolTable,(yyvsp[(1) - (1)].at),lastCalledMethod,cantParams);}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 420 "yaccC-TDS.y"
    {mType = RetVoid;}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 431 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(1) - (1)].at);}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 432 "yaccC-TDS.y"
    {(yyval.at) = returnOr(errorQ, lcode3d, (yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at), (yyval.at));}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 435 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(1) - (1)].at);}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 436 "yaccC-TDS.y"
    {(yyval.at) = returnAnd(errorQ, lcode3d, (yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at), (yyval.at));}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 439 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(1) - (1)].at);}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 440 "yaccC-TDS.y"
    {(yyval.at) = returnDistinct(errorQ, lcode3d, (yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at), (yyval.at));}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 443 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(1) - (1)].at);}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 444 "yaccC-TDS.y"
    {(yyval.at) = returnEqual(errorQ, lcode3d, (yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at), (yyval.at));}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 447 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(1) - (1)].at);}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 448 "yaccC-TDS.y"
    {(yyval.at) = returnMinorComparison(errorQ, lcode3d, (yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at), (yyval.at));}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 449 "yaccC-TDS.y"
    {(yyval.at) = returnMajorComparison(errorQ, lcode3d, (yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at), (yyval.at));}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 450 "yaccC-TDS.y"
    {(yyval.at) = returnGEqualComparison(errorQ, lcode3d, (yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at), (yyval.at));}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 451 "yaccC-TDS.y"
    {(yyval.at) = returnLEqualComparison(errorQ, lcode3d, (yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at), (yyval.at));}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 454 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(1) - (1)].at);}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 455 "yaccC-TDS.y"
    {(yyval.at) = returnAdd(errorQ, lcode3d, (yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at), (yyval.at));}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 456 "yaccC-TDS.y"
    {(yyval.at) = returnSub(errorQ, lcode3d, (yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at), (yyval.at));}
    break;

  case 103:

/* Line 1806 of yacc.c  */
#line 457 "yaccC-TDS.y"
    {(yyval.at) = returnMod(errorQ, lcode3d, (yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at), (yyval.at));}
    break;

  case 104:

/* Line 1806 of yacc.c  */
#line 458 "yaccC-TDS.y"
    {(yyval.at) = returnDiv(errorQ, lcode3d, (yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at), (yyval.at));}
    break;

  case 105:

/* Line 1806 of yacc.c  */
#line 459 "yaccC-TDS.y"
    {(yyval.at) = returnMult(errorQ, lcode3d, (yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at), (yyval.at));}
    break;

  case 106:

/* Line 1806 of yacc.c  */
#line 462 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(1) - (1)].at);}
    break;

  case 107:

/* Line 1806 of yacc.c  */
#line 463 "yaccC-TDS.y"
    {(yyval.at) = returnNot(errorQ, lcode3d, (yyvsp[(2) - (2)].at), (yyval.at));}
    break;

  case 108:

/* Line 1806 of yacc.c  */
#line 464 "yaccC-TDS.y"
    {(yyval.at) = returnNeg(errorQ, lcode3d, (yyvsp[(2) - (2)].at), (yyval.at));}
    break;

  case 109:

/* Line 1806 of yacc.c  */
#line 467 "yaccC-TDS.y"
    {(yyval.at) = returnValue(lcode3d, Int, (yyvsp[(1) - (1)].stringValue), (yyval.at));}
    break;

  case 110:

/* Line 1806 of yacc.c  */
#line 468 "yaccC-TDS.y"
    {(yyval.at) = returnValue(lcode3d, Float, (yyvsp[(1) - (1)].stringValue), (yyval.at));}
    break;

  case 111:

/* Line 1806 of yacc.c  */
#line 469 "yaccC-TDS.y"
    {(yyval.at) = returnValue(lcode3d, Bool, (yyvsp[(1) - (1)].stringValue), (yyval.at));}
    break;

  case 112:

/* Line 1806 of yacc.c  */
#line 470 "yaccC-TDS.y"
    {(yyval.at) = getVariableAttribute(errorQ,&symbolTable,(yyvsp[(1) - (1)].stringValue));}
    break;

  case 113:

/* Line 1806 of yacc.c  */
#line 471 "yaccC-TDS.y"
    {(yyval.at) = checkArrayPos(errorQ,&symbolTable,(yyvsp[(1) - (4)].stringValue),(yyvsp[(3) - (4)].at));}
    break;

  case 114:

/* Line 1806 of yacc.c  */
#line 472 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(2) - (3)].at);}
    break;

  case 115:

/* Line 1806 of yacc.c  */
#line 473 "yaccC-TDS.y"
    {if (methodReturnType(errorQ,&symbolTable,lastCalledMethod) == RetVoid)
										{	insertError(errorQ,toString("El metodo \"",lastCalledMethod,"\" no puede ser usado en una expresion ya que retorna void."));
											(yyval.at) = createVariable("",Int); /* creamos variables int por defecto ------------------------------- */
										}
										else (yyval.at) = (yyvsp[(1) - (1)].at);
										lastCalledMethod=removeLastString(methodsIDStack);}
    break;



/* Line 1806 of yacc.c  */
#line 2462 "y.tab.c"
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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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



/* Line 2067 of yacc.c  */
#line 483 "yaccC-TDS.y"



