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
char* translate(char* operation, char* code1, char* code2);

/* BASIC OPERATIONS TREATEMENT */
void load_const_translate(FILE *file, Code3D *code);
void translate_goto_label(FILE *file, Code3D *code);
void translate_goto_label_condition(FILE *file, Code3D *code);
void translate_return(FILE *file, Code3D *code);
void translate_return_expression(FILE *file, Code3D *code);
void translate_or(FILE *file, Code3D *code);
void translate_and(FILE *file, Code3D *code);
void translate_not(FILE *file, Code3D *code);
void print_operation(FILE *file, Code3D *code);
void write_label(FILE*, ListMLabel*, Code3D*);
void translate_load_array(FILE *file, Code3D *code);
void goto_method(FILE *file, Code3D *code);

/* INT OPERATIONS TREATEMENT */
void translate_assignation_int(FILE *file, Code3D *code);
void translate_param_assign_int(FILE *file, Code3D *code);
void neg_int_translate(FILE *file, Code3D *code);
void add_int_translate(FILE *file, Code3D *code);
void mult_int_translate(FILE *file, Code3D *code);
void greater_int_translate(FILE *file, Code3D *code);
void greater_eq_int_translate(FILE *file, Code3D *code);
void translate_minus_int(FILE *file, Code3D *code);
void translate_mod_int(FILE *file, Code3D *code);
void translate_div_int(FILE *file, Code3D *code);
void translate_lesser_int(FILE *file, Code3D *code);
void translate_lesser_or_equal_int(FILE *file, Code3D *code);
void translate_equal_int(FILE *file, Code3D *code);
void translate_distinct_int(FILE *file, Code3D *code);

/* FLOAT OPERATIONS TREATEMENT */
void assignation_float_translate(FILE *file, Code3D *code);
void translate_param_assign_float(FILE *file, Code3D *code);
void neg_float_translate(FILE *file, Code3D *code);
void eq_float_translate(FILE *file, Code3D *code);
void dist_float_translate(FILE *file, Code3D *code);
void greater_float_translate(FILE *file, Code3D *code);
void greater_eq_float_translate(FILE *file, Code3D *code);
void translate_lesser_or_equal_float(FILE *file, Code3D *code);
void translate_lesser_float(FILE *file, Code3D *code);
void translate_div_float(FILE *file, Code3D *code);
void translate_mult_float(FILE *file, Code3D *code);
void translate_add_float(FILE *file, Code3D *code);
void translate_minus_float(FILE *file, Code3D *code);

/* EXTERN INVOCATIONS OPERATIONS */
void translate_externinvk(FILE *file, Code3D *code);
void translate_int_extern_param(FILE *file, Code3D *code);
void translate_float_extern_param(FILE *file, Code3D *code);
void translate_bool_extern_param(FILE *file, Code3D *code);

void write_neg_float(FILE *file);

#endif
