%{
/*Declaration Section*/
/*------- Include Section -------*/
#include <stdio.h>
#include <iostream>
#include "output.hpp"
#include "parser.tab.h"
#include "nodes.hpp"


/*------- Function Declarion Section -------*/
using namespace std;
using namespace ast;

static RelOpType whatRelOpRecieved(string received);
static BinOpType whatBinOpRecieved(string received);
void accumalateStringLexema(void);

/*------- Static Variables Declarion Section -------*/
static char accumalatedString[2096] = {0};
static char accumalatedStrLen = 0;

%}

%option yylineno
%option noyywrap

whitespace                              ([\t\r\n ])
decimalDigit                            ([0-9])
hexDigit                                ([0-9a-fA-F])
letter                                  ([a-zA-Z])

voidToken                               (void)
intToken                                (int)
byteToken                               (byte)
boolToken                               (bool)
andToken                                (and)
orToken                                 (or)
notToken                                (not)
trueToken                               (true)
falseToken                              (false)
returnToken                             (return)
ifToken                                 (if)
elseToken                               (else)
whileToken                              (while)
breakToken                              (break)
continueToken                           (continue)
semicolonToken                          (;)
commaToken                              (,)
lParenToken                             (\()
rParenToken                             (\))
lBraceToken                             (\{)
rBraceToken                             (\})
lBrackToken                             (\[)
rBrackToken                             (\])
assignToken                             (\=)

relopSign                               (==|!=|<|>|<=|>=)
binopSign                               (\+|\-|\*|\/)

commentLexema                           (\/\/.*)

idLexema                                ({letter}+[0-9a-zA-Z]*)

numLexema                               ((0)|([1-9]+{decimalDigit}*))

byteNumLexema                           ({numLexema}b)

%x STRING_LEXEMA
%x STRING_ESCAPE
stringLexemaEnterExit                   (\")


%%
{voidToken}                             { yylval = make_shared<PrimitiveType>(VOID); return T_VOID; }
{intToken}                              { yylval = make_shared<PrimitiveType>(INT); return T_INT; }
{byteToken}                             { yylval = make_shared<PrimitiveType>(BYTE); return T_BYTE; }
{boolToken}                             { yylval = make_shared<PrimitiveType>(BOOL); return T_BOOL; }
{andToken}                              { return T_AND; }
{orToken}                               { return T_OR; }
{notToken}                              { return T_NOT; }
{trueToken}                             { return T_TRUE; }
{falseToken}                            { return T_FALSE; }
{returnToken}                           { return T_RETURN; }
{ifToken}                               { return T_IF; }
{elseToken}                             { return T_ELSE; }
{whileToken}                            { return T_WHILE; }
{breakToken}                            { return T_BREAK; }
{continueToken}                         { return T_CONTINUE; }
{semicolonToken}                        { return T_SC; }
{commaToken}                            { return T_COMMA; }
{lParenToken}                           { return T_LPAREN; }
{rParenToken}                           { return T_RPAREN; }
{lBraceToken}                           { return T_LBRACE; }
{rBraceToken}                           { return T_RBRACE; }
{lBrackToken}                           { return T_LBRACK; }
{rBrackToken}                           { return T_RBRACK; }
{assignToken}                           { return T_ASSIGN; }

{relopSign}                             { yylval = make_shared<RelOp>(whatRelOpRecieved(yytext), nullptr, nullptr); return T_RELOP; }
[+-]                                    { yylval = make_shared<BinOp>(whatBinOpRecieved(yytext), nullptr, nullptr); return T_ADD_SUB; }
[*/]                                    { yylval = make_shared<BinOp>(whatBinOpRecieved(yytext), nullptr, nullptr); return T_MUL_DIV; }
{commentLexema}                         { ; }
{idLexema}                              { yylval = make_shared<ID>(yytext); return T_ID; }
{numLexema}                             { yylval = make_shared<Num>(yytext); return T_NUM; }
{byteNumLexema}                         { yylval = make_shared<NumB>(yytext); return T_NUM_B; }


{stringLexemaEnterExit}                 { BEGIN(STRING_LEXEMA); accumalateStringLexema(); }
<STRING_LEXEMA>[\\]                     { BEGIN(STRING_ESCAPE); accumalateStringLexema(); }
<STRING_LEXEMA>{stringLexemaEnterExit}  {   BEGIN(INITIAL); 
                                            accumalateStringLexema(); 
                                            accumalatedString[accumalatedStrLen] = 0; 
                                            yylval = make_shared<String>(accumalatedString); 
                                            accumalatedStrLen = 0; 
                                            return T_STRING; }
<STRING_LEXEMA><<EOF>>                  { BEGIN(INITIAL); output::errorLex(yylineno); return T_STRING; }
<STRING_LEXEMA>[\n]                     { BEGIN(INITIAL); output::errorLex(yylineno - 1); return T_STRING; }
<STRING_LEXEMA>[\r]                     { BEGIN(INITIAL); output::errorLex(yylineno - 1); return T_STRING; }
<STRING_LEXEMA>(.)                      { accumalateStringLexema(); }


<STRING_ESCAPE><<EOF>>                  { BEGIN(INITIAL); output::errorLex(yylineno); return T_STRING; }
<STRING_ESCAPE>.                        { BEGIN(STRING_LEXEMA); accumalateStringLexema(); }



{whitespace}                            ;
.                                       { output::errorLex(yylineno); }

%%

void accumalateStringLexema(void)
{
    for(int j = 0; j < yyleng; ++j)
    {
        //printf("%c", yytext[j]);
        accumalatedString[accumalatedStrLen + j] = yytext[j];
    }
    //printf("\n");

    accumalatedStrLen += yyleng;
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
        output::errorLex(yylineno);
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
        output::errorLex(yylineno);
    }

    return retval;
}
