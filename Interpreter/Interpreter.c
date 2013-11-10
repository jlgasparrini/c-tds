/*
 * The interpreter.
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../SymbolsTable/StringStack.h"
#include "../SymbolsTable/Utils.h"
#include "Interpreter.h"

ListMLabel *labelList;
LCode3D *codeList;
StringStack *methodsCallStack;

/*
 * param position: position in the 3D list of the 3 directions code that must be interpreted.
 * Interprets the 3 direccions code
 * Returns the position of the next 3 direction code to be interpreted.
 */
int runOperation(int position)
{
    Code3D*	code = get_code(codeList,position);
    switch ((*code).command)
    {

/********************************* GENERAL OPERATIONS TREATEMENT ********************************/

        /* LOAD_CONST */
       case 0:
            if (getAttributeType(getAttribute(code,2)) == Int)
                setIntVal(getAttribute(code,2), (*(*code).param1).val.intAttri);
            if (getAttributeType(getAttribute(code,2)) == Float)
                setFloatVal(getAttribute(code,2), (*(*code).param1).val.floatAttri);
            if (getAttributeType(getAttribute(code,2)) == Bool)
                setBoolVal(getAttribute(code,2), (*(*code).param1).val.boolAttri);
            return position + 1;

            /* LOAD_ARRAY */
        case 1: 
            /* parameter 1 of 3d code is the position of the array
               parameter 2 is the array from which the number will be getted from.
               parameter 3 is the resulting attribute. 
               */
            (*getAttribute(code,3)).decl.variable = &(*getAttribute(code,2)).decl.array.arrayValues[getIntVal(getAttribute(code,1))];
            return position + 1;

            /* PRINT */
        case 2:
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

            /* RETURN */
        case 3: 
            return atoi(popString(methodsCallStack));

            /* RETURN_EXPR */
        case 4: 
            /* Link the expression obtained with the return value of the method */
            if (getAttributeType(getAttribute(code,2)) == Int)
                setIntVal(getAttribute(code,2), getIntVal(getAttribute(code,1)));
            if (getAttributeType(getAttribute(code,2)) == Float)
                setFloatVal(getAttribute(code,2), getFloatVal(getAttribute(code,1)));
            if (getAttributeType(getAttribute(code,2)) == Bool)
                setBoolVal(getAttribute(code,2), getBoolVal(getAttribute(code,1)));
            return atoi(popString(methodsCallStack));

            /* LABEL */
        case 5: 
            return position + 1;

            /* GOTO_LABEL */
        case 6: 
            return searchByLabel((*codeList).codes, getLabel(code, 1));

            /* GOTO_LABEL_COND */
        case 7:
            if (getBoolVal((*(*code).param1).val.attri) == False)
                return searchByLabel((*codeList).codes,getLabel(code, 2)); 
            return position + 1;

            /* GOTO_METHOD */
        case 8: 
            /* Save on the stack the place where treatment must continue after the method call */
            pushString(methodsCallStack, intToString(position + 1));
            return searchByLabel((*codeList).codes, getLabel(code,1));

/********************************* INT OPERATIONS TREATEMENT ********************************/

            /* ASSIGNATION_INT */
        case 9: 
            setIntVal(getAttribute(code,2), getIntVal(getAttribute(code,1)));
            return position + 1;
        
            /* PARAM_ASSIGN_INT */
        case 10: 
            setIntVal(getAttribute(code,2), getIntVal(getAttribute(code,1)));
            return position + 1;

            /* MINUS_INT */
        case 11:
            setIntVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) - getIntVal(getAttribute(code,2)));
            return position + 1;

            /* ADD_INT */
        case 12:
            setIntVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) + getIntVal(getAttribute(code,2)));
            return position + 1;

            /* MULT_INT */
        case 13:
            setIntVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) * getIntVal(getAttribute(code,2)));
            return position + 1;

            /* DIV_INT */
        case 14:
            setIntVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) / getIntVal(getAttribute(code,2)));
            return position + 1;

            /* MOD_INT */
        case 15:
            setIntVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) % getIntVal(getAttribute(code,2)));
            return position + 1;

            /* NEG_INT */
        case 16:
            setIntVal(getAttribute(code,2), -getIntVal(getAttribute(code,1)));
            return position + 1;

            /* EQ_INT */
        case 17:
            setBoolVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) == getIntVal(getAttribute(code,2)));
            return position + 1;

            /* DIST_INT */
        case 18:
            setBoolVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) != getIntVal(getAttribute(code,2)));
            return position + 1;

            /* GREATER_INT */
        case 19:
            setBoolVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) > getIntVal(getAttribute(code,2)));
            return position + 1;

            /* LOWER_INT */
        case 20: 
            setBoolVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) < getIntVal(getAttribute(code,2)));
            return position + 1;

            /* GEQ_INT */
        case 21:
            setBoolVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) >= getIntVal(getAttribute(code,2)));
            return position + 1;

            /* LEQ_INT */
        case 22:
            setBoolVal(getAttribute(code,3), getIntVal(getAttribute(code,1)) <= getIntVal(getAttribute(code,2)));
            return position + 1;

/********************************* FLOAT OPERATIONS TREATEMENT ******************************/

            /* ASSIGNATION_FLOAT */
        case 23: 
            setFloatVal(getAttribute(code,2), getFloatVal(getAttribute(code,1)));
            return position + 1;

            /* PARAM_ASSIGN_FLOAT */
        case 24: 
            setFloatVal(getAttribute(code,2), getFloatVal(getAttribute(code,1)));
            return position + 1;

            /* MINUS_FLOAT */
        case 25:
            setFloatVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) - getFloatVal(getAttribute(code,2)));
            return position + 1;

            /* ADD_FLOAT */
        case 26:
            setFloatVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) + getFloatVal(getAttribute(code,2)));
            return position + 1;

            /* MULT_FLOAT */
        case 27:
            setFloatVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) * getFloatVal(getAttribute(code,2)));
            return position + 1;

            /* DIV_FLOAT */
        case 28:
            setFloatVal(getAttribute(code,3), ((float) getFloatVal(getAttribute(code,1))) / (float) getFloatVal(getAttribute(code,2)));
            return position + 1;

            /* NEG_FLOAT */
        case 29: 
            setFloatVal(getAttribute(code,2), -getFloatVal(getAttribute(code,1)));
            return position + 1;

            /* EQ_FLOAT */
        case 30:
            setBoolVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) == getFloatVal(getAttribute(code,2)));
            return position + 1;

            /* DIST_FLOAT */
        case 31:
            setBoolVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) != getFloatVal(getAttribute(code,2)));
            return position + 1;

            /* GREATER_FLOAT */
        case 32:
            setBoolVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) > getFloatVal(getAttribute(code,2)));
            return position + 1;

            /* LOWER_FLOAT */
        case 33: 
            setBoolVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) < getFloatVal(getAttribute(code,2)));
            return position + 1;

            /* GEQ_FLOAT */
        case 34:
            setBoolVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) >= getFloatVal(getAttribute(code,2)));
            return position + 1;

            /* LEQ_FLOAT */
        case 35:
            setBoolVal(getAttribute(code,3), getFloatVal(getAttribute(code,1)) <= getFloatVal(getAttribute(code,2)));
            return position + 1;


/********************************* BOOLEAN OPERATIONS TREATEMENT ******************************/

            /* ASSIGNATION_BOOL */
        case 36: 
            setBoolVal(getAttribute(code,2), getBoolVal(getAttribute(code,1)));
            return position + 1;

            /* PARAM_ASSIGN_BOOL */
        case 37: 
            setBoolVal(getAttribute(code,2), getBoolVal(getAttribute(code,1)));
            return position + 1;

            /* EQ_BOOL */
        case 38:
            setBoolVal(getAttribute(code,3), getBoolVal(getAttribute(code,1)) == getBoolVal(getAttribute(code,2)));
            return position + 1;

            /* DIST_BOOL */
        case 39:
            setBoolVal(getAttribute(code,3), getBoolVal(getAttribute(code,1)) != getBoolVal(getAttribute(code,2)));
            return position + 1;

            /* OR */
        case 40:
            setBoolVal(getAttribute(code,3), getBoolVal(getAttribute(code,1)) || getBoolVal(getAttribute(code,2)));
            return position + 1;

            /* AND */
        case 41:
            setBoolVal(getAttribute(code,3), getBoolVal(getAttribute(code,1)) && getBoolVal(getAttribute(code,2)));
            return position + 1;

            /* NOT */
        case 42: 
            setBoolVal(getAttribute(code,2), !getBoolVal(getAttribute(code,1)));
            return position + 1;

    }

}

/* 
 * param label: name of the method that must be found.
 * Returns the position with the label "label" in the list of code 3D. 
 * If "label" is not found then return -1.
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

/*
 * param pos: position in the list of 3 directions code of the label "main".
 * Executes the method "main".
 */ 
void runMain(int pos)
{
    while (pos < codeSize(codeList))
        pos = runOperation(pos);
}

/* 
 * param labelL: list with the labels of methods found on the parsing stage.
 * param codeL: list with the 3 directions code.
 * Initializes the interpreter and runs it.
 */
void initInterpreter(ListMLabel *labelL, LCode3D *codeL)
{
    labelList = labelL;
    codeList = codeL;
    methodsCallStack = initializeSS();
    pushString(methodsCallStack, intToString(codeSize(codeL)));
    runMain(searchByMethodLabel("main"));
}
