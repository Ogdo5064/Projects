%{

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

%}

%start program

//ta eixe ekfwnisi 
//proseteristikotita kai protereottita

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
char* stringValue;
int intValue;
double realValue;
}

/*auta ta tokens apoteloun ta termatika sumbola ths grammatikhs*/

%token ID  
%token INTNUMBER 
%token REALNUMBER 
%token STRING


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

%type <intValue> lvalue


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

    // sthn arxh tou symbol table einai auta ta function ths bilbiothikhs

}
;


statements: statements statement {printf("statements-statement\n");}
            | {printf("statements-EMPTY\n");}
            ;
 

statement: expr SEMICOLON {printf("statement-expr SEMICOLON\n");}
            |if_statement {printf("statement-if_statement\n");}
            |while_statement {printf("statement-while_statement\n");}
            |for_statement {printf("statement-for_statement\n");}
            |return_statement {
                if(returncounter == 0)
                {
                    yyerror("ERROR -> return not in a function");                   
                }
                printf("statement-return_statement\n");}
            |BREAK SEMICOLON  {          
                if(BrCnCounter == 0)
                {
                    yyerror("ERROR -> break not in loop");
                }
                printf("statement-BREAK SEMICOLON\n");}
            |CONTINUE SEMICOLON {       
                if(BrCnCounter == 0)
                {
                    yyerror("ERROR -> continue not in loop");
                }
                printf("statement-CONTINUE SEMICOLON\n");}
            |block				{printf("statement-block\n");}
            |funcdef			{printf("statement-funcdef\n");}
            |SEMICOLON			{printf("statement-SEMICOLON\n");}
            ;

expr:      assign_expr {printf("expr-assign_expr\n");}
            |expr PLUS expr {printf("expr-expr PLUS expr\n");}
            |expr MINUS expr {printf("expr-expr MINUS expr\n");}
            |expr MULTI expr {printf("expr-expr MULTI expr\n");}
            |expr DIV expr {printf("expr-expr DIV expr\n");}
            |expr MOD expr {printf("expr-expr MOD expr\n");}
            |expr GREATER expr {printf("expr-expr GREATER expr\n");}
            |expr GREATEREQUAL expr {printf("expr-expr GREATEREQUAL expr\n");}
            |expr LESS expr {printf("expr-expr LESS expr\n");}
            |expr LESSEQUAL expr {printf("expr-expr LESSEQUAL expr\n");}
            |expr EQUAL expr {printf("expr-expr EQUAL expr\n");}
            |expr NOTEQUAL expr {printf("expr-expr NOTEQUAL expr\n");}
            |expr AND expr {printf("expr-expr AND expr\n");}
            |expr OR expr {printf("expr-expr OR expr\n");}
            |term {printf("expr-TERM\n");}
            ;

term:      LEFTPARENTHESIS expr RIGHTPARENTHESIS {printf("term-LEFTPARENTHESIS expr RIGHTPARENTHESIS\n");}
            |MINUS expr %prec U_MINUS {printf("term-MINUS\n");}
            |NOT expr {printf("term-NOT\n");}
            |DOUBLEPLUS lvalue {printf("term-DOUBLEPLUS lvalue\n");
                if($2 == 1){ // to $2 phre timh 1 giati ekane lookup kai brhke function-libfunct 
                    yyerror("ERROR -> cannot modify function");
                }
            }
            |lvalue DOUBLEPLUS {printf("term-lvalue DOUBLEPLUS\n");
                if($1 == 1){
                    yyerror("ERROR -> cannot modify function");
                }
            
            }
            |DOUBLEMINUS lvalue {printf("term-DOUBLEMINUS lvalue\n");
                if($2 == 1){
                    yyerror("ERROR -> cannot modify function");
                }
            
            }
            |lvalue DOUBLEMINUS {printf("term-lvalue DOUBLEMINUS\n");
                if($1 == 1){
                    yyerror("ERROR -> cannot modify function");
                }
            }
            |primary {printf("term-primary\n");}
            ;

assign_expr: lvalue ASSIGN expr {
                if($1 == 1){
                    yyerror("ERROR -> cannot assign to function");
                }
    
                printf("assign_expr-lvalue ASSIGN expr\n");
            }
            ;

primary:   lvalue {printf("primary-lvalue\n");}
            |call {printf("primary-call\n");}
            |objectdef {printf("primary-objectdef\n");}
            |LEFTPARENTHESIS funcdef RIGHTPARENTHESIS {printf("primary-LEFTPARENTHESIS funcdef RIGHTPARENTHESIS\n");}
            |const {printf("primary-const\n");}
            ;

lvalue:    ID {

                printf("lvalue-ID\n");
                /*
                    userORlib = 1 otan anaferomai se userfucntion h libfunc, alliws miden
                
                */
                int userORlib = LookupExpression(yytext);
                $$=userORlib;

            }
            |LOCAL ID {printf("lvalue-LOCAL ID\n");
            
                /* psaxnei sto trexwn scope stin periptwsi tou local */

                int userORlib = LookupandDoLocal(yytext);            
                $$=userORlib;
            }
            |DOUBLECOLON ID {printf("lvalue-DOUBLECOLON ID\n");
            
                int userORlib = LookupGlobal(yytext);
                $$=userORlib;
            
            }
            |member{printf("lvalue-member\n");$$=0;}
            ;

member:    lvalue DOT ID {printf("member-lvalue DOT ID\n");}
            |lvalue LEFTTETR expr RIGHTTETR {printf("member-lvalue LEFTTETR expr RIGHTTETR\n");}
            |call DOT ID {printf("member-call DOT ID\n");}
            |call LEFTTETR expr RIGHTTETR {printf("member-call LEFTTETR expr RIGHTTETR\n");}
            ;

call:      call LEFTPARENTHESIS elist RIGHTPARENTHESIS {printf("call-call LEFTPARENTHESIS elist RIGHTPARENTHESIS\n");}
            |lvalue callsuffix {printf("call-lvalue callsuffix\n");}
            |LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS {printf("call-LEFTPARENTHESIS funcdef RIGHTPARENTHESIS LEFTPARENTHESIS elist RIGHTPARENTHESIS\n");}
            ;

callsuffix: normcall {printf("callsuffix-methodcall\n");}
            |methodcall {printf("callsuffix-methodcall\n");}
            ;

normcall:   LEFTPARENTHESIS elist RIGHTPARENTHESIS {printf("normcall-LEFT_RIGHT_PARENTHESIS\n");}
            ;

methodcall: DOTS ID LEFTPARENTHESIS elist RIGHTPARENTHESIS {printf("methodcall-DOT ID_LEFT_RIGHT_PARENTHESIS\n");}
            ; 

elist:  expr {printf("ELIST-EXPR\n");}
        | elist COMMA expr {printf("ELIST-elist COMMA expr\n");}
        | {printf("ELIST-EMPTY\n");}
        ;

objectdef: LEFTTETR elist RIGHTTETR {printf("objectdef LEFTTETR elist RIGHTTETR\n");}
            |LEFTTETR indexed RIGHTTETR {printf("LEFTTETR indexed RIGHTTETR\n");}
            ;

indexed:   indexedelem {printf("indexed indexedelem\n");}
            | indexed COMMA indexedelem {printf("indexed COMMA indexedelem\n");}
            ;

indexedelem: LEFTAGGILI expr COLON expr RIGHTAGGILI {printf("indexedelem LEFTAGGILI expr COLON expr RIGHTAGGILI\n");}
                ;

block:     LEFTAGGILI {scope++;} statements RIGHTAGGILI {printf("block LEFTAGGILI statements RIGHTAGGILI\n");Hider(scope);scope--;}
            ;

funcdef:   FUNCTION FID LEFTPARENTHESIS idlist RIGHTPARENTHESIS CORRECT_SCOPE block {
                printf("funcdef FUNCTION ID LEFTPARENTHESIS idlist RIGHTPARENTHESIS block\n");
                returncounter--;
                removeFromStack();
            }
            ;

CORRECT_SCOPE: {returncounter++;scope--;}
            ;

FID: ID {

        /* slide 21 */
        LookupFunction(yytext);
        scope++;
    }
    | {    

        /* ftiaxnoume ena diko mas onoma synarthshs */
        int tmp = SizeOfInt(fcounter);
        /*printf("\n\ntmp=%d\n", tmp);*/
        char *string = (char*)malloc(sizeof(char)*(tmp+2));/* osa einai ta digits + '\0 + $ ara +2*/
        sprintf(string,"$%d",fcounter++);
        InsertionToList(string , scope , yylineno , A_USERFUNC);
        InsertionToStack(string , scope , yylineno , A_USERFUNC);

        scope++;       
    }
    ;
     

const:     INTNUMBER {printf("const INTNUMBER\n");}
            |REALNUMBER {printf("const REALNUMBER\n");}
            |STRING {printf("const STRING\n");}
            |NIL {printf("const NIL\n");}
            |TRUE {printf("const TRUE\n");}
            |FALSE {printf("const FALSE\n");}
            ;

idlist:    ID {
        
        printf("idlist ID\n");
        LookupParameter(yytext);

    }
            | idlist COMMA ID {printf("idlist idlist COMMA ID\n"); LookupParameter(yytext);}
            | {printf("idlist empty\n");}
            ;

if_statement: IF LEFTPARENTHESIS expr RIGHTPARENTHESIS statement {printf("if_statement IF LEFTPARENTHESIS expr RIGHTPARENTHESIS statement\n");}
                | IF LEFTPARENTHESIS expr RIGHTPARENTHESIS statement ELSE statement {printf("if_statement IF LEFTPARENTHESIS expr RIGHTPARENTHESIS statement ELSE statement\n");}
                ;

while_statement: WHILE LEFTPARENTHESIS expr RIGHTPARENTHESIS {BrCnCounter++;} statement {BrCnCounter--;}{printf("while_statement WHILE LEFTPARENTHESIS expr RIGHTPARENTHESIS statement\n");}
                    ;

for_statement: FOR LEFTPARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHTPARENTHESIS {BrCnCounter++;} statement {BrCnCounter--;}{printf("for_statement FOR LEFTPARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHTPARENTHESIS statement\n");}
                ;

return_statement: RETURN expr SEMICOLON {printf(" return RETURN expr SEMICOLON\n");}
                | RETURN SEMICOLON {printf("return_statement RETURN SEMICOLON\n");}
                    ;





%%
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