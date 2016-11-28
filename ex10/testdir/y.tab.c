/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "../tglc.y" /* yacc.c:339  */

using namespace std;

/*******************************************************************
  この次の行に，課題作成に参加したメンバ全員の学籍番号を記入すること．
  s1220091 国分佑太朗
  s1220228 海老原圭吾
  s1220233 小松凌也
  s1220244 向佐裕貴
 *******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <string>
#include "const.h"
#include "code.h"
#include "symtable.h"
#include "interpret.h"
#include "scanner.h"
#include "error.h"


// 関数のプロトタイプ宣言
template <typename Tnum>
static int allocateGlobalVar(VarEntry *var, Tnum val);
static void allocateArray(VarEntry *var);
static int allocateGlobalIntVar(int val);
static int allocateGlobalIntVar(double val);
static int allocateGlobalRealVar(int val);
static int allocateGlobalRealVar(double val);
static AssignTree *makeAssignTree(VarEntry *var,
                                  ExprTree *expr, ExprTree *index);
static ExprTree *makeBinExprTree(CConst op, ExprTree *lexp, ExprTree *rexp);
static RelationTree *makeRelationTree(CConst op, ExprTree *e1, ExprTree *e2);
static ExprTree *makeCallTree(string name, ArgList *params, ProcEntry *callee);
static LocalVarTree *initLocalVar(string name, Type vtype, ExprTree *expr);
static ReturnTree *makeDefaultReturnTree(Type type);
static ReturnTree *makeReturnTreeWithValue(ExprTree *val);
static void addParameters(ParamList *params);

/*
   静的変数
*/
static Code *compiled;	// main()の構文木

// 相続属性
VarEntry *var;          // vinit, localvinit の相続属性
static ProcEntry *proc; // localDeclList, localDecl, localvinit, body,
                        // stmt, stmtList, ifPart, elsePart の相続属性

#line 119 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INUM = 259,
    RNUM = 260,
    ADDOP = 261,
    MULOP = 262,
    RELOP = 263,
    LOGOP = 264,
    ULOGOP = 265,
    SIGNOP = 266,
    IF = 267,
    ELSIF = 268,
    ELSE = 269,
    WHILE = 270,
    REPEAT = 271,
    RETURN = 272,
    VOID = 273,
    INT = 274,
    REAL = 275
  };
#endif
/* Tokens.  */
#define ID 258
#define INUM 259
#define RNUM 260
#define ADDOP 261
#define MULOP 262
#define RELOP 263
#define LOGOP 264
#define ULOGOP 265
#define SIGNOP 266
#define IF 267
#define ELSIF 268
#define ELSE 269
#define WHILE 270
#define REPEAT 271
#define RETURN 272
#define VOID 273
#define INT 274
#define REAL 275

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 54 "../tglc.y" /* yacc.c:355  */

  CConst op;		// 演算子を表す定数
  string *symbol;	// 識別子名へのポインタ
  VarEntry *var;	// 変数エントリへのポインタ
  ProcEntry *proc;	// 手続きエントリへのポインタ
  STree *tree;		// 構文木へのポインタ
  ExprTree *expression;	// 式の構文木へのポインタ
  int inum;		// 整数
  double rnum;		// 実数
  Code *code;		// 中間コードへのポインタ
  CondList *condlist;	// 条件と文リストのペアの列
  CondTree *condition;	// 条件の構文木へのポインタ
  Type type;		// 変数、手続きの型
  ParamType *param;	// 引数
  ParamList *params;	// 引数リストへのポインタ
  ArgList *args;	// 実引数リストへのポインタ
  int loc;		// 番地

#line 218 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 235 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   183

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  152

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   275

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      24,    25,     2,     2,    29,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    21,
       2,    26,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    22,     2,    23,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    27,     2,    28,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   105,   105,   109,   111,   118,   117,   122,   124,   130,
     131,   133,   139,   140,   145,   146,   151,   152,   153,   157,
     158,   164,   163,   170,   172,   177,   178,   183,   184,   190,
     195,   197,   203,   202,   210,   211,   217,   218,   231,   230,
     241,   249,   240,   257,   258,   260,   259,   267,   267,   270,
     272,   279,   282,   288,   289,   297,   298,   299,   300,   301,
     307,   306,   317,   318,   320,   319,   327,   332,   333,   338,
     339,   344,   345,   346,   347
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INUM", "RNUM", "ADDOP", "MULOP",
  "RELOP", "LOGOP", "ULOGOP", "SIGNOP", "IF", "ELSIF", "ELSE", "WHILE",
  "REPEAT", "RETURN", "VOID", "INT", "REAL", "';'", "'['", "']'", "'('",
  "')'", "'='", "'{'", "'}'", "','", "$accept", "program", "declPart",
  "decl", "@1", "vinit", "iconst", "rconst", "type", "defPart", "procDef",
  "$@2", "body", "formalParamList", "formalParamList2", "formalParam",
  "localDeclList", "localDecl", "$@3", "localvinit", "stmtList", "stmt",
  "$@4", "$@5", "$@6", "$@7", "$@8", "ifPart", "elsePart", "expr", "$@9",
  "$@10", "vname", "argList", "argList2", "cond", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,    59,    91,    93,    40,    41,    61,   123,   125,    44
};
# endif

#define YYPACT_NINF -107

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-107)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -107,    12,   131,  -107,  -107,  -107,  -107,  -107,    22,   131,
    -107,   -19,    31,  -107,    11,   131,    30,    25,    47,    74,
      60,    66,  -107,   148,    79,   131,   107,  -107,    -4,   131,
    -107,  -107,    40,  -107,  -107,  -107,    72,  -107,  -107,  -107,
    -107,  -107,  -107,   109,  -107,   131,   136,    38,  -107,  -107,
     110,   119,   137,   138,   114,  -107,  -107,    61,   122,   120,
    -107,     3,     3,    77,   139,  -107,  -107,    77,  -107,    77,
     116,   142,   141,   133,  -107,  -107,  -107,    77,   145,    77,
       3,     3,   149,    13,    53,    33,  -107,  -107,   100,    77,
      77,  -107,  -107,     3,  -107,    77,    77,   152,  -107,   152,
     143,   112,  -107,    23,   115,    77,     3,   140,   144,  -107,
      77,  -107,   162,  -107,    77,   117,    48,    80,   124,   151,
      77,  -107,   152,  -107,  -107,  -107,   146,   150,   106,   147,
    -107,  -107,  -107,  -107,  -107,   152,    56,    76,  -107,  -107,
    -107,  -107,   153,  -107,  -107,    93,    99,    77,  -107,  -107,
     126,  -107
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,    18,    16,    17,     4,     0,     2,
      19,     5,     0,    20,     0,    25,     9,     0,     0,     0,
       0,    26,    27,     0,     0,    25,     0,    29,     0,     0,
      12,    14,     0,    10,    11,     6,     0,     7,     8,    21,
      28,    13,    15,     0,    30,    23,     0,     0,    31,    32,
      66,     0,     0,     0,     0,    22,    24,    53,     0,    34,
      47,     0,     0,     0,    66,    62,    63,     0,    49,     0,
       0,    59,     0,     0,    43,    40,    38,     0,     0,    67,
       0,     0,     0,     0,     0,     0,    64,    57,     0,     0,
       0,    50,    60,     0,    36,     0,     0,    35,    33,    69,
       0,    68,    72,     0,     0,     0,     0,     0,     0,    45,
      67,    58,    55,    56,     0,     0,     0,     0,     0,     0,
       0,    74,    73,    71,    36,    36,     0,     0,     0,     0,
      54,    37,    41,    39,    48,    70,     0,     0,    36,    65,
      61,    36,     0,    51,    44,     0,     0,     0,    46,    52,
       0,    42
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -107,  -107,  -107,  -107,  -107,  -107,  -107,  -107,     2,  -107,
     161,  -107,  -107,   155,  -107,   154,  -107,  -107,  -107,  -107,
    -106,   129,  -107,  -107,  -107,  -107,  -107,  -107,  -107,   -53,
    -107,  -107,   -47,    67,  -107,   -60
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,    16,    24,    33,    34,    19,     9,
      10,    44,    47,    20,    21,    22,    45,    48,    59,    78,
     116,   131,    96,    95,   142,   126,    79,    57,    74,    82,
     114,   110,    71,   100,   101,    83
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      58,    70,    84,    14,     8,    15,    64,    65,    66,    67,
      85,    12,     3,    80,    87,    18,    88,    38,   136,   137,
     102,   104,   106,    39,    97,    11,    99,    81,   103,    89,
      90,   105,   145,   115,    17,   146,   112,   113,   107,    89,
      90,    50,   117,   118,    41,    42,   123,    46,   111,    25,
      51,    50,   122,    52,    53,    54,    23,    99,   109,    50,
      51,   128,   106,    52,    53,    54,    55,   135,    51,    58,
      26,    52,    53,    54,    72,    73,   130,    27,   108,    50,
      64,    65,    66,    67,   143,    28,    89,    90,    51,    58,
      58,    52,    53,    54,   150,    29,    50,    43,    58,    58,
      35,    69,    50,   132,   144,    51,    89,    90,    52,    53,
      54,    51,    89,    90,    52,    53,    54,    64,    65,    66,
      67,   148,    89,    90,   106,   111,   106,   149,    37,   140,
      89,    90,    89,    90,    60,    68,    39,    91,    69,    49,
     121,   120,   129,    61,    75,   133,    77,   151,    76,     4,
       5,     6,    30,    31,    32,    89,    90,   105,    89,    90,
      94,    62,    63,    86,    92,    93,    98,   124,   119,    90,
      13,   125,   134,   138,   141,   139,    56,   127,     0,   147,
      36,     0,     0,    40
};

static const yytype_int16 yycheck[] =
{
      47,    54,    62,    22,     2,    24,     3,     4,     5,     6,
      63,     9,     0,    10,    67,     4,    69,    21,   124,   125,
      80,    81,     9,    27,    77,     3,    79,    24,    81,     6,
       7,     8,   138,    93,     3,   141,    89,    90,    25,     6,
       7,     3,    95,    96,     4,     5,   106,    45,    25,    24,
      12,     3,   105,    15,    16,    17,    26,   110,    25,     3,
      12,   114,     9,    15,    16,    17,    28,   120,    12,   116,
      23,    15,    16,    17,    13,    14,    28,     3,    25,     3,
       3,     4,     5,     6,    28,    25,     6,     7,    12,   136,
     137,    15,    16,    17,   147,    29,     3,    25,   145,   146,
      21,    24,     3,    23,    28,    12,     6,     7,    15,    16,
      17,    12,     6,     7,    15,    16,    17,     3,     4,     5,
       6,    28,     6,     7,     9,    25,     9,    28,    21,    23,
       6,     7,     6,     7,    24,    21,    27,    21,    24,     3,
      25,    29,    25,    24,    22,    21,    26,    21,    26,    18,
      19,    20,     4,     5,     6,     6,     7,     8,     6,     7,
      27,    24,    24,    24,    22,    24,    21,    27,    25,     7,
       9,    27,    21,    27,    27,    25,    47,   110,    -1,    26,
      25,    -1,    -1,    29
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    31,    32,     0,    18,    19,    20,    33,    38,    39,
      40,     3,    38,    40,    22,    24,    34,     3,     4,    38,
      43,    44,    45,    26,    35,    24,    23,     3,    25,    29,
       4,     5,     6,    36,    37,    21,    43,    21,    21,    27,
      45,     4,     5,    25,    41,    46,    38,    42,    47,     3,
       3,    12,    15,    16,    17,    28,    51,    57,    62,    48,
      24,    24,    24,    24,     3,     4,     5,     6,    21,    24,
      59,    62,    13,    14,    58,    22,    26,    26,    49,    56,
      10,    24,    59,    65,    65,    59,    24,    59,    59,     6,
       7,    21,    22,    24,    27,    53,    52,    59,    21,    59,
      63,    64,    65,    59,    65,     8,     9,    25,    25,    25,
      61,    25,    59,    59,    60,    65,    50,    59,    59,    25,
      29,    25,    59,    65,    27,    27,    55,    63,    59,    25,
      28,    51,    23,    21,    21,    59,    50,    50,    27,    25,
      23,    27,    54,    28,    28,    50,    50,    26,    28,    28,
      59,    21
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    30,    31,    32,    32,    34,    33,    33,    33,    35,
      35,    35,    36,    36,    37,    37,    38,    38,    38,    39,
      39,    41,    40,    42,    42,    43,    43,    44,    44,    45,
      46,    46,    48,    47,    49,    49,    50,    50,    52,    51,
      53,    54,    51,    51,    51,    55,    51,    56,    51,    51,
      51,    57,    57,    58,    58,    59,    59,    59,    59,    59,
      60,    59,    59,    59,    61,    59,    62,    63,    63,    64,
      64,    65,    65,    65,    65
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     2,     0,     5,     6,     6,     0,
       2,     2,     1,     2,     1,     2,     1,     1,     1,     1,
       2,     0,    10,     0,     2,     0,     1,     1,     3,     2,
       0,     2,     0,     5,     0,     2,     0,     2,     0,     5,
       0,     0,     9,     2,     7,     0,     8,     0,     6,     2,
       3,     7,     8,     0,     4,     3,     3,     2,     3,     1,
       0,     5,     1,     1,     0,     5,     1,     0,     1,     1,
       3,     3,     2,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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
      yychar = yylex ();
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
     '$$ = $1'.

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
#line 105 "../tglc.y" /* yacc.c:1646  */
    { checkProgram(); compiled = getMainCode(); }
#line 1419 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 118 "../tglc.y" /* yacc.c:1646  */
    { (yyval.var) = addGlobalVariable(*(yyvsp[0].symbol),(yyvsp[-1].type)); var = (yyval.var); }
#line 1425 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 120 "../tglc.y" /* yacc.c:1646  */
    { (yyvsp[-2].var)->setLocation((yyvsp[-1].loc)); registerVariable((yyvsp[-2].var));
        delete (yyvsp[-3].symbol); }
#line 1432 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 123 "../tglc.y" /* yacc.c:1646  */
    { allocateArray(addArray(*(yyvsp[-4].symbol),(yyvsp[-5].type),(yyvsp[-2].inum))); delete (yyvsp[-4].symbol); }
#line 1438 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 125 "../tglc.y" /* yacc.c:1646  */
    { addProcedure(*(yyvsp[-4].symbol),(yyvsp[-5].type),(yyvsp[-2].params)); delete (yyvsp[-4].symbol); }
#line 1444 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 130 "../tglc.y" /* yacc.c:1646  */
    { (yyval.loc) = allocateGlobalVar(var,0); }
#line 1450 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 132 "../tglc.y" /* yacc.c:1646  */
    { (yyval.loc) = allocateGlobalVar(var,(yyvsp[0].inum)); }
#line 1456 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 134 "../tglc.y" /* yacc.c:1646  */
    { (yyval.loc) = allocateGlobalVar(var,(yyvsp[0].rnum)); }
#line 1462 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 139 "../tglc.y" /* yacc.c:1646  */
    { (yyval.inum) = (yyvsp[0].inum); }
#line 1468 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 140 "../tglc.y" /* yacc.c:1646  */
    { (yyval.inum) = (yyvsp[-1].op) == Cadd ?  (yyvsp[0].inum) : -(yyvsp[0].inum); }
#line 1474 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 145 "../tglc.y" /* yacc.c:1646  */
    { (yyval.rnum) = (yyvsp[0].rnum); }
#line 1480 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 146 "../tglc.y" /* yacc.c:1646  */
    { (yyval.rnum) = (yyvsp[-1].op) == Cadd ?  (yyvsp[0].rnum) : -(yyvsp[0].rnum); }
#line 1486 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 151 "../tglc.y" /* yacc.c:1646  */
    { (yyval.type) = TInt; }
#line 1492 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 152 "../tglc.y" /* yacc.c:1646  */
    { (yyval.type) = TReal; }
#line 1498 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 153 "../tglc.y" /* yacc.c:1646  */
    { }
#line 1504 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 164 "../tglc.y" /* yacc.c:1646  */
    { }
#line 1510 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 166 "../tglc.y" /* yacc.c:1646  */
    { }
#line 1516 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 172 "../tglc.y" /* yacc.c:1646  */
    { proc->push_back((yyvsp[0].tree)); }
#line 1522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 177 "../tglc.y" /* yacc.c:1646  */
    { (yyval.params) = NULL; }
#line 1528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 183 "../tglc.y" /* yacc.c:1646  */
    { (yyval.params) = new ParamList; (yyval.params)->push_back(*(yyvsp[0].param)); delete (yyvsp[0].param); }
#line 1534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 185 "../tglc.y" /* yacc.c:1646  */
    { (yyval.params) = (yyvsp[-2].params); (yyval.params)->push_back(*(yyvsp[0].param)); delete (yyvsp[0].param); }
#line 1540 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 191 "../tglc.y" /* yacc.c:1646  */
    { }
#line 1546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 203 "../tglc.y" /* yacc.c:1646  */
    { }
#line 1552 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 204 "../tglc.y" /* yacc.c:1646  */
    { delete (yyvsp[-3].symbol); }
#line 1558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 210 "../tglc.y" /* yacc.c:1646  */
    { proc->push_back(new LocalVarTree(var->getName(),var->getType(),NULL)); }
#line 1564 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 212 "../tglc.y" /* yacc.c:1646  */
    { proc->push_back(initLocalVar(var->getName(),var->getType(),(yyvsp[0].expression))); }
#line 1570 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 217 "../tglc.y" /* yacc.c:1646  */
    { (yyval.code) = new Code; }
#line 1576 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 218 "../tglc.y" /* yacc.c:1646  */
    { (yyvsp[-1].code)->push_back((yyvsp[0].tree)); (yyval.code) = (yyvsp[-1].code); }
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 231 "../tglc.y" /* yacc.c:1646  */
    {
      //vnameが配列である場合は単純変数ではないのでコンパイルエラーを出す
      if( (yyvsp[-1].var)->isArray() == true ) {
      string name = (yyvsp[-1].var)->getName();
        compileError(EDeclaredAsArray, name.c_str(), name.c_str());
      }
      }
#line 1594 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 239 "../tglc.y" /* yacc.c:1646  */
    { (yyval.tree) = makeAssignTree((yyvsp[-4].var), (yyvsp[-1].expression), NULL); /* 代入文の構文木を生成し合成属性に代入する */}
#line 1600 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 241 "../tglc.y" /* yacc.c:1646  */
    {
      //vnameが単純変数である場合は配列ではないのでコンパイルエラーを出す
      if( (yyvsp[-1].var)->isArray() == false) {
        string name = (yyvsp[-1].var)->getName();
        compileError(EDeclaredAsSimpleVar, name.c_str(), name.c_str());
      }
      }
#line 1612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 249 "../tglc.y" /* yacc.c:1646  */
    {
      //配列の添字exprはInt型である必要があるので、違う場合にはコンパイルエラーを出す
      if( (yyvsp[-1].expression)->getType() != TInt ){
        compileError(EIndexTypeMismatch, (yyvsp[-4].var)->getName().c_str(), (yyvsp[-4].var)->getName().c_str());
      }
      }
#line 1623 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 256 "../tglc.y" /* yacc.c:1646  */
    { (yyval.tree) = makeAssignTree((yyvsp[-8].var), (yyvsp[-1].expression), (yyvsp[-5].expression)); /* 代入文の構文木を生成し合成属性に代入する*/ }
#line 1629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 257 "../tglc.y" /* yacc.c:1646  */
    { (yyval.tree) = new IfTree((yyvsp[-1].condlist),(yyvsp[0].code)); }
#line 1635 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 258 "../tglc.y" /* yacc.c:1646  */
    { (yyval.tree) = new WhileTree((yyvsp[-4].condition),(yyvsp[-1].code)); }
#line 1641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 260 "../tglc.y" /* yacc.c:1646  */
    {
      //repeat構文はIntで回数を指定するので、型が違う場合にはコンパイルエラーを出す
      if( (yyvsp[-1].expression)->getType() != TInt ){
        compileError(ERepeatTypeMismatch);
      }
      }
#line 1652 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 266 "../tglc.y" /* yacc.c:1646  */
    { (yyval.tree) = new RepeatTree((yyvsp[-5].expression),(yyvsp[-1].code)); }
#line 1658 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 267 "../tglc.y" /* yacc.c:1646  */
    { }
#line 1664 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 269 "../tglc.y" /* yacc.c:1646  */
    { }
#line 1670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 271 "../tglc.y" /* yacc.c:1646  */
    { }
#line 1676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 273 "../tglc.y" /* yacc.c:1646  */
    { }
#line 1682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 280 "../tglc.y" /* yacc.c:1646  */
    { (yyval.condlist) = new CondList;
        (yyval.condlist)->push_back(make_pair((yyvsp[-4].condition),(yyvsp[-1].code))); }
#line 1689 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 283 "../tglc.y" /* yacc.c:1646  */
    { (yyval.condlist)->push_back(make_pair((yyvsp[-4].condition),(yyvsp[-1].code))); }
#line 1695 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 288 "../tglc.y" /* yacc.c:1646  */
    { (yyval.code) = NULL; }
#line 1701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 289 "../tglc.y" /* yacc.c:1646  */
    { (yyval.code) = (yyvsp[-1].code); }
#line 1707 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 297 "../tglc.y" /* yacc.c:1646  */
    { (yyval.expression) = makeBinExprTree((yyvsp[-1].op),(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 1713 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 298 "../tglc.y" /* yacc.c:1646  */
    { (yyval.expression) = makeBinExprTree((yyvsp[-1].op),(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 1719 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 299 "../tglc.y" /* yacc.c:1646  */
    { (yyval.expression) = new UniExprTree((yyvsp[-1].op),(yyvsp[0].expression)); }
#line 1725 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 300 "../tglc.y" /* yacc.c:1646  */
    { (yyval.expression) = (yyvsp[-1].expression); }
#line 1731 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 302 "../tglc.y" /* yacc.c:1646  */
    { if((yyvsp[0].var)->isArray() == true){//意味規則を満たさないとき
    compileError(EDeclaredAsArray, (yyvsp[0].var)->getName().c_str());
  } else (yyval.expression) = new SmplVarNode((yyvsp[0].var)->getName(),(yyvsp[0].var)->getLocation(),(yyvsp[0].var)->getType()); //単純変数の構文木を生成する
}
#line 1740 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 307 "../tglc.y" /* yacc.c:1646  */
    { if((yyvsp[-1].var)->isArray() != true){//意味規則を満たさないとき
    compileError(EDeclaredAsSimpleVar, (yyvsp[-1].var)->getName().c_str());
  }
}
#line 1749 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 312 "../tglc.y" /* yacc.c:1646  */
    { if((yyvsp[-1].expression)->getType() != TInt){
    compileError(EIndexTypeMismatch, (yyvsp[-4].var)->getName().c_str());
  }
  else (yyval.expression) = new ArrayElemTree((yyvsp[-4].var)->getName(), (yyvsp[-4].var)->getLocation(), (yyvsp[-4].var)->getType(), (yyvsp[-1].expression), (yyvsp[-4].var)->getArraySize()); //配列要素の構文木を生成する
  }
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 317 "../tglc.y" /* yacc.c:1646  */
    { (yyval.expression) = new INumNode((yyvsp[0].inum)); }
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 318 "../tglc.y" /* yacc.c:1646  */
    { (yyval.expression) = new RNumNode((yyvsp[0].rnum)); }
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 320 "../tglc.y" /* yacc.c:1646  */
    { }
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 322 "../tglc.y" /* yacc.c:1646  */
    { }
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 327 "../tglc.y" /* yacc.c:1646  */
    { (yyval.var) = findVariable(*(yyvsp[0].symbol)); }
#line 1789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 332 "../tglc.y" /* yacc.c:1646  */
    { (yyval.args) = NULL; }
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 333 "../tglc.y" /* yacc.c:1646  */
    { (yyval.args) = (yyvsp[0].args); }
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 338 "../tglc.y" /* yacc.c:1646  */
    { (yyval.args) = new ArgList; (yyval.args)->push_back((yyvsp[0].expression)); }
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 339 "../tglc.y" /* yacc.c:1646  */
    { (yyval.args) = (yyvsp[-2].args); (yyval.args)->push_back((yyvsp[0].expression)); }
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 344 "../tglc.y" /* yacc.c:1646  */
    { (yyval.condition) = new BinCondTree((yyvsp[-1].op),(yyvsp[-2].condition),(yyvsp[0].condition)); }
#line 1819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 345 "../tglc.y" /* yacc.c:1646  */
    { (yyval.condition) = new UniCondTree((yyvsp[-1].op),(yyvsp[0].condition)); }
#line 1825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 346 "../tglc.y" /* yacc.c:1646  */
    { (yyval.condition) = makeRelationTree((yyvsp[-1].op),(yyvsp[-2].expression),(yyvsp[0].expression)); }
#line 1831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 347 "../tglc.y" /* yacc.c:1646  */
    { (yyval.condition) = (yyvsp[-1].condition); }
#line 1837 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1841 "y.tab.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 350 "../tglc.y" /* yacc.c:1906  */


template <typename Tnum>
static int allocateGlobalVar(VarEntry *var, Tnum val)
{
  switch (var->getType())  {
  case TInt:
    return allocateGlobalIntVar(val);
  case TReal:
    return allocateGlobalRealVar(val);
  default:
    compileError(EVoidVariable,var->getName().c_str());
  }
}

static int allocateGlobalIntVar(int val)
{
  return allocateMemory(val);
}

static int allocateGlobalIntVar(double val)
{
  return allocateMemory((int)val);
}

static int allocateGlobalRealVar(int val)
{
  return allocateMemory((double)val);
}

static int allocateGlobalRealVar(double val)
{
  return allocateMemory(val);
}

static void allocateArray(VarEntry *var)
{
  Type type = var->getType();
  int size = var->getArraySize();
  if (type == TVoid)
    compileError(EVoidVariable,var->getName().c_str());
  else  {
    if (size == 0)
      compileError(EIllegalSize,var->getName().c_str());
    var->setLocation(allocateGlobalVar(var,0));
    for (int i=1; i<size; i++)
      allocateGlobalVar(var,0);
    registerVariable(var);
  }
}

static AssignTree *makeAssignTree(VarEntry *var,
                                  ExprTree *expr, ExprTree *index)
{
  int loc = var->getLocation();
  string name = var->getName();
  Type type = var->getType();

  Variable *vtree;
  if(index == NULL) {
  // 単純変数の構文木を作る
  vtree = new SmplVarNode(name, loc, type);

  } else {
  // 配列要素の構文木を作る
  int size = var->getArraySize();
  vtree = new ArrayElemTree(name, loc, type, index, size);
  }

 // 型変換を行う
 Type ltype = var->getType();
 Type rtype = expr->getType();


 // 型変換の必要がある場合
 if (ltype != rtype) {

    // 右の構文木をTInt型に変換する
    if (ltype == TInt && rtype == TReal) {
        expr = new UniExprTree(Creal2int, expr, ltype);
    }

    // 右の構文木をTReal型に変換する
    else if (ltype == TReal && rtype == TInt) {
        expr = new UniExprTree(Cint2real, expr, ltype);
    }
 }


 // 代入木の構文期を作成し，返却する
 AssignTree *tree = new AssignTree(vtree, expr);
 return tree;
}




static ExprTree *makeBinExprTree(CConst op, ExprTree *lexp, ExprTree *rexp)
{
 // 型変換を行う
 Type ltype = lexp->getType();
 Type rtype = rexp->getType();
 // 型変換の必要がある場合
 if (ltype != rtype) {
    
    // 左の構文木をTReal型に変換する
    if (ltype == TInt && rtype == TReal) {
        lexp = new UniExprTree(Cint2real, lexp, TReal);
    }

    // 右の構文木をTReal型に変換する
    else if (ltype == TReal && rtype == TInt) {
        rexp = new UniExprTree(Cint2real, rexp, TReal);
    }
  }

 // 二項演算子をもつ式の構文木を生成し，返却する．
 BinExprTree *btree = new BinExprTree(op, lexp, rexp);
 return btree;

}

static RelationTree *makeRelationTree(CConst op, ExprTree *e1, ExprTree *e2)
{
 // 型変換を行う
 Type ltype = e1->getType();
 Type rtype = e2->getType();
 // 型変換の必要がある場合
 if (ltype != rtype) {
    
    // 左の構文木をTReal型に変換する
    if (ltype == TInt && rtype == TReal) {
        e1 = new UniExprTree(Cint2real, e1, TReal);
    }

    // 右の構文木をTReal型に変換する
    else if (ltype == TReal && rtype == TInt) {
        e2 = new UniExprTree(Cint2real, e2, TReal);
    }
  }

 // 関係演算子をもつ条件を構文木を作成し，返却する
 RelationTree *rtree = new RelationTree(op, e1, e2);
 return rtree;

}

static ExprTree *makeCallTree(string name, ArgList *args, ProcEntry *callee)
{

}

static LocalVarTree *initLocalVar(string name, Type vtype, ExprTree *expr)
{

}

static ReturnTree *makeDefaultReturnTree(Type type)
{
  ReturnTree *tree;
  int num = proc->getParamNumber();
  switch (type)  {
  case TInt:
    tree = new ReturnTree(new INumNode(0), num);
    break;
  case TReal:
    tree = new ReturnTree(new RNumNode(0), num);
    break;
  default:  // TVoid
    tree = new ReturnTree(NULL, num);
  }
  return tree;
}

static ReturnTree *makeReturnTreeWithValue(ExprTree *val)
{

}

static void addParameters(ParamList *params)
{//仮引数リストが空か調べる
  if(!params->empty()){
    //VarEntry var = new VarEntry(Param,params,params->getType(),true,params->size());
       
    //先頭から順に仮引数の型と仮引数名を取り出し記号表に登録
    for(vector<ParamType>::iterator it = params->begin(); it != params->end(); it++ ){
      addParameter(it->second, it->first);//addParameter(string name, Type type)
    }
  }
}

void usage(char *cmd)
{
  fprintf(stderr,"利用法: %s 原始プログラムファイル名\n",cmd);
  exit(2);
}

main(int argc, char **argv)
{
#if YYDEBUG
  extern int yydebug;

yydebug = 1;	/* デバッグ表示付きの構文解析系を生成したいとき 1 を代入 */
#endif

/* list が true なら，コンパイル後実行せず
     構文木から再現された原始プログラムを表示する */
  bool list = false;
  bool trace = false;
  char *cmd = *argv;	// コンパイラのコマンド名

if (argc < 2)
    usage(cmd);

/* 最初の引数がオプションか？ */
  while (**++argv == '-')  {
    argc--;
    switch (*(*argv+1))  {
    case 'l':
      if (!trace)
        list = true;
      break;
    case 't':
      if (!list)  {
        setTrace();
        trace = true;
      }
      break;
    case 's':
      setSpeed(atoi(*argv+2));
      break;
    default:
      printf("無効なオプション -%s\n",*argv);
    }
  }
  if (argc <= 0)
    usage(cmd);

#if YYDEBUG
  yydebug = 1;	/* デバッグ表示付きの構文解析系を生成したいとき 1 を代入 */
#endif

setFileName(*argv);
  initializeScanner(*argv);
  initializeSymbolTable();
  addSystemProcedures();
  yyparse();
  if (list == 1)
    printCode(compiled);
  else
    interpret(compiled);
}
