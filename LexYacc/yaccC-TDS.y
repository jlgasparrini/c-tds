%{
#  include  <stdio.h>
#  include  <ctype.h>
#  include  <string.h>
#  include  <stdlib.h>
#  include  "../SymbolsTable/Attribute.h"
#  include  "../SymbolsTable/SymbolsTable.h"
#  include  "../SymbolsTable/StringStack.h"
#  include  "../SymbolsTable/Utils.h"
#  include  "../ErrorsQueue/ErrorsQueue.h"

extern FILE *yyin;
ErrorsQueue *errorQ;						/* Errors Queue definition */
SymbolsTable symbolTable;					/* <----Symbols Table Definition----- */
StringStack *paramsStack, *methodsIDStack;  /* StringStack containing the amount of parameters and lastCalledMethods in each level of method_call*/
unsigned char cantParams = 0, returns;		/* Amount of parameters and amount of returns that a method will have. */
unsigned char iter = 0;						/* Number of "while" or "for" in the current block */
PrimitiveType vaType;						/* Type of the variable or array */
ReturnType mType;							/* Return type of the method */
char *lastDefMethod, *lastCalledMethod = "";/* Name of the last defined method (lastDefMethod) and the last called method (lastCalledMethod) */
int yydebug = 1;

int yyerror (char *str)
{
		printErrorList(errorQ);
        deleteAllErrors(errorQ);
        if (strcmp(str, "syntax error") == 0)
			printf("%s\n",toString("Error GRAMATICO.","",""));
        else
			printf("%s\n",toString("Error DESCONOCIDO: \"",str,"\"."));
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
        deleteAllErrors(errorQ);
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
              |    CLASS ID '{' {initializeSymbolsTable(&symbolTable); pushLevel(&symbolTable); errorQ=initializeQueue();
								paramsStack=initializeSS(); methodsIDStack=initializeSS();} body 
								{checkMain(errorQ,&symbolTable); popLevel(&symbolTable); finalizar();} '}' 
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

field         :    ID			{pushElement(errorQ, &symbolTable, createVariable($1, vaType));}
              |    ID '[' INTEGER {if (atoi($3) <= 0) insertError(errorQ,toString("Error en definicion del arreglo \"",$1,"\". El tamaño del arreglo debe ser un entero mayor que 0."));
										pushElement(errorQ, &symbolTable, createArray($1, vaType, atoi($3)));} ']'	
              ;

type          :		INTW		{vaType = Int; mType = RetInt;} 
              |		FLOATW		{vaType = Float; mType = RetFloat;}
              |		BOOLEANW	{vaType = Bool; mType = RetBool;}
              ;

method_decl   :     type ID {lastDefMethod=$2; pushElement(errorQ,&symbolTable,createMethod($2,mType,0)); pushLevel(&symbolTable); returns=0;} param block {popLevel(&symbolTable); if(returns==0) insertError(errorQ,toString("El metodo \"",$2,"\" debe tener al menos un return."));}
              |		method_decl type ID {lastDefMethod=$3; pushElement(errorQ,&symbolTable,createMethod($3,mType,0)); pushLevel(&symbolTable); returns=0;} param block {popLevel(&symbolTable); if(returns==0) insertError(errorQ,toString("El metodo \"",$3,"\" debe tener al menos un return."));}
              |     VOID ID {lastDefMethod=$2; pushElement(errorQ,&symbolTable,createMethod($2,RetVoid,0)); pushLevel(&symbolTable); returns=0;} param block {popLevel(&symbolTable); if(returns==0) insertError(errorQ,toString("El metodo \"",$2,"\" debe tener al menos un return."));}
              |	    method_decl VOID ID {lastDefMethod=$3; pushElement(errorQ,&symbolTable,createMethod($3,RetVoid,0)); pushLevel(&symbolTable); returns=0;} param block {popLevel(&symbolTable); if(returns==0) insertError(errorQ,toString("El metodo \"",$3,"\" debe tener al menos un return."));}
              ;

param		  :    '(' {cantParams = 0; setAmountOfParameters(searchIdInSymbolsTable(errorQ,&symbolTable,lastDefMethod),0);} ')' 
			  |    '(' {if (strcmp(lastDefMethod,"main") == 0)
							insertError(errorQ,toString("El metodo \"main\" no debe contener parametros.","","")); cantParams = 0;}
					parameters {setAmountOfParameters(searchIdInSymbolsTable(errorQ,&symbolTable,lastDefMethod),cantParams);} ')'
			  ;
              
parameters    :		type ID {Attribute *aux = createParameter(lastDefinedMethod(&symbolTable),cantParams,$2,vaType);
								if (aux != NULL) {pushElement(errorQ,&symbolTable,aux); cantParams++;}}
			  |		type ID {Attribute *aux = createParameter(lastDefinedMethod(&symbolTable),cantParams,$2,vaType);
								if (aux != NULL) {pushElement(errorQ,&symbolTable,aux); cantParams++;}} ',' parameters 
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
              |    {pushLevel(&symbolTable);} block {popLevel(&symbolTable);}
              ;
              
action        :
              |    BREAK {if (iter==0) insertError(errorQ,toString("Error. Solo se puede usar la sentencia \"break\" dentro de un ciclo.","",""));}
              |    CONTINUE {if (iter==0) insertError(errorQ,toString("Error. Solo se puede usar la sentencia \"continue\" dentro de un ciclo.","",""));}
			  |	   RETURN {returns++; checkReturn(errorQ,&symbolTable,lastDefMethod);}
			  |	   RETURN expression {returns++; checkReturnExpression(errorQ,&symbolTable,lastDefMethod,$2);}
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

iteration     :    WHILE expression {controlVariableType(errorQ,$2,Bool); iter++;} block {iter--;}
              |    FOR ID {if ((*getVariableAttribute(errorQ,&symbolTable,$2)).decl.variable.type != Int)
							insertError(errorQ,toString("El identificador \"", $2, "\" no pertenece a una variable de tipo \"int\""));}
					'=' expression ',' expression {controlVariableType(errorQ,$5,Int); controlVariableType(errorQ,$7,Int); iter++;} block {iter--;}
              ;                                                               

/* -------------------- END OF CONDITIONALS AND CICLES ------------------------------- */

/* -------------------- EXPRESSIONS ------------------------------- */

location      :    ID {$$ = getVariableAttribute(errorQ, &symbolTable, $1);}
              |    ID '[' term ']' {$$ = checkArrayPos(errorQ,&symbolTable,$1,$3);}
              ;

method_call   :	   ID '(' ')' {cantParams=0; insertString(paramsStack,intToString(cantParams));
								lastCalledMethod=$1; $$=getMethodAttribute(errorQ,&symbolTable,$1,0);}

              |    ID '(' {insertString(paramsStack,intToString(cantParams)); cantParams=0;
							insertString(methodsIDStack,lastCalledMethod); lastCalledMethod = $1;} expression_aux ')' 
							{$$ = getMethodAttribute(errorQ,&symbolTable,$1,cantParams); cantParams=atoi(removeLastString(paramsStack));} 

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
              |    arg ',' externinvk_arg
              ;
						
arg           :    expression
              |    STRING                     
              ;
              
expression    :    conjunction                   {$$ = $1;}                             
              |    expression OR conjunction     {$$ = returnOr(errorQ, $1, $3);}
              ;

conjunction   :    inequality                    {$$ = $1;}                                
              |    conjunction AND inequality    {$$ = returnAnd(errorQ, $1, $3);}
              ;

inequality    :    comparison                       {$$ = $1;}                             
              |    inequality DISTINCT comparison   {$$ = returnDistinct($1, $3);}
              ;

comparison    :    relation                   {$$ = $1;} 
              |    relation EQUAL relation    {$$ = returnEqual($1, $3);}
              ;

relation      :    term                 {$$ = $1;}
              |    term '<' term        {$$ = returnMinorComparison(errorQ, $1, $3);}
              |    term '>' term        {$$ = returnMajorComparison(errorQ, $1, $3);}
              |    term GEQUAL term     {$$ = returnGEqualComparison(errorQ, $1, $3);}
              |    term LEQUAL term     {$$ = returnLEqualComparison(errorQ, $1, $3);}
              ;

term          :    factor			{$$ = $1;}
              |    term '+' factor	{$$ = returnAdd(errorQ, $1, $3);}
              |    term '-' factor	{$$ = returnSub(errorQ, $1, $3);} 
              |    term '%' factor	{$$ = returnMod(errorQ, $1, $3);} 
              |    term '/' factor	{$$ = returnDiv(errorQ, $1, $3);} 
              |    term '*' factor	{$$ = returnMult(errorQ, $1, $3);} 
              ;

factor        :    primary		{$$ = $1;}  
              |    '!' factor	{$$ = $2;} 
              |    '-' factor	{$$ = $2;}
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
										else $$ = $1;
										lastCalledMethod=removeLastString(methodsIDStack);}
              ;

/* ------------------------- END OF EXPRESSIONS ------------------------------- */

%%

