%{ /*apo edo kai kato einai oloi oi kanones-orismoi*/
#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct TokenList{
    int line;
    char *token; 
    char *type;
    struct TokenList *next;
};

struct TokenList *ListHead = NULL;

struct TokenList *AddTokenToList(struct TokenList *ListHead , int line , char *token , char* type) 
{

    struct TokenList *new = (struct TokenList *)malloc(sizeof(struct TokenList));
    new->next = NULL;
    new->line = line;
    new->token = strdup(token);
    new->type = strdup(type);

    if(ListHead == NULL)
    {    
        ListHead = new;
    }
    else
    {
        struct TokenList *tmp = ListHead;
        while(tmp->next != NULL)
        {       
            tmp = tmp->next;
        }

        tmp->next = new;
    }

    return ListHead;
}   


void PrintList(struct TokenList *head) 
{
    int i=1;
    struct TokenList *tmp = ListHead;
    while(tmp != NULL)
    {
        printf("--%d #%d \"%s\" %s\n" , tmp->line ,i++, tmp->token , tmp->type); 
        /*EDO OTAN TO TOKEN EINAI \n KANEI NEW LINE STHN EKTUPOSH 
        DEN 3ERO POS NA TO FTIA3O*/
        tmp = tmp->next;
    }
}



%} 
/*edo einai grammena ola ta macros analutika gia na 3erei o lex ti akribos einai id,punctuation...*/


%option noyywrap
%option yylineno


ID [a-zA-Z][a-zA-Z_0-9]*   
SPACE [\r\t\v\n ]
NUMBER [0-9][0-9]*
REALNUMBER [0-9]*\.[0-9][0-9]*
COMMENT "//".*

IF "if"
ELSE "else"
WHILE "while"
FOR	"for"
FUNCTION "function"
RETURN "return"
BREAK "break"
CONTINUE "continue"
AND	"and"
NOT	"not"
OR "or"
LOCAL "local"
TRUE "true"	
FALSE "false"
NIL "nil"

ASSIGN "="
PLUS "+"
MINUS "-"
MULTI "*"
DIV "/"
MOD	"%"
EQUAL "=="
NOTEQUAL "!="
DOUBLEPLUS "++"
DOUBLEMINUS "--"
GREATER ">"
LESS "<"
GREATEREQUAL ">="
LESSEQUAL "<="

LEFTAGGILI \{
RIGHTAGGILI \}
LEFTTETR \[
RIGHTTETR \]
LEFTPARENTHESIS	\(
RIGHTPARENTHESIS \)
SEMICOLON \;
COMMA \,
COLON \:
DOUBLECOLON \:\:
DOT \.
DOTS \.\.


/*edo kathe fora pou o lex diabazei ena xarakthra kai ton 
kanei identify me thn bohtheia ton orismwn erxete edo kai kanei oti tou leei*/

/*KANONES*/

%% 


{IF} {printf("keyword recognized %s\n" , yytext); ListHead = AddTokenToList(ListHead , yylineno , yytext , "KEYWORD");}
{ELSE} {printf("keyword recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "KEYWORD");
{WHILE} {printf("keyword recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "KEYWORD");
{FOR} {printf("keyword recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "KEYWORD");
{FUNCTION} {printf("keyword recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "KEYWORD");
{RETURN} {printf("keyword recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "KEYWORD");
{BREAK} {printf("keyword recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "KEYWORD");
{CONTINUE} {printf("keyword recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "KEYWORD");
{AND} {printf("keyword recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "KEYWORD");
{NOT} {printf("keyword recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "KEYWORD");
{OR} {printf("keyword recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "KEYWORD");
{LOCAL} {printf("keyword recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "KEYWORD");
{TRUE} {printf("keyword recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "KEYWORD");
{FALSE} {printf("keyword recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "KEYWORD");
{NIL} {printf("keyword recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "KEYWORD");

{COMMENT} {printf("single line comment detected %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "SINGLE LINE COMMENT");
{ID} {printf("recognized id %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "ID");
{SPACE} {/*printf("white char recognized\n");*/} ListHead = AddTokenToList(ListHead , yylineno , yytext , "SPACE");
{REALNUMBER} {printf("realnumber recognized: %s\n", yytext);ListHead = AddTokenToList(ListHead , yylineno , yytext , "REALCONST");} 
{NUMBER} {printf("number recognized %s\n" , yytext); ListHead = AddTokenToList(ListHead , yylineno , yytext , "INTCONST"); } 


{ASSIGN} {printf("operation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "OPERATOR");
{PLUS} {printf("operation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "OPERATOR");
{MINUS} {printf("operation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "OPERATOR");
{MULTI} {printf("operation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "OPERATOR");
{DIV} {printf("operation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "OPERATOR");
{MOD} {printf("operation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "OPERATOR");
{EQUAL} {printf("operation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "OPERATOR");
{NOTEQUAL} {printf("operation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "OPERATOR");
{DOUBLEPLUS} {printf("operation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "OPERATOR");
{DOUBLEMINUS} {printf("operation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "OPERATOR");
{GREATER} {printf("operation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "OPERATOR");
{LESS} {printf("operation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "OPERATOR");
{GREATEREQUAL} {printf("operation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "OPERATOR");
{LESSEQUAL} {printf("operation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "OPERATOR");

{LEFTAGGILI} {printf("punctuation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "PUNCTUATION");
{RIGHTAGGILI} {printf("punctuation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "PUNCTUATION");
{LEFTTETR} {printf("punctuation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "PUNCTUATION");
{RIGHTTETR} {printf("punctuation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "PUNCTUATION");
{LEFTPARENTHESIS} {printf("punctuation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "PUNCTUATION");
{RIGHTPARENTHESIS} {printf("punctuation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "PUNCTUATION");
{SEMICOLON} {printf("punctuation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "PUNCTUATION");
{COMMA} {printf("punctuation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "PUNCTUATION");
{COLON} {printf("punctuation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "PUNCTUATION");
{DOUBLECOLON} {printf("punctuation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "PUNCTUATION");
{DOT} {printf("punctuation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "PUNCTUATION");
{DOTS} {printf("punctuation recognized %s\n" , yytext);} ListHead = AddTokenToList(ListHead , yylineno , yytext , "PUNCTUATION");




"/*" {

    /*kathe fora pou dei to sumbolo comment tha mpei se auto to block kodika*/


    int counter = 1; /*idea counter, otan blepo kleisimo -1 h otan blepo anoigma +1*/
    int c , d;
    while((c = input()) != 0) /*input epistrefei 0(linux) otan teliosei na diabazei*/
    {
        if(c==EOF)break; /*trexe oso den eimaste sto EOF*/
        if(c == '*') 
        {
            d = input();
            if(d == '/') /*epitiximeno kleisimo*/
            {
                counter--;

                if(counter == 0) /*an o counter eftasa 0 shmainei oti panta eimaste sto telos tou comment*/
                {
                    printf("comment\n");
                    break;
                }
                else /*allios an ekeise kai den einai 0 htan kleisimo nested comment*/
                {
                    printf("nested comment\n");
                }
            }
            else /*shmantiko na kanoume unput gia na gurisei piso o extra xarakthras pou klepsame*/
            {
                unput(d);
            }
        }

        if(c == '/') /*omoios me pano apla edo +1 ston counter*/
        {
            d = input();
            if(d == '*')
            {
                counter++;
                //printf("anoigma detected\n");
            }else
            {
                unput(d);
            }
        }
    }
    if(counter != 0) /*an den einai 0 shmainei oti kapoio comment den ekleise*/
    {
        printf("error in comment\n");
        break;
    }
    else
    {
        ListHead = AddTokenToList(ListHead , yylineno , yytext , "COMMENT");
    }
}



\" {    
        /*string handling, an do na anoigei autaki tha mpo edo*/

        char string[1000]; /*bazoume to string se pinaka gia na to kanoume add to list sto telos*/
        int j=0;
        int close=0;
        int warn=0; /*flag*/
        int c;
        while((c = input()) != 0) /*trexe oso den eisai 0*/
        { 
            warn=0;
            if(c==EOF)break;
            if(c == '"') /*an 3anado autaki shmainei oti teliose to string*/
            {
                close=1;
                printf("\nString recognized -> " );
                break;
            }
            else if(c=='\\') /* brhka \ */ 
            { 
                /*mesa sto string prepei to \t \n.... na ta metatrepoume se auto pou shmainoun*/

                int d = input(); /*koitao ena xarakthra pio pera gia na doume ti exoume*/
                if(d == 'n') /* brhka n */
                {
                    c='\n';
                }
                else if(d == 't') /* brhka t */
                {
                    c = '\t';
                }
                else if(d == '\\') /* brhka allo ena \  */
                {
                    c = '\\';
                }
                else if(d == '"') /* brhka " */
                {
                    c = '"';
                }
                else 
                {
                    c=d;
                    warn=1;
                }
            }

            if(warn) /*eidikos xarakthras \agnostos den anagnoristike*/ /*to bazoume omos ston pinaka string opos einai*/
            {
                printf("\n---WARNING: not recognized \\%c---", c);
                string[j]='\\'; /*bazo \*/
                ++j;
            }
            string[j]=c;
            ++j;      
        }
        if(close==0) /*3exase na kleisei to string an to close einai 0*/
        {
            printf("\nERROR in string -> ");
        }
        string[j]='\0'; /*bale terminating character*/
        puts(string); /*printare to string sto console*/

        ListHead = AddTokenToList(ListHead , yylineno , string , "STRING"); /*balto sthn lista*/

}




. {printf("cannot match character %s\n",yytext);} 




%%


/* ./a.out -> diavazw apo stdin grafw se stdout 1 argc */
/* ./a.out file1 -> diavazw apo file1 grafw stdout 2 argc */
/* ./a.out file1 file2 -> diavazw file1 grafw file2 3 argc */
/*oles oi periptoseis, eite mas dosei to terminal gia eisodo eite fakelo eite na grapsoume se fakelo thn e3odo*/

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
    yylex(); /*auth edo diabazei ena ena tous xarakthres*/
    printf("\n\n");PrintList(ListHead); /*otan teliosei to diabasma kane print olh thn lista*/
}