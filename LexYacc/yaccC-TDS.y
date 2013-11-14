%{
#  include  <stdio.h>
#  include  <ctype.h>
#  include  <string.h>
#  include  <stdlib.h>
#  include  "../SymbolsTable/StringStack.h"
#  include  "../SymbolsTable/Utils.h"
#  include	"../Stack/stack.h"
#  include	"../Stack/stackOffset.h"
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
char *labelID = "label_%d_";
int labelCount = 0;

Stack *labelsCYC;
Stack *labelsWhile;
Stack *labelsFor;
Stack *returnStack;//Utilizada para los saltos en el interprete!
Stack *maxMethodOffset;
StackOffset *offsetsVar;
StackOffset *offsetsParam;
ListMLabel *listmlabel;

//Assembly
char* fileName;

/*Create new Label*/
char* newLabelName(char* msg) 
{
    char *labelName = malloc(sizeof(char)*(digitAmount(labelCount)+strlen("%d_label_")+strlen(msg)));
    sprintf(labelName, labelID, labelCount);
    strcat(labelName,msg);
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
    char **argv; 
    { 
    ++argv, --argc; /* skip over program name */
    fileName = argv[0];
        if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
        else
            yyin = stdin;
        yyparse();
    return 0;
}

void finalizar() 
{
    if ((*errorQ).size > 0) 
        yyerror("incorrecto");
    else
    {
        // show the list of code 3D
        show3DCode(lcode3d); // uncommenting this line will show the 3 directions code of the parsed code;
        //initInterpreter(listmlabel, lcode3d); // The interpreter in this version is not working.
        initAssembler(listmlabel, lcode3d, returnStack, fileName);
        printf("-----Codigo Assembler Generado.-----\n");
    }
}

void out(char *msg) 
{
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
%token<stringValue> FLOAT INTEGER BOOLEAN INTW FLOATW BOOLEANW ID PLUSEQUAL MINUSEQUAL STRING
%token EQUAL DISTINCT GEQUAL LEQUAL ORR ANDD 
%token BREAK IF CONTINUE ELSE RETURNN WHILE CLASS FOR VOID EXTERNINVK PRINTT
%nonassoc '<' '>' EQUAL DISTINCT GEQUAL LEQUAL
%left '+' '-'
%left '*' '/'
%left '%'
%type<at> expression conjunction inequality comparison relation term factor primary method_call location factor1
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
                                    returnStack = newStack();
                                    labelsFor = newStack();
                                    maxMethodOffset = newStack();
									offsetsVar = newStackOffset();
									offsetsParam = newStackOffset();
                                    listmlabel = initL();
                                    lcode3d = initLCode3D();
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
                                pushOffset(offsetsVar, getGlobalVarOffset());/////////////////////////////////
								resetGlobalVarOffset();////////////////////////////
								lastDefMethod=$2; 
                                pushElement(errorQ,symbolsTable,createMethod($2,mType)); 
                                pushLevel(symbolsTable);
                                returns = 0;
                                add_CodeLabel(lcode3d, newCode(LABEL), $2); // Mark to Label of Init of Method
                                push(maxMethodOffset, intToString(codeSize(lcode3d)));
                                insert_MethodL(listmlabel, $2, $2);
                    } param block {
                                int pos = atoi(pop(maxMethodOffset));
                                set_code_int(lcode3d, pos, 2, getGlobalVarOffset());
								setGlobalVarOffset(popOffset(offsetsVar));//////////////////////////////////////////
                                if(returns==0) insertError(errorQ,toString("El metodo \"",$2,"\" debe tener al menos un return."));
                                popLevel(symbolsTable);
                    }
              |		method_decl type ID {
								pushOffset(offsetsVar, getGlobalVarOffset());////////////////////////////
								resetGlobalVarOffset();////////////////////////////
                                lastDefMethod=$3; 
                                pushElement(errorQ,symbolsTable,createMethod($3,mType)); 
                                pushLevel(symbolsTable);
                                returns = 0;
                                add_CodeLabel(lcode3d, newCode(LABEL), $3); // Mark to Label of Init of Method
                                push(maxMethodOffset, intToString(codeSize(lcode3d)));
                                insert_MethodL(listmlabel, $3, $3);
                    } param block {
                                int pos = atoi(pop(maxMethodOffset));
                                set_code_int(lcode3d, pos, 2, getGlobalVarOffset());
								setGlobalVarOffset(popOffset(offsetsVar));//////////////////////////////////////////
                                if(returns==0) insertError(errorQ,toString("El metodo \"",$3,"\" debe tener al menos un return."));
                                popLevel(symbolsTable);
                    }
              |     VOID ID {
			  					pushOffset(offsetsVar, getGlobalVarOffset());////////////////////////////
								resetGlobalVarOffset();////////////////////////////
                                lastDefMethod=$2; 
                                pushElement(errorQ,symbolsTable,createMethod($2,RetVoid)); 
                                pushLevel(symbolsTable);
                                returns = 0;
                                returns = 0;
                                add_CodeLabel(lcode3d, newCode(LABEL), $2); // Mark to Label of Init of Method
                                push(maxMethodOffset, intToString(codeSize(lcode3d)));
                                insert_MethodL(listmlabel, $2, $2);
                    } param block {
                                int pos = atoi(pop(maxMethodOffset));
                                set_code_int(lcode3d, pos, 2, getGlobalVarOffset());
								setGlobalVarOffset(popOffset(offsetsVar));//////////////////////////////////////////
                                if(returns==0) insertError(errorQ,toString("El metodo \"",$2,"\" debe tener al menos un return."));
                                popLevel(symbolsTable);
                    }
              |	    method_decl VOID ID {
								pushOffset(offsetsVar, getGlobalVarOffset());////////////////////////////
								resetGlobalVarOffset();////////////////////////////
                                lastDefMethod=$3; 
                                pushElement(errorQ,symbolsTable,createMethod($3,RetVoid)); 
                                pushLevel(symbolsTable);
                                returns = 0;
                                returns = 0;
                                add_CodeLabel(lcode3d, newCode(LABEL), $3); // Mark to Label of Init of Method
                                push(maxMethodOffset, intToString(codeSize(lcode3d)));
                                insert_MethodL(listmlabel, $3, $3);
                    } param block {
                                int pos = atoi(pop(maxMethodOffset));
                                set_code_int(lcode3d, pos, 2, getGlobalVarOffset());
								setGlobalVarOffset(popOffset(offsetsVar));//////////////////////////////////////////
                                if(returns==0) insertError(errorQ,toString("El metodo \"",$3,"\" debe tener al menos un return."));
                                popLevel(symbolsTable);
                    }
              ;

param		  :    '(' {cantParams = 0; setAmountOfParameters(searchIdInSymbolsTable(errorQ,symbolsTable,lastDefMethod),0);} ')' 
              |    '(' {if (strcmp(lastDefMethod,"main") == 0)
                            insertError(errorQ,toString("El metodo \"main\" no debe contener parametros.","",""));
                        cantParams = 0;
						pushOffset(offsetsParam, getGlobalParamOffset());////////////////////////////
						resetGlobalParamOffset();////////////////////////////
                        }
                    parameters {
                                setAmountOfParameters(searchIdInSymbolsTable(errorQ,symbolsTable,lastDefMethod),cantParams);
								setGlobalParamOffset(popOffset(offsetsParam));/////////////////////////////////////
                               }
                    ')'
              ;

parameters    :		type ID {
                                Attribute *aux = createParameter(searchIdInSymbolsTable(errorQ,symbolsTable,lastDefMethod),cantParams,$2,vaType);
                                if (aux != NULL) {pushElement(errorQ,symbolsTable,aux); cantParams++;}
                                else insertError(errorQ,toString("El identificador \"",$2,"\" no puede contener parametros/esa cantidad de parametros."));
                            }

              |		type ID {
                                Attribute *aux = createParameter(searchIdInSymbolsTable(errorQ,symbolsTable,lastDefMethod),cantParams,$2,vaType);
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
              |    PRINTT expression ';' {add_Print(lcode3d, newCode(PRINT), $2);}
              ;

action        :
              |    BREAK {
                            if (isEmpty(labelsWhile) && isEmpty(labelsFor))
                                insertError(errorQ,toString("Error. Solo se puede usar la sentencia \"break\" dentro de un ciclo.","",""));
                            else{
                                char* aux = pop(labelsWhile);
                                char* aux2 = pop(labelsWhile);
                                add_CodeLabel(lcode3d, newCode(GOTO_LABEL), peek(labelsWhile)); //Go to char of End of While
                                push(labelsWhile, aux2);
                                push(labelsWhile, aux);
                                }
                    }
              |    CONTINUE {
                            if (isEmpty(labelsWhile) && isEmpty(labelsFor))
                                insertError(errorQ,toString("Error. Solo se puede usar la sentencia \"continue\" dentro de un ciclo.","",""));
                            else
                            {
                                char *posLabel = pop(labelsWhile); //Label of End of While
                                add_CodeLabel(lcode3d, newCode(GOTO_LABEL), peek(labelsWhile)); //Go to char of Init of While
                                push(labelsWhile, posLabel);
                            } 
                    }
              |	   RETURNN {
                            returns++; 
                            if ((idNotFound == False) && (checkReturn(errorQ,symbolsTable,lastDefMethod) == 0))
                            {
                                Code3D *ret = newCode(RETURN);
                                setCodeLabel(ret, "   -   ");  /* Label "    -    " is added because there are no arguments */
                                add_code(lcode3d, ret);
                            }
                    }   
              |	   RETURNN expression {
                                    returns++; 									
                                    if (idNotFound == False && checkReturnExpression(errorQ,symbolsTable,lastDefMethod,$2) == 0)
                                    { 
                                        Code3D *ret = newCode(RETURN_EXPR);
                                        setCode2D(ret, $2, searchIdInSymbolsTable(errorQ,symbolsTable,lastDefMethod)); 
                                        add_code(lcode3d, ret);  
                                    }                           
                    }
              |    asignation 
              |    method_call                        
              ;

asignation    :     location assig_op expression {
                        controlAssignation(errorQ,lcode3d,$1,$2,$3);
                    }
              ;

assig_op      :    '=' {$$ = "=";} 
              |    PLUSEQUAL {$$ = "+=";}
              |    MINUSEQUAL {$$ = "-=";}
              ;

/* -------------------- END OF STATEMENTS ------------------------------- */

/* -------------------- CONDITIONALS AND CICLES ------------------------------ */

conditional   :     IF '(' {
                            add_CodeLabel(lcode3d, newCode(LABEL), newLabelName("if"));
                        } expression { 
                            controlType(errorQ,$4,Bool,"if",1);
                            char *elseLabel = newLabelName("else");
                            add_CodeLabelCond(lcode3d, newCode(GOTO_LABEL_COND), $4, elseLabel); 
                            push(labelsCYC, newLabelName("end_if"));
                            push(labelsCYC, elseLabel);
                        } ')' block optional 
              ;

optional	  :		{
                        add_CodeLabel(lcode3d, newCode(LABEL), pop(labelsCYC)); // Mark to char of End
                        push(returnStack, pop(labelsCYC));
                    }
              |	   	ELSE {
                        char* elseLabel = pop(labelsCYC);
                        add_CodeLabel(lcode3d, newCode(GOTO_LABEL), peek(labelsCYC)); //Go to char of Else
                        add_CodeLabel(lcode3d, newCode(LABEL), elseLabel); // Mark to char of Else
                    } block {	
                        char* aux = pop(labelsCYC);
                        add_CodeLabel(lcode3d, newCode(LABEL), aux); // Mark to char of End
                        push(returnStack, aux);
                    }
              ;
                                
iteration     :    WHILE {
                                char *whileLabel = newLabelName("while"); 
                                add_CodeLabel(lcode3d, newCode(LABEL), whileLabel); // label of While
                                push(labelsWhile, whileLabel);
                                push(labelsWhile, intToString(codeSize(lcode3d)));
                    } 
                   expression { 
                                char *endWhile = newLabelName("end_while");
                                char *pos = pop(labelsWhile);
                                char *whileLabel = pop(labelsWhile);
                                push(labelsWhile, endWhile);
                                push(labelsWhile, whileLabel); 
                                push(labelsWhile, pos);
                                controlType(errorQ,$3,Bool,"while",1);
                                add_CodeLabelCond(lcode3d, newCode(GOTO_LABEL_COND), $3, endWhile); // Go to label of Expression
                    } block {							
                            add_code(lcode3d, get_code(lcode3d, atoi(pop(labelsWhile))+1));
                            add_CodeLabel(lcode3d, newCode(GOTO_LABEL), pop(labelsWhile)); // Go to label of while
                            add_CodeLabel(lcode3d, newCode(LABEL), pop(labelsWhile)); // label_end of while
                    }
              |    FOR ID {
                        if (getAttributeType(getVariableAttribute(errorQ,symbolsTable,$2)) != Int)
                            insertError(errorQ,toString("El identificador \"", $2, "\" no pertenece a una variable de tipo \"int\""));
                        /* It musn't have the same treatment that while? */
                    } '=' expression ',' expression {
                                    controlType(errorQ,$5,Int,"for",2); controlType(errorQ,$7,Int,"for",3); 
                                    char *forLabel = newLabelName("for");
                                    char *endLabel = newLabelName("end_for");
                                    push(labelsFor, endLabel);
                                    push(labelsFor, forLabel);
                                    push(labelsFor, intToString(codeSize(lcode3d)));
                                    add_Assignation(lcode3d, $5, getVariableAttribute(errorQ, symbolsTable, $2));
                                    Attribute *res = returnMinorComparison(errorQ, lcode3d, getVariableAttribute(errorQ, symbolsTable, $2), $7);
                                    add_CodeLabel(lcode3d, newCode(LABEL), forLabel);
                                    add_CodeLabelCond(lcode3d, newCode(GOTO_LABEL_COND), res, endLabel); // Go to label of Expression
                    } block {
                            controlAssignation(errorQ,lcode3d,getVariableAttribute(errorQ,symbolsTable,$2),"+=",returnValue(lcode3d,Int,"1"));
                            add_code(lcode3d, get_code(lcode3d, atoi(pop(labelsFor))+1));
                            add_CodeLabel(lcode3d, newCode(GOTO_LABEL), pop(labelsFor)); // Go to label of For
                            add_CodeLabel(lcode3d, newCode(LABEL), pop(labelsFor)); // label_end of For
                    }
              ;                                                               

/* -------------------- END OF CONDITIONALS AND CICLES ------------------------------- */

/* -------------------- EXPRESSIONS ------------------------------- */

location      :    ID {$$ = getVariableAttribute(errorQ, symbolsTable, $1);}
              |    ID '[' expression ']' { $$ = checkArrayPos(errorQ,symbolsTable,lcode3d,$1,$3);}
              ;

method_call   :	   ID '(' ')' {
                                cantParams=0; 
                                lastCalledMethod=$1; 
                                add_CodeLabel(lcode3d, newCode(GOTO_METHOD), get_Label(listmlabel, $1)); //Go to char of Init of Method
                                $$ = checkAndGetMethodRetAttribute(errorQ,symbolsTable,lcode3d,$1,0);
                    }

				|    ID '(' {if (searchIdInSymbolsTable(errorQ,symbolsTable,$1) == NULL) 
                                idNotFound = True; 
                            else
                            {
                                pushString(paramsStack,intToString(cantParams));
                                cantParams=0;								
                                pushString(methodsIDStack,lastCalledMethod);
                                lastCalledMethod = $1;
                            }
                    } expression_aux ')' {
                            if (idNotFound != True)
                            {
                                add_CodeLabel(lcode3d, newCode(GOTO_METHOD), get_Label(listmlabel, $1)); //Go to char of Init of Method 
                                $$ = checkAndGetMethodRetAttribute(errorQ,symbolsTable,lcode3d,$1,cantParams); 
                                cantParams=atoi(popString(paramsStack));
                            }
                            else
                            {
                                $$ = createVariable((char*) getVariableName(),Int); 
                                idNotFound = False;
                            }
                    } 

				|    EXTERNINVK '(' STRING ',' typevoid ')' {
                                                            Attribute* res;
                                                            if (mType != RetVoid) 
                                                                res = createVariable("",mType);
                                                            else
                                                                res = createVariable((char*) getVariableName(),Int);
                                                            //add_CodeExternInvk(lcode3d, newCode(EXTERN_INVOKATION),$3, res);
                                                            $$ = res;
                                                            }
				|    EXTERNINVK '(' STRING ',' typevoid ',' externinvk_arg ')' {
                                                                                Attribute* res;
                                                                                if (mType != RetVoid) 
                                                                                    res = createVariable("",mType);
                                                                                else
                                                                                    res = createVariable((char*) getVariableName(),Int);
                                                                                //add_CodeExternInvk(lcode3d, newCode(EXTERN_INVOKATION),$3, res);
                                                                                $$ = res;
                                                                                }
				;

expression_aux:    expression {
                                if (idNotFound != True)
                                {
                                    correctParamBC(errorQ,symbolsTable,lcode3d,$1,lastCalledMethod,cantParams); 
                                    cantParams++;
                                }
                    }
              |    expression {
                                if (idNotFound != True)
                                {
                                    correctParamIC(errorQ,symbolsTable,lcode3d,$1,lastCalledMethod,cantParams); 
                                    cantParams++;
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

expression    :    conjunction					{$$ = $1;}                             
              |    expression ORR conjunction	{$$ = returnOr(errorQ, lcode3d, $1, $3);}
              ;

conjunction   :    inequality                   {$$ = $1;}                                
              |    conjunction ANDD inequality	{$$ = returnAnd(errorQ, lcode3d, $1, $3);}
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

term          :    factor1			{$$ = $1;}
              |    factor1 '+' term	{$$ = returnAdd(errorQ, lcode3d, $1, $3);}
              |    factor1 '-' term	{$$ = returnSub(errorQ, lcode3d, $1, $3);}
              ;

factor1       :    factor			{$$ = $1;}
              |    factor '*' factor1	{$$ = returnMult(errorQ, lcode3d, $1, $3);}
              |    factor '/' factor1	{$$ = returnDiv(errorQ, lcode3d, $1, $3);}
              |    factor '%' factor1	{$$ = returnMod(errorQ, lcode3d, $1, $3);}
              ;

factor        :    primary		{$$ = $1;}  
              |    '!' factor	{$$ = returnNot(errorQ, lcode3d, $2);}
              |    '-' factor	{$$ = returnNeg(errorQ, lcode3d, $2);}
              ;


primary       :    INTEGER			{$$ = returnValue(lcode3d, Int, $1);}
              |    FLOAT            {$$ = returnValue(lcode3d, Float, $1);}
              |    BOOLEAN          {$$ = returnValue(lcode3d, Bool, $1);}
              |    ID				{$$ = getVariableAttribute(errorQ,symbolsTable,$1);}
              |    ID '[' expression ']'  {$$ = checkArrayPos(errorQ,symbolsTable,lcode3d,$1,$3);}
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

