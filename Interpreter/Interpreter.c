/*
 * The interpreter.
 */
#include "Interpreter.h"

ListMLabel *labelList;
ListC3D *codeList;
int size;

void initInterpreter(ListMLabel *labelL, ListC3D *codeL)
{
    labelList = labelL;
    codeList = codeL;
    size = (*l).size;
    int posMain = searchByLabel("main");
    runMain(codeList, posMain);
}

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
 * Returns the position with the label "main" into the list of code 3D. 
 * If "main" is not founded then return -1
 */
int searchByLabel(char* label)
{
    int i = 0;
    char *auxLabel = get_Label(labelList, label);
    if (auxLabel == "NULL")
        //Se supone que esto no va a pasar nunca!!
        printf("ERROR: LABEL no encontrado!    %s  encontrado. \n", auxLabel);
    else
    {
        bool labelFound = false;
        int i = 0;
        while (!labelFound && (i < codeSize(codeList))
        {
            NodeC3D *aux = get_listC3D(codeList,i);
            if (getCommand(getInfo_NodeC3D(aux)) == COM_MARK && (strcmp(auxLabel, getLabel(getInfo_NodeC3D(aux), 1)) == 0) 
                mainFound = true;
            i++;
        } 
        return i--; //Lo encontre, sumé uno y me pase del label encontrado.
    }
}

//Dada la posicion ejecuto esa instruccion!
void runOperation(ListC3D list, int position)
{
        
}
