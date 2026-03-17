#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

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


double * numConsts;
unsigned totalNumConsts;

char ** stringConsts;
unsigned totalStringConsts;

char ** namedLibfuncs;
unsigned totalNamedLibfuncs;

userfunc* userFuncs;
unsigned totalUserFuncs;

unsigned programVarOffset=0;
int totalInstructions = 0;

instruction* instructions = (instruction*) 0;
/* PHASE 5 */


char* binary_read_string(FILE *file_abc){
    int length;
    fread(&length , sizeof(int) , 1 , file_abc);//including '\0'
    char *s = malloc(sizeof(char)*length);
    fread(s, sizeof(char) , length , file_abc);
    return s;
}
/*
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

void instructionPrinter()
{

    instruction *p;
    for(int i=0;i<totalInstructions;i++)
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
}*/

/* FASI 5 */
//o typos tou avm_memcell
typedef enum avm_memcell_t{
	number_m=0,
	string_m =1,
	bool_m =2,
	table_m=3,
	userfunc_m=4,
	libfunc_m=5,
	nil_m=6,
	undef_m=7
}avm_memcell_t;


typedef struct avm_table avm_table;
//thesi mnimis sthn eikoniki mixani
typedef struct avm_memcell{
	avm_memcell_t type;//typos
	union{
		double numVal;//arithmos double
		char* strVal;//string
		unsigned char boolVal;//boolean
		avm_table* tableVal;//table
		unsigned funcVal;//unserfunction address
		char* libfuncVal;//library function name
	}data;
}avm_memcell;

//megethos mnimis me 4096 kelia
#define AVM_STACKSIZE 4096
#define AVM_WIPEOUT(m) memset(&(m),0,sizeof(m))

//i mnimi
avm_memcell stack[AVM_STACKSIZE];

static void avm_initstack(void){
	for(unsigned i=0;i<AVM_STACKSIZE;i++){
		AVM_WIPEOUT(stack[i]);
        stack[i].type=undef_m;
	}
}

//megethos stoivas otan kalw synartisi
unsigned top,topsp;
#define AVM_STACKENV_SIZE 4

//kataxwites
avm_memcell ax,bx,cx;//kataxwrites genikou skopou
avm_memcell retval;//gia na epistrepsw timi


double consts_getnumber(unsigned index){    return numConsts[index];}
char *consts_getstring(unsigned index){     return stringConsts[index];}
char *libfuncs_getused(unsigned index){     return namedLibfuncs[index];}
userfunc* userfuncs_getfunc(unsigned index){return &userFuncs[index];}

//opws i make operand pairnei ena vmarg kai to antistoixei se avm_memcell
avm_memcell *avm_translate_operand(vmarg* arg, avm_memcell *reg)
{
    switch(arg->type){
        case global_a: return       &stack[AVM_STACKSIZE-1-arg->val];
        case local_a:   return      &stack[topsp-arg->val];
        case formal_a: return       &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];
        case retval_a: return &retval;
        case number_a: {
            reg->type = number_m;
            reg->data.numVal = consts_getnumber(arg->val);
            return reg;
        }
        case string_a: {
            reg->type = string_m;
            reg->data.strVal = strdup(consts_getstring(arg->val));
            return reg;
        }
        case bool_a: {
            reg->type = bool_m;
            reg->data.boolVal = arg->val;
            return reg;
        }
        case nil_a: {reg->type = nil_m; return reg;}
        case userfunc_a: {
            reg->type = userfunc_m;
            reg->data.funcVal = arg->val;
            reg->data.funcVal = userfuncs_getfunc(arg->val)->address;
            return reg;
        }
        case libfunc_a:{
            reg->type = libfunc_m;
            reg->data.libfuncVal = libfuncs_getused(arg->val);
            return reg;
        }
        default: assert(0);
    }
}
//table implementation
avm_memcell* avm_tablegetelem (avm_table* table,avm_memcell* key){return NULL;}
void         avm_tablesetelem (avm_table* table,avm_memcell* key, avm_memcell* value){}

#define AVM_TABLE_HASHSIZE 211

typedef struct avm_table_bucket{
	avm_memcell key;
	avm_memcell value;
	struct avm_table_bucket* next;
}avm_table_bucket;


struct avm_table{
	unsigned refCounter;
	avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
	avm_table_bucket* numIndexed[AVM_TABLE_HASHSIZE];
	unsigned total;
};


void avm_memcellclear (avm_memcell* m);


void avm_tablebucketsdestroy(avm_table_bucket **p)
{
    for(unsigned i=0;i<AVM_TABLE_HASHSIZE;i++)
    {
        for(avm_table_bucket *b = *p; b;)
        {
            avm_table_bucket *del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = (avm_table_bucket*)0;
    }
}

void avm_tabledestroy(avm_table* t)
{
    avm_tablebucketsdestroy(t->strIndexed);
    avm_tablebucketsdestroy(t->numIndexed);
    free(t);
}

void avm_tableincrefcounter (avm_table* t)
	{ ++t->refCounter; }

void avm_tabledecrefcounter (avm_table* t){
	assert(t->refCounter > 0);
	if(! --t->refCounter)
		avm_tabledestroy(t);
}


typedef void (*memclear_func_t)(avm_memcell*);

void memclear_string (avm_memcell* m){
	assert(m->data.strVal);
	free(m->data.strVal);
}

void memclear_table(avm_memcell *m){
    assert(m->data.tableVal);
    avm_tabledecrefcounter(m->data.tableVal);
}


memclear_func_t memclearFuncs[] = {
    0,
    memclear_string,
    0,
    memclear_table,
    0,
    0,
    0,
    0
};

void avm_memcellclear (avm_memcell* m){
	if(m->type != undef_m){
		memclear_func_t f = memclearFuncs[m->type];
		if (f)
		     (*f) (m);
		m->type = undef_m;
	}
}

void avm_tablebucketsinit(avm_table_bucket** p){
	for(unsigned i=0; i<AVM_TABLE_HASHSIZE; ++i)
		p[i] = (avm_table_bucket*) 0;
}


avm_table* avm_tablenew(void){
	avm_table* t = (avm_table*) malloc(sizeof(avm_table));
	AVM_WIPEOUT(*t);

    t->refCounter = t->total = 0;
    avm_tablebucketsinit(t->numIndexed);
    avm_tablebucketsinit(t->strIndexed);

    return t;
}
//////////////////////////////////////////////////////////

//execution
unsigned char executionFinished=0;
unsigned pc=0;
unsigned currLine=0;
unsigned codeSize=0;
instruction* code =(instruction*)0;

#define AVM_ENDING_PC codeSize

unsigned totalActuals=0;
#include <stdarg.h>

void avm_error(char *format,...){
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

void avm_warning(char* format, ...){
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

//tostring for libfunc print
typedef char* (*tostring_func_t)(avm_memcell *);

char* number_tostring(avm_memcell *cell){
    
    char tostring[150];
    sprintf(tostring, "%.3f", cell->data.numVal);
    return strdup(tostring);
}

char* bool_tostring(avm_memcell *cell){

    char tostring[150];
    if(cell->data.boolVal==1){
        sprintf(tostring, "%s", "TRUE");
        return strdup(tostring);
    }else{
        sprintf(tostring, "%s", "FALSE");
        return strdup(tostring);
    }
}

char* table_tostring(avm_memcell *cell){
    char tostring[150];
    sprintf(tostring, "TABLE with tableval %p", cell->data.tableVal);
    return strdup(tostring);
}

char* userfunc_tostring(avm_memcell *cell){
    char tostring[150];
    int index = instructions[cell->data.funcVal].result.val;
    sprintf(tostring, "user function: %s with addr %d", userFuncs[index].id, userFuncs[index].address);
    return strdup(tostring);
}

char* libfunc_tostring(avm_memcell *cell){
    char tostring[150];
    sprintf(tostring, "%s", cell->data.libfuncVal);
    return strdup(tostring);
}
char* nil_tostring(avm_memcell *cell){
    char tostring[150];
    sprintf(tostring, "%s", "nil");
    return strdup(tostring);    
}
char* undef_tostring(avm_memcell *cell){
    char tostring[150];
    sprintf(tostring, "%s", "undef");
    return strdup(tostring);
}
char* string_tostring(avm_memcell *cell){
    char tostring[150];
    sprintf(tostring, "%s", cell->data.strVal);
    return strdup(tostring);
}

tostring_func_t tostringFuncs[]={
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring,
    libfunc_tostring,
    nil_tostring,
    undef_tostring
};

char *avm_tostring(avm_memcell * m){
    assert(m->type >=0 && m->type <= undef_m);
    return(*tostringFuncs[m->type])(m);
}

void avm_callsaveenvironment(void);

void avm_dec_top(void){
	if(!top){
		avm_error("stack overflow");
		executionFinished=1;
	}
	else
		--top;
}

void avm_push_table_arg(avm_table *t){
    stack[top].type = table_m;
    avm_tableincrefcounter(stack[top].data.tableVal = t);
    ++totalActuals;
    avm_dec_top();
}

void avm_call_functor(avm_table *t){
    cx.type = string_m;
    cx.data.strVal = "()";
    avm_memcell *f = avm_tablegetelem(t,&cx);
    if(!f)
        avm_error("in calling tabler: no '()' element found!");
    else
        if(f->type == table_m)
            avm_call_functor(f->data.tableVal);
        else
            if(f->type == userfunc_a){
                avm_push_table_arg(t);
                avm_callsaveenvironment();
                pc = f->data.funcVal;
                assert(pc < AVM_ENDING_PC && code[pc].opcode == funcenter_v);
            }
            else
                avm_error("in calling table: illegal '()' element value!");
}


void avm_push_envvalue(unsigned val){
	stack[top].type=number_m;
	stack[top].data.numVal=val;
	avm_dec_top();
}

void avm_callsaveenvironment(void){
	avm_push_envvalue(totalActuals);//n slide 34
	assert(code[pc].opcode==call_v);
	avm_push_envvalue(pc+1);//ret address
	avm_push_envvalue(top+totalActuals+2);//previous top
	avm_push_envvalue(topsp);//previous topsp
}

typedef void (*execute_func_t)(instruction*);

#define AVM_MAX_INSTRUCTION (unsigned) jump_v

extern void avm_assign(avm_memcell* lv, avm_memcell* rv);

#define N 4096

void execute_assign (instruction* instr){
	avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*) 0);
	avm_memcell *rv = avm_translate_operand(&instr->arg1, &ax);

	assert(lv && (&stack[N-1] >= lv && lv > &stack[top] || lv == &retval));
	assert(rv);

	avm_assign(lv,rv);
}



void avm_assign (avm_memcell* lv, avm_memcell* rv){
	if(lv == rv)
		return;
	if(lv->type == table_m &&
	   rv->type == table_m &&
	   lv->data.tableVal == rv->data.tableVal)
	   return;


	if(rv->type == undef_m)
		avm_warning("assigning from 'undef' content!");

    avm_memcellclear(lv);
    memcpy(lv, rv, sizeof(avm_memcell));

	if(lv->type == string_m)
		lv->data.strVal = strdup(rv->data.strVal);
    else
	    if(lv->type == table_m)
		    avm_tableincrefcounter(lv->data.tableVal);
}

typedef double(*arithmetic_func_t)(double x, double y);

double add_impl(double x, double y){return x+y;}
double sub_impl(double x, double y){return x-y;}
double mul_impl(double x, double y){return x*y;}
double div_impl(double x, double y){return x/y;}
double mod_impl(double x, double y){
    return ((unsigned) x) % ((unsigned) y);
} 

arithmetic_func_t arithmeticFuncs[]={
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl
};


void execute_arithmetic(instruction *instr){
    avm_memcell *lv = avm_translate_operand(&instr->result , (avm_memcell *) 0);
    avm_memcell *rv1 = avm_translate_operand(&instr->arg1 , &ax);
    avm_memcell *rv2 = avm_translate_operand(&instr->arg2 , &bx);
 
    assert(lv && (&stack[N-1] >= lv && lv > &stack[top] || lv == &retval));

    if(rv1->type != number_m || rv2->type != number_m){
        avm_error("not a number in arithmetic!");
        executionFinished = 1;
    }
    else{
        int index=0;

        if(instr->opcode==add_v){
            index=0;
        }else if(instr->opcode==sub_v){
            index=1;
        }else if(instr->opcode==mul_v){
            index=2;
        }else if(instr->opcode==div_v){
            index=3;
        }else if(instr->opcode==mod_v){
            index=4;
        }

        arithmetic_func_t op = arithmeticFuncs[index];
        avm_memcellclear(lv);
        lv->type = number_m;
        lv->data.numVal = (*op)(rv1->data.numVal , rv2->data.numVal);
    }
}

userfunc* avm_getfuncinfo (unsigned address){return &userFuncs[address];}



 void execute_add (instruction* instr){execute_arithmetic(instr);}
 void execute_sub (instruction* instr){execute_arithmetic(instr);}
 void execute_mul (instruction* instr){execute_arithmetic(instr);}
 void execute_div (instruction* instr){execute_arithmetic(instr);}
 void execute_mod (instruction* instr){execute_arithmetic(instr);}

//not used - apo tin 4 exw afairesei tis entoles uminus, add, or, not
 void execute_uminus (instruction*instr){}
 void execute_and (instruction*instr){}
 void execute_or (instruction*instr){}
 void execute_not (instruction*instr){}
 

//to xrisimopoiw sta relational > >= < <= == !=
typedef unsigned char (*tobool_func_t)(avm_memcell*);

unsigned char number_tobool (avm_memcell* m) {return m->data.numVal!=0;}//true otan den einai miden
unsigned char string_tobool(avm_memcell* m) {return m->data.strVal[0]!=0;}//true otan den einai keno
unsigned char bool_tobool(avm_memcell* m){return m->data.boolVal;}
unsigned char table_tobool(avm_memcell* m){return 1;}//by default true
unsigned char userfunc_tobool(avm_memcell* m){return 1;}//by default true
unsigned char libfunc_tobool(avm_memcell* m){return 1;}//by default true
unsigned char nil_tobool(avm_memcell* m){return 0;}//by default false
unsigned char undef_tobool(avm_memcell* m){return 0;}





tobool_func_t toboolFuncs[]={
	number_tobool,
	string_tobool,
	bool_tobool,
	table_tobool,
	userfunc_tobool,
	libfunc_tobool,
	nil_tobool,
	undef_tobool
	};
	
	unsigned char avm_tobool(avm_memcell* m){
		assert(m->type>=0&&m->type<undef_m);
		return (*toboolFuncs[m->type])(m);
	}
	

char* typeStrings[]={
	"number",
	"string",
	"bool",
	"table",
	"userfunc",
	"libfunc",
	"nil",
	"undef"
};

void execute_jeq (instruction* instr){
	assert(instr->result.type==label_a);
	
	avm_memcell* rv1=avm_translate_operand(&instr->arg1,&ax);
	avm_memcell* rv2=avm_translate_operand(&instr->arg2,&bx);
	
	unsigned char result=0;
	//proairetiko
	if(rv1->type==undef_m||rv2->type==undef_m)
		avm_error("'undef' involved in equality!");
	else
	if(rv1->type==bool_m||rv2->type==bool_m)
		result=(avm_tobool(rv1)==avm_tobool(rv2));
	else
	if(rv1->type==nil_m||rv2->type==nil_m)
		result=rv1->type==nil_m&&rv2->type==nil_m;
	else
	if (rv1->type!=rv2->type)
		avm_error(
			"%s==%s is illegal!",
			typeStrings[rv1->type],
			typeStrings[rv2->type]
			);
	else{//ara exoune ta idia types kai kanw dispatch gia ola ta types
        if(rv1->type==number_m && rv2->type==number_m){
            if(rv1->data.numVal==rv2->data.numVal){
                result=1;
            }else{
                result=0;
            }
        }
        else if(rv1->type==string_m && rv2->type==string_m)
        {
            if(strcmp(rv1->data.strVal,rv2->data.strVal)==0)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }

        }
        else if(rv1->type==bool_m && rv2->type==bool_m)
        {
            if(rv1->data.boolVal == rv2->data.boolVal)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
        
        }
        else if(rv1->type==table_m && rv2->type==table_m)
        {
            if(rv1->data.tableVal == rv2->data.tableVal)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
        }
        else if(rv1->type==userfunc_m && rv2->type==userfunc_m)
        {
            if(rv1->data.funcVal == rv2->data.funcVal)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
        
        }
        else if(rv1->type==libfunc_m && rv2->type==libfunc_m)
        {
            if(strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal)==0)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
        }
	/*ylopoihsh.....equality check with dispatching.*/

	}
		
	if(!executionFinished && result)
		pc=instr->result.val;
}

/*typedef enum avm_memcell_t{
	number_m=0,
	string_m =1,
	bool_m =2,
	table_m=3,
	userfunc_m=4,
	libfunc_m=5,
	nil_m=6,
	undef_m=7
}avm_memcell_t;*/


 void execute_jne (instruction* instr)
 {
	assert(instr->result.type==label_a);
	
	avm_memcell* rv1=avm_translate_operand(&instr->arg1,&ax);
	avm_memcell* rv2=avm_translate_operand(&instr->arg2,&bx);
	
	unsigned char result=0;
	//proairetiko
	if(rv1->type==undef_m||rv2->type==undef_m)
		avm_error("'undef' involved in equality!");
	else
	if(rv1->type==bool_m||rv2->type==bool_m)
		result=(avm_tobool(rv1)==avm_tobool(rv2));
	else
	if(rv1->type==nil_m||rv2->type==nil_m)
		result=rv1->type==nil_m&&rv2->type==nil_m;
	else
	if (rv1->type!=rv2->type)
		avm_error(
			"%s==%s is illegal!",
			typeStrings[rv1->type],
			typeStrings[rv2->type]
			);
	else{//ara exoune ta idia types kai kanw dispatch gia ola ta types
        if(rv1->type==number_m && rv2->type==number_m){
            if(rv1->data.numVal==rv2->data.numVal){
                result=1;
            }else{
                result=0;
            }
        }
        else if(rv1->type==string_m && rv2->type==string_m)
        {
            if(strcmp(rv1->data.strVal,rv2->data.strVal)==0)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }

        }
        else if(rv1->type==bool_m && rv2->type==bool_m)
        {
            if(rv1->data.boolVal == rv2->data.boolVal)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
        
        }
        else if(rv1->type==table_m && rv2->type==table_m)
        {
            if(rv1->data.tableVal == rv2->data.tableVal)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
        }
        else if(rv1->type==userfunc_m && rv2->type==userfunc_m)
        {
            if(rv1->data.funcVal == rv2->data.funcVal)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
        
        }
        else if(rv1->type==libfunc_m && rv2->type==libfunc_m)
        {
            if(strcmp(rv1->data.libfuncVal, rv2->data.libfuncVal)==0)
            {
                result = 1;
            }
            else
            {
                result = 0;
            }
        }
	

	}

    if(result==1)
        result=0;
    else
        result=1;
		
	if(!executionFinished && result)
		pc=instr->result.val;
}

void execute_jle (instruction* instr){
    assert(instr->result.type==label_a);
	
	avm_memcell* rv1=avm_translate_operand(&instr->arg1,&ax);
	avm_memcell* rv2=avm_translate_operand(&instr->arg2,&bx);
	
	unsigned char result=0;
	//proairetiko
	if(rv1->type==undef_m||rv2->type==undef_m)
		avm_error("'undef' involved in equality!");
	else
	if (rv1->type!=rv2->type)
		avm_error(
			"%s==%s is illegal!",
			typeStrings[rv1->type],
			typeStrings[rv2->type]
			);
	else{//ara exoune ta idia types kai kanw dispatch gia ola ta types
        if(rv1->type==number_m && rv2->type==number_m){
            if(rv1->data.numVal<=rv2->data.numVal){
                result=1;
            }else{
                result=0;
            }
        }
        else {
            avm_error("jle type error!");
        }
	}

		
	if(!executionFinished && result)
		pc=instr->result.val;
}
 void execute_jge (instruction* instr){
        assert(instr->result.type==label_a);
	
	avm_memcell* rv1=avm_translate_operand(&instr->arg1,&ax);
	avm_memcell* rv2=avm_translate_operand(&instr->arg2,&bx);
	
	unsigned char result=0;
	//proairetiko
	if(rv1->type==undef_m||rv2->type==undef_m)
		avm_error("'undef' involved in equality!");
	else
	if (rv1->type!=rv2->type)
		avm_error(
			"%s==%s is illegal!",
			typeStrings[rv1->type],
			typeStrings[rv2->type]
			);
	else{//ara exoune ta idia types kai kanw dispatch gia ola ta types
        if(rv1->type==number_m && rv2->type==number_m){
            if(rv1->data.numVal>=rv2->data.numVal){
                result=1;
            }else{
                result=0;
            }
        }
        else {
            avm_error("jge type error!");
        }
	}

		
	if(!executionFinished && result)
		pc=instr->result.val;
 }
 void execute_jlt (instruction* instr){
        assert(instr->result.type==label_a);
	
	avm_memcell* rv1=avm_translate_operand(&instr->arg1,&ax);
	avm_memcell* rv2=avm_translate_operand(&instr->arg2,&bx);
	
	unsigned char result=0;
	//proairetiko
	if(rv1->type==undef_m||rv2->type==undef_m)
		avm_error("'undef' involved in equality!");
	else
	if (rv1->type!=rv2->type)
		avm_error(
			"%s==%s is illegal!",
			typeStrings[rv1->type],
			typeStrings[rv2->type]
			);
	else{//ara exoune ta idia types kai kanw dispatch gia ola ta types
        if(rv1->type==number_m && rv2->type==number_m){
            if(rv1->data.numVal<rv2->data.numVal){
                result=1;
            }else{
                result=0;
            }
        }
        else {
            avm_error("jlt type error!");
        }
	}

		
	if(!executionFinished && result)
		pc=instr->result.val;
 }
 void execute_jgt (instruction* instr){    assert(instr->result.type==label_a);
	
	avm_memcell* rv1=avm_translate_operand(&instr->arg1,&ax);
	avm_memcell* rv2=avm_translate_operand(&instr->arg2,&bx);
	
	unsigned char result=0;
	//proairetiko
	if(rv1->type==undef_m||rv2->type==undef_m)
		avm_error("'undef' involved in equality!");
	else
	if (rv1->type!=rv2->type)
		avm_error(
			"%s==%s is illegal!",
			typeStrings[rv1->type],
			typeStrings[rv2->type]
			);
	else{//ara exoune ta idia types kai kanw dispatch gia ola ta types
        if(rv1->type==number_m && rv2->type==number_m){
            if(rv1->data.numVal>rv2->data.numVal){
                result=1;
            }else{
                result=0;
            }
        }
        else {
            avm_error("jgt type error!");
        }
	}

		
	if(!executionFinished && result)
		pc=instr->result.val;}

typedef void(*library_func_t)(void);


struct libfuncinfo{
    char *id;
    library_func_t addr;
    struct libfuncinfo *next;
};
struct libfuncinfo *libfuncinfohead = NULL;


library_func_t avm_getlibraryfunc(char*id){
    
    struct libfuncinfo *tmp = libfuncinfohead;
    while(tmp != NULL)
    {
        if(!strcmp(tmp->id,id))
        {
            return tmp->addr;
        }
        tmp = tmp->next;
    }
    return NULL;
    
}
void execute_funcexit (instruction* unused);

unsigned avm_get_envvalue(unsigned i);



#define AVM_NUMACTUALS_OFFSET +4
#define AVM_SAVEDPC_OFFSET +3
#define AVM_SAVEDTOP_OFFSET +2
#define AVM_SAVEDTOPSP_OFFSET +1


unsigned avm_totalactuals(void){
	return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i){
	assert(i < avm_totalactuals());
	return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

//ylopoihsh tis libfunc print
void libfunc_print(void){
    unsigned n = avm_totalactuals();//pairnw ton arithmo twn prismatwn pou pragmatika kalestike i print
    for(unsigned i = 0; i < n; ++i){
        char* s = avm_tostring(avm_getactual(i));
        /*puts(s);*/printf("%s",s);//ta metatrepw se string kai ta ektypwnw
        free(s);
    }
}

//ylopoihsh tis typeof
void libfunc_typeof(void){
	unsigned n=avm_totalactuals();
	
	if(n!=1)//elegxw an kalestike me ena orima
		avm_error("one argument (not %d) expected in 'typeof'!",n);
	else{
		avm_memcellclear(&retval);
		retval.type=string_m;//epistrefw to type tou orismatos
        //giana epistrepsw kati to vazw 
		retval.data.strVal=strdup(typeStrings[avm_getactual(0)->type]);
	}
}

//ylopoihsh tis totalarguments
void libfunc_totalarguments(void){
	unsigned p_topsp=avm_get_envvalue(topsp+AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);
	
	if(!p_topsp){
		avm_error("'totalarguments' called outside a function!");
		retval.type=nil_m;
	}
	else{
		retval.type=number_m;
		retval.data.numVal=avm_get_envvalue(p_topsp+AVM_NUMACTUALS_OFFSET);
	}
}

void libfunc_argument(void){

    unsigned p_topsp=avm_get_envvalue(topsp+AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);
	
	if(!p_topsp){
		avm_error("'argument' called outside a function!");
		retval.type=nil_m;
	}
	else{
        unsigned n=avm_totalactuals();
	
        if(n!=1)
            avm_error("one argument (not %d) expected in 'argument'!",n);
        else{
            avm_memcellclear(&retval);

            avm_memcell *argument_parameter = avm_getactual(0);
            int index = argument_parameter->data.numVal;//poio parameter theloume
            //lecture 12 stack[topsp + Κ + sym->offset + 1]
            int K = AVM_STACKENV_SIZE;
            avm_memcell *function_parameter = &stack[p_topsp + K + index + 1];

            if(function_parameter->type==number_m){
                retval.type=number_m;
		        retval.data.numVal=function_parameter->data.numVal;
                return;
            }

            if(function_parameter->type==string_m){
                retval.type=string_m;
		        retval.data.strVal=strdup(function_parameter->data.strVal);
                return;
            }

            if(function_parameter->type==bool_m){
                retval.type=bool_m;
		        retval.data.boolVal=function_parameter->data.boolVal;
                return;
            }

            if(function_parameter->type==table_m){
                retval.type=table_m;
		        retval.data.tableVal=function_parameter->data.tableVal;
                return;
            }

            if(function_parameter->type==userfunc_m){
                retval.type=userfunc_m;
		        retval.data.funcVal=function_parameter->data.funcVal;
                return;
            }

            if(function_parameter->type==libfunc_m){
                retval.type=libfunc_m;
		        retval.data.libfuncVal=strdup(function_parameter->data.libfuncVal);
                return;
            }

            if(function_parameter->type==nil_m){
                retval.type=nil_m;
                return;
            }
        }
		
	}



}


void avm_registerlibfunc(char* id, library_func_t addr){
    struct libfuncinfo *tmp = libfuncinfohead;
    struct libfuncinfo *new = (struct libfuncinfo *)malloc(sizeof(struct libfuncinfo));

    new->addr = addr;
    new->id = id;
    new->next = NULL;

    if(tmp == NULL){
        libfuncinfohead = new;
        return;
    }

    while(tmp->next != NULL)
    {
        tmp = tmp->next;
    }

    tmp->next = new;
}



void avm_calllibfunc (char* id){
    library_func_t f = avm_getlibraryfunc(id);
    if(!f){
        avm_error("unsupported lib func '%s' called!", id);
        executionFinished = 1;
    }
    else{
        avm_callsaveenvironment();
        topsp = top;
        totalActuals = 0;
        (*f)();
        if(!executionFinished)
            execute_funcexit((instruction*)0);
    }
}


 void execute_call(instruction *instr)
{
    avm_memcell *func = avm_translate_operand(&instr->arg1 , &ax);
    assert(func);
    switch(func->type){
        case userfunc_m:{
            avm_callsaveenvironment();
            pc = func->data.funcVal;
            assert(pc<AVM_ENDING_PC);
            assert(code[pc].opcode == funcenter_v);
            break;
        }
        case string_m: avm_calllibfunc(func->data.strVal);break;
        case libfunc_m: avm_calllibfunc(func->data.libfuncVal);break;
        case table_m: avm_call_functor(func->data.tableVal);break;
        default:{
            char *s = avm_tostring(func);
            avm_error("call: cannot bind '%s' to function!" , s);
            free(s);
            executionFinished = 1;
        }
    }
}

void execute_pusharg(instruction *instr)
{
    avm_memcell *arg = avm_translate_operand(&instr->arg1 , &ax);
    assert(arg);
    avm_assign(&stack[top],arg);
    ++totalActuals;
    avm_dec_top();
}
 
void execute_funcenter (instruction* instr){
	avm_memcell* func=avm_translate_operand(&instr->result,&ax);
	assert(func);
	assert(pc==func->data.funcVal);
	
	totalActuals=0;
	userfunc* funcInfo=avm_getfuncinfo(instructions[func->data.funcVal].result.val);
	topsp=top;
	top=top-funcInfo->localSize;
}

unsigned avm_get_envvalue(unsigned i){
	assert(stack[i].type == number_m);
	unsigned val=(unsigned)stack[i].data.numVal;
	assert(stack[i].data.numVal == ((double)val));
	return val;
}

void execute_funcexit (instruction* unused){
	unsigned oldTop=top;
	top=avm_get_envvalue(topsp+AVM_SAVEDTOP_OFFSET);
	pc=avm_get_envvalue(topsp+AVM_SAVEDPC_OFFSET);
	topsp=avm_get_envvalue(topsp+AVM_SAVEDTOPSP_OFFSET);
	
	while (++oldTop<=top)
		avm_memcellclear(&stack[oldTop]);
	
}
 
void execute_newtable (instruction* instr){
	avm_memcell* lv = avm_translate_operand(&instr->arg1, (avm_memcell*)0);
	assert(lv && (&stack[N-1] >= lv && lv > &stack[top] || lv == &retval));

    avm_memcellclear(lv);
    lv->type = table_m;
    lv->data.tableVal = avm_tablenew();
    avm_tableincrefcounter(lv->data.tableVal);
}

void execute_tablegetelem(instruction* instr){

    avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*) 0);
    avm_memcell* t = avm_translate_operand(&instr->arg1, (avm_memcell*)0);
    avm_memcell* i = avm_translate_operand(&instr->arg2, &ax);

    assert(lv && &stack[N-1] >= lv && lv > &stack[top] || lv == &retval);
    assert( t && &stack[N-1] >= t && t > &stack[top] );
    assert(i);

    avm_memcellclear(lv);
    lv->type = nil_m;
    if(t->type != table_m){
        avm_error("illegal use of type %s as table!", typeStrings[t->type]);
    }
    else{
        avm_memcell* content = avm_tablegetelem(t->data.tableVal, i);
        if(content)
            avm_assign(lv, content);
        else{
            char* ts = avm_tostring(t);
            char* is = avm_tostring(i);
            avm_warning("%s [%s] not found!", ts, is);
            free(ts);
            free(is);
        }
    }

}


void execute_tablesetelem(instruction* instr){
	avm_memcell* c = avm_translate_operand(&instr->result, &bx);
	avm_memcell* t = avm_translate_operand(&instr->arg1, (avm_memcell*) 0);
	avm_memcell* i = avm_translate_operand(&instr->arg2, &ax);
    assert( t && &stack[N-1] >= t && t > &stack[top]);
    assert(i && c);

    if(t->type != table_m)
        avm_error("illegal use of type %s as table!", typeStrings[t->type]);
    else
        avm_tablesetelem(t->data.tableVal, i , c);
}


//not used
void execute_nop (instruction*instr){}
void execute_jump (instruction* instr){
    int destination= instr->result.val;
    pc=destination;
}

execute_func_t executeFuncs[]={
	execute_assign,
	execute_mul,
	execute_uminus,
	execute_not,
	execute_jle,
	execute_jgt,
	execute_funcenter,
	execute_tablegetelem,
	execute_add,
	execute_div,
	execute_and,
	execute_jeq,
    execute_jge,
	execute_call,
	execute_funcexit,
	execute_tablesetelem,
	execute_sub,
	execute_mod,
	execute_or,
	execute_jne,
	execute_jlt,
	execute_pusharg,
	execute_newtable,
	execute_nop,
    execute_jump
};

//me aytin eketeleitai o kwdikas stin eikoniki mixani
//kathe fora kalei mia entoli
void execute_cycle(void){
	if(executionFinished)
		return;
	else
	if(pc==AVM_ENDING_PC){
		executionFinished=1;
		return;
	}
	else{
		assert(pc<AVM_ENDING_PC);
		instruction* instr =code+pc;//pairnw tin entoli sto sygkekrimeno pc
		assert(
			instr->opcode>=0&&
			instr->opcode<=AVM_MAX_INSTRUCTION
		);
		if(instr->srcLine)
			currLine=instr->srcLine;
			unsigned oldPC=pc;
			(*executeFuncs[instr->opcode])(instr);//ektelw tin antistoixi execute
			if(pc==oldPC)
				++pc;
	}
}

void avm_initialize (void){
	avm_initstack();
	avm_registerlibfunc("print",libfunc_print);
	avm_registerlibfunc("typeof",libfunc_typeof);
	

    avm_registerlibfunc("totalarguments",libfunc_totalarguments);
	avm_registerlibfunc("argument",libfunc_argument);

	/*same for all the rest library function.*/

    while(programVarOffset--){
        avm_dec_top();//allocate space for globals
    }

}

void run_avm(){
    avm_initialize();

    while(executionFinished != 1){
        execute_cycle();
    }

}

int main(){

    FILE* file_abc = fopen("alpha_binary_code.abc", "rb");

    int magicnumber;
    fread(&magicnumber,sizeof(magicnumber),1,file_abc);
    fread(&programVarOffset,sizeof(programVarOffset),1,file_abc);
        
    /*printf("%d globals %d\n", magicnumber, programVarOffset);*/

    fread(&totalStringConsts , sizeof(totalStringConsts) , 1, file_abc);
    //printf("%d\n" , totalStringConsts);
    stringConsts = (char**)malloc(sizeof(char*)*totalStringConsts);
    for(int i=0;i<totalStringConsts;i++)
    {
        stringConsts[i] = binary_read_string(file_abc);
        //printf("[%s]\n", stringConsts[i]);
    }

    fread(&totalNumConsts , sizeof(totalNumConsts) , 1 , file_abc);
    //printf("%d\n" , totalNumConsts);
    numConsts = malloc(totalNumConsts * sizeof(double));
    for(int i=0;i<totalNumConsts;i++)
    {
        fread(&numConsts[i] , sizeof(numConsts[i]) , 1, file_abc);
        //printf("%f\n" , numConsts[i]);
    }
    //fread(&numConsts , sizeof(double) , totalNumConsts , file_abc);

    fread(&totalUserFuncs , sizeof(totalUserFuncs) , 1,file_abc);
    //printf("%d\n" , totalUserFuncs);
    
    userFuncs = malloc(totalUserFuncs * sizeof(struct userfunc));

    for(int i=0;i<totalUserFuncs;i++)
    {
        fread(&userFuncs[i].address , sizeof(userFuncs[i].address) ,1 , file_abc);
        fread(&userFuncs[i].localSize , sizeof(userFuncs[i].localSize) , 1, file_abc);
        userFuncs[i].id = binary_read_string(file_abc);

      //  printf("%d %d %s\n", userFuncs[i].address, userFuncs[i].localSize, userFuncs[i].id);
    
    }

    fread(&totalNamedLibfuncs , sizeof(totalNamedLibfuncs) , 1, file_abc);
    //printf("%d\n" , totalNamedLibfuncs);
    namedLibfuncs = (char**)malloc(sizeof(char*)*totalNamedLibfuncs);
    for(int i=0;i<totalNamedLibfuncs;i++)
    {
        namedLibfuncs[i] = binary_read_string(file_abc);
      //  printf("[%s]\n", namedLibfuncs[i]);
    }

    fread(&totalInstructions , sizeof(totalInstructions) , 1, file_abc);

    instructions = (instruction*)malloc(sizeof(instruction)*totalInstructions);
    
    for(int i=0;i<totalInstructions;i++)
    {
        fread(&instructions[i].opcode , sizeof(instructions[i].opcode) , 1, file_abc);
        fread(&instructions[i].result , sizeof(instructions[i].result) , 1, file_abc);
        fread(&instructions[i].arg1 , sizeof(instructions[i].arg1) , 1, file_abc);
        fread(&instructions[i].arg2 , sizeof(instructions[i].arg2) , 1, file_abc);
        fread(&instructions[i].srcLine , sizeof(instructions[i].srcLine) , 1, file_abc);
    }

    fclose(file_abc);

    //instructionPrinter();
    code=instructions;
    codeSize=totalInstructions;
    top=N-1;//4095
    run_avm();    
}
