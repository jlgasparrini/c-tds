%{
#  include  <stdio.h>
#  include  <ctype.h>
#  include  <string.h>
#  include  <stdlib.h>
#  include  "../SymbolsTable/Attribute.h"
#  include  "../SymbolsTable/SymbolsTable.h"
#  include  "../SymbolsTable/Utils.h"
#  include  "../ErrorsQueue/ErrorsQueue.h"

extern FILE *yyin;
ErrorsQueue *errorQ;						/* Errors Queue definition */
SymbolsTable symbolTable;					/* <----Symbols Table Definition----- */
unsigned char cantParams = 0;				/* Amount of parameters that a method will have */
PrimitiveType vaType;						/* Type of the variable or array */
ReturnType mType;							/* Return type of the method */
char *lastDefMethod, *lastCalledMethod;		/* Name of the last defined method (lastDefMethod) and the last called method (lastCalledMethod) */
int yydebug = 1;

int yyerror (char *str)
{
		printErrorList(errorQ);
        if (strcmp(str, "syntax error") == 0)
			printf ("%s",toString("Error GRAMATICO.","",""));
        else
			printf ("%s",toString("Error DESCONOCIDO: \"",str,"\"."));
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
		printErrorList(errorQ);
        printf("------Se termino de parsear.----------\n");
}

out(char *msg) {
        printf("%s\n", msg);
}


%}

%union
{
	char *stringValue;
	Attribute *at;
}


%start program

/* %token<stringValue> es solo para tokens */
%token<stringValue> FLOAT INTEGER BOOLEAN INTW FLOATW BOOLEANW ID PLUSEQUAL MINUSEQUAL
%token EQUAL DISTINCT GEQUAL LEQUAL OR AND 
%token BREAK IF CONTINUE ELSE RETURN WHILE CLASS FOR VOID EXTERNINVK STRING 
%nonassoc '<' '>' EQUAL DISTINCT GEQUAL LEQUAL
%left '+' '-'
%left '*' '/'
%left '%'
%type<at> expression conjunction inequality comparison relation term factor primary method_call location
%type<stringValue> assig_op
/* %type<at> es solo para no-terminales */

%%      /*  beginning  of  rules  section  */


/* ------------------- PROGRAM -------------------- */

program       :    CLASS ID '{' '}' {errorQ=initializeQueue(); finalizar();} 
              |    CLASS ID '{' {initializeSymbolsTable(&symbolTable); pushLevel(&symbolTable); errorQ=initializeQueue();} body {popLevel(&symbolTable); finalizar();} '}' 
              ;

body          :    fields_decls method_decl
              |    fields_decls
              |    method_decl
              ;

fields_decls  :    type fields ';' 			
              |    fields_decls type fields ';' 	
			  ;

fields        :    field 	
			  |    fields ',' field 	    
			  ;

field         :    ID					{pushElement(errorQ, &symbolTable, createVariable($1, vaType));}
              |    ID '[' INTEGER ']'	{pushElement(errorQ, &symbolTable, createArray($1, vaType, atoi($3)));}
              ;

type          :		INTW		{vaType = Int; mType = RetInt;} 
              |		FLOATW		{vaType = Float; mType = RetFloat;}
              |		BOOLEANW	{vaType = Bool; mType = RetBool;}
              ;

method_decl   :     type ID {lastDefMethod=$2; pushElement(errorQ,&symbolTable,createMethod($2,mType,0)); pushLevel(&symbolTable);} param block {popLevel(&symbolTable);}
              |		method_decl type ID {lastDefMethod=$3; pushElement(errorQ,&symbolTable,createMethod($3,mType,0)); pushLevel(&symbolTable);} param block {popLevel(&symbolTable);}
              |     VOID ID {lastDefMethod=$2; pushElement(errorQ,&symbolTable,createMethod($2,RetVoid,0)); pushLevel(&symbolTable);} param block {popLevel(&symbolTable);}
              |	    method_decl VOID ID {lastDefMethod=$3; pushElement(errorQ,&symbolTable,createMethod($3,RetVoid,0)); pushLevel(&symbolTable);} param block {popLevel(&symbolTable);}
              ;

param		  :    '(' ')' {cantParams = 0; setAmountOfParameters(searchIdInSymbolsTable(errorQ,&symbolTable,lastDefMethod),0);}
			  |    '(' {cantParams = 0;} parameters {setAmountOfParameters(searchIdInSymbolsTable(errorQ,&symbolTable,lastDefMethod),cantParams);} ')'
			  ;    /* esta bien hecho esto asi? no se cuentan primero todos los parametros dentro del no terminal "parameters" 
						y una vez que matchea con esta regla "param", setea cantParams en 0 y luego reduce a "param" ----------------------
						-------------------------------------------------------------------------------------------------------------------
						------------------------------------------------------------------------------------------------------------------*/
              
parameters    :		type ID {Attribute *aux = createParameter(lastDefinedMethod(&symbolTable),cantParams,$2,vaType);
								if (aux != NULL) {pushElement(errorQ,&symbolTable,aux); cantParams++;}}
			  |		type ID ',' {Attribute *aux = createParameter(lastDefinedMethod(&symbolTable),cantParams,$2,vaType);
								if (aux != NULL) {pushElement(errorQ,&symbolTable,aux); cantParams++;}} parameters 
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
			  |	   RETURN {checkReturn(errorQ,&symbolTable,lastDefMethod);}
			  |	   RETURN expression {checkReturnExpression(errorQ,&symbolTable,lastDefMethod,$2);}
              |    asignation 
              |    method_call                        
              ;
              
asignation    :    location assig_op expression {controlAssignation(errorQ,$1,$2,$3);}
			  ;
              
assig_op      :    '=' {$$ = "=";} 
              |    PLUSEQUAL {$$ = $1;}
              |    MINUSEQUAL {$$ = $1;}
              ;

/* -------------------- END OF STATEMENTS ------------------------------- */

/* -------------------- CONDITIONALS AND CICLES ------------------------------ */

conditional   :    IF '(' expression ')' block {controlVariableType(errorQ,$3,Bool);} ELSE block 
			  |    IF '(' expression ')' block {controlVariableType(errorQ,$3,Bool);}
			  ;

iteration     :    WHILE expression {controlVariableType(errorQ,$2,Bool);} block
              |    FOR ID '=' expression ',' expression {if ((*getVariableAttribute(errorQ,&symbolTable,$2)).decl.variable.type != Int)
															insertError(errorQ,toString("El identificador \"", $2, "\" no pertenece a una variable de tipo \"int\""));
														controlVariableType(errorQ,$4,Int); controlVariableType(errorQ,$6,Int);} block                
              ;                                                               

/* -------------------- END OF CONDITIONALS AND CICLES ------------------------------- */

/* -------------------- EXPRESSIONS ------------------------------- */

location      :    ID {$$ = getVariableAttribute(errorQ, &symbolTable, $1);}
              |    ID '[' term ']' {$$ = checkArrayPos(errorQ,&symbolTable,$1,$3);}
              ;

method_call   :	   ID '(' ')' {cantParams=0; lastCalledMethod = $1; $$ = getMethodAttribute(errorQ, &symbolTable, $1, cantParams);}
              |    ID '(' {cantParams=0; lastCalledMethod = $1;} expression_aux ')' {$$ = getMethodAttribute(errorQ,&symbolTable,$1,cantParams);}
              |    EXTERNINVK '(' STRING ',' typevoid ')' {if (mType != RetVoid) $$=createVariable("",mType);}
              |    EXTERNINVK '(' STRING ',' typevoid ',' externinvk_arg ')' {if (mType != RetVoid) $$=createVariable("",mType);}
              ;

expression_aux:    expression {cantParams++; correctParamBC(errorQ,&symbolTable,$1,lastCalledMethod,cantParams);}
			  |    expression {cantParams++; correctParamIC(errorQ,&symbolTable,$1,lastCalledMethod,cantParams);} ',' expression_aux 
			  ;
              
typevoid      :    type                            
              |    VOID {mType = RetVoid;} 
              ;

externinvk_arg:    arg                           
              |    externinvk_arg ',' arg       
              ;
							/* Se verifica que todas las expresiones de extern_invk_arg que se usen en externinvk tengan 
							el mismo tipo typeVoid. En caso de querer aplicar esta restriccion, eliminar el comentario de la siguiente linea */
arg           :    expression /*{if ((*$1).decl.variable.type != mType) insertError(errorQ,toString("Error en \"externinvk\". La expresion no retorna algo de tipo \"",getType(mType),"\"."));}*/
              |    STRING                     
              ;
              
expression    :    conjunction                   {$$ = $1;}                             
              |    expression OR conjunction     {$$ = returnOr($1, $3);}
              ;

conjunction   :    inequality                    {$$ = $1;}                                
              |    conjunction AND inequality    {$$ = returnAnd($1, $3);}
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
              |    ID				{$$ = getVariableAttribute(errorQ,&symbolTable,$1);}				
              |    ID '[' term ']'  {$$ = checkArrayPos(errorQ,&symbolTable,$1,$3);} 
              |    '(' expression ')'  {$$ = $2;}
              |    method_call         {if (methodReturnType(errorQ,&symbolTable,lastCalledMethod) == RetVoid)
										{	insertError(errorQ,toString("El metodo \"",lastCalledMethod,"\" no puede ser usado en una expresion ya que retorna void."));
											$$ = createVariable("",Int); /* creamos variables int por defecto ------------------------------- */
										}
										else $$ = $1;}
              ;

/* ------------------------- END OF EXPRESSIONS ------------------------------- */

%%

