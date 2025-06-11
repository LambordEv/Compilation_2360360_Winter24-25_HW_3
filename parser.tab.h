/* A Bison parser, made by GNU Bison 3.7.6.  */

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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    T_ID = 258,                    /* T_ID  */
    T_STRING = 259,                /* T_STRING  */
    T_NUM = 260,                   /* T_NUM  */
    T_NUM_B = 261,                 /* T_NUM_B  */
    T_COMMA = 262,                 /* T_COMMA  */
    T_SC = 263,                    /* T_SC  */
    T_CONTINUE = 264,              /* T_CONTINUE  */
    T_BREAK = 265,                 /* T_BREAK  */
    T_WHILE = 266,                 /* T_WHILE  */
    T_IF = 267,                    /* T_IF  */
    T_RETURN = 268,                /* T_RETURN  */
    T_FALSE = 269,                 /* T_FALSE  */
    T_TRUE = 270,                  /* T_TRUE  */
    T_BOOL = 271,                  /* T_BOOL  */
    T_BYTE = 272,                  /* T_BYTE  */
    T_INT = 273,                   /* T_INT  */
    T_VOID = 274,                  /* T_VOID  */
    T_COMMENT = 275,               /* T_COMMENT  */
    T_ASSIGN = 276,                /* T_ASSIGN  */
    T_OR = 277,                    /* T_OR  */
    T_AND = 278,                   /* T_AND  */
    T_RELOP = 279,                 /* T_RELOP  */
    T_ADD_SUB = 280,               /* T_ADD_SUB  */
    T_MUL_DIV = 281,               /* T_MUL_DIV  */
    T_NOT = 282,                   /* T_NOT  */
    T_LPAREN = 283,                /* T_LPAREN  */
    T_RPAREN = 284,                /* T_RPAREN  */
    T_LBRACE = 285,                /* T_LBRACE  */
    T_RBRACE = 286,                /* T_RBRACE  */
    T_RBRACK = 287,                /* T_RBRACK  */
    T_LBRACK = 288,                /* T_LBRACK  */
    T_ELSE = 289                   /* T_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
