%{

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
}vmarg_t;

typedef struct vmarg{
    vmarg_t type;
    unsigned val;
    char description[100];//for nice printing
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



%}

%start program

%right ASSIGN
%left OR
%left AND
%nonassoc EQUAL NOTEQUAL
%nonassoc GREATER GREATEREQUAL LESS LESSEQUAL
%left PLUS MINUS
%left MULTI DIV MOD
%right NOT DOUBLEPLUS DOUBLEMINUS U_MINUS
%left DOT DOTS
%left LEFTTETR RIGHTTETR
%left LEFTPARENTHESIS RIGHTPARENTHESIS

%union {
    struct stmt_t* stmt_t;
    struct elemlist* elemlist;
    struct call* call;
    struct FOR_struct* for_union;
    struct Entry* symbol;
    struct expr* expr;
    char* stringValue;
    int intValue;
    double realValue;
    unsigned unsignedValue;
}

/*auta ta tokens apoteloun ta termatika sumbola ths grammatikhs*/

%token <stringValue> ID  
%token <intValue> INTNUMBER 
%token <realValue> REALNUMBER 
%token <stringValue> STRING


%token IF 
%token ELSE 
%token WHILE 
%token FOR
%token FUNCTION 
%token RETURN 
%token BREAK 
%token CONTINUE 
%token AND	
%token NOT	
%token OR 
%token LOCAL 
%token TRUE
%token FALSE 
%token NIL 

%token ASSIGN 
%token PLUS 
%token MINUS 
%token MULTI
%token DIV 
%token MOD	
%token EQUAL 
%token NOTEQUAL 
%token DOUBLEPLUS 
%token DOUBLEMINUS 
%token GREATER
%token LESS 
%token GREATEREQUAL 
%token LESSEQUAL 

%token LEFTAGGILI 
%token RIGHTAGGILI 
%token LEFTTETR 
%token RIGHTTETR 
%token LEFTPARENTHESIS	
%token RIGHTPARENTHESIS 
%token SEMICOLON 
%token COMMA 
%token COLON 
%token DOUBLECOLON 
%token DOT 
%token DOTS 


%type <for_union> forprefix
%type <expr> objectdef call const lvalue assign_expr term primary expr member elist 
%type <symbol> funcdef funcprefix

%type <stringValue> FID
%type <unsignedValue> N M funcbody ifprefix elseprefix whilecond whilestart 
%type <elemlist> indexedelem indexed

%type <call> methodcall normcall callsuffix

%type <stmt_t> break_stmt continue_stmt statement statements
%type <stmt_t> for_statement while_statement if_statement return_statement block

%%

program:  init_libs statements {printf("program-statements\n");}
            ;

init_libs: {
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
;


statements: statements statement {printf("statements-statement\n");
                $$=create_stmt();
                make_stmt($$);

                $$->breaklist = mergelist($1->breaklist, $2->breaklist);
                $$->contlist = mergelist($1->contlist, $2->contlist);


            }
            | {$statements=create_stmt();make_stmt($statements);printf("statements-EMPTY\n");}
            ;


break_stmt: BREAK SEMICOLON{
                $break_stmt=create_stmt();
                make_stmt($break_stmt);
                $break_stmt->breaklist = newlist(nextquad()); 
                emit(jump,NULL,NULL,0,0,yylineno);
            }
            ;

continue_stmt: CONTINUE SEMICOLON{
                $continue_stmt=create_stmt();
                make_stmt($continue_stmt);
                $continue_stmt->contlist = newlist(nextquad()); 
                emit(jump,NULL,NULL,0,0,yylineno);
            }
            ;



statement: expr SEMICOLON {printf("statement-expr SEMICOLON\n");$$=create_stmt();make_stmt($$);}
            |if_statement {printf("statement-if_statement\n");$statement=$if_statement;}
            |while_statement {printf("statement-while_statement\n");$statement=$while_statement;}
            |for_statement {printf("statement-for_statement\n");$statement=$for_statement;}
            |return_statement {
                if(returncounter == 0)
                {
                    yyerror("ERROR -> return not in a function");                   
                }
                printf("statement-return_statement\n");
                $$=create_stmt();make_stmt($$);
            }
            |break_stmt  {          
                if(BrCnCounter == 0)
                {
                    yyerror("ERROR -> break not in loop");
                }
                printf("statement-BREAK SEMICOLON\n");
                $statement=$break_stmt;}
            |continue_stmt {       
                if(BrCnCounter == 0)
                {
                    yyerror("ERROR -> continue not in loop");
                }
                printf("statement-CONTINUE SEMICOLON\n");
                $statement=$continue_stmt;}
            |block				{printf("statement-block\n");$statement=$block;}
            |funcdef			{printf("statement-funcdef\n");$$=create_stmt();make_stmt($$);}
            |SEMICOLON			{printf("statement-SEMICOLON\n");$$=create_stmt();make_stmt($$);}
            ;

expr:      assign_expr {$$=$1;printf("expr-assign_expr\n");}
            |expr PLUS expr {printf("expr-expr PLUS expr\n");
            
                $$ = newexpr(arithexpr_e);   
                $$->sym = newtemp();
                emit(add, $1 , $3, $$, 0 , yylineno);
            
            
            }
            |expr MINUS expr {printf("expr-expr MINUS expr\n");
                
                
                $$ = newexpr(arithexpr_e);   
                $$->sym = newtemp();
                emit(sub, $1 , $3, $$, 0 , yylineno);
            
            }
            |expr MULTI expr {printf("expr-expr MULTI expr\n");
            
            
                $$ = newexpr(arithexpr_e);   
                $$->sym = newtemp();
                emit(mul, $1 , $3, $$, 0 , yylineno);
            
            
            }
            |expr DIV expr {printf("expr-expr DIV expr\n");
            
            
            
                $$ = newexpr(arithexpr_e);   
                $$->sym = newtemp();
                emit(divv, $1 , $3, $$, 0 , yylineno);
            
            }
            |expr MOD expr {printf("expr-expr MOD expr\n");
            
        
                $$ = newexpr(arithexpr_e);   
                $$->sym = newtemp();
                emit(mod, $1 , $3, $$, 0 , yylineno);
            
            }
            |expr GREATER expr {printf("expr-expr GREATER expr\n");
            
                $$ = newexpr(boolexpr_e);
                $$->sym = newtemp();
                emit(if_greater, $1, $3, NULL, nextquad()+3,yylineno);
                emit(assign, newexpr_constboolean("false"),NULL, $$,0,yylineno);
                emit(jump, NULL, NULL, NULL, nextquad()+2,yylineno);
                emit(assign, newexpr_constboolean("true"),NULL, $$,0,yylineno);
            
            
            }
            |expr GREATEREQUAL expr {printf("expr-expr GREATEREQUAL expr\n");
                
                $$ = newexpr(boolexpr_e);
                $$->sym = newtemp();
                emit(if_greatereq, $1, $3, NULL, nextquad()+3,yylineno);
                emit(assign, newexpr_constboolean("false"),NULL, $$,0,yylineno);
                emit(jump, NULL, NULL, NULL, nextquad()+2,yylineno);
                emit(assign, newexpr_constboolean("true"),NULL, $$,0,yylineno);
            
            }
            |expr LESS expr {printf("expr-expr LESS expr\n");
            
                $$ = newexpr(boolexpr_e);
                $$->sym = newtemp();
                emit(if_less, $1, $3, NULL, nextquad()+3,yylineno);
                emit(assign, newexpr_constboolean("false"),NULL, $$,0,yylineno);
                emit(jump, NULL, NULL, NULL, nextquad()+2,yylineno);
                emit(assign, newexpr_constboolean("true"),NULL, $$,0,yylineno);
            
            }
            |expr LESSEQUAL expr {printf("expr-expr LESSEQUAL expr\n");
            
                $$ = newexpr(boolexpr_e);
                $$->sym = newtemp();
                emit(if_lesseq, $1, $3, NULL, nextquad()+3,yylineno);
                emit(assign, newexpr_constboolean("false"),NULL, $$,0,yylineno);
                emit(jump, NULL, NULL, NULL, nextquad()+2,yylineno);
                emit(assign, newexpr_constboolean("true"),NULL, $$,0,yylineno);
            
            
            }
            |expr EQUAL expr {printf("expr-expr EQUAL expr\n");
            
                $$ = newexpr(boolexpr_e);
                $$->sym = newtemp();
                emit(if_eq, $1, $3, NULL, nextquad()+3,yylineno);
                emit(assign, newexpr_constboolean("false"),NULL, $$,0,yylineno);
                emit(jump, NULL, NULL, NULL, nextquad()+2,yylineno);
                emit(assign, newexpr_constboolean("true"),NULL, $$,0,yylineno);
            
            
            
            }
            |expr NOTEQUAL expr {printf("expr-expr NOTEQUAL expr\n");
                
                
                $$ = newexpr(boolexpr_e);
                $$->sym = newtemp();
                emit(if_noteq, $1, $3, NULL, nextquad()+3,yylineno);
                emit(assign, newexpr_constboolean("false"),NULL, $$,0,yylineno);
                emit(jump, NULL, NULL, NULL, nextquad()+2,yylineno);
                emit(assign, newexpr_constboolean("true"),NULL, $$,0,yylineno);
            
            
            
            }
            |expr AND expr {printf("expr-expr AND expr\n");
            
                $$ = newexpr(boolexpr_e);
                $$->sym = newtemp();
                emit(and, $1 , $3, $$, 0 , yylineno);
            
            }
            |expr OR expr {printf("expr-expr OR expr\n");
                
                
                $$ = newexpr(boolexpr_e);
                $$->sym = newtemp();
                emit(or, $1 , $3, $$,0,yylineno);
            
            }
            |term {printf("expr-TERM\n");$$=$1;}
            ;

term:      LEFTPARENTHESIS expr RIGHTPARENTHESIS 
            {$$=$2;
            printf("term-LEFTPARENTHESIS expr RIGHTPARENTHESIS\n");}
            |MINUS expr %prec U_MINUS {printf("term-MINUS\n");

                check_arith($expr, "unary minus");
                $$ = newexpr(arithexpr_e);
                $$->sym = newtemp();
                emit(uminus,$expr, NULL, $term,0,yylineno);
            
            }
            |NOT expr {printf("term-NOT\n");
            
            
                $$ = newexpr(boolexpr_e);
                $$->sym = newtemp();
                emit(not,$expr, NULL, $term,0,yylineno);
            
            
            }
            |DOUBLEPLUS lvalue {printf("term-DOUBLEPLUS lvalue\n");
                
                if($2->userORlib == 1){
                    yyerror("ERROR -> cannot modify function");
                }

                check_arith($lvalue, "++lvalue");
                if ($lvalue->type == tableitem_e) {
                    $$ = emit_iftableitem($lvalue);
                    emit(add, $$, newexpr_constnum(1), $$,0,yylineno);
                    emit(tablesetelem, $lvalue, $lvalue->index, $$,0,yylineno);
                }
                else {
                    emit(add, $lvalue, newexpr_constnum(1), $lvalue,0,yylineno);
                    $$ = newexpr(arithexpr_e);
                    $$->sym = newtemp();
                    emit(assign, $lvalue, NULL, $$,0,yylineno);
                }

            }
            |lvalue DOUBLEPLUS {printf("term-lvalue DOUBLEPLUS\n");
                if($1->userORlib == 1){
                    yyerror("ERROR -> cannot modify function");
                }


                check_arith($lvalue, "lvalue++");
                $$ = newexpr(var_e);
                $$->sym = newtemp();
                if ($lvalue->type == tableitem_e)
                {
                    expr* val = emit_iftableitem($lvalue);
                    emit(assign, val, NULL, $$,0,yylineno);
                    emit(add, val, newexpr_constnum(1), val,0,yylineno);
                    emit(tablesetelem, $lvalue, $lvalue->index, val,0,yylineno);
                }
                else 
                {
                    emit(assign, $lvalue, NULL, $$,0,yylineno);
                    emit(add, $lvalue, newexpr_constnum(1), $lvalue,0,yylineno);
                }

            
            }
            |DOUBLEMINUS lvalue {printf("term-DOUBLEMINUS lvalue\n");
                if($2->userORlib == 1){
                    yyerror("ERROR -> cannot modify function");
                }
            
            
                check_arith($lvalue, "--lvalue");
                if ($lvalue->type == tableitem_e) {
                    $$ = emit_iftableitem($lvalue);
                    emit(sub, $$, newexpr_constnum(1), $$,0,yylineno);
                    emit(tablesetelem, $lvalue, $lvalue->index, $$,0,yylineno);
                }
                else {
                    emit(sub, $lvalue, newexpr_constnum(1), $lvalue,0,yylineno);
                    $$ = newexpr(arithexpr_e);
                    $$->sym = newtemp();
                    emit(assign, $lvalue, NULL, $$,0,yylineno);
                }

            }
            |lvalue DOUBLEMINUS {printf("term-lvalue DOUBLEMINUS\n");
                if($1->userORlib == 1){
                    yyerror("ERROR -> cannot modify function");
                }
                
                check_arith($lvalue, "lvalue++");
                $$ = newexpr(var_e);
                $$->sym = newtemp();
                if ($lvalue->type == tableitem_e)
                {
                    expr* val = emit_iftableitem($lvalue);
                    emit(assign, val, NULL, $$,0,yylineno);
                    emit(sub, val, newexpr_constnum(1), val,0,yylineno);
                    emit(tablesetelem, $lvalue, $lvalue->index, val,0,yylineno);
                }
                else 
                {
                    emit(assign, $lvalue, NULL, $$,0,yylineno);
                    emit(sub, $lvalue, newexpr_constnum(1), $lvalue,0,yylineno);
                }

            }
            |primary {printf("term-primary\n");$$=$1;}
            ;

assign_expr: lvalue ASSIGN expr {
                if($1->userORlib == 1){
                    yyerror("ERROR -> cannot assign to function");
                }
                
                
                    if($lvalue->type == tableitem_e)
                    {
                        emit(
                            tablesetelem,
                            $lvalue,
                            $lvalue->index,
                            $expr,0,yylineno
                        );
                        $assign_expr = emit_iftableitem($lvalue);
                        $assign_expr->type = assignexpr_e;
                    }
                    else
                    {
                        emit(
                            assign,
                            $expr,
                            NULL,
                            $lvalue,0,yylineno
                        );
                        $assign_expr = newexpr(assignexpr_e);
                        $assign_expr->sym = newtemp();
                        emit(assign,$lvalue,NULL,$assign_expr,0,yylineno);
                    }

                printf("assign_expr-lvalue ASSIGN expr\n");
            }
            ;

primary:   lvalue {printf("primary-lvalue\n");$$=emit_iftableitem($lvalue);}
            |call {printf("primary-call\n");$primary=$call;}
            |objectdef {printf("primary-objectdef\n");$primary=$objectdef;}
            |LEFTPARENTHESIS funcdef RIGHTPARENTHESIS {
                $primary = newexpr(programfunc_e);
                $primary->sym = $funcdef;
                printf("primary-LEFTPARENTHESIS funcdef RIGHTPARENTHESIS\n");
            }
            |const {printf("primary-const\n"); $primary=$const;}
            ;

lvalue:    ID {

                printf("lvalue-ID\n");
                /*
                    userORlib = 1 otan anaferomai se userucntion h libfunc 
                    alliws miden
                
                */
                int userORlib;
                Entry * sym = LookupExpression(yytext, &userORlib);
                $$=lvalue_expr(sym);
                $$->userORlib=userORlib;

            }
            |LOCAL ID {printf("lvalue-LOCAL ID\n");
            
                /* psaxnei sto trexwn scope stin periptwsi tou local */

                int userORlib;
                Entry * sym = LookupandDoLocal(yytext, &userORlib);            
                $$=lvalue_expr(sym);
                $$->userORlib=userORlib;
            }
            |DOUBLECOLON ID {printf("lvalue-DOUBLECOLON ID\n");
                int userORlib;
                Entry * sym = LookupGlobal(yytext , &userORlib);            
                $$=lvalue_expr(sym);
                $$->userORlib=userORlib;
            }
            |member{printf("lvalue-member\n");$$=$member;}
            ;

member:    lvalue DOT ID {
                $$=member_item($lvalue, $ID);
                printf("member-lvalue DOT ID\n");
            }
            |lvalue LEFTTETR expr RIGHTTETR {
                $lvalue = emit_iftableitem($lvalue);
                $member = newexpr(tableitem_e);
                $member->sym = $lvalue->sym;
                $member->index = $expr; 
                printf("member-lvalue LEFTTETR expr RIGHTTETR\n");
            }
            |call DOT ID {
                printf("member-call DOT ID\n");
                $$=member_item($call, $ID);}
            |call LEFTTETR expr RIGHTTETR {
                printf("member-call LEFTTETR expr RIGHTTETR\n");
                $call = emit_iftableitem($call);
                $member = newexpr(tableitem_e);
                $member->sym = $call->sym;
                $member->index = $expr;
            }
            ;

call:      call LEFTPARENTHESIS elist RIGHTPARENTHESIS {
                $$ = make_call($1, $elist);
                printf("call-call LEFTPARENTHESIS elist RIGHTPARENTHESIS\n");}
            |lvalue callsuffix {
                $lvalue = emit_iftableitem($lvalue); 
                if ($callsuffix->method){
                    if($callsuffix->elist==NULL)
                        $callsuffix->elist=$lvalue;
                    else
                        get_last($callsuffix->elist)->next = $lvalue; 
                    $lvalue = emit_iftableitem(member_item($lvalue, $callsuffix->name));
                }
                $call = make_call($lvalue, $callsuffix->elist);

                printf("call-lvalue callsuffix\n");}
            |LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS {
                expr* func = newexpr(programfunc_e);
                func->sym = $funcdef;
                $call = make_call(func, $elist);
                printf("call-LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS\n");}
            ;

callsuffix: 
    normcall {
        $callsuffix = $normcall;
        printf("callsuffix-methodcall\n");
    }
    |methodcall {
        $callsuffix = $methodcall;
        printf("callsuffix-methodcall\n");
    }
    ;

normcall: LEFTPARENTHESIS elist RIGHTPARENTHESIS {
    $normcall=make_new_call();
    $normcall->elist = $elist;
    $normcall->method = 0;
    $normcall->name = NULL;
    printf("normcall-LEFT_RIGHT_PARENTHESIS\n");}
            ;

methodcall: DOTS ID LEFTPARENTHESIS elist RIGHTPARENTHESIS {
    $methodcall=make_new_call();
    $methodcall->elist = $elist;
    $methodcall->method = 1;
    $methodcall->name = strdup($ID);
    printf("methodcall-DOT ID_LEFT_RIGHT_PARENTHESIS\n");}
            ; 

elist:  expr {
            printf("ELIST-EXPR \n");
            $elist=$1;//vazw head to prwto stoixeio
            $1->next=NULL;
        }
        | elist COMMA expr {
            $$=$expr;
            //kanw LIFO
            $expr->next=$1;//vazw head kathe epomeno stoixeio 
            printf("ELIST-elist COMMA expr\n");
        }
        | {printf("ELIST-EMPTY\n");$elist=NULL;}
        ;

objectdef: LEFTTETR elist RIGHTTETR {
                expr* t = newexpr(newtable_e);
                t->sym = newtemp();
                emit(tablecreate, t, NULL, NULL,0,yylineno);
                $elist=reverse($elist);
                for (int i = 0; $elist; $elist = $elist->next)
                    emit(tablesetelem, t, newexpr_constnum(i++), $elist,0,yylineno);
                $objectdef = t;
                printf("objectdef LEFTTETR elist RIGHTTETR\n");}
            |LEFTTETR indexed RIGHTTETR {
                printf("LEFTTETR indexed RIGHTTETR\n");
                expr* t = newexpr(newtable_e);
                t->sym = newtemp();
                emit(tablecreate, t, NULL, NULL, 0,yylineno);
                //emit(tablesetelem, t, index, value);
                struct elemlist *tmp = $2;

                //foreach <index, value> in $indexed do
                $2 = reverse2($2);

                tmp = $2;
                int counter = 0;
                
                while(tmp!=NULL)
                {
                    emit(tablesetelem, t, tmp->expr1, tmp->expr2 , 0 , yylineno);
                    tmp=tmp->next;
                }
                $objectdef = t;
            }
            ;
        

indexed:   indexedelem {
                struct elemlist *new = (struct elemlist *)malloc(sizeof(struct elemlist));
                new->next = NULL;
                new->expr1 = expr1;
                new->expr2 = expr2;
                $1=new;

                //head einai to indexed   
                $indexed=$1;//vazw head to prwto stoixeio
                $1->next=NULL;    
                
                printf("indexed indexedelem\n");
            }
            | indexed COMMA indexedelem {
                struct elemlist *new = (struct elemlist *)malloc(sizeof(struct elemlist));
                new->next = NULL;
                new->expr1 = expr1;
                new->expr2 = expr2;
                $3=new;
    
                $3->next=$1;//vazw head kathe epomeno stoixeio
                $$=$3;//kanw LIFO
                printf("indexed COMMA indexedelem\n");
            }
            ;

indexedelem: LEFTAGGILI expr COLON expr RIGHTAGGILI {
                expr1=$2;
                expr2=$4;
                printf("indexedelem LEFTAGGILI expr COLON expr RIGHTAGGILI\n");}
                ;

block:     LEFTAGGILI {scope++;} statements RIGHTAGGILI {$block=$statements; printf("block LEFTAGGILI statements RIGHTAGGILI\n");Hider(scope);scope--;}
            ;


FID: ID {

        /* slide 21 */
        
        //scope++;
        $$=$ID;
    }
    | {    

        /* ftiaxnoume ena diko mas onoma synartisi */
        int tmp = SizeOfInt(fcounter);
        /*printf("\n\ntmp=%d\n", tmp);*/
        char *string = (char*)malloc(sizeof(char)*(tmp+2));/* osa einai ta digits + '\0 + $ ara +2*/
        sprintf(string,"$%d",fcounter++);
        
        //scope++;
        $$=string;       
    }
    ;

funcprefix: FUNCTION FID{

    //$funcprefix = newsymbol($funcname,function_s)
    if($FID[0]=='$'){//anonymous functions
        $funcprefix=InsertionToList($FID , scope , yylineno , A_USERFUNC);
        InsertionToStack($FID , scope , yylineno , A_USERFUNC);
    }else{
        $funcprefix=LookupFunction($FID);
    }
    scope++;

    emit(jump,NULL,NULL,NULL,0,yylineno);
    //$funcprefix->userORlib=1;//fasi2 
    $funcprefix->iaddress = nextquadlabel();
    emit(funcstart,lvalue_expr($funcprefix),NULL,NULL,0,yylineno);
    
    //push(scopeoffsetstack,currscopeoffset();)
    PushStackOffset(currscopeoffset());
    
    enterscopespace();
    resetformalargsoffset();
};

funcargs: LEFTPARENTHESIS idlist RIGHTPARENTHESIS
{
    enterscopespace();
    resetfunctionlocaloffset();
};

funcbody: CORRECT_SCOPE block {
    $funcbody = currscopeoffset();
    exitscopespace();

    pop_loopcounter();
    /*  pop  */ 
};


funcdef: funcprefix funcargs funcbody
 {
    exitscopespace(); 
    $funcprefix->totalLocals = $funcbody; 
    int offset = pop_and_top(); 
    restorecurrscopeoffset(offset); 
    $funcdef = $funcprefix; 
    emit(funcend, lvalue_expr($funcprefix), NULL, NULL, 0, yylineno);

    patchlabel($funcprefix->iaddress-1,nextquadlabel());
    
    printf("funcdef FUNCTION ID LEFTPARENTHESIS idlist RIGHTPARENTHESIS block\n");
    returncounter--;
    removeFromStack();
}
;

CORRECT_SCOPE: {returncounter++;scope--;   push_loopcounter();  }
            ;





const:     INTNUMBER {
                printf("const INTNUMBER\n");
                $const = newexpr_constnum($INTNUMBER);
            }
            |REALNUMBER {printf("const REALNUMBER\n");
                $const = newexpr_constnum($REALNUMBER);
            }
            |STRING {printf("const STRING\n");
                $const = newexpr_conststring($STRING);
            }
            |NIL {printf("const NIL\n");
                $const = newexpr_constnill();
            }
            |TRUE {printf("const TRUE\n");
                $const = newexpr_constboolean("true");
            }
            |FALSE {printf("const FALSE\n");
                $const = newexpr_constboolean("false");
            }
            ;

idlist:    ID {
        
        printf("idlist ID\n");
        LookupParameter(yytext);

    }
            | idlist COMMA ID {printf("idlist idlist COMMA ID\n"); LookupParameter(yytext);}
            | {printf("idlist empty\n");}
            ;
/*
if_statement: IF LEFTPARENTHESIS expr RIGHTPARENTHESIS statement {
    printf("if_statement IF LEFTPARENTHESIS expr RIGHTPARENTHESIS statement\n");}
                | IF LEFTPARENTHESIS expr RIGHTPARENTHESIS statement ELSE statement {
                    printf("if_statement IF LEFTPARENTHESIS expr RIGHTPARENTHESIS statement ELSE statement\n");}
                ;
*/

ifprefix: IF LEFTPARENTHESIS expr RIGHTPARENTHESIS{
    emit(if_eq, $expr , newexpr_constbool(1) , 0, nextquad()+2, yylineno);
    $ifprefix = nextquad();
    emit(jump , NULL, NULL, 0 ,0 ,yylineno);
}

if_statement: ifprefix statement{
                            patchlabel($ifprefix,nextquad());
                printf("if_statement IF LEFTPARENTHESIS expr RIGHTPARENTHESIS statement\n");
                $$=create_stmt();
                make_stmt($$);

                $$->breaklist = mergelist($2->breaklist, $$->breaklist);
                $$->contlist = mergelist($2->contlist, $$->contlist);
                }
                
                |ifprefix statement elseprefix statement{
    patchlabel($ifprefix,$elseprefix+1);
    patchlabel($elseprefix, nextquad());
printf("if_statement IF LEFTPARENTHESIS expr RIGHTPARENTHESIS statement ELSE statement\n");
$$=create_stmt();
                make_stmt($$);

                $$->breaklist = mergelist($4->breaklist, $2->breaklist);
                $$->contlist = mergelist($4->contlist, $2->contlist);
}
                ;

elseprefix: ELSE{
    $elseprefix = nextquad();
    emit(jump , NULL ,NULL , 0 , 0 , yylineno);
}  

/*
while_statement: WHILE LEFTPARENTHESIS expr RIGHTPARENTHESIS {BrCnCounter++;} statement {BrCnCounter--;}{printf("while_statement WHILE LEFTPARENTHESIS expr RIGHTPARENTHESIS statement\n");}
                    ;
*/


whilestart : WHILE{
    $whilestart = nextquad();
}                                                                                    

whilecond: LEFTPARENTHESIS expr RIGHTPARENTHESIS{
    
    emit(if_eq,$expr,newexpr_constbool(1),0,nextquad() + 2,yylineno);
    $whilecond = nextquad();
    emit(jump, NULL, NULL, 0,0,yylineno);
}

while_statement: whilestart whilecond {BrCnCounter++;} statement {BrCnCounter--;}
{printf("while_statement WHILE LEFTPARENTHESIS expr RIGHTPARENTHESIS statement\n");
    emit(jump, NULL, NULL, NULL, $whilestart,yylineno);
    patchlabel($whilecond, nextquad());
        patchlist($statement->breaklist, nextquad());
        patchlist($statement->contlist, $whilestart);
        make_stmt($statement);
        $while_statement=$statement;
    }
    ;

/*
for_statement: FOR LEFTPARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHTPARENTHESIS {BrCnCounter++;} statement {BrCnCounter--;}{printf("for_statement FOR LEFTPARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHTPARENTHESIS statement\n");}
                ;
*/

N: {$N = nextquad();emit(jump,NULL,NULL,0,0,yylineno);};
M: {$M = nextquad();};

forprefix: FOR LEFTPARENTHESIS elist SEMICOLON M expr SEMICOLON {
    struct FOR_struct FORNODE;
    $forprefix=&FORNODE;//get some memory                 
    
    $forprefix->test = $M;
    $forprefix->enter = nextquad();
    emit(if_eq, $expr, newexpr_constbool(1),0,0,yylineno);
};

for_statement: forprefix N elist RIGHTPARENTHESIS N {BrCnCounter++;} statement {BrCnCounter--;} N{
    patchlabel($forprefix->enter, $5+1);
    patchlabel($2, nextquad());
    patchlabel($5, $forprefix->test);
    patchlabel($9, $2+1); 
    patchlist($statement->breaklist, nextquad());
    patchlist($statement->contlist, $2+1);
    make_stmt($statement);
    $for_statement=$statement;
};

return_statement: RETURN expr SEMICOLON {printf("return RETURN expr SEMICOLON\n"); emit(ret, $expr, NULL,NULL,0,yylineno);}
                | RETURN SEMICOLON {printf("return_statement RETURN SEMICOLON\n"); emit(ret, NULL, NULL,NULL,0,yylineno);}
                ;


            

%%

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






