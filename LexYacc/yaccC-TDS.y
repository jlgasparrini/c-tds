%{
#  include  <stdio.h>
#  include  <ctype.h>
#  include  <string.h>
#  include  <stdlib.h>
#  include  "../SymbolsTable/StringStack.h"
#  include  "../SymbolsTable/Utils.h"
#  include	"../Stack/stack.h"
#  include  "../Stack/label.h" //////////// ver si esta bien que esten aca, ya que al eliminarlos sigue compilando todo OK
#  include  "../ListMethod/genlistml.h"


extern FILE *yyin;
ErrorsQueue *errorQ;						/* Errors Queue definition */
SymbolsTable *symbolsTable;					/* <----Symbols Table Definition----- */
StringStack *paramsStack, *methodsIDStack;  /* StringStack containing the amount of parameters and lastCalledMethods in each level of method_call */
unsigned char cantParams = 0, returns;		/* Amount of parameters and amount of returns that a method will have. */
PrimitiveType vaType;						/* Type of the variable or array */
ReturnType mType;							/* Return type of the method */
char *lastDefMethod, *lastCalledMethod = "";/* Name of the last defined method (lastDefMethod) and the last called method (lastCalledMethod) */
Boolean idNotFound;

/* Variables used for 3D code */
LCode3D *lcode3d;
char *labelID = "%d_label_";
int  labelCount = 0;

Stack *labelsCYC;
Stack *labelsWhile;
Stack *labelsFor;
ListMLabel *listmlabel;

/*Create new Label*/
char* newLabelName(char* msg) {
	char *labelName = malloc(sizeof(char)*(digitAmount(labelCount)+strlen("%d_label_")+strlen(msg)));
	sprintf(labelName, labelID, labelCount);
	strcat(labelName,msg);
   	labelCount++;
   	return labelName;
}

/* To show after compilation, for interpreter */
StringStack *printMsg;
char *printMessage = "Print. El valor es: ";
unsigned char printFound = 0;

int yydebug = 1;

int yyerror (char *str)
{
	printErrorList(errorQ);
    deleteAllErrors(errorQ);
    if (strcmp(str, "syntax error") == 0)
		printf("%s\n",toString("Error GRAMATICO.","",""));
    else
		if (strcmp(str, "incorrecto") != 0)
			printf("%s\n","Error DESCONOCIDO.");
    return 0;
}
 
int yywrap()
{
	return 1;
} 
  
int main( argc, argv )
    int argc;
    char **argv; {
        ++argv, --argc;	/* skip over program name */
        if ( argc > 0 )
			yyin = fopen( argv[0], "r" );
        else
			yyin = stdin;
			yyparse();
	return 0;
}

void finalizar() {
    if ((*errorQ).size > 0) 
        yyerror("incorrecto");
    else
	{
        // show the list of code 3D
		show3DCode(lcode3d);
		printf("------Se termino de parsear.----------\n");
		printf("-----Corriendo interprete------\n");
		initInterpreter(listmlabel, lcode3d);
		if (printFound == 1)
//			printCorrectOrder(printMsg);
			printInverseOrder(printMsg);	
		printf("-----Se acabo de correr el interprete.-----\n");
	}
}

void out(char *msg) {
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
%token BREAK IF CONTINUE ELSE RETURN WHILE CLASS FOR VOID EXTERNINVK STRING PRINT
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
									lcode3d = initLCode3D();
									finalizar();
					} 
              |    CLASS ID '{' {
									symbolsTable = initializeSymbolsTable(); 
									pushLevel(symbolsTable);
									errorQ = initializeQueue();
									paramsStack = initializeSS(); 
									methodsIDStack = initializeSS();
									labelsCYC = newStack();
                                    labelsWhile = newStack();
									labelsFor = newStack();
									listmlabel = initL();
									lcode3d = initLCode3D();
									printMsg = initializeSS();
					} body {
								checkMain(errorQ,symbolsTable); 
								popLevel(symbolsTable); 
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

field         :    ID			{pushElement(errorQ, symbolsTable, createVariable($1, vaType));}
              |    ID '[' INTEGER {if (atoi($3) <= 0) 
									{	insertError(errorQ,toString("Error en definicion del arreglo \"",$1,"\". El tamaño del arreglo debe ser un entero mayor que 0."));
										pushElement(errorQ, symbolsTable, createArray($1, vaType, 10)); /* Array size of 10 in case of error */
									}
									else
										pushElement(errorQ, symbolsTable, createArray($1, vaType, atoi($3)));
								}
						']'	
              ;

type          :		INTW		{vaType = Int; mType = RetInt;} 
              |		FLOATW		{vaType = Float; mType = RetFloat;}
              |		BOOLEANW	{vaType = Bool; mType = RetBool;}
              ;

method_decl   :     type ID {
								lastDefMethod=$2; 
								pushElement(errorQ,symbolsTable,createMethod($2,mType)); 
								pushLevel(symbolsTable); 
								returns = 0;
								char *initLabel = newLabelName($2);
								insert_MethodL(listmlabel, $2, initLabel);
								add_CodeLabel(lcode3d, newCode(MARK), initLabel); // Mark to Label of Init of Method
					} param block {
								popLevel(symbolsTable); 
								if(returns==0) insertError(errorQ,toString("El metodo \"",$2,"\" debe tener al menos un return."));
					}
              |		method_decl type ID {
								lastDefMethod=$3; 
								pushElement(errorQ,symbolsTable,createMethod($3,mType)); 
								pushLevel(symbolsTable); 
								returns = 0;
								char *initLabel = newLabelName($3);
								insert_MethodL(listmlabel, $3, initLabel);
								add_CodeLabel(lcode3d, newCode(MARK), initLabel); // Mark to Label of Init of Method
					} param block {
								popLevel(symbolsTable); 
								if(returns==0) insertError(errorQ,toString("El metodo \"",$3,"\" debe tener al menos un return."));
					}
              |     VOID ID {
								lastDefMethod=$2; 
								pushElement(errorQ,symbolsTable,createMethod($2,RetVoid)); 
								pushLevel(symbolsTable); 
								returns = 0;
								char *initLabel = newLabelName($2);
								insert_MethodL(listmlabel, $2, initLabel);
								add_CodeLabel(lcode3d, newCode(MARK), initLabel); // Mark to Label of Init of Method
					} param block {
								popLevel(symbolsTable); 
								if(returns==0) insertError(errorQ,toString("El metodo \"",$2,"\" debe tener al menos un return."));
					}
              |	    method_decl VOID ID {
								lastDefMethod=$3; 
								pushElement(errorQ,symbolsTable,createMethod($3,RetVoid)); 
								pushLevel(symbolsTable); 
								returns = 0;
								char *initLabel = newLabelName($3);
								insert_MethodL(listmlabel, $3, initLabel);
								add_CodeLabel(lcode3d, newCode(MARK), initLabel); // Mark to Label of Init of Method
					} param block {
								popLevel(symbolsTable); 
								if(returns==0) insertError(errorQ,toString("El metodo \"",$3,"\" debe tener al menos un return."));
					}
              ;

param		  :    '(' {cantParams = 0; setAmountOfParameters(searchIdInSymbolsTable(errorQ,symbolsTable,lastDefMethod),0);} ')' 
			  |    '(' {if (strcmp(lastDefMethod,"main") == 0)
							insertError(errorQ,toString("El metodo \"main\" no debe contener parametros.","","")); cantParams = 0;}
					parameters {setAmountOfParameters(searchIdInSymbolsTable(errorQ,symbolsTable,lastDefMethod),cantParams);} ')'
			  ;
              
parameters    :		type ID {Attribute *aux = createParameter(searchIdInSymbolsTable(errorQ,symbolsTable,lastDefMethod),cantParams,$2,vaType);
								if (aux != NULL) {pushElement(errorQ,symbolsTable,aux); cantParams++;}
								else insertError(errorQ,toString("El identificador \"",$2,"\" no puede contener parametros/esa cantidad de parametros."));
							}

			  |		type ID {Attribute *aux = createParameter(searchIdInSymbolsTable(errorQ,symbolsTable,lastDefMethod),cantParams,$2,vaType);
								if (aux != NULL) {pushElement(errorQ,symbolsTable,aux); cantParams++;}
								else insertError(errorQ,toString("El identificador \"",$2,"\" no puede contener parametros/esa cantidad de parametros."));
							}
							',' parameters 
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
              |    {pushLevel(symbolsTable);} block {popLevel(symbolsTable);}
              |    PRINT expression ';' {
											printFound = 1;
											char *val;
											if (getAttributeType($2) == Int)
											{
												val = (char*) malloc (strlen(printMessage)+digitAmount(getIntVal($2)+strlen("\n"))*sizeof(char));
												strcat(val,printMessage);
												strcat(val,intToString(getIntVal($2)));
												strcat(val,"\n");
											}
			
											if (getAttributeType($2) == Float)
											{ 
												val = (char*) malloc ((strlen(printMessage)+50+strlen("\n"))*sizeof(char));
												char *numero = (char*) malloc (50*sizeof(char));
												sprintf(numero, "%f", getFloatVal($2)); /* Here the float is transformed into a string */
												strcat(val,printMessage);
												strcat(val,numero);
												strcat(val,"\n");
											}
			
											if (getAttributeType($2) == Bool)
											{
												val = (char*) malloc ((strlen(printMessage)+5+strlen("\n"))*sizeof(char));
												strcat(val,printMessage);
												if (getBoolVal($2) == True)	
													strcat(val,"true");
												if (getBoolVal($2) == False)	
													strcat(val,"false");
												strcat(val,"\n");
											}
											pushString(printMsg,val);
										}
              ;
              
action        :
              |    BREAK {
							if (isEmpty(labelsWhile) && isEmpty(labelsFor))
								insertError(errorQ,toString("Error. Solo se puede usar la sentencia \"break\" dentro de un ciclo.","",""));
							else
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), peek(labelsWhile)->label); //Go to Label of End of While
					}
              |    CONTINUE {
							if (isEmpty(labelsWhile) && isEmpty(labelsFor))
                                insertError(errorQ,toString("Error. Solo se puede usar la sentencia \"continue\" dentro de un ciclo.","",""));
							else
							{
                                Label *endOfWhile = pop(labelsWhile); //Label of End of While
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), peek(labelsWhile)->label); //Go to Label of Init of While
								push(labelsWhile, endOfWhile->label);
							} 
					}
			  |	   RETURN {
							returns++; 
							if ((idNotFound == False) && (checkReturn(errorQ,symbolsTable,lastDefMethod) == 0))
							{
								Code3D *ret = newCode(RETURN); ///////////////////////////////////////////////////////////////////////////
							//	setCode1D(ret, void);  /////////////// VER ESTA LINEA, NO DEBERIA HABER NADA ////////////////////////////////
								add_code(lcode3d, ret); ////////////////////////////////////////////////////////////////////////////////////
							}
					}   
			  |	   RETURN expression {
									returns++; 									
									if ((idNotFound == False) && (checkReturnExpression(errorQ,symbolsTable,lastDefMethod,$2) == 0))
									{ 
										Code3D *ret = newCode(RETURN);
										setCode1D(ret, $2); 
										add_code(lcode3d, ret);  
									}                           
					}
              |    asignation 
              |    method_call                        
              ;
              
asignation    :    location assig_op expression {
							if (controlAssignation(errorQ,lcode3d,$1,$2,$3) == 0)
                                $1 = $3;
                            else
                                $1 = NULL;
					}
			  ;
              
assig_op      :    '=' {$$ = "=";} 
              |    PLUSEQUAL {$$ = "+=";}
              |    MINUSEQUAL {$$ = "-=";}
              ;

/* -------------------- END OF STATEMENTS ------------------------------- */

/* -------------------- CONDITIONALS AND CICLES ------------------------------ */

conditional   :    IF '(' expression { 
										controlType(errorQ,$3,Bool,"if",1);
                                        char *ifLabel = newLabelName("if");
                                        char *elseLabel = newLabelName("else");
                                        char *endLabel = newLabelName("end_if");
										add_CodeLabelCond(lcode3d, newCode(GOTOLABEL_COND), $3, ifLabel); //Go to Label of If
										add_CodeLabel(lcode3d, newCode(GOTOLABEL), elseLabel); //Go to Label of Else
                                        add_CodeLabel(lcode3d, newCode(MARK), ifLabel); // Mark to Label of If
                                        push(labelsCYC, elseLabel);
                                        push(labelsCYC, endLabel);
					} ')' block {
									add_CodeLabel(lcode3d, newCode(GOTOLABEL), peek(labelsCYC)->label); //Go to Label of End
								}
					 optional
			  ;

optional	  :		{
                        Label *markEnd = pop(labelsCYC);
						add_CodeLabel(lcode3d, newCode(MARK), pop(labelsCYC)->label); // Mark to Label of Else. There's always an else label, but in case of an if then statement, it is not used
						add_CodeLabel(lcode3d, newCode(GOTOLABEL), markEnd->label); // Go to Label of End
						add_CodeLabel(lcode3d, newCode(MARK), markEnd->label); // Mark to Label of End
					}
			  |	   	ELSE {
                         Label *markEnd = pop(labelsCYC);
						 add_CodeLabel(lcode3d, newCode(MARK), pop(labelsCYC)->label); // Mark to Label of Else
                         push(labelsCYC, markEnd->label);
                    } block	{
						add_CodeLabel(lcode3d, newCode(GOTOLABEL), peek(labelsCYC)->label); // Go to Label of End
						add_CodeLabel(lcode3d, newCode(MARK), pop(labelsCYC)->label); // Mark to Label of End
					} 
			  ;

iteration     :    WHILE {     
                            char *whileLabel = newLabelName("while"); 
							push(labelsWhile,whileLabel);
							add_CodeLabel(lcode3d, newCode(MARK), whileLabel); // Mark to Label of While
                    } expression {
								controlType(errorQ,$3,Bool,"while",1);	/* MODIFICADO PORQUE SINO TIRA SEGMENTATION FAULT! */
								char *endLabel = newLabelName("end_while");/* DEBIDO A QUE NO GENERA EL SIG CODIGO Y EN BLOQUE LO TRATA DE ELIMINAR */
								push(labelsWhile, endLabel);
								char *expressionLabel = newLabelName("expr_while");
								add_CodeLabelCond(lcode3d, newCode(GOTOLABEL_COND), $3, expressionLabel); // Go to Label of Expression
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), endLabel); // Go to Label of End
								add_CodeLabel(lcode3d, newCode(MARK), expressionLabel); // Mark to Label of Expression           
					} block {							
							Label *endOfCycle = pop(labelsWhile); 														
							add_CodeLabel(lcode3d, newCode(GOTOLABEL), pop(labelsWhile)->label); // Go to Label of While
							add_CodeLabel(lcode3d, newCode(MARK), endOfCycle->label); // Mark to Label of End
					}
              |    FOR {     
                        char *forLabel = newLabelName("for"); 
						push(labelsFor,forLabel);
						add_CodeLabel(lcode3d, newCode(MARK), forLabel); // Mark to Label of For
                    } ID {
						if (getAttributeType(getVariableAttribute(errorQ,symbolsTable,$3)) != Int)
							insertError(errorQ,toString("El identificador \"", $3, "\" no pertenece a una variable de tipo \"int\""));
					}
					'=' expression ',' expression {
									controlType(errorQ,$6,Int,"for",2); /* MODIFICADO PORQUE SINO TIRA SEGMENTATION FAULT! */
									controlType(errorQ,$8,Int,"for",3); /* DEBIDO A QUE NO GENERA EL SIG CODIGO Y EN BLOQUE LO TRATA DE ELIMINAR */
									char *endLabel = newLabelName("end_for");									 
									push(labelsFor, endLabel);
									char *expressionLabel = newLabelName("expr_for");
									Attribute *res = returnDistinct(errorQ, lcode3d, getVariableAttribute(errorQ, symbolsTable, $3), $8);
									add_CodeLabelCond(lcode3d, newCode(GOTOLABEL_COND), res, expressionLabel); // Go to Label of Expression
									add_CodeLabel(lcode3d, newCode(GOTOLABEL), endLabel); // Go to Label of End
									add_CodeLabel(lcode3d, newCode(MARK), expressionLabel); // Mark to Label of Expression           
					} block {
							Label *endOfCycle = pop(labelsFor); 							 							
							add_CodeLabel(lcode3d, newCode(GOTOLABEL), pop(labelsFor)->label); // Go to Label of For
							add_CodeLabel(lcode3d, newCode(MARK), endOfCycle->label); // Mark to Label of End
					}
              ;                                                               

/* -------------------- END OF CONDITIONALS AND CICLES ------------------------------- */

/* -------------------- EXPRESSIONS ------------------------------- */

location      :    ID {$$ = getVariableAttribute(errorQ, symbolsTable, $1);}
              |    ID '[' expression ']' { $$ = checkArrayPos(errorQ,symbolsTable,$1,$3);}
			  ;
				/* --------------------------------------------------------------------------------------- */
				/* --------------------------------------------------------------------------------------- */
				/* --------------- ^ --------------------------------------------------------------------- */
				/* --------------- | --------------------------------------------------------------------- */
				/* --------------- | --------------------------------------------------------------------- */
				/* --------------- | --------------------------------------------------------------------- */
				/* --------------- | --------------------------------------------------------------------- */
				/* --------------------------------------------------------------------------------------- */
				/* ---- Verificar que aca se podria guardar la ultima posicion de arreglo a setear,
						definiendo una nueva variable "lastUsedArrayPosition" y desde el asignation
						usar algun metodo setArrayPos() para setear el valor en la posicion 
						correspondiente del arreglo ------------------------------------------------------ */
				/* --------------------------------------------------------------------------------------- */
                        /* if (getAttributeType($3) == Int) lastUsedArrayPosition = atoi($3); */
				/* --------------------------------------------------------------------------------------- */
				/* --------------------------------------------------------------------------------------- */
				/* --------------------------------------------------------------------------------------- */
				/* --------------------------------------------------------------------------------------- */
				/* --------------------------------------------------------------------------------------- */
				/* --------------------------------------------------------------------------------------- */
				/* --------------------------------------------------------------------------------------- */
				/* --------------------------------------------------------------------------------------- */

method_call   :	   ID '(' ')' {
								cantParams=0; 
								pushString(paramsStack,intToString(cantParams)); /*ver si esta linea debe ir o no*/
								lastCalledMethod=$1; 
								$$=checkAndGetMethodRetAttribute(errorQ,symbolsTable,$1,0);
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), get_Label(listmlabel, $1)); //Go to Label of Init of Method
								//char *endLabel = newLabelName("end_m_call");
								//insert_MethodL(listmlabel, $1, endLabel);
								//add_CodeLabel(lcode3d, newCode(MARK), endLabel); // Mark to Label of End of Method // ver si es necesario esta marca, si es asi cambiar toda la lista.
					}

              |    ID '(' {if (searchIdInSymbolsTable(errorQ,symbolsTable,$1) == NULL) 
								idNotFound = True; 
							else
							{
								pushString(paramsStack,intToString(cantParams)); /* Este caso fue modificado para que contuviera todas */
								cantParams=0;									 /* ya que contenia solamente a "idNotFound = True" y en caso */
								pushString(methodsIDStack,lastCalledMethod);	 /* de error no deberian actualizarse ninguna de las variables */
								lastCalledMethod = $1;
							}
					} expression_aux ')' {
							if (idNotFound != True)
							{
								$$ = checkAndGetMethodRetAttribute(errorQ,symbolsTable,$1,cantParams); 
								cantParams=atoi(popString(paramsStack));
								add_CodeLabel(lcode3d, newCode(GOTOLABEL), get_Label(listmlabel, $1)); //Go to Label of Init of Method 
								//char *endLabel = newLabelName("end_m_call");
								//insert_MethodL(listmlabel, $1, endLabel);
								//add_CodeLabel(lcode3d, newCode(MARK), endLabel); // Mark to Label of End of Method // ver si es necesario esta marca, si es asi cambiar toda la lista.
							}
							else
							{
								$$ = createVariable("",Int); 
								idNotFound = False;
							}
					} 

              |    EXTERNINVK '(' STRING ',' typevoid ')' {if (mType != RetVoid) $$=createVariable("",mType);}
              |    EXTERNINVK '(' STRING ',' typevoid ',' externinvk_arg ')' {if (mType != RetVoid) $$=createVariable("",mType);}
              ;

expression_aux:    expression {
								if (idNotFound != True)
								{
									correctParamBC(errorQ,symbolsTable,$1,lastCalledMethod,cantParams); 
									StVariable *param = (StVariable*) malloc (sizeof(StVariable));
									param = &((*searchIdInSymbolsTable(errorQ,symbolsTable,lastCalledMethod)).decl.method.parameters[cantParams]); // obtencion del parametro formal.
									add_MethodCall(lcode3d, newCode(STORE_MEM_METHOD), $1, param); 
									cantParams++; /* This sentence must be in the last line because parameter's numbers start from 0 */
								}
					}
			  |    expression {
								if (idNotFound != True)
								{
									correctParamIC(errorQ,symbolsTable,$1,lastCalledMethod,cantParams); 
									StVariable *param = (StVariable*) malloc (sizeof(StVariable));
									param = &((*searchIdInSymbolsTable(errorQ,symbolsTable,lastCalledMethod)).decl.method.parameters[cantParams]); // obtencion del parametro formal.
									add_MethodCall(lcode3d, newCode(STORE_MEM_METHOD), $1, param);
									cantParams++; /* This sentence must be in the last line because parameter's numbers start from 0 */
								} 
					} ',' expression_aux 
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
              |    expression OR conjunction    {$$ = returnOr(errorQ, lcode3d, $1, $3);}
              ;

conjunction   :    inequality                   {$$ = $1;}                                
              |    conjunction AND inequality   {$$ = returnAnd(errorQ, lcode3d, $1, $3);}
              ;

inequality    :    comparison                       {$$ = $1;}                             
              |    inequality DISTINCT comparison   {$$ = returnDistinct(errorQ, lcode3d, $1, $3);}
              ;

comparison    :    relation                   {$$ = $1;} 
              |    relation EQUAL relation    {$$ = returnEqual(errorQ, lcode3d, $1, $3);}
              ;

relation      :    term                 {$$ = $1;}
              |    term '<' term        {$$ = returnMinorComparison(errorQ, lcode3d, $1, $3);}
              |    term '>' term        {$$ = returnMajorComparison(errorQ, lcode3d, $1, $3);}
              |    term GEQUAL term     {$$ = returnGEqualComparison(errorQ, lcode3d, $1, $3);}
              |    term LEQUAL term     {$$ = returnLEqualComparison(errorQ, lcode3d, $1, $3);}
              ;

term          :    factor			{$$ = $1;}
              |    term '+' factor	{$$ = returnAdd(errorQ, lcode3d, $1, $3);}
              |    term '-' factor	{$$ = returnSub(errorQ, lcode3d, $1, $3);}
              |    term '%' factor	{$$ = returnMod(errorQ, lcode3d, $1, $3);}
              |    term '/' factor	{$$ = returnDiv(errorQ, lcode3d, $1, $3);}
              |    term '*' factor	{$$ = returnMult(errorQ, lcode3d, $1, $3);printf(" | | | | |  | |      %d   \n", (*$1).decl.variable.value.intVal); }
              ;

factor        :    primary		{$$ = $1;}  
              |    '!' factor	{$$ = returnNot(errorQ, lcode3d, $2);}
              |    '-' factor	{$$ = returnNeg(errorQ, lcode3d, $2);}
              ;

primary       :    INTEGER			{$$ = returnValue(lcode3d, Int, $1);}
              |    FLOAT            {$$ = returnValue(lcode3d, Float, $1);}
              |    BOOLEAN          {$$ = returnValue(lcode3d, Bool, $1);}
              |    ID				{$$ = getVariableAttribute(errorQ,symbolsTable,$1);}
              |    ID '[' expression ']'  {$$ = checkArrayPos(errorQ,symbolsTable,$1,$3);}
              |    '(' expression ')'  {$$ = $2;}
              |    method_call      {
										if (methodReturnType(errorQ,symbolsTable,lastCalledMethod) == RetVoid)
										{	insertError(errorQ,toString("El metodo \"",lastCalledMethod,"\" no puede ser usado en una expresion ya que retorna void."));
											$$ = createVariable("",Int); /* creamos variables int por defecto ------------------------------- */
										}
										else $$ = $1;
										lastCalledMethod=popString(methodsIDStack);
									}
              ;

/* ------------------------- END OF EXPRESSIONS ------------------------------- */

%%

