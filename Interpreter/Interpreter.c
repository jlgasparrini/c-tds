/*
 * The interpreter.
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../Code3D/codespecs.h"
#include "Interpreter.h"

ListMLabel *labelList;
LCode3D *codeList;
int size;

// Given the position, I run that operation from the codeList
void runOperation(int position)
{
	Code3D*	code = get_code(codeList,position);
	switch ((*code).command)
	{
		/* LOAD_CONST */
        case 0: if (getAttributeType((*(*code).param2).val.attri) == Int)
					setIntVal((*(*code).param2).val.attri, (*(*code).param1).val.intAttri);
				if (getAttributeType((*(*code).param2).val.attri) == Float)
					setFloatVal((*(*code).param2).val.attri, (*(*code).param1).val.floatAttri);
				if (getAttributeType((*(*code).param2).val.attri) == Bool)
					setBoolVal((*(*code).param2).val.attri, (*(*code).param1).val.boolAttri);
				break;

		/* STORE_MEM */
        case 1: 
				if (getAttributeType((*(*code).param1).val.attri) == Int)
					setIntVal((*(*code).param2).val.attri, getIntVal((*(*code).param1).val.attri));
				if (getAttributeType((*(*code).param1).val.attri) == Float)
					setFloatVal((*(*code).param2).val.attri, getFloatVal((*(*code).param1).val.attri));
				if (getAttributeType((*(*code).param1).val.attri) == Bool)
					setBoolVal((*(*code).param2).val.attri, getBoolVal((*(*code).param1).val.attri));
				break;

		/* COM_MINUS_INT */
//		case 2: setIntVal((*(*code).param3).val.attri, (*(*code).param1).val.intAttri - (*(*code).param2).val.intAttri);
        case 2: setIntVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) - getIntVal((*(*code).param2).val.attri));
				break;

		/* COM_ADD_INT */
//		case 3: setIntVal((*(*code).param3).val.attri, (*(*code).param1).val.intAttri + (*(*code).param2).val.intAttri);
        case 3: setIntVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) + getIntVal((*(*code).param2).val.attri));
				break;

		/* COM_MULT_INT */
//		case 4: setIntVal((*(*code).param3).val.attri, (*(*code).param1).val.intAttri * (*(*code).param2).val.intAttri);
        case 4: setIntVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) * getIntVal((*(*code).param2).val.attri));
				break;

		/* COM_DIV_INT */
//		case 5: setIntVal((*(*code).param3).val.attri, (*(*code).param1).val.intAttri / (*(*code).param2).val.intAttri);
        case 5: setIntVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) / getIntVal((*(*code).param2).val.attri));
				break;

		/* COM_MOD_INT */
//		case 6: setIntVal((*(*code).param3).val.attri, (*(*code).param1).val.intAttri % (*(*code).param2).val.intAttri);
        case 6: setIntVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) % getIntVal((*(*code).param2).val.attri));
				break;

		/* COM_MINUS_FLOAT */
//		case 7: setFloatVal((*(*code).param3).val.attri, (*(*code).param1).val.intAttri - (*(*code).param2).val.intAttri);
        case 7: setFloatVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) - getFloatVal((*(*code).param2).val.attri));
				break;

		/* COM_ADD_FLOAT */
//		case 8: setFloatVal((*(*code).param3).val.attri, (*(*code).param1).val.intAttri + (*(*code).param2).val.intAttri);
        case 8: setFloatVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) + getFloatVal((*(*code).param2).val.attri));
				break;

		/* COM_MULT_FLOAT */
//		case 9: setFloatVal((*(*code).param3).val.attri, (*(*code).param1).val.intAttri * (*(*code).param2).val.intAttri);
        case 9: setFloatVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) * getFloatVal((*(*code).param2).val.attri));
				break;

		/* COM_DIV_FLOAT */
//		case 10: setFloatVal((*(*code).param3).val.attri, (*(*code).param1).val.intAttri / (*(*code).param2).val.intAttri);
        case 10: setFloatVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) / getFloatVal((*(*code).param2).val.attri));
				break;

        /* COM_EQ */
        case 11:
				if (getAttributeType((*(*code).param2).val.attri) == Int)
					setBoolVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) == getIntVal((*(*code).param2).val.attri));
				if (getAttributeType((*(*code).param2).val.attri) == Float)
					setBoolVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) == getFloatVal((*(*code).param2).val.attri));
				if (getAttributeType((*(*code).param2).val.attri) == Bool)
					setBoolVal((*(*code).param2).val.attri, getBoolVal((*(*code).param1).val.attri) == getBoolVal((*(*code).param2).val.attri));
				break;

        /* COM_DIST */
        case 12:
				if (getAttributeType((*(*code).param2).val.attri) == Int)
					setBoolVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) != getIntVal((*(*code).param2).val.attri));
				if (getAttributeType((*(*code).param2).val.attri) == Float)
					setBoolVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) != getFloatVal((*(*code).param2).val.attri));
				if (getAttributeType((*(*code).param2).val.attri) == Bool)
					setBoolVal((*(*code).param2).val.attri, getBoolVal((*(*code).param1).val.attri) != getBoolVal((*(*code).param2).val.attri));
				break;

        /* COM_GT */
        case 13:
				if (getAttributeType((*(*code).param2).val.attri) == Int)
					setBoolVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) > getIntVal((*(*code).param2).val.attri));
				if (getAttributeType((*(*code).param3).val.attri) == Float)
					setBoolVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) > getFloatVal((*(*code).param2).val.attri));
				if (getAttributeType((*(*code).param3).val.attri) == Bool)
					setBoolVal((*(*code).param3).val.attri, getBoolVal((*(*code).param1).val.attri) > getBoolVal((*(*code).param2).val.attri));
				break;

        /* COM_LR */
        case 14: 
				if (getAttributeType((*(*code).param2).val.attri) == Int)
					setBoolVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) < getIntVal((*(*code).param2).val.attri));
				if (getAttributeType((*(*code).param2).val.attri) == Float)
					setBoolVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) < getFloatVal((*(*code).param2).val.attri));
				if (getAttributeType((*(*code).param2).val.attri) == Bool)
					setBoolVal((*(*code).param3).val.attri, getBoolVal((*(*code).param1).val.attri) < getBoolVal((*(*code).param2).val.attri));
				break;

        /* COM_GEQ */
        case 15:
				if (getAttributeType((*(*code).param2).val.attri) == Int)
					setBoolVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) >= getIntVal((*(*code).param2).val.attri));
				if (getAttributeType((*(*code).param2).val.attri) == Float)
					setBoolVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) >= getFloatVal((*(*code).param2).val.attri));
				if (getAttributeType((*(*code).param2).val.attri) == Bool)
					setBoolVal((*(*code).param3).val.attri, getBoolVal((*(*code).param1).val.attri) >= getBoolVal((*(*code).param2).val.attri));
				break;

        /* COM_LEQ */
        case 16:
				if (getAttributeType((*(*code).param2).val.attri) == Int)
					setBoolVal((*(*code).param3).val.attri, getIntVal((*(*code).param1).val.attri) <= getIntVal((*(*code).param2).val.attri));
				if (getAttributeType((*(*code).param2).val.attri) == Float)
					setBoolVal((*(*code).param3).val.attri, getFloatVal((*(*code).param1).val.attri) <= getFloatVal((*(*code).param2).val.attri));
				if (getAttributeType((*(*code).param2).val.attri) == Bool)
					setBoolVal((*(*code).param3).val.attri, getBoolVal((*(*code).param1).val.attri) <= getBoolVal((*(*code).param2).val.attri));
				break;
		/* COM_OR */
//      case 17: setBoolVal((*(*code).param3).val.attri, (*(*code).param1).val.boolAttri || (*(*code).param2).val.boolAttri);
        case 17: setBoolVal((*(*code).param3).val.attri, getBoolVal((*(*code).param1).val.attri) || getBoolVal((*(*code).param2).val.attri));
				 break;

		/* COM_AND */
//      case 18: setBoolVal((*(*code).param3).val.attri, (*(*code).param1).val.boolAttri && (*(*code).param2).val.boolAttri);
        case 18: setBoolVal((*(*code).param3).val.attri, getBoolVal((*(*code).param1).val.attri) && getBoolVal((*(*code).param2).val.attri));
				 break;

		/* COM_NOT */
        case 19: setBoolVal((*(*code).param2).val.attri, !getBoolVal((*(*code).param1).val.attri));
				 break;

		/* COM_MARK */
        case 20: 
				 break;

		/* GOTOLABEL */
        case 21: 
				 break;

		/* GOTOLABEL_COND */
        case 22: 
				 break;

		/* COM_RETURN */
        case 23: 
				 break;

		/* COM_NEG_INT */
        case 24: setIntVal((*(*code).param2).val.attri, -getIntVal((*(*code).param1).val.attri));
				 break;

		/* COM_NEG_FLOAT */
        case 25: setFloatVal((*(*code).param2).val.attri, -getFloatVal((*(*code).param1).val.attri));
				 break;

		/* STORE_MEM_METHOD */
		case 26: 
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
				break;
    }
  
}

/* 
 * Returns the position with the label "label" in the list of code 3D. 
 * If "label" is not found then return -1
 */
int searchByLabel(char* label)
{
    int i = 0;
    char *auxLabel = get_Label(labelList, label);
    if (auxLabel == "NULL")
        printf("ERROR: LABEL no encontrado!    %s  encontrado. \n", auxLabel);
    else
    {
        bool labelFound = false;
        int i = 0;
		Code3D *aux;
        while (!labelFound && (i < codeSize(codeList)))
        {
            aux = get_code(codeList,i);
			/* POR QUE EL COMANDO TRAIDO DE AUX DEBE SER IGUAL A COM_MARK??????????????????????????????????????????????????????????????????? */
            if ((getCommand(aux) == COM_MARK) && (strcmp(auxLabel, getLabel(aux, 1)) == 0))
                labelFound = true;
            i++;
        } 
		if (labelFound)
			return i-1;
    }
	return -1;
}

//ejecuta cada una de las intrucciones del main hasta encontrar el return!
void runMain(int pos)
{
    bool returnFound = false;
	Code3D *aux;
    while (pos < codeSize(codeList) && !returnFound)
    {
        aux = get_code(codeList,pos);
        if (getCommand(aux) != COM_RETURN) 
            runOperation(pos);
        else
            returnFound = true;
        pos++;
    }
}

/* Initializes the interpreter and run */
void initInterpreter(ListMLabel *labelL, LCode3D *codeL)
{
    labelList = labelL;
    codeList = codeL;
    size = codeSize(codeL);
    runMain(searchByLabel("main"));
}


