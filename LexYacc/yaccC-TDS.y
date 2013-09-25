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
extern lineNumb;
extern columnNumb;
ErrorsQueue *errorQ;
SymbolsTable symbolTable;   /* <----Definicion de la tabla de simbolos----- */
Attribute *auxAtr;          /* Atributo auxiliar usado para la creacion de nuevos atributos */           
unsigned char cantParams = 0;  /* Cantidad de parametros que tendra un metodo */
PrimitiveType vaType; /* Type of the variable or array */
ReturnType mType;     /* Return type of the method */
char* lastCalledMethod;

int yydebug = 1;

int yyerror (char *str)
{
		printErrorList(errorQ);
        if (strcmp(str, "syntax error") == 0)
            fprintf(stderr,"Error gramatico en la linea: %d.%d\n", lineNumb, columnNumb);
        else
            printf("ERROR DESCONOCIDO:%s\n", str);
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
	/* ver si se puede hacer solamente asi, y sino agregar un atributo de tipo int y otro de tipo float ------------------ */
	char *stringValue;
	Attribute *at;
}


%start program

/* %token<stringValue> es solo para tokens..*/
%token<stringValue> FLOAT INTEGER BOOLEAN INTW FLOATW BOOLEANW ID PLUSEQUAL MINUSEQUAL
%token EQUAL DISTINCT GEQUAL LEQUAL OR AND 
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

program       :    CLASS ID '{' '}' {finalizar();} 
              |    CLASS ID '{' {initializeSymbolsTable(&symbolTable); pushLevel(&symbolTable); errorQ=initializeQueue();} body {popLevel(&symbolTable); finalizar();} '}' 
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
field         :    ID					{pushElement(errorQ, &symbolTable, createVariable($1, vaType));}
              |    ID '[' INTEGER ']'	{pushElement(errorQ, &symbolTable, createArray($1, vaType, atoi($3)));}
              ;

type          :		INTW		{vaType = Int; mType = RetInt;} 
              |		FLOATW		{vaType = Float; mType = RetFloat;}
              |		BOOLEANW	{vaType = Bool; mType = RetVoid;}
              ;

method_decl   :     type ID {if (searchIdInSymbolsTable(&symbolTable, $2) == NULL) {Attribute *aux = createMethod($2, mType, 0); pushElement(errorQ, &symbolTable, aux); pushLevel(&symbolTable);}
							else insertError(errorQ, toString("El identificador \"", $2,"\" ya se encuentra definido."));} param block {popLevel(&symbolTable);}
              |		method_decl type ID {if (searchIdInSymbolsTable(&symbolTable, $3) == NULL) {Attribute *aux = createMethod($3, mType, 0); pushElement(errorQ, &symbolTable, aux); pushLevel(&symbolTable);}
							else insertError(errorQ, toString("El identificador \"",$3,"\" ya se encuentra definido."));} param block {popLevel(&symbolTable);}
              |     VOID ID {if (searchIdInSymbolsTable(&symbolTable, $2) == NULL) {Attribute *aux = createMethod($2, RetVoid, 0); pushElement(errorQ, &symbolTable, aux); pushLevel(&symbolTable);}
							else insertError(errorQ, toString("El identificador \"", $2,"\" ya se encuentra definido."));} param block {popLevel(&symbolTable);}
              |	    method_decl VOID ID {if (searchIdInSymbolsTable(&symbolTable, $3) == NULL) {Attribute *aux = createMethod($3, RetVoid, 0); pushElement(errorQ, &symbolTable, aux); pushLevel(&symbolTable);}
							else insertError(errorQ, toString("El identificador \"",$3,"\" ya se encuentra definido."));} param block {popLevel(&symbolTable);}
              ;

param		  :    '(' ')' {cantParams = 0;}
			  |    '(' {cantParams = 0;} parameters ')'
			  ;
              
parameters    :		type ID {Attribute *aux = createParameter(lastDefinedMethod(&symbolTable),cantParams,$2,vaType);
								if (aux != NULL) {pushElement(errorQ, &symbolTable,aux); cantParams++;}}
			  |		type ID ',' {Attribute *aux = createParameter(lastDefinedMethod(&symbolTable),cantParams,$2,vaType);
								if (aux != NULL) {pushElement(errorQ, &symbolTable,aux); cantParams++;}} parameters 
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

iteration     :    WHILE expression {} block
              |    FOR ID '=' expression ',' expression {} block                
              ;                                                               

/* -------------------- END OF CONDITIONALS AND CICLES ------------------------------- */

/* -------------------- EXPRESSIONS ------------------------------- */

location      :    ID {$$ = getVariableAttribute(errorQ, &symbolTable, $1);}
              |    ID '[' term ']' {$$ = getArrayAttribute(errorQ, &symbolTable, $1, (*$3).decl.variable.value.intVal);}
              ;

method_call   :	   ID '(' ')'   {cantParams=0; lastCalledMethod=$1; $$ = getMethodAttribute(errorQ, &symbolTable, $1, cantParams);}
              |    ID '('  {cantParams=0; lastCalledMethod=$1;} expression_aux ')' {ReturnType rt = methodReturnType(errorQ, &symbolTable, $1);
							/*	if (rt == RetVoid)  ESTE METHOD_CALL PUEDE SER LLAMADO FUERA DE UNA EXPRESION, POR LO QUE NO TENDRIA QUE OBLIGAR
													A QUE RETORNE ALGO DE TIPO PRIMITIVO. HAY QUE CORREGIR ESTO-------------------------------
									insertError(eq, toString("El metodo \"", lastCalledMethod, "\" retorna tipo void, no puede ser usado en una expresion."));

								else
								{
									/* ESTA BIEN ESTO? createVariable toma algo de tipo PrimitiveType pero se la pasa rt que es de ReturnType
									Attribute *aux=createVariable("",rt); setVariableValue(aux,rt,$1); /*habria que ver como setear el
									valor que retorna la llamada del metodo (que cada metodo tenga un VarValue donde almacenar el resultado)
									$$ = aux;
								}*/
							}
			  
              |    EXTERNINVK '(' STRING ',' typevoid ')'  {if (mType != RetVoid) 
															{	Attribute *aux=createVariable("",mType); }
														}
              |    EXTERNINVK '(' STRING ',' typevoid ',' externinvk_arg ')'   {Attribute *at; $$ = at;}
              ;

expression_aux:    expression {cantParams++; correctParamBC(errorQ, &symbolTable,$1,lastCalledMethod,cantParams);}
			  |    expression {cantParams++; correctParamIC(errorQ, &symbolTable,$1,lastCalledMethod,cantParams);} ',' expression_aux 

			  ;
              
typevoid      :    type                            
              |    VOID {mType = RetVoid;} 
              ;

externinvk_arg:    arg                           
              |    externinvk_arg ',' arg       
              ;
												
arg           :    expression                  
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
              |    ID				{$$ = getVariableAttribute(errorQ, &symbolTable, $1);}								/* ----PREGUNTAR--------- */
              |    ID '[' term ']'  {$$ = getArrayAttribute(errorQ, &symbolTable, $1, (*$3).decl.variable.value.intVal);/* aca deberiamos verificar que $3 es de tipo int en lugar de suponerlo?*/} 
              |    '(' expression ')'  {$$ = $2;}
              |    method_call         {$$ = $1;}
              ;

/* ------------------------- END OF EXPRESSIONS ------------------------------- */

%%

