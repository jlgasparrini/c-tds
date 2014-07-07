%{
  #include <stdio.h>
  #include "../SymbolsTable/Attribute.h"
  #include "y.tab.h"

  #define ERROR_MSG "Lexical error line %d.%d. Invalid symbol: \"%s\"\n"
  unsigned int line_numb = 1;
  unsigned int column_numb = 1;
  
  static inline void inc_column_numb() {
    column_numb += strlen(yytext);
  }

  static inline void save_value() {
    yylval.string_value = strdup(yytext);
  }
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
[\t]							  { column_numb += 4; }
\n                  { line_numb++; column_numb = 1; }
"/*"                { column_numb += 2; BEGIN(comment); }
<comment>"*/"	      { column_numb += 2; BEGIN(INITIAL); }
<comment>(.|\n)     { if (strcmp(yytext,"\n") == 0)
                        { line_numb++; column_numb = 1; }
                      else 
                        column_numb++; }
"//"(.)*            // found a comment 
"+"                 { column_numb++; return('+'); }
"-"                 { column_numb++; return('-'); }
"*"                 { column_numb++; return('*'); }
"/"                 { column_numb++; return('/'); }
"%"                 { column_numb++; return('%'); }
"!"                 { column_numb++; return('!'); }
"="                 { column_numb++; return('='); }
","                 { column_numb++; return(','); }
"<"                 { column_numb++; return('<'); }
">"                 { column_numb++; return('>'); }
"("                 { column_numb++; return('('); }
")"                 { column_numb++; return(')'); }
"{"                 { column_numb++; return('{'); }
"}"                 { column_numb++; return('}'); }
";"                 { column_numb++; return(';'); }
"["				          { column_numb++; return('['); }
"]"			            { column_numb++; return(']'); }
"int"               { inc_column_numb(); save_value(); return(INT_WORD); }
"float"             { inc_column_numb(); save_value(); return(FLOAT_WORD); }
"boolean"           { inc_column_numb(); save_value(); return(BOOLEAN_WORD); }
"+="                { inc_column_numb(); return(PLUSEQUAL); }
"-="                { inc_column_numb(); return(MINUSEQUAL); }
"=="                { inc_column_numb(); return(EQUAL); }
"!="				        { inc_column_numb(); return(DISTINCT); }
"<="                { inc_column_numb(); return(LEQUAL); }
">="			          { inc_column_numb(); return(GEQUAL); }
"||"                { inc_column_numb(); return(ORR); }
"&&"                { inc_column_numb(); return(ANDD); }
"print"						  { inc_column_numb(); return(PRINTT); }
{string}            { inc_column_numb(); save_value(); return(STRING); }
"externinvk"			  { inc_column_numb(); return(EXTERNINVK); }
"true"              { inc_column_numb(); save_value(); return(BOOLEAN); }
"false"             { inc_column_numb(); save_value(); return(BOOLEAN); }
{int}               { inc_column_numb(); save_value(); return(INTEGER); }
{float}						  { inc_column_numb(); save_value(); return(FLOAT); }
"break"             { inc_column_numb(); return(BREAK); }
"class"             { inc_column_numb(); return(CLASS); }
"continue"          { inc_column_numb(); return(CONTINUE); }
"if"                { inc_column_numb(); return(IF); }
"else"              { inc_column_numb(); return(ELSE); }
"while"             { inc_column_numb(); return(WHILE); }
"for"               { inc_column_numb(); return(FOR); }
"return"            { inc_column_numb(); return(RETURNN); }
"void"              { inc_column_numb(); return(VOID); }
{identifier}        { inc_column_numb(); save_value(); return(ID); }
.                   { printf(ERROR_MSG, line_numb, column_numb, yytext); }

%%
