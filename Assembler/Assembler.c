
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
    printf("Voy a generar la operacion %i   %s\n", position, getCodeByID(code->command));
    switch ((*code).command)
    {
        /********************************* GENERAL OPERATIONS ******************************/
			/* LOAD_CONST */
        case 0:
            load_Const_Translate(file, code);
            break;

			/* LOAD_ARRAY */
        /* --------------------------------------- MUST BE IMPLEMENTED --------------------------------------- */
        case 1: 
            translateLoadArray(file, code);
            break;

			/* PRINT */
        case 2:
            printOperation(file, code);
            break;			
		
			/* RETURN */
        case 3: 
            translateReturn(file, code);
            break;
		
			/* RETURN_EXPR */
        case 4:
            translateReturnExpression(file, code);
            break;
		
		    /* LABEL */
        case 5: 
            writeLabel(file, labelList, code);
            break;
            /* GOTO_LABEL */
        case 6: 
            translateGotoLabel(file, code);
            break;
            /* GOTO_LABEL_COND */
        case 7:
            translateGotoLabelCondition(file, code);
            break;
		
		/* GOTO_METHOD */
        case 8: 
            goTo_Method(file, code);
            break;
		
        /********************************* INT OPERATIONS **********************************/		
            /* ASSIGNATION_INT */
        case 9: 
            translateAssignationInt(file, code); 
            break;
			/* PARAM_ASSIGN_INT */
        case 10: 
            translateParamAssignInt(file, code);
            break;	
			
            /* MINUS_INT */
        case 11:
            translateMinusInt(file, code);
            break;
            /* ADD_INT */
        case 12:
            add_Int_Translate(file, code);
            break;
            /* MULT_INT */
        case 13:
            mult_Int_Translate(file, code);
            break;
            /* DIV_INT */
        case 14:
            translateDivInt(file, code);
            break;
            /* MOD_INT */
        case 15:
            translateModInt(file, code);
            break;
			/* NEG_INT */
        case 16:
            neg_Int_Translate(file, code);
            break;
		            
			/* EQ_INT */
        case 17:
            translateEqualInt(file, code);
            break;
            /* DIST_INT */
        case 18:
            translateDistinctInt(file, code);
            break;	
			
            /* GREATER_INT */
        case 19:
            greater_IntTranslate(file, code);
            break;
            /* LOWER_INT */
        case 20: 
            translateLesserInt(file, code);
            break;		
			/* GEQ_INT */
        case 21:
            greater_Eq_IntTranslate(file, code);
            break;
			
		    /* LEQ_INT */
        case 22:
            translateLesserOrEqualInt(file, code);
            break;
			
        /********************************* FLOAT OPERATIONS ******************************/			
		    /* ASSIGNATION_FLOAT */
        case 23:
            assignation_FloatTranslate(file, code);
            break;
            /* PARAM_ASSIGN_FLOAT */
        case 24:
			translateParamAssignFloat(file, code);
            break;
			
            /* MINUS_FLOAT */
        case 25:
            translateMinusFloat(file, code);
            break;
            /* ADD_FLOAT */
        case 26:
            translateAddFloat(file, code);
            break;
            /* MULT_FLOAT */
        case 27:
            translateMultFloat(file, code);
            break;
            /* DIV_FLOAT */
        case 28:
            translateDivFloat(file, code);
            break;
			/* NEG_FLOAT */
        case 29: 
            neg_Float_Translate(file, code);
            break;
			/* EQ_FLOAT */
        case 30:
            eq_FloatTranslate(file, code);
            break;
            /* DIST_FLOAT */
        case 31:
            dist_FloatTranslate(file, code);
            break;
            /* GREATER_FLOAT */
        case 32:
            greater_FloatTranslate(file, code);
            break;
            /* LOWER_FLOAT */
        case 33: 
            translateLesserFloat(file, code);
            break;
            /* GEQ_FLOAT */
        case 34:
            greater_Eq_FloatTranslate(file, code);
            break;
            /* LEQ_FLOAT */
        case 35:
            translateLesserOrEqualFloat(file, code);
            break;
        /********************************* BOOLEAN OPERATIONS ******************************/
		    /* ASSIGNATION_BOOL */
        case 36:
            translateAssignationInt(file, code);
            break;
            /* PARAM_ASSIGN_BOOL */
        case 37:
			translateParamAssignInt(file, code);
            break;
			/* EQ_BOOL */
        case 38:
            translateEqualInt(file, code);
            break;
            /* DIST_BOOL */
        case 39:
            translateDistinctInt(file, code);
            break;
            /* OR */
        case 40:
            translateOr(file, code);
            break;
            /* AND */
        case 41:
            translateAnd(file, code);
            break;
            /* NOT */
        case 42: 
            translateNot(file, code);
            break;
            /* EXTERN_INVOKATION */
        case 43:
            translateExternInvk(file, code);
            break;
    }
    writeCodeInFile(file, "\n");
}

/* Initializes the assembly engine and run */
void initAssembler(ListMLabel *labelL, LCode3D *codeL, Stack *stack, char* nameOfFile)
{
    //Initialize file.
    char *fileName = concat(nameOfFile, ".s");
    file = fopen(fileName,"w");
    writeCodeInFile(file, translate(".file", concat(concat("\"", concat(nameOfFile, ".s")), "\""), ""));
    writeCodeInFile(file, translate(".global", "main", ""));
    writeCodeInFile(file, translate(".type", "main", "@function"));
    writeCodeInFile(file, ".INT:\n");
    writeCodeInFile(file, translate(".string", "\"Print. El valor entero es: %d \\n\"", ""));
    writeCodeInFile(file, ".FLOAT:\n");
    writeCodeInFile(file, translate(".string", "\"Print. El valor flotante es: %f \\n\"", ""));
    writeCodeInFile(file, ".BOOL_TRUE:\n");
    writeCodeInFile(file, translate(".string", "\"Print. El valor booleano es: True \\n\"", ""));
    writeCodeInFile(file, ".BOOL_FALSE:\n");
    writeCodeInFile(file, translate(".string", "\"Print. El valor booleano es: False \\n\"", ""));
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
    writeNegFloat(file);
}
