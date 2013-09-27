%{
#include <stdio.h>
#include "../SymbolsTable/Attribute.h"
#include "y.tab.h"

unsigned int lineNumb = 1;
unsigned int columnNumb = 1;
%}
%x comment

boolean     "boolean"
true        "true"
false       "false"
break       "break"
class       "class"
continue    "continue"
if          "if"
else        "else"
while       "while"
for         "for"
return      "return"
void        "void"
intw        "int"
floatw      "float"
letter      [a-zA-Z]
digit       [0-9]
dot         "."
int         {digit}+
float		{int}{expVal}|{int}*{dot}{int}{expVal}?
plus        "+"
minus       "-"
mult        "*"
div         "/"
mod         "%"
admClose    "!"
questClose  "?"
twoPoints   ":"
assign      "="
plusequal   "+="
minusequal  "-="
equal	    "=="
distinct    "!="
comma       ","
oangle      "<"
cangle      ">"
lequal      "<="
gequal      ">="
oparen      "("
cparen      ")"
obrace      "{"
cbrace      "}"
or          "||"
and         "&&"
dotcomma    ";"
string      "\""{ascii}*"\"" 
expVal      [Ee][+-]{int}
externinvk  "externinvk"
ascii		[-!-:<-~ ]	
obracket	"["
cbracket	"]"

%%

[ ]							    {columnNumb++;};
[\t]							{columnNumb=columnNumb + 4;}
\n                              {lineNumb++; columnNumb = 1;}
"/*"                            {columnNumb = columnNumb + 2; BEGIN(comment);}
<comment>"*/"	                {columnNumb = columnNumb + 2; BEGIN(INITIAL);}
<comment>(.|\n)                 {if (strcmp(yytext,"\n") == 0) {lineNumb++; columnNumb=1;} else columnNumb++;}
"//"(.)*                        
{plus}                          {columnNumb++; return('+');}
{minus}                         {columnNumb++; return('-');}
{mult}                          {columnNumb++; return('*');}
{div}                           {columnNumb++; return('*');}
{mod}                           {columnNumb++; return('%');}
{admClose}                      {columnNumb++; return('!');}
{questClose}                    {columnNumb++; return('?');}
{twoPoints}                     {columnNumb++; return(':');}
{assign}                        {columnNumb++; return('=');}
{comma}                         {columnNumb++; return(',');}
{oangle}                        {columnNumb++; return('<');}
{cangle}                        {columnNumb++; return('>');}
{oparen}                        {columnNumb++; return('(');}
{cparen}                        {columnNumb++; return(')');}
{obrace}                        {columnNumb++; return('{');}
{cbrace}                        {columnNumb++; return('}');}
{dotcomma}                      {columnNumb++; return(';');}
{obracket}					    {columnNumb++; return('[');}
{cbracket}					    {columnNumb++; return(']');}
{intw}                          {columnNumb=columnNumb+strlen(yytext); yylval.stringValue = strdup(yytext); return(INTW);}
{floatw}                        {columnNumb=columnNumb+strlen(yytext); yylval.stringValue = strdup(yytext); return(FLOATW);}
{boolean}                       {columnNumb=columnNumb+strlen(yytext); yylval.stringValue = strdup(yytext); return(BOOLEANW);}
{plusequal}                     {columnNumb=columnNumb+strlen(yytext); return(PLUSEQUAL);}
{minusequal}                    {columnNumb=columnNumb+strlen(yytext); return(MINUSEQUAL);}
{equal}                         {columnNumb=columnNumb+strlen(yytext); return(EQUAL);}
{distinct}					   	{columnNumb=columnNumb+strlen(yytext); return(DISTINCT);} 
{lequal}                        {columnNumb=columnNumb+strlen(yytext); return(LEQUAL);}
{gequal}					   	{columnNumb=columnNumb+strlen(yytext); return(GEQUAL);}
{or}                            {columnNumb=columnNumb+strlen(yytext); return(OR);}
{and}                           {columnNumb=columnNumb+strlen(yytext); return(AND);}
{string}                        {columnNumb=columnNumb+strlen(yytext); return(STRING);}
{externinvk}					{columnNumb=columnNumb+strlen(yytext); return(EXTERNINVK);}
{true}                          {columnNumb=columnNumb+strlen(yytext); yylval.stringValue = strdup(yytext); return(BOOLEAN);}
{false}                         {columnNumb=columnNumb+strlen(yytext); yylval.stringValue = strdup(yytext); return(BOOLEAN);}
{int}                           {columnNumb=columnNumb+strlen(yytext); yylval.stringValue = strdup(yytext); return(INTEGER);}
{float}						    {columnNumb=columnNumb+strlen(yytext); yylval.stringValue = strdup(yytext); return(FLOAT);}
{break}                         {columnNumb=columnNumb+strlen(yytext); return(BREAK);}
{class}                         {columnNumb=columnNumb+strlen(yytext); return(CLASS);}
{continue}                      {columnNumb=columnNumb+strlen(yytext); return(CONTINUE);}
{if}                            {columnNumb=columnNumb+strlen(yytext); return(IF);}
{else}                          {columnNumb=columnNumb+strlen(yytext); return(ELSE);}
{while}                         {columnNumb=columnNumb+strlen(yytext); return(WHILE);}
{for}                           {columnNumb=columnNumb+strlen(yytext); return(FOR);}
{return}                        {columnNumb=columnNumb+strlen(yytext); return(RETURN);}
{void}                          {columnNumb=columnNumb+strlen(yytext); return(VOID);}
{letter}({letter}|{digit}|_)*   {columnNumb=columnNumb+strlen(yytext); yylval.stringValue = strdup(yytext); return(ID);}
.                               {printf( "Error lexico en la linea: %d.%d.   Simbolo invalido: \"%s\"\n",lineNumb,columnNumb,yytext);}


%%
