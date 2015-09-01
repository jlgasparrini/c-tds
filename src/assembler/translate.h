/* Functions for translation to assembly code */
#ifndef Translate_H
#define Translate_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../method_list/genlistml.h"
#include "../code_3d/gencode3d.h"
#include "../SymbolsTable/Utils.h"

typedef union {
	int integer;
	float real;
} FloatValue;

FloatValue f_value;

/* Returns the respective operation in assembly code */
char* translate(char*, char*, char*);

/* BASIC OPERATIONS TREATEMENT */
void load_const_translate(FILE*, Code3D*);
void translate_goto_label(FILE*, Code3D*);
void translate_goto_label_condition(FILE*, Code3D*);
void translate_return(FILE*, Code3D*);
void translate_return_expression(FILE*, Code3D*);
void translate_or(FILE*, Code3D*);
void translate_and(FILE*, Code3D*);
void translate_not(FILE*, Code3D*);
void print_operation(FILE*, Code3D*);
void write_label(FILE*, ListMLabel*, Code3D*);
void translate_load_array(FILE*, Code3D*);
void goto_method (FILE*, Code3D*);

/* INT OPERATIONS TREATEMENT */
void translate_assignation_int(FILE*, Code3D*);
void translate_param_assign_int(FILE*, Code3D*);
void neg_int_translate(FILE*, Code3D*);
void add_int_translate(FILE*, Code3D*);
void mult_int_translate(FILE*, Code3D*);
void greater_int_translate(FILE*, Code3D*);
void greater_eq_int_translate(FILE*, Code3D*);
void translate_minus_int(FILE*, Code3D*);
void translate_mod_int(FILE*, Code3D*);
void translate_div_int(FILE*, Code3D*);
void translate_lesser_int(FILE*, Code3D*);
void translate_lesser_or_equal_int(FILE*, Code3D*);
void translate_equal_int(FILE*, Code3D*);
void translate_distinct_int(FILE*, Code3D*);

/* FLOAT OPERATIONS TREATEMENT */
void assignation_float_translate(FILE*, Code3D*);
void translate_param_assign_float(FILE*, Code3D*);
void neg_float_translate(FILE*, Code3D*);
void eq_float_translate(FILE*, Code3D*);
void dist_float_translate(FILE*, Code3D*);
void greater_float_translate(FILE*, Code3D*);
void greater_eq_float_translate(FILE*, Code3D*);
void translate_lesser_or_equal_float(FILE*, Code3D*);
void translate_lesser_float(FILE*, Code3D*);
void translate_div_float(FILE*, Code3D*);
void translate_mult_float(FILE*, Code3D*);
void translate_add_float(FILE*, Code3D*);
void translate_minus_float(FILE*, Code3D*);

/* EXTERN INVOCATIONS OPERATIONS */
void translate_externinvk(FILE*, Code3D*);
void translate_int_extern_param(FILE*, Code3D*);
void translate_float_extern_param(FILE*, Code3D*);
void translate_bool_extern_param(FILE*, Code3D*);

void write_neg_float(FILE* file);

#endif
