/* A Bison parser, made by GNU Bison 3.8.2.  */

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
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "alpha.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*void print_token_value(FILE *, int, YYSTYPE);*/

extern int yylineno;
int yyerror(char *yaccProvidedMessage);
int yylex(void);

extern char *yytext;
extern FILE* yyin, *yyout;
int scope = 0;
int fcounter = 0;

//pianoume tis return pou einai eksw apo synartiseis kai ta break continue pou einai eksw apo loops
int BrCnCounter = 0;
int returncounter = 0;

enum SymbolType {A_GLOBAL, A_LOCAL, A_FORMAL,  A_USERFUNC, A_LIBFUNC};

//gia kathe mia metavliti exoume ena Entry sto symbol table
struct Entry{
    int active;
    char *name;
    int scope;
    int line;
    enum SymbolType type;
    char *type_string;

    //to fscope kai oi listes sto telos painroun zwh mono otan to Entry einai user function
    int fscope;//ayto kai tis dyo listes sto telos
    //tis kaname gia na ylopoihsoyme tin prosvasimotita twn symvolwn


    struct Entry *next;
    struct Entry *prev;

    struct Entry *formallist;//lista me ta formal
    struct Entry *locallist;//lista me tis local
};
// to symbol table mas einai san ta3inomhmenh diplh sundedemenh lista opou mpainoun me thn seira ola ta scopes -> au3ousa
// 1-><-1-><-1-><-2-><-3....



struct Entry *head = NULL;

struct Entry *stack = NULL;

void InsertionToList(char *name , int scope , int line , enum SymbolType type);

void InsertionToStack(char *name , int scope , int line , enum SymbolType type);

void removeFromStack();

void Hider(int scope);

struct Entry *PrinterForScope(struct Entry *tmp);

void Printer();

int SizeOfInt();




/* psaxnei sto trexwn scope stin periptwsi tou local */

int LookupandDoLocal(char *name);

int LookupGlobal(char *name);

void LookupFunction(char *name);

void LookupParameter(char *name);

/*----------------------------------------------------------------*/

int LookupExpression(char *name);


#line 156 "alpha2.c"

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

#include "alpha2.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_U_MINUS = 3,                    /* U_MINUS  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_INTNUMBER = 5,                  /* INTNUMBER  */
  YYSYMBOL_REALNUMBER = 6,                 /* REALNUMBER  */
  YYSYMBOL_STRING = 7,                     /* STRING  */
  YYSYMBOL_IF = 8,                         /* IF  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_WHILE = 10,                     /* WHILE  */
  YYSYMBOL_FOR = 11,                       /* FOR  */
  YYSYMBOL_FUNCTION = 12,                  /* FUNCTION  */
  YYSYMBOL_RETURN = 13,                    /* RETURN  */
  YYSYMBOL_BREAK = 14,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 15,                  /* CONTINUE  */
  YYSYMBOL_AND = 16,                       /* AND  */
  YYSYMBOL_NOT = 17,                       /* NOT  */
  YYSYMBOL_OR = 18,                        /* OR  */
  YYSYMBOL_LOCAL = 19,                     /* LOCAL  */
  YYSYMBOL_TRUE = 20,                      /* TRUE  */
  YYSYMBOL_FALSE = 21,                     /* FALSE  */
  YYSYMBOL_NIL = 22,                       /* NIL  */
  YYSYMBOL_ASSIGN = 23,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 24,                      /* PLUS  */
  YYSYMBOL_MINUS = 25,                     /* MINUS  */
  YYSYMBOL_MULTI = 26,                     /* MULTI  */
  YYSYMBOL_DIV = 27,                       /* DIV  */
  YYSYMBOL_MOD = 28,                       /* MOD  */
  YYSYMBOL_EQUAL = 29,                     /* EQUAL  */
  YYSYMBOL_NOTEQUAL = 30,                  /* NOTEQUAL  */
  YYSYMBOL_DOUBLEPLUS = 31,                /* DOUBLEPLUS  */
  YYSYMBOL_DOUBLEMINUS = 32,               /* DOUBLEMINUS  */
  YYSYMBOL_GREATER = 33,                   /* GREATER  */
  YYSYMBOL_LESS = 34,                      /* LESS  */
  YYSYMBOL_GREATEREQUAL = 35,              /* GREATEREQUAL  */
  YYSYMBOL_LESSEQUAL = 36,                 /* LESSEQUAL  */
  YYSYMBOL_LEFTAGGILI = 37,                /* LEFTAGGILI  */
  YYSYMBOL_RIGHTAGGILI = 38,               /* RIGHTAGGILI  */
  YYSYMBOL_LEFTTETR = 39,                  /* LEFTTETR  */
  YYSYMBOL_RIGHTTETR = 40,                 /* RIGHTTETR  */
  YYSYMBOL_LEFTPARENTHESIS = 41,           /* LEFTPARENTHESIS  */
  YYSYMBOL_RIGHTPARENTHESIS = 42,          /* RIGHTPARENTHESIS  */
  YYSYMBOL_SEMICOLON = 43,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 44,                     /* COMMA  */
  YYSYMBOL_COLON = 45,                     /* COLON  */
  YYSYMBOL_DOUBLECOLON = 46,               /* DOUBLECOLON  */
  YYSYMBOL_DOT = 47,                       /* DOT  */
  YYSYMBOL_DOTS = 48,                      /* DOTS  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_init_libs = 51,                 /* init_libs  */
  YYSYMBOL_statements = 52,                /* statements  */
  YYSYMBOL_statement = 53,                 /* statement  */
  YYSYMBOL_expr = 54,                      /* expr  */
  YYSYMBOL_term = 55,                      /* term  */
  YYSYMBOL_assign_expr = 56,               /* assign_expr  */
  YYSYMBOL_primary = 57,                   /* primary  */
  YYSYMBOL_lvalue = 58,                    /* lvalue  */
  YYSYMBOL_member = 59,                    /* member  */
  YYSYMBOL_call = 60,                      /* call  */
  YYSYMBOL_callsuffix = 61,                /* callsuffix  */
  YYSYMBOL_normcall = 62,                  /* normcall  */
  YYSYMBOL_methodcall = 63,                /* methodcall  */
  YYSYMBOL_elist = 64,                     /* elist  */
  YYSYMBOL_objectdef = 65,                 /* objectdef  */
  YYSYMBOL_indexed = 66,                   /* indexed  */
  YYSYMBOL_indexedelem = 67,               /* indexedelem  */
  YYSYMBOL_block = 68,                     /* block  */
  YYSYMBOL_69_1 = 69,                      /* $@1  */
  YYSYMBOL_funcdef = 70,                   /* funcdef  */
  YYSYMBOL_CORRECT_SCOPE = 71,             /* CORRECT_SCOPE  */
  YYSYMBOL_FID = 72,                       /* FID  */
  YYSYMBOL_const = 73,                     /* const  */
  YYSYMBOL_idlist = 74,                    /* idlist  */
  YYSYMBOL_if_statement = 75,              /* if_statement  */
  YYSYMBOL_while_statement = 76,           /* while_statement  */
  YYSYMBOL_77_2 = 77,                      /* $@2  */
  YYSYMBOL_78_3 = 78,                      /* $@3  */
  YYSYMBOL_for_statement = 79,             /* for_statement  */
  YYSYMBOL_80_4 = 80,                      /* $@4  */
  YYSYMBOL_81_5 = 81,                      /* $@5  */
  YYSYMBOL_return_statement = 82           /* return_statement  */
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
typedef yytype_uint8 yy_state_t;

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

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   557

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  172

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   303


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   166,   166,   169,   190,   191,   195,   196,   197,   198,
     199,   205,   211,   217,   218,   219,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   239,   240,   241,   242,   247,   253,   259,   264,   267,
     276,   277,   278,   279,   280,   283,   294,   301,   307,   310,
     311,   312,   313,   316,   317,   318,   321,   322,   325,   328,
     331,   332,   333,   336,   337,   340,   341,   344,   347,   347,
     350,   357,   360,   366,   381,   382,   383,   384,   385,   386,
     389,   395,   396,   399,   400,   403,   403,   403,   406,   406,
     406,   409,   410
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
  "\"end of file\"", "error", "\"invalid token\"", "U_MINUS", "ID",
  "INTNUMBER", "REALNUMBER", "STRING", "IF", "ELSE", "WHILE", "FOR",
  "FUNCTION", "RETURN", "BREAK", "CONTINUE", "AND", "NOT", "OR", "LOCAL",
  "TRUE", "FALSE", "NIL", "ASSIGN", "PLUS", "MINUS", "MULTI", "DIV", "MOD",
  "EQUAL", "NOTEQUAL", "DOUBLEPLUS", "DOUBLEMINUS", "GREATER", "LESS",
  "GREATEREQUAL", "LESSEQUAL", "LEFTAGGILI", "RIGHTAGGILI", "LEFTTETR",
  "RIGHTTETR", "LEFTPARENTHESIS", "RIGHTPARENTHESIS", "SEMICOLON", "COMMA",
  "COLON", "DOUBLECOLON", "DOT", "DOTS", "$accept", "program", "init_libs",
  "statements", "statement", "expr", "term", "assign_expr", "primary",
  "lvalue", "member", "call", "callsuffix", "normcall", "methodcall",
  "elist", "objectdef", "indexed", "indexedelem", "block", "$@1",
  "funcdef", "CORRECT_SCOPE", "FID", "const", "idlist", "if_statement",
  "while_statement", "$@2", "$@3", "for_statement", "$@4", "$@5",
  "return_statement", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-106)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -106,     3,  -106,  -106,   156,  -106,  -106,  -106,  -106,   -30,
     -18,   -12,    36,    14,    22,    39,   245,    84,  -106,  -106,
    -106,   245,     6,     6,  -106,   199,   222,  -106,    88,  -106,
     291,  -106,  -106,  -106,    62,  -106,    40,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,   245,   245,   245,  -106,    74,
    -106,   312,  -106,  -106,  -106,  -106,  -106,    83,    15,    40,
      15,  -106,   245,   480,   -16,   -14,  -106,   354,    69,  -106,
     245,   245,   245,   245,   245,   245,   245,   245,   245,   245,
     245,   245,   245,  -106,   245,  -106,  -106,   245,   245,   117,
     135,  -106,  -106,  -106,   245,   245,   136,   375,   396,    -6,
     137,  -106,   100,   112,   269,  -106,   245,  -106,   109,  -106,
     106,   508,   495,    78,    78,  -106,  -106,  -106,   521,   521,
     -20,   -20,   -20,   -20,   480,   417,    17,  -106,   107,   438,
      42,  -106,   156,  -106,   245,  -106,    47,   106,  -106,   245,
     480,  -106,   245,  -106,  -106,   245,  -106,  -106,   145,   156,
     333,  -106,   152,   459,    54,    70,   156,  -106,   245,   120,
    -106,  -106,  -106,  -106,  -106,  -106,    94,  -106,  -106,   156,
    -106,  -106
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     5,     1,     2,    45,    74,    75,    76,     0,
       0,     0,    73,     0,     0,     0,     0,     0,    78,    79,
      77,     0,     0,     0,    68,    62,     0,    15,     0,     4,
       0,    30,    16,    38,    40,    48,    41,    42,    13,    14,
      44,     7,     8,     9,    10,     0,     0,    62,    72,     0,
      92,     0,    11,    12,    33,    46,    32,     0,    34,     0,
      36,     5,     0,    60,     0,     0,    65,     0,     0,    47,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,     0,    35,    37,     0,    62,     0,
       0,    54,    56,    57,     0,    62,     0,     0,     0,     0,
      82,    91,     0,     0,     0,    63,     0,    64,     0,    31,
      43,    28,    29,    17,    18,    19,    20,    21,    26,    27,
      22,    24,    23,    25,    39,     0,     0,    49,     0,     0,
       0,    51,     0,    85,     0,    80,     0,     0,    69,     0,
      61,    66,    62,    50,    58,    62,    52,    53,    83,     0,
       0,    71,     0,     0,     0,     0,     0,    86,    62,     0,
      81,    67,    55,    59,    84,    87,     0,    70,    88,     0,
      89,    90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -106,  -106,  -106,    98,  -105,    -4,  -106,  -106,  -106,    26,
    -106,    85,  -106,  -106,  -106,   -45,  -106,  -106,    64,    20,
    -106,   -25,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     4,    29,    63,    31,    32,    33,    34,
      35,    36,    91,    92,    93,    64,    37,    65,    66,    38,
      61,    39,   159,    49,    40,   136,    41,    42,   149,   165,
      43,   169,   171,    44
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      30,    68,    99,     3,    72,    73,    74,    75,    76,    51,
       5,    45,    54,    -1,    -1,    -1,    -1,    56,     5,     6,
       7,     8,    67,    46,   105,    17,   107,   148,   106,    47,
     108,    16,   102,    17,    18,    19,    20,   134,   106,    21,
      48,    97,    98,   126,   157,    22,    23,    57,    58,    60,
     130,   164,    28,    25,    87,    26,    88,    50,   104,   144,
      28,   106,    89,    90,   170,    52,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,    94,
     124,    95,    53,   125,   147,    84,   106,    96,    55,   151,
     129,   152,    69,    85,    86,    12,   162,   154,   106,    30,
     155,    87,   140,    88,    74,    75,    76,    59,    59,    89,
      90,   110,   163,   166,   106,   100,     5,     6,     7,     8,
       9,   127,    10,    11,    12,    13,    14,    15,    30,    16,
     150,    17,    18,    19,    20,   153,   168,    21,   106,   128,
     131,   135,   137,    22,    23,    30,    62,   142,   145,    24,
     138,    25,    30,    26,   156,    27,   160,    24,    28,   103,
       5,     6,     7,     8,     9,    30,    10,    11,    12,    13,
      14,    15,   141,    16,     0,    17,    18,    19,    20,   167,
       0,    21,     0,     0,     0,     0,     0,    22,    23,     0,
       0,     0,     0,    24,     0,    25,     0,    26,     0,    27,
       0,     0,    28,     5,     6,     7,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,     0,    17,    18,
      19,    20,     0,     0,    21,     0,     5,     6,     7,     8,
      22,    23,     0,     0,    12,     0,    62,     0,    25,    16,
      26,    17,    18,    19,    20,    28,     0,    21,     0,     5,
       6,     7,     8,    22,    23,     0,     0,     0,     0,     0,
       0,    25,    16,    26,    17,    18,    19,    20,    28,     0,
      21,     0,     0,     0,     0,     0,    22,    23,     0,     0,
       0,     0,     0,     0,    25,    70,    26,    71,     0,     0,
       0,    28,     0,    72,    73,    74,    75,    76,    77,    78,
       0,     0,    79,    80,    81,    82,     0,    70,     0,    71,
       0,     0,     0,     0,   139,    72,    73,    74,    75,    76,
      77,    78,     0,     0,    79,    80,    81,    82,    70,     0,
      71,     0,     0,     0,    83,     0,    72,    73,    74,    75,
      76,    77,    78,     0,     0,    79,    80,    81,    82,    70,
       0,    71,     0,     0,     0,   101,     0,    72,    73,    74,
      75,    76,    77,    78,     0,     0,    79,    80,    81,    82,
      70,     0,    71,     0,     0,     0,   158,     0,    72,    73,
      74,    75,    76,    77,    78,     0,     0,    79,    80,    81,
      82,    70,     0,    71,     0,     0,   109,     0,     0,    72,
      73,    74,    75,    76,    77,    78,     0,     0,    79,    80,
      81,    82,    70,     0,    71,     0,     0,   132,     0,     0,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    79,
      80,    81,    82,    70,     0,    71,     0,     0,   133,     0,
       0,    72,    73,    74,    75,    76,    77,    78,     0,     0,
      79,    80,    81,    82,    70,     0,    71,   143,     0,     0,
       0,     0,    72,    73,    74,    75,    76,    77,    78,     0,
       0,    79,    80,    81,    82,    70,     0,    71,   146,     0,
       0,     0,     0,    72,    73,    74,    75,    76,    77,    78,
       0,     0,    79,    80,    81,    82,    70,   161,    71,     0,
       0,     0,     0,     0,    72,    73,    74,    75,    76,    77,
      78,    70,     0,    79,    80,    81,    82,     0,     0,    72,
      73,    74,    75,    76,    77,    78,     0,     0,    79,    80,
      81,    82,    72,    73,    74,    75,    76,    77,    78,     0,
       0,    79,    80,    81,    82,    72,    73,    74,    75,    76,
      -1,    -1,     0,     0,    79,    80,    81,    82
};

static const yytype_int16 yycheck[] =
{
       4,    26,    47,     0,    24,    25,    26,    27,    28,    13,
       4,    41,    16,    33,    34,    35,    36,    21,     4,     5,
       6,     7,    26,    41,    40,    19,    40,   132,    44,    41,
      44,    17,    57,    19,    20,    21,    22,    43,    44,    25,
       4,    45,    46,    88,   149,    31,    32,    41,    22,    23,
      95,   156,    46,    39,    39,    41,    41,    43,    62,    42,
      46,    44,    47,    48,   169,    43,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    39,
      84,    41,    43,    87,    42,    23,    44,    47,     4,    42,
      94,    44,     4,    31,    32,    12,    42,   142,    44,   103,
     145,    39,   106,    41,    26,    27,    28,    22,    23,    47,
      48,    42,    42,   158,    44,    41,     4,     5,     6,     7,
       8,     4,    10,    11,    12,    13,    14,    15,   132,    17,
     134,    19,    20,    21,    22,   139,    42,    25,    44,     4,
       4,     4,    42,    31,    32,   149,    37,    41,    41,    37,
      38,    39,   156,    41,     9,    43,     4,    37,    46,    61,
       4,     5,     6,     7,     8,   169,    10,    11,    12,    13,
      14,    15,   108,    17,    -1,    19,    20,    21,    22,   159,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    32,    -1,
      -1,    -1,    -1,    37,    -1,    39,    -1,    41,    -1,    43,
      -1,    -1,    46,     4,     5,     6,     7,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    17,    -1,    19,    20,
      21,    22,    -1,    -1,    25,    -1,     4,     5,     6,     7,
      31,    32,    -1,    -1,    12,    -1,    37,    -1,    39,    17,
      41,    19,    20,    21,    22,    46,    -1,    25,    -1,     4,
       5,     6,     7,    31,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    17,    41,    19,    20,    21,    22,    46,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    31,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    16,    41,    18,    -1,    -1,
      -1,    46,    -1,    24,    25,    26,    27,    28,    29,    30,
      -1,    -1,    33,    34,    35,    36,    -1,    16,    -1,    18,
      -1,    -1,    -1,    -1,    45,    24,    25,    26,    27,    28,
      29,    30,    -1,    -1,    33,    34,    35,    36,    16,    -1,
      18,    -1,    -1,    -1,    43,    -1,    24,    25,    26,    27,
      28,    29,    30,    -1,    -1,    33,    34,    35,    36,    16,
      -1,    18,    -1,    -1,    -1,    43,    -1,    24,    25,    26,
      27,    28,    29,    30,    -1,    -1,    33,    34,    35,    36,
      16,    -1,    18,    -1,    -1,    -1,    43,    -1,    24,    25,
      26,    27,    28,    29,    30,    -1,    -1,    33,    34,    35,
      36,    16,    -1,    18,    -1,    -1,    42,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    -1,    -1,    33,    34,
      35,    36,    16,    -1,    18,    -1,    -1,    42,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    -1,    -1,    33,
      34,    35,    36,    16,    -1,    18,    -1,    -1,    42,    -1,
      -1,    24,    25,    26,    27,    28,    29,    30,    -1,    -1,
      33,    34,    35,    36,    16,    -1,    18,    40,    -1,    -1,
      -1,    -1,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    33,    34,    35,    36,    16,    -1,    18,    40,    -1,
      -1,    -1,    -1,    24,    25,    26,    27,    28,    29,    30,
      -1,    -1,    33,    34,    35,    36,    16,    38,    18,    -1,
      -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,    29,
      30,    16,    -1,    33,    34,    35,    36,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    -1,    -1,    33,    34,
      35,    36,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    33,    34,    35,    36,    24,    25,    26,    27,    28,
      29,    30,    -1,    -1,    33,    34,    35,    36
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    50,    51,     0,    52,     4,     5,     6,     7,     8,
      10,    11,    12,    13,    14,    15,    17,    19,    20,    21,
      22,    25,    31,    32,    37,    39,    41,    43,    46,    53,
      54,    55,    56,    57,    58,    59,    60,    65,    68,    70,
      73,    75,    76,    79,    82,    41,    41,    41,     4,    72,
      43,    54,    43,    43,    54,     4,    54,    41,    58,    60,
      58,    69,    37,    54,    64,    66,    67,    54,    70,     4,
      16,    18,    24,    25,    26,    27,    28,    29,    30,    33,
      34,    35,    36,    43,    23,    31,    32,    39,    41,    47,
      48,    61,    62,    63,    39,    41,    47,    54,    54,    64,
      41,    43,    70,    52,    54,    40,    44,    40,    44,    42,
      42,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    64,     4,     4,    54,
      64,     4,    42,    42,    43,     4,    74,    42,    38,    45,
      54,    67,    41,    40,    42,    41,    40,    42,    53,    77,
      54,    42,    44,    54,    64,    64,     9,    53,    43,    71,
       4,    38,    42,    42,    53,    78,    64,    68,    42,    80,
      53,    81
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    55,    55,    55,    55,    55,    55,    55,    55,    56,
      57,    57,    57,    57,    57,    58,    58,    58,    58,    59,
      59,    59,    59,    60,    60,    60,    61,    61,    62,    63,
      64,    64,    64,    65,    65,    66,    66,    67,    69,    68,
      70,    71,    72,    72,    73,    73,    73,    73,    73,    73,
      74,    74,    74,    75,    75,    77,    78,    76,    80,    81,
      79,    82,    82
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     2,     0,     2,     1,     1,     1,
       1,     2,     2,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     3,     2,     2,     2,     2,     2,     2,     1,     3,
       1,     1,     1,     3,     1,     1,     2,     2,     1,     3,
       4,     3,     4,     4,     2,     6,     1,     1,     3,     5,
       1,     3,     0,     3,     3,     1,     3,     5,     0,     4,
       7,     0,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     5,     7,     0,     0,     7,     0,     0,
      11,     3,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
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
  case 2: /* program: init_libs statements  */
#line 166 "alpha.y"
                               {printf("program-statements\n");}
#line 1422 "alpha2.c"
    break;

  case 3: /* init_libs: %empty  */
#line 169 "alpha.y"
           {
    int yylineno=0;
    InsertionToList("print", scope , yylineno ,  A_LIBFUNC);
    InsertionToList("input", scope , yylineno ,  A_LIBFUNC);
    InsertionToList("objectmemberkeys", scope , yylineno ,   A_LIBFUNC);
    InsertionToList("objecttotalmembers", scope , yylineno ,  A_LIBFUNC);
    InsertionToList("objectcopy", scope , yylineno ,  A_LIBFUNC);
    InsertionToList("totalarguments", scope , yylineno ,   A_LIBFUNC);
    InsertionToList("argument", scope , yylineno ,   A_LIBFUNC);
    InsertionToList("typeof", scope , yylineno ,  A_LIBFUNC);
    InsertionToList("strtonum", scope , yylineno ,   A_LIBFUNC);
    InsertionToList("sqrt", scope , yylineno ,   A_LIBFUNC);
    InsertionToList("cos", scope , yylineno ,   A_LIBFUNC);
    InsertionToList("sin", scope , yylineno ,   A_LIBFUNC);

    // sthn arxh tou symbol table einai auta ta function ths bilbiothikhs

}
#line 1445 "alpha2.c"
    break;

  case 4: /* statements: statements statement  */
#line 190 "alpha.y"
                                 {printf("statements-statement\n");}
#line 1451 "alpha2.c"
    break;

  case 5: /* statements: %empty  */
#line 191 "alpha.y"
              {printf("statements-EMPTY\n");}
#line 1457 "alpha2.c"
    break;

  case 6: /* statement: expr SEMICOLON  */
#line 195 "alpha.y"
                          {printf("statement-expr SEMICOLON\n");}
#line 1463 "alpha2.c"
    break;

  case 7: /* statement: if_statement  */
#line 196 "alpha.y"
                          {printf("statement-if_statement\n");}
#line 1469 "alpha2.c"
    break;

  case 8: /* statement: while_statement  */
#line 197 "alpha.y"
                             {printf("statement-while_statement\n");}
#line 1475 "alpha2.c"
    break;

  case 9: /* statement: for_statement  */
#line 198 "alpha.y"
                           {printf("statement-for_statement\n");}
#line 1481 "alpha2.c"
    break;

  case 10: /* statement: return_statement  */
#line 199 "alpha.y"
                              {
                if(returncounter == 0)
                {
                    yyerror("ERROR -> return not in a function");                   
                }
                printf("statement-return_statement\n");}
#line 1492 "alpha2.c"
    break;

  case 11: /* statement: BREAK SEMICOLON  */
#line 205 "alpha.y"
                              {          
                if(BrCnCounter == 0)
                {
                    yyerror("ERROR -> break not in loop");
                }
                printf("statement-BREAK SEMICOLON\n");}
#line 1503 "alpha2.c"
    break;

  case 12: /* statement: CONTINUE SEMICOLON  */
#line 211 "alpha.y"
                                {       
                if(BrCnCounter == 0)
                {
                    yyerror("ERROR -> continue not in loop");
                }
                printf("statement-CONTINUE SEMICOLON\n");}
#line 1514 "alpha2.c"
    break;

  case 13: /* statement: block  */
#line 217 "alpha.y"
                                                {printf("statement-block\n");}
#line 1520 "alpha2.c"
    break;

  case 14: /* statement: funcdef  */
#line 218 "alpha.y"
                                        {printf("statement-funcdef\n");}
#line 1526 "alpha2.c"
    break;

  case 15: /* statement: SEMICOLON  */
#line 219 "alpha.y"
                                        {printf("statement-SEMICOLON\n");}
#line 1532 "alpha2.c"
    break;

  case 16: /* expr: assign_expr  */
#line 222 "alpha.y"
                       {printf("expr-assign_expr\n");}
#line 1538 "alpha2.c"
    break;

  case 17: /* expr: expr PLUS expr  */
#line 223 "alpha.y"
                            {printf("expr-expr PLUS expr\n");}
#line 1544 "alpha2.c"
    break;

  case 18: /* expr: expr MINUS expr  */
#line 224 "alpha.y"
                             {printf("expr-expr MINUS expr\n");}
#line 1550 "alpha2.c"
    break;

  case 19: /* expr: expr MULTI expr  */
#line 225 "alpha.y"
                             {printf("expr-expr MULTI expr\n");}
#line 1556 "alpha2.c"
    break;

  case 20: /* expr: expr DIV expr  */
#line 226 "alpha.y"
                           {printf("expr-expr DIV expr\n");}
#line 1562 "alpha2.c"
    break;

  case 21: /* expr: expr MOD expr  */
#line 227 "alpha.y"
                           {printf("expr-expr MOD expr\n");}
#line 1568 "alpha2.c"
    break;

  case 22: /* expr: expr GREATER expr  */
#line 228 "alpha.y"
                               {printf("expr-expr GREATER expr\n");}
#line 1574 "alpha2.c"
    break;

  case 23: /* expr: expr GREATEREQUAL expr  */
#line 229 "alpha.y"
                                    {printf("expr-expr GREATEREQUAL expr\n");}
#line 1580 "alpha2.c"
    break;

  case 24: /* expr: expr LESS expr  */
#line 230 "alpha.y"
                            {printf("expr-expr LESS expr\n");}
#line 1586 "alpha2.c"
    break;

  case 25: /* expr: expr LESSEQUAL expr  */
#line 231 "alpha.y"
                                 {printf("expr-expr LESSEQUAL expr\n");}
#line 1592 "alpha2.c"
    break;

  case 26: /* expr: expr EQUAL expr  */
#line 232 "alpha.y"
                             {printf("expr-expr EQUAL expr\n");}
#line 1598 "alpha2.c"
    break;

  case 27: /* expr: expr NOTEQUAL expr  */
#line 233 "alpha.y"
                                {printf("expr-expr NOTEQUAL expr\n");}
#line 1604 "alpha2.c"
    break;

  case 28: /* expr: expr AND expr  */
#line 234 "alpha.y"
                           {printf("expr-expr AND expr\n");}
#line 1610 "alpha2.c"
    break;

  case 29: /* expr: expr OR expr  */
#line 235 "alpha.y"
                          {printf("expr-expr OR expr\n");}
#line 1616 "alpha2.c"
    break;

  case 30: /* expr: term  */
#line 236 "alpha.y"
                  {printf("expr-TERM\n");}
#line 1622 "alpha2.c"
    break;

  case 31: /* term: LEFTPARENTHESIS expr RIGHTPARENTHESIS  */
#line 239 "alpha.y"
                                                 {printf("term-LEFTPARENTHESIS expr RIGHTPARENTHESIS\n");}
#line 1628 "alpha2.c"
    break;

  case 32: /* term: MINUS expr  */
#line 240 "alpha.y"
                                      {printf("term-MINUS\n");}
#line 1634 "alpha2.c"
    break;

  case 33: /* term: NOT expr  */
#line 241 "alpha.y"
                      {printf("term-NOT\n");}
#line 1640 "alpha2.c"
    break;

  case 34: /* term: DOUBLEPLUS lvalue  */
#line 242 "alpha.y"
                               {printf("term-DOUBLEPLUS lvalue\n");
                if((yyvsp[0].intValue) == 1){ // to $2 phre timh 1 giati ekane lookup kai brhke function-libfunct 
                    yyerror("ERROR -> cannot modify function");
                }
            }
#line 1650 "alpha2.c"
    break;

  case 35: /* term: lvalue DOUBLEPLUS  */
#line 247 "alpha.y"
                               {printf("term-lvalue DOUBLEPLUS\n");
                if((yyvsp[-1].intValue) == 1){
                    yyerror("ERROR -> cannot modify function");
                }
            
            }
#line 1661 "alpha2.c"
    break;

  case 36: /* term: DOUBLEMINUS lvalue  */
#line 253 "alpha.y"
                                {printf("term-DOUBLEMINUS lvalue\n");
                if((yyvsp[0].intValue) == 1){
                    yyerror("ERROR -> cannot modify function");
                }
            
            }
#line 1672 "alpha2.c"
    break;

  case 37: /* term: lvalue DOUBLEMINUS  */
#line 259 "alpha.y"
                                {printf("term-lvalue DOUBLEMINUS\n");
                if((yyvsp[-1].intValue) == 1){
                    yyerror("ERROR -> cannot modify function");
                }
            }
#line 1682 "alpha2.c"
    break;

  case 38: /* term: primary  */
#line 264 "alpha.y"
                     {printf("term-primary\n");}
#line 1688 "alpha2.c"
    break;

  case 39: /* assign_expr: lvalue ASSIGN expr  */
#line 267 "alpha.y"
                                {
                if((yyvsp[-2].intValue) == 1){
                    yyerror("ERROR -> cannot assign to function");
                }
    
                printf("assign_expr-lvalue ASSIGN expr\n");
            }
#line 1700 "alpha2.c"
    break;

  case 40: /* primary: lvalue  */
#line 276 "alpha.y"
                  {printf("primary-lvalue\n");}
#line 1706 "alpha2.c"
    break;

  case 41: /* primary: call  */
#line 277 "alpha.y"
                  {printf("primary-call\n");}
#line 1712 "alpha2.c"
    break;

  case 42: /* primary: objectdef  */
#line 278 "alpha.y"
                       {printf("primary-objectdef\n");}
#line 1718 "alpha2.c"
    break;

  case 43: /* primary: LEFTPARENTHESIS funcdef RIGHTPARENTHESIS  */
#line 279 "alpha.y"
                                                      {printf("primary-LEFTPARENTHESIS funcdef RIGHTPARENTHESIS\n");}
#line 1724 "alpha2.c"
    break;

  case 44: /* primary: const  */
#line 280 "alpha.y"
                   {printf("primary-const\n");}
#line 1730 "alpha2.c"
    break;

  case 45: /* lvalue: ID  */
#line 283 "alpha.y"
              {

                printf("lvalue-ID\n");
                /*
                    userORlib = 1 otan anaferomai se userfucntion h libfunc, alliws miden
                
                */
                int userORlib = LookupExpression(yytext);
                (yyval.intValue)=userORlib;

            }
#line 1746 "alpha2.c"
    break;

  case 46: /* lvalue: LOCAL ID  */
#line 294 "alpha.y"
                      {printf("lvalue-LOCAL ID\n");
            
                /* psaxnei sto trexwn scope stin periptwsi tou local */

                int userORlib = LookupandDoLocal(yytext);            
                (yyval.intValue)=userORlib;
            }
#line 1758 "alpha2.c"
    break;

  case 47: /* lvalue: DOUBLECOLON ID  */
#line 301 "alpha.y"
                            {printf("lvalue-DOUBLECOLON ID\n");
            
                int userORlib = LookupGlobal(yytext);
                (yyval.intValue)=userORlib;
            
            }
#line 1769 "alpha2.c"
    break;

  case 48: /* lvalue: member  */
#line 307 "alpha.y"
                   {printf("lvalue-member\n");(yyval.intValue)=0;}
#line 1775 "alpha2.c"
    break;

  case 49: /* member: lvalue DOT ID  */
#line 310 "alpha.y"
                         {printf("member-lvalue DOT ID\n");}
#line 1781 "alpha2.c"
    break;

  case 50: /* member: lvalue LEFTTETR expr RIGHTTETR  */
#line 311 "alpha.y"
                                            {printf("member-lvalue LEFTTETR expr RIGHTTETR\n");}
#line 1787 "alpha2.c"
    break;

  case 51: /* member: call DOT ID  */
#line 312 "alpha.y"
                         {printf("member-call DOT ID\n");}
#line 1793 "alpha2.c"
    break;

  case 52: /* member: call LEFTTETR expr RIGHTTETR  */
#line 313 "alpha.y"
                                          {printf("member-call LEFTTETR expr RIGHTTETR\n");}
#line 1799 "alpha2.c"
    break;

  case 53: /* call: call LEFTPARENTHESIS elist RIGHTPARENTHESIS  */
#line 316 "alpha.y"
                                                       {printf("call-call LEFTPARENTHESIS elist RIGHTPARENTHESIS\n");}
#line 1805 "alpha2.c"
    break;

  case 54: /* call: lvalue callsuffix  */
#line 317 "alpha.y"
                               {printf("call-lvalue callsuffix\n");}
#line 1811 "alpha2.c"
    break;

  case 55: /* call: LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS  */
#line 318 "alpha.y"
                                                                                             {printf("call-LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS\n");}
#line 1817 "alpha2.c"
    break;

  case 56: /* callsuffix: normcall  */
#line 321 "alpha.y"
                     {printf("callsuffix-methodcall\n");}
#line 1823 "alpha2.c"
    break;

  case 57: /* callsuffix: methodcall  */
#line 322 "alpha.y"
                        {printf("callsuffix-methodcall\n");}
#line 1829 "alpha2.c"
    break;

  case 58: /* normcall: LEFTPARENTHESIS elist RIGHTPARENTHESIS  */
#line 325 "alpha.y"
                                                   {printf("normcall-LEFT_RIGHT_PARENTHESIS\n");}
#line 1835 "alpha2.c"
    break;

  case 59: /* methodcall: DOTS ID LEFTPARENTHESIS elist RIGHTPARENTHESIS  */
#line 328 "alpha.y"
                                                           {printf("methodcall-DOT ID_LEFT_RIGHT_PARENTHESIS\n");}
#line 1841 "alpha2.c"
    break;

  case 60: /* elist: expr  */
#line 331 "alpha.y"
             {printf("ELIST-EXPR\n");}
#line 1847 "alpha2.c"
    break;

  case 61: /* elist: elist COMMA expr  */
#line 332 "alpha.y"
                           {printf("ELIST-elist COMMA expr\n");}
#line 1853 "alpha2.c"
    break;

  case 62: /* elist: %empty  */
#line 333 "alpha.y"
          {printf("ELIST-EMPTY\n");}
#line 1859 "alpha2.c"
    break;

  case 63: /* objectdef: LEFTTETR elist RIGHTTETR  */
#line 336 "alpha.y"
                                    {printf("objectdef LEFTTETR elist RIGHTTETR\n");}
#line 1865 "alpha2.c"
    break;

  case 64: /* objectdef: LEFTTETR indexed RIGHTTETR  */
#line 337 "alpha.y"
                                        {printf("LEFTTETR indexed RIGHTTETR\n");}
#line 1871 "alpha2.c"
    break;

  case 65: /* indexed: indexedelem  */
#line 340 "alpha.y"
                       {printf("indexed indexedelem\n");}
#line 1877 "alpha2.c"
    break;

  case 66: /* indexed: indexed COMMA indexedelem  */
#line 341 "alpha.y"
                                        {printf("indexed COMMA indexedelem\n");}
#line 1883 "alpha2.c"
    break;

  case 67: /* indexedelem: LEFTAGGILI expr COLON expr RIGHTAGGILI  */
#line 344 "alpha.y"
                                                    {printf("indexedelem LEFTAGGILI expr COLON expr RIGHTAGGILI\n");}
#line 1889 "alpha2.c"
    break;

  case 68: /* $@1: %empty  */
#line 347 "alpha.y"
                      {scope++;}
#line 1895 "alpha2.c"
    break;

  case 69: /* block: LEFTAGGILI $@1 statements RIGHTAGGILI  */
#line 347 "alpha.y"
                                                        {printf("block LEFTAGGILI statements RIGHTAGGILI\n");Hider(scope);scope--;}
#line 1901 "alpha2.c"
    break;

  case 70: /* funcdef: FUNCTION FID LEFTPARENTHESIS idlist RIGHTPARENTHESIS CORRECT_SCOPE block  */
#line 350 "alpha.y"
                                                                                    {
                printf("funcdef FUNCTION ID LEFTPARENTHESIS idlist RIGHTPARENTHESIS block\n");
                returncounter--;
                removeFromStack();
            }
#line 1911 "alpha2.c"
    break;

  case 71: /* CORRECT_SCOPE: %empty  */
#line 357 "alpha.y"
               {returncounter++;scope--;}
#line 1917 "alpha2.c"
    break;

  case 72: /* FID: ID  */
#line 360 "alpha.y"
        {

        /* slide 21 */
        LookupFunction(yytext);
        scope++;
    }
#line 1928 "alpha2.c"
    break;

  case 73: /* FID: %empty  */
#line 366 "alpha.y"
      {    

        /* ftiaxnoume ena diko mas onoma synarthshs */
        int tmp = SizeOfInt(fcounter);
        /*printf("\n\ntmp=%d\n", tmp);*/
        char *string = (char*)malloc(sizeof(char)*(tmp+2));/* osa einai ta digits + '\0 + $ ara +2*/
        sprintf(string,"$%d",fcounter++);
        InsertionToList(string , scope , yylineno , A_USERFUNC);
        InsertionToStack(string , scope , yylineno , A_USERFUNC);

        scope++;       
    }
#line 1945 "alpha2.c"
    break;

  case 74: /* const: INTNUMBER  */
#line 381 "alpha.y"
                     {printf("const INTNUMBER\n");}
#line 1951 "alpha2.c"
    break;

  case 75: /* const: REALNUMBER  */
#line 382 "alpha.y"
                        {printf("const REALNUMBER\n");}
#line 1957 "alpha2.c"
    break;

  case 76: /* const: STRING  */
#line 383 "alpha.y"
                    {printf("const STRING\n");}
#line 1963 "alpha2.c"
    break;

  case 77: /* const: NIL  */
#line 384 "alpha.y"
                 {printf("const NIL\n");}
#line 1969 "alpha2.c"
    break;

  case 78: /* const: TRUE  */
#line 385 "alpha.y"
                  {printf("const TRUE\n");}
#line 1975 "alpha2.c"
    break;

  case 79: /* const: FALSE  */
#line 386 "alpha.y"
                   {printf("const FALSE\n");}
#line 1981 "alpha2.c"
    break;

  case 80: /* idlist: ID  */
#line 389 "alpha.y"
              {
        
        printf("idlist ID\n");
        LookupParameter(yytext);

    }
#line 1992 "alpha2.c"
    break;

  case 81: /* idlist: idlist COMMA ID  */
#line 395 "alpha.y"
                              {printf("idlist idlist COMMA ID\n"); LookupParameter(yytext);}
#line 1998 "alpha2.c"
    break;

  case 82: /* idlist: %empty  */
#line 396 "alpha.y"
              {printf("idlist empty\n");}
#line 2004 "alpha2.c"
    break;

  case 83: /* if_statement: IF LEFTPARENTHESIS expr RIGHTPARENTHESIS statement  */
#line 399 "alpha.y"
                                                                 {printf("if_statement IF LEFTPARENTHESIS expr RIGHTPARENTHESIS statement\n");}
#line 2010 "alpha2.c"
    break;

  case 84: /* if_statement: IF LEFTPARENTHESIS expr RIGHTPARENTHESIS statement ELSE statement  */
#line 400 "alpha.y"
                                                                                    {printf("if_statement IF LEFTPARENTHESIS expr RIGHTPARENTHESIS statement ELSE statement\n");}
#line 2016 "alpha2.c"
    break;

  case 85: /* $@2: %empty  */
#line 403 "alpha.y"
                                                             {BrCnCounter++;}
#line 2022 "alpha2.c"
    break;

  case 86: /* $@3: %empty  */
#line 403 "alpha.y"
                                                                                        {BrCnCounter--;}
#line 2028 "alpha2.c"
    break;

  case 87: /* while_statement: WHILE LEFTPARENTHESIS expr RIGHTPARENTHESIS $@2 statement $@3  */
#line 403 "alpha.y"
                                                                                                        {printf("while_statement WHILE LEFTPARENTHESIS expr RIGHTPARENTHESIS statement\n");}
#line 2034 "alpha2.c"
    break;

  case 88: /* $@4: %empty  */
#line 406 "alpha.y"
                                                                                         {BrCnCounter++;}
#line 2040 "alpha2.c"
    break;

  case 89: /* $@5: %empty  */
#line 406 "alpha.y"
                                                                                                                    {BrCnCounter--;}
#line 2046 "alpha2.c"
    break;

  case 90: /* for_statement: FOR LEFTPARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHTPARENTHESIS $@4 statement $@5  */
#line 406 "alpha.y"
                                                                                                                                    {printf("for_statement FOR LEFTPARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHTPARENTHESIS statement\n");}
#line 2052 "alpha2.c"
    break;

  case 91: /* return_statement: RETURN expr SEMICOLON  */
#line 409 "alpha.y"
                                        {printf(" return RETURN expr SEMICOLON\n");}
#line 2058 "alpha2.c"
    break;

  case 92: /* return_statement: RETURN SEMICOLON  */
#line 410 "alpha.y"
                                   {printf("return_statement RETURN SEMICOLON\n");}
#line 2064 "alpha2.c"
    break;


#line 2068 "alpha2.c"

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
  ++yynerrs;

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
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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

#line 417 "alpha.y"

//kanei tin eisagwgi enos id sto symbol table
//dld stin dipla syndedemeni taksinomimeni lista

void InsertionToList(char *name , int scope , int line , enum SymbolType type)
{

    struct Entry *new = (struct Entry *)malloc(sizeof(struct Entry));
    new->active = 1;
    new->name = strdup(name);
    new->scope = scope;
    new->line = line;
    new->type = type;


    if(type==A_GLOBAL)
    {
        new->type_string=strdup("global variable");
    }
    if(type==A_LOCAL)
    {
        new->type_string=strdup("local variable");
    }
    if(type==A_FORMAL)
    {
        new->type_string=strdup("formal argument");
    }
    if(type==A_USERFUNC)
    {
        new->type_string=strdup("user function");
    }
    if(type==A_LIBFUNC)
    {
        new->type_string=strdup("library function");
    }
    new->next = NULL;
    new->prev = NULL;

    if(head == NULL)
    {
        head = new;
    }
    else
    {
        struct Entry *tmp = head;
        struct Entry *tmpprev = NULL;
        while(tmp != NULL && tmp->scope <= scope)
        {
            tmpprev = tmp;
            tmp = tmp->next;
        }

        if(tmp==NULL)
        {
            new->prev = tmpprev;
            tmpprev->next = new;
        }
        else
        {
            new->prev = tmp->prev;
            new->next = tmp;

            if(tmp->prev)
            {
                tmp->prev->next = new;
            }
            else
            {
                head=new;
            }
            tmp->prev = new;
        }  
    }
}
//exw ena stack me tis synartiseis//gt to xreiazomai stin ylopoihsh tou error
//tis prosvasimotitas



void removeFromStack()
{
    stack=stack->next;
}

void InsertionToStack(char *name , int scope , int line , enum SymbolType type)
{
    struct Entry *new = (struct Entry *)malloc(sizeof(struct Entry));
    new->fscope=scope;
    new->active = 1;
    new->name = strdup(name);
    new->scope = scope;
    new->line = line;
    new->type = type;

    new->formallist=NULL;
    new->locallist=NULL;

    new->type_string=strdup("user function");
    
    new->next = stack;
    stack = new;
    
}

void Hider(int scope)
{
    struct Entry *tmp = head;
    while(tmp != NULL)
    {
        if(tmp->scope == scope)
        {
            tmp->active = 0;
        }
        tmp = tmp->next;
    }
}

struct Entry *PrinterForScope(struct Entry *tmp)
{
    int scope = tmp->scope;
    printf("------ Scope #%d ------\n" , scope);
    while(tmp != NULL && tmp->scope == scope)
    {
        printf("\"%s\" [%s] (line %d) (scope %d)\n", tmp->name, tmp->type_string, tmp->line, tmp->scope);
        tmp = tmp->next;
    }
    return tmp;
}


void Printer()
{
    struct Entry *tmp = head;
    while(tmp != NULL)
    {
        tmp = PrinterForScope(tmp);
    }
}


/* psaxnei sto trexwn scope stin periptwsi tou local */
//ylopoihsh tou slide pouy leei to local x
int LookupandDoLocal(char *name)
{

    struct Entry *tmp = head;

    if(scope!=0)
    {
        //elegxos collision me libraryfunctions
        //den prepei to name na einai libraryfunction
        while(tmp != NULL)
        {
        
            if(tmp->scope > 0)
            {
                break;
            }

            if(tmp->scope == 0 && tmp->active == 1 && tmp->type == A_LIBFUNC)
            {
            
                if(strcmp(tmp->name, name) == 0)
                {
                    yyerror("ERROR -> Conflict with LIBFUNC");
                    return -1; /* vrethike kati*/
                }
            }
            tmp = tmp->next;  
        } 
    }

    tmp = head;

    while(tmp != NULL)
    {
        
        if(tmp->scope > scope){
            break;
        }

        if(tmp->scope == scope && tmp->active == 1)
        {
            /*printf("name in list %s -- name in parameter %s\n" , tmp->name , name);*/
            if(strcmp(tmp->name, name) == 0)
            {
                if(tmp->type == A_LIBFUNC || tmp->type == A_USERFUNC)
                    return 1; /* vrethike kati ara den kanw tipota*/
                else
                    return 0;
            }
        }
        tmp = tmp->next;
        
    }

    /* den vrethike kati */
    /* eisagwgi */
    if(scope==0)
        InsertionToList(yytext, scope , yylineno , A_GLOBAL);
    else
        InsertionToList(yytext, scope , yylineno , A_LOCAL);

    return 0;
    
}

//ylopoihsh tou global x ::x
int LookupGlobal(char *name)
{
    struct Entry *tmp = head;
    while(tmp!=NULL)
    {
        if(tmp->scope == 0)
        {   
            if(strcmp(tmp->name, name) == 0)
                {
                    if(tmp->type == A_LIBFUNC || tmp->type == A_USERFUNC)
                        return 1; /* vrethike kati ara den kanw tipota*/
                    else
                        return 0; /* variable */
                }
        }
        tmp = tmp->next;
    }
    //undefinedf
    yyerror("ERROR -> did not find global");
    return -1;
}

//kanonas me function definition 

void LookupFunction(char *name)
{
    struct Entry *tmp = head;

    //elegxos collision me libraryfunctions
    //den prepei to name na einai libraryfunction
    while(tmp != NULL)
    {
        
            if(tmp->scope > 0)
            {
                break;
            }

            if(tmp->scope == 0 && tmp->active == 1 && tmp->type == A_LIBFUNC)
            {
        
                if(strcmp(tmp->name, name) == 0)
                {
                    yyerror("ERROR -> Conflict with LIBFUNC");
                    return; /* vrethike kati*/
                }
            }
            tmp = tmp->next;  
    } 
    

    tmp = head;

    while(tmp != NULL)
    {
        
        if(tmp->scope > scope){
            break;
        }

        if(tmp->scope == scope && tmp->active == 1)
        {
            /*printf("name in list %s -- name in parameter %s\n" , tmp->name , name);*/
            if(strcmp(tmp->name, name) == 0)
            {
                //redefinition 
                yyerror("ERROR -> function name already in use");
                return;
            }
        }
        tmp = tmp->next;
        
    }

    /* den vrethike kati */
    /* eisagwgi */
    
    InsertionToList(yytext, scope , yylineno , A_USERFUNC);
    InsertionToStack(yytext, scope , yylineno , A_USERFUNC);
}

//kanonas me to formal argument
void LookupParameter(char *name)
{
    struct Entry *tmp = head;

    //elegxos collision me libraryfunctions
    //den prepei to name na einai libraryfunction
    while(tmp != NULL)
    {
        
            if(tmp->scope > 0)
            {
                break;
            }

            if(tmp->scope == 0 && tmp->active == 1 && tmp->type == A_LIBFUNC)
            {
        
                if(strcmp(tmp->name, name) == 0)
                {
                    yyerror("ERROR -> Conflict with LIBFUNC");
                    return; /* vrethike kati*/
                }
            }
            tmp = tmp->next;  
    } 


    
    tmp = head;

    while(tmp != NULL)
    {
        
        if(tmp->scope > scope){
            break;
        }

        if(tmp->scope == scope && tmp->active == 1)
        {
            /*printf("name in list %s -- name in parameter %s\n" , tmp->name , name);*/
            if(strcmp(tmp->name, name) == 0)
            {
                //redefinition
                yyerror("ERROR -> parameter name already in use in this scope\n");
                return;
            }
        }
        tmp = tmp->next;
        
    }

    /* den vrethike kati */
    /* eisagwgi */
    
    InsertionToList(yytext, scope , yylineno , A_FORMAL);
    //eisagwgi sto stack stin function

    struct Entry *new = (struct Entry *)malloc(sizeof(struct Entry));
    new->name = strdup(yytext);
    new->next=stack->formallist;
    stack->formallist=new;
}


/*psaxno pros ta kato, an bro anaferomai ekei an oxi kano insert*/

/*
5

0 0 0 3 3 3 3 4 5(afeteria) 9(tmp) NULL
*/

struct Entry* getAfetiria(int scope2){
    struct Entry *tmp = head;

    struct Entry *afetiria = NULL;

    while(tmp != NULL)
    {
        if(tmp->scope > scope2)
        {
            break;
        }

        afetiria = tmp;
        tmp = tmp->next;
    }

    return afetiria;
}
//lvalue id
int LookupExpression(char *name) 
{
    struct Entry *tmp, *tmp2;
        

    //eimai mesa se synartisi
    if(stack!=NULL)
    {//prosvasimotitas pou koitaei otan i metavliti einai mesa stin synartisi an mporw na tin kanw prosvasi

        //elegxos sta dika mou formal - an vrethei OK
        tmp=stack->formallist;
        while(tmp)
        {
            if(strcmp(tmp->name, name) == 0)
            {
                return 0;    
            }
            tmp=tmp->next;
        }

        //elegxos sta dika mou local (trexwn scope) -> scope tis synartisis - an vrethei OK

        tmp = getAfetiria(scope);
        while(tmp)
        {
            if(tmp->scope==stack->fscope) 
                break;
            
            if(strcmp(tmp->name, name) == 0)
            {
                if(tmp->type == A_LIBFUNC || tmp->type == A_USERFUNC)
                    return 1; /* vrethike kati ara den kanw tipota*/
                else
                    return 0;
     
            }
            tmp=tmp->prev;
        }


        //elegxos sta param twn allwn synartsewn - an vrethei error

        tmp2=stack->next;
        while(tmp2){

            tmp=tmp2->formallist;
            while(tmp)
            {
                if(strcmp(tmp->name, name) == 0)
                {
                    yyerror("ERROR -> refer to illegal variable\n");
                    return 0;    
                }
                tmp=tmp->next;
            }

            tmp2=tmp2->next;
        }

        //elegxos sto scope synartisi mexri kai to 1 - an vrethei error

        tmp = getAfetiria(stack->fscope);
        while(tmp)
        {
            if(tmp->scope==0) 
                break;
            
            if(strcmp(tmp->name, name) == 0)
            {
                if(tmp->type == A_USERFUNC)
                    return 1; /* vrethike kati ara den kanw tipota*/
                else{
                    yyerror("ERROR -> refer to illegal variable\n");
                    return 0;
                }
     
            }
            tmp=tmp->prev;
        }


        //elegxos sto global - an vrethei OK
        tmp = head;
        while(tmp!=NULL)
        {
            if(tmp->scope == 0)
            {   
                if(strcmp(tmp->name, name) == 0)
                    {
                        if(tmp->type == A_LIBFUNC || tmp->type == A_USERFUNC)
                             return 1; /* vrethike kati ara den kanw tipota*/
                        else
                            return 0;
       
                    }
            }
            tmp = tmp->next;
        }

        //alliws eisagwgi
        /* den vrethike kati */
        /* eisagwgi */
        if(scope==0)
            InsertionToList(yytext, scope , yylineno , A_GLOBAL);
        else
            InsertionToList(yytext, scope , yylineno , A_LOCAL);

        return 0;
    }

    tmp = head;

    struct Entry *afetiria = NULL;

    while(tmp != NULL)
    {
        if(tmp->scope > scope)
        {
            break;
        }

        afetiria = tmp;
        tmp = tmp->next;
    }

    tmp = afetiria;


    while(tmp!=NULL)
    {
        if(strcmp(tmp->name, name) == 0 && tmp->active==1) /*anaferomai edo dhladh den ginetai eisagogh sto sumbol table*/
        {
            if(tmp->type == A_LIBFUNC || tmp->type == A_USERFUNC)
                return 1; /* vrethike kati ara den kanw tipota*/
            else
                return 0;
        }
        tmp = tmp->prev;
    }

    /* den vrethike kati */
    /* eisagwgi */
    if(scope==0)
        InsertionToList(yytext, scope , yylineno , A_GLOBAL);
    else
        InsertionToList(yytext, scope , yylineno , A_LOCAL);

    return 0;

}

/* epistrefei to posa psifia einai to x */

int SizeOfInt(int x)
{
    int tmp=x;
    int counter = 0;
    while(tmp!=0)
    {
        counter++;
        tmp = tmp/10;
    }
    return counter; 
}


int yyerror(char *yaccProvidedMessage)
{
    fprintf(stderr, "\n\n\t\t%s: at line %d, before token: %s\n" , yaccProvidedMessage,yylineno,yytext);
    fprintf(stderr, "\t\tINPUT NOT VALID\n\n\n");

    
}

int main(int argc , char **argv)
{
    /*orizoume to yyin kai yyout analogos me to poia periptosh eimaste*/

    if(argc == 1)
    {
        yyin = stdin;
        yyout = stdout;
    }
    else if(argc == 2)
    {
        if(!(yyin = fopen(argv[1] , "r")))
        {
            fprintf(stderr, "Cant read file: %s\n" , argv[1]);
            return 1;
        }
        yyout = stdout;
    }
    else if(argc == 3)
    {
        if(!(yyin = fopen(argv[1] , "r")))
        {
            fprintf(stderr, "Cant read file: %s\n" , argv[1]);
            return 1;
        }
        if(!(yyout = fopen(argv[2] , "w")))
        {
            fprintf(stderr, "Cant write file: %s\n", argv[2]);
            return 1;
        }
    }
    yyparse();
    Printer();
    return 0;
}


/*

    z = 5
    local k = 2
    // z-k scope = 0 = global
    //----------------------------------------------
    function foo(x,y) // x-y scope = 1
    {
        x=1
        y=1
        //epitrepete
        {
            x = 1
            y = 1
            // epitrepete
            function zoo()
            {
                x = 1
                y = 1
                //apogoreuete - no access
            }
        }
    }

    //ta formal variables (parametroi sunarthshs) mporoun na xrhsimopoihthoun 
    //mesa se emfoleumena scopes sthn sunarthsh alla oxi se emfoleumenh sunarthsh

    //-----------------------------------------------
    
    function foo()
    {
        local x = 5
        local x = 10
        //epitrepete
        function x(){} // apogoreuete-ta function names den mporoun na kanoun collide me tipota sto scope tous 
    }
    function foo(){} // apogoreuete-collide me function foo

    //------------------------------------------------

    x(1,2) // auto einai metablhth , oxi sunarthsh

*/


//302



/*
    paradeigmata redefinition error

    a)
        function f(){}
        function f(){}
    b)  
        f=1;
        function f(){}
    c)
        function f(x,x){}


    paradeigmata collision libfunc   


    a)
        function print(){}

    b)
        function foo(print){}

    c)
        {//scope 1
            local print;
        }

    paradeigma undefined error

    a)
    {
        ::x=5;
    }



    x = -(function(x, y) { return (x + y); });

*/
