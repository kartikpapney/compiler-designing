%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "token.h"


int LINE = 0;
FILE *fp, *fpout, *out;

%}


%%
[\n] {LINE++; continue;}
[\t] {continue;}
"STOP" {fprintf(out, "%d ",TOKEN_STOP); putw(TOKEN_STOP, fpout);}
"ADD" {fprintf(out, "%d ",TOKEN_ADD); putw(TOKEN_ADD, fpout);}
"SUB" {fprintf(out, "%d ",TOKEN_SUB); putw(TOKEN_SUB, fpout);}
"MULT" {fprintf(out, "%d ",TOKEN_MULT); putw(TOKEN_MULT, fpout);}
"DIV" {fprintf(out, "%d ",TOKEN_DIV); putw(TOKEN_DIV, fpout);}
"LOAD" {fprintf(out, "%d ",TOKEN_LOAD); putw(TOKEN_LOAD, fpout);}
"STORE" {fprintf(out, "%d ",TOKEN_STORE); putw(TOKEN_STORE, fpout);}
"TRANS" {fprintf(out, "%d ",TOKEN_TRANS); putw(TOKEN_TRANS, fpout);}
"TRIM" {fprintf(out, "%d ",TOKEN_TRIM); putw(TOKEN_TRIM, fpout);}
"READ" {fprintf(out, "%d ",TOKEN_READ); putw(TOKEN_READ, fpout);}
"PRINT" {fprintf(out, "%d ",TOKEN_PRINT); putw(TOKEN_PRINT, fpout);}
"LIR" {fprintf(out, "%d ",TOKEN_LIR); putw(TOKEN_LIR, fpout);}
"IIR" {fprintf(out, "%d ",TOKEN_IIR); putw(TOKEN_IIR, fpout);}
"LOOP" {fprintf(out, "%d ",TOKEN_LOOP); putw(TOKEN_LOOP, fpout);}
"START" {fprintf(out, "%d ",TOKEN_START); putw(TOKEN_START, fpout);}
"END" {fprintf(out, "%d ",TOKEN_END); putw(TOKEN_END, fpout);}
"LTORG" {fprintf(out, "%d ",TOKEN_LTORG); putw(TOKEN_LTORG, fpout);}
"DS" {fprintf(out, "%d ",TOKEN_DS); putw(TOKEN_DS, fpout);}
"DC" {fprintf(out, "%d ",TOKEN_DC); putw(TOKEN_DC, fpout);}
"," {fprintf(out, "%d ",TOKEN_COMA); putw(TOKEN_COMA, fpout);}
[0-9]+ {fprintf(out, "%d(%s) ",TOKEN_NUM,yytext); putw(TOKEN_NUM, fpout);}
[a-zA-Z][a-zA-Z0-9]* {fprintf(out, "%d(%s) ",TOKEN_ID,yytext); putw(TOKEN_ID, fpout); printf("%s         --------------->           %d\n", yytext, LINE);};

%%

int yywrap(){}

int main()
{
    printf("Submitted By CSB19047 (Kartik Papney)\n\n");
    printf("-------------Below is the Symbol Table-----------------\n\n");
    printf("SYMBOL                            LINE NO\n");
    extern FILE *yyin;    // yyin as pointer of File type
    out = fopen("output.txt", "w");
    yyin = fopen("test.asm", "r");
    fpout = fopen("output.bin", "w");

  yylex();
  return 0;
}