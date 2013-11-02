
/*
 * The assembly generator.
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Assembler.h"
#include "Translate.h"
#include "../Code3D/codespecs.h"

FILE *file;
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
			load_Const_Translate(file, code);
            break;

            /* ASSIGNATION */
        case 1: 
			translateAssignation(file, code);
            break;

            /* MINUS_INT */
        case 2:
			translateMinusInt(file, code);
            break;

            /* ADD_INT */
        case 3:
			add_Int_Translate(file, code);
            break;

            /* MULT_INT */
        case 4:
			mult_Int_Translate(file, code);
            break;

            /* DIV_INT */
        case 5:
			translateDivInt(file, code);
            break;

            /* MOD_INT */
        case 6:
			translateModInt(file, code);
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

            /* EQ_INT */
        case 11:
			translateEqualInt(file, code);
            break;

            /* DIST_INT */
        case 12:
			translateDistinctInt(file, code);
            break;

            /* GREATER_INT */
        case 13:
			greater_IntTranslate(file, code);
            break;

            /* LESSER_INT */
        case 14: 
			translateLesserInt(file, code);
            break;

            /* GEQ_INT */
        case 15:
			greater_Eq_IntTranslate(file, code);
            break;

			/* LESSER_EQ_INT */
        case 16:
			translateLesserOrEqualInt(file, code);
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
            writeLabel(file, code);
            break;

            /* GOTO_LABEL */
        case 21: 
			translateGotoLabel(file, code);
            break;

            /* GOTO_LABEL_COND */
        case 22:
			translateGotoLabelCondition(file, code);
            break;

            /* RETURN */
        case 23: 
			translateReturn(file, code);
            break;

            /* NEG_INT */
        case 24:
			neg_Int_Translate(file, code);
            break;

            /* NEG_FLOAT */
        case 25: 
            break;
            
            /* PARAM_ASSIGN */
        case 26: 
            break;

            /* PRINT */
        case 27:
            printOperation(file, code);
            break;
			
			/* LOAD_ARRAY */
		case 28: 
            break;
			
		    /* RETURN_EXPR */
        case 29:
			translateReturnExpression(file, code);
            break;

			/* GOTO_METHOD */
		case 30: 
            break;
			
		    /* EQ_FLOAT */
        case 31:
            break;

            /* DIST_FLOAT */
        case 32:
            break;

            /* GREATER_FLOAT */
        case 33:
			greater_FloatTranslate(file, code);
            break;

            /* LESSER_FLOAT */
        case 34: 
            break;

            /* GEQ_FLOAT */
        case 35:
			greater_Eq_FloatTranslate(file, code);
            break;

            /* LEQ_FLOAT */
        case 36:
            break;
    }

}

/* Initializes the interpreter and run */
//Toma el codigo 3D, la lista de metodos y la pila de IF's!!
void initAssembler(ListMLabel *labelL, LCode3D *codeL, Stack *stack, char* nameOfFile)
{
    //Initialize file.
    char *fileName = concat(nameOfFile, ".s");
    file = fopen(fileName,"w");
    writeCodeInFile(file, "\t.file", concat(concat("\"", concat(nameOfFile, ".s")), "\""), "");
    writeCodeInFile(file, "\t.global", "main", "");
    writeCodeInFile(file, ".INT:", "", "");
    writeCodeInFile(file, "\t.string", "\"Print. El valor entero es: %d \\n\"", "");
    writeCodeInFile(file, ".FLOAT:", "", "");
    writeCodeInFile(file, "\t.string", "\"Print. El valor flotante es: %d \\n\"", "");
    writeCodeInFile(file, ".BOOL:", "", "");
    writeCodeInFile(file, "\t.string", "\"Print. El valor booleano es: %d \\n\"", "");
    labelList = labelL;
    codeList = codeL;
    returnStack = stack;
    size = codeSize(codeL);
    int i = 0;
    while (i < size - 1)
    {       
        generateOperation(i);
        i++;
    }
}
