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
#  include	"../Stack/stack.h"
#  include  "../Stack/label.h"
#  include  "../Code3D/gencode3d.h"
#  include  "../Code3D/codespecs.h"

extern FILE *yyin;
ErrorsQueue *errorQ;						/* Errors Queue definition */
SymbolsTable symbolTable;					/* <----Symbols Table Definition----- */
StringStack *paramsStack, *methodsIDStack;  /* StringStack containing the amount of parameters and lastCalledMethods in each level of method_call*/
unsigned char cantParams = 0, returns;		/* Amount of parameters and amount of returns that a method will have. */
PrimitiveType vaType;						/* Type of the variable or array */
ReturnType mType;							/* Return type of the method */
char *lastDefMethod, *lastCalledMethod = "";/* Name of the last defined method (lastDefMethod) and the last called method (lastCalledMethod) */

/*Variables used to code 3D*/

LCode3D *lcode3d;
char *labelID = "label_%d";
int  labelCount = 0;

Stack *labelsCYC;
Stack *labelsWhile;
Stack *labelsFor;
Stack *labelsMethod;

/*Create new Label*/
char* newLabel() {
        char *labelName = malloc(sizeof(char)*20);
        sprintf(labelName, labelID, labelCount);
        labelCount++;
        return labelName;
}


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
		// show the list of code 3D
		//int cantCodes = cantCode(lcode3d);
        //int i;
        //for (i = 0; i < cantCodes; i++) {
        //        Code3D *code = get_code(lcode3d, i);
        //        toString3DC(code);
        //}
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

program       :    CLASS ID '{' '}' {
									errorQ=initializeQueue(); 
									finalizar();
					} 
              |    CLASS ID '{' {
									initializeSymbolsTable(&symbolTable); 
									pushLevel(&symbolTable);
									errorQ=initializeQueue();
									paramsStack=initializeSS(); 
									methodsIDStack=initializeSS();
									labelsCYC = newStack();
                                    labelsWhile = newStack();
									labelsFor = newStack();
									labelsMethod = newStack();
									lcode3d = initLCode3D();
					} body {
								checkMain(errorQ,&symbolTable); 
								popLevel(&symbolTable); 
								finalizar();
					} '}' 
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

method_decl   :     type ID {
								lastDefMethod=$2; 
								pushElement(errorQ,&symbolTable,createMethod($2,mType,0)); 
								pushLevel(&symbolTable); returns=0;
					} param block {
								popLevel(&symbolTable); 
								if(returns==0) insertError(errorQ,toString("El metodo \"",$2,"\" debe tener al menos un return."));
					}
              |		method_decl type ID {
								lastDefMethod=$3; 
								pushElement(errorQ,&symbolTable,createMethod($3,mType,0)); 
								pushLevel(&symbolTable); returns=0;
					} param block {
								popLevel(&symbolTable); 
								if(returns==0) insertError(errorQ,toString("El metodo \"",$3,"\" debe tener al menos un return."));
					}
              |     VOID ID {
								lastDefMethod=$2; 
								pushElement(errorQ,&symbolTable,createMethod($2,RetVoid,0)); 
								pushLevel(&symbolTable); returns=0;
					} param block {
								popLevel(&symbolTable); 
								if(returns==0) insertError(errorQ,toString("El metodo \"",$2,"\" debe tener al menos un return."));
					}
              |	    method_decl VOID ID {
								lastDefMethod=$3; 
								pushElement(errorQ,&symbolTable,createMethod($3,RetVoid,0)); 
								pushLevel(&symbolTable); 
								returns=0;
					} param block {
								popLevel(&symbolTable); 
								if(returns==0) insertError(errorQ,toString("El metodo \"",$3,"\" debe tener al menos un return."));
					}
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
              |    BREAK {
							if (isEmpty(labelsWhile) && isEmpty(labelsFor)) {
								insertError(errorQ,toString("Error. Solo se puede usar la sentencia \"break\" dentro de un ciclo.","",""));
							} else {
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), peek(labelsWhile)->label); //Go to Label of End of While
							}
					}
              |    CONTINUE {
							if (isEmpty(labelsWhile) && isEmpty(labelsFor)) {
                                insertError(errorQ,toString("Error. Solo se puede usar la sentencia \"continue\" dentro de un ciclo.","",""));
							} else {
                                Label *endOfWhile = pop(labelsWhile); //Label of End of While
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), peek(labelsWhile)->label); //Go to Label of Init of While
								push(labelsWhile, endOfWhile->label, NULL);
							} 
					}
			  |	   RETURN {
							returns++; 
							checkReturn(errorQ,&symbolTable,lastDefMethod);
							Code3D *ret = newCode(COM_RETURN); ///////////////////////////////////////////////////////////////////////////////////////
							setCode1D(ret, void);  //////////////////////// que quiere decir con "void" acá?? ///////////////////////////////////////
							add_code(lcode3d, ret); ////////////////////////////////////////////////////////////////////////////////////////////////
					}   
			  |	   RETURN expression {
									returns++; 									
									if (checkReturnExpression(errorQ,&symbolTable,lastDefMethod,$2) == 0) { ////////////////////////////////////////////////////
										Code3D *loadToReturn = newCode(LOAD_MEM); /////////////////////////////////////////////////////////////////////////////
										setCode2D(loadToReturn, ($2), methodReturnType(errorQ,&symbolTable,lastDefMethod)); //fijarse de como puedo obtener la variable de retorno
										add_code(lcode3d, loadToReturn); ////////////////////////////////////////////////////////////////////////////////////
										Code3D *ret = newCode(COM_RETURN); /////////////////////////////////////////////////////////////////////////////////
										setCode1D(ret, retorno);  }////////// "retorno" ver aca como obtener la variable de retorno del metodo ////////////
										add_code(lcode3d, ret);  /////////////////////////////////////////////////////////////////////////////////////////
									}                           /////////////////////////////////////////////////////////////////////////////////////////
					}
              |    asignation 
              |    method_call                        
              ;
              
asignation    :    location assig_op expression {
							controlAssignation(errorQ,$1,$2,$3);
                            Code3D *add;
							if (strcmp($2, "+=") == 0){
								if ((getAttributeType($1) == Int) && (getAttributeType($3) == Int)){
									add = newCode(COM_ADD_INT);
								} 
								if ((getAttributeType($1) == Float) && (getAttributeType($3) == Float)){
									add = newCode(COM_ADD_FLOAT);
								}
								setCode2D(add, ($1), ($3));
								add_code(lcode3d, add);
							} 
							if (strcmp($2, "-=") == 0){
								if ((getAttributeType($1) == Int) && (getAttributeType($3) == Int)){
									add = newCode(COM_MINUS_INT);
								} 
								if ((getAttributeType($1) == Float) && (getAttributeType($3) == Float)){
									add = newCode(COM_MINUS_FLOAT);																				
								}
								setCode2D(add, ($1), ($3));
								add_code(lcode3d, add);
							}
							Code3D *asig = newCode(STORE_MEM);
							setCode2D(asig, ($3), ($1));
							add_code(lcode3d, asig);
					}
			  ;
              
assig_op      :    '=' {$$ = "=";} 
              |    PLUSEQUAL {$$ = $1;}
              |    MINUSEQUAL {$$ = $1;}
              ;

/* -------------------- END OF STATEMENTS ------------------------------- */

/* -------------------- CONDITIONALS AND CICLES ------------------------------ */

conditional   :    IF '(' expression ')' block { 
                                if (controlType(errorQ,$3,Bool) == 0) {
                                        char *ifLabel = newLabel();
                                        char *elseLabel = newLabel();
                                        char *endLabel = newLabel();
										add_CodeLabelCond(lcode3d, newCode(GOTOLABEL_COND), ($3), ifLabel); //Go to Label of If
										add_CodeLabel(lcode3d, newCode(GOTOLABEL), elseLabel); //Go to Label of Else
                                        add_CodeLabel(lcode3d, newCode(COM_MARK), ifLabel); // Mark to Label of If
                                        push(labelsCYC, elseLabel, NULL);
                                        push(labelsCYC, endLabel, NULL);
								}
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), peek(labelsCYC)->label); //Go to Label of End
					} ELSE {
                                Label *markEnd = pop(labelsCYC);
								add_CodeLabel(lcode3d, newCode(COM_MARK), pop(labelsCYC)->label); // Mark to Label of Else
                                push(labelsCYC, markEnd->label, NULL);
                    } block {
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), peek(labelsCYC)->label); // Go to Label of End
								add_CodeLabel(lcode3d, newCode(COM_MARK), pop(labelsCYC)->label); // Mark to Label of End
                    }
			  |    IF '(' expression ')' block { 
                                if (controlType(errorQ,$3,Bool) == 0) {
                                        char *ifLabel = newLabel();
                                        char *endLabel = newLabel();
										add_CodeLabelCond(lcode3d, newCode(GOTOLABEL_COND), ($3), ifLabel); //Go to Label of If
										add_CodeLabel(lcode3d, newCode(GOTOLABEL), endLabel); //Go to Label of End
                                        add_CodeLabel(lcode3d, newCode(COM_MARK), ifLabel); // Mark to Label of If
                                        push(labelsCYC, endLabel, NULL);
                                }
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), peek(labelsCYC)->label); // Go to Label of End
								add_CodeLabel(lcode3d, newCode(COM_MARK), pop(labelsCYC)->label); // Mark to Label of End
					}
			  ;

iteration     :    WHILE {     
                            char *whileLabel = newLabel(); 
							push(labelsWhile,whileLabel,NULL);
							add_CodeLabel(lcode3d, newCode(COM_MARK), whileLabel); // Mark to Label of While
                    } expression {
							if (controlType(errorQ,$3,Bool) == 0) {
								char *endLabel = newLabel(); 
								push(labelsWhile, endLabel, NULL);
								char *expressionLabel = newLabel();
								add_CodeLabelCond(lcode3d, newCode(GOTOLABEL_COND),($3), expressionLabel); // Go to Label of Expression
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), endLabel); // Go to Label of End
								add_CodeLabel(lcode3d, newCode(COM_MARK), expressionLabel); // Mark to Label of Expression           
                            }
					} block {							
							Label *endOfCycle = pop(labelsWhile); 														
							add_CodeLabel(lcode3d, newCode(GOTOLABEL), pop(labelsWhile)->label); // Go to Label of While
							add_CodeLabel(lcode3d, newCode(COM_MARK), endOfCycle->label); // Mark to Label of End
					}
              |    FOR {     
                        char *forLabel = newLabel(); 
						push(labelsFor,forLabel,NULL);
						add_CodeLabel(lcode3d, newCode(COM_MARK), forLabel); // Mark to Label of For
                    }ID {
						if (getAttributeType(getVariableAttribute(errorQ,&symbolTable,$3)) != Int){
							insertError(errorQ,toString("El identificador \"", $3, "\" no pertenece a una variable de tipo \"int\""));
						}
					}
					'=' expression ',' expression {
								if ((controlType(errorQ,$6,Int) == 0) && (controlType(errorQ,$8,Int)== 0)) {
									char *endLabel = newLabel();									 
									push(labelsFor, endLabel, NULL);
									char *expressionLabel = newLabel();
									Attribute *res = createVariable("", Bool);
									returnEqual(errorQ, lcode3d, $6, $8, res); //creo la comparacion la hago aca o lo hago en assembler?
									add_CodeLabelCond(lcode3d, newCode(GOTOLABEL_COND), res, expressionLabel); // Go to Label of Expression (falta hacer la comparacion)
									add_CodeLabel(lcode3d, newCode(GOTOLABEL), endLabel); // Go to Label of End
									add_CodeLabel(lcode3d, newCode(COM_MARK), expressionLabel); // Mark to Label of Expression           
								}
					} block {
							Label *endOfCycle = pop(labelsFor); 							 							
							add_CodeLabel(lcode3d, newCode(GOTOLABEL), pop(labelsFor)->label); // Go to Label of For
							add_CodeLabel(lcode3d, newCode(COM_MARK), endOfCycle->label); // Mark to Label of End
					}
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
              
expression    :    conjunction                  {$$ = $1;}                             
              |    expression OR conjunction    {$$ = returnOr(errorQ, lcode3d, $1, $3, $$);}
              ;

conjunction   :    inequality                   {$$ = $1;}                                
              |    conjunction AND inequality   {$$ = returnAnd(errorQ, lcode3d, $1, $3, $$);}
              ;

inequality    :    comparison                       {$$ = $1;}                             
              |    inequality DISTINCT comparison   {$$ = returnDistinct(errorQ, lcode3d, $1, $3, $$);}
              ;

comparison    :    relation                   {$$ = $1;} 
              |    relation EQUAL relation    {$$ = returnEqual(errorQ, lcode3d, $1, $3, $$);}
              ;

relation      :    term                 {$$ = $1;}
              |    term '<' term        {$$ = returnMinorComparison(errorQ, lcode3d, $1, $3, $$);}
              |    term '>' term        {$$ = returnMajorComparison(errorQ, lcode3d, $1, $3, $$);}
              |    term GEQUAL term     {$$ = returnGEqualComparison(errorQ, lcode3d, $1, $3, $$);}
              |    term LEQUAL term     {$$ = returnLEqualComparison(errorQ, lcode3d, $1, $3, $$);}
              ;

term          :    factor			{$$ = $1;}
              |    term '+' factor	{$$ = returnAdd(errorQ, lcode3d, $1, $3, $$);}
              |    term '-' factor	{$$ = returnSub(errorQ, lcode3d, $1, $3, $$);}
              |    term '%' factor	{$$ = returnMod(errorQ, lcode3d, $1, $3, $$);}
              |    term '/' factor	{$$ = returnDiv(errorQ, lcode3d, $1, $3, $$);}
              |    term '*' factor	{$$ = returnMult(errorQ, lcode3d, $1, $3, $$);}
              ;

factor        :    primary		{$$ = $1;}  
              |    '!' factor	{$$ = returnNot(errorQ, lcode3d, $2, $$);}
              |    '-' factor	{$$ = returnNeg(errorQ, lcode3d, $2, $$);}
              ;

primary       :    INTEGER			{$$ = returnValue(lcode3d, Int, $1, $$);}
              |    FLOAT            {$$ = returnValue(lcode3d, Float, $1, $$);}
              |    BOOLEAN          {$$ = returnValue(lcode3d, Bool, $1, $$);}
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

