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

typedef struct Entry{ // symbol table
    int active;
    char *name;
    int scope;
    int line;
    enum SymbolType type;
    char *type_string;


    scopespace_t space;
    unsigned offset;
    int fscope;

    int iaddress;
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
int golbalresult = 0;


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

struct quad{ 
	iopcode op;
	expr* result;
	expr* arg1;
	expr* arg2;
	unsigned label;
	unsigned line;
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
void spacegenerator(int size);


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
   
    //$funcprefix->userORlib=1;//fasi2 
    emit(jump,NULL,NULL,NULL,0,yylineno);

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
    
    InsertionToList(yytext, scope , yylineno , A_FORMAL);
    //eisagwgi sto stack stin function

    /*

    sym->space = currscopespace();
                sym->offset = currscopeoffset();
                inccurrscopeoffset();
                

                */

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
    golbalresult = 0;
    if(head!=NULL){
        if(head->type==tableitem_e||head->type==boolexpr_e||head->type==var_e||head->type==programfunc_e||head->type==libraryfunc_e||head->type==assignexpr_e){
            if(head->sym==NULL)assert(NULL);
            printf("%s", head->sym->name);  
            golbalresult = strlen(head->sym->name);
            //printf("size of result %d" , golbalresult);
        }


        if(head->type==arithexpr_e){
            if(head->sym==NULL)assert(NULL);
            printf("%s", head->sym->name);  
            golbalresult = strlen(head->sym->name);
        }

        
        if(head->type==newtable_e){
            if(head->sym==NULL)assert(NULL);
            printf("%s", head->sym->name); 
            golbalresult = strlen(head->sym->name); 
        }


        if(head->type==constnum_e){
            printf("%.0f", head->numConst);
            golbalresult = 1;
        }else if(head->type==conststring_e){
            printf("\"");
            printf("%s", head->strConst);
            printf("\"");
            golbalresult = strlen(head->strConst) + 2;
        }else if(head->type==constbool_e){
            if(head->boolConst==1){
                printf("true");
                golbalresult = 4;
            }else{
                printf("false");
                golbalresult = 5;
            }
        }

        if(head->type==nil_e){
            printf("nil");
            golbalresult = 3;
        }
    }
    //printf("%d" , golbalresult);
    
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
    int size=0;
    printf("quad#   opcode          result          arg1          arg2          label\n--------------------------------------------------------------------------\n");
    quad *p;
    for(int i=0;i<currQuad;i++)
    {   
        //golbalresult = 0;
        if(i<10)
        {
            printf("%d:      ",i);
        }
        else
        {
            printf("%d:     ",i);
        }
        p = &quads[i];
        
        if(p->op == assign)
        {
            printf("assign ");size = 6;
        }
        else if(p->op == add){size=3;printf("add ");}
        else if(p->op == sub){size=3;printf("sub ");}
        else if(p->op == mul){size=3;printf("mul ");}
        else if(p->op == divv){size=4;printf("divv ");}
        else if(p->op == mod){size=3;printf("mod ");}
        else if(p->op == uminus){size=6;printf("uminus ");}
        else if(p->op == and){size=3;printf("and ");}
        else if(p->op == or){size=2;printf("or ");}
        else if(p->op == not){size=3;printf("not ");}
        else if(p->op == if_eq){size=5;printf("if_eq ");}
        else if(p->op == if_noteq){size=8;printf("if_noteq ");}
        else if(p->op == if_lesseq){size=9;printf("if_lesseq ");}
        else if(p->op == if_greatereq){size=12;printf("if_greatereq ");}
        else if(p->op == if_less){size=7;printf("if_less ");}
        else if(p->op == if_greater){size=10;printf("if_greater ");}
        else if(p->op == call){size=4;printf("call ");}
        else if(p->op == param){size=5;printf("param ");}
        else if(p->op == ret){size=3;printf("ret ");}
        else if(p->op == getretval){size=9;printf("getretval ");}
        else if(p->op == funcstart){size=9;printf("funcstart ");}
        else if(p->op == tablecreate){size=11;printf("tablecreate ");}
        else if(p->op == tablegetelem){size=12;printf("tablegetelem ");}
        else if(p->op == tablesetelem){size=12;printf("tablesetelem ");}
        else if(p->op == jump){size=4;printf("jump ");}
        else if(p->op == funcend){size=7;printf("funcend ");}
        else if(p->op == ret){size=3;printf("ret ");}
        else{
            size = p->op;
            printf("%d", p->op);
        }
        spacegenerator(15-size);
        //printf("size is %d " , size);
        exprPrinter(p->result);
        //printf("i");
        spacegenerator(16-golbalresult);
        //printf("%d",golbalresult);
        exprPrinter(p->arg1);
        spacegenerator(14-golbalresult);
        exprPrinter(p->arg2);
        spacegenerator(14-golbalresult);
        if(p->op>=if_eq){printf("%d " , p->label);}
        printf("\n");
    }
    printf("--------------------------------------------------------------------------");
}


void spacegenerator(int size)
{
    //printf("%dHERE",size);
    for(int i=0;i<size;i++)
    {
        printf(" ");
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
    return 0;
}


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


