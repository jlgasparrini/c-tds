
/*
 * The assembly generator.
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../Code3D/codespecs.h"
#include "../Stack/stack.h"
#include "Assembler.h"

FILE *archivo;
ListMLabel *labelList;
LCode3D *codeList;
Stack *returnStack;
int size;

// Given the position, I run that operation from the codeList
// also this function return the next position of operation to execute!
int generateOperation(int position)
{
    Code3D*	code = get_code(codeList,position);
    switch ((*code).command)
    {
            /* LOAD_CONST */
        case 0:
            break;

            /* ASSIGNATION */
        case 1: 
            break;

            /* MINUS_INT */
        case 2:
            break;

            /* ADD_INT */
        case 3:
            break;

            /* MULT_INT */
        case 4:
            break;

            /* DIV_INT */
        case 5:
            break;

            /* MOD_INT */
        case 6:
            break;

            /* MINUS_FLOAT */
        case 7:
            break;

            /* ADD_FLOAT */
        case 8:
            break;

            /* MULT_FLOAT */
        case 9:
            break;

            /* DIV_FLOAT */
        case 10:
            break;

            /* EQ */
        case 11:
            break;

            /* DIST */
        case 12:
            break;

            /* GT */
        case 13:
            break;

            /* LR */
        case 14: 
            break;

            /* GEQ */
        case 15:
            break;

            /* LEQ */
        case 16:
            break;

            /* OR */
        case 17:
            break;

            /* AND */
        case 18:
            break;

            /* NOT */
        case 19: 
            break;

            /* LABEL */
        case 20: 

            break;

            /* GOTO_LABEL */
        case 21: 
            break;

            /* GOTO_LABEL_COND */
        case 22:
            break;

            /* RETURN */
        case 23: 
            break;

            /* NEG_INT */
        case 24:
            break;

            /* NEG_FLOAT */
        case 25: 
            break;
            
            /* PARAM_ASSIGN */
        case 26: 
            break;

            /* PRINT */
        case 27:
            break;

			/* LOAD_ARRAY */
		case 28: 
            break;
    }

}

/* 
 * Returns the position with the label "label" in the list of code 3D. 
 * If "label" is not found then return -1
 */
// Esto solamente sirve para los metodos!!! -.-
int jumpByMethodLabel(char* label, int pos)
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
    return pos;
}

//ejecuta cada una de las intrucciones del main hasta encontrar el return! toma la posicion en donde se encuentra el el label main.
void generateMethod(int pos)
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
    }
}

/* Initializes the interpreter and run */
//Toma el codigo 3D, la lista de metodos y la pila de IF's!!
void initAssembler(ListMLabel *labelL, LCode3D *codeL, Stack *stack, char* fileName)
{
    //Initialize file.
    char *fileName = concat(fileName, ".asm");
    archivo = fopen(fileName,"w");
    writeCodeInFile(".file", fileName, "");

    labelList = labelL;
    codeList = codeL;
    returnStack = stack;
    size = codeSize(codeL);
}

//Este podria tomar por separado las operaciones a meter en el archivo.
void writeCodeInFile(char* operation, char* code1, char* code2)
{
    char* backSlashN = strdup("\n");
    char* blank = strdup(" ");
    char *result = malloc(strlen(operation)+strlen(code1)+strlen(code2)+4);
    strcpy(result, operation);
    strcat(result, blank);
    strcat(result, code1);
    strcat(result, blank);
    strcat(result, code2);
    strcat(result, backSlashN);
    fprintf(archivo, result);
}

void writeBlank()
{
    fprintf(archivo, "\n");
}

char* concat(char* str1, char* str2)
{
    char* result = malloc(strlen(str1)+strlen(str2)+1);
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}
