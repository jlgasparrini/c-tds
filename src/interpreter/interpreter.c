/*
 * The interpreter.
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"
#include "../SymbolsTable/StringStack.h"
#include "../SymbolsTable/Utils.h"

ListMLabel *label_list;
LCode3D *code_list;
StringStack *methods_call_stack;

/* Show warnings on interpreter for externinvk senteces.*/
static void warning_externinvk()
{
  printf("WARNING! the externinvk sentences are ignored on interpreter mode.\n");
}

/*
 * param position: position in the 3D list of the 3 directions code that must be interpreted.
 * Interprets the 3 direccions code
 * Returns the position of the next 3 direction code to be interpreted.
 */
static int run_operation(int position)
{
  Code3D*	code = get_code(code_list, position);
  switch (code->command)
  {
    /* GENERAL OPERATIONS TREATEMENT */
    case LOAD_CONST:
      if (getAttributeType(getAttribute(code, 2)) == Int)
        setIntVal(getAttribute(code, 2), code->param1->val.intAttri);
      if (getAttributeType(getAttribute(code, 2)) == Float)
        setFloatVal(getAttribute(code, 2), code->param1->val.floatAttri);
      if (getAttributeType(getAttribute(code, 2)) == Bool)
        setBoolVal(getAttribute(code, 2), code->param1->val.boolAttri);
      break;

    case LOAD_ARRAY:
      /* parameter 1 of 3d code is the position of the array
         parameter 2 is the array from which the number will be getted from.
         parameter 3 is the resulting attribute.
         */
      getAttribute(code, 3)->decl.variable = &getAttribute(code, 2)->decl.array.arrayValues[getIntVal(getAttribute(code, 1))];
      break;

    case PRINT:
      if (getAttributeType(getAttribute(code, 1)) == Int)
        printf("Print. El valor entero es: %d\n", getIntVal(getAttribute(code, 1)));
      if (getAttributeType(getAttribute(code, 1)) == Float)
        printf("Print. El valor flotante es: %f\n", getFloatVal(getAttribute(code, 1)));
      if (getAttributeType(getAttribute(code, 1)) == Bool)
      {
        if (getBoolVal(getAttribute(code, 1)) == True)
          printf("Print. El valor booleano es: true\n");
        if (getBoolVal(getAttribute(code, 1)) == False)
          printf("Print. El valor booleano es: false\n");
      }
      break;

    case RETURN:
      return atoi(popString(methods_call_stack));

    case RETURN_EXPR:
      /* Link the expression obtained with the return value of the method */
      if (getAttributeType(getAttribute(code, 2)) == Int)
        setIntVal(getAttribute(code, 2), getIntVal(getAttribute(code, 1)));
      if (getAttributeType(getAttribute(code, 2)) == Float)
        setFloatVal(getAttribute(code, 2), getFloatVal(getAttribute(code, 1)));
      if (getAttributeType(getAttribute(code, 2)) == Bool)
        setBoolVal(getAttribute(code, 2), getBoolVal(getAttribute(code, 1)));
      return atoi(popString(methods_call_stack));

    case LABEL: break;

    case GOTO_LABEL: return searchByLabel(code_list->codes, getLabel(code, 1));

    case GOTO_LABEL_COND: if (getBoolVal(getAttribute(code, 1)) == False)
                            return searchByLabel(code_list->codes,getLabel(code, 2));
                          break;

    /* Save on the stack the place where treatment must continue after the method call */
    case GOTO_METHOD: pushString(methods_call_stack, intToString(position + 1)); 
                      return searchByLabel(code_list->codes, getLabel(code, 1));

    /*INT OPERATIONS TREATEMENT */
    case ASSIGNATION_INT:   setIntVal(getAttribute(code, 2), getIntVal(getAttribute(code, 1))); break;
    case PARAM_ASSIGN_INT:  setIntVal(getAttribute(code, 2), getIntVal(getAttribute(code, 1))); break;
    case MINUS_INT:         setIntVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) - getIntVal(getAttribute(code, 2))); break;
    case ADD_INT:           setIntVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) + getIntVal(getAttribute(code, 2))); break;
    case MULT_INT:          setIntVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) * getIntVal(getAttribute(code, 2))); break;
    case DIV_INT:           setIntVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) / getIntVal(getAttribute(code, 2))); break;
    case MOD_INT:           setIntVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) % getIntVal(getAttribute(code, 2))); break;
    case NEG_INT:           setIntVal(getAttribute(code, 2), -getIntVal(getAttribute(code, 1))); break;
    case EQ_INT:            setBoolVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) == getIntVal(getAttribute(code, 2))); break;
    case DIST_INT:          setBoolVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) != getIntVal(getAttribute(code, 2))); break;
    case GREATER_INT:       setBoolVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) > getIntVal(getAttribute(code, 2))); break;
    case LOWER_INT:         setBoolVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) < getIntVal(getAttribute(code, 2))); break;
    case GEQ_INT:           setBoolVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) >= getIntVal(getAttribute(code, 2))); break;
    case LEQ_INT:           setBoolVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) <= getIntVal(getAttribute(code, 2))); break;

    /* FLOAT OPERATIONS TREATEMENT */
    case ASSIGNATION_FLOAT:   setFloatVal(getAttribute(code, 2), getFloatVal(getAttribute(code, 1))); break;
    case PARAM_ASSIGN_FLOAT:  setFloatVal(getAttribute(code, 2), getFloatVal(getAttribute(code, 1))); break;
    case MINUS_FLOAT:         setFloatVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) - getFloatVal(getAttribute(code, 2))); break;
    case ADD_FLOAT:           setFloatVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) + getFloatVal(getAttribute(code, 2))); break;
    case MULT_FLOAT:          setFloatVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) * getFloatVal(getAttribute(code, 2))); break;
    case DIV_FLOAT:           setFloatVal(getAttribute(code, 3), ((float) getFloatVal(getAttribute(code, 1))) / (float) getFloatVal(getAttribute(code, 2))); break;
    case NEG_FLOAT:           setFloatVal(getAttribute(code, 2), -getFloatVal(getAttribute(code, 1))); break;
    case EQ_FLOAT:            setBoolVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) == getFloatVal(getAttribute(code, 2))); break;
    case DIST_FLOAT:          setBoolVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) != getFloatVal(getAttribute(code, 2))); break;
    case GREATER_FLOAT:       setBoolVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) > getFloatVal(getAttribute(code, 2))); break;
    case LOWER_FLOAT:         setBoolVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) < getFloatVal(getAttribute(code, 2))); break;
    case GEQ_FLOAT:           setBoolVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) >= getFloatVal(getAttribute(code, 2))); break;
    case LEQ_FLOAT:           setBoolVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) <= getFloatVal(getAttribute(code, 2))); break;

    /* BOOLEAN OPERATIONS TREATEMENT */
    case ASSIGNATION_BOOL:  setBoolVal(getAttribute(code, 2), getBoolVal(getAttribute(code, 1))); break;
    case PARAM_ASSIGN_BOOL: setBoolVal(getAttribute(code, 2), getBoolVal(getAttribute(code, 1))); break;
    case EQ_BOOL:           setBoolVal(getAttribute(code, 3), getBoolVal(getAttribute(code, 1)) == getBoolVal(getAttribute(code, 2))); break;
    case DIST_BOOL:         setBoolVal(getAttribute(code, 3), getBoolVal(getAttribute(code, 1)) != getBoolVal(getAttribute(code, 2))); break;
    case OR:                setBoolVal(getAttribute(code, 3), getBoolVal(getAttribute(code, 1)) || getBoolVal(getAttribute(code, 2))); break;
    case AND:               setBoolVal(getAttribute(code, 3), getBoolVal(getAttribute(code, 1)) && getBoolVal(getAttribute(code, 2))); break;
    case NOT:               setBoolVal(getAttribute(code, 2), !getBoolVal(getAttribute(code, 1))); break;

    /* EXTERNAL INVOCATIONS OPERATIONS */
    case EXTERN_INVK:               warning_externinvk(); break;
    case EXTERN_PARAM_ASSIGN_BOOL:  warning_externinvk(); break;
    case EXTERN_PARAM_ASSIGN_FLOAT: warning_externinvk(); break;
    case EXTERN_PARAM_ASSIGN_INT:   warning_externinvk(); break;
  }
  return position + 1;
}

/*
 * param label: name of the method that must be found.
 * Returns the position with the label "label" in the list of code 3D.
 * If "label" is not found then return -1.
 */
static int search_by_method_label(char* label)
{
  char *auxLabel = get_Label(label_list, label);
  if (strcmp(auxLabel, "NULL") == 0)
    printf("ERROR: LABEL no encontrado!    %s  encontrado. \n", auxLabel);
  else
  {
    bool labelFound = false;
    int i = 0;
    Code3D *aux;
    while (!labelFound && i < codeSize(code_list))
    {
      aux = get_code(code_list,i);
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
  return -1;
}

/*
 * param pos: position in the list of 3 directions code of the label "main".
 * Executes the method "main".
 */
static void run_main(int pos)
{
  while (pos < codeSize(code_list))
    pos = run_operation(pos);
}

/*
 * param label_l: list with the labels of methods found on the parsing stage.
 * param code_l: list with the 3 directions code.
 * Initializes the interpreter and runs it.
 */
void init_interpreter(ListMLabel *label_l, LCode3D *code_l)
{
  label_list = label_l;
  code_list = code_l;
  methods_call_stack = initializeSS();
  pushString(methods_call_stack, intToString(codeSize(code_l)));
  run_main(search_by_method_label("main"));
}
