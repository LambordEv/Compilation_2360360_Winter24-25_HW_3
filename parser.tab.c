/* A Bison parser, made by GNU Bison 3.7.6.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30706

/* Bison version string.  */
#define YYBISON_VERSION "3.7.6"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"


#include <iostream>
#include "nodes.hpp"
#include "output.hpp"
#include "visitor.hpp"

// bison declarations
extern int yylineno;
extern char* yytext;
extern int yylex();

using namespace std;
using namespace ast;

void yyerror(const char*);
static RelOpType whatRelOpRecieved(string);
static BinOpType whatBinOpRecieved(string);
static BuiltInType whatTypeReceived(string);

// root of the AST, set by the parser and used by other parts of the compiler
shared_ptr<Node> program;

// TODO: Place any additional declarations here

#line 97 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_ID = 3,                       /* T_ID  */
  YYSYMBOL_T_STRING = 4,                   /* T_STRING  */
  YYSYMBOL_T_NUM = 5,                      /* T_NUM  */
  YYSYMBOL_T_NUM_B = 6,                    /* T_NUM_B  */
  YYSYMBOL_T_COMMA = 7,                    /* T_COMMA  */
  YYSYMBOL_T_SC = 8,                       /* T_SC  */
  YYSYMBOL_T_CONTINUE = 9,                 /* T_CONTINUE  */
  YYSYMBOL_T_BREAK = 10,                   /* T_BREAK  */
  YYSYMBOL_T_WHILE = 11,                   /* T_WHILE  */
  YYSYMBOL_T_IF = 12,                      /* T_IF  */
  YYSYMBOL_T_RETURN = 13,                  /* T_RETURN  */
  YYSYMBOL_T_FALSE = 14,                   /* T_FALSE  */
  YYSYMBOL_T_TRUE = 15,                    /* T_TRUE  */
  YYSYMBOL_T_BOOL = 16,                    /* T_BOOL  */
  YYSYMBOL_T_BYTE = 17,                    /* T_BYTE  */
  YYSYMBOL_T_INT = 18,                     /* T_INT  */
  YYSYMBOL_T_VOID = 19,                    /* T_VOID  */
  YYSYMBOL_T_ASSIGN = 20,                  /* T_ASSIGN  */
  YYSYMBOL_T_OR = 21,                      /* T_OR  */
  YYSYMBOL_T_AND = 22,                     /* T_AND  */
  YYSYMBOL_T_RELOP = 23,                   /* T_RELOP  */
  YYSYMBOL_T_ADD_SUB = 24,                 /* T_ADD_SUB  */
  YYSYMBOL_T_MUL_DIV = 25,                 /* T_MUL_DIV  */
  YYSYMBOL_T_NOT = 26,                     /* T_NOT  */
  YYSYMBOL_T_LPAREN = 27,                  /* T_LPAREN  */
  YYSYMBOL_T_RPAREN = 28,                  /* T_RPAREN  */
  YYSYMBOL_T_LBRACE = 29,                  /* T_LBRACE  */
  YYSYMBOL_T_RBRACE = 30,                  /* T_RBRACE  */
  YYSYMBOL_T_ELSE = 31,                    /* T_ELSE  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_Program = 33,                   /* Program  */
  YYSYMBOL_Funcs = 34,                     /* Funcs  */
  YYSYMBOL_FuncDecl = 35,                  /* FuncDecl  */
  YYSYMBOL_RetType = 36,                   /* RetType  */
  YYSYMBOL_Formals = 37,                   /* Formals  */
  YYSYMBOL_FormalsList = 38,               /* FormalsList  */
  YYSYMBOL_FormalDecl = 39,                /* FormalDecl  */
  YYSYMBOL_Statements = 40,                /* Statements  */
  YYSYMBOL_Statement = 41,                 /* Statement  */
  YYSYMBOL_Call = 42,                      /* Call  */
  YYSYMBOL_ExpList = 43,                   /* ExpList  */
  YYSYMBOL_Type = 44,                      /* Type  */
  YYSYMBOL_Exp = 45                        /* Exp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   205

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  48
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  94

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    65,    65,    68,    69,    78,    87,    88,    90,    91,
      93,    94,   102,   109,   110,   118,   119,   125,   132,   138,
     139,   140,   141,   147,   154,   160,   161,   163,   169,   171,
     172,   180,   181,   182,   184,   185,   193,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   215,   221,   229
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "T_ID", "T_STRING",
  "T_NUM", "T_NUM_B", "T_COMMA", "T_SC", "T_CONTINUE", "T_BREAK",
  "T_WHILE", "T_IF", "T_RETURN", "T_FALSE", "T_TRUE", "T_BOOL", "T_BYTE",
  "T_INT", "T_VOID", "T_ASSIGN", "T_OR", "T_AND", "T_RELOP", "T_ADD_SUB",
  "T_MUL_DIV", "T_NOT", "T_LPAREN", "T_RPAREN", "T_LBRACE", "T_RBRACE",
  "T_ELSE", "$accept", "Program", "Funcs", "FuncDecl", "RetType",
  "Formals", "FormalsList", "FormalDecl", "Statements", "Statement",
  "Call", "ExpList", "Type", "Exp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286
};
#endif

#define YYPACT_NINF (-30)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      23,   -30,   -30,   -30,   -30,     2,   -30,    23,     4,   -30,
     -30,   -30,   -11,    96,    -8,   -30,    14,    65,    36,    96,
     -30,   108,   -30,   -10,    61,    70,    45,    52,   140,   108,
      64,   -30,    80,    87,   154,     0,   -30,   -30,   154,   154,
      73,   -30,   -30,   -30,   -30,   -30,   -30,   154,   124,   -30,
      62,    86,   -30,   -30,   -30,    30,    84,   -30,    63,    22,
     161,   169,   -30,    82,   177,   -30,   154,   154,   154,   154,
     154,   -30,   -30,   154,   -30,   -30,   154,   108,   108,   154,
     -30,    37,    11,   -13,    76,   -30,   153,   -30,   -30,    91,
     -30,   -30,   108,   -30
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,    33,    32,    31,     7,     0,     2,     3,     0,     6,
       1,     4,     0,     8,     0,     9,    10,     0,     0,     0,
      12,     0,    11,     0,     0,     0,     0,     0,     0,     0,
       0,    13,     0,     0,     0,     0,    26,    25,     0,     0,
      37,    41,    39,    40,    20,    43,    42,     0,     0,    38,
       0,     0,     5,    14,    19,     0,     0,    28,     0,    29,
       0,     0,    44,     0,     0,    21,     0,     0,     0,     0,
       0,    15,    16,     0,    18,    27,     0,     0,     0,     0,
      34,    46,    45,    47,    36,    35,     0,    30,    24,    22,
      48,    17,     0,    23
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -30,   -30,   116,   -30,   -30,   -30,   112,   -30,   103,   -29,
     -21,    57,    18,   -15
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,     8,    14,    15,    16,    30,    31,
      49,    58,    33,    59
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      32,    53,    10,    40,    41,    42,    43,    12,    32,    32,
      34,    69,    70,    50,    45,    46,    13,    35,     9,    56,
      18,    19,    53,    60,    61,     9,    47,    48,    57,    76,
      32,    17,    62,    64,    68,    69,    70,    17,    72,     1,
       2,     3,     4,    66,    67,    68,    69,    70,    88,    89,
      73,    81,    82,    83,    84,    85,    32,    32,    86,    67,
      68,    69,    70,    93,    90,    21,    63,    23,    20,    36,
      65,    32,    38,    24,    25,    26,    27,    28,    37,    39,
       1,     2,     3,    66,    67,    68,    69,    70,    54,    23,
      55,    75,    74,    29,    52,    24,    25,    26,    27,    28,
      35,    70,     1,     2,     3,    66,    67,    68,    69,    70,
      79,    23,     1,     2,     3,    29,    71,    24,    25,    26,
      27,    28,    92,    11,     1,     2,     3,    40,    41,    42,
      43,    22,    51,    87,     0,     0,     0,    29,    45,    46,
       1,     2,     3,    40,    41,    42,    43,     0,    44,     0,
      47,    48,     0,     0,    45,    46,     0,    40,    41,    42,
      43,    91,     0,     0,     0,     0,    47,    48,    45,    46,
       0,     0,     0,     0,    66,    67,    68,    69,    70,     0,
      47,    48,    66,    67,    68,    69,    70,     0,     0,    77,
      66,    67,    68,    69,    70,     0,     0,    78,    66,    67,
      68,    69,    70,     0,     0,    80
};

static const yytype_int8 yycheck[] =
{
      21,    30,     0,     3,     4,     5,     6,     3,    29,    30,
      20,    24,    25,    28,    14,    15,    27,    27,     0,    34,
      28,     7,    51,    38,    39,     7,    26,    27,    28,     7,
      51,    13,    47,    48,    23,    24,    25,    19,     8,    16,
      17,    18,    19,    21,    22,    23,    24,    25,    77,    78,
      20,    66,    67,    68,    69,    70,    77,    78,    73,    22,
      23,    24,    25,    92,    79,    29,    48,     3,     3,     8,
       8,    92,    27,     9,    10,    11,    12,    13,     8,    27,
      16,    17,    18,    21,    22,    23,    24,    25,     8,     3,
       3,    28,     8,    29,    30,     9,    10,    11,    12,    13,
      27,    25,    16,    17,    18,    21,    22,    23,    24,    25,
      28,     3,    16,    17,    18,    29,    30,     9,    10,    11,
      12,    13,    31,     7,    16,    17,    18,     3,     4,     5,
       6,    19,    29,    76,    -1,    -1,    -1,    29,    14,    15,
      16,    17,    18,     3,     4,     5,     6,    -1,     8,    -1,
      26,    27,    -1,    -1,    14,    15,    -1,     3,     4,     5,
       6,     8,    -1,    -1,    -1,    -1,    26,    27,    14,    15,
      -1,    -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,
      26,    27,    21,    22,    23,    24,    25,    -1,    -1,    28,
      21,    22,    23,    24,    25,    -1,    -1,    28,    21,    22,
      23,    24,    25,    -1,    -1,    28
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    16,    17,    18,    19,    33,    34,    35,    36,    44,
       0,    34,     3,    27,    37,    38,    39,    44,    28,     7,
       3,    29,    38,     3,     9,    10,    11,    12,    13,    29,
      40,    41,    42,    44,    20,    27,     8,     8,    27,    27,
       3,     4,     5,     6,     8,    14,    15,    26,    27,    42,
      45,    40,    30,    41,     8,     3,    45,    28,    43,    45,
      45,    45,    45,    44,    45,     8,    21,    22,    23,    24,
      25,    30,     8,    20,     8,    28,     7,    28,    28,    28,
      28,    45,    45,    45,    45,    45,    45,    43,    41,    41,
      45,     8,    31,    41
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    36,    36,    37,    37,
      38,    38,    39,    40,    40,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    41,    41,    42,    42,    43,
      43,    44,    44,    44,    45,    45,    45,    45,    45,    45,
      45,    45,    45,    45,    45,    45,    45,    45,    45
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     8,     1,     1,     0,     1,
       1,     3,     2,     1,     2,     3,     3,     5,     4,     2,
       2,     3,     5,     7,     5,     2,     2,     4,     3,     1,
       3,     1,     1,     1,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     2,     3,     3,     3,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* Program: Funcs  */
#line 65 "parser.y"
               { program = yyvsp[0]; }
#line 1215 "parser.tab.c"
    break;

  case 3: /* Funcs: %empty  */
#line 68 "parser.y"
       { yyval = make_shared<Funcs>(); }
#line 1221 "parser.tab.c"
    break;

  case 4: /* Funcs: FuncDecl Funcs  */
#line 70 "parser.y"
            { 
                shared_ptr<Funcs> funcs_ptr = dynamic_pointer_cast<Funcs>(yyvsp[0]);
                shared_ptr<FuncDecl> singleFunc_ptr = dynamic_pointer_cast<FuncDecl>(yyvsp[-1]);
                funcs_ptr->push_front(singleFunc_ptr);
                yyval = funcs_ptr;
            }
#line 1232 "parser.tab.c"
    break;

  case 5: /* FuncDecl: RetType T_ID T_LPAREN Formals T_RPAREN T_LBRACE Statements T_RBRACE  */
#line 79 "parser.y"
            { 
                shared_ptr<ID> id_ptr = dynamic_pointer_cast<ID>(yyvsp[-6]);
                shared_ptr<Type> retType_ptr = dynamic_pointer_cast<Type>(yyvsp[-7]);
                shared_ptr<Formals> formals_ptr = dynamic_pointer_cast<Formals>(yyvsp[-4]);
                shared_ptr<Statements> statements_ptr = dynamic_pointer_cast<Statements>(yyvsp[-1]);
                yyval = make_shared<FuncDecl>(id_ptr, retType_ptr, formals_ptr, statements_ptr); 
            }
#line 1244 "parser.tab.c"
    break;

  case 6: /* RetType: Type  */
#line 87 "parser.y"
              { yyval = make_shared<Type>(whatTypeReceived(yyvsp[0]->text)); }
#line 1250 "parser.tab.c"
    break;

  case 7: /* RetType: T_VOID  */
#line 88 "parser.y"
                 { yyval = make_shared<Type>(whatTypeReceived(yyvsp[0]->text)); }
#line 1256 "parser.tab.c"
    break;

  case 8: /* Formals: %empty  */
#line 90 "parser.y"
         { yyval = make_shared<Formals>(); }
#line 1262 "parser.tab.c"
    break;

  case 9: /* Formals: FormalsList  */
#line 91 "parser.y"
                      { yyval = yyvsp[0]; }
#line 1268 "parser.tab.c"
    break;

  case 10: /* FormalsList: FormalDecl  */
#line 93 "parser.y"
                        { yyval = make_shared<Formals>(dynamic_pointer_cast<Formal>(yyvsp[0])); }
#line 1274 "parser.tab.c"
    break;

  case 11: /* FormalsList: FormalDecl T_COMMA FormalsList  */
#line 95 "parser.y"
        { 
            shared_ptr<Formals> formals_ptr = dynamic_pointer_cast<Formals>(yyvsp[0]);
            shared_ptr<Formal> singleFormal_ptr = dynamic_pointer_cast<Formal>(yyvsp[-2]);
            formals_ptr->push_front(singleFormal_ptr);
            yyval = formals_ptr;
        }
#line 1285 "parser.tab.c"
    break;

  case 12: /* FormalDecl: Type T_ID  */
#line 103 "parser.y"
            { 
                shared_ptr<ID> id_ptr = make_shared<ID>(yyvsp[0]->text);
                shared_ptr<Type> retType_ptr = dynamic_pointer_cast<Type>(yyvsp[-1]);
                yyval = make_shared<Formal>(id_ptr, retType_ptr); 
            }
#line 1295 "parser.tab.c"
    break;

  case 13: /* Statements: Statement  */
#line 109 "parser.y"
                      { yyval = make_shared<Statements>(dynamic_pointer_cast<Statement>(yyvsp[0])); }
#line 1301 "parser.tab.c"
    break;

  case 14: /* Statements: Statements Statement  */
#line 111 "parser.y"
            { 
                shared_ptr<Statements> statements_ptr = dynamic_pointer_cast<Statements>(yyvsp[-1]);
                shared_ptr<Statement> singleStatement_ptr = dynamic_pointer_cast<Statement>(yyvsp[0]);
                statements_ptr->push_back(singleStatement_ptr);
                yyval = statements_ptr;
            }
#line 1312 "parser.tab.c"
    break;

  case 15: /* Statement: T_LBRACE Statements T_RBRACE  */
#line 118 "parser.y"
                                        { yyval = yyvsp[-1]; }
#line 1318 "parser.tab.c"
    break;

  case 16: /* Statement: Type T_ID T_SC  */
#line 120 "parser.y"
            { 
                shared_ptr<ID> id_ptr = make_shared<ID>(yyvsp[-1]->text);
                shared_ptr<Type> type_ptr = dynamic_pointer_cast<Type>(yyvsp[-2]);
                yyval = make_shared<VarDecl>(id_ptr, type_ptr); 
            }
#line 1328 "parser.tab.c"
    break;

  case 17: /* Statement: Type T_ID T_ASSIGN Exp T_SC  */
#line 126 "parser.y"
            { 
                shared_ptr<ID> id_ptr = make_shared<ID>(yyvsp[-3]->text);
                shared_ptr<Type> type_ptr = dynamic_pointer_cast<Type>(yyvsp[-4]);
                shared_ptr<Exp> exp_ptr = dynamic_pointer_cast<Exp>(yyvsp[-1]);
                yyval = make_shared<VarDecl>(id_ptr, type_ptr, exp_ptr); 
            }
#line 1339 "parser.tab.c"
    break;

  case 18: /* Statement: T_ID T_ASSIGN Exp T_SC  */
#line 133 "parser.y"
            { 
                shared_ptr<ID> id_ptr = make_shared<ID>(yyvsp[-3]->text);
                shared_ptr<Exp> exp_ptr = dynamic_pointer_cast<Exp>(yyvsp[-1]);
                yyval = make_shared<Assign>(id_ptr, exp_ptr); 
            }
#line 1349 "parser.tab.c"
    break;

  case 19: /* Statement: Call T_SC  */
#line 138 "parser.y"
                        { yyval = yyvsp[-1]; }
#line 1355 "parser.tab.c"
    break;

  case 20: /* Statement: T_RETURN T_SC  */
#line 139 "parser.y"
                            { yyval = make_shared<Return>(); }
#line 1361 "parser.tab.c"
    break;

  case 21: /* Statement: T_RETURN Exp T_SC  */
#line 140 "parser.y"
                                { yyval = make_shared<Return>(dynamic_pointer_cast<Exp>(yyvsp[-1])); }
#line 1367 "parser.tab.c"
    break;

  case 22: /* Statement: T_IF T_LPAREN Exp T_RPAREN Statement  */
#line 142 "parser.y"
            { 
                shared_ptr<Exp> exp_ptr = dynamic_pointer_cast<Exp>(yyvsp[-2]);
                shared_ptr<Statement> statement_ptr = dynamic_pointer_cast<Statement>(yyvsp[0]);
                yyval = make_shared<If>(exp_ptr, statement_ptr); 
            }
#line 1377 "parser.tab.c"
    break;

  case 23: /* Statement: T_IF T_LPAREN Exp T_RPAREN Statement T_ELSE Statement  */
#line 148 "parser.y"
            { 
                shared_ptr<Exp> exp_ptr = dynamic_pointer_cast<Exp>(yyvsp[-4]);
                shared_ptr<Statement> statement_ptr1 = dynamic_pointer_cast<Statement>(yyvsp[-2]);
                shared_ptr<Statement> statement_ptr2 = dynamic_pointer_cast<Statement>(yyvsp[0]);
                yyval = make_shared<If>(exp_ptr, statement_ptr1, statement_ptr2); 
            }
#line 1388 "parser.tab.c"
    break;

  case 24: /* Statement: T_WHILE T_LPAREN Exp T_RPAREN Statement  */
#line 155 "parser.y"
            { 
                shared_ptr<Exp> exp_ptr = dynamic_pointer_cast<Exp>(yyvsp[-2]);
                shared_ptr<Statement> statement_ptr = dynamic_pointer_cast<Statement>(yyvsp[0]);
                yyval = make_shared<While>(exp_ptr, statement_ptr); 
            }
#line 1398 "parser.tab.c"
    break;

  case 25: /* Statement: T_BREAK T_SC  */
#line 160 "parser.y"
                           { yyval = make_shared<Break>(); }
#line 1404 "parser.tab.c"
    break;

  case 26: /* Statement: T_CONTINUE T_SC  */
#line 161 "parser.y"
                              { yyval = make_shared<Continue>(); }
#line 1410 "parser.tab.c"
    break;

  case 27: /* Call: T_ID T_LPAREN ExpList T_RPAREN  */
#line 164 "parser.y"
            {
                shared_ptr<ID> id_ptr = make_shared<ID>(yyvsp[-3]->text);
                shared_ptr<ExpList> expList_ptr = dynamic_pointer_cast<ExpList>(yyvsp[-1]);
                yyval = make_shared<Call>(id_ptr, expList_ptr); 
            }
#line 1420 "parser.tab.c"
    break;

  case 28: /* Call: T_ID T_LPAREN T_RPAREN  */
#line 169 "parser.y"
                                 { yyval = make_shared<Call>(make_shared<ID>(yyvsp[-2]->text)); }
#line 1426 "parser.tab.c"
    break;

  case 29: /* ExpList: Exp  */
#line 171 "parser.y"
             { yyval = make_shared<ExpList>(dynamic_pointer_cast<Exp>(yyvsp[0])); }
#line 1432 "parser.tab.c"
    break;

  case 30: /* ExpList: Exp T_COMMA ExpList  */
#line 173 "parser.y"
            { 
                shared_ptr<ExpList> exp_list_ptr = dynamic_pointer_cast<ExpList>(yyvsp[0]);
                shared_ptr<Exp> exp_ptr = dynamic_pointer_cast<Exp>(yyvsp[-2]);
                exp_list_ptr->push_front(exp_ptr);
                yyval = exp_list_ptr;
            }
#line 1443 "parser.tab.c"
    break;

  case 31: /* Type: T_INT  */
#line 180 "parser.y"
              { yyval = make_shared<Type>(BuiltInType::INT); }
#line 1449 "parser.tab.c"
    break;

  case 32: /* Type: T_BYTE  */
#line 181 "parser.y"
                     { yyval = make_shared<Type>(BuiltInType::BYTE); }
#line 1455 "parser.tab.c"
    break;

  case 33: /* Type: T_BOOL  */
#line 182 "parser.y"
                     { yyval = make_shared<Type>(BuiltInType::BOOL); }
#line 1461 "parser.tab.c"
    break;

  case 34: /* Exp: T_LPAREN Exp T_RPAREN  */
#line 184 "parser.y"
                              { yyval = yyvsp[-1]; }
#line 1467 "parser.tab.c"
    break;

  case 35: /* Exp: Exp T_MUL_DIV Exp  */
#line 186 "parser.y"
            { 
                BinOpType binOp = whatBinOpRecieved(yyvsp[-1]->text);
                shared_ptr<Exp> left_exp = dynamic_pointer_cast<Exp>(yyvsp[-2]);
                shared_ptr<Exp> right_exp = dynamic_pointer_cast<Exp>(yyvsp[0]);
                
                yyval = make_shared<BinOp>(binOp, left_exp, right_exp);
            }
#line 1479 "parser.tab.c"
    break;

  case 36: /* Exp: Exp T_ADD_SUB Exp  */
#line 194 "parser.y"
            { 
                BinOpType binOp = whatBinOpRecieved(yyvsp[-1]->text);
                shared_ptr<Exp> left_exp = dynamic_pointer_cast<Exp>(yyvsp[-2]);
                shared_ptr<Exp> right_exp = dynamic_pointer_cast<Exp>(yyvsp[0]);

                yyval = make_shared<BinOp>(binOp, left_exp, right_exp);
            }
#line 1491 "parser.tab.c"
    break;

  case 37: /* Exp: T_ID  */
#line 201 "parser.y"
                   { yyval = make_shared<ID>(yyvsp[0]->text); }
#line 1497 "parser.tab.c"
    break;

  case 38: /* Exp: Call  */
#line 202 "parser.y"
                   { yyval = yyvsp[0]; }
#line 1503 "parser.tab.c"
    break;

  case 39: /* Exp: T_NUM  */
#line 203 "parser.y"
                    { yyval = make_shared<Num>(yyvsp[0]->text); }
#line 1509 "parser.tab.c"
    break;

  case 40: /* Exp: T_NUM_B  */
#line 204 "parser.y"
                      { yyval = make_shared<NumB>(yyvsp[0]->text); }
#line 1515 "parser.tab.c"
    break;

  case 41: /* Exp: T_STRING  */
#line 205 "parser.y"
                       { yyval = dynamic_pointer_cast<String>(yyvsp[0]); }
#line 1521 "parser.tab.c"
    break;

  case 42: /* Exp: T_TRUE  */
#line 206 "parser.y"
                     { yyval = make_shared<Bool>(true); }
#line 1527 "parser.tab.c"
    break;

  case 43: /* Exp: T_FALSE  */
#line 207 "parser.y"
                      { yyval = make_shared<Bool>(false); }
#line 1533 "parser.tab.c"
    break;

  case 44: /* Exp: T_NOT Exp  */
#line 208 "parser.y"
                        { yyval = make_shared<Not>(dynamic_pointer_cast<Exp>(yyvsp[0])); }
#line 1539 "parser.tab.c"
    break;

  case 45: /* Exp: Exp T_AND Exp  */
#line 210 "parser.y"
            { 
                shared_ptr<Exp> exp_ptr1 = dynamic_pointer_cast<Exp>(yyvsp[-2]);
                shared_ptr<Exp> exp_ptr2 = dynamic_pointer_cast<Exp>(yyvsp[0]);
                yyval = make_shared<And>(exp_ptr1, exp_ptr2); 
            }
#line 1549 "parser.tab.c"
    break;

  case 46: /* Exp: Exp T_OR Exp  */
#line 216 "parser.y"
            { 
                shared_ptr<Exp> exp_ptr1 = dynamic_pointer_cast<Exp>(yyvsp[-2]);
                shared_ptr<Exp> exp_ptr2 = dynamic_pointer_cast<Exp>(yyvsp[0]);
                yyval = make_shared<Or>(exp_ptr1, exp_ptr2); 
            }
#line 1559 "parser.tab.c"
    break;

  case 47: /* Exp: Exp T_RELOP Exp  */
#line 222 "parser.y"
            { 
                auto left_exp = dynamic_pointer_cast<Exp>(yyvsp[-2]);
                auto right_exp = dynamic_pointer_cast<Exp>(yyvsp[0]);
                
                RelOpType relop = whatRelOpRecieved(yyvsp[-1]->text);
                yyval = make_shared<RelOp>(relop, left_exp, right_exp);
            }
#line 1571 "parser.tab.c"
    break;

  case 48: /* Exp: T_LPAREN Type T_RPAREN Exp  */
#line 230 "parser.y"
            { 
                shared_ptr<Type> type_ptr = dynamic_pointer_cast<Type>(yyvsp[-2]);
                shared_ptr<Exp> exp_ptr = dynamic_pointer_cast<Exp>(yyvsp[0]);
                yyval = make_shared<Cast>(exp_ptr, type_ptr); 
            }
#line 1581 "parser.tab.c"
    break;


#line 1585 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

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


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 236 "parser.y"


// TODO: Place any additional code here
void yyerror(const char* msg) {
    output::errorSyn(yylineno);
    //cerr << "Syntax error at line " << yylineno << ": " << msg << endl;
}

static BinOpType whatBinOpRecieved(string received)
{
    //cout << received << endl;
    BinOpType retval = BIN_ERROR;
    if("+" == received){
        retval = ADD;
    } else if("-" == received){
        retval = SUB;
    } else if("*" == received){
        retval = MUL;
    } else if("/" == received){
        retval = DIV;
    } else {
        yyerror("Unknown binop operator");
    }

    return retval;
}

static RelOpType whatRelOpRecieved(string received)
{
    //cout << received << endl;
    RelOpType retval = REL_ERROR;
    if("==" == received){
        retval = EQ;
    } else if("!=" == received){
        retval = NE;
    } else if("<" == received){
        retval = LT;
    } else if(">" == received){
        retval = GT;
    } else if("<=" == received){
        retval = LE;
    } else if(">=" == received){
        retval = GE;
    } else {
        yyerror("Unknown relop operator");
    }

    return retval;
}

static BuiltInType whatTypeReceived(string received)
{
    BuiltInType retval = TYPE_ERROR;
    if("int" == received){
        retval = INT;
    } else if("bool" == received){
        retval = BOOL;
    } else if("byte" == received){
        retval = BYTE;
    } else if("string" == received){
        retval = STRING;
    } else if("void" == received){
        retval = VOID;
    } else {
        yyerror("Unknown Type operator");
    }

    return retval;
}
