%{
  #include <stdio.h>
  #include "../SymbolsTable/Attribute.h"
  #include "y.tab.h"

  unsigned int line_numb = 1;
  unsigned int column_numb = 1;
  char* error_message = "Lexical error line %d.%d. Invalid symbol: \"%s\"\n";
%}

%x comment

letter              [a-zA-Z]
digit               [0-9]
exp_val             [Ee][+-]{int}
dot                 "."
int                 {digit}+
float		            -?{int}{exp_val}|-?{int}*{dot}{int}{exp_val}?
string              "\""{ascii}*"\""
ascii		            [-!#-:<-~ ]
identifier          {letter}({letter}|{digit}|_)*

%%

[ ]							    { column_numb++; }
[\t]							  { column_numb = column_numb + 4; }
\n                  { line_numb++; column_numb = 1; }
"/*"                { column_numb = column_numb + 2;
                      BEGIN(comment); }
<comment>"*/"	      { column_numb = column_numb + 2;
                      BEGIN(INITIAL); }
<comment>(.|\n)     { if (strcmp(yytext,"\n") == 0)
                        { line_numb++; column_numb = 1; }
                      else 
                        column_numb++; }
"//"(.)*             
"+"                 { column_numb++;
                      return('+'); }
"-"                 { column_numb++;
                      return('-'); }
"*"                 { column_numb++;
                      return('*'); }
"/"                 { column_numb++;
                      return('/'); }
"%"                 { column_numb++;
                      return('%'); }
"!"                 { column_numb++;
                      return('!'); }
"="                 { column_numb++;
                      return('='); }
","                 { column_numb++;
                      return(','); }
"<"                 { column_numb++;
                      return('<'); }
">"                 { column_numb++;
                      return('>'); }
"("                 { column_numb++;
                      return('('); }
")"                 { column_numb++;
                      return(')'); }
"{"                 { column_numb++;
                      return('{'); }
"}"                 { column_numb++;
                      return('}'); }
";"                 { column_numb++;
                      return(';'); }
"["				          { column_numb++;
                      return('['); }
"]"			            { column_numb++;
                      return(']'); }
"int"               { column_numb = column_numb + strlen(yytext);
                      yylval.string_value = strdup(yytext); 
                      return(INT_WORD); }
"float"             { column_numb = column_numb + strlen(yytext);
                      yylval.string_value = strdup(yytext); 
                      return(FLOAT_WORD); }
"boolean"           { column_numb = column_numb + strlen(yytext);
                      yylval.string_value = strdup(yytext);
                      return(BOOLEAN_WORD); }
"+="                { column_numb = column_numb + strlen(yytext);
                      return(PLUSEQUAL); }
"-="                { column_numb = column_numb + strlen(yytext);
                      return(MINUSEQUAL); }
"=="                { column_numb = column_numb + strlen(yytext);
                      return(EQUAL); }
"!="				        { column_numb = column_numb + strlen(yytext);
                      return(DISTINCT); }
"<="                { column_numb = column_numb + strlen(yytext);
                      return(LEQUAL); }
">="			          { column_numb = column_numb + strlen(yytext);
                      return(GEQUAL); }
"||"                { column_numb = column_numb + strlen(yytext);
                      return(ORR); }
"&&"                { column_numb = column_numb + strlen(yytext);
                      return(ANDD); }
"print"						  { column_numb = column_numb + strlen(yytext);
                      return(PRINTT); }
{string}            { column_numb = column_numb + strlen(yytext);
                      yylval.string_value = strdup(yytext);
                      return(STRING); }
"externinvk"			  { column_numb = column_numb + strlen(yytext);
                      return(EXTERNINVK); }
"true"              { column_numb = column_numb + strlen(yytext);
                      yylval.string_value = strdup(yytext);
                      return(BOOLEAN); }
"false"             { column_numb = column_numb + strlen(yytext);
                      yylval.string_value = strdup(yytext);
                      return(BOOLEAN); }
{int}               { column_numb = column_numb + strlen(yytext);
                      yylval.string_value = strdup(yytext);
                      return(INTEGER); }
{float}						  { column_numb = column_numb + strlen(yytext);
                      yylval.string_value = strdup(yytext);
                      return(FLOAT); }
"break"             { column_numb = column_numb + strlen(yytext);
                      return(BREAK); }
"class"             { column_numb = column_numb + strlen(yytext);
                      return(CLASS); }
"continue"          { column_numb = column_numb + strlen(yytext);
                      return(CONTINUE); }
"if"                { column_numb = column_numb + strlen(yytext);
                      return(IF); }
"else"              { column_numb = column_numb + strlen(yytext);
                      return(ELSE); }
"while"             { column_numb = column_numb + strlen(yytext);
                      return(WHILE); }
"for"               { column_numb = column_numb + strlen(yytext);
                      return(FOR); }
"return"            { column_numb = column_numb + strlen(yytext);
                      return(RETURNN); }
"void"              { column_numb = column_numb + strlen(yytext);
                      return(VOID); }
{identifier}        { column_numb = column_numb + strlen(yytext);
                      yylval.string_value = strdup(yytext);
                      return(ID); }
.                   { printf(error_message, line_numb, column_numb, yytext); }

%%
