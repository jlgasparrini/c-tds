
/*
 * The assembly generator.
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Code3D/codespecs.h"
#include "../Stack/stack.h"
#include "Assembler.h"
#include "Translate.h"

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

/* Initializes the interpreter and run */
//Toma el codigo 3D, la lista de metodos y la pila de IF's!!
void initAssembler(ListMLabel *labelL, LCode3D *codeL, Stack *stack, char* file)
{
    //Initialize file.
    char *fileName = concat(file, ".asm");
    archivo = fopen(fileName,"w");
    writeCodeInFile(archivo, "\t.file", fileName, "");

    labelList = labelL;
    codeList = codeL;
    returnStack = stack;
    size = codeSize(codeL);
}
