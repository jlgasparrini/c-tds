
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
  switch ((*code).command)
  {
    /********************************* GENERAL OPERATIONS ******************************/
    /* LOAD_CONST */
    case LOAD_CONST:
      load_Const_Translate(file, code);
      break;
    case LOAD_ARRAY: 
      translateLoadArray(file, code);
      break;
    case PRINT:
      printOperation(file, code);
      break;			
    case RETURN: 
      translateReturn(file, code);
      break;
    case RETURN_EXPR:
      translateReturnExpression(file, code);
      break;
    case LABEL: 
      writeLabel(file, labelList, code);
      break;
    case GOTO_LABEL: 
      translateGotoLabel(file, code);
      break;
    case GOTO_LABEL_COND:
      translateGotoLabelCondition(file, code);
      break;
    case GOTO_METHOD: 
      goTo_Method(file, code);
      break;
      /********************************* INT OPERATIONS **********************************/		
    case ASSIGNATION_INT: 
      translateAssignationInt(file, code); 
      break;
    case PARAM_ASSIGN_INT:
      translateParamAssignInt(file, code);
      break;	
    case MINUS_INT:
      translateMinusInt(file, code);
      break;
    case ADD_INT:
      add_Int_Translate(file, code);
      break;
    case MULT_INT:
      mult_Int_Translate(file, code);
      break;
    case DIV_INT:
      translateDivInt(file, code);
      break;
    case MOD_INT:
      translateModInt(file, code);
      break;
    case NEG_INT:
      neg_Int_Translate(file, code);
      break;
    case EQ_INT:
      translateEqualInt(file, code);
      break;
    case DIST_INT:
      translateDistinctInt(file, code);
      break;	
    case GREATER_INT:
      greater_IntTranslate(file, code);
      break;
    case LOWER_INT: 
      translateLesserInt(file, code);
      break;		
    case GEQ_INT:
      greater_Eq_IntTranslate(file, code);
      break;
    case LEQ_INT:
      translateLesserOrEqualInt(file, code);
      break;
      /********************************* FLOAT OPERATIONS ******************************/			
    case ASSIGNATION_FLOAT:
      assignation_FloatTranslate(file, code);
      break;
    case PARAM_ASSIGN_FLOAT:
      translateParamAssignFloat(file, code);
      break;
    case MINUS_FLOAT:
      translateMinusFloat(file, code);
      break;
    case ADD_FLOAT:
      translateAddFloat(file, code);
      break;
    case MULT_FLOAT:
      translateMultFloat(file, code);
      break;
    case DIV_FLOAT:
      translateDivFloat(file, code);
      break;
    case NEG_FLOAT: 
      neg_Float_Translate(file, code);
      break;
    case EQ_FLOAT:
      eq_FloatTranslate(file, code);
      break;
    case DIST_FLOAT:
      dist_FloatTranslate(file, code);
      break;
    case GREATER_FLOAT:
      greater_FloatTranslate(file, code);
      break;
    case LOWER_FLOAT: 
      translateLesserFloat(file, code);
      break;
    case GEQ_FLOAT:
      greater_Eq_FloatTranslate(file, code);
      break;
    case LEQ_FLOAT:
      translateLesserOrEqualFloat(file, code);
      break;
      /********************************* BOOLEAN OPERATIONS ******************************/
    case ASSIGNATION_BOOL:
      translateAssignationInt(file, code);
      break;
    case PARAM_ASSIGN_BOOL:
      translateParamAssignInt(file, code);
      break;
    case EQ_BOOL:
      translateEqualInt(file, code);
      break;
    case DIST_BOOL:
      translateDistinctInt(file, code);
      break;
    case OR:
      translateOr(file, code);
      break;
    case AND:
      translateAnd(file, code);
      break;
    case NOT: 
      translateNot(file, code);
      break;
      /********************************* EXTERNAL OPERATIONS ******************************/
    case EXTERN_INVK:
      translateExternInvk(file, code);
      break;
    case EXTERN_PARAM_ASSIGN_BOOL:
      translateIntExternParam(file, code);
      break;
    case EXTERN_PARAM_ASSIGN_FLOAT:
      translateFloatExternParam(file, code);
      break;
    case EXTERN_PARAM_ASSIGN_INT:
      translateIntExternParam(file, code);
      break;
  }
  writeCodeInFile(file, "\n");
}

/* Initializes the assembly engine and run */
void InitAssembler(ListMLabel *labelL, LCode3D *codeL, Stack *stack, char* nameOfFile)
{
  //Initialize file.
  char *fileName = concat(nameOfFile, ".s");
  printf("Assembler generado. Nombre de archivo: %s\n", fileName);
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
