
/*
 * The assembly generator.
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Assembler.h"
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
    printf("ENTRO POR ACA!         %i   ==    %s\n", code->command, getCodeByID(code->command));
    switch ((*code).command)
    {
        /* LOAD_CONST */
        case 0:
            load_Const_Translate(file, code);
            break;

            /* ASSIGNATION_INT */
        case 1: 
            translateAssignationInt(file, code); 
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
            translateMinusFloat(file, code);
            break;

            /* ADD_FLOAT */
        case 8:
            translateAddFloat(file, code);
            break;

            /* MULT_FLOAT */
        case 9:
            translateMultFloat(file, code);
            break;

            /* DIV_FLOAT */
        case 10:
            translateDivFloat(file, code);
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
            translateOr(file, code);
            break;

            /* AND */
        case 18:
            translateAnd(file, code);
            break;

            /* NOT */
        case 19: 
            translateNot(file, code);
            break;

            /* LABEL */
        case 20: 
            writeLabel(file, labelList, code);
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
            neg_Float_Translate(file, code);
            break;

            /* PARAM_ASSIGN_INT */
            /* --------------------------------------- MUST BE IMPLEMENTED --------------------------------------- */
        case 26: 
            translateParamAssign(file, code);
            break;

            /* PRINT */
        case 27:
            printOperation(file, code);
            break;

            /* LOAD_ARRAY */
            /* --------------------------------------- MUST BE IMPLEMENTED --------------------------------------- */
        case 28: 
            translateLoadArray(file, code);
            break;

            /* RETURN_EXPR */
        case 29:
            translateReturnExpression(file, code);
            break;

            /* GOTO_METHOD */
        case 30: 
            goTo_Method(file, code);
            break;

            /* EQ_FLOAT */
        case 31:
            eq_FloatTranslate(file, code);
            break;

            /* DIST_FLOAT */
        case 32:
            dist_FloatTranslate(file, code);
            break;

            /* GREATER_FLOAT */
        case 33:
            greater_FloatTranslate(file, code);
            break;

            /* LESSER_FLOAT */
        case 34: 
            translateLesserFloat(file, code);
            break;

            /* GEQ_FLOAT */
        case 35:
            greater_Eq_FloatTranslate(file, code);
            break;

            /* LESSER_EQ_FLOAT */
        case 36:
            translateLesserOrEqualFloat(file, code);
            break;

            /* ASSIGNATION_FLOAT */
        case 37:
            assignation_FloatTranslate(file, code);
            break;

            /* PARAM_ASSIGN_FLOAT */
            /* --------------------------------------- MUST BE IMPLEMENTED --------------------------------------- */
        case 38:
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
    writeCodeInFile(file, translate(".file", concat(concat("\"", concat(nameOfFile, ".s")), "\""), ""));
    writeCodeInFile(file, translate(".global", "main", ""));
    writeCodeInFile(file, ".INT:\n");
    writeCodeInFile(file, translate("\t.string", "\"Print. El valor entero es: %d \\n\"", ""));
    writeCodeInFile(file, ".FLOAT:\n");
    writeCodeInFile(file, translate("\t.string", "\"Print. El valor flotante es: %d \\n\"", ""));
    writeCodeInFile(file, ".BOOL:\n");
    writeCodeInFile(file, translate("\t.string", "\"Print. El valor booleano es: %d \\n\"", ""));
    labelList = labelL;
    codeList = codeL;
    returnStack = stack;
    size = codeSize(codeL);
    int i = 0;
    while (i < size)
    {       
        generateOperation(i);
        i++;
    }
}
