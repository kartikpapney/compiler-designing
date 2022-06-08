/*
Write a lexical analyser for the assembly language described in the file attached. The program should take as input a text file containing an assembly program and print the stream of token values corresponding to the items in the input file. For identifiers and numbers the actual input item should also appear within brackets along with the token value. e.g. the output may look like:

17 20(100) 21(AGAIN) 14 20(3) 21(TERM) ....

Write the program once in plain C, and once using flex utility (later).

[Create the file token.h to put the token definitions. In the plain C implementation, you should also define the mnemonic table containing the mnemonic strings and the corresponding numeric token values.]
*/

/*
        Submitted By CSB19047 (Kartik Papney)
        Output from input.txt
        Output to output.txt
*/

%{
#include<stdio.h>
#include "token.h"
FILE *out;
%}

%%

[\n \t] {continue;}
"STOP" {fprintf(out, "%d ",TOKEN_STOP);}
"ADD" {fprintf(out, "%d ",TOKEN_ADD);}
"SUB" {fprintf(out, "%d ",TOKEN_SUB);}
"MULT" {fprintf(out, "%d ",TOKEN_MULT);}
"DIV" {fprintf(out, "%d ",TOKEN_DIV);}
"LOAD" {fprintf(out, "%d ",TOKEN_LOAD);}
"STORE" {fprintf(out, "%d ",TOKEN_STORE);}
"TRANS" {fprintf(out, "%d ",TOKEN_TRANS);}
"TRIM" {fprintf(out, "%d ",TOKEN_TRIM);}
"READ" {fprintf(out, "%d ",TOKEN_READ);}
"PRINT" {fprintf(out, "%d ",TOKEN_PRINT);}
"LIR" {fprintf(out, "%d ",TOKEN_LIR);}
"IIR" {fprintf(out, "%d ",TOKEN_IIR);}
"LOOP" {fprintf(out, "%d ",TOKEN_LOOP);}
"START" {fprintf(out, "%d ",TOKEN_START);}
"END" {fprintf(out, "%d ",TOKEN_END);}
"LTORG" {fprintf(out, "%d ",TOKEN_LTORG);}
"DS" {fprintf(out, "%d ",TOKEN_DS);}
"DC" {fprintf(out, "%d ",TOKEN_DC);}
"," {fprintf(out, "%d ",TOKEN_COMA);}
[0-9]+ {fprintf(out, "%d(%s) ",TOKEN_NUM,yytext);}
[a-zA-Z][a-zA-Z0-9]* {fprintf(out, "%d(%s) ",TOKEN_ID,yytext);}

%%

int yywrap(void){}

int main()
{  
        extern FILE *yyin;    // yyin as pointer of File type
         
        yyin = fopen("input.txt","r");
        out = fopen("output.txt", "w");
        yylex();
        return 0;
}