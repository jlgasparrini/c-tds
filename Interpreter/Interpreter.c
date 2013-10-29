/*
 * The interpreter.
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../Code3D/codespecs.h"
#include "../SymbolsTable/StringStack.h"
#include "../SymbolsTable/Utils.h"
#include "Interpreter.h"

ListMLabel *labelList;
LCode3D *codeList;
StringStack *methodsCallStack;

// Given the position, I write that operation from the codeList
// also this function return the next position of operation to generate!
int runOperation(int position)
{
    Code3D*	code = get_code(codeList,position);
//	printf("voy a mostrar el codigo de 3 direcciones: \n");
//	showCode(code);
//	printf("\n");
    printf("Corro la operacion de la posicion %d\n", position);
    switch ((*code).command)
    {
            /* LOAD_CONST */
        case 0:
            if (getAttributeType(getAttribute(code,2)) == Int)
                setIntVal(getAttribute(code,2), (*(*code).param1).val.intAttri);
            if (getAttributeType(getAttribute(code,2)) == Float)
                setFloatVal(getAttribute(code,2), (*(*code).param1).val.floatAttri);
            if (getAttributeType(getAttribute(code,2)) == Bool)
                setBoolVal(getAttribute(code,2), (*(*code).param1).val.boolAttri);
            return position + 1;

            /* ASSIGNATION */
        case 1: 
            if (getAttributeType(getAttribute(code,1)) == Int)
                setIntVal(getAttribute(code,2), getIntVal(getAttribute(code,1)));
            if (getAttributeType(getAttribute(code,1)) == Float)
                setFloatVal(getAttribute(code,2), getFloatVal(getAttribute(code,1)));
            if (getAttributeType(getAttribute(code,1)) == Bool)
                setBoolVal(getAttribute(code,2), getBoolVal(getAttribute(code,1)));
            return position + 1;

            /* MINUS_INT */
        case 2:
            setIntVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) - getIntVal(getAttribute(code,2)));
            return position + 1;

            /* ADD_INT */
        case 3:
            setIntVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) + getIntVal(getAttribute(code,2)));
            return position + 1;

            /* MULT_INT */
        case 4:
            setIntVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) * getIntVal(getAttribute(code,2)));
            return position + 1;

            /* DIV_INT */
        case 5:
            setIntVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) / getIntVal(getAttribute(code,2)));
            return position + 1;

            /* MOD_INT */
        case 6:
            setIntVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) % getIntVal(getAttribute(code,2)));
            return position + 1;

            /* MINUS_FLOAT */
        case 7:
            setFloatVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) - getFloatVal(getAttribute(code,2)));
            return position + 1;

            /* ADD_FLOAT */
        case 8:
            setFloatVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) + getFloatVal(getAttribute(code,2)));
            return position + 1;

            /* MULT_FLOAT */
        case 9:
            setFloatVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) * getFloatVal(getAttribute(code,2)));
            return position + 1;

            /* DIV_FLOAT */
        case 10:
            setFloatVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) / getFloatVal(getAttribute(code,2)));
            return position + 1;

            /* EQ */
        case 11:
            if (getAttributeType(getAttribute(code,2)) == Int)
                setBoolVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) == getIntVal(getAttribute(code,2)));
            if (getAttributeType(getAttribute(code,2)) == Float)
                setBoolVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) == getFloatVal(getAttribute(code,2)));
            if (getAttributeType(getAttribute(code,2)) == Bool)
                setBoolVal(getAttribute(code,2), getBoolVal(getAttribute(code,1)) == getBoolVal(getAttribute(code,2)));
            return position + 1;

            /* DIST */
        case 12:
            if (getAttributeType(getAttribute(code,2)) == Int)
                setBoolVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) != getIntVal(getAttribute(code,2)));
            if (getAttributeType(getAttribute(code,2)) == Float)
                setBoolVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) != getFloatVal(getAttribute(code,2)));
            if (getAttributeType(getAttribute(code,2)) == Bool)
                setBoolVal(getAttribute(code,2), getBoolVal(getAttribute(code,1)) != getBoolVal(getAttribute(code,2)));
            return position + 1;

            /* GT */
        case 13:
            if (getAttributeType(getAttribute(code,2)) == Int)
                setBoolVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) > getIntVal(getAttribute(code,2)));
            if (getAttributeType(getAttribute(code,3)) == Float)
                setBoolVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) > getFloatVal(getAttribute(code,2)));
            if (getAttributeType(getAttribute(code,3)) == Bool)
                setBoolVal(getAttribute(code,3), getBoolVal(getAttribute(code,1)) > getBoolVal(getAttribute(code,2)));
            return position + 1;

            /* LR */
        case 14: 
            if (getAttributeType(getAttribute(code,2)) == Int)
                setBoolVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) < getIntVal(getAttribute(code,2)));
            if (getAttributeType(getAttribute(code,2)) == Float)
                setBoolVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) < getFloatVal(getAttribute(code,2)));
            if (getAttributeType(getAttribute(code,2)) == Bool)
                setBoolVal(getAttribute(code,3), getBoolVal(getAttribute(code,1)) < getBoolVal(getAttribute(code,2)));
            return position + 1;

            /* GEQ */
        case 15:
            if (getAttributeType(getAttribute(code,2)) == Int)
                setBoolVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) >= getIntVal(getAttribute(code,2)));
            if (getAttributeType(getAttribute(code,2)) == Float)
                setBoolVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) >= getFloatVal(getAttribute(code,2)));
            if (getAttributeType(getAttribute(code,2)) == Bool)
                setBoolVal(getAttribute(code,3), getBoolVal(getAttribute(code,1)) >= getBoolVal(getAttribute(code,2)));
            return position + 1;

            /* LEQ */
        case 16:
            if (getAttributeType(getAttribute(code,2)) == Int)
                setBoolVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) <= getIntVal(getAttribute(code,2)));
            if (getAttributeType(getAttribute(code,2)) == Float)
                setBoolVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) <= getFloatVal(getAttribute(code,2)));
            if (getAttributeType(getAttribute(code,2)) == Bool)
                setBoolVal(getAttribute(code,3), getBoolVal(getAttribute(code,1)) <= getBoolVal(getAttribute(code,2)));
            return position + 1;
            break;

            /* OR */
        case 17:
            setBoolVal(getAttribute(code,3), getBoolVal(getAttribute(code,1)) || getBoolVal(getAttribute(code,2)));
            return position + 1;

            /* AND */
        case 18:
            setBoolVal(getAttribute(code,3), getBoolVal(getAttribute(code,1)) && getBoolVal(getAttribute(code,2)));
            return position + 1;

            /* NOT */
        case 19: 
            setBoolVal(getAttribute(code,2), !getBoolVal(getAttribute(code,1)));
            return position + 1;

            /* LABEL */
        case 20: 
            return position + 1;

            /* GOTO_LABEL */
        case 21: 
		    return searchByLabel((*codeList).codes, getLabel(code, 1));

            /* GOTO_LABEL_COND */
        case 22:
            if (getBoolVal((*(*code).param1).val.attri) == False)
                return searchByLabel((*codeList).codes,getLabel(code, 2)); 
            return position + 1;

            /* RETURN */
        case 23: 
            return atoi(popString(methodsCallStack));

            /* NEG_INT */
        case 24:
            setIntVal(getAttribute(code,2), -getIntVal(getAttribute(code,1)));
            return position + 1;

            /* NEG_FLOAT */
        case 25: 
            setFloatVal(getAttribute(code,2), -getFloatVal(getAttribute(code,1)));
            return position + 1;
            
            /* PARAM_ASSIGN */
        case 26: 
			printf("se llamo a param_assign!!!\n");
			if (getAttributeType(getAttribute(code,1)) == Int)
				(*getVariable(code,2)).value.intVal = getIntVal(getAttribute(code,1));
            if (getAttributeType(getAttribute(code,1)) == Float)
				(*getVariable(code,2)).value.floatVal = getFloatVal(getAttribute(code,1));
            if (getAttributeType(getAttribute(code,1)) == Bool)
				(*getVariable(code,2)).value.boolVal = getBoolVal(getAttribute(code,1));
			printf("salio de param_assign!!!\n");
            return position + 1;

            /* PRINT */
        case 27:
            if (getAttributeType(getAttribute(code,1)) == Int)
                printf("Print. El valor entero es: %d\n", getIntVal(getAttribute(code,1)));
            if (getAttributeType(getAttribute(code,1)) == Float)
                printf("Print. El valor flotante es: %f\n", getFloatVal(getAttribute(code,1)));
            if (getAttributeType(getAttribute(code,1)) == Bool)
            {
                if (getBoolVal(getAttribute(code,1)) == True)	
                    printf("Print. El valor booleano es: true\n");
                if (getBoolVal(getAttribute(code,1)) == False)
					printf("Print. El valor booleano es: false\n");
            }
            return position + 1;

			/* LOAD_ARRAY */
		case 28: 
			/* parameter 1 of 3d code is the position of the array
			   parameter 2 is the array from which the number will be getted from.
			   parameter 3 is the resulting attribute. 
			    */
			(*getAttribute(code,3)).decl.variable = &(*getAttribute(code,2)).decl.array.arrayValues[getIntVal(getAttribute(code,1))];
            return position + 1;

            /* RETURN_EXPR */
        case 29: 
            if (getAttributeType(getAttribute(code,2)) == Int)
                setIntVal(getAttribute(code,2), getIntVal(getAttribute(code,1)));
            if (getAttributeType(getAttribute(code,2)) == Float)
                setFloatVal(getAttribute(code,2), getFloatVal(getAttribute(code,1)));
            if (getAttributeType(getAttribute(code,2)) == Bool)
                setBoolVal(getAttribute(code,2), getBoolVal(getAttribute(code,1)));
            return atoi(popString(methodsCallStack));

			/* GOTO_METHOD */
		case 30: 
			/* Save on the stack the place where treatment must continue after the method call */
			pushString(methodsCallStack, intToString(position + 1));
			return searchByLabel((*codeList).codes, getLabel(code,1));
    }

}

/* 
 * Returns the position with the label "label" in the list of code 3D. 
 * If "label" is not found then return -1
 */
int searchByMethodLabel(char* label)
{
    char *auxLabel = get_Label(labelList, label);
    if (auxLabel == "NULL")
        printf("ERROR: LABEL no encontrado!    %s  encontrado. \n", auxLabel);
    else
    {
        bool labelFound = false;
        int i = 0;
        Code3D *aux;
        while (!labelFound && i < codeSize(codeList))
        {
            aux = get_code(codeList,i);
			if (isLabel(aux,1))
			{
	            if (strcmp(auxLabel, getLabel(aux, 1)) == 0)
		            labelFound = true;
			}
            i++;
        } 
        if (labelFound)
            return i-1;
    }
    return -1;
}

//ejecuta cada una de las intrucciones del main hasta encontrar el return! toma la posicion en donde se encuentra el el label main.
void runMain(int pos)
{
    while (pos < codeSize(codeList))
		pos = runOperation(pos);
}

/* Initializes the interpreter and run */
//Toma el codigo 3D, la lista de metodos y la pila de IF's!!
void initInterpreter(ListMLabel *labelL, LCode3D *codeL)
{
    labelList = labelL;
    codeList = codeL;
	methodsCallStack = initializeSS();
	pushString(methodsCallStack, intToString(codeSize(codeL)));
    runMain(searchByMethodLabel("main"));
}
