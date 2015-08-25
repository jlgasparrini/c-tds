/*
 * The assembly generator.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "assembler.h"
#include "../lib/assembler_utils.h"
#include "../code_3d/operations_code.h"

FILE *file;
ListMLabel *label_list;
LCode3D *code_list;

// Given the position, I run that operation from the code_list
// also this function return the next position of operation to execute!
//static int generate_operation(int position)
static void generate_operation(int position)
{
  Code3D*	code = get_code(code_list, position);
  switch (code->command)
  {
    /* GENERAL OPERATIONS */
    case LOAD_CONST:        load_const_translate(file, code); break;
    case LOAD_ARRAY:        translate_load_array(file, code); break;
    case PRINT:             print_operation(file, code); break;
    case RETURN:            translate_return(file, code); break;
    case RETURN_EXPR:       translate_return_expression(file, code); break;
    case LABEL:             write_label(file, label_list, code); break;
    case GOTO_LABEL:        translate_goto_label(file, code); break;
    case GOTO_LABEL_COND:   translate_goto_label_condition(file, code); break;
    case GOTO_METHOD:       goto_method(file, code); break;

    /* INT OPERATIONS */
    case ASSIGNATION_INT:   translate_assignation_int(file, code); break;
    case PARAM_ASSIGN_INT:  translate_param_assign_int(file, code); break;
    case MINUS_INT:         translate_minus_int(file, code); break;
    case ADD_INT:           add_int_translate(file, code); break;
    case MULT_INT:          mult_int_translate(file, code); break;
    case DIV_INT:           translate_div_int(file, code); break;
    case MOD_INT:           translate_mod_int(file, code); break;
    case NEG_INT:           neg_int_translate(file, code); break;
    case EQ_INT:            translate_equal_int(file, code); break;
    case DIST_INT:          translate_distinct_int(file, code); break;
    case GREATER_INT:       greater_int_translate(file, code); break;
    case LOWER_INT:         translate_lesser_int(file, code); break;
    case GEQ_INT:           greater_eq_int_translate(file, code); break;
    case LEQ_INT:           translate_lesser_or_equal_int(file, code); break;

    /* FLOAT OPERATIONS */
    case ASSIGNATION_FLOAT:     assignation_float_translate(file, code); break;
    case PARAM_ASSIGN_FLOAT:    translate_param_assign_float(file, code); break;
    case MINUS_FLOAT:           translate_minus_float(file, code); break;
    case ADD_FLOAT:             translate_add_float(file, code); break;
    case MULT_FLOAT:            translate_mult_float(file, code); break;
    case DIV_FLOAT:             translate_div_float(file, code); break;
    case NEG_FLOAT:             neg_float_translate(file, code); break;
    case EQ_FLOAT:              eq_float_translate(file, code); break;
    case DIST_FLOAT:            dist_float_translate(file, code); break;
    case GREATER_FLOAT:         greater_float_translate(file, code); break;
    case LOWER_FLOAT:           translate_lesser_float(file, code); break;
    case GEQ_FLOAT:             greater_eq_float_translate(file, code); break;
    case LEQ_FLOAT:             translate_lesser_or_equal_float(file, code); break;

    /* BOOLEAN OPERATIONS */
    case ASSIGNATION_BOOL:  translate_assignation_int(file, code); break;
    case PARAM_ASSIGN_BOOL: translate_param_assign_int(file, code); break;
    case EQ_BOOL:           translate_equal_int(file, code); break;
    case DIST_BOOL:         translate_distinct_int(file, code); break;
    case OR:                translate_or(file, code); break;
    case AND:               translate_and(file, code); break;
    case NOT:               translate_not(file, code); break;

    /* EXTERNAL INVOCATIONS OPERATIONS */
    case EXTERN_INVK:               translate_externinvk(file, code); break;
    case EXTERN_PARAM_ASSIGN_BOOL:  translate_int_extern_param(file, code); break;
    case EXTERN_PARAM_ASSIGN_FLOAT: translate_float_extern_param(file, code); break;
    case EXTERN_PARAM_ASSIGN_INT:   translate_int_extern_param(file, code); break;
  }
  write_code_in_file(file, "\n");
}

/* Initializes the assembly engine and run */
void init_assembler(ListMLabel *ext_label_list, LCode3D *ext_code_list, char* name_of_file)
{
  //Initialize file.
  char* file_name = (char*) concat(name_of_file, ".s");
  file = fopen(file_name, "w");
  write_code_in_file(file, translate(".file", (char*) concat(concat("\"", file_name), "\""), ""));
  write_code_in_file(file, translate(".global", "main", ""));
  write_code_in_file(file, translate(".type", "main", "@function"));
  write_code_in_file(file, ".INT:\n");
  write_code_in_file(file, translate(".string", "\"Print. El valor entero es: %d \\n\"", ""));
  write_code_in_file(file, ".FLOAT:\n");
  write_code_in_file(file, translate(".string", "\"Print. El valor flotante es: %f \\n\"", ""));
  write_code_in_file(file, ".BOOL_TRUE:\n");
  write_code_in_file(file, translate(".string", "\"Print. El valor booleano es: True \\n\"", ""));
  write_code_in_file(file, ".BOOL_FALSE:\n");
  write_code_in_file(file, translate(".string", "\"Print. El valor booleano es: False \\n\"", ""));
  label_list = ext_label_list;
  code_list = ext_code_list;
  int index;
  for (index = 0; index < codeSize(code_list); index++)
    generate_operation(index);
  write_neg_float(file);
}
