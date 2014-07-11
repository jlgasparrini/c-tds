/*
 * The interpreter.
 */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "interpreter.h"
#include "../SymbolsTable/StringStack.h"
#include "../SymbolsTable/Utils.h"

ListMLabel *label_list;
LCode3D *code_list;
StringStack *methods_call_stack;

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
      return position + 1;

    case LOAD_ARRAY:
      /* parameter 1 of 3d code is the position of the array
         parameter 2 is the array from which the number will be getted from.
         parameter 3 is the resulting attribute.
         */
      getAttribute(code, 3)->decl.variable = &getAttribute(code, 2)->decl.array.arrayValues[getIntVal(getAttribute(code, 1))];
      return position + 1;

      /* PRINT */
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
      return position + 1;

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

    case LABEL:
      return position + 1;

    case GOTO_LABEL:
      return searchByLabel(code_list->codes, getLabel(code, 1));

    case GOTO_LABEL_COND:
      if (getBoolVal(getAttribute(code, 1)) == False)
        return searchByLabel(code_list->codes,getLabel(code, 2));
      return position + 1;

    case GOTO_METHOD:
      /* Save on the stack the place where treatment must continue after the method call */
      pushString(methods_call_stack, intToString(position + 1));
      return searchByLabel(code_list->codes, getLabel(code, 1));

      /*INT OPERATIONS TREATEMENT */
    case ASSIGNATION_INT:
      setIntVal(getAttribute(code, 2), getIntVal(getAttribute(code, 1)));
      return position + 1;

    case PARAM_ASSIGN_INT:
      setIntVal(getAttribute(code, 2), getIntVal(getAttribute(code, 1)));
      return position + 1;

    case MINUS_INT:
      setIntVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) - getIntVal(getAttribute(code, 2)));
      return position + 1;

    case ADD_INT:
      setIntVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) + getIntVal(getAttribute(code, 2)));
      return position + 1;

    case MULT_INT:
      setIntVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) * getIntVal(getAttribute(code, 2)));
      return position + 1;

    case DIV_INT:
      setIntVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) / getIntVal(getAttribute(code, 2)));
      return position + 1;

    case MOD_INT:
      setIntVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) % getIntVal(getAttribute(code, 2)));
      return position + 1;

    case NEG_INT:
      setIntVal(getAttribute(code, 2), -getIntVal(getAttribute(code, 1)));
      return position + 1;

    case EQ_INT:
      setBoolVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) == getIntVal(getAttribute(code, 2)));
      return position + 1;

    case DIST_INT:
      setBoolVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) != getIntVal(getAttribute(code, 2)));
      return position + 1;

    case GREATER_INT:
      setBoolVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) > getIntVal(getAttribute(code, 2)));
      return position + 1;

    case LOWER_INT:
      setBoolVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) < getIntVal(getAttribute(code, 2)));
      return position + 1;

    case GEQ_INT:
      setBoolVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) >= getIntVal(getAttribute(code, 2)));
      return position + 1;

    case LEQ_INT:
      setBoolVal(getAttribute(code, 3), getIntVal(getAttribute(code, 1)) <= getIntVal(getAttribute(code, 2)));
      return position + 1;

      /* FLOAT OPERATIONS TREATEMENT */

      /* ASSIGNATION_FLOAT */
    case 23:
      setFloatVal(getAttribute(code, 2), getFloatVal(getAttribute(code, 1)));
      return position + 1;

      /* PARAM_ASSIGN_FLOAT */
    case 24:
      setFloatVal(getAttribute(code, 2), getFloatVal(getAttribute(code, 1)));
      return position + 1;

      /* MINUS_FLOAT */
    case 25:
      setFloatVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) - getFloatVal(getAttribute(code, 2)));
      return position + 1;

      /* ADD_FLOAT */
    case 26:
      setFloatVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) + getFloatVal(getAttribute(code, 2)));
      return position + 1;

      /* MULT_FLOAT */
    case 27:
      setFloatVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) * getFloatVal(getAttribute(code, 2)));
      return position + 1;

      /* DIV_FLOAT */
    case 28:
      setFloatVal(getAttribute(code, 3), ((float) getFloatVal(getAttribute(code, 1))) / (float) getFloatVal(getAttribute(code, 2)));
      return position + 1;

      /* NEG_FLOAT */
    case 29:
      setFloatVal(getAttribute(code, 2), -getFloatVal(getAttribute(code, 1)));
      return position + 1;

      /* EQ_FLOAT */
    case 30:
      setBoolVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) == getFloatVal(getAttribute(code, 2)));
      return position + 1;

      /* DIST_FLOAT */
    case 31:
      setBoolVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) != getFloatVal(getAttribute(code, 2)));
      return position + 1;

      /* GREATER_FLOAT */
    case 32:
      setBoolVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) > getFloatVal(getAttribute(code, 2)));
      return position + 1;

      /* LOWER_FLOAT */
    case 33:
      setBoolVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) < getFloatVal(getAttribute(code, 2)));
      return position + 1;

      /* GEQ_FLOAT */
    case 34:
      setBoolVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) >= getFloatVal(getAttribute(code, 2)));
      return position + 1;

      /* LEQ_FLOAT */
    case 35:
      setBoolVal(getAttribute(code, 3), getFloatVal(getAttribute(code, 1)) <= getFloatVal(getAttribute(code, 2)));
      return position + 1;


      /* BOOLEAN OPERATIONS TREATEMENT */

      /* ASSIGNATION_BOOL */
    case 36:
      setBoolVal(getAttribute(code, 2), getBoolVal(getAttribute(code, 1)));
      return position + 1;

      /* PARAM_ASSIGN_BOOL */
    case 37:
      setBoolVal(getAttribute(code, 2), getBoolVal(getAttribute(code, 1)));
      return position + 1;

      /* EQ_BOOL */
    case 38:
      setBoolVal(getAttribute(code, 3), getBoolVal(getAttribute(code, 1)) == getBoolVal(getAttribute(code, 2)));
      return position + 1;

      /* DIST_BOOL */
    case 39:
      setBoolVal(getAttribute(code, 3), getBoolVal(getAttribute(code, 1)) != getBoolVal(getAttribute(code, 2)));
      return position + 1;

      /* OR */
    case 40:
      setBoolVal(getAttribute(code, 3), getBoolVal(getAttribute(code, 1)) || getBoolVal(getAttribute(code, 2)));
      return position + 1;

      /* AND */
    case 41:
      setBoolVal(getAttribute(code, 3), getBoolVal(getAttribute(code, 1)) && getBoolVal(getAttribute(code, 2)));
      return position + 1;

      /* NOT */
    case 42:
      setBoolVal(getAttribute(code, 2), !getBoolVal(getAttribute(code, 1)));
      return position + 1;
  }
}

/*
 * param label: name of the method that must be found.
 * Returns the position with the label "label" in the list of code 3D.
 * If "label" is not found then return -1.
 */
static int search_by_method_label(char* label)
{
  char *auxLabel = get_Label(label_list, label);
  if (auxLabel == "NULL")
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
void InitInterpreter(ListMLabel *label_l, LCode3D *code_l)
{
  label_list = label_l;
  code_list = code_l;
  methods_call_stack = initializeSS();
  pushString(methods_call_stack, intToString(codeSize(code_l)));
  run_main(search_by_method_label("main"));
}
