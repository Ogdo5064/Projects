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


#include <assert.h>
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
//int BrCnCounter = 0;
int returncounter = 0;

typedef enum scopespace_t scopespace_t; 

enum scopespace_t {
    programvar,
    functionlocal,
    formalarg
};

enum symbol_t {var_s,programfunc_s,libraryfunc_s};

enum SymbolType {A_GLOBAL, A_LOCAL, A_FORMAL,  A_USERFUNC, A_LIBFUNC};

struct returnListNode{
    int instrNo;
    struct returnListNode * next;
};

typedef struct Entry{ // symbol table
    int active;
    char *name;
    int scope;
    int line;
    enum SymbolType type;
    char *type_string;

    struct returnListNode* returnList;

    scopespace_t space;
    unsigned offset;
    int fscope;

    int iaddress;
    int taddress;

    unsigned totalLocals;

    struct Entry *next;
    struct Entry *prev;

    struct Entry *formallist;//lista me ta formal
    struct Entry *locallist;//lista ma tis local
}Entry;



struct Entry *head = NULL;

struct Entry *stack = NULL;

Entry* InsertionToList(char *name , int scope , int line , enum SymbolType type);

void InsertionToStack(char *name , int scope , int line , enum SymbolType type);

void removeFromStack();

void Hider(int scope);

struct Entry *PrinterForScope(struct Entry *tmp);

void Printer();

int SizeOfInt();


/* psaxnei sto trexwn scope stin periptwsi tou local */

Entry* LookupandDoLocal(char *name, int *flag);

Entry *LookupGlobal(char *name , int *flag);

Entry *LookupFunction(char *name);

void LookupParameter(char *name);

/*----------------------------------------------------------------*/

Entry* LookupExpression(char *name, int *flag);

/*----------------------------------------------------------------*/
/* PHASE 3 */

typedef struct Entry Entry;
typedef enum iopcode iopcode;
typedef enum expr_t expr_t;
typedef struct expr expr;
typedef struct quad quad;



enum iopcode // perigrafei ti pra3h tha ginei
{
    assign, add, sub,
    mul, divv, mod,
    uminus, and, or,
    not, call, param,
    ret, getretval, funcstart,
    funcend, tablecreate,tablegetelem,tablesetelem,
    if_eq, if_noteq,
    if_lesseq, if_greatereq, if_less,
    if_greater, jump
};


enum expr_t{ // ti eidos expression einai
	var_e,
	tableitem_e,
	programfunc_e,
	libraryfunc_e,
	arithexpr_e,
	boolexpr_e,
	assignexpr_e,
	newtable_e,
	constnum_e,
	constbool_e,
	conststring_e,
	nil_e
};

struct expr{ // krataei ta expressions me ta opoia tha ginoun oi pra3eis ton quads
	expr_t type;
	Entry* sym;
	expr* index;
	double numConst;
	char* strConst;
	unsigned char boolConst;
    int userORlib;
	expr* next;
};

struct quad{ // olh h entolh kodikopoihmenh se assembly -> op(pra3h) -> expr1-2-3(kataxorhtes) -> label(jump if needed) -> line
	iopcode op;
	expr* result;
	expr* arg1;
	expr* arg2;
	unsigned label;
	unsigned line;
    unsigned taddress;//krataei tin antistoixi dieythinsi tou quad se instruction 
};

struct StackOffset{
    int x;
    struct StackOffset *next;
};

struct call {
    expr* elist;
    unsigned char method;
    char* name;
};

struct FOR_struct{
    unsigned int test;
    unsigned int enter;
};

struct elemlist{
    expr* expr1; 
    expr* expr2;
    struct elemlist *next;
};

struct lc_stack_t{
    unsigned counter;         
    struct lc_stack_t* next;                                  
};

struct lc_stack_t *lcs_top = 0; 
struct lc_stack_t *lcs_bottom = 0;

#define BrCnCounter (lcs_top->counter)

void push_loopcounter (void);
void pop_loopcounter (void);

void push_loopcounter()
{
    struct lc_stack_t *new = (struct lc_stack_t *)malloc(sizeof(struct lc_stack_t));
    new->next = NULL;
    new->counter = 0;
    if(lcs_top == NULL)
    {
        lcs_top = new;
    }
    else
    {
        new->next = lcs_top;
        lcs_top = new;
    }
}

void pop_loopcounter()
{
    lcs_top=lcs_top->next;
}

struct elemlist *elemlisthead = NULL;
expr* expr1; 
expr* expr2;

struct StackOffset *stackoffsethead = NULL;

void PushStackOffset(int x);
int pop_and_top();

struct call * make_new_call();

int tempcounter = 0;

struct stmt_t {
    int breaklist, contlist;
};

typedef struct stmt_t stmt_t;

stmt_t* create_stmt();
void make_stmt (stmt_t* s);
int newlist (int i);

int mergelist (int l1, int l2) ;
void patchlist (int list, int label);

unsigned programVarOffset=0;
unsigned functionLocalOffset=0;
unsigned formalArgOffset=0;
unsigned scopeSpaceCounter=1;

quad* quads = (quad*) 0;
unsigned total = 0;
unsigned int currQuad = 0;

#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)

expr* newexpr_constnum(double i);
expr *emit_iftableitem (expr * e);
expr* member_item (expr *lvalue, char *name);
expr* lvalue_expr(Entry *sym);
expr *newexpr_conststring(char *s);
expr *newexpr(expr_t t);
Entry* newtemp();
expr* newexpr_constboolean(char *b);
expr *newexpr_constnill();
int nextquad();
void check_arith (expr* e, const char* context);


void expand (void);

void emit(
    iopcode op,
    expr* arg1,
    expr* arg2,
    expr* result,
    unsigned label,
    unsigned line
);

unsigned currscopeoffset(void);
void inccurrscopeoffset(void);
void enterscopespace(void);
void exitscopespace(void);
void resetformalargsoffset(void);
void resetfunctionlocaloffset(void);
void restorecurrscopeoffset(unsigned n);
unsigned nextquadlabel(void);
void patchlabel(unsigned quadNo,unsigned label);
expr* get_last(expr* elist);
void patchlabel (unsigned quadNo, unsigned label);
expr* newexpr_constbool (unsigned int b);
void patchlist (int list, int label);
int mergelist (int l1, int l2);


scopespace_t currscopespace(void);
expr* make_call (expr* lv, expr* reversed_elist) ;
expr* reverse(expr* head);
struct elemlist* reverse2(struct elemlist* head);


/*--------------------------------*/
/* PHASE 4 */

typedef enum vmopcode{
    assign_v,
    mul_v,
    uminus_v,
    not_v,
    jle_v,
    jgt_v,
    funcenter_v,
    tablegetelem_v,
    add_v,
    div_v,
    and_v,
    jeq_v,
    jge_v,
    call_v,
    funcexit_v,
    tablesetelem_v,
    sub_v,
    mod_v,
    or_v,
    jne_v,
    jlt_v,
    pusharg_v,
    newtable_v,
    nop_v,
    jump_v,
    funccall_v,
}vmopcode;

//type of vmarg 
typedef enum vmarg_t{
    label_a = 0, //hdh arithmos
    global_a = 1, //offset scopespace
    formal_a = 2, //offset scopespace
    local_a = 3, //offset scopespace
    number_a = 4, //global pinakas ara krataw to index toy
    string_a = 5,//global pinakas ara krataw to index toy
    bool_a = 6,//einai hdh arithmos tru h false
    nil_a = 7,//me noiazei mono to type ara den exw arithmo
    userfunc_a = 8,//global pinakas ara krataw to index toy
    libfunc_a = 9,//global pinakas ara krataw to index toy
    retval_a = 10,//me noiazei mono to type ara den exw arithmo
}vmarg_t;


//assign x y (arg2=NULL)
//assign_V global,0 global,1 (vmarg_memory=0)

typedef struct vmarg{
    vmarg_t type;
    unsigned val;
    char description[100];//for nice printing

    //kathe ena expr tis tritis fasis antistixizetai se ena vmarg
    //ops kai kathe ena quad se ena instruction

    //ena null expr mesa se ena quad metatrepetai se ena vmarg me memory=0 sto antistoixo instruction

    int memory;//flag for null expressions - not printing
}vmarg;

typedef struct instruction{
    vmopcode opcode;
    vmarg result;
    vmarg arg1;
    vmarg arg2;
    unsigned srcLine;
}instruction;

typedef struct userfunc{
    unsigned address;
    unsigned localSize;
    char * id;
}userfunc;

struct funcstack{
    Entry *f;
    struct funcstack *next;
};

struct funcstack *funcstackhead = NULL;

struct Entry *popfuncstack();
void pushfuncstack(struct Entry *new);
struct Entry *topfuncstack();

struct Entry *topfuncstack()
{
    return funcstackhead->f;
}

struct Entry *popfuncstack()
{
    struct funcstack *tmp = funcstackhead;
    funcstackhead = funcstackhead->next;
    return tmp->f;
}

void pushfuncstack(struct Entry *new)
{
    struct funcstack *tmp = (struct funcstack *)malloc(sizeof(struct funcstack));
    tmp->f = new;
    tmp->next=NULL;
    if(funcstackhead == NULL)
    {
        funcstackhead=tmp;
        return;
    }

    tmp->next = funcstackhead;
    funcstackhead = tmp;
}


//pinakes statherwn gia ta instructions
double * numConsts;
unsigned totalNumConsts;

char ** stringConsts;
unsigned totalStringConsts;

char ** namedLibfuncs;
unsigned totalNamedLibfuncs;

userfunc* userFuncs;
unsigned totalUserFuncs;



//silde 12
void make_numberoperand (vmarg* arg, double val);
void make_booloperand (vmarg* arg, unsigned val);
void make_retvaloperand(vmarg* arg);

typedef struct incomplete_jump{
	unsigned instrNo;
	unsigned iaddress;
	struct incomplete_jump* next;
}incomplete_jump;

incomplete_jump* ij_head=(incomplete_jump*) 0;
unsigned ij_total=0;

void add_incomplete_jump(unsigned instrNo, unsigned iaddress);


unsigned consts_newstring(char*s);
unsigned consts_newnumber (double n);

unsigned libfuncs_newused(char *s);
unsigned userfuncs_newfunc(Entry *sym);
void patch_incomplete_jumps();

extern void generate_ADD (quad*);
extern void generate_SUB (quad*);
extern void generate_MUL (quad*);
extern void generate_DIV (quad*);
extern void generate_MOD (quad*);
extern void generate_NEWTABLE (quad*);
extern void generate_TABLEGETELEM (quad*);
extern void generate_TABLESETELEM (quad*);
extern void generate_ASSIGN (quad*);
extern void generate_NOP (quad*);
extern void generate_JUMP (quad*);
extern void generate_IF_EQ (quad*);
extern void generate_IF_NOTEQ (quad*);
extern void generate_IF_GREATER (quad*);
extern void generate_IF_GREATEREQ (quad*);
extern void generate_IF_LESS (quad*);
extern void generate_IF_LESSEQ (quad*);
extern void generate_NOT (quad*);
extern void generate_OR (quad*);
extern void generate_PARAM (quad*);
extern void generate_CALL (quad*);
extern void generate_GETRETVAL (quad*);
extern void generate_FUNCSTART (quad*);
extern void generate_RETURN (quad*);
extern void generate_FUNCEND (quad*);

extern void generate_AND (quad*);
extern void generate_UMINUS (quad*);
typedef void(*generator_func_t)(quad*);
extern void generate_relational(vmopcode op, struct quad* quad);
int currprocessedquad();
void reset_operand(vmarg*);


generator_func_t generators[]={
    generate_ASSIGN,
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UMINUS,
    generate_AND,
    generate_OR,
    generate_NOT,
    generate_CALL,
    generate_PARAM,
    generate_RETURN,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_NEWTABLE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,
    generate_IF_GREATEREQ,
    generate_IF_LESS,
    generate_IF_GREATER,
    generate_JUMP
};

void generateprakseis(vmopcode op, struct quad *);
void generate(void);

//pairnei ena expr kai to kanei vmarg
void make_operand (expr* e, vmarg* arg);


unsigned totalInstructions = 0;
unsigned int currInstruction = 0;

instruction* instructions = (instruction*) 0;
#define EXPAND_SIZE_INSTRUCTION 1024
#define CURR_SIZE_INSTRUCTION (totalInstructions*sizeof(instruction))
#define NEW_SIZE_INSTRUCTION (EXPAND_SIZE_INSTRUCTION*sizeof(instruction)+CURR_SIZE_INSTRUCTION)

int nextinstructionlabel();
void instructionPrinter();

void expandInstructions (void);
void emitInstructions(
    instruction i
);




#line 617 "alpha2.c"

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
  YYSYMBOL_break_stmt = 53,                /* break_stmt  */
  YYSYMBOL_continue_stmt = 54,             /* continue_stmt  */
  YYSYMBOL_statement = 55,                 /* statement  */
  YYSYMBOL_expr = 56,                      /* expr  */
  YYSYMBOL_term = 57,                      /* term  */
  YYSYMBOL_assign_expr = 58,               /* assign_expr  */
  YYSYMBOL_primary = 59,                   /* primary  */
  YYSYMBOL_lvalue = 60,                    /* lvalue  */
  YYSYMBOL_member = 61,                    /* member  */
  YYSYMBOL_call = 62,                      /* call  */
  YYSYMBOL_callsuffix = 63,                /* callsuffix  */
  YYSYMBOL_normcall = 64,                  /* normcall  */
  YYSYMBOL_methodcall = 65,                /* methodcall  */
  YYSYMBOL_elist = 66,                     /* elist  */
  YYSYMBOL_objectdef = 67,                 /* objectdef  */
  YYSYMBOL_indexed = 68,                   /* indexed  */
  YYSYMBOL_indexedelem = 69,               /* indexedelem  */
  YYSYMBOL_block = 70,                     /* block  */
  YYSYMBOL_71_1 = 71,                      /* $@1  */
  YYSYMBOL_FID = 72,                       /* FID  */
  YYSYMBOL_funcprefix = 73,                /* funcprefix  */
  YYSYMBOL_funcargs = 74,                  /* funcargs  */
  YYSYMBOL_funcbody = 75,                  /* funcbody  */
  YYSYMBOL_funcdef = 76,                   /* funcdef  */
  YYSYMBOL_CORRECT_SCOPE = 77,             /* CORRECT_SCOPE  */
  YYSYMBOL_const = 78,                     /* const  */
  YYSYMBOL_idlist = 79,                    /* idlist  */
  YYSYMBOL_ifprefix = 80,                  /* ifprefix  */
  YYSYMBOL_if_statement = 81,              /* if_statement  */
  YYSYMBOL_elseprefix = 82,                /* elseprefix  */
  YYSYMBOL_whilestart = 83,                /* whilestart  */
  YYSYMBOL_whilecond = 84,                 /* whilecond  */
  YYSYMBOL_while_statement = 85,           /* while_statement  */
  YYSYMBOL_86_2 = 86,                      /* $@2  */
  YYSYMBOL_87_3 = 87,                      /* $@3  */
  YYSYMBOL_N = 88,                         /* N  */
  YYSYMBOL_M = 89,                         /* M  */
  YYSYMBOL_forprefix = 90,                 /* forprefix  */
  YYSYMBOL_for_statement = 91,             /* for_statement  */
  YYSYMBOL_92_4 = 92,                      /* $@4  */
  YYSYMBOL_93_5 = 93,                      /* $@5  */
  YYSYMBOL_return_statement = 94           /* return_statement  */
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
#define YYLAST   576

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  186

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
       0,   642,   642,   645,   665,   674,   678,   686,   696,   697,
     698,   699,   700,   708,   715,   722,   723,   724,   727,   728,
     736,   744,   753,   762,   770,   781,   791,   801,   812,   824,
     837,   844,   852,   855,   858,   866,   875,   895,   919,   939,
     961,   964,   998,   999,  1000,  1001,  1006,  1009,  1023,  1032,
    1038,  1041,  1045,  1052,  1055,  1064,  1067,  1079,  1087,  1091,
    1097,  1105,  1113,  1118,  1124,  1127,  1136,  1160,  1173,  1186,
    1192,  1192,  1196,  1203,  1216,  1239,  1245,  1254,  1271,  1278,
    1282,  1285,  1288,  1291,  1294,  1299,  1305,  1306,  1316,  1322,
    1332,  1344,  1355,  1359,  1366,  1366,  1366,  1382,  1383,  1385,
    1394,  1394,  1394,  1405,  1406
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
  "statements", "break_stmt", "continue_stmt", "statement", "expr", "term",
  "assign_expr", "primary", "lvalue", "member", "call", "callsuffix",
  "normcall", "methodcall", "elist", "objectdef", "indexed", "indexedelem",
  "block", "$@1", "FID", "funcprefix", "funcargs", "funcbody", "funcdef",
  "CORRECT_SCOPE", "const", "idlist", "ifprefix", "if_statement",
  "elseprefix", "whilestart", "whilecond", "while_statement", "$@2", "$@3",
  "N", "M", "forprefix", "for_statement", "$@4", "$@5", "return_statement", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-162)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -162,     4,  -162,  -162,   168,  -162,  -162,  -162,  -162,   -30,
    -162,   -25,    21,   211,     1,    13,   264,    25,  -162,  -162,
    -162,   264,    23,    23,  -162,    14,   241,  -162,    54,  -162,
    -162,  -162,   310,  -162,  -162,  -162,   423,  -162,   -15,  -162,
    -162,    29,  -162,  -162,   168,  -162,    53,  -162,  -162,  -162,
    -162,   264,   264,  -162,  -162,  -162,   331,  -162,  -162,  -162,
    -162,  -162,    50,    20,   -15,    20,  -162,   264,   512,   -37,
     -34,  -162,   373,    55,  -162,   264,   264,   264,   264,   264,
     264,   264,   264,   264,   264,   264,   264,   264,  -162,   264,
    -162,  -162,   264,   264,    92,    94,  -162,  -162,  -162,   264,
     264,    95,    96,  -162,    93,   264,  -162,   264,   394,    -6,
    -162,    62,   108,   288,  -162,   264,  -162,    69,  -162,    68,
     134,   527,   -13,   -13,  -162,  -162,  -162,   540,   540,   266,
     266,   266,   266,   512,   449,   -14,  -162,    76,   470,    10,
    -162,  -162,    42,  -162,    87,  -162,   168,   415,   168,    45,
    -162,  -162,    68,  -162,   264,   512,  -162,   264,  -162,  -162,
     264,  -162,  -162,  -162,   122,  -162,  -162,  -162,  -162,  -162,
     264,   491,    48,    49,  -162,  -162,  -162,   352,  -162,  -162,
    -162,   168,  -162,  -162,  -162,  -162
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     5,     1,     2,    47,    79,    80,    81,     0,
      92,     0,    73,     0,     0,     0,     0,     0,    83,    84,
      82,     0,     0,     0,    70,    64,     0,    17,     0,    13,
      14,     4,     0,    32,    18,    40,    42,    50,    43,    44,
      15,     0,    16,    46,     0,     9,     0,    10,    97,    11,
      12,     0,    64,    72,    74,   104,     0,     6,     7,    35,
      48,    34,     0,    36,     0,    38,     5,     0,    62,     0,
       0,    67,     0,     0,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     8,     0,
      37,    39,     0,    64,     0,     0,    56,    58,    59,     0,
      64,     0,    87,    78,    89,     0,    94,    64,     0,     0,
     103,     0,     0,     0,    65,     0,    66,     0,    33,    45,
      30,    31,    19,    20,    21,    22,    23,    28,    29,    24,
      26,    25,    27,    41,     0,     0,    51,     0,     0,     0,
      53,    85,     0,    77,     0,    91,     0,     0,     0,     0,
      88,    98,     0,    71,     0,    63,    68,    64,    52,    60,
      64,    54,    55,    75,     0,    76,    90,    93,    95,    97,
       0,     0,     0,     0,    86,    96,   100,     0,    69,    57,
      61,     0,    99,   101,    97,   102
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -162,  -162,  -162,    65,  -162,  -162,   -43,    -4,  -162,  -162,
    -162,    26,  -162,    43,  -162,  -162,  -162,   -50,  -162,  -162,
      15,   -10,  -162,  -162,  -162,  -162,  -162,   -21,  -162,  -162,
    -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -162,  -161,
    -162,  -162,  -162,  -162,  -162,  -162
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     4,    29,    30,    31,    68,    33,    34,
      35,    36,    37,    38,    96,    97,    98,    69,    39,    70,
      71,    40,    66,    54,    41,   103,   143,    42,   144,    43,
     142,    44,    45,   146,    46,   106,    47,   148,   175,   107,
     170,    48,    49,   181,   184,    50
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      32,   104,   109,   114,     3,    73,   116,   115,   176,    56,
     117,    51,    59,    79,    80,    81,    52,    61,     5,     6,
       7,     8,    72,   185,    99,    53,   100,     5,   159,    60,
     115,    16,   101,    17,    18,    19,    20,   151,   115,    21,
      32,   111,    17,   135,    57,    22,    23,   108,    63,    65,
     139,    67,   162,    25,   115,    26,    58,   149,    74,    92,
      28,    93,    12,   113,    62,    64,    64,    94,    95,    28,
     102,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   163,   133,   164,   169,   134,   115,
     179,   180,   115,   115,   105,   138,   136,   119,   137,   140,
     141,   147,   145,   166,   152,   168,    67,   172,    32,   157,
     173,   155,     5,     6,     7,     8,     9,   160,    10,    11,
      12,    13,    14,    15,    24,    16,   174,    17,    18,    19,
      20,   112,   156,    21,   165,     0,     0,     0,   183,    22,
      23,     0,    32,     0,    32,    24,   153,    25,     0,    26,
     171,    27,     0,     0,    28,     0,     0,     0,    77,    78,
      79,    80,    81,    82,    83,     0,   177,    84,    85,    86,
      87,     0,     5,     6,     7,     8,     9,    32,    10,    11,
      12,    13,    14,    15,     0,    16,     0,    17,    18,    19,
      20,     0,     0,    21,     0,     0,     0,     0,     0,    22,
      23,     0,     0,     0,     0,    24,     0,    25,     0,    26,
       0,    27,     0,     0,    28,     5,     6,     7,     8,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    16,     0,
      17,    18,    19,    20,     0,     0,    21,     0,     0,     0,
       0,     0,    22,    23,     0,     5,     6,     7,     8,     0,
      25,     0,    26,    12,    55,     0,     0,    28,    16,     0,
      17,    18,    19,    20,     0,     0,    21,     0,     5,     6,
       7,     8,    22,    23,     0,     0,     0,     0,     0,     0,
      25,    16,    26,    17,    18,    19,    20,    28,     0,    21,
      77,    78,    79,    80,    81,    22,    23,     0,     0,    -1,
      -1,    -1,    -1,    25,    75,    26,    76,     0,     0,     0,
      28,     0,    77,    78,    79,    80,    81,    82,    83,     0,
       0,    84,    85,    86,    87,     0,    75,     0,    76,     0,
       0,     0,     0,   154,    77,    78,    79,    80,    81,    82,
      83,     0,     0,    84,    85,    86,    87,    75,     0,    76,
       0,     0,     0,    88,     0,    77,    78,    79,    80,    81,
      82,    83,     0,     0,    84,    85,    86,    87,    75,     0,
      76,     0,     0,     0,   110,     0,    77,    78,    79,    80,
      81,    82,    83,     0,     0,    84,    85,    86,    87,    75,
       0,    76,     0,     0,     0,   182,     0,    77,    78,    79,
      80,    81,    82,    83,     0,     0,    84,    85,    86,    87,
      75,     0,    76,     0,     0,   118,     0,     0,    77,    78,
      79,    80,    81,    82,    83,     0,     0,    84,    85,    86,
      87,    75,     0,    76,     0,     0,   150,     0,     0,    77,
      78,    79,    80,    81,    82,    83,    89,     0,    84,    85,
      86,    87,     0,     0,    90,    91,     0,   167,     0,     0,
       0,     0,    92,     0,    93,    75,     0,    76,     0,     0,
      94,    95,     0,    77,    78,    79,    80,    81,    82,    83,
       0,     0,    84,    85,    86,    87,    75,     0,    76,   158,
       0,     0,     0,     0,    77,    78,    79,    80,    81,    82,
      83,     0,     0,    84,    85,    86,    87,    75,     0,    76,
     161,     0,     0,     0,     0,    77,    78,    79,    80,    81,
      82,    83,     0,     0,    84,    85,    86,    87,    75,   178,
      76,     0,     0,     0,     0,     0,    77,    78,    79,    80,
      81,    82,    83,    75,     0,    84,    85,    86,    87,     0,
       0,    77,    78,    79,    80,    81,    82,    83,     0,     0,
      84,    85,    86,    87,    77,    78,    79,    80,    81,    -1,
      -1,     0,     0,    84,    85,    86,    87
};

static const yytype_int16 yycheck[] =
{
       4,    44,    52,    40,     0,    26,    40,    44,   169,    13,
      44,    41,    16,    26,    27,    28,    41,    21,     4,     5,
       6,     7,    26,   184,    39,     4,    41,     4,    42,     4,
      44,    17,    47,    19,    20,    21,    22,    43,    44,    25,
      44,    62,    19,    93,    43,    31,    32,    51,    22,    23,
     100,    37,    42,    39,    44,    41,    43,   107,     4,    39,
      46,    41,    12,    67,    41,    22,    23,    47,    48,    46,
      41,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    42,    89,    44,    42,    92,    44,
      42,    42,    44,    44,    41,    99,     4,    42,     4,     4,
       4,   105,     9,   146,    42,   148,    37,   157,   112,    41,
     160,   115,     4,     5,     6,     7,     8,    41,    10,    11,
      12,    13,    14,    15,    37,    17,     4,    19,    20,    21,
      22,    66,   117,    25,   144,    -1,    -1,    -1,   181,    31,
      32,    -1,   146,    -1,   148,    37,    38,    39,    -1,    41,
     154,    43,    -1,    -1,    46,    -1,    -1,    -1,    24,    25,
      26,    27,    28,    29,    30,    -1,   170,    33,    34,    35,
      36,    -1,     4,     5,     6,     7,     8,   181,    10,    11,
      12,    13,    14,    15,    -1,    17,    -1,    19,    20,    21,
      22,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,
      32,    -1,    -1,    -1,    -1,    37,    -1,    39,    -1,    41,
      -1,    43,    -1,    -1,    46,     4,     5,     6,     7,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    17,    -1,
      19,    20,    21,    22,    -1,    -1,    25,    -1,    -1,    -1,
      -1,    -1,    31,    32,    -1,     4,     5,     6,     7,    -1,
      39,    -1,    41,    12,    43,    -1,    -1,    46,    17,    -1,
      19,    20,    21,    22,    -1,    -1,    25,    -1,     4,     5,
       6,     7,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    17,    41,    19,    20,    21,    22,    46,    -1,    25,
      24,    25,    26,    27,    28,    31,    32,    -1,    -1,    33,
      34,    35,    36,    39,    16,    41,    18,    -1,    -1,    -1,
      46,    -1,    24,    25,    26,    27,    28,    29,    30,    -1,
      -1,    33,    34,    35,    36,    -1,    16,    -1,    18,    -1,
      -1,    -1,    -1,    45,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    16,    -1,    18,
      -1,    -1,    -1,    43,    -1,    24,    25,    26,    27,    28,
      29,    30,    -1,    -1,    33,    34,    35,    36,    16,    -1,
      18,    -1,    -1,    -1,    43,    -1,    24,    25,    26,    27,
      28,    29,    30,    -1,    -1,    33,    34,    35,    36,    16,
      -1,    18,    -1,    -1,    -1,    43,    -1,    24,    25,    26,
      27,    28,    29,    30,    -1,    -1,    33,    34,    35,    36,
      16,    -1,    18,    -1,    -1,    42,    -1,    -1,    24,    25,
      26,    27,    28,    29,    30,    -1,    -1,    33,    34,    35,
      36,    16,    -1,    18,    -1,    -1,    42,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    23,    -1,    33,    34,
      35,    36,    -1,    -1,    31,    32,    -1,    42,    -1,    -1,
      -1,    -1,    39,    -1,    41,    16,    -1,    18,    -1,    -1,
      47,    48,    -1,    24,    25,    26,    27,    28,    29,    30,
      -1,    -1,    33,    34,    35,    36,    16,    -1,    18,    40,
      -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36,    16,    -1,    18,
      40,    -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,
      29,    30,    -1,    -1,    33,    34,    35,    36,    16,    38,
      18,    -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,
      28,    29,    30,    16,    -1,    33,    34,    35,    36,    -1,
      -1,    24,    25,    26,    27,    28,    29,    30,    -1,    -1,
      33,    34,    35,    36,    24,    25,    26,    27,    28,    29,
      30,    -1,    -1,    33,    34,    35,    36
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    50,    51,     0,    52,     4,     5,     6,     7,     8,
      10,    11,    12,    13,    14,    15,    17,    19,    20,    21,
      22,    25,    31,    32,    37,    39,    41,    43,    46,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    67,
      70,    73,    76,    78,    80,    81,    83,    85,    90,    91,
      94,    41,    41,     4,    72,    43,    56,    43,    43,    56,
       4,    56,    41,    60,    62,    60,    71,    37,    56,    66,
      68,    69,    56,    76,     4,    16,    18,    24,    25,    26,
      27,    28,    29,    30,    33,    34,    35,    36,    43,    23,
      31,    32,    39,    41,    47,    48,    63,    64,    65,    39,
      41,    47,    41,    74,    55,    41,    84,    88,    56,    66,
      43,    76,    52,    56,    40,    44,    40,    44,    42,    42,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    66,     4,     4,    56,    66,
       4,     4,    79,    75,    77,     9,    82,    56,    86,    66,
      42,    43,    42,    38,    45,    56,    69,    41,    40,    42,
      41,    40,    42,    42,    44,    70,    55,    42,    55,    42,
      89,    56,    66,    66,     4,    87,    88,    56,    38,    42,
      42,    92,    43,    55,    93,    88
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    52,    52,    53,    54,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    56,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    57,    57,    57,    57,    57,    57,    57,
      57,    58,    59,    59,    59,    59,    59,    60,    60,    60,
      60,    61,    61,    61,    61,    62,    62,    62,    63,    63,
      64,    65,    66,    66,    66,    67,    67,    68,    68,    69,
      71,    70,    72,    72,    73,    74,    75,    76,    77,    78,
      78,    78,    78,    78,    78,    79,    79,    79,    80,    81,
      81,    82,    83,    84,    86,    87,    85,    88,    89,    90,
      92,    93,    91,    94,    94
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     0,     2,     0,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     1,     3,     2,     2,     2,     2,     2,     2,
       1,     3,     1,     1,     1,     3,     1,     1,     2,     2,
       1,     3,     4,     3,     4,     4,     2,     6,     1,     1,
       3,     5,     1,     3,     0,     3,     3,     1,     3,     5,
       0,     4,     1,     0,     2,     3,     2,     3,     0,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     2,
       4,     1,     1,     3,     0,     0,     5,     0,     0,     7,
       0,     0,     9,     3,     2
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
#line 642 "alpha.y"
                               {printf("program-statements\n");}
#line 1908 "alpha2.c"
    break;

  case 3: /* init_libs: %empty  */
#line 645 "alpha.y"
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
    expand();
    push_loopcounter();
}
#line 1930 "alpha2.c"
    break;

  case 4: /* statements: statements statement  */
#line 665 "alpha.y"
                                 {printf("statements-statement\n");
                (yyval.stmt_t)=create_stmt();
                make_stmt((yyval.stmt_t));

                (yyval.stmt_t)->breaklist = mergelist((yyvsp[-1].stmt_t)->breaklist, (yyvsp[0].stmt_t)->breaklist);
                (yyval.stmt_t)->contlist = mergelist((yyvsp[-1].stmt_t)->contlist, (yyvsp[0].stmt_t)->contlist);


            }
#line 1944 "alpha2.c"
    break;

  case 5: /* statements: %empty  */
#line 674 "alpha.y"
              {(yyval.stmt_t)=create_stmt();make_stmt((yyval.stmt_t));printf("statements-EMPTY\n");}
#line 1950 "alpha2.c"
    break;

  case 6: /* break_stmt: BREAK SEMICOLON  */
#line 678 "alpha.y"
                           {
                (yyval.stmt_t)=create_stmt();
                make_stmt((yyval.stmt_t));
                (yyval.stmt_t)->breaklist = newlist(nextquad()); 
                emit(jump,NULL,NULL,0,0,yylineno);
            }
#line 1961 "alpha2.c"
    break;

  case 7: /* continue_stmt: CONTINUE SEMICOLON  */
#line 686 "alpha.y"
                                 {
                (yyval.stmt_t)=create_stmt();
                make_stmt((yyval.stmt_t));
                (yyval.stmt_t)->contlist = newlist(nextquad()); 
                emit(jump,NULL,NULL,0,0,yylineno);
            }
#line 1972 "alpha2.c"
    break;

  case 8: /* statement: expr SEMICOLON  */
#line 696 "alpha.y"
                          {printf("statement-expr SEMICOLON\n");(yyval.stmt_t)=create_stmt();make_stmt((yyval.stmt_t));}
#line 1978 "alpha2.c"
    break;

  case 9: /* statement: if_statement  */
#line 697 "alpha.y"
                          {printf("statement-if_statement\n");(yyval.stmt_t)=(yyvsp[0].stmt_t);}
#line 1984 "alpha2.c"
    break;

  case 10: /* statement: while_statement  */
#line 698 "alpha.y"
                             {printf("statement-while_statement\n");(yyval.stmt_t)=(yyvsp[0].stmt_t);}
#line 1990 "alpha2.c"
    break;

  case 11: /* statement: for_statement  */
#line 699 "alpha.y"
                           {printf("statement-for_statement\n");(yyval.stmt_t)=(yyvsp[0].stmt_t);}
#line 1996 "alpha2.c"
    break;

  case 12: /* statement: return_statement  */
#line 700 "alpha.y"
                              {
                if(returncounter == 0)
                {
                    yyerror("ERROR -> return not in a function");                   
                }
                printf("statement-return_statement\n");
                (yyval.stmt_t)=create_stmt();make_stmt((yyval.stmt_t));
            }
#line 2009 "alpha2.c"
    break;

  case 13: /* statement: break_stmt  */
#line 708 "alpha.y"
                         {          
                if(BrCnCounter == 0)
                {
                    yyerror("ERROR -> break not in loop");
                }
                printf("statement-BREAK SEMICOLON\n");
                (yyval.stmt_t)=(yyvsp[0].stmt_t);}
#line 2021 "alpha2.c"
    break;

  case 14: /* statement: continue_stmt  */
#line 715 "alpha.y"
                           {       
                if(BrCnCounter == 0)
                {
                    yyerror("ERROR -> continue not in loop");
                }
                printf("statement-CONTINUE SEMICOLON\n");
                (yyval.stmt_t)=(yyvsp[0].stmt_t);}
#line 2033 "alpha2.c"
    break;

  case 15: /* statement: block  */
#line 722 "alpha.y"
                                                {printf("statement-block\n");(yyval.stmt_t)=(yyvsp[0].stmt_t);}
#line 2039 "alpha2.c"
    break;

  case 16: /* statement: funcdef  */
#line 723 "alpha.y"
                                        {printf("statement-funcdef\n");(yyval.stmt_t)=create_stmt();make_stmt((yyval.stmt_t));}
#line 2045 "alpha2.c"
    break;

  case 17: /* statement: SEMICOLON  */
#line 724 "alpha.y"
                                        {printf("statement-SEMICOLON\n");(yyval.stmt_t)=create_stmt();make_stmt((yyval.stmt_t));}
#line 2051 "alpha2.c"
    break;

  case 18: /* expr: assign_expr  */
#line 727 "alpha.y"
                       {(yyval.expr)=(yyvsp[0].expr);printf("expr-assign_expr\n");}
#line 2057 "alpha2.c"
    break;

  case 19: /* expr: expr PLUS expr  */
#line 728 "alpha.y"
                            {printf("expr-expr PLUS expr\n");
            
                (yyval.expr) = newexpr(arithexpr_e);   
                (yyval.expr)->sym = newtemp();
                emit(add, (yyvsp[-2].expr) , (yyvsp[0].expr), (yyval.expr), 0 , yylineno);
            
            
            }
#line 2070 "alpha2.c"
    break;

  case 20: /* expr: expr MINUS expr  */
#line 736 "alpha.y"
                             {printf("expr-expr MINUS expr\n");
                
                
                (yyval.expr) = newexpr(arithexpr_e);   
                (yyval.expr)->sym = newtemp();
                emit(sub, (yyvsp[-2].expr) , (yyvsp[0].expr), (yyval.expr), 0 , yylineno);
            
            }
#line 2083 "alpha2.c"
    break;

  case 21: /* expr: expr MULTI expr  */
#line 744 "alpha.y"
                             {printf("expr-expr MULTI expr\n");
            
            
                (yyval.expr) = newexpr(arithexpr_e);   
                (yyval.expr)->sym = newtemp();
                emit(mul, (yyvsp[-2].expr) , (yyvsp[0].expr), (yyval.expr), 0 , yylineno);
            
            
            }
#line 2097 "alpha2.c"
    break;

  case 22: /* expr: expr DIV expr  */
#line 753 "alpha.y"
                           {printf("expr-expr DIV expr\n");
            
            
            
                (yyval.expr) = newexpr(arithexpr_e);   
                (yyval.expr)->sym = newtemp();
                emit(divv, (yyvsp[-2].expr) , (yyvsp[0].expr), (yyval.expr), 0 , yylineno);
            
            }
#line 2111 "alpha2.c"
    break;

  case 23: /* expr: expr MOD expr  */
#line 762 "alpha.y"
                           {printf("expr-expr MOD expr\n");
            
        
                (yyval.expr) = newexpr(arithexpr_e);   
                (yyval.expr)->sym = newtemp();
                emit(mod, (yyvsp[-2].expr) , (yyvsp[0].expr), (yyval.expr), 0 , yylineno);
            
            }
#line 2124 "alpha2.c"
    break;

  case 24: /* expr: expr GREATER expr  */
#line 770 "alpha.y"
                               {printf("expr-expr GREATER expr\n");
            
                (yyval.expr) = newexpr(boolexpr_e);
                (yyval.expr)->sym = newtemp();
                emit(if_greater, (yyvsp[-2].expr), (yyvsp[0].expr), NULL, nextquad()+3,yylineno);
                emit(assign, newexpr_constboolean("false"),NULL, (yyval.expr),0,yylineno);
                emit(jump, NULL, NULL, NULL, nextquad()+2,yylineno);
                emit(assign, newexpr_constboolean("true"),NULL, (yyval.expr),0,yylineno);
            
            
            }
#line 2140 "alpha2.c"
    break;

  case 25: /* expr: expr GREATEREQUAL expr  */
#line 781 "alpha.y"
                                    {printf("expr-expr GREATEREQUAL expr\n");
                
                (yyval.expr) = newexpr(boolexpr_e);
                (yyval.expr)->sym = newtemp();
                emit(if_greatereq, (yyvsp[-2].expr), (yyvsp[0].expr), NULL, nextquad()+3,yylineno);
                emit(assign, newexpr_constboolean("false"),NULL, (yyval.expr),0,yylineno);
                emit(jump, NULL, NULL, NULL, nextquad()+2,yylineno);
                emit(assign, newexpr_constboolean("true"),NULL, (yyval.expr),0,yylineno);
            
            }
#line 2155 "alpha2.c"
    break;

  case 26: /* expr: expr LESS expr  */
#line 791 "alpha.y"
                            {printf("expr-expr LESS expr\n");
            
                (yyval.expr) = newexpr(boolexpr_e);
                (yyval.expr)->sym = newtemp();
                emit(if_less, (yyvsp[-2].expr), (yyvsp[0].expr), NULL, nextquad()+3,yylineno);
                emit(assign, newexpr_constboolean("false"),NULL, (yyval.expr),0,yylineno);
                emit(jump, NULL, NULL, NULL, nextquad()+2,yylineno);
                emit(assign, newexpr_constboolean("true"),NULL, (yyval.expr),0,yylineno);
            
            }
#line 2170 "alpha2.c"
    break;

  case 27: /* expr: expr LESSEQUAL expr  */
#line 801 "alpha.y"
                                 {printf("expr-expr LESSEQUAL expr\n");
            
                (yyval.expr) = newexpr(boolexpr_e);
                (yyval.expr)->sym = newtemp();
                emit(if_lesseq, (yyvsp[-2].expr), (yyvsp[0].expr), NULL, nextquad()+3,yylineno);
                emit(assign, newexpr_constboolean("false"),NULL, (yyval.expr),0,yylineno);
                emit(jump, NULL, NULL, NULL, nextquad()+2,yylineno);
                emit(assign, newexpr_constboolean("true"),NULL, (yyval.expr),0,yylineno);
            
            
            }
#line 2186 "alpha2.c"
    break;

  case 28: /* expr: expr EQUAL expr  */
#line 812 "alpha.y"
                             {printf("expr-expr EQUAL expr\n");
            
                (yyval.expr) = newexpr(boolexpr_e);
                (yyval.expr)->sym = newtemp();
                emit(if_eq, (yyvsp[-2].expr), (yyvsp[0].expr), NULL, nextquad()+3,yylineno);
                emit(assign, newexpr_constboolean("false"),NULL, (yyval.expr),0,yylineno);
                emit(jump, NULL, NULL, NULL, nextquad()+2,yylineno);
                emit(assign, newexpr_constboolean("true"),NULL, (yyval.expr),0,yylineno);
            
            
            
            }
#line 2203 "alpha2.c"
    break;

  case 29: /* expr: expr NOTEQUAL expr  */
#line 824 "alpha.y"
                                {printf("expr-expr NOTEQUAL expr\n");
                
                
                (yyval.expr) = newexpr(boolexpr_e);
                (yyval.expr)->sym = newtemp();
                emit(if_noteq, (yyvsp[-2].expr), (yyvsp[0].expr), NULL, nextquad()+3,yylineno);
                emit(assign, newexpr_constboolean("false"),NULL, (yyval.expr),0,yylineno);
                emit(jump, NULL, NULL, NULL, nextquad()+2,yylineno);
                emit(assign, newexpr_constboolean("true"),NULL, (yyval.expr),0,yylineno);
            
            
            
            }
#line 2221 "alpha2.c"
    break;

  case 30: /* expr: expr AND expr  */
#line 837 "alpha.y"
                           {printf("expr-expr AND expr\n");
            
                (yyval.expr) = newexpr(boolexpr_e);
                (yyval.expr)->sym = newtemp();
                emit(and, (yyvsp[-2].expr) , (yyvsp[0].expr), (yyval.expr), 0 , yylineno);
            
            }
#line 2233 "alpha2.c"
    break;

  case 31: /* expr: expr OR expr  */
#line 844 "alpha.y"
                          {printf("expr-expr OR expr\n");
                
                
                (yyval.expr) = newexpr(boolexpr_e);
                (yyval.expr)->sym = newtemp();
                emit(or, (yyvsp[-2].expr) , (yyvsp[0].expr), (yyval.expr),0,yylineno);
            
            }
#line 2246 "alpha2.c"
    break;

  case 32: /* expr: term  */
#line 852 "alpha.y"
                  {printf("expr-TERM\n");(yyval.expr)=(yyvsp[0].expr);}
#line 2252 "alpha2.c"
    break;

  case 33: /* term: LEFTPARENTHESIS expr RIGHTPARENTHESIS  */
#line 856 "alpha.y"
            {(yyval.expr)=(yyvsp[-1].expr);
            printf("term-LEFTPARENTHESIS expr RIGHTPARENTHESIS\n");}
#line 2259 "alpha2.c"
    break;

  case 34: /* term: MINUS expr  */
#line 858 "alpha.y"
                                      {printf("term-MINUS\n");

                check_arith((yyvsp[0].expr), "unary minus");
                (yyval.expr) = newexpr(arithexpr_e);
                (yyval.expr)->sym = newtemp();
                emit(uminus,(yyvsp[0].expr), NULL, (yyval.expr),0,yylineno);
            
            }
#line 2272 "alpha2.c"
    break;

  case 35: /* term: NOT expr  */
#line 866 "alpha.y"
                      {printf("term-NOT\n");
            
            
                (yyval.expr) = newexpr(boolexpr_e);
                (yyval.expr)->sym = newtemp();
                emit(not,(yyvsp[0].expr), NULL, (yyval.expr),0,yylineno);
            
            
            }
#line 2286 "alpha2.c"
    break;

  case 36: /* term: DOUBLEPLUS lvalue  */
#line 875 "alpha.y"
                               {printf("term-DOUBLEPLUS lvalue\n");
                
                if((yyvsp[0].expr)->userORlib == 1){
                    yyerror("ERROR -> cannot modify function");
                }

                check_arith((yyvsp[0].expr), "++lvalue");
                if ((yyvsp[0].expr)->type == tableitem_e) {
                    (yyval.expr) = emit_iftableitem((yyvsp[0].expr));
                    emit(add, (yyval.expr), newexpr_constnum(1), (yyval.expr),0,yylineno);
                    emit(tablesetelem, (yyvsp[0].expr), (yyvsp[0].expr)->index, (yyval.expr),0,yylineno);
                }
                else {
                    emit(add, (yyvsp[0].expr), newexpr_constnum(1), (yyvsp[0].expr),0,yylineno);
                    (yyval.expr) = newexpr(arithexpr_e);
                    (yyval.expr)->sym = newtemp();
                    emit(assign, (yyvsp[0].expr), NULL, (yyval.expr),0,yylineno);
                }

            }
#line 2311 "alpha2.c"
    break;

  case 37: /* term: lvalue DOUBLEPLUS  */
#line 895 "alpha.y"
                               {printf("term-lvalue DOUBLEPLUS\n");
                if((yyvsp[-1].expr)->userORlib == 1){
                    yyerror("ERROR -> cannot modify function");
                }


                check_arith((yyvsp[-1].expr), "lvalue++");
                (yyval.expr) = newexpr(var_e);
                (yyval.expr)->sym = newtemp();
                if ((yyvsp[-1].expr)->type == tableitem_e)
                {
                    expr* val = emit_iftableitem((yyvsp[-1].expr));
                    emit(assign, val, NULL, (yyval.expr),0,yylineno);
                    emit(add, val, newexpr_constnum(1), val,0,yylineno);
                    emit(tablesetelem, (yyvsp[-1].expr), (yyvsp[-1].expr)->index, val,0,yylineno);
                }
                else 
                {
                    emit(assign, (yyvsp[-1].expr), NULL, (yyval.expr),0,yylineno);
                    emit(add, (yyvsp[-1].expr), newexpr_constnum(1), (yyvsp[-1].expr),0,yylineno);
                }

            
            }
#line 2340 "alpha2.c"
    break;

  case 38: /* term: DOUBLEMINUS lvalue  */
#line 919 "alpha.y"
                                {printf("term-DOUBLEMINUS lvalue\n");
                if((yyvsp[0].expr)->userORlib == 1){
                    yyerror("ERROR -> cannot modify function");
                }
            
            
                check_arith((yyvsp[0].expr), "--lvalue");
                if ((yyvsp[0].expr)->type == tableitem_e) {
                    (yyval.expr) = emit_iftableitem((yyvsp[0].expr));
                    emit(sub, (yyval.expr), newexpr_constnum(1), (yyval.expr),0,yylineno);
                    emit(tablesetelem, (yyvsp[0].expr), (yyvsp[0].expr)->index, (yyval.expr),0,yylineno);
                }
                else {
                    emit(sub, (yyvsp[0].expr), newexpr_constnum(1), (yyvsp[0].expr),0,yylineno);
                    (yyval.expr) = newexpr(arithexpr_e);
                    (yyval.expr)->sym = newtemp();
                    emit(assign, (yyvsp[0].expr), NULL, (yyval.expr),0,yylineno);
                }

            }
#line 2365 "alpha2.c"
    break;

  case 39: /* term: lvalue DOUBLEMINUS  */
#line 939 "alpha.y"
                                {printf("term-lvalue DOUBLEMINUS\n");
                if((yyvsp[-1].expr)->userORlib == 1){
                    yyerror("ERROR -> cannot modify function");
                }
                
                check_arith((yyvsp[-1].expr), "lvalue++");
                (yyval.expr) = newexpr(var_e);
                (yyval.expr)->sym = newtemp();
                if ((yyvsp[-1].expr)->type == tableitem_e)
                {
                    expr* val = emit_iftableitem((yyvsp[-1].expr));
                    emit(assign, val, NULL, (yyval.expr),0,yylineno);
                    emit(sub, val, newexpr_constnum(1), val,0,yylineno);
                    emit(tablesetelem, (yyvsp[-1].expr), (yyvsp[-1].expr)->index, val,0,yylineno);
                }
                else 
                {
                    emit(assign, (yyvsp[-1].expr), NULL, (yyval.expr),0,yylineno);
                    emit(sub, (yyvsp[-1].expr), newexpr_constnum(1), (yyvsp[-1].expr),0,yylineno);
                }

            }
#line 2392 "alpha2.c"
    break;

  case 40: /* term: primary  */
#line 961 "alpha.y"
                     {printf("term-primary\n");(yyval.expr)=(yyvsp[0].expr);}
#line 2398 "alpha2.c"
    break;

  case 41: /* assign_expr: lvalue ASSIGN expr  */
#line 964 "alpha.y"
                                {
                if((yyvsp[-2].expr)->userORlib == 1){
                    yyerror("ERROR -> cannot assign to function");
                }
                
                
                    if((yyvsp[-2].expr)->type == tableitem_e)
                    {
                        emit(
                            tablesetelem,
                            (yyvsp[-2].expr),
                            (yyvsp[-2].expr)->index,
                            (yyvsp[0].expr),0,yylineno
                        );
                        (yyval.expr) = emit_iftableitem((yyvsp[-2].expr));
                        (yyval.expr)->type = assignexpr_e;
                    }
                    else
                    {
                        emit(
                            assign,
                            (yyvsp[0].expr),
                            NULL,
                            (yyvsp[-2].expr),0,yylineno
                        );
                        (yyval.expr) = newexpr(assignexpr_e);
                        (yyval.expr)->sym = newtemp();
                        emit(assign,(yyvsp[-2].expr),NULL,(yyval.expr),0,yylineno);
                    }

                printf("assign_expr-lvalue ASSIGN expr\n");
            }
#line 2435 "alpha2.c"
    break;

  case 42: /* primary: lvalue  */
#line 998 "alpha.y"
                  {printf("primary-lvalue\n");(yyval.expr)=emit_iftableitem((yyvsp[0].expr));}
#line 2441 "alpha2.c"
    break;

  case 43: /* primary: call  */
#line 999 "alpha.y"
                  {printf("primary-call\n");(yyval.expr)=(yyvsp[0].expr);}
#line 2447 "alpha2.c"
    break;

  case 44: /* primary: objectdef  */
#line 1000 "alpha.y"
                       {printf("primary-objectdef\n");(yyval.expr)=(yyvsp[0].expr);}
#line 2453 "alpha2.c"
    break;

  case 45: /* primary: LEFTPARENTHESIS funcdef RIGHTPARENTHESIS  */
#line 1001 "alpha.y"
                                                      {
                (yyval.expr) = newexpr(programfunc_e);
                (yyval.expr)->sym = (yyvsp[-1].symbol);
                printf("primary-LEFTPARENTHESIS funcdef RIGHTPARENTHESIS\n");
            }
#line 2463 "alpha2.c"
    break;

  case 46: /* primary: const  */
#line 1006 "alpha.y"
                   {printf("primary-const\n"); (yyval.expr)=(yyvsp[0].expr);}
#line 2469 "alpha2.c"
    break;

  case 47: /* lvalue: ID  */
#line 1009 "alpha.y"
              {

                printf("lvalue-ID\n");
                /*
                    userORlib = 1 otan anaferomai se userucntion h libfunc 
                    alliws miden
                
                */
                int userORlib;
                Entry * sym = LookupExpression(yytext, &userORlib);
                (yyval.expr)=lvalue_expr(sym);
                (yyval.expr)->userORlib=userORlib;

            }
#line 2488 "alpha2.c"
    break;

  case 48: /* lvalue: LOCAL ID  */
#line 1023 "alpha.y"
                      {printf("lvalue-LOCAL ID\n");
            
                /* psaxnei sto trexwn scope stin periptwsi tou local */

                int userORlib;
                Entry * sym = LookupandDoLocal(yytext, &userORlib);            
                (yyval.expr)=lvalue_expr(sym);
                (yyval.expr)->userORlib=userORlib;
            }
#line 2502 "alpha2.c"
    break;

  case 49: /* lvalue: DOUBLECOLON ID  */
#line 1032 "alpha.y"
                            {printf("lvalue-DOUBLECOLON ID\n");
                int userORlib;
                Entry * sym = LookupGlobal(yytext , &userORlib);            
                (yyval.expr)=lvalue_expr(sym);
                (yyval.expr)->userORlib=userORlib;
            }
#line 2513 "alpha2.c"
    break;

  case 50: /* lvalue: member  */
#line 1038 "alpha.y"
                   {printf("lvalue-member\n");(yyval.expr)=(yyvsp[0].expr);}
#line 2519 "alpha2.c"
    break;

  case 51: /* member: lvalue DOT ID  */
#line 1041 "alpha.y"
                         {
                (yyval.expr)=member_item((yyvsp[-2].expr), (yyvsp[0].stringValue));
                printf("member-lvalue DOT ID\n");
            }
#line 2528 "alpha2.c"
    break;

  case 52: /* member: lvalue LEFTTETR expr RIGHTTETR  */
#line 1045 "alpha.y"
                                            {
                (yyvsp[-3].expr) = emit_iftableitem((yyvsp[-3].expr));
                (yyval.expr) = newexpr(tableitem_e);
                (yyval.expr)->sym = (yyvsp[-3].expr)->sym;
                (yyval.expr)->index = (yyvsp[-1].expr); 
                printf("member-lvalue LEFTTETR expr RIGHTTETR\n");
            }
#line 2540 "alpha2.c"
    break;

  case 53: /* member: call DOT ID  */
#line 1052 "alpha.y"
                         {
                printf("member-call DOT ID\n");
                (yyval.expr)=member_item((yyvsp[-2].expr), (yyvsp[0].stringValue));}
#line 2548 "alpha2.c"
    break;

  case 54: /* member: call LEFTTETR expr RIGHTTETR  */
#line 1055 "alpha.y"
                                          {
                printf("member-call LEFTTETR expr RIGHTTETR\n");
                (yyvsp[-3].expr) = emit_iftableitem((yyvsp[-3].expr));
                (yyval.expr) = newexpr(tableitem_e);
                (yyval.expr)->sym = (yyvsp[-3].expr)->sym;
                (yyval.expr)->index = (yyvsp[-1].expr);
            }
#line 2560 "alpha2.c"
    break;

  case 55: /* call: call LEFTPARENTHESIS elist RIGHTPARENTHESIS  */
#line 1064 "alpha.y"
                                                       {
                (yyval.expr) = make_call((yyvsp[-3].expr), (yyvsp[-1].expr));
                printf("call-call LEFTPARENTHESIS elist RIGHTPARENTHESIS\n");}
#line 2568 "alpha2.c"
    break;

  case 56: /* call: lvalue callsuffix  */
#line 1067 "alpha.y"
                               {
                (yyvsp[-1].expr) = emit_iftableitem((yyvsp[-1].expr)); 
                if ((yyvsp[0].call)->method){
                    if((yyvsp[0].call)->elist==NULL)
                        (yyvsp[0].call)->elist=(yyvsp[-1].expr);
                    else
                        get_last((yyvsp[0].call)->elist)->next = (yyvsp[-1].expr); 
                    (yyvsp[-1].expr) = emit_iftableitem(member_item((yyvsp[-1].expr), (yyvsp[0].call)->name));
                }
                (yyval.expr) = make_call((yyvsp[-1].expr), (yyvsp[0].call)->elist);

                printf("call-lvalue callsuffix\n");}
#line 2585 "alpha2.c"
    break;

  case 57: /* call: LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS  */
#line 1079 "alpha.y"
                                                                                             {
                expr* func = newexpr(programfunc_e);
                func->sym = (yyvsp[-4].symbol);
                (yyval.expr) = make_call(func, (yyvsp[-1].expr));
                printf("call-LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS\n");}
#line 2595 "alpha2.c"
    break;

  case 58: /* callsuffix: normcall  */
#line 1087 "alpha.y"
             {
        (yyval.call) = (yyvsp[0].call);
        printf("callsuffix-methodcall\n");
    }
#line 2604 "alpha2.c"
    break;

  case 59: /* callsuffix: methodcall  */
#line 1091 "alpha.y"
                {
        (yyval.call) = (yyvsp[0].call);
        printf("callsuffix-methodcall\n");
    }
#line 2613 "alpha2.c"
    break;

  case 60: /* normcall: LEFTPARENTHESIS elist RIGHTPARENTHESIS  */
#line 1097 "alpha.y"
                                                 {
    (yyval.call)=make_new_call();
    (yyval.call)->elist = (yyvsp[-1].expr);
    (yyval.call)->method = 0;
    (yyval.call)->name = NULL;
    printf("normcall-LEFT_RIGHT_PARENTHESIS\n");}
#line 2624 "alpha2.c"
    break;

  case 61: /* methodcall: DOTS ID LEFTPARENTHESIS elist RIGHTPARENTHESIS  */
#line 1105 "alpha.y"
                                                           {
    (yyval.call)=make_new_call();
    (yyval.call)->elist = (yyvsp[-1].expr);
    (yyval.call)->method = 1;
    (yyval.call)->name = strdup((yyvsp[-3].stringValue));
    printf("methodcall-DOT ID_LEFT_RIGHT_PARENTHESIS\n");}
#line 2635 "alpha2.c"
    break;

  case 62: /* elist: expr  */
#line 1113 "alpha.y"
             {
            printf("ELIST-EXPR \n");
            (yyval.expr)=(yyvsp[0].expr);//vazw head to prwto stoixeio
            (yyvsp[0].expr)->next=NULL;
        }
#line 2645 "alpha2.c"
    break;

  case 63: /* elist: elist COMMA expr  */
#line 1118 "alpha.y"
                           {
            (yyval.expr)=(yyvsp[0].expr);
            //kanw LIFO
            (yyvsp[0].expr)->next=(yyvsp[-2].expr);//vazw head kathe epomeno stoixeio 
            printf("ELIST-elist COMMA expr\n");
        }
#line 2656 "alpha2.c"
    break;

  case 64: /* elist: %empty  */
#line 1124 "alpha.y"
          {printf("ELIST-EMPTY\n");(yyval.expr)=NULL;}
#line 2662 "alpha2.c"
    break;

  case 65: /* objectdef: LEFTTETR elist RIGHTTETR  */
#line 1127 "alpha.y"
                                    {
                expr* t = newexpr(newtable_e);
                t->sym = newtemp();
                emit(tablecreate, t, NULL, NULL,0,yylineno);
                (yyvsp[-1].expr)=reverse((yyvsp[-1].expr));
                for (int i = 0; (yyvsp[-1].expr); (yyvsp[-1].expr) = (yyvsp[-1].expr)->next)
                    emit(tablesetelem, t, newexpr_constnum(i++), (yyvsp[-1].expr),0,yylineno);
                (yyval.expr) = t;
                printf("objectdef LEFTTETR elist RIGHTTETR\n");}
#line 2676 "alpha2.c"
    break;

  case 66: /* objectdef: LEFTTETR indexed RIGHTTETR  */
#line 1136 "alpha.y"
                                        {
                printf("LEFTTETR indexed RIGHTTETR\n");
                expr* t = newexpr(newtable_e);
                t->sym = newtemp();
                emit(tablecreate, t, NULL, NULL, 0,yylineno);
                //emit(tablesetelem, t, index, value);
                struct elemlist *tmp = (yyvsp[-1].elemlist);

                //foreach <index, value> in $indexed do
                (yyvsp[-1].elemlist) = reverse2((yyvsp[-1].elemlist));

                tmp = (yyvsp[-1].elemlist);
                int counter = 0;
                
                while(tmp!=NULL)
                {
                    emit(tablesetelem, t, tmp->expr1, tmp->expr2 , 0 , yylineno);
                    tmp=tmp->next;
                }
                (yyval.expr) = t;
            }
#line 2702 "alpha2.c"
    break;

  case 67: /* indexed: indexedelem  */
#line 1160 "alpha.y"
                       {
                struct elemlist *new = (struct elemlist *)malloc(sizeof(struct elemlist));
                new->next = NULL;
                new->expr1 = expr1;
                new->expr2 = expr2;
                (yyvsp[0].elemlist)=new;

                //head einai to indexed   
                (yyval.elemlist)=(yyvsp[0].elemlist);//vazw head to prwto stoixeio
                (yyvsp[0].elemlist)->next=NULL;    
                
                printf("indexed indexedelem\n");
            }
#line 2720 "alpha2.c"
    break;

  case 68: /* indexed: indexed COMMA indexedelem  */
#line 1173 "alpha.y"
                                        {
                struct elemlist *new = (struct elemlist *)malloc(sizeof(struct elemlist));
                new->next = NULL;
                new->expr1 = expr1;
                new->expr2 = expr2;
                (yyvsp[0].elemlist)=new;
    
                (yyvsp[0].elemlist)->next=(yyvsp[-2].elemlist);//vazw head kathe epomeno stoixeio
                (yyval.elemlist)=(yyvsp[0].elemlist);//kanw LIFO
                printf("indexed COMMA indexedelem\n");
            }
#line 2736 "alpha2.c"
    break;

  case 69: /* indexedelem: LEFTAGGILI expr COLON expr RIGHTAGGILI  */
#line 1186 "alpha.y"
                                                    {
                expr1=(yyvsp[-3].expr);
                expr2=(yyvsp[-1].expr);
                printf("indexedelem LEFTAGGILI expr COLON expr RIGHTAGGILI\n");}
#line 2745 "alpha2.c"
    break;

  case 70: /* $@1: %empty  */
#line 1192 "alpha.y"
                      {scope++;}
#line 2751 "alpha2.c"
    break;

  case 71: /* block: LEFTAGGILI $@1 statements RIGHTAGGILI  */
#line 1192 "alpha.y"
                                                        {(yyval.stmt_t)=(yyvsp[-1].stmt_t); printf("block LEFTAGGILI statements RIGHTAGGILI\n");Hider(scope);scope--;}
#line 2757 "alpha2.c"
    break;

  case 72: /* FID: ID  */
#line 1196 "alpha.y"
        {

        /* slide 21 */
        
        //scope++;
        (yyval.stringValue)=(yyvsp[0].stringValue);
    }
#line 2769 "alpha2.c"
    break;

  case 73: /* FID: %empty  */
#line 1203 "alpha.y"
      {    

        /* ftiaxnoume ena diko mas onoma synartisi */
        int tmp = SizeOfInt(fcounter);
        /*printf("\n\ntmp=%d\n", tmp);*/
        char *string = (char*)malloc(sizeof(char)*(tmp+2));/* osa einai ta digits + '\0 + $ ara +2*/
        sprintf(string,"$%d",fcounter++);
        
        //scope++;
        (yyval.stringValue)=string;       
    }
#line 2785 "alpha2.c"
    break;

  case 74: /* funcprefix: FUNCTION FID  */
#line 1216 "alpha.y"
                        {

    //$funcprefix = newsymbol($funcname,function_s)
    if((yyvsp[0].stringValue)[0]=='$'){//anonymous functions
        (yyval.symbol)=InsertionToList((yyvsp[0].stringValue) , scope , yylineno , A_USERFUNC);
        InsertionToStack((yyvsp[0].stringValue) , scope , yylineno , A_USERFUNC);
    }else{
        (yyval.symbol)=LookupFunction((yyvsp[0].stringValue));
    }
    scope++;

    emit(jump,NULL,NULL,NULL,0,yylineno);
    //$funcprefix->userORlib=1;//fasi2 
    (yyval.symbol)->iaddress = nextquadlabel();
    emit(funcstart,lvalue_expr((yyval.symbol)),NULL,NULL,0,yylineno);
    
    //push(scopeoffsetstack,currscopeoffset();)
    PushStackOffset(currscopeoffset());
    
    enterscopespace();
    resetformalargsoffset();
}
#line 2812 "alpha2.c"
    break;

  case 75: /* funcargs: LEFTPARENTHESIS idlist RIGHTPARENTHESIS  */
#line 1240 "alpha.y"
{
    enterscopespace();
    resetfunctionlocaloffset();
}
#line 2821 "alpha2.c"
    break;

  case 76: /* funcbody: CORRECT_SCOPE block  */
#line 1245 "alpha.y"
                              {
    (yyval.unsignedValue) = currscopeoffset();
    exitscopespace();

    pop_loopcounter();
    /*  pop  */ 
}
#line 2833 "alpha2.c"
    break;

  case 77: /* funcdef: funcprefix funcargs funcbody  */
#line 1255 "alpha.y"
 {
    exitscopespace(); 
    (yyvsp[-2].symbol)->totalLocals = (yyvsp[0].unsignedValue); 
    int offset = pop_and_top(); 
    restorecurrscopeoffset(offset); 
    (yyval.symbol) = (yyvsp[-2].symbol); 
    emit(funcend, lvalue_expr((yyvsp[-2].symbol)), NULL, NULL, 0, yylineno);

    patchlabel((yyvsp[-2].symbol)->iaddress-1,nextquadlabel());
    
    printf("funcdef FUNCTION ID LEFTPARENTHESIS idlist RIGHTPARENTHESIS block\n");
    returncounter--;
    removeFromStack();
}
#line 2852 "alpha2.c"
    break;

  case 78: /* CORRECT_SCOPE: %empty  */
#line 1271 "alpha.y"
               {returncounter++;scope--;   push_loopcounter();  }
#line 2858 "alpha2.c"
    break;

  case 79: /* const: INTNUMBER  */
#line 1278 "alpha.y"
                     {
                printf("const INTNUMBER\n");
                (yyval.expr) = newexpr_constnum((yyvsp[0].intValue));
            }
#line 2867 "alpha2.c"
    break;

  case 80: /* const: REALNUMBER  */
#line 1282 "alpha.y"
                        {printf("const REALNUMBER\n");
                (yyval.expr) = newexpr_constnum((yyvsp[0].realValue));
            }
#line 2875 "alpha2.c"
    break;

  case 81: /* const: STRING  */
#line 1285 "alpha.y"
                    {printf("const STRING\n");
                (yyval.expr) = newexpr_conststring((yyvsp[0].stringValue));
            }
#line 2883 "alpha2.c"
    break;

  case 82: /* const: NIL  */
#line 1288 "alpha.y"
                 {printf("const NIL\n");
                (yyval.expr) = newexpr_constnill();
            }
#line 2891 "alpha2.c"
    break;

  case 83: /* const: TRUE  */
#line 1291 "alpha.y"
                  {printf("const TRUE\n");
                (yyval.expr) = newexpr_constboolean("true");
            }
#line 2899 "alpha2.c"
    break;

  case 84: /* const: FALSE  */
#line 1294 "alpha.y"
                   {printf("const FALSE\n");
                (yyval.expr) = newexpr_constboolean("false");
            }
#line 2907 "alpha2.c"
    break;

  case 85: /* idlist: ID  */
#line 1299 "alpha.y"
              {
        
        printf("idlist ID\n");
        LookupParameter(yytext);

    }
#line 2918 "alpha2.c"
    break;

  case 86: /* idlist: idlist COMMA ID  */
#line 1305 "alpha.y"
                              {printf("idlist idlist COMMA ID\n"); LookupParameter(yytext);}
#line 2924 "alpha2.c"
    break;

  case 87: /* idlist: %empty  */
#line 1306 "alpha.y"
              {printf("idlist empty\n");}
#line 2930 "alpha2.c"
    break;

  case 88: /* ifprefix: IF LEFTPARENTHESIS expr RIGHTPARENTHESIS  */
#line 1316 "alpha.y"
                                                  {
    emit(if_eq, (yyvsp[-1].expr) , newexpr_constbool(1) , 0, nextquad()+2, yylineno);
    (yyval.unsignedValue) = nextquad();
    emit(jump , NULL, NULL, 0 ,0 ,yylineno);
}
#line 2940 "alpha2.c"
    break;

  case 89: /* if_statement: ifprefix statement  */
#line 1322 "alpha.y"
                                {
                            patchlabel((yyvsp[-1].unsignedValue),nextquad());
                printf("if_statement IF LEFTPARENTHESIS expr RIGHTPARENTHESIS statement\n");
                (yyval.stmt_t)=create_stmt();
                make_stmt((yyval.stmt_t));

                (yyval.stmt_t)->breaklist = mergelist((yyvsp[0].stmt_t)->breaklist, (yyval.stmt_t)->breaklist);
                (yyval.stmt_t)->contlist = mergelist((yyvsp[0].stmt_t)->contlist, (yyval.stmt_t)->contlist);
                }
#line 2954 "alpha2.c"
    break;

  case 90: /* if_statement: ifprefix statement elseprefix statement  */
#line 1332 "alpha.y"
                                                        {
    patchlabel((yyvsp[-3].unsignedValue),(yyvsp[-1].unsignedValue)+1);
    patchlabel((yyvsp[-1].unsignedValue), nextquad());
printf("if_statement IF LEFTPARENTHESIS expr RIGHTPARENTHESIS statement ELSE statement\n");
(yyval.stmt_t)=create_stmt();
                make_stmt((yyval.stmt_t));

                (yyval.stmt_t)->breaklist = mergelist((yyvsp[0].stmt_t)->breaklist, (yyvsp[-2].stmt_t)->breaklist);
                (yyval.stmt_t)->contlist = mergelist((yyvsp[0].stmt_t)->contlist, (yyvsp[-2].stmt_t)->contlist);
}
#line 2969 "alpha2.c"
    break;

  case 91: /* elseprefix: ELSE  */
#line 1344 "alpha.y"
                {
    (yyval.unsignedValue) = nextquad();
    emit(jump , NULL ,NULL , 0 , 0 , yylineno);
}
#line 2978 "alpha2.c"
    break;

  case 92: /* whilestart: WHILE  */
#line 1355 "alpha.y"
                  {
    (yyval.unsignedValue) = nextquad();
}
#line 2986 "alpha2.c"
    break;

  case 93: /* whilecond: LEFTPARENTHESIS expr RIGHTPARENTHESIS  */
#line 1359 "alpha.y"
                                                {
    
    emit(if_eq,(yyvsp[-1].expr),newexpr_constbool(1),0,nextquad() + 2,yylineno);
    (yyval.unsignedValue) = nextquad();
    emit(jump, NULL, NULL, 0,0,yylineno);
}
#line 2997 "alpha2.c"
    break;

  case 94: /* $@2: %empty  */
#line 1366 "alpha.y"
                                      {BrCnCounter++;}
#line 3003 "alpha2.c"
    break;

  case 95: /* $@3: %empty  */
#line 1366 "alpha.y"
                                                                 {BrCnCounter--;}
#line 3009 "alpha2.c"
    break;

  case 96: /* while_statement: whilestart whilecond $@2 statement $@3  */
#line 1367 "alpha.y"
{printf("while_statement WHILE LEFTPARENTHESIS expr RIGHTPARENTHESIS statement\n");
    emit(jump, NULL, NULL, NULL, (yyvsp[-4].unsignedValue),yylineno);
    patchlabel((yyvsp[-3].unsignedValue), nextquad());
        patchlist((yyvsp[-1].stmt_t)->breaklist, nextquad());
        patchlist((yyvsp[-1].stmt_t)->contlist, (yyvsp[-4].unsignedValue));
        make_stmt((yyvsp[-1].stmt_t));
        (yyval.stmt_t)=(yyvsp[-1].stmt_t);
    }
#line 3022 "alpha2.c"
    break;

  case 97: /* N: %empty  */
#line 1382 "alpha.y"
   {(yyval.unsignedValue) = nextquad();emit(jump,NULL,NULL,0,0,yylineno);}
#line 3028 "alpha2.c"
    break;

  case 98: /* M: %empty  */
#line 1383 "alpha.y"
   {(yyval.unsignedValue) = nextquad();}
#line 3034 "alpha2.c"
    break;

  case 99: /* forprefix: FOR LEFTPARENTHESIS elist SEMICOLON M expr SEMICOLON  */
#line 1385 "alpha.y"
                                                                {
    struct FOR_struct FORNODE;
    (yyval.for_union)=&FORNODE;//get some memory                 
    
    (yyval.for_union)->test = (yyvsp[-2].unsignedValue);
    (yyval.for_union)->enter = nextquad();
    emit(if_eq, (yyvsp[-1].expr), newexpr_constbool(1),0,0,yylineno);
}
#line 3047 "alpha2.c"
    break;

  case 100: /* $@4: %empty  */
#line 1394 "alpha.y"
                                                    {BrCnCounter++;}
#line 3053 "alpha2.c"
    break;

  case 101: /* $@5: %empty  */
#line 1394 "alpha.y"
                                                                               {BrCnCounter--;}
#line 3059 "alpha2.c"
    break;

  case 102: /* for_statement: forprefix N elist RIGHTPARENTHESIS N $@4 statement $@5 N  */
#line 1394 "alpha.y"
                                                                                                 {
    patchlabel((yyvsp[-8].for_union)->enter, (yyvsp[-4].unsignedValue)+1);
    patchlabel((yyvsp[-7].unsignedValue), nextquad());
    patchlabel((yyvsp[-4].unsignedValue), (yyvsp[-8].for_union)->test);
    patchlabel((yyvsp[0].unsignedValue), (yyvsp[-7].unsignedValue)+1); 
    patchlist((yyvsp[-2].stmt_t)->breaklist, nextquad());
    patchlist((yyvsp[-2].stmt_t)->contlist, (yyvsp[-7].unsignedValue)+1);
    make_stmt((yyvsp[-2].stmt_t));
    (yyval.stmt_t)=(yyvsp[-2].stmt_t);
}
#line 3074 "alpha2.c"
    break;

  case 103: /* return_statement: RETURN expr SEMICOLON  */
#line 1405 "alpha.y"
                                        {printf("return RETURN expr SEMICOLON\n"); emit(ret, (yyvsp[-1].expr), NULL,NULL,0,yylineno);}
#line 3080 "alpha2.c"
    break;

  case 104: /* return_statement: RETURN SEMICOLON  */
#line 1406 "alpha.y"
                                   {printf("return_statement RETURN SEMICOLON\n"); emit(ret, NULL, NULL,NULL,0,yylineno);}
#line 3086 "alpha2.c"
    break;


#line 3090 "alpha2.c"

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

#line 1412 "alpha.y"


Entry* InsertionToList(char *name , int scope , int line , enum SymbolType type)
{

    struct Entry *new = (struct Entry *)malloc(sizeof(struct Entry));
    new->returnList=NULL;
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

    return new;
}

void removeFromStack()
{
    stack=stack->next;
}

void InsertionToStack(char *name , int scope , int line , enum SymbolType type)
{
    struct Entry *new = (struct Entry *)malloc(sizeof(struct Entry));
    new->returnList=NULL;
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

Entry* LookupandDoLocal(char *name,int *flag)
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
                    *flag=-1;
                    return NULL; /* vrethike kati*/
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
                if(tmp->type == A_LIBFUNC || tmp->type == A_USERFUNC){
                    *flag=1;
                    return tmp; /* vrethike kati ara den kanw tipota*/
                }else{
                    *flag=0;
                    return tmp;
                }
            }
        }
        tmp = tmp->next;
        
    }

    /* den vrethike kati */
    /* eisagwgi */
    Entry *new;
    if(scope==0)
        new=InsertionToList(name, scope , yylineno , A_GLOBAL);
    else
        new=InsertionToList(name, scope , yylineno , A_LOCAL);
    
    new->space = currscopespace();
    new->offset = currscopeoffset();
    inccurrscopeoffset();
                
    *flag=0;
    return new;
    
}


Entry *LookupGlobal(char *name ,int *flag)
{
    struct Entry *tmp = head;
    while(tmp!=NULL)
    {
        if(tmp->scope == 0)
        {   
            if(strcmp(tmp->name, name) == 0)
                {
                    if(tmp->type == A_LIBFUNC || tmp->type == A_USERFUNC)
                    {
                        *flag = 1; /* vrethike kati ara den kanw tipota*/
                        return tmp;
                    }
                    else
                    {
                        *flag = 0; /* variable */
                        return tmp;
                    }
                }
        }
        tmp = tmp->next;
    }
    yyerror("ERROR -> did not find global");
    *flag =-1;
    return NULL;
}


Entry* LookupFunction(char *name)
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
                    return NULL; /* vrethike kati*/
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
                yyerror("ERROR -> function name already in use");
                return NULL;
            }
        }
        tmp = tmp->next;
        
    }

    /* den vrethike kati */
    /* eisagwgi */
    Entry *new;
    new=InsertionToList(yytext, scope , yylineno , A_USERFUNC);
    InsertionToStack(yytext, scope , yylineno , A_USERFUNC);
    return new;
}

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
                yyerror("ERROR -> parameter name already in use in this scope\n");
                return;
            }
        }
        tmp = tmp->next;
        
    }

    /* den vrethike kati */
    /* eisagwgi */



    tmp=InsertionToList(yytext, scope , yylineno , A_FORMAL);
    //eisagwgi sto stack stin function

    tmp->space = currscopespace();
    tmp->offset = currscopeoffset();
    
                

                

    struct Entry *new = (struct Entry *)malloc(sizeof(struct Entry));
    new->returnList=NULL;
    new->name = strdup(yytext);
    new->space = currscopespace();
    new->offset = currscopeoffset();
    

    //new->returnList=NULL;
    new->active = 1;
    //new->name = strdup(name);
    new->scope = tmp->scope;
    new->line = tmp->line;
    new->type = tmp->type;



    
    new->next=stack->formallist;
    stack->formallist=new;

    inccurrscopeoffset();

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

Entry* LookupExpression(char *name, int *flag) 
{
    struct Entry *tmp, *tmp2;
        

    //eimai mesa se synartisi
    if(stack!=NULL)
    {

        //elegxos sta dika mou formal - an vrethei OK
        tmp=stack->formallist;
        while(tmp)
        {
            if(strcmp(tmp->name, name) == 0)
            {
                *flag=0;//den einai synartisi
                return tmp;    
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
                if(tmp->type == A_LIBFUNC || tmp->type == A_USERFUNC){
                    *flag=1;
                    return tmp; /* vrethike kati ara den kanw tipota*/
                }else{
                    *flag=0;
                    return tmp;
                }
     
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
                    *flag=0;
                    return NULL;    
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
                if(tmp->type == A_USERFUNC){
                    *flag=1;
                    return tmp; /* vrethike kati ara den kanw tipota*/
                }else{
                    yyerror("ERROR -> refer to illegal variable\n");
                    *flag=0;
                    return NULL;
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
                        if(tmp->type == A_LIBFUNC || tmp->type == A_USERFUNC){
                            *flag=1;
                             return tmp; /* vrethike kati ara den kanw tipota*/
                        }else{
                            *flag=0;
                            return tmp;
                        }
       
                    }
            }
            tmp = tmp->next;
        }

        //alliws eisagwgi
        /* den vrethike kati */
        /* eisagwgi */
        Entry *sym; 
        if(scope==0)
            sym=InsertionToList(yytext, scope , yylineno , A_GLOBAL);
        else
            sym=InsertionToList(yytext, scope , yylineno , A_LOCAL);

        sym->space = currscopespace();
        sym->offset = currscopeoffset();
        inccurrscopeoffset();
                

        *flag=0;
        return sym;
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
            if(tmp->type == A_LIBFUNC || tmp->type == A_USERFUNC){
                *flag=1;
                return tmp; /* vrethike kati ara den kanw tipota*/
            }else{
                *flag=0;
                return tmp;
            }
        }
        tmp = tmp->prev;
    }

    /* den vrethike kati */
    /* eisagwgi */
    Entry *sym; 
    if(scope==0)
        sym=InsertionToList(yytext, scope , yylineno , A_GLOBAL);
    else
        sym=InsertionToList(yytext, scope , yylineno , A_LOCAL);

    sym->space = currscopespace();
    sym->offset = currscopeoffset();
    inccurrscopeoffset();
                

    *flag=0;
    return sym;

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

/*---------------------------------------*/
/*     PHASE 3 */

char *newtempname() {

    int tmp = SizeOfInt(tempcounter);
    
    char *string = (char*)malloc(sizeof(char)*(tmp+3));/* osa einai ta digits + '\0 + _t ara +3*/
    sprintf(string,"_t%d",tempcounter++);
        
    return string; 
}

void resettemp() { tempcounter = 0; }

Entry* newtemp() {
    int flag;
    char *name = newtempname();
    Entry *sym = LookupandDoLocal(name,&flag);
    return sym;
}


void expand (void){
    assert (total==currQuad);
    quad* p= (quad*) malloc(NEW_SIZE);
    if(quads){
        memcpy(p,quads,CURR_SIZE);
        free(quads);
    }
    quads=p;
    total+=EXPAND_SIZE;
}

void emit(
    iopcode op,
    expr* arg1,
    expr* arg2,
    expr* result,
    unsigned label,
    unsigned line
){
    if(currQuad==total)
        expand();

    quad* p =quads+currQuad++;
    p->op=op;
    p->arg1=arg1;
    p->arg2=arg2;
    p->result=result;
    p->label=label;
    p->line=line;
}

expr * emit_iftableitem(expr * e)
{
    if(e->type != tableitem_e)
    {
        return e;
    }
    else
    {
        expr* result = newexpr(var_e);
        result->sym = newtemp();
        emit(
            tablegetelem,
            e,
            e->index,
            result,0,yylineno
        );
        return result;
    }
    return NULL;
}

expr* member_item(expr *lvalue, char *name)
{
    lvalue = emit_iftableitem(lvalue); 
    expr *item = newexpr(tableitem_e);
    item->sym = lvalue->sym;
    item->index = newexpr_conststring(name);
    return item;
}

expr *newexpr(expr_t t)
{
    expr* e = (expr*)malloc(sizeof(expr));
    memset(e,0,sizeof(expr));
    e->type = t;
    return e;
}

expr *newexpr_conststring(char *s)
{
    expr *e = newexpr(conststring_e);
    e->strConst = strdup(s);
    return e;
}

expr* make_call (expr* lv, expr* reversed_elist) {
    expr* func = emit_iftableitem(lv);
    while (reversed_elist) {
        emit(param, reversed_elist, NULL, NULL, 0 , yylineno);
        reversed_elist = reversed_elist->next;
    }
    emit(call, func, NULL, NULL,  0 , yylineno);
    expr* result = newexpr(var_e);
    result->sym = newtemp();
    emit(getretval, result, NULL, NULL,  0 , yylineno);
    return result;
}

expr* get_last(expr* elist){
    struct expr *tmp = elist;
    if(tmp == NULL)return NULL;
    while(tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    return tmp;
}


/*
struct quad{
	iopcode op;
	expr* result;
	expr* arg1;
	expr* arg2;
	unsigned label;
	unsigned line;
};
*/

void exprPrinter(struct expr *head)
{
    if(head!=NULL){
        if(head->type==tableitem_e||head->type==boolexpr_e||head->type==var_e||head->type==programfunc_e||head->type==libraryfunc_e||head->type==assignexpr_e){
            if(head->sym==NULL)assert(NULL);
            printf("%s ", head->sym->name);  
        }


        if(head->type==arithexpr_e){
            if(head->sym==NULL)assert(NULL);
            printf("%s ", head->sym->name);  
        }

        
        if(head->type==newtable_e){
            if(head->sym==NULL)assert(NULL);
            printf("%s ", head->sym->name);  
        }


        if(head->type==constnum_e){
            printf("%f ", head->numConst);
        }else if(head->type==conststring_e){
            printf("\"");
            printf("%s", head->strConst);
            printf("\" ");
        }else if(head->type==constbool_e){
            if(head->boolConst==1){
                printf("true ");
            }else{
                printf("false ");
            }
        }

        if(head->type==nil_e){
            printf("nil ");
        }
    }
    
}


/*
enum iopcode
{
    assign, add, sub,
    mul, divv, mod,
    uminus, and, or,
    not, if_eq, if_noteq,
    if_lesseq, if_greatereq, if_less,
    if_greater, call, param,
    ret, getretval, funcstart,
    funcend, tablecreate,tablegetelem,tablesetelem
};

*/

int nextquad(){return currQuad;}


void quadPrinter()
{
    quad *p;
    for(int i=0;i<currQuad;i++)
    {   
        
        printf("%d: ",i);
        p = &quads[i];
        
        if(p->op == assign)
        {
            printf("assign ");
        }
        else if(p->op == add){printf("add ");}
        else if(p->op == sub){printf("sub ");}
        else if(p->op == mul){printf("mul ");}
        else if(p->op == divv){printf("divv ");}
        else if(p->op == mod){printf("mod ");}
        else if(p->op == uminus){printf("uminus ");}
        else if(p->op == and){printf("and ");}
        else if(p->op == or){printf("or ");}
        else if(p->op == not){printf("not ");}
        else if(p->op == if_eq){printf("if_eq ");}
        else if(p->op == if_noteq){printf("if_noteq ");}
        else if(p->op == if_lesseq){printf("if_lesseq ");}
        else if(p->op == if_greatereq){printf("if_greatereq ");}
        else if(p->op == if_less){printf("if_less ");}
        else if(p->op == if_greater){printf("if_greater ");}
        else if(p->op == call){printf("call ");}
        else if(p->op == param){printf("param ");}
        else if(p->op == ret){printf("ret ");}
        else if(p->op == getretval){printf("getretval ");}
        else if(p->op == funcstart){printf("funcstart ");}
        else if(p->op == tablecreate){printf("tablecreate ");}
        else if(p->op == tablegetelem){printf("tablegetelem ");}
        else if(p->op == tablesetelem){printf("tablesetelem ");}
        else if(p->op == jump){printf("jump ");}
        else if(p->op == funcend){printf("funcend ");}
        else if(p->op == ret){printf("ret ");}
        else{
            printf("%d", p->op);
        }
        exprPrinter(p->result);
        exprPrinter(p->arg1);
        exprPrinter(p->arg2);
        if(p->op>=if_eq){printf("%d " , p->label);}
        printf("\n");
    }
}


expr* newexpr_constnum(double i)
{
    expr *e = newexpr(constnum_e);
    e->numConst = i;
    return e;
}


expr* newexpr_constboolean(char *b)
{
    expr *e = newexpr(constbool_e);
    if(!strcmp(b,"true")){
        e->boolConst = 1;
    }else{
        e->boolConst = 0;
    }
    return e;
}

expr *newexpr_constnill()
{
    expr *e = newexpr(nil_e);
    //e->numConst = i;
    return e;
}


void check_arith (expr* e, const char* context) 
{
    if ( e->type == constbool_e ||
    e->type == conststring_e ||
    e->type == nil_e ||
    e->type == newtable_e ||
    e->type == programfunc_e ||
    e->type == libraryfunc_e ||
    e->type == boolexpr_e )
    printf("Illegal expr used in %s!", context);
}

void resetformalargsoffset(void){formalArgOffset=0;}

void resetfunctionlocaloffset(void)
{
    functionLocalOffset =0;
}

void restorecurrscopeoffset(unsigned n){
    switch(currscopespace()){
        case programvar : programVarOffset = n;break;
        case functionlocal : functionLocalOffset = n;break;
        case formalarg : formalArgOffset = n;break;
        default : assert(0);
    }
}

unsigned nextquadlabel(void)
{
    return currQuad;
}

void patchlabel(unsigned quadNo,unsigned label)
{
    assert(quadNo < currQuad);
    quads[quadNo].label = label;
}


int yyerror(char *yaccProvidedMessage)
{
    fprintf(stderr, "\n\n\t\t%s: at line %d, before token: %s\n" , yaccProvidedMessage,yylineno,yytext);
    fprintf(stderr, "\t\tINPUT NOT VALID\n\n\n");

    exit(1);
}

struct call * make_new_call(){
    struct call* tmp =malloc(sizeof(struct call));
    return tmp;
}

void binary_write_string(FILE *file_abc, char *s){
    int length = strlen(s)+1;//for '\0'
    fwrite(&length , sizeof(int) , 1 , file_abc);
    fwrite(s, sizeof(char) , length , file_abc);
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
    quadPrinter();
 
    instructionPrinter();
 

    FILE* file_abc = fopen("alpha_binary_code.abc", "wb");

    int magicnumber=340200501;
    fwrite(&magicnumber,sizeof(magicnumber),1,file_abc);
    
    //need to allocate global space in stack
    fwrite(&programVarOffset,sizeof(programVarOffset),1,file_abc);

    fwrite(&totalStringConsts,sizeof(totalStringConsts),1,file_abc);
   
    for(int i=0;i<totalStringConsts;i++)
    {
        binary_write_string(file_abc,stringConsts[i]);
    }

    fwrite(&totalNumConsts , sizeof(totalNumConsts) , 1, file_abc);
    fwrite(numConsts, sizeof(double), totalNumConsts, file_abc);    

    fwrite(&totalUserFuncs , sizeof(totalUserFuncs) , 1 , file_abc);
//    fwrite(&userFuncs , sizeof(userFuncs) , totalUserFuncs , file_abc);
    for(int i=0;i<totalUserFuncs;i++)
    {
        fwrite(&userFuncs[i].address, sizeof(userFuncs[i].address), 1, file_abc);    
        fwrite(&userFuncs[i].localSize, sizeof(userFuncs[i].localSize), 1, file_abc);    
        binary_write_string(file_abc,userFuncs[i].id);
        
    }

    fwrite(&totalNamedLibfuncs,sizeof(totalNamedLibfuncs),1,file_abc);
   
    for(int i=0;i<totalNamedLibfuncs;i++)
    {
        binary_write_string(file_abc,namedLibfuncs[i]);
    }

    totalInstructions=currInstruction;
    fwrite(&totalInstructions , sizeof(totalInstructions) , 1, file_abc);
    
    for(int i=0;i<totalInstructions;i++)
    {
        fwrite(&instructions[i].opcode , sizeof(instructions[i].opcode) , 1, file_abc);
        fwrite(&instructions[i].result , sizeof(instructions[i].result) , 1, file_abc);
        fwrite(&instructions[i].arg1 , sizeof(instructions[i].arg1) , 1, file_abc);
        fwrite(&instructions[i].arg2 , sizeof(instructions[i].arg2) , 1, file_abc);
        fwrite(&instructions[i].srcLine , sizeof(instructions[i].srcLine) , 1, file_abc);
    }

    fclose(file_abc);

    return 0;
}

/*double * numConsts;
unsigned totalNumConsts;

char ** stringConsts;
unsigned totalStringConsts;

char ** namedLibfuncs;
unsigned totalNamedLibfuncs;

userfunc* userFuncs;
unsigned totalUserFuncs;*/


expr* lvalue_expr(Entry *sym)
{
    assert(sym);
    expr *e = (expr*)malloc(sizeof(expr));
    memset(e,0,sizeof(expr));
    e->next = (expr *) 0;
    e->sym = sym;

//antistoixizoume ta types tis deyteris fasis me ayta tis tritis
//otan dimiourgoume ena expr
    if(sym->type==A_GLOBAL){
        e->type = var_e; 
    }else if(sym->type==A_LOCAL){
        e->type = var_e; 
    }else if(sym->type==A_FORMAL){
        e->type = var_e; 
    }else if(sym->type==A_USERFUNC){
        e->type = programfunc_e;
    }else if(sym->type==A_LIBFUNC){
        e->type = libraryfunc_e;
    } 
/*
    switch(sym->type){
        case var_s : e->type = var_e; break;
        case programfunc_s : e->type = programfunc_e; break;
        case libraryfunc_s : e->type = libraryfunc_e;break;
        default: assert(0);
    }*/
    return e;
}

unsigned currscopeoffset(void)
{
    switch(currscopespace()){
        case programvar : return programVarOffset;
        case functionlocal : return functionLocalOffset;
        case formalarg : return formalArgOffset;
        default : assert(0);
    }
}

void inccurrscopeoffset(void)
{
    switch(currscopespace()){
        case programvar : ++programVarOffset;break;
        case functionlocal : ++functionLocalOffset;break;
        case formalarg : ++formalArgOffset; break;
        default: assert(0);
    }
}

void enterscopespace(void)
{
    ++scopeSpaceCounter;
}

void exitscopespace(void)
{
    assert(scopeSpaceCounter>1);
    --scopeSpaceCounter;
}


scopespace_t currscopespace(void){
    if(scopeSpaceCounter==1)
        return programvar;
    else 
    if (scopeSpaceCounter%2==0)
        return formalarg;
    else
        return functionlocal;
}

void PushStackOffset(int x)
{
    struct StackOffset *new = (struct StackOffset *)malloc(sizeof(struct StackOffset));
    new->next = NULL;
    new->x=x;
    if(stackoffsethead == NULL)
    {
        stackoffsethead = new;
        return;
    }
    new->next = stackoffsethead;
    stackoffsethead=new;
}

int pop_and_top()
{
    struct StackOffset *tmp;
    tmp = stackoffsethead;
    stackoffsethead = stackoffsethead->next;
    return tmp->x;
}


expr* reverse(expr* head)
{
    expr* head2=NULL;//stack
    expr* tmp;
    
    while(head != NULL)
    {
        tmp=head->next;//krataw to vima

        //push stin head2
        head->next=head2;
        head2=head;

        head=tmp;
    }

    return head2;

}


void addtoelemlist(expr *expr1,expr *expr2)
{
    struct elemlist *new = (struct elemlist *)malloc(sizeof(struct elemlist));
    new->next = NULL;
    new->expr1 = expr1;
    new->expr2 = expr2;

    if(elemlisthead != NULL)
    {
        struct elemlist *tmp = elemlisthead;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        tmp->next = new;
        return;
    }

    elemlisthead = new;

}

struct elemlist* reverse2(struct elemlist* head)
{
    struct elemlist* head2=NULL;//stack
    struct elemlist* tmp;
    
    while(head != NULL)
    {
        tmp=head->next;//krataw to vima

        //push stin head2
        head->next=head2;
        head2=head;

        head=tmp;
    }
    return head2;
}

/*
void patchlabel (unsigned quadNo, unsigned label) 
{
    assert(quadNo < currQuad && !quads[quadNo].label);
    quads[quadNo].label = label;
}

expr* newexpr_constbool (unsigned int b) 
{
    expr* e = newexpr(constbool_e);
    e->boolConst = !!b;
    return e;
}


unsigned nextquad (void) { return currQuad;}*/


expr* newexpr_constbool (unsigned int b) 
{
    expr* e = newexpr(constbool_e);
    e->boolConst = !!b;
    return e;
}


stmt_t* create_stmt(){
    stmt_t* s=malloc(sizeof(stmt_t));
    return s;
}

void make_stmt (stmt_t* s){     
        s->breaklist = 0;
        s->contlist = 0;      
}

int newlist (int i){ quads[i].label = 0; return i; }


int mergelist (int l1, int l2) {
    if (!l1)return l2;
    else
        if (!l2)return l1;
        else {
            int i = l1;
            while (quads[i].label)
            i = quads[i].label;
            quads[i].label = l2;
            return l1;
        }
}

void patchlist (int list, int label) 
{
    while (list)
    {
        int next = quads[list].label;
        quads[list].label = label;
        list = next;
    }
}

/* PHASE 4 */

/*
//num consts
double * numConsts;
unsigned totalNumConsts;

//string consts
char ** stringConsts;
unsigned totalStringConsts;

//libfunctions consts
char ** namedLibfuncs;
unsigned totalNamedLibfuncs;

//userfunctions consts
userfunc* userFuncs;
unsigned totalUserFuncs;


*/

int number_capacity=1;

unsigned consts_newnumber (double s)
{
    //anazitisi
    int i=0;
    while(i < totalNumConsts)
    {
        if(numConsts[i] == s)
        {
            return i;
        }
        i++;
    }

    //desmeysi xwrou an xreiazetai
    if(totalNumConsts+1 == number_capacity)
    {
        number_capacity=number_capacity*2;
        numConsts = (double *)realloc(numConsts, sizeof(double)*number_capacity);
    }

    

    //eisagwgi
    numConsts[totalNumConsts] = s;
    ++totalNumConsts;
    return totalNumConsts-1;

}



int strings_capacity=1;

unsigned consts_newstring(char *s)
{
    //anazitisi
    int i=0;
    while(i < totalStringConsts)
    {
        if(strcmp(stringConsts[i], s)==0)
        {
            return i;
        }
        i++;
    }

    //desmeysi xwrou an xreiazetai
    if(totalStringConsts+1 == strings_capacity)
    {
        strings_capacity=strings_capacity*2;
        stringConsts = (char**)realloc(stringConsts, sizeof(char*)*strings_capacity);
    }

    

    //eisagwgi
    stringConsts[totalStringConsts] = s;
    ++totalStringConsts;
    return totalStringConsts-1;
}



int libfuncs_capacity=1;


unsigned libfuncs_newused(char *s)
{
    //anazitisi
    int i=0;
    while(i < totalNamedLibfuncs)
    {
        if(strcmp(namedLibfuncs[i], s)==0)
        {
            return i;
        }
        i++;
    }

    //desmeysi xwrou an xreiazetai
    if(totalNamedLibfuncs+1 == libfuncs_capacity)
    {
        libfuncs_capacity=libfuncs_capacity*2;
        namedLibfuncs = (char**)realloc(namedLibfuncs, sizeof(char*)*libfuncs_capacity);
    }

    

    //eisagwgi
    namedLibfuncs[totalNamedLibfuncs] = s;
    ++totalNamedLibfuncs;
    return totalNamedLibfuncs-1;
}

int userfuncs_capacity=1;
unsigned userfuncs_newfunc(Entry *sym){

    //anazitisi
    int i=0;
    while(i < totalUserFuncs)
    {
        if(userFuncs[i].address == sym->taddress)
        {
            return i;
        }
        i++;
    }

    //desmeysi xwrou an xreiazetai
    if(totalUserFuncs+1 == userfuncs_capacity)
    {
        userfuncs_capacity=userfuncs_capacity*2;
        userFuncs = (struct userfunc*)realloc(userFuncs, sizeof(struct userfunc)*userfuncs_capacity);
    }    

    //eisagwgi
    userFuncs[totalUserFuncs].address = sym->taddress;
    userFuncs[totalUserFuncs].localSize = sym->totalLocals;
    userFuncs[totalUserFuncs].id = sym->name;

    ++totalUserFuncs;
    return totalUserFuncs-1;


}

//silde 12
void make_numberoperand (vmarg* arg, double val){
	arg->memory=1;
    arg->val=consts_newnumber(val);
	arg->type=number_a;
    sprintf(arg->description, "%.3f", val);
}

void make_booloperand (vmarg* arg, unsigned val){
	arg->val=val;
	arg->type=bool_a;
    if(arg->val==1){
        strcpy(arg->description, "true");
    }else{
        strcpy(arg->description, "false");
    }
                
}

void make_retvaloperand(vmarg* arg){
	arg->type=retval_a;
}
/*
typedef struct incomplete_jump{
	unsigned instrNo;
	unsigned iaddress;
	struct incomplete_jump* next;
}incomplete_jump;

incomplete_jump* ij_head=(incomplete_jump*) 0;
*/
void add_incomplete_jump(unsigned instrNo, unsigned iaddress){
    
    struct incomplete_jump *tmp = ij_head;
    struct incomplete_jump *new = (struct incomplete_jump *)malloc(sizeof(incomplete_jump));
    new->instrNo = instrNo;
    new->iaddress = iaddress;
    new->next = NULL;
    if(ij_head == NULL)
    {
        ij_head = new;
        return;
    }

    while(tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = new;
}

/*typedef struct incomplete_jump{
	unsigned instrNo;
	unsigned iaddress;
	struct incomplete_jump* next;
}incomplete_jump;

incomplete_jump* ij_head=(incomplete_jump*) 0;*/

void patch_incomplete_jumps() {
    /*
    for each incomplete jump x do {
    if x.iaddress = intermediate code size then
    instructions[x.instrNo].result = target code size;
    else
    instructions[x.instrNo].result = quads[x.iaddress].taddress;
    }
    
*/
    struct incomplete_jump *tmp = ij_head;
    while(tmp != NULL)
    {
        if(tmp->iaddress == nextquadlabel()){
            instructions[tmp->instrNo].result.val =  nextinstructionlabel();
        }else{
            instructions[tmp->instrNo].result.val =  quads[tmp->iaddress].taddress;
        }
        

        tmp = tmp->next;
    }
}

/* oles oi generate metatrepoun ena quad se instruction */ 
 void generate_ADD (quad* quadi){generateprakseis(add_v, quadi);}
 void generate_SUB (quad* quadi){generateprakseis(sub_v, quadi);}
 void generate_MUL (quad* quadi){generateprakseis(mul_v, quadi);}
 void generate_DIV (quad* quadi){generateprakseis(div_v, quadi);}
 void generate_MOD (quad* quadi){generateprakseis(mod_v, quadi);}
 void generate_NEWTABLE (quad* quadi){generateprakseis(newtable_v, quadi);}
 void generate_TABLEGETELEM (quad* quadi){generateprakseis(tablegetelem_v, quadi);}
 void generate_TABLESETELEM (quad* quadi){generateprakseis(tablesetelem_v, quadi);}
 void generate_ASSIGN (quad* quadi){generateprakseis(assign_v, quadi);}
 void generate_NOP (quad* quadi){instruction t;t.opcode = nop_v; emitInstructions(t);}
 void generate_JUMP (quad* quadi){generate_relational(jump_v,quadi);} 
 void generate_IF_EQ (quad* quadi){generate_relational(jeq_v,quadi);}
 void generate_IF_NOTEQ (quad* quadi){generate_relational(jne_v,quadi);}
 void generate_IF_GREATER (quad* quadi){generate_relational(jgt_v,quadi);}
 void generate_IF_GREATEREQ (quad* quadi){generate_relational(jge_v,quadi);}
 void generate_IF_LESS (quad* quadi){generate_relational(jlt_v,quadi);}
 void generate_IF_LESSEQ (quad* quadi){generate_relational(jle_v,quadi);}
 void generate_NOT (quad* quadi){
    quadi->taddress = nextinstructionlabel();
    
    instruction t;
    
    t.opcode = jeq_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;

    make_operand(quadi->arg1, &t.arg1);
    make_booloperand(&t.arg2, 0);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel()+3;
    emitInstructions(t);
    
    t.opcode = assign_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    make_booloperand(&t.arg1, 0);
    reset_operand(&t.arg2);
    make_operand(quadi->result, &t.result);
    emitInstructions(t); 
    
    t.opcode = jump_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    reset_operand (&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel()+2;
    emitInstructions(t);
    
    t.opcode = assign_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    make_booloperand(&t.arg1, 1);
    reset_operand(&t.arg2);
    make_operand(quadi->result, &t.result);
    emitInstructions(t); 
    
 }

 void generate_OR (quad* quadi){
    quadi->taddress = nextinstructionlabel();
    instruction t;

    t.opcode = jeq_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    make_operand(quadi->arg1, &t.arg1);
    make_booloperand(&t.arg2, 1);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel()+4;
    emitInstructions(t);
    
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    make_operand(quadi->arg2, &t.arg1);
    t.result.val = nextinstructionlabel()+3;
    emitInstructions(t);

    t.opcode = assign_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    make_booloperand(&t.arg1, 0);
    reset_operand(&t.arg2);
    make_operand(quadi->result, &t.result);
    emitInstructions(t);

    t.opcode = jump_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    reset_operand (&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel()+2;
    emitInstructions(t);

    t.opcode = assign_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    make_booloperand(&t.arg1, 1);
    reset_operand(&t.arg2);
    make_operand(quadi->result, &t.result);
    emitInstructions(t);
 }
 
 void generate_AND (quad* quadi){
    quadi->taddress = nextinstructionlabel();
    instruction t;

    t.opcode = jeq_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    make_operand(quadi->arg1, &t.arg1);
    make_booloperand(&t.arg2, 0);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel()+4;
    emitInstructions(t);
    
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    make_operand(quadi->arg2, &t.arg1);
    t.result.val = nextinstructionlabel()+3;
    emitInstructions(t);

    t.opcode = assign_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    make_booloperand(&t.arg1, 1);
    reset_operand(&t.arg2);
    make_operand(quadi->result, &t.result);
    emitInstructions(t);

    t.opcode = jump_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    reset_operand (&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val = nextinstructionlabel()+2;
    emitInstructions(t);

    t.opcode = assign_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    make_booloperand(&t.arg1, 0);
    reset_operand(&t.arg2);
    make_operand(quadi->result, &t.result);
    emitInstructions(t);
 }
 
 
 
 void generate_PARAM (quad* quadi){
    quadi->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = pusharg_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    make_operand(quadi->arg1, &t.arg1);
    reset_operand(&t.arg2);
    reset_operand(&t.result);

    emitInstructions(t);
 }
 void generate_CALL (quad* quadi){
    quadi->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = call_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    make_operand(quadi->arg1, &t.arg1);
    reset_operand(&t.arg2);
    reset_operand(&t.result);
    emitInstructions(t); 
 }
 void generate_GETRETVAL (quad* quadi){
    quadi->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = assign_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    make_operand(quadi->arg1, &t.result);
    make_retvaloperand(&t.arg1);
    reset_operand(&t.arg2);
    
    emitInstructions(t);
 }

 void generate_FUNCSTART (quad* quadi){
    Entry *f = quadi->arg1->sym;
    f->taddress = nextinstructionlabel();
    quadi->taddress = nextinstructionlabel();

    pushfuncstack(f);

    instruction t;
    t.opcode = funcenter_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    make_operand(quadi->arg1 , &t.result);
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    emitInstructions(t);
 }

 void append(Entry *f, unsigned instrNo){

    //eisagwgi sto f->returnList

    struct returnListNode *tmp = f->returnList;
    struct returnListNode *new = (struct returnListNode *)malloc(sizeof(struct returnListNode));
    new->instrNo = instrNo;
    new->next = NULL;

    if(tmp == NULL)
    {
        f->returnList = new;
        return;
    }

    while(tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = new;
 }

 void generate_RETURN (quad* quadi){
    quadi->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = assign_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    make_retvaloperand(&t.result);
    make_operand(quadi->arg1, &t.arg1);
    reset_operand(&t.arg2);
    emitInstructions(t);

    Entry *f = topfuncstack();
    append(f,nextinstructionlabel());
    
    t.opcode = jump_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    t.result.type = label_a;
    t.result.val=0;
    emitInstructions(t);
 }

void backpatch(Entry *f, unsigned instrNo){
    struct returnListNode * tmp = f->returnList;
    while(tmp != NULL)
    {
        instructions[tmp->instrNo].result.val=instrNo;
        tmp = tmp->next;
    }
} 

 void generate_FUNCEND (quad* quadi){
    Entry *f = popfuncstack();
    backpatch(f,nextinstructionlabel());

    quadi->taddress = nextinstructionlabel();
    instruction t;
    t.opcode = funcexit_v;
    t.arg1.memory=t.arg2.memory=t.result.memory=1;
    make_operand(quadi->arg1 , &t.result);
    reset_operand(&t.arg1);
    reset_operand(&t.arg2);
    emitInstructions(t);
 }

 void generate_UMINUS (quad* quadi){
    instruction t;
    t.opcode = mul_v;
    make_operand(quadi->arg1, &t.arg1);
    make_numberoperand(&t.arg2,-1);
    make_operand(quadi->result, &t.result);
    quadi->taddress = nextinstructionlabel();
    emitInstructions(t);
 }

 

void generateprakseis(vmopcode op, struct quad* quad){
    instruction t;
    t.opcode = op;
    make_operand(quad->arg1, &t.arg1);
    make_operand(quad->arg2, &t.arg2);
    make_operand(quad->result, &t.result);
    quad->taddress = nextinstructionlabel();
    emitInstructions(t);
}


void generate_relational(vmopcode op, struct quad* quad)
{
    instruction t;
    t.opcode = op;
    t.arg1.memory = t.arg2.memory = t.result.memory = 1;
    make_operand(quad->arg1,&t.arg1);
    make_operand(quad->arg2,&t.arg2);
    t.result.type = label_a;
    t.result.val=0;
    if(quad->label < currprocessedquad())
    {
        t.result.val = quads[quad->label].taddress;
    }
    else
    {
        add_incomplete_jump(nextinstructionlabel(),quad->label);
       
    }
    quad->taddress = nextinstructionlabel();
    emitInstructions(t);
}



/* metatrepei ena expr se vmarg */
void make_operand (expr* e, vmarg* arg){
	
    if(e!=0){
        strcpy(arg->description, "\0");
        switch (e->type){

            case var_e:
            case tableitem_e:
            case arithexpr_e:
            case boolexpr_e:
            case newtable_e:
            case assignexpr_e:{

                assert (e->sym);
                arg->val=e->sym->offset;

                if(strcmp(e->sym->name,"z")==0){
                    printf("test");
                }


                switch(e->sym->space){
                    case programvar: arg->type = global_a; break;
                    case functionlocal: arg->type = local_a; break;
                    case formalarg: arg->type = formal_a; break;
                    default: assert(0);
                }
                strcpy(arg->description, e->sym->name);
                break;
            }

            case constbool_e:{
                arg->val = e->boolConst;
                arg->type = bool_a; 
                
                if(e->boolConst==1){
                    strcpy(arg->description, "true");
                }else{
                    strcpy(arg->description, "false");
                }
                break;
            }

            case conststring_e:{
                arg->val = consts_newstring(e->strConst);
                arg->type = string_a; 
                strcpy(arg->description, e->strConst);
                break;
            }

            case constnum_e:{
                arg->val = consts_newnumber(e->numConst);
                arg->type = number_a; 
                sprintf(arg->description, "%.3f", e->numConst);
                break;
            }

            case nil_e: { arg->type = nil_a; 
            strcpy(arg->description, "");
            break; }

            case programfunc_e:{
                arg->type = userfunc_a;
                //arg->val = e->sym->taddress;
                arg->val = userfuncs_newfunc (e->sym);
                strcpy(arg->description, e->sym->name);
                break;
            }

            case libraryfunc_e:{
                arg->type = libfunc_a;
                arg->val = libfuncs_newused(e->sym->name);
                strcpy(arg->description, e->sym->name);
                break;
            }
            default: assert(0);
        }
        arg->memory=1;
    }else{
        strcpy(arg->description, "NULL");//
        arg->memory=0;
    }

}


int nextinstructionlabel(){
    return currInstruction;
}


void expandInstructions (void){
    assert (totalInstructions==currInstruction);
    instruction* p= (instruction*) malloc(NEW_SIZE_INSTRUCTION);
    if(instructions){
        memcpy(p,instructions,CURR_SIZE_INSTRUCTION);
        free(instructions);
    }
    instructions=p;
    totalInstructions+=EXPAND_SIZE_INSTRUCTION;
}

void emitInstructions(
    instruction i
){
    if(currInstruction==totalInstructions)
        expandInstructions();

    instruction* p =instructions+currInstruction++;
    *p=i;
    
}


/*typedef struct instruction{
    vmopcode opcode;
    vmarg result;
    vmarg arg1;
    vmarg arg2;
    unsigned srcLine;
}instruction;*/

/*


    label_a = 0,
    global_a = 1,
    formal_a = 2,
    local_a = 3,
    number_a = 4,
    string_a = 5,
    bool_a = 6,
    nil_a = 7,
    userfunc_a = 8,
    libfunc_a = 9,
    retval_a = 10,
*/


void argPrinter(vmarg v){

    if(v.memory==1){

        if(v.type==global_a){
            printf("%d(%s), ", v.type, "global_a");
        }else if(v.type==label_a){
            printf("%d(%s), ", v.type, "label_a");
        }else if(v.type==formal_a){
            printf("%d(%s), ", v.type, "formal_a");
        }else if(v.type==local_a){
            printf("%d(%s), ", v.type, "local_a");
        }else if(v.type==number_a){
            printf("%d(%s), ", v.type, "number_a");
        }else if(v.type==string_a){
            printf("%d(%s), ", v.type, "string_a");
        }else if(v.type==bool_a){
            printf("%d(%s), ", v.type, "bool_a");
        }else if(v.type==nil_a){
            printf("%d(%s), ", v.type, "nil_a");
        }else if(v.type==userfunc_a){
            printf("%d(%s), ", v.type, "userfunc_a");
        }else if(v.type==libfunc_a){
            printf("%d(%s), ", v.type, "libfunc_a");
        }else if(v.type==retval_a){
            printf("%d(%s), ", v.type, "retval_a");
        }

        if(v.type!=retval_a && v.type!=label_a && v.type!=nil_a)
            printf("%d:%s", v.val,v.description);
        else
            printf("%d", v.val);

    }else{
        printf("        ");
    }

    printf("\t");

}

unsigned currprocessedquad_integer=0;
int currprocessedquad(){return currprocessedquad_integer;}

void instructionPrinter()
{
    //generate instructions before printing them
    for(currprocessedquad_integer=0;currprocessedquad_integer<currQuad;++currprocessedquad_integer)
	    (*generators[quads[currprocessedquad_integer].op])(quads+currprocessedquad_integer);

    patch_incomplete_jumps();

    instruction *p;
    for(int i=0;i<currInstruction;i++)
    {   
        
        printf("%d: ",i);
        p = &instructions[i];
        
        if(p->opcode == assign_v)
        {
            printf("assign ");
        }
        else if(p->opcode == add_v){printf("add ");}
        else if(p->opcode == sub_v){printf("sub ");}
        else if(p->opcode == mul_v){printf("mul ");}
        else if(p->opcode == div_v){printf("divv ");}
        else if(p->opcode == mod_v){printf("mod ");}
        else if(p->opcode == uminus_v){printf("uminus ");}
        else if(p->opcode == and_v){printf("and ");}
        else if(p->opcode == or_v){printf("or ");}
        else if(p->opcode == not_v){printf("not ");}
        else if(p->opcode == call_v){printf("call ");}
        else if(p->opcode == funcenter_v){printf("funcenter_v ");}
        else if(p->opcode == tablegetelem_v){printf("tablegetelem ");}
        else if(p->opcode == tablesetelem_v){printf("tablesetelem ");}
        else if(p->opcode == funcexit_v){printf("funcexit_v ");}
        else if(p->opcode == jle_v){printf("jle_v ");}
        else if(p->opcode == jgt_v){printf("jgt_v ");}
        else if(p->opcode == jeq_v){printf("jeq_v ");}
        else if(p->opcode == jge_v){printf("jge_v ");}
        else if(p->opcode == pusharg_v){printf("pusharg_v ");}
        else if(p->opcode == newtable_v){printf("newtable_v ");}
        else if(p->opcode == nop_v){printf("nop_v ");}
        else if(p->opcode == jne_v){printf("jne_v ");}
        else if(p->opcode == jlt_v){printf("jlt_v ");}
        else if(p->opcode == jump_v){printf("jump_v ");}
        else{
            printf("error missing vmopcode %d", p->opcode);
            exit(1);
        }

        printf("\t");
        argPrinter(p->result);
        argPrinter(p->arg1);
        argPrinter(p->arg2);
        
        printf("\n");
    }
}

void reset_operand(vmarg* test)
{
    test->val=0;
    test->type=0;
    test->memory=0;
}






