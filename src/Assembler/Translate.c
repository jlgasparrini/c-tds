#include "Translate.h";

int nameLabelCount = 0;
int auxParam = 1;
int print_count = 0;
int extern_offset = 0;
bool any_goto_method = false;

/*-----------------------------------------------------------------------*/
/**Metodo para la obtencion del valor de una constante*/  
char* value(Code3D* code, int i)
{
  char *result = (char*) malloc(sizeof(char));/* CHECK OUT THIS CASE BECAUSE sizeof(char) ONLY STORES MEMORY FOR ONLY ONE CHARACTER! */
  if (isInt(code, i))/* IF THE NUMBER HAS MORE THAN ONE DIGIT (CHARACTER) IT WILL BROKE! */
    sprintf(result, "%d", getInt(code, i));
  if (isFloat(code, i))
    sprintf(result, "%f", getFloat(code, i));
  if (isBool(code, i))
    sprintf(result, "%d", getBool(code, i));
  return concat("$", result);		
}

/*Create new Label*/
char* createNewLabel(char* msg) 
{
  char* aux;
  sprintf(aux, "%d", nameLabelCount);
  char *newLabel = concat(msg, aux);
  nameLabelCount++; return newLabel; }

  //Retorna la contatenacion de dos cadenas.
char* concat(char *s1, char *s2)
{
  char *result = malloc(strlen(s1)+strlen(s2)+1);
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}

//Este podria tomar por separado las operaciones a meter en el file.
void writeCodeInFile(FILE* file, char* code)
{
  fprintf(file,"%s", code);
}

/* Returns the respective operation in assembly code */
char* translate(char* operation, char* code1, char* code2)
{
  char* backSlashN = "\n";
  char* blank = " ";
  char* tab = "\t";
  char* comma = ",";
  char* result = (char*) malloc(strlen(tab)+strlen(operation)+2*strlen(blank)+strlen(code1)+strlen(comma)+strlen(code2)+strlen(backSlashN));
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
  strcat(result, backSlashN);
  return result;
}

/**Metodo para la obtencion del offset de una variable*/
char* offset(Code3D* code, int param)
{
  char *result = (char*) malloc(sizeof(char));/* CHECK OUT THIS CASE BECAUSE sizeof(char) ONLY STORES MEMORY FOR ONLY ONE CHARACTER! */
  result =intToString(getOffsetVal(getAttribute(code, param)));
  return concat (result, "(%rbp)");
}

/**Metodo para la obtencion del offset de un numero dado. Utilizado para las invocaciones externas.*/
char* offset_num(int offset)
{
  char *result = (char*) malloc(sizeof(char));/* CHECK OUT THIS CASE BECAUSE sizeof(char) ONLY STORES MEMORY FOR ONLY ONE CHARACTER! */
  result =intToString(offset);
  if (offset == 0)
    return "(%rsp)";
  else
    return concat (result, "(%rsp)");
}

/**Metodo para la obtencion del offset de un arreglo*/
char* offsetArray(Code3D* code, int param, char* reg)
{
  int offset = getOffsetArray(getAttribute(code, param));
  return concat(concat(concat(intToString(offset), "(%rbp,"), reg), ",4)");
}

/*-----------------------------------------------------------------------*/
/**"LOAD_CONST %s %s\n" */
void load_Const_Translate(FILE* file, Code3D* code)
{
  if (!isFloat(code, 1))
    writeCodeInFile(file, translate("movl", value(code, 1), offset(code, 2)));
  else
  {
    fValue.real = getFloat(code, 1);
    fprintf(file, "\tmov $0x");
    fprintf(file, "%x",fValue.entero);
    fprintf(file, ", %rax\n");
    writeCodeInFile(file, translate("movl", "%eax", offset(code, 2)));
  }
}

/* Puts in the file the translation of the GOTO_LABEL action */
void translateGotoLabel(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("jmp", getLabel(code,1), ""));
}

/* Puts in the file the translation of the GOTO_LABEL_CONDITION action */
void translateGotoLabelCondition(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("cmp", "$0", offset(code, 1)));
  writeCodeInFile(file, translate("jz", getLabel(code,2), ""));
}

/* Puts in the file the translation of the RETURN action */
void translateReturn(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movl", "$0", "%eax"));
  writeCodeInFile(file, translate("leave","",""));
  writeCodeInFile(file, translate("ret","",""));
}

/* Puts in the file the translation of the RETURN_EXPR action */
void translateReturnExpression(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movl", offset(code,1), "%eax"));
  writeCodeInFile(file, translate("leave","",""));
  writeCodeInFile(file, translate("ret","",""));
}

/* Puts in the file the translation of the MINUS_INT action */
void translateOr(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movl", offset(code,1), "%eax"));
  writeCodeInFile(file, translate("or", offset(code,2), "%eax"));
  writeCodeInFile(file, translate("movl", "%eax", offset(code,3)));
}

/* Puts in the file the translation of the MINUS_INT action */
void translateAnd(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movl", offset(code,1), "%eax"));
  writeCodeInFile(file, translate("and", offset(code,2), "%eax"));
  writeCodeInFile(file, translate("movl", "%eax", offset(code,3)));
}

/* Puts in the file the translation of the MINUS_INT action */
void translateNot(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("cmpl", "$1", offset(code,1)));
  writeCodeInFile(file, translate("setne", "%al", ""));
  writeCodeInFile(file, translate("movzbl", "%al", "%eax"));
  writeCodeInFile(file, translate("movl", "%eax", offset(code, 2)));
}

/* Puts in the file the translation of the PRINT action */
void printOperation(FILE *file, Code3D *code)
{
  if (getAttributeType(getAttribute(code, 1)) == Int)
  {
    writeCodeInFile(file, translate("movq", offset(code, 1), "%rsi"));
    writeCodeInFile(file, translate("movq", concat("$", ".INT"), "%rdi"));
  }
  if (getAttributeType(getAttribute(code, 1)) == Float)
  {
    writeCodeInFile(file, translate("movss", offset(code, 1), "%xmm0"));
    writeCodeInFile(file, translate("cvtps2pd", "%xmm0", "%xmm0"));
    writeCodeInFile(file, translate("movq", concat("$", ".FLOAT"), "%rdi"));
  }
  if (getAttributeType(getAttribute(code, 1)) == Bool)
  {
    int count = intToString(print_count);
    writeCodeInFile(file, translate("cmp", "$0", offset(code, 1)));
    writeCodeInFile(file, translate("jz", concat("label_bool_condition_of_print", count), ""));
    writeCodeInFile(file, translate("movq", concat("$", ".BOOL_TRUE"), "%rdi"));
    writeCodeInFile(file, translate("jmp", concat("end_label_bool_condition_of_print", count), ""));
    writeCodeInFile(file, concat(concat("label_bool_condition_of_print", count), ":\n"));
    writeCodeInFile(file, translate("movq", concat("$", ".BOOL_FALSE"), "%rdi"));
    writeCodeInFile(file, concat(concat("end_label_bool_condition_of_print", count), ":\n"));
    print_count = print_count + 1;
  }
  writeCodeInFile(file, translate("movq", "$0", "%rax"));
  writeCodeInFile(file, translate("call", "printf", ""));
}

/* Puts in the file the translation of the LABEL action */
void writeLabel(FILE *file, ListMLabel *labelList, Code3D *code)
{
  if (strcmp(get_Label(labelList, getLabel(code, 1)), "NULL") == 0)
  {
    writeCodeInFile(file, concat(getLabel(code,1), ":\n"));
  }
  else
  {
    writeCodeInFile(file, concat(getLabel(code,1), ":\n"));
    writeCodeInFile(file, translate("pushq", "%rbp", ""));
    writeCodeInFile(file, translate("movq", "%rsp", "%rbp"));
    char *result = (char*) malloc(sizeof(char));
    sprintf(result, "%d", getInt(code, 2) - 4);
    writeCodeInFile(file, translate("addq", concat("$", result),  "%rsp"));
  }
}

/* Puts in the file the translation of the LOAD_ARRAY action */
void translateLoadArray(FILE *file, Code3D *code)
{
  /* parameter 1 of 3d code is the position of the array
   * parameter 2 is the array from which the number will be getted from.
   * parameter 3 is the resulting attribute. 
   */
  writeCodeInFile(file, translate("movq", offset(code,1), "%rax"));

  if (getAttributeType(getAttribute(code, 2)) == Float)
  {
    writeCodeInFile(file, translate("movss", offsetArray(code,2,"%rax"), "%xmm0"));
    writeCodeInFile(file, translate("movss", "%xmm0", offset(code,3)));
  }
  else
  {
    writeCodeInFile(file, translate("movq", offsetArray(code,2,"%rax"), "%rdx"));
    writeCodeInFile(file, translate("movq", "%rdx", offset(code,3)));
  }
}

/* Puts in the file the translation of the GOTO_METHOD action */
/* "GOTO_METHOD %s\n" */
void goTo_Method (FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("call", getLabel(code,1), ""));
  /*   DEBO   PREGUNTAR   SI   EL TIPO DE RETORNO DEL METODO ESif DISSTINTO DE VOID!    */
    any_goto_method = true;
}

/********************************************************************************************/
/********************************* INT OPERATIONS TREATEMENT ********************************/
/********************************************************************************************/

/* Puts in the file the translation of the ASSIGNATION_INT action */
void translateAssignationInt(FILE* file, Code3D* code)
{
  if (!any_goto_method)
  {
    writeCodeInFile(file, translate("movl", offset(code,1), "%eax"));
    any_goto_method = false;
  }
  writeCodeInFile(file, translate("movl", "%eax", offset(code,2)));
}

/* Puts in the file the translation of the PARAM_ASSIGN_INT action */
void translateParamAssignInt(FILE *file, Code3D *code)
{
  if (getInt(code, 3) != NULL)
    writeCodeInFile(file, translate("subq", concat("$", intToString(getInt(code, 3)*4)), "%rsp"));
  writeCodeInFile(file, translate("movq", offset(code, 1), "%rax"));
  writeCodeInFile(file, translate("movq", "%rax", concat(intToString(auxParam*4), "(%rsp)")));
  auxParam++;
}

/*-----------------------------------------------------------------------*/
/**"NEG_INT %s %s\n" */
void neg_Int_Translate(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movl", offset(code, 1), "%eax"));
  writeCodeInFile(file, translate("negl", "%eax", ""));
  writeCodeInFile(file, translate("movl", "%eax", offset(code, 2)));
}

/*-----------------------------------------------------------------------*/
/**"ADD_INT %s %s %s\n" */
void add_Int_Translate(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movq", offset(code, 1), "%rax"));
  writeCodeInFile(file, translate("add", offset(code, 2) ,"%rax"));
  writeCodeInFile(file, translate("movq", "%rax", offset(code, 3)));
}

/*-----------------------------------------------------------------------*/
/**"MULT_INT %s %s %s\n" */
void mult_Int_Translate(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movq", offset(code, 1), "%rax"));
  writeCodeInFile(file, translate("imulq", offset(code, 2) ,"%rax"));
  writeCodeInFile(file, translate("movq", "%rax", offset(code, 3)));
}

/* Puts in the file the translation of the MINUS_INT action */
void translateMinusInt(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movq", offset(code,2), "%rax"));
  writeCodeInFile(file, translate("movq", offset(code,1), "%r10"));
  writeCodeInFile(file, translate("subq", "%rax", "%r10"));
  writeCodeInFile(file, translate("movq", "%r10", offset(code,3)));
}

/* Puts in the file the translation of the MOD_INT action */
void translateModInt(FILE* file, Code3D* code)
{
  /* it divides"rdx:rax" by "divisor". Stores quotient in rax and remainder in rdx */
  writeCodeInFile(file, translate("movq", "$0", "%rdx"));
  writeCodeInFile(file, translate("movq", "$0", "%rax"));
  writeCodeInFile(file, translate("movq", offset(code,1) ,"%rax"));
  writeCodeInFile(file, translate("idivl", offset(code,2), ""));
  writeCodeInFile(file, translate("movq", "%rdx", offset(code,3)));
}

/* Puts in the file the translation of the DIV_INT action */
void translateDivInt(FILE* file, Code3D* code)
{
  /* it divides"rdx:rax" by "divisor". Stores quotient in rax and remainder in rdx */
  writeCodeInFile(file, translate("movq", "$0", "%rdx"));
  writeCodeInFile(file, translate("movq", offset(code,1) ,"%rax"));
  writeCodeInFile(file, translate("idivl", offset(code,2), ""));
  writeCodeInFile(file, translate("movq", "%rax", offset(code,3)));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_INT %s %s %s\n" */
void greater_IntTranslate(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movl", offset(code,1), "%eax"));
  writeCodeInFile(file, translate("cmp", offset(code,2), "%eax"));
  writeCodeInFile(file, translate("setg", "%al", ""));
  writeCodeInFile(file, translate("movzbl", "%al", "%eax"));
  writeCodeInFile(file, translate("movl", "%eax", offset(code,3))); 
}

/*-----------------------------------------------------------------------*/
/**"GREATER_ EQ_INT %s %s %s\n" */
void greater_Eq_IntTranslate(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movl", offset(code,1), "%eax"));
  writeCodeInFile(file, translate("cmp", offset(code,2), "%eax"));
  writeCodeInFile(file, translate("setge", "%al", ""));
  writeCodeInFile(file, translate("movzbl", "%al", "%eax"));
  writeCodeInFile(file, translate("movl", "%eax", offset(code,3))); 
}

/* Puts in the file the translation of the LESSER_INT action */
void translateLesserInt(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movl", offset(code,1), "%eax"));
  writeCodeInFile(file, translate("cmp", offset(code,2), "%eax"));
  writeCodeInFile(file, translate("setl", "%al", ""));
  writeCodeInFile(file, translate("movzbl", "%al", "%eax"));
  writeCodeInFile(file, translate("movl", "%eax", offset(code,3))); 
}

/* Puts in the file the translation of the LESSER_EQ_INT action */
void translateLesserOrEqualInt(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movl", offset(code,1), "%eax"));
  writeCodeInFile(file, translate("cmp", offset(code,2), "%eax"));
  writeCodeInFile(file, translate("setle", "%al", ""));
  writeCodeInFile(file, translate("movzbl", "%al", "%eax"));
  writeCodeInFile(file, translate("movl", "%eax", offset(code,3))); 
}

/* Puts in the file the translation of the EQ_INT action */
void translateEqualInt(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movl", offset(code,1), "%eax"));
  writeCodeInFile(file, translate("cmp", offset(code,2) ,"%eax"));
  writeCodeInFile(file, translate("sete", "%al", ""));
  writeCodeInFile(file, translate("movzbl", "%al", "%eax"));
  writeCodeInFile(file, translate("movl", "%eax", offset(code,3))); 
}

/* Puts in the file the translation of the DIST_INT action */
void translateDistinctInt(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movl", offset(code,1), "%eax"));
  writeCodeInFile(file, translate("cmp", offset(code,2) ,"%eax"));
  writeCodeInFile(file, translate("setne", "%al", ""));
  writeCodeInFile(file, translate("movzbl", "%al", "%eax"));
  writeCodeInFile(file, translate("movl", "%eax", offset(code,3))); 
}

/********************************************************************************************/
/********************************* FLOAT OPERATIONS TREATEMENT ******************************/
/********************************************************************************************/

/*-----------------------------------------------------------------------*/
/**"ASSIGNATION_FLOAT %s %s\n" */
void assignation_FloatTranslate(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movss", offset(code,1), "%xmm0"));
  writeCodeInFile(file, translate("movss", "%xmm0", offset(code,2)));
}

/* Puts in the file the translation of the PARAM_ASSIGN_FLOAT action */
void translateParamAssignFloat(FILE *file, Code3D *code)
{
  if (getInt(code, 3) != NULL)
    writeCodeInFile(file, translate("subq", concat("$", intToString(getInt(code, 3)*4)), "%rsp"));
  writeCodeInFile(file, translate("movss", offset(code, 1), "%xmm0"));
  writeCodeInFile(file, translate("movq", "%rax", concat(intToString(auxParam*4), "(%rsp)")));
}

/**"NEG_FLOAT %s %s\n" */
void neg_Float_Translate(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movss", offset(code, 1), "%xmm1"));
  writeCodeInFile(file, translate("movss", ".NEG_FLOAT(%rip)", "%xmm0"));
  writeCodeInFile(file, translate("xorps", "%xmm1", "%xmm0"));
  writeCodeInFile(file, translate("movss", "%xmm0", offset(code, 2)));
}

/*-----------------------------------------------------------------------*/
/**"EQ_FLOAT %s %s %s\n" */
void eq_FloatTranslate(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movss", offset(code, 1), "%xmm0"));
  writeCodeInFile(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
  writeCodeInFile(file, translate("setnp", "%dl", ""));
  writeCodeInFile(file, translate("movq", "%0", "%rax"));
  writeCodeInFile(file, translate("movss", offset(code, 1), "%xmm0"));
  writeCodeInFile(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
  writeCodeInFile(file, translate("cmove", "%edx", "%rax"));
  writeCodeInFile(file, translate("movb", "%al", offset(code, 3)));
}

/**"DIST_FLOAT %s %s %s\n" */
void dist_FloatTranslate(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movss", offset(code, 1), "%xmm0"));
  writeCodeInFile(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
  writeCodeInFile(file, translate("setp", "%dl", ""));
  writeCodeInFile(file, translate("movq", "$1", "%rax"));
  writeCodeInFile(file, translate("movss", offset(code, 1), "%xmm0"));
  writeCodeInFile(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
  writeCodeInFile(file, translate("cmove", "%edx", "%rax"));
  writeCodeInFile(file, translate("movb", "%al", offset(code, 3)));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_FLOAT %s %s %s\n" */
void greater_FloatTranslate(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movss", offset(code, 1), "%xmm0"));
  writeCodeInFile(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
  writeCodeInFile(file, translate("seta", "%al", ""));
  writeCodeInFile(file, translate("movb", "%al", offset(code, 3)));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_ EQ_FLOAT %s %s %s\n" */
void greater_Eq_FloatTranslate(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movss", offset(code, 1), "%xmm0"));
  writeCodeInFile(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
  writeCodeInFile(file, translate("setae", "%al", ""));
  writeCodeInFile(file, translate("movb", "%al", offset(code, 3)));
}

/* Puts in the file the translation of the LESSER_EQ_FLOAT action */
void translateLesserOrEqualFloat(FILE *file, Code3D* code)
{
  writeCodeInFile(file, translate("movss", offset(code, 1), "%xmm0"));
  writeCodeInFile(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
  writeCodeInFile(file, translate("setbe", "%al", ""));
  writeCodeInFile(file, translate("movb", "%al", offset(code, 3)));
}

/* Puts in the file the translation of the LESSER_FLOAT action */
void translateLesserFloat(FILE *file, Code3D* code)
{
  writeCodeInFile(file, translate("movss", offset(code, 1), "%xmm0"));
  writeCodeInFile(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
  writeCodeInFile(file, translate("setb", "%al", ""));
  writeCodeInFile(file, translate("movb", "%al", offset(code, 3)));
}

/* Puts in the file the translation of the DIV_FLOAT action */
void translateDivFloat(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movss", offset(code,1) ,"%xmm0"));
  writeCodeInFile(file, translate("divss", offset(code,2), "%xmm0"));
  writeCodeInFile(file, translate("movss", "%xmm0", offset(code,3)));
}

/* Puts in the file the translation of the MULT_FLOAT action */
void translateMultFloat(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movss", offset(code,1) ,"%xmm0"));
  writeCodeInFile(file, translate("mulss", offset(code,2), "%xmm0"));
  writeCodeInFile(file, translate("movss", "%xmm0", offset(code,3)));
}

/* Puts in the file the translation of the ADD_FLOAT action */
void translateAddFloat(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movss", offset(code,1) ,"%xmm0"));
  writeCodeInFile(file, translate("addss", offset(code,2), "%xmm0"));
  writeCodeInFile(file, translate("movss", "%xmm0", offset(code,3)));
}

/* Puts in the file the translation of the MINUS_FLOAT action */
void translateMinusFloat(FILE* file, Code3D* code)
{
  writeCodeInFile(file, translate("movss", offset(code,1) ,"%xmm0"));
  writeCodeInFile(file, translate("subss", offset(code,2), "%xmm0"));
  writeCodeInFile(file, translate("movss", "%xmm0", offset(code,3)));
}

/* Puts in the file the translation of the EXTERNINVK action */
void translateExternInvk(FILE* file, Code3D* code)
{
  writeCodeInFile(file, "\tmovl	$0, %eax\n");
  writeCodeInFile(file, translate("call", getLabel(code, 1), ""));
}

void translateIntExternParam(FILE *file, Code3D *code)
{
  switch (getInt(code, 2))
  {
    case 1: writeCodeInFile(file, translate("movl", offset(code, 1), "%edi"));
            break;
    case 2: writeCodeInFile(file, translate("movl", offset(code, 1), "%esi"));
            break;
    case 3: writeCodeInFile(file, translate("movl", offset(code, 1), "%edx"));
            break;
    case 4: writeCodeInFile(file, translate("movl", offset(code, 1), "%ecx"));
            break;
    case 5: writeCodeInFile(file, translate("movl", offset(code, 1), "%r8d"));
            break;
    case 6: writeCodeInFile(file, translate("movl", offset(code, 1), "%r9d"));
            break;
  }
  if (getInt(code, 2) > 6)
  {
    writeCodeInFile(file, translate("movl", offset(code, 1), "%eax"));
    writeCodeInFile(file, translate("movl", "%eax", offset_num(extern_offset)));
    extern_offset = extern_offset + 8;
  }
  else
    extern_offset = 0;
}

void translateFloatExternParam(FILE *file, Code3D *code)
{
  switch (getInt(code, 2))
  {
    case 1: writeCodeInFile(file, translate("movsd", offset(code, 1), "%xmm0"));
            break;
    case 2: writeCodeInFile(file, translate("movsd", offset(code, 1), "%xmm1"));
            break;
    case 3: writeCodeInFile(file, translate("movsd", offset(code, 1), "%xmm2"));
            break;
    case 4: writeCodeInFile(file, translate("movsd", offset(code, 1), "%xmm3"));
            break;
    case 5: writeCodeInFile(file, translate("movsd", offset(code, 1), "%xmm4"));
            break;
    case 6: writeCodeInFile(file, translate("movsd", offset(code, 1), "%xmm5"));
            break;
    case 7: writeCodeInFile(file, translate("movsd", offset(code, 1), "%xmm6"));
            break;
    case 8: writeCodeInFile(file, translate("movsd", offset(code, 1), "%xmm7"));
            break;
  }
  if (getInt(code, 2) > 6)
  {
    writeCodeInFile(file, translate("movq", offset(code, 1), "%rax"));
    writeCodeInFile(file, translate("movq", "%rax", offset_num(extern_offset)));
    extern_offset = extern_offset + 8;
  }
  else
    extern_offset = 0;
}

void translateBoolExternParam(FILE *file, Code3D *code)
{
  switch (getInt(code, 2))
  {
    case 1: writeCodeInFile(file, translate("movl", offset(code, 1), "%edi"));
            break;
    case 2: writeCodeInFile(file, translate("movl", offset(code, 1), "%esi"));
            break;
    case 3: writeCodeInFile(file, translate("movl", offset(code, 1), "%edx"));
            break;
    case 4: writeCodeInFile(file, translate("movl", offset(code, 1), "%ecx"));
            break;
    case 5: writeCodeInFile(file, translate("movl", offset(code, 1), "%r8d"));
            break;
    case 6: writeCodeInFile(file, translate("movl", offset(code, 1), "%r9d"));
            break;
  }
}

void writeNegFloat(FILE* file)
{
  writeCodeInFile(file, "\t.NEG_FLOAT:\n");
  writeCodeInFile(file, "\t\t.long 2147483648\n");
}