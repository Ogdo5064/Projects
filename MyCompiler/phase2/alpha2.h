/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_ALPHA2_H_INCLUDED
# define YY_YY_ALPHA2_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    U_MINUS = 258,                 /* U_MINUS  */
    ID = 259,                      /* ID  */
    INTNUMBER = 260,               /* INTNUMBER  */
    REALNUMBER = 261,              /* REALNUMBER  */
    STRING = 262,                  /* STRING  */
    IF = 263,                      /* IF  */
    ELSE = 264,                    /* ELSE  */
    WHILE = 265,                   /* WHILE  */
    FOR = 266,                     /* FOR  */
    FUNCTION = 267,                /* FUNCTION  */
    RETURN = 268,                  /* RETURN  */
    BREAK = 269,                   /* BREAK  */
    CONTINUE = 270,                /* CONTINUE  */
    AND = 271,                     /* AND  */
    NOT = 272,                     /* NOT  */
    OR = 273,                      /* OR  */
    LOCAL = 274,                   /* LOCAL  */
    TRUE = 275,                    /* TRUE  */
    FALSE = 276,                   /* FALSE  */
    NIL = 277,                     /* NIL  */
    ASSIGN = 278,                  /* ASSIGN  */
    PLUS = 279,                    /* PLUS  */
    MINUS = 280,                   /* MINUS  */
    MULTI = 281,                   /* MULTI  */
    DIV = 282,                     /* DIV  */
    MOD = 283,                     /* MOD  */
    EQUAL = 284,                   /* EQUAL  */
    NOTEQUAL = 285,                /* NOTEQUAL  */
    DOUBLEPLUS = 286,              /* DOUBLEPLUS  */
    DOUBLEMINUS = 287,             /* DOUBLEMINUS  */
    GREATER = 288,                 /* GREATER  */
    LESS = 289,                    /* LESS  */
    GREATEREQUAL = 290,            /* GREATEREQUAL  */
    LESSEQUAL = 291,               /* LESSEQUAL  */
    LEFTAGGILI = 292,              /* LEFTAGGILI  */
    RIGHTAGGILI = 293,             /* RIGHTAGGILI  */
    LEFTTETR = 294,                /* LEFTTETR  */
    RIGHTTETR = 295,               /* RIGHTTETR  */
    LEFTPARENTHESIS = 296,         /* LEFTPARENTHESIS  */
    RIGHTPARENTHESIS = 297,        /* RIGHTPARENTHESIS  */
    SEMICOLON = 298,               /* SEMICOLON  */
    COMMA = 299,                   /* COMMA  */
    COLON = 300,                   /* COLON  */
    DOUBLECOLON = 301,             /* DOUBLECOLON  */
    DOT = 302,                     /* DOT  */
    DOTS = 303                     /* DOTS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define U_MINUS 258
#define ID 259
#define INTNUMBER 260
#define REALNUMBER 261
#define STRING 262
#define IF 263
#define ELSE 264
#define WHILE 265
#define FOR 266
#define FUNCTION 267
#define RETURN 268
#define BREAK 269
#define CONTINUE 270
#define AND 271
#define NOT 272
#define OR 273
#define LOCAL 274
#define TRUE 275
#define FALSE 276
#define NIL 277
#define ASSIGN 278
#define PLUS 279
#define MINUS 280
#define MULTI 281
#define DIV 282
#define MOD 283
#define EQUAL 284
#define NOTEQUAL 285
#define DOUBLEPLUS 286
#define DOUBLEMINUS 287
#define GREATER 288
#define LESS 289
#define GREATEREQUAL 290
#define LESSEQUAL 291
#define LEFTAGGILI 292
#define RIGHTAGGILI 293
#define LEFTTETR 294
#define RIGHTTETR 295
#define LEFTPARENTHESIS 296
#define RIGHTPARENTHESIS 297
#define SEMICOLON 298
#define COMMA 299
#define COLON 300
#define DOUBLECOLON 301
#define DOT 302
#define DOTS 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 103 "alpha.y"

char* stringValue;
int intValue;
double realValue;

#line 169 "alpha2.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_ALPHA2_H_INCLUDED  */
