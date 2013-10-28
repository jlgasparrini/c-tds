/*
 * The interpreter.
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../Code3D/codespecs.h"
#include "../Stack/stack.h"
#include "Interpreter.h"

ListMLabel *labelList;
LCode3D *codeList;
Stack *returnStack;
int size;

// Given the position, I run that operation from the codeList
// also this function return the next position of operation to execute!
int runOperation(int position)
{
//	printf("entre a run operation \n");
    Code3D*	code = get_code(codeList,position);
//	printf("voy a mostrar el codigo de 3 direcciones: \n");
//	showCode(code);
//	printf("\n");
    printf("Corro la operacion de la posicion %d\n", position);
    switch ((*code).command)
    {
            /* LOAD_CONST */
        case 0:
            if (getAttributeType((*(*code).param2).val.attri) == Int)
                setIntVal((*(*code).param2).val.attri, (*(*code).param1).val.intAttri);
            if (getAttributeType((*(*code).param2).val.attri) == Float)
                setFloatVal((*(*code).param2).val.attri, (*(*code).param1).val.floatAttri);
            if (getAttributeType((*(*code).param2).val.attri) == Bool)
                setBoolVal((*(*code).param2).val.attri, (*(*code).param1).val.boolAttri);
            return position+1;

            /* ASSIGNATION */
        case 1: 
            if (getAttributeType((*(*code).param1).val.attri) == Int)
                setIntVal((*(*code).param2).val.attri, getIntVal((*(*code).param1).val.attri));
            if (getAttributeType((*(*code).param1).val.attri) == Float)
                setFloatVal((*(*code).param2).val.attri, getFloatVal((*(*code).param1).val.attri));
            if (getAttributeType((*(*code).param1).val.attri) == Bool)
                setBoolVal((*(*code).param2).val.attri, getBoolVal((*(*code).param1).val.attri));
            return position+1;

            /* MINUS_INT */
        case 2:
            setIntVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) - getIntVal((*(*code).param2).val.attri));
            return position+1;

            /* ADD_INT */
        case 3:
            setIntVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) + getIntVal((*(*code).param2).val.attri));
            return position+1;

            /* MULT_INT */
        case 4:
            setIntVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) * getIntVal((*(*code).param2).val.attri));
            return position+1;

            /* DIV_INT */
        case 5:
            setIntVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) / getIntVal((*(*code).param2).val.attri));
            return position+1;

            /* MOD_INT */
        case 6:
            setIntVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) % getIntVal((*(*code).param2).val.attri));
            return position+1;

            /* MINUS_FLOAT */
        case 7:
            setFloatVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) - getFloatVal((*(*code).param2).val.attri));
            return position+1;

            /* ADD_FLOAT */
        case 8:
            setFloatVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) + getFloatVal((*(*code).param2).val.attri));
            return position+1;

            /* MULT_FLOAT */
        case 9:
            setFloatVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) * getFloatVal((*(*code).param2).val.attri));
            return position+1;

            /* DIV_FLOAT */
        case 10:
            setFloatVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) / getFloatVal((*(*code).param2).val.attri));
            return position+1;

            /* EQ */
        case 11:
            if (getAttributeType((*(*code).param2).val.attri) == Int)
                setBoolVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) == getIntVal((*(*code).param2).val.attri));
            if (getAttributeType((*(*code).param2).val.attri) == Float)
                setBoolVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) == getFloatVal((*(*code).param2).val.attri));
            if (getAttributeType((*(*code).param2).val.attri) == Bool)
                setBoolVal((*(*code).param2).val.attri, getBoolVal((*(*code).param1).val.attri) == getBoolVal((*(*code).param2).val.attri));
            return position+1;

            /* DIST */
        case 12:
            if (getAttributeType((*(*code).param2).val.attri) == Int)
                setBoolVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) != getIntVal((*(*code).param2).val.attri));
            if (getAttributeType((*(*code).param2).val.attri) == Float)
                setBoolVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) != getFloatVal((*(*code).param2).val.attri));
            if (getAttributeType((*(*code).param2).val.attri) == Bool)
                setBoolVal((*(*code).param2).val.attri, getBoolVal((*(*code).param1).val.attri) != getBoolVal((*(*code).param2).val.attri));
            //printf("code con %d\n", code->param1->val.attri->decl.variable.value.boolVal);
            return position+1;

            /* GT */
        case 13:
            if (getAttributeType((*(*code).param2).val.attri) == Int)
                setBoolVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) > getIntVal((*(*code).param2).val.attri));
            if (getAttributeType((*(*code).param3).val.attri) == Float)
                setBoolVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) > getFloatVal((*(*code).param2).val.attri));
            if (getAttributeType((*(*code).param3).val.attri) == Bool)
                setBoolVal((*(*code).param3).val.attri, getBoolVal((*(*code).param1).val.attri) > getBoolVal((*(*code).param2).val.attri));
            return position+1;

            /* LR */
        case 14: 
            if (getAttributeType((*(*code).param2).val.attri) == Int)
                setBoolVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) < getIntVal((*(*code).param2).val.attri));
            if (getAttributeType((*(*code).param2).val.attri) == Float)
                setBoolVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) < getFloatVal((*(*code).param2).val.attri));
            if (getAttributeType((*(*code).param2).val.attri) == Bool)
                setBoolVal((*(*code).param3).val.attri, getBoolVal((*(*code).param1).val.attri) < getBoolVal((*(*code).param2).val.attri));
            return position+1;

            /* GEQ */
        case 15:
            if (getAttributeType((*(*code).param2).val.attri) == Int)
                setBoolVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) >= getIntVal((*(*code).param2).val.attri));
            if (getAttributeType((*(*code).param2).val.attri) == Float)
                setBoolVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) >= getFloatVal((*(*code).param2).val.attri));
            if (getAttributeType((*(*code).param2).val.attri) == Bool)
                setBoolVal((*(*code).param3).val.attri, getBoolVal((*(*code).param1).val.attri) >= getBoolVal((*(*code).param2).val.attri));
            return position+1;

            /* LEQ */
        case 16:
            if (getAttributeType((*(*code).param2).val.attri) == Int)
                setBoolVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) <= getIntVal((*(*code).param2).val.attri));
            if (getAttributeType((*(*code).param2).val.attri) == Float)
                setBoolVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) <= getFloatVal((*(*code).param2).val.attri));
            if (getAttributeType((*(*code).param2).val.attri) == Bool)
                setBoolVal((*(*code).param3).val.attri, getBoolVal((*(*code).param1).val.attri) <= getBoolVal((*(*code).param2).val.attri));
            return position+1;
            break;

            /* OR */
        case 17:
            setBoolVal((*(*code).param3).val.attri, getBoolVal((*(*code).param1).val.attri) || getBoolVal((*(*code).param2).val.attri));
            return position+1;

            /* AND */
        case 18:
            setBoolVal((*(*code).param3).val.attri, getBoolVal((*(*code).param1).val.attri) && getBoolVal((*(*code).param2).val.attri));
            return position+1;

            /* NOT */
        case 19: 
            setBoolVal((*(*code).param2).val.attri, !getBoolVal((*(*code).param1).val.attri));
            return position+1;

            /* LABEL */
        case 20: 
            return position+1;

            /* GOTO_LABEL */
        case 21: 
            //printf("Voy a saltar a %s en la posicion %d\n", getLabel(code, 1),searchByLabel((*codeList).codes, getLabel(code, 1)) + 1);
	    return searchByLabel((*codeList).codes, getLabel(code, 1)) + 1;
            break;

            /* GOTO_LABEL_COND */
        case 22:
            //printf("Voy a saltar a %d\n", searchByLabel((*codeList).codes,getLabel(code, 2)) + 1);
            //printf("%s tiene %d\n", code->param1->val.attri->decl.variable.id, code->param1->val.attri->decl.variable.value.intVal);
            if ((*(*(*code).param1).val.attri).decl.variable.value.boolVal == False)
                return searchByLabel((*codeList).codes,getLabel(code, 2)); 
            return position + 1;

            /* RETURN */
        case 23: 
            return position;

            /* NEG_INT */
        case 24:
            setIntVal((*(*code).param2).val.attri, -getIntVal((*(*code).param1).val.attri));
            return position + 1;

            /* NEG_FLOAT */
        case 25: 
            setFloatVal((*(*code).param2).val.attri, -getFloatVal((*(*code).param1).val.attri));
            return position + 1;
            
            /* PARAM_ASSIGN */
        case 26: 
	    (*(*code).param2).val.attri = (*(*code).param1).val.attri;
            return position + 1;
            break;

            /* PRINT */
        case 27:
            if (getAttributeType((*(*code).param1).val.attri) == Int)
                printf("Print. El valor entero es: %d\n", getIntVal((*(*code).param1).val.attri));
            if (getAttributeType((*(*code).param1).val.attri) == Float)
                printf("Print. El valor flotante es: %f\n", getFloatVal((*(*code).param1).val.attri));
            if (getAttributeType((*(*code).param1).val.attri) == Bool)
            {
                if (getBoolVal((*(*code).param1).val.attri) == True)	
                    printf("Print. El valor booleano es: true\n");
                if (getBoolVal((*(*code).param1).val.attri) == False)	
                    printf("Print. El valor booleano es: false\n");
            }
            return position+1;
    }

}

/* 
 * Returns the position with the label "label" in the list of code 3D. 
 * If "label" is not found then return -1
 */
// Esto solamente sirve para los metodos!!! -.-
int searchByMethodLabel(char* label, int pos)
{
    char *auxLabel = get_Label(labelList, label);
    if (auxLabel == "NULL")
        printf("ERROR: LABEL no encontrado!    %s  encontrado. \n", auxLabel);
    else
    {
        bool labelFound = false;
        int i = pos;
        Code3D *aux;
        while (!labelFound && i < codeSize(codeList))
        {
            aux = get_code(codeList,i);
            if (strcmp(auxLabel, getLabel(aux, 1)) == 0)
                labelFound = true;
            i++;
        } 
        if (labelFound)
            return i-1;
    }
    return pos;
}

//ejecuta cada una de las intrucciones del main hasta encontrar el return! toma la posicion en donde se encuentra el el label main.
void runMain(int pos)
{
    bool returnFound = false;
    Code3D *aux;
    while (pos < codeSize(codeList) && !returnFound)
    {
        aux = get_code(codeList,pos);
        if (getCommand(aux) != RETURN) 
            pos = runOperation(pos);
        else
            returnFound = true;
        //pos++; Ahora la proxima instruccion a ejecutar la devolverá runOperation!
    }
}

/* Initializes the interpreter and run */
//Toma el codigo 3D, la lista de metodos y la pila de IF's!!
void initInterpreter(ListMLabel *labelL, LCode3D *codeL, Stack *stack)
{
    labelList = labelL;
    codeList = codeL;
    returnStack = stack;
    size = codeSize(codeL);
    runMain(searchByMethodLabel("main", 0));
}
