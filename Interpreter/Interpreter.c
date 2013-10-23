/*
 * The interpreter.
 */
#include <stdbool.h>
#include "Interpreter.h"

ListMLabel *labelList;
ListC3D *codeList;
int size;

//ejecuta cada una de las intrucciones del main hasta encontrar el return!
void runMain(ListC3D *list, int pos)
{
    bool returnFound = false;
    while (pos < codeSize && !labelFound)
    {
        NodeC3D *aux = get_listC3D(codeList,i);
        if (strcmp(COM_RETURN, getCommand(getInfo_NodeC3D(aux))) != 0) 
            runOperation(list, pos);
        else
            returnFound = true;
        pos++;
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
		NodeC3D *aux;
        while (!labelFound && (i < codeSize(codeList))
        {
            aux = get_listC3D(codeList,i);
            if ((getCommand(getInfo_NodeC3D(aux)) == COM_MARK) && (strcmp(auxLabel, getLabel(getInfo_NodeC3D(aux), 1)) == 0))
                labelFound = true;
            i++;
        } 
		if (labelFound)
			return i-1;
    }
	return -1;
}

/* Initializes the interpreter and run */
void initInterpreter(ListMLabel *labelL, ListC3D *codeL)
{
    labelList = labelL;
    codeList = codeL;
    size = (*l).size;
    int posMain = searchByLabel("main");
    runMain(codeList, posMain);
}

//Dada la posicion ejecuto esa instruccion!
void runOperation(ListC3D list, int position)
{
	Code3D*	code = get_listC3D(list,position);
	switch ((*code).command)
	{
		/* LOAD_CONST */
        case 0: if (getAttributeType((*(*code).parametro2).val.attri) == Int)
					setIntVal((*(*code).parametro2).val.attri, (*(*code).parametro1).val.intAttri);
				if (getAttributeType((*(*code).parametro2).val.attri) == Float)
					setFloatVal((*(*code).parametro2).val.attri, (*(*code).parametro1).val.floatAttri);
				if (getAttributeType((*(*code).parametro2).val.attri) == Bool)
					setBoolVal((*(*code).parametro2).val.attri, (*(*code).parametro1).val.boolAttri);
				break;
		/* LOAD_MEM */
        case 1: break; //OPERACION NO UTILIZADA EN NINGUNO DE LOS TESTS!
		/* STORE_CONST */
        case 2: break; //OPERACION NO UTILIZADA EN NINGUNO DE LOS TESTS!
		/* STORE_MEM */
        case 3: if (getAttributeType((*(*code).parametro2).val.attri) == Int)
					setIntVal((*(*code).parametro2).val.attri, (*(*code).parametro1).val.intAttri);
				if (getAttributeType((*(*code).parametro2).val.attri) == Float)
					setFloatVal((*(*code).parametro2).val.attri, (*(*code).parametro1).val.floatAttri);
				if (getAttributeType((*(*code).parametro2).val.attri) == Bool)
					setBoolVal((*(*code).parametro2).val.attri, (*(*code).parametro1).val.boolAttri);
				break;
		/* COM_MINUS_INT */
        case 4: setIntVal((*(*code).parametro3).val.attri, (*(*code).parametro1).val.intAttri - (*(*code).parametro2).val.intAttri);
				break;
		/* COM_ADD_INT */
        case 5: setIntVal((*(*code).parametro3).val.attri, (*(*code).parametro1).val.intAttri + (*(*code).parametro2).val.intAttri);
				break;
		/* COM_SUB_INT */
        case 6: break; //ESTE NO SE USA NUNCA!!! ES EL MISMO QUE EL "COM_MINUS_INT".
		/* COM_MULT_INT */
        case 7: setIntVal((*(*code).parametro3).val.attri, (*(*code).parametro1).val.intAttri * (*(*code).parametro2).val.intAttri);
				break;
		/* COM_DIV_INT */
        case 8: setIntVal((*(*code).parametro3).val.attri, (*(*code).parametro1).val.intAttri / (*(*code).parametro2).val.intAttri);
				break;
		/* COM_MOD_INT */
        case 9: setIntVal((*(*code).parametro3).val.attri, (*(*code).parametro1).val.intAttri % (*(*code).parametro2).val.intAttri);
				break;
		/* COM_PLUSEQ_INT */
        case 10: break; //ESTA OPERACION NO EXISTE!!! O AL MENOS NO SE USA
		/* COM_MINUSEQ_INT */
        case 11: break; //ESTA OPERACION NO EXISTE!!! O AL MENOS NO SE USA
		/* COM_MINUS_FLOAT */
        case 12: setFloatVal((*(*code).parametro3).val.attri, (*(*code).parametro1).val.intAttri - (*(*code).parametro2).val.intAttri);
				break;
		/* COM_ADD_FLOAT */
        case 13: setFloatVal((*(*code).parametro3).val.attri, (*(*code).parametro1).val.intAttri + (*(*code).parametro2).val.intAttri);
				break;
		/* COM_SUB_FLOAT */
        case 14: break; //PASA LO MISMO QUE CON EL COM_SUB_INT
		/* COM_MULT_FLOAT */
        case 15: setFloatVal((*(*code).parametro3).val.attri, (*(*code).parametro1).val.intAttri * (*(*code).parametro2).val.intAttri);
				break;
		/* COM_DIV_FLOAT */
        case 16: setFloatVal((*(*code).parametro3).val.attri, (*(*code).parametro1).val.intAttri / (*(*code).parametro2).val.intAttri);
				break;
		/* COM_MOD_FLOAT */
        case 16: break; //ESTA OPERACION NO EXISTE!!
		/* COM_PLUSEQ_FLOAT */
        case 18: break; //OPERACION NO USADA!!
		/* COM_MINUSEQ_FLOAT */
        case 19: break; //OPERACION NO USADA!!
        case 20: return "COM_EQ"; break;
        case 20: setBoolVal((*(*code).parametro3).val.attri, (*(*code).parametro1).val.intAttri == (*(*code).parametro2).val.intAttri);
				break;
        /* COM_DIST */
        case 21: setBoolVal((*(*code).parametro3).val.attri, (*(*code).parametro1).val.intAttri == (*(*code).parametro2).val.intAttri);
				break;
        /* COM_GT */
        case 22: setBoolVal((*(*code).parametro3).val.attri, (*(*code).parametro1).val.intAttri > (*(*code).parametro2).val.intAttri);
				break;
        /* COM_LR */
        case 22: setBoolVal((*(*code).parametro3).val.attri, (*(*code).parametro1).val.intAttri < (*(*code).parametro2).val.intAttri);
				break;
        /* COM_GEQ */
        case 23: setBoolVal((*(*code).parametro3).val.attri, (*(*code).parametro1).val.intAttri >= (*(*code).parametro2).val.intAttri);
				break;
        /* COM_LEQ */
        case 24: setBoolVal((*(*code).parametro3).val.attri, (*(*code).parametro1).val.intAttri <= (*(*code).parametro2).val.intAttri);
				break;
        case 26: return "COM_OR"; break;
        case 27: return "COM_AND"; break;
        case 28: return "COM_NOT"; break;
        case 29: return "COM_MARK"; break;
        case 30: return "GOTOLABEL"; break;
        case 31: return "GOTOLABEL_COND"; break;
        case 32: return "COM_RETURN"; break;
        case 33: return "COM_NEG_INT"; break;
        case 34: return "COM_NEG_FLOAT"; break;
		case 35: return "STORE_MEM_METHOD"; break;
    }
  
}


