%{
#  include  <stdio.h>
#  include  <ctype.h>
#  include  <string.h>
#  include  <stdlib.h>
#  include  "../SymbolsTable/Attribute.h"
#  include  "../SymbolsTable/SymbolsTable.h"
#  include  "../SymbolsTable/Utils.h"

extern FILE *yyin;
SymbolsTable symbolTable;   /* <----Definicion de la tabla de simbolos----- */
Attribute *auxAtr;          /* Atributo auxiliar usado para la creacion de nuevos atributos */           
unsigned char cantParams = 0;  /* Cantidad de parametros que tendra un metodo */
PrimitiveType vaType; /* Type of the variable or array */
ReturnType mType;     /* Return type of the method */

int yydebug = 1;

int yyerror (const char *str)
{
        fprintf(stderr,"Error gramatico en la linea:   %s\n", str); /* tratar de usar yylineno */
        return 0;
}
 
int yywrap()
{
        return 1;
} 
  
main( argc, argv )
    int argc;
    char **argv;
    {
        ++argv, --argc;	/* skip over program name */
        if ( argc > 0 )
                yyin = fopen( argv[0], "r" );
        else
                yyin = stdin;
                yyparse();
    }

finalizar() {
        printf("se parseo correctamente\n");
}

out(char *msg) {
        printf("%s\n", msg);
}


%}

%union
{
	/* ver si se puede hacer solamente asi, y sino agregar un atributo de tipo int y otro de tipo float ------------------ */
	char *stringValue;
	Attribute *at;
}


%start program

/* %token<stringValue> es solo para tokens..*/
%token<stringValue> FLOAT INTEGER BOOLEAN INTW FLOATW BOOLEANW ID
%token PLUSEQUAL MINUSEQUAL EQUAL DISTINCT GEQUAL LEQUAL OR AND 
%token BREAK IF CONTINUE ELSE RETURN WHILE CLASS FOR VOID EXTERNINVK STRING 
%nonassoc '<' '>' EQUAL DISTINCT GEQUAL LEQUAL
%left '+' '-'
%left '*' '/'
%left '%'
%type<at> expression conjunction inequality comparison relation term factor primary method_call location

/* %type<at> es solo para no-terminales!! */
/*      %type<at> field      */

%%      /*  beginning  of  rules  section  */


/* ------------------- PROGRAM -------------------- */

program       :    CLASS ID '{' '}' 
              |    CLASS ID '{' {initializeSymbolsTable(&symbolTable); pushLevel(&symbolTable);} body {popLevel(&symbolTable);} '}' 
              ;

body          :    fields_decls method_decl
              |    fields_decls
              |    method_decl
              ;
			     						/* o $$1.at.decl.variable.type */
fields_decls  :    type fields ';' 			
              |    fields_decls type fields ';' 	
			  ;

fields        :    field 	
			  |    fields ',' field 	    
			  ;
										/*aca hay que crear el atributo nuevo*/
field         :    ID					{pushElement(&symbolTable, createVariable($1, vaType));}
              |    ID '[' INTEGER ']'	{pushElement(&symbolTable, createArray($1, vaType, atoi($3)));}
              ;

type          :		INTW		{vaType = Int; mType = RetInt;} 
              |		FLOATW		{vaType = Float; mType = RetFloat;}
              |		BOOLEANW	{vaType = Bool; mType = RetVoid;}
              ;

method_decl   :     type ID {if (searchIdInSymbolsTable(&symbolTable, $2) == NULL) {Attribute *aux = createMethod($2, mType, 0); pushElement(&symbolTable, aux); pushLevel(&symbolTable);}
							else printf("El identificador \"%s\" ya se encuentra definido.\n", $2);} param block {popLevel(&symbolTable);}
              |		method_decl type ID {if (searchIdInSymbolsTable(&symbolTable, $3) == NULL) {Attribute *aux = createMethod($3, mType, 0); pushElement(&symbolTable, aux); pushLevel(&symbolTable);}
							else printf("El identificador \"%s\" ya se encuentra definido.\n", $3);} param block {popLevel(&symbolTable);}
              |     VOID ID {if (searchIdInSymbolsTable(&symbolTable, $2) == NULL) {Attribute *aux = createMethod($2, RetVoid, 0); pushElement(&symbolTable, aux); pushLevel(&symbolTable);}
							else printf("El identificador \"%s\" ya se encuentra definido.\n", $2);} param block {popLevel(&symbolTable);}
              |	    method_decl VOID ID {if (searchIdInSymbolsTable(&symbolTable, $3) == NULL) {Attribute *aux = createMethod($3, RetVoid, 0); pushElement(&symbolTable, aux); pushLevel(&symbolTable);}
							else printf("El identificador \"%s\" ya se encuentra definido.\n", $3);} param block {popLevel(&symbolTable);}
              ;

param		  :    '(' ')' {cantParams = 0;}
			  |    '(' {cantParams = 0;} parameters ')'
			  ;
              
parameters    :		type ID {Attribute *aux = createParameter(lastDefinedMethod(&symbolTable),cantParams,$2,vaType);
								if (aux != NULL) {pushElement(&symbolTable,aux); cantParams++;}}
			  |		type ID ',' {Attribute *aux = createParameter(lastDefinedMethod(&symbolTable),cantParams,$2,vaType);
								if (aux != NULL) {pushElement(&symbolTable,aux); cantParams++;}} parameters 
			  ;

block         :    '{' '}'
			  |    '{' codeBlock '}' 
			  ;

codeBlock     :    fields_decls statements
              |    statements
              |    fields_decls
              ;

statements    :    statement
              |    statements statement 
              ;

/* -------------------- END OF PROGRAM ------------------------------- */

/* -------------------- STATEMENTS ------------------------------- */

statement     :    conditional 
              |    iteration 
              |    action ';'     
              |    block
              ;
              
action        :
              |    BREAK 
              |    CONTINUE 
			  |	   RETURN
			  |	   RETURN expression
              |    asignation 
              |    method_call                        
              ;
              
asignation    :    location assig_op expression;
              
assig_op      :    '=' 
              |    PLUSEQUAL
              |    MINUSEQUAL
              ;

/* -------------------- END OF STATEMENTS ------------------------------- */

/* -------------------- CONDITIONALS AND CICLES ------------------------------ */

conditional   :    IF '(' expression ')' block ELSE block
			  |    IF '(' expression ')' block
			  ;

iteration     :    WHILE expression block
              |    FOR ID '=' expression ',' expression block                  
              ;                                                               

/* -------------------- END OF CONDITIONALS AND CICLES ------------------------------- */

/* -------------------- EXPRESSIONS ------------------------------- */

location      :    ID {$$ = getVariableAttribute(&symbolTable, $1);}
              |    ID '[' term ']' {$$ = getArrayAttribute(&symbolTable, $1, (*$3).decl.variable.value.intVal);}
              ;

method_call   :	   ID '(' ')'   { auxAtr = searchIdInSymbolsTable(&symbolTable, $1);
                                    if(auxAtr == NULL) 
                                        printf("El metodo \"%s\" no esta definido.\n", $1);
                                    else
                                    {
                                        if((*auxAtr).type != Method)
	                                        printf("El identificador \"%s\" no es un metodo.\n", $1);
                                        else
                                        { 
                                            if ((*auxAtr).decl.method.paramSize > 0)
												if ((*auxAtr).decl.method.paramSize == 1)
													printf("El metodo \"%s\" no contiene su parametro correspondiente.\n", $1);
												else
													printf("El metodo \"%s\" no contiene sus %d parametros correspondientes.\n", $1, (*auxAtr).decl.method.paramSize);
                                        }
                                    }
                                }
              |    ID '('{cantParams=0;} expression_aux ')' { auxAtr = searchIdInSymbolsTable(&symbolTable, $1);
                                                if(auxAtr == NULL) 
                                                    printf("El metodo \"%s\" no esta definido.\n", $1);
                                                else
                                                {
                                                    if((*auxAtr).type != Method)
                                                    printf("El identificador \"%s\" no es un metodo.\n", $1);
                                                    else
                                                    { 
                                                        if ((*auxAtr).decl.method.paramSize != cantParams)
                                                           printf("El metodo \"%s\" no tiene la misma cantidad de parametros.\n", $1);
                                                    //bjdsabdjsadas
                                                    }
                                                }
                                            }   
              |    EXTERNINVK '(' STRING ',' typevoid ')'  {Attribute *at; $$ = at;}
              |    EXTERNINVK '(' STRING ',' typevoid ',' externinvk_arg ')'   {Attribute *at; $$ = at;}
              ;

expression_aux:    expression {cantParams++;}                       
			  |    expression_aux ',' {cantParams++;} expression    
			  ;
              
typevoid      :    type                            
              |    VOID                           
              ;

externinvk_arg:    arg                           
              |    externinvk_arg ',' arg       
              ;
												/*-------------PREGUNTAR------------------*/
arg           :    expression                  /* VER QUE SE PUEDE HACER CON EXPRESSION EN ESTE CASO!! ---------------------------------------*/
              |    STRING                     
              ;
              
expression    :    conjunction                   {$$ = $1;}                             
              |    expression OR conjunction     {$$ = returnOr($1, $3);}
              ;

conjunction   :    inequality                        {$$ = $1;}                                
              |    conjunction AND inequality        {$$ = returnAnd($1, $3);}
              ;

inequality    :    comparison                       {$$ = $1;}                             
              |    inequality DISTINCT comparison   {$$ = returnDistinct($1, $3);}
              ;

comparison    :    relation                   {$$ = $1;} 
              |    relation EQUAL relation    {$$ = returnEqual($1, $3);}
              ;

relation      :    term                 {$$ = $1;}
              |    term '<' term        {$$ = returnMinorComparison($1, $3);}
              |    term '>' term        {$$ = returnMajorComparison($1, $3);}
              |    term GEQUAL term     {$$ = returnGEqualComparison($1, $3);}
              |    term LEQUAL term     {$$ = returnLEqualComparison($1, $3);}
              ;

term          :    factor          {$$ = $1;}
              |    term '+' factor {$$ = returnAdd($1, $3);}
              |    term '-' factor {$$ = returnSub($1, $3);} 
              |    term '%' factor {$$ = returnMod($1, $3);} 
              |    term '/' factor {$$ = returnDiv($1, $3);} 
              |    term '*' factor {$$ = returnMult($1, $3);} 
              ;

factor        :    primary     {$$ = $1;}  
              |    '!' factor  {$$ = $2;} 
              |    '-' factor  {$$ = $2;}
              ;

primary       :    INTEGER			{Attribute *aux = createVariable("", Int); setVariableValue(aux,Int,$1); $$=aux;}
              |    FLOAT            {Attribute *aux = createVariable("", Float); setVariableValue(aux,Float,$1); $$=aux;}
              |    BOOLEAN          {Attribute *aux = createVariable("", Bool); setVariableValue(aux,Bool,$1); $$=aux;}
              |    ID				{$$ = getVariableAttribute(&symbolTable, $1);}								/* ----PREGUNTAR--------- */
              |    ID '[' term ']'  {$$ = getArrayAttribute(&symbolTable, $1, (*$3).decl.variable.value.intVal);/* aca deberiamos verificar que $3 es de tipo int en lugar de suponerlo?*/} 
              |    '(' expression ')'  {$$ = $2;}
              |    method_call         {$$ = $1;}
              ;

/* ------------------------- END OF EXPRESSIONS ------------------------------- */

%%

