/*
 * MISSING DOCUMENTATION!
 */

#include "translate.h"
#include "../lib/assembler_utils.h"

int name_label_count = 0;
int aux_param = 1;
int print_count = 0;
int extern_offset = 0;
bool any_goto_method = false;

/* Return value of a constant. */
char* value(Code3D *code, int i)
{
  char *result = (char*) malloc(sizeof(char));/* CHECK OUT THIS CASE BECAUSE sizeof(char) ONLY STORES MEMORY FOR ONLY ONE CHARACTER! */
  if (is_int(code, i))/* IF THE NUMBER HAS MORE THAN ONE DIGIT (CHARACTER) IT WILL BROKE! */
    sprintf(result, "%d", get_int(code, i));
  if (is_float(code, i))
    sprintf(result, "%f", get_float(code, i));
  if (is_bool(code, i))
    sprintf(result, "%d", get_bool(code, i));
  return concat("$", result);
}

/* Returns the respective operation in assembly code */
char* translate(char *operation, char *code1, char *code2)
{
  char* new_line = "\n";
  char* blank = " ";
  char* tab = "\t";
  char* comma = ",";
  char* result = (char*) malloc(strlen(tab)+strlen(operation)+2*strlen(blank)+strlen(code1)+strlen(comma)+strlen(code2)+strlen(new_line));
  strcpy(result, tab);
  strcat(result, operation);
  if (strlen(code1)>0)
  {
    strcat(result, blank);
    strcat(result, code1);
  }
  if (strlen(code2)>0)
  {
    strcat(result, comma);
    strcat(result, blank);
    strcat(result, code2);
  }
  strcat(result, new_line);
  return result;
}

/**Metodo para la obtencion del offset de una variable*/
char* offset(Code3D *code, int param)
{
  char *result = (char*) malloc(sizeof(char));/* CHECK OUT THIS CASE BECAUSE sizeof(char) ONLY STORES MEMORY FOR ONLY ONE CHARACTER! */
  result =int_to_string(get_offset_val(get_attribute(code, param)));
  return concat(result, "(%rbp)");
}

/**Metodo para la obtencion del offset de un numero dado. Utilizado para las invocaciones externas.*/
char* offset_num(int offset)
{
  char *result = (char*) malloc(sizeof(char));/* CHECK OUT THIS CASE BECAUSE sizeof(char) ONLY STORES MEMORY FOR ONLY ONE CHARACTER! */
  result =int_to_string(offset);
  if (offset == 0)
    return "(%rsp)";
  else
    return concat(result, "(%rsp)");
}

/* Return offset of an array */
static char* offset_array(Code3D *code, int param, char *reg)
{
  int offset = get_offset_array(get_attribute(code, param));
  return concat(concat(concat(int_to_string(offset), "(%rbp,"), reg), ",4)");
}

/* BASIC OPERATIONS */
/**"LOAD_CONST %s %s\n" */
void load_const_translate(FILE *file, Code3D *code)
{
  if (!is_float(code, 1))
    write_code_in_file(file, translate("movl", value(code, 1), offset(code, 2)));
  else
  {
    f_value.real = get_float(code, 1);
    fprintf(file, "\tmov $0x");
    fprintf(file, "%x",f_value.integer);
    fprintf(file, ", %%rax\n");
    write_code_in_file(file, translate("movl", "%eax", offset(code, 2)));
  }
}

/* Puts in the file the translation of the GOTO_LABEL action */
inline void translate_goto_label(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("jmp", get_label(code,1), ""));
}

/* Puts in the file the translation of the GOTO_LABEL_CONDITION action */
void translate_goto_label_condition(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("cmp", "$0", offset(code, 1)));
  write_code_in_file(file, translate("jz", get_label(code,2), ""));
}

/* Puts in the file the translation of the RETURN action */
void translate_return(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movl", "$0", "%eax"));
  write_code_in_file(file, translate("leave","",""));
  write_code_in_file(file, translate("ret","",""));
}

/* Puts in the file the translation of the RETURN_EXPR action */
void translate_return_expression(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movl", offset(code,1), "%eax"));
  write_code_in_file(file, translate("leave","",""));
  write_code_in_file(file, translate("ret","",""));
}

/* Puts in the file the translation of the MINUS_INT action */
void translate_or(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movl", offset(code,1), "%eax"));
  write_code_in_file(file, translate("or", offset(code,2), "%eax"));
  write_code_in_file(file, translate("movl", "%eax", offset(code,3)));
}

/* Puts in the file the translation of the MINUS_INT action */
void translate_and(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movl", offset(code,1), "%eax"));
  write_code_in_file(file, translate("and", offset(code,2), "%eax"));
  write_code_in_file(file, translate("movl", "%eax", offset(code,3)));
}

/* Puts in the file the translation of the MINUS_INT action */
void translate_not(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("cmpl", "$1", offset(code,1)));
  write_code_in_file(file, translate("setne", "%al", ""));
  write_code_in_file(file, translate("movzbl", "%al", "%eax"));
  write_code_in_file(file, translate("movl", "%eax", offset(code, 2)));
}

/* Puts in the file the translation of the PRINT action */
void print_operation(FILE *file, Code3D *code)
{
  if (get_attribute_type(get_attribute(code, 1)) == Int)
  {
    write_code_in_file(file, translate("movq", offset(code, 1), "%rsi"));
    write_code_in_file(file, translate("movq", concat("$", ".INT"), "%rdi"));
  }
  if (get_attribute_type(get_attribute(code, 1)) == Float)
  {
    write_code_in_file(file, translate("movss", offset(code, 1), "%xmm0"));
    write_code_in_file(file, translate("cvtps2pd", "%xmm0", "%xmm0"));
    write_code_in_file(file, translate("movq", concat("$", ".FLOAT"), "%rdi"));
  }
  if (get_attribute_type(get_attribute(code, 1)) == Bool)
  {
    char* count = int_to_string(print_count);
    write_code_in_file(file, translate("cmp", "$0", offset(code, 1)));
    write_code_in_file(file, translate("jz", concat("label_bool_condition_of_print", count), ""));
    write_code_in_file(file, translate("movq", concat("$", ".BOOL_TRUE"), "%rdi"));
    write_code_in_file(file, translate("jmp", concat("end_label_bool_condition_of_print", count), ""));
    write_code_in_file(file, concat(concat("label_bool_condition_of_print", count), ":\n"));
    write_code_in_file(file, translate("movq", concat("$", ".BOOL_FALSE"), "%rdi"));
    write_code_in_file(file, concat(concat("end_label_bool_condition_of_print", count), ":\n"));
    print_count = print_count + 1;
  }
  write_code_in_file(file, translate("movq", "$0", "%rax"));
  write_code_in_file(file, translate("call", "printf", ""));
}

/* Puts in the file the translation of the LABEL action */
void write_label(FILE *file, ListMLabel *list_m_label, Code3D *code)
{
  if (strcmp(get_label_ml(list_m_label, get_label(code, 1)), "NULL") == 0)
    write_code_in_file(file, concat(get_label(code,1), ":\n"));
  else
  {
    write_code_in_file(file, concat(get_label(code,1), ":\n"));
    write_code_in_file(file, translate("pushq", "%rbp", ""));
    write_code_in_file(file, translate("movq", "%rsp", "%rbp"));
    char *result = (char*) malloc(sizeof(char));
    sprintf(result, "%d", get_int(code, 2) - 4);
    write_code_in_file(file, translate("addq", concat("$", result),  "%rsp"));
  }
}

/* Puts in the file the translation of the LOAD_ARRAY action */
void translate_load_array(FILE *file, Code3D *code)
{
  /* parameter 1 of 3d code is the position of the array
   * parameter 2 is the array from which the number will be getted from.
   * parameter 3 is the resulting attribute.
   */
  write_code_in_file(file, translate("movq", offset(code,1), "%rax"));

  if (get_attribute_type(get_attribute(code, 2)) == Float)
  {
    write_code_in_file(file, translate("movss", offset_array(code,2,"%rax"), "%xmm0"));
    write_code_in_file(file, translate("movss", "%xmm0", offset(code,3)));
  }
  else
  {
    write_code_in_file(file, translate("movq", offset_array(code,2,"%rax"), "%rdx"));
    write_code_in_file(file, translate("movq", "%rdx", offset(code,3)));
  }
}

/* Puts in the file the translation of the GOTO_METHOD action */
/* "GOTO_METHOD %s\n" */
void goto_method (FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("call", get_label(code,1), ""));
  /*   DEBO   PREGUNTAR   SI   EL TIPO DE RETORNO DEL METODO ESif DISSTINTO DE VOID!    */
    any_goto_method = true;
}

/* INT OPERATIONS TREATEMENT */
/* Puts in the file the translation of the ASSIGNATION_INT action */
void translate_assignation_int(FILE *file, Code3D *code)
{
  if (!any_goto_method)
  {
    write_code_in_file(file, translate("movl", offset(code,1), "%eax"));
    any_goto_method = false;
  }
  write_code_in_file(file, translate("movl", "%eax", offset(code,2)));
}

/* Puts in the file the translation of the PARAM_ASSIGN_INT action */
void translate_param_assign_int(FILE *file, Code3D *code)
{
  if (is_int(code, 3))
    write_code_in_file(file, translate("subq", concat("$", int_to_string(get_int(code, 3)*4)), "%rsp"));
  write_code_in_file(file, translate("movq", offset(code, 1), "%rax"));
  write_code_in_file(file, translate("movq", "%rax", concat(int_to_string(aux_param*4), "(%rsp)")));
  aux_param++;
}

/*-----------------------------------------------------------------------*/
/**"NEG_INT %s %s\n" */
void neg_int_translate(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movl", offset(code, 1), "%eax"));
  write_code_in_file(file, translate("negl", "%eax", ""));
  write_code_in_file(file, translate("movl", "%eax", offset(code, 2)));
}

/*-----------------------------------------------------------------------*/
/**"ADD_INT %s %s %s\n" */
void add_int_translate(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movq", offset(code, 1), "%rax"));
  write_code_in_file(file, translate("add", offset(code, 2) ,"%rax"));
  write_code_in_file(file, translate("movq", "%rax", offset(code, 3)));
}

/*-----------------------------------------------------------------------*/
/**"MULT_INT %s %s %s\n" */
void mult_int_translate(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movq", offset(code, 1), "%rax"));
  write_code_in_file(file, translate("imulq", offset(code, 2) ,"%rax"));
  write_code_in_file(file, translate("movq", "%rax", offset(code, 3)));
}

/**"GREATER_INT %s %s %s\n" */
void greater_int_translate(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movl", offset(code, 1), "%eax"));
  write_code_in_file(file, translate("cmp", offset(code, 2), "%eax"));
  write_code_in_file(file, translate("setg", "%al", ""));
  write_code_in_file(file, translate("movzbl", "%al", "%eax"));
  write_code_in_file(file, translate("movl", "%eax", offset(code, 3)));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_ EQ_INT %s %s %s\n" */
void greater_eq_int_translate(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movl", offset(code, 1), "%eax"));
  write_code_in_file(file, translate("cmp", offset(code, 2), "%eax"));
  write_code_in_file(file, translate("setge", "%al", ""));
  write_code_in_file(file, translate("movzbl", "%al", "%eax"));
  write_code_in_file(file, translate("movl", "%eax", offset(code, 3)));
}

/* Puts in the file the translation of the MINUS_INT action */
void translate_minus_int(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movq", offset(code,2), "%rax"));
  write_code_in_file(file, translate("movq", offset(code,1), "%r10"));
  write_code_in_file(file, translate("subq", "%rax", "%r10"));
  write_code_in_file(file, translate("movq", "%r10", offset(code,3)));
}

/* Puts in the file the translation of the MOD_INT action */
void translate_mod_int(FILE *file, Code3D *code)
{
  /* it divides"rdx:rax" by "divisor". Stores quotient in rax and remainder in rdx */
  write_code_in_file(file, translate("movq", "$0", "%rdx"));
  write_code_in_file(file, translate("movq", "$0", "%rax"));
  write_code_in_file(file, translate("movq", offset(code, 1) ,"%rax"));
  write_code_in_file(file, translate("idivl", offset(code, 2), ""));
  write_code_in_file(file, translate("movq", "%rdx", offset(code, 3)));
}

/* Puts in the file the translation of the DIV_INT action */
void translate_div_int(FILE *file, Code3D *code)
{
  /* it divides"rdx:rax" by "divisor". Stores quotient in rax and remainder in rdx */
  write_code_in_file(file, translate("movq", "$0", "%rdx"));
  write_code_in_file(file, translate("movq", offset(code, 1) ,"%rax"));
  write_code_in_file(file, translate("idivl", offset(code, 2), ""));
  write_code_in_file(file, translate("movq", "%rax", offset(code, 3)));
}

/* Puts in the file the translation of the LESSER_INT action */
void translate_lesser_int(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movl", offset(code, 1), "%eax"));
  write_code_in_file(file, translate("cmp", offset(code, 2), "%eax"));
  write_code_in_file(file, translate("setl", "%al", ""));
  write_code_in_file(file, translate("movzbl", "%al", "%eax"));
  write_code_in_file(file, translate("movl", "%eax", offset(code, 3)));
}

/* Puts in the file the translation of the LESSER_EQ_INT action */
void translate_lesser_or_equal_int(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movl", offset(code, 1), "%eax"));
  write_code_in_file(file, translate("cmp", offset(code, 2), "%eax"));
  write_code_in_file(file, translate("setle", "%al", ""));
  write_code_in_file(file, translate("movzbl", "%al", "%eax"));
  write_code_in_file(file, translate("movl", "%eax", offset(code, 3)));
}

/* Puts in the file the translation of the EQ_INT action */
void translate_equal_int(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movl", offset(code, 1), "%eax"));
  write_code_in_file(file, translate("cmp", offset(code, 2) ,"%eax"));
  write_code_in_file(file, translate("sete", "%al", ""));
  write_code_in_file(file, translate("movzbl", "%al", "%eax"));
  write_code_in_file(file, translate("movl", "%eax", offset(code, 3)));
}

/* Puts in the file the translation of the DIST_INT action */
void translate_distinct_int(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movl", offset(code, 1), "%eax"));
  write_code_in_file(file, translate("cmp", offset(code, 2) ,"%eax"));
  write_code_in_file(file, translate("setne", "%al", ""));
  write_code_in_file(file, translate("movzbl", "%al", "%eax"));
  write_code_in_file(file, translate("movl", "%eax", offset(code, 3)));
}

/* FLOAT OPERATIONS TREATEMENT */

/*-----------------------------------------------------------------------*/
/**"ASSIGNATION_FLOAT %s %s\n" */
void assignation_float_translate(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movss", offset(code, 1), "%xmm0"));
  write_code_in_file(file, translate("movss", "%xmm0", offset(code, 2)));
}

/* Puts in the file the translation of the PARAM_ASSIGN_FLOAT action */
void translate_param_assign_float(FILE *file, Code3D *code)
{
  if (is_float(code, 3))
    write_code_in_file(file, translate("subq", concat("$", float_to_string(get_float(code, 3)*4)), "%rsp"));
  write_code_in_file(file, translate("movss", offset(code, 1), "%xmm0"));
  write_code_in_file(file, translate("movq", "%rax", concat(int_to_string(aux_param*4), "(%rsp)")));
}

/**"NEG_FLOAT %s %s\n" */
void neg_float_translate(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movss", offset(code, 1), "%xmm1"));
  write_code_in_file(file, translate("movss", ".NEG_FLOAT(%rip)", "%xmm0"));
  write_code_in_file(file, translate("xorps", "%xmm1", "%xmm0"));
  write_code_in_file(file, translate("movss", "%xmm0", offset(code, 2)));
}

/*-----------------------------------------------------------------------*/
/**"EQ_FLOAT %s %s %s\n" */
void eq_float_translate(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movss", offset(code, 1), "%xmm0"));
  write_code_in_file(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
  write_code_in_file(file, translate("setnp", "%dl", ""));
  write_code_in_file(file, translate("movq", "%0", "%rax"));
  write_code_in_file(file, translate("movss", offset(code, 1), "%xmm0"));
  write_code_in_file(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
  write_code_in_file(file, translate("cmove", "%edx", "%rax"));
  write_code_in_file(file, translate("movb", "%al", offset(code, 3)));
}

/**"DIST_FLOAT %s %s %s\n" */
void dist_float_translate(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movss", offset(code, 1), "%xmm0"));
  write_code_in_file(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
  write_code_in_file(file, translate("setp", "%dl", ""));
  write_code_in_file(file, translate("movq", "$1", "%rax"));
  write_code_in_file(file, translate("movss", offset(code, 1), "%xmm0"));
  write_code_in_file(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
  write_code_in_file(file, translate("cmove", "%edx", "%rax"));
  write_code_in_file(file, translate("movb", "%al", offset(code, 3)));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_FLOAT %s %s %s\n" */
void greater_float_translate(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movss", offset(code, 1), "%xmm0"));
  write_code_in_file(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
  write_code_in_file(file, translate("seta", "%al", ""));
  write_code_in_file(file, translate("movb", "%al", offset(code, 3)));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_ EQ_FLOAT %s %s %s\n" */
void greater_eq_float_translate(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movss", offset(code, 1), "%xmm0"));
  write_code_in_file(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
  write_code_in_file(file, translate("setae", "%al", ""));
  write_code_in_file(file, translate("movb", "%al", offset(code, 3)));
}

/* Puts in the file the translation of the LESSER_EQ_FLOAT action */
void translate_lesser_or_equal_float(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movss", offset(code, 1), "%xmm0"));
  write_code_in_file(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
  write_code_in_file(file, translate("setbe", "%al", ""));
  write_code_in_file(file, translate("movb", "%al", offset(code, 3)));
}

/* Puts in the file the translation of the LESSER_FLOAT action */
void translate_lesser_float(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movss", offset(code, 1), "%xmm0"));
  write_code_in_file(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
  write_code_in_file(file, translate("setb", "%al", ""));
  write_code_in_file(file, translate("movb", "%al", offset(code, 3)));
}

/* Puts in the file the translation of the DIV_FLOAT action */
void translate_div_float(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movss", offset(code, 1) ,"%xmm0"));
  write_code_in_file(file, translate("divss", offset(code, 2), "%xmm0"));
  write_code_in_file(file, translate("movss", "%xmm0", offset(code, 3)));
}

/* Puts in the file the translation of the MULT_FLOAT action */
void translate_mult_float(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movss", offset(code, 1) ,"%xmm0"));
  write_code_in_file(file, translate("mulss", offset(code, 2), "%xmm0"));
  write_code_in_file(file, translate("movss", "%xmm0", offset(code, 3)));
}

/* Puts in the file the translation of the ADD_FLOAT action */
void translate_add_float(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movss", offset(code, 1) ,"%xmm0"));
  write_code_in_file(file, translate("addss", offset(code, 2), "%xmm0"));
  write_code_in_file(file, translate("movss", "%xmm0", offset(code, 3)));
}

/* Puts in the file the translation of the MINUS_FLOAT action */
void translate_minus_float(FILE *file, Code3D *code)
{
  write_code_in_file(file, translate("movss", offset(code, 1) ,"%xmm0"));
  write_code_in_file(file, translate("subss", offset(code, 2), "%xmm0"));
  write_code_in_file(file, translate("movss", "%xmm0", offset(code, 3)));
}

/* EXTERN INVOCATIONS OPERATIONS */

/* Puts in the file the translation of the EXTERNINVK action */
void translate_externinvk(FILE *file, Code3D *code)
{
  write_code_in_file(file, "\tmovl	$0, %eax\n");
  write_code_in_file(file, translate("call", get_label(code, 1), ""));
}

void translate_int_extern_param(FILE *file, Code3D *code)
{
  switch (get_int(code, 2))
  {
    case 1: write_code_in_file(file, translate("movl", offset(code, 1), "%edi")); break;
    case 2: write_code_in_file(file, translate("movl", offset(code, 1), "%esi")); break;
    case 3: write_code_in_file(file, translate("movl", offset(code, 1), "%edx")); break;
    case 4: write_code_in_file(file, translate("movl", offset(code, 1), "%ecx")); break;
    case 5: write_code_in_file(file, translate("movl", offset(code, 1), "%r8d")); break;
    case 6: write_code_in_file(file, translate("movl", offset(code, 1), "%r9d")); break;
  }
  if (get_int(code, 2) > 6)
  {
    write_code_in_file(file, translate("movl", offset(code, 1), "%eax"));
    write_code_in_file(file, translate("movl", "%eax", offset_num(extern_offset)));
    extern_offset = extern_offset + 8;
  }
  else
    extern_offset = 0;
}

void translate_float_extern_param(FILE *file, Code3D *code)
{
  switch (get_int(code, 2))
  {
    case 1: write_code_in_file(file, translate("movsd", offset(code, 1), "%xmm0")); break;
    case 2: write_code_in_file(file, translate("movsd", offset(code, 1), "%xmm1")); break;
    case 3: write_code_in_file(file, translate("movsd", offset(code, 1), "%xmm2")); break;
    case 4: write_code_in_file(file, translate("movsd", offset(code, 1), "%xmm3")); break;
    case 5: write_code_in_file(file, translate("movsd", offset(code, 1), "%xmm4")); break;
    case 6: write_code_in_file(file, translate("movsd", offset(code, 1), "%xmm5")); break;
    case 7: write_code_in_file(file, translate("movsd", offset(code, 1), "%xmm6")); break;
    case 8: write_code_in_file(file, translate("movsd", offset(code, 1), "%xmm7")); break;
  }
  if (get_int(code, 2) > 6)
  {
    write_code_in_file(file, translate("movq", offset(code, 1), "%rax"));
    write_code_in_file(file, translate("movq", "%rax", offset_num(extern_offset)));
    extern_offset = extern_offset + 8;
  }
  else
    extern_offset = 0;
}

void translate_bool_extern_param(FILE *file, Code3D *code)
{
  switch (get_int(code, 2))
  {
    case 1: write_code_in_file(file, translate("movl", offset(code, 1), "%edi")); break;
    case 2: write_code_in_file(file, translate("movl", offset(code, 1), "%esi")); break;
    case 3: write_code_in_file(file, translate("movl", offset(code, 1), "%edx")); break;
    case 4: write_code_in_file(file, translate("movl", offset(code, 1), "%ecx")); break;
    case 5: write_code_in_file(file, translate("movl", offset(code, 1), "%r8d")); break;
    case 6: write_code_in_file(file, translate("movl", offset(code, 1), "%r9d")); break;
  }
}

inline void write_neg_float(FILE *file)
{
  write_code_in_file(file, "\t.NEG_FLOAT:\n");
  write_code_in_file(file, "\t\t.long 2147483648\n");
}
