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
      if (get_attribute_type(get_attribute(code, 2)) == Int)
        set_int_val(get_attribute(code, 2), code->param1->val.intAttri);
      if (get_attribute_type(get_attribute(code, 2)) == Float)
        set_float_val(get_attribute(code, 2), code->param1->val.floatAttri);
      if (get_attribute_type(get_attribute(code, 2)) == Bool)
        set_bool_val(get_attribute(code, 2), code->param1->val.boolAttri);
      break;

    case LOAD_ARRAY:
      /* parameter 1 of 3d code is the position of the array
         parameter 2 is the array from which the number will be getted from.
         parameter 3 is the resulting attribute.
         */
      get_attribute(code, 3)->decl.variable = &get_attribute(code, 2)->decl.array.arrayValues[get_int_val(get_attribute(code, 1))];
      break;

    case PRINT:
      if (get_attribute_type(get_attribute(code, 1)) == Int)
        printf("Print. El valor entero es: %d\n", get_int_val(get_attribute(code, 1)));
      if (get_attribute_type(get_attribute(code, 1)) == Float)
        printf("Print. El valor flotante es: %f\n", get_float_val(get_attribute(code, 1)));
      if (get_attribute_type(get_attribute(code, 1)) == Bool)
      {
        if (get_bool_val(get_attribute(code, 1)) == True)
          printf("Print. El valor booleano es: true\n");
        if (get_bool_val(get_attribute(code, 1)) == False)
          printf("Print. El valor booleano es: false\n");
      }
      break;

    case RETURN:
      return atoi(pop_string(methods_call_stack));

    case RETURN_EXPR:
      /* Link the expression obtained with the return value of the method */
      if (get_attribute_type(get_attribute(code, 2)) == Int)
        set_int_val(get_attribute(code, 2), get_int_val(get_attribute(code, 1)));
      if (get_attribute_type(get_attribute(code, 2)) == Float)
        set_float_val(get_attribute(code, 2), get_float_val(get_attribute(code, 1)));
      if (get_attribute_type(get_attribute(code, 2)) == Bool)
        set_bool_val(get_attribute(code, 2), get_bool_val(get_attribute(code, 1)));
      return atoi(pop_string(methods_call_stack));

    case LABEL: break;

    case GOTO_LABEL: return search_by_label(code_list->codes, get_label(code, 1));

    case GOTO_LABEL_COND: if (get_bool_val(get_attribute(code, 1)) == False)
                            return search_by_label(code_list->codes,get_label(code, 2));
                          break;

    /* Save on the stack the place where treatment must continue after the method call */
    case GOTO_METHOD: push_string(methods_call_stack, int_to_string(position + 1));
                      return search_by_label(code_list->codes, get_label(code, 1));

    /*INT OPERATIONS TREATEMENT */
    case ASSIGNATION_INT:   set_int_val(get_attribute(code, 2), get_int_val(get_attribute(code, 1))); break;
    case PARAM_ASSIGN_INT:  set_int_val(get_attribute(code, 2), get_int_val(get_attribute(code, 1))); break;
    case MINUS_INT:         set_int_val(get_attribute(code, 3), get_int_val(get_attribute(code, 1)) - get_int_val(get_attribute(code, 2))); break;
    case ADD_INT:           set_int_val(get_attribute(code, 3), get_int_val(get_attribute(code, 1)) + get_int_val(get_attribute(code, 2))); break;
    case MULT_INT:          set_int_val(get_attribute(code, 3), get_int_val(get_attribute(code, 1)) * get_int_val(get_attribute(code, 2))); break;
    case DIV_INT:           set_int_val(get_attribute(code, 3), get_int_val(get_attribute(code, 1)) / get_int_val(get_attribute(code, 2))); break;
    case MOD_INT:           set_int_val(get_attribute(code, 3), get_int_val(get_attribute(code, 1)) % get_int_val(get_attribute(code, 2))); break;
    case NEG_INT:           set_int_val(get_attribute(code, 2), -get_int_val(get_attribute(code, 1))); break;
    case EQ_INT:            set_bool_val(get_attribute(code, 3), get_int_val(get_attribute(code, 1)) == get_int_val(get_attribute(code, 2))); break;
    case DIST_INT:          set_bool_val(get_attribute(code, 3), get_int_val(get_attribute(code, 1)) != get_int_val(get_attribute(code, 2))); break;
    case GREATER_INT:       set_bool_val(get_attribute(code, 3), get_int_val(get_attribute(code, 1)) > get_int_val(get_attribute(code, 2))); break;
    case LOWER_INT:         set_bool_val(get_attribute(code, 3), get_int_val(get_attribute(code, 1)) < get_int_val(get_attribute(code, 2))); break;
    case GEQ_INT:           set_bool_val(get_attribute(code, 3), get_int_val(get_attribute(code, 1)) >= get_int_val(get_attribute(code, 2))); break;
    case LEQ_INT:           set_bool_val(get_attribute(code, 3), get_int_val(get_attribute(code, 1)) <= get_int_val(get_attribute(code, 2))); break;

    /* FLOAT OPERATIONS TREATEMENT */
    case ASSIGNATION_FLOAT:   set_float_val(get_attribute(code, 2), get_float_val(get_attribute(code, 1))); break;
    case PARAM_ASSIGN_FLOAT:  set_float_val(get_attribute(code, 2), get_float_val(get_attribute(code, 1))); break;
    case MINUS_FLOAT:         set_float_val(get_attribute(code, 3), get_float_val(get_attribute(code, 1)) - get_float_val(get_attribute(code, 2))); break;
    case ADD_FLOAT:           set_float_val(get_attribute(code, 3), get_float_val(get_attribute(code, 1)) + get_float_val(get_attribute(code, 2))); break;
    case MULT_FLOAT:          set_float_val(get_attribute(code, 3), get_float_val(get_attribute(code, 1)) * get_float_val(get_attribute(code, 2))); break;
    case DIV_FLOAT:           set_float_val(get_attribute(code, 3), ((float) get_float_val(get_attribute(code, 1))) / (float) get_float_val(get_attribute(code, 2))); break;
    case NEG_FLOAT:           set_float_val(get_attribute(code, 2), -get_float_val(get_attribute(code, 1))); break;
    case EQ_FLOAT:            set_bool_val(get_attribute(code, 3), get_float_val(get_attribute(code, 1)) == get_float_val(get_attribute(code, 2))); break;
    case DIST_FLOAT:          set_bool_val(get_attribute(code, 3), get_float_val(get_attribute(code, 1)) != get_float_val(get_attribute(code, 2))); break;
    case GREATER_FLOAT:       set_bool_val(get_attribute(code, 3), get_float_val(get_attribute(code, 1)) > get_float_val(get_attribute(code, 2))); break;
    case LOWER_FLOAT:         set_bool_val(get_attribute(code, 3), get_float_val(get_attribute(code, 1)) < get_float_val(get_attribute(code, 2))); break;
    case GEQ_FLOAT:           set_bool_val(get_attribute(code, 3), get_float_val(get_attribute(code, 1)) >= get_float_val(get_attribute(code, 2))); break;
    case LEQ_FLOAT:           set_bool_val(get_attribute(code, 3), get_float_val(get_attribute(code, 1)) <= get_float_val(get_attribute(code, 2))); break;

    /* BOOLEAN OPERATIONS TREATEMENT */
    case ASSIGNATION_BOOL:  set_bool_val(get_attribute(code, 2), get_bool_val(get_attribute(code, 1))); break;
    case PARAM_ASSIGN_BOOL: set_bool_val(get_attribute(code, 2), get_bool_val(get_attribute(code, 1))); break;
    case EQ_BOOL:           set_bool_val(get_attribute(code, 3), get_bool_val(get_attribute(code, 1)) == get_bool_val(get_attribute(code, 2))); break;
    case DIST_BOOL:         set_bool_val(get_attribute(code, 3), get_bool_val(get_attribute(code, 1)) != get_bool_val(get_attribute(code, 2))); break;
    case OR:                set_bool_val(get_attribute(code, 3), get_bool_val(get_attribute(code, 1)) || get_bool_val(get_attribute(code, 2))); break;
    case AND:               set_bool_val(get_attribute(code, 3), get_bool_val(get_attribute(code, 1)) && get_bool_val(get_attribute(code, 2))); break;
    case NOT:               set_bool_val(get_attribute(code, 2), !get_bool_val(get_attribute(code, 1))); break;

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
  char *auxLabel = get_label_ml(label_list, label);
  if (strcmp(auxLabel, "NULL") == 0)
    printf("ERROR: LABEL no encontrado!    %s  encontrado. \n", auxLabel);
  else
  {
    bool labelFound = false;
    int i = 0;
    Code3D *aux;
    while (!labelFound && i < code_size(code_list))
    {
      aux = get_code(code_list,i);
      if (is_label(aux,1))
      {
        if (strcmp(auxLabel, get_label(aux, 1)) == 0)
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
  while (pos < code_size(code_list))
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
  methods_call_stack = initialize_string_stack();
  push_string(methods_call_stack, int_to_string(code_size(code_l)));
  run_main(search_by_method_label("main"));
}
