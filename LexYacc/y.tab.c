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
#  include  "../SymbolsTable/Utils.h"

extern FILE *yyin;
SymbolsTable symbolTable;   /* <----Definicion de la tabla de simbolos----- */
Attribute *auxAtr;          /* Atributo auxiliar usado para la creacion de nuevos atributos */           
unsigned char cantParams = 0;  /* Cantidad de parametros que tendra un metodo */
PrimitiveType vaType; /* Type of the variable or array */
ReturnType mType;     /* Return type of the method */

int yydebug = 1;

int yyerror (const char *str)
{
        fprintf(stderr,"Error gramatico en la linea:   %s\n", str); /* tratar de usar yylineno */
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
        printf("se parseo correctamente\n");
}

out(char *msg) {
        printf("%s\n", msg);
}




/* Line 268 of yacc.c  */
#line 124 "y.tab.c"

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
#line 54 "yaccC-TDS.y"

	/* ver si se puede hacer solamente asi, y sino agregar un atributo de tipo int y otro de tipo float ------------------ */
	char *stringValue;
	Attribute *at;



/* Line 293 of yacc.c  */
#line 224 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 236 "y.tab.c"

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
#define YYLAST   216

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNRULES -- Number of states.  */
#define YYNSTATES  181

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
      29,    34,    36,    40,    42,    47,    49,    51,    53,    54,
      60,    61,    68,    69,    75,    76,    83,    86,    87,    92,
      95,    96,   102,   105,   109,   112,   114,   116,   118,   121,
     123,   125,   128,   130,   131,   133,   135,   137,   140,   142,
     144,   148,   150,   152,   154,   162,   168,   172,   180,   182,
     187,   191,   192,   198,   205,   214,   216,   217,   222,   224,
     226,   228,   232,   234,   236,   238,   242,   244,   248,   250,
     254,   256,   260,   262,   266,   270,   274,   278,   280,   284,
     288,   292,   296,   300,   302,   305,   308,   310,   312,   314,
     316,   321,   325
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      47,     0,    -1,    24,     9,    36,    37,    -1,    -1,    -1,
      24,     9,    36,    48,    50,    49,    37,    -1,    51,    55,
      -1,    51,    -1,    55,    -1,    54,    52,    38,    -1,    51,
      54,    52,    38,    -1,    53,    -1,    52,    39,    53,    -1,
       9,    -1,     9,    40,     4,    41,    -1,     6,    -1,     7,
      -1,     8,    -1,    -1,    54,     9,    56,    60,    64,    -1,
      -1,    55,    54,     9,    57,    60,    64,    -1,    -1,    26,
       9,    58,    60,    64,    -1,    -1,    55,    26,     9,    59,
      60,    64,    -1,    42,    43,    -1,    -1,    42,    61,    62,
      43,    -1,    54,     9,    -1,    -1,    54,     9,    39,    63,
      62,    -1,    36,    37,    -1,    36,    65,    37,    -1,    51,
      66,    -1,    66,    -1,    51,    -1,    67,    -1,    66,    67,
      -1,    71,    -1,    72,    -1,    68,    38,    -1,    64,    -1,
      -1,    18,    -1,    20,    -1,    22,    -1,    22,    81,    -1,
      69,    -1,    74,    -1,    73,    70,    81,    -1,    44,    -1,
      10,    -1,    11,    -1,    19,    42,    81,    43,    64,    21,
      64,    -1,    19,    42,    81,    43,    64,    -1,    23,    81,
      64,    -1,    25,     9,    44,    81,    39,    81,    64,    -1,
       9,    -1,     9,    40,    86,    41,    -1,     9,    42,    43,
      -1,    -1,     9,    42,    75,    76,    43,    -1,    27,    42,
      28,    39,    78,    43,    -1,    27,    42,    28,    39,    78,
      39,    79,    43,    -1,    81,    -1,    -1,    76,    39,    77,
      81,    -1,    54,    -1,    26,    -1,    80,    -1,    79,    39,
      80,    -1,    81,    -1,    28,    -1,    82,    -1,    81,    16,
      82,    -1,    83,    -1,    82,    17,    83,    -1,    84,    -1,
      83,    13,    84,    -1,    85,    -1,    85,    12,    85,    -1,
      86,    -1,    86,    29,    86,    -1,    86,    30,    86,    -1,
      86,    14,    86,    -1,    86,    15,    86,    -1,    87,    -1,
      86,    31,    87,    -1,    86,    32,    87,    -1,    86,    35,
      87,    -1,    86,    34,    87,    -1,    86,    33,    87,    -1,
      88,    -1,    45,    87,    -1,    32,    87,    -1,     4,    -1,
       3,    -1,     5,    -1,     9,    -1,     9,    40,    86,    41,
      -1,    42,    81,    43,    -1,    74,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    81,    81,    82,    82,    82,    85,    86,    87,    90,
      91,    94,    95,    98,    99,   102,   103,   104,   107,   107,
     109,   109,   111,   111,   113,   113,   117,   118,   118,   121,
     123,   123,   127,   128,   131,   132,   133,   136,   137,   144,
     145,   146,   147,   150,   151,   152,   153,   154,   155,   156,
     159,   161,   162,   163,   170,   171,   174,   175,   182,   183,
     186,   203,   203,   218,   219,   222,   223,   223,   226,   227,
     230,   231,   234,   235,   238,   239,   242,   243,   246,   247,
     250,   251,   254,   255,   256,   257,   258,   261,   262,   263,
     264,   265,   266,   269,   270,   271,   274,   275,   276,   277,
     278,   279,   280
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
  "type", "method_decl", "$@3", "$@4", "$@5", "$@6", "param", "$@7",
  "parameters", "$@8", "block", "codeBlock", "statements", "statement",
  "action", "asignation", "assig_op", "conditional", "iteration",
  "location", "method_call", "$@9", "expression_aux", "$@10", "typevoid",
  "externinvk_arg", "arg", "expression", "conjunction", "inequality",
  "comparison", "relation", "term", "factor", "primary", 0
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
      51,    52,    52,    53,    53,    54,    54,    54,    56,    55,
      57,    55,    58,    55,    59,    55,    60,    61,    60,    62,
      63,    62,    64,    64,    65,    65,    65,    66,    66,    67,
      67,    67,    67,    68,    68,    68,    68,    68,    68,    68,
      69,    70,    70,    70,    71,    71,    72,    72,    73,    73,
      74,    75,    74,    74,    74,    76,    77,    76,    78,    78,
      79,    79,    80,    80,    81,    81,    82,    82,    83,    83,
      84,    84,    85,    85,    85,    85,    85,    86,    86,    86,
      86,    86,    86,    87,    87,    87,    88,    88,    88,    88,
      88,    88,    88
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     0,     0,     7,     2,     1,     1,     3,
       4,     1,     3,     1,     4,     1,     1,     1,     0,     5,
       0,     6,     0,     5,     0,     6,     2,     0,     4,     2,
       0,     5,     2,     3,     2,     1,     1,     1,     2,     1,
       1,     2,     1,     0,     1,     1,     1,     2,     1,     1,
       3,     1,     1,     1,     7,     5,     3,     7,     1,     4,
       3,     0,     5,     6,     8,     1,     0,     4,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       3,     3,     3,     1,     2,     2,     1,     1,     1,     1,
       4,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,     2,     0,    15,    16,
      17,     0,     4,     7,     0,     8,    22,     0,     0,     6,
      13,     0,    11,     0,     0,     0,     5,     0,     0,     0,
       9,     0,    24,    20,    27,     0,    10,     0,     0,    13,
      12,     0,     0,    26,     0,    43,    23,    14,    19,     0,
       0,     0,     0,    58,    44,     0,    45,    46,     0,     0,
       0,    32,    36,     0,    42,     0,    35,    37,     0,    48,
      39,    40,     0,    49,    25,    21,    29,    28,     0,    61,
       0,    97,    96,    98,    99,     0,     0,     0,   102,    47,
      74,    76,    78,    80,    82,    87,    93,     0,     0,     0,
       0,    34,    33,    38,    41,    52,    53,    51,     0,    30,
       0,    60,     0,     0,     0,    95,     0,    94,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    56,     0,     0,    50,     0,    59,     0,    65,     0,
       0,   101,    75,    77,    79,    81,    85,    86,    83,    84,
      88,    89,    92,    91,    90,     0,     0,    31,    66,    62,
      55,   100,     0,    69,    68,     0,     0,     0,     0,     0,
      63,    67,    54,    57,    73,     0,    70,    72,     0,    64,
      71
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     7,    17,    12,    13,    21,    22,    24,    15,
      29,    42,    25,    41,    35,    44,    52,   135,    64,    65,
      66,    67,    68,    69,   108,    70,    71,    72,    88,   112,
     137,   166,   165,   175,   176,   177,    90,    91,    92,    93,
      94,    95,    96
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -65
static const yytype_int16 yypact[] =
{
      30,    58,    84,    20,   -65,    41,   -65,    14,   -65,   -65,
     -65,    87,   -65,    14,    92,    26,   -65,    66,    92,    26,
       9,    75,   -65,    97,    99,    68,   -65,    78,   114,    68,
     -65,   111,   -65,   -65,    86,    85,   -65,    89,    85,    91,
     -65,    68,    68,   -65,    11,   139,   -65,   -65,   -65,    85,
      85,   118,    95,    22,   -65,    90,   -65,    77,    77,   132,
     101,   -65,   117,   111,   -65,   113,   159,   -65,   116,   -65,
     -65,   -65,     0,   -65,   -65,   -65,   112,   -65,    77,   109,
      77,   -65,   -65,   -65,    43,    77,    77,    77,   -65,   140,
     143,   150,   -65,   153,   158,   -65,   -65,     7,   123,   141,
     111,   159,   -65,   -65,   -65,   -65,   -65,   -65,    77,   -65,
      59,   -65,    77,    -8,    77,   -65,    -4,   -65,    77,    77,
      77,    77,    77,    77,    77,    77,    77,    77,    77,    77,
      77,   -65,    77,   131,   140,    11,   -65,   -15,   140,    85,
     167,   -65,   143,   150,   -65,   -65,   172,   172,   172,   172,
     -65,   -65,   -65,   -65,   -65,    -3,    40,   -65,   -65,   -65,
     162,   -65,    77,   -65,   -65,     2,    77,    85,     7,    70,
     -65,   140,   -65,   -65,   -65,    56,   -65,   140,    70,   -65,
     -65
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -65,   -65,   -65,   -65,   -65,   126,   -13,   149,    -7,   161,
     -65,   -65,   -65,   -65,    47,   -65,    50,   -65,   -34,   -65,
     134,   -59,   -65,   -65,   -65,   -65,   -65,   -65,   -36,   -65,
     -65,   -65,   -65,   -65,    16,   -55,    93,    94,    96,    88,
     -64,   -58,   -65
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -44
static const yytype_int16 yytable[] =
{
      14,    46,    89,    97,    48,    27,    18,   103,   118,    73,
     105,   106,   118,   118,   110,    74,    75,     8,     9,    10,
       8,     9,    10,   118,   158,   113,    73,   115,   159,   117,
      73,   116,     8,     9,    10,   139,   162,    51,    63,   141,
      11,   169,   103,    45,   107,   170,     8,     9,    10,    28,
     140,   -18,    23,   134,     1,   100,     5,   138,   146,   147,
     148,   149,    78,   131,    79,    73,   163,     3,   150,   151,
     152,   153,   154,    81,    82,    83,    38,   155,     6,    84,
      81,    82,    83,   114,     4,    79,    84,    27,    49,    50,
     126,   127,   128,   129,   130,   178,    16,    60,   174,   179,
     136,    20,    85,    26,    60,   160,    32,   168,    33,    85,
      34,   171,    86,    30,    31,    87,    36,    31,    37,    86,
      39,    45,    87,     8,     9,    10,    53,    76,    51,    43,
      47,    28,    80,   172,   173,    54,    55,    56,    77,    57,
      58,    98,    59,    99,    60,     8,     9,    10,    53,   164,
     102,   109,   111,    45,   104,   -43,   118,    54,    55,    56,
     119,    57,    58,   120,    59,   121,    60,   132,    53,   133,
     156,    62,   122,   123,    19,    45,    61,    54,    55,    56,
      40,    57,    58,   167,    59,   157,    60,   124,   125,   126,
     127,   128,   129,   130,   180,    45,   101,   -43,   126,   127,
     128,   129,   130,   126,   127,   128,   129,   130,   161,   145,
       0,   142,     0,   143,     0,     0,   144
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-65))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       7,    35,    57,    58,    38,    18,    13,    66,    16,    45,
      10,    11,    16,    16,    78,    49,    50,     6,     7,     8,
       6,     7,     8,    16,    39,    80,    62,    85,    43,    87,
      66,    86,     6,     7,     8,    43,    39,    44,    45,    43,
      26,    39,   101,    36,    44,    43,     6,     7,     8,    40,
     114,    42,    26,   108,    24,    62,    36,   112,   122,   123,
     124,   125,    40,    97,    42,   101,    26,     9,   126,   127,
     128,   129,   130,     3,     4,     5,    29,   132,    37,     9,
       3,     4,     5,    40,     0,    42,     9,   100,    41,    42,
      31,    32,    33,    34,    35,    39,     9,    27,    28,    43,
      41,     9,    32,    37,    27,   139,     9,   162,     9,    32,
      42,   166,    42,    38,    39,    45,    38,    39,     4,    42,
       9,    36,    45,     6,     7,     8,     9,     9,   135,    43,
      41,    40,    42,   167,   168,    18,    19,    20,    43,    22,
      23,     9,    25,    42,    27,     6,     7,     8,     9,   156,
      37,    39,    43,    36,    38,    38,    16,    18,    19,    20,
      17,    22,    23,    13,    25,    12,    27,    44,     9,    28,
      39,    45,    14,    15,    13,    36,    37,    18,    19,    20,
      31,    22,    23,    21,    25,   135,    27,    29,    30,    31,
      32,    33,    34,    35,   178,    36,    62,    38,    31,    32,
      33,    34,    35,    31,    32,    33,    34,    35,    41,   121,
      -1,   118,    -1,   119,    -1,    -1,   120
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    47,     9,     0,    36,    37,    48,     6,     7,
       8,    26,    50,    51,    54,    55,     9,    49,    54,    55,
       9,    52,    53,    26,    54,    58,    37,    52,    40,    56,
      38,    39,     9,     9,    42,    60,    38,     4,    60,     9,
      53,    59,    57,    43,    61,    36,    64,    41,    64,    60,
      60,    54,    62,     9,    18,    19,    20,    22,    23,    25,
      27,    37,    51,    54,    64,    65,    66,    67,    68,    69,
      71,    72,    73,    74,    64,    64,     9,    43,    40,    42,
      42,     3,     4,     5,     9,    32,    42,    45,    74,    81,
      82,    83,    84,    85,    86,    87,    88,    81,     9,    42,
      54,    66,    37,    67,    38,    10,    11,    44,    70,    39,
      86,    43,    75,    81,    40,    87,    81,    87,    16,    17,
      13,    12,    14,    15,    29,    30,    31,    32,    33,    34,
      35,    64,    44,    28,    81,    63,    41,    76,    81,    43,
      86,    43,    82,    83,    84,    85,    86,    86,    86,    86,
      87,    87,    87,    87,    87,    81,    39,    62,    39,    43,
      64,    41,    39,    26,    54,    78,    77,    21,    81,    39,
      43,    81,    64,    64,    28,    79,    80,    81,    39,    43,
      80
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
        case 3:

/* Line 1806 of yacc.c  */
#line 82 "yaccC-TDS.y"
    {initializeSymbolsTable(&symbolTable); pushLevel(&symbolTable);}
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 82 "yaccC-TDS.y"
    {popLevel(&symbolTable);}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 98 "yaccC-TDS.y"
    {pushElement(&symbolTable, createVariable((yyvsp[(1) - (1)].stringValue), vaType));}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 99 "yaccC-TDS.y"
    {pushElement(&symbolTable, createArray((yyvsp[(1) - (4)].stringValue), vaType, atoi((yyvsp[(3) - (4)].stringValue))));}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 102 "yaccC-TDS.y"
    {vaType = Int; mType = RetInt;}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 103 "yaccC-TDS.y"
    {vaType = Float; mType = RetFloat;}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 104 "yaccC-TDS.y"
    {vaType = Bool; mType = RetVoid;}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 107 "yaccC-TDS.y"
    {if (searchIdInSymbolsTable(&symbolTable, (yyvsp[(2) - (2)].stringValue)) == NULL) {Attribute *aux = createMethod((yyvsp[(2) - (2)].stringValue), mType, 0); pushElement(&symbolTable, aux); pushLevel(&symbolTable);}
							else printf("El identificador \"%s\" ya se encuentra definido.\n", (yyvsp[(2) - (2)].stringValue));}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 108 "yaccC-TDS.y"
    {popLevel(&symbolTable);}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 109 "yaccC-TDS.y"
    {if (searchIdInSymbolsTable(&symbolTable, (yyvsp[(3) - (3)].stringValue)) == NULL) {Attribute *aux = createMethod((yyvsp[(3) - (3)].stringValue), mType, 0); pushElement(&symbolTable, aux); pushLevel(&symbolTable);}
							else printf("El identificador \"%s\" ya se encuentra definido.\n", (yyvsp[(3) - (3)].stringValue));}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 110 "yaccC-TDS.y"
    {popLevel(&symbolTable);}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 111 "yaccC-TDS.y"
    {if (searchIdInSymbolsTable(&symbolTable, (yyvsp[(2) - (2)].stringValue)) == NULL) {Attribute *aux = createMethod((yyvsp[(2) - (2)].stringValue), RetVoid, 0); pushElement(&symbolTable, aux); pushLevel(&symbolTable);}
							else printf("El identificador \"%s\" ya se encuentra definido.\n", (yyvsp[(2) - (2)].stringValue));}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 112 "yaccC-TDS.y"
    {popLevel(&symbolTable);}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 113 "yaccC-TDS.y"
    {if (searchIdInSymbolsTable(&symbolTable, (yyvsp[(3) - (3)].stringValue)) == NULL) {Attribute *aux = createMethod((yyvsp[(3) - (3)].stringValue), RetVoid, 0); pushElement(&symbolTable, aux); pushLevel(&symbolTable);}
							else printf("El identificador \"%s\" ya se encuentra definido.\n", (yyvsp[(3) - (3)].stringValue));}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 114 "yaccC-TDS.y"
    {popLevel(&symbolTable);}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 117 "yaccC-TDS.y"
    {cantParams = 0;}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 118 "yaccC-TDS.y"
    {cantParams = 0;}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 121 "yaccC-TDS.y"
    {Attribute *aux = createParameter(lastDefinedMethod(&symbolTable),cantParams,(yyvsp[(2) - (2)].stringValue),vaType);
								if (aux != NULL) {pushElement(&symbolTable,aux); cantParams++;}}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 123 "yaccC-TDS.y"
    {Attribute *aux = createParameter(lastDefinedMethod(&symbolTable),cantParams,(yyvsp[(2) - (3)].stringValue),vaType);
								if (aux != NULL) {pushElement(&symbolTable,aux); cantParams++;}}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 182 "yaccC-TDS.y"
    {(yyval.at) = getVariableAttribute(&symbolTable, (yyvsp[(1) - (1)].stringValue));}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 183 "yaccC-TDS.y"
    {(yyval.at) = getArrayAttribute(&symbolTable, (yyvsp[(1) - (4)].stringValue), (*(yyvsp[(3) - (4)].at)).decl.variable.value.intVal);}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 186 "yaccC-TDS.y"
    { auxAtr = searchIdInSymbolsTable(&symbolTable, (yyvsp[(1) - (3)].stringValue));
                                    if(auxAtr == NULL) 
                                        printf("El metodo \"%s\" no esta definido.\n", (yyvsp[(1) - (3)].stringValue));
                                    else
                                    {
                                        if((*auxAtr).type != Method)
	                                        printf("El identificador \"%s\" no es un metodo.\n", (yyvsp[(1) - (3)].stringValue));
                                        else
                                        { 
                                            if ((*auxAtr).decl.method.paramSize > 0)
												if ((*auxAtr).decl.method.paramSize == 1)
													printf("El metodo \"%s\" no contiene su parametro correspondiente.\n", (yyvsp[(1) - (3)].stringValue));
												else
													printf("El metodo \"%s\" no contiene sus %d parametros correspondientes.\n", (yyvsp[(1) - (3)].stringValue), (*auxAtr).decl.method.paramSize);
                                        }
                                    }
                                }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 203 "yaccC-TDS.y"
    {cantParams=0;}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 203 "yaccC-TDS.y"
    { auxAtr = searchIdInSymbolsTable(&symbolTable, (yyvsp[(1) - (5)].stringValue));
                                                if(auxAtr == NULL) 
                                                    printf("El metodo \"%s\" no esta definido.\n", (yyvsp[(1) - (5)].stringValue));
                                                else
                                                {
                                                    if((*auxAtr).type != Method)
                                                    printf("El identificador \"%s\" no es un metodo.\n", (yyvsp[(1) - (5)].stringValue));
                                                    else
                                                    { 
                                                        if ((*auxAtr).decl.method.paramSize != cantParams)
                                                           printf("El metodo \"%s\" no tiene la misma cantidad de parametros.\n", (yyvsp[(1) - (5)].stringValue));
                                                    //bjdsabdjsadas
                                                    }
                                                }
                                            }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 218 "yaccC-TDS.y"
    {Attribute *at; (yyval.at) = at;}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 219 "yaccC-TDS.y"
    {Attribute *at; (yyval.at) = at;}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 222 "yaccC-TDS.y"
    {cantParams++;}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 223 "yaccC-TDS.y"
    {cantParams++;}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 238 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(1) - (1)].at);}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 239 "yaccC-TDS.y"
    {(yyval.at) = returnOr((yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at));}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 242 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(1) - (1)].at);}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 243 "yaccC-TDS.y"
    {(yyval.at) = returnAnd((yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at));}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 246 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(1) - (1)].at);}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 247 "yaccC-TDS.y"
    {(yyval.at) = returnDistinct((yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at));}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 250 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(1) - (1)].at);}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 251 "yaccC-TDS.y"
    {(yyval.at) = returnEqual((yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at));}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 254 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(1) - (1)].at);}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 255 "yaccC-TDS.y"
    {(yyval.at) = returnMinorComparison((yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at));}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 256 "yaccC-TDS.y"
    {(yyval.at) = returnMajorComparison((yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at));}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 257 "yaccC-TDS.y"
    {(yyval.at) = returnGEqualComparison((yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at));}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 258 "yaccC-TDS.y"
    {(yyval.at) = returnLEqualComparison((yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at));}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 261 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(1) - (1)].at);}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 262 "yaccC-TDS.y"
    {(yyval.at) = returnAdd((yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at));}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 263 "yaccC-TDS.y"
    {(yyval.at) = returnSub((yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at));}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 264 "yaccC-TDS.y"
    {(yyval.at) = returnMod((yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at));}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 265 "yaccC-TDS.y"
    {(yyval.at) = returnDiv((yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at));}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 266 "yaccC-TDS.y"
    {(yyval.at) = returnMult((yyvsp[(1) - (3)].at), (yyvsp[(3) - (3)].at));}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 269 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(1) - (1)].at);}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 270 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(2) - (2)].at);}
    break;

  case 95:

/* Line 1806 of yacc.c  */
#line 271 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(2) - (2)].at);}
    break;

  case 96:

/* Line 1806 of yacc.c  */
#line 274 "yaccC-TDS.y"
    {Attribute *aux = createVariable("", Int); setVariableValue(aux,Int,(yyvsp[(1) - (1)].stringValue)); (yyval.at)=aux;}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 275 "yaccC-TDS.y"
    {Attribute *aux = createVariable("", Float); setVariableValue(aux,Float,(yyvsp[(1) - (1)].stringValue)); (yyval.at)=aux;}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 276 "yaccC-TDS.y"
    {Attribute *aux = createVariable("", Bool); setVariableValue(aux,Bool,(yyvsp[(1) - (1)].stringValue)); (yyval.at)=aux;}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 277 "yaccC-TDS.y"
    {(yyval.at) = getVariableAttribute(&symbolTable, (yyvsp[(1) - (1)].stringValue));}
    break;

  case 100:

/* Line 1806 of yacc.c  */
#line 278 "yaccC-TDS.y"
    {(yyval.at) = getArrayAttribute(&symbolTable, (yyvsp[(1) - (4)].stringValue), (*(yyvsp[(3) - (4)].at)).decl.variable.value.intVal);/* aca deberiamos verificar que $3 es de tipo int en lugar de suponerlo?*/}
    break;

  case 101:

/* Line 1806 of yacc.c  */
#line 279 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(2) - (3)].at);}
    break;

  case 102:

/* Line 1806 of yacc.c  */
#line 280 "yaccC-TDS.y"
    {(yyval.at) = (yyvsp[(1) - (1)].at);}
    break;



/* Line 1806 of yacc.c  */
#line 2074 "y.tab.c"
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
#line 285 "yaccC-TDS.y"



