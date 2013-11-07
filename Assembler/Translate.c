#include "Translate.h"

int nameLabelCount = 0;

/*Create new Label*/
char* createNewLabel(char* msg) 
{
    char* aux;
    sprintf(aux, "%d", nameLabelCount);
    char *newLabel = concat(msg, aux);
    nameLabelCount++;
   	return newLabel;
}

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

void writeBlank(FILE* file)
{
    fprintf(file, "\n");
}

/* Returns the respective operation in assembly code */
char* translate(char* operation, char* code1, char* code2)
{
    char* backSlashN = "\n";
    char* blank = " ";
    char* tab = "\t";
    char* comma = ",";
    char* result = malloc(strlen(tab)+strlen(operation)+2*strlen(blank)+strlen(code1)+strlen(comma)+strlen(code2)+strlen(backSlashN));
    strcat(result, tab); 
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

/*-----------------------------------------------------------------------*/
/**Metodo para la obtencion del valor de una constante*/  
char* value(Code3D* code)
{
	char *result = (char*) malloc(sizeof(char));/* CHECK OUT THIS CASE BECAUSE sizeof(char) ONLY STORES MEMORY FOR ONLY ONE CHARACTER! */
	if (isInt(code, 1))/* IF THE NUMBER HAS MORE THAN ONE DIGIT (CHARACTER) IT WILL BROKE! */
        sprintf(result, "%d", getInt(code, 1));
	if (isFloat(code, 1))
        sprintf(result, "%f", getFloat(code, 1));
	if (isBool(code, 1))
        sprintf(result, "%d", getBool(code, 1));
	return concat("$", result);		
}

/**Metodo para la obtencion del offset de una variable*/
char* offset(Code3D* code, int param)
{
	char *result = (char*) malloc(sizeof(char));
	//result = getOffset(code, param);   NO EXISTE getOffset
	return concat (result, ", (%rbp)");
}


/*-----------------------------------------------------------------------*/
/**"LOAD_CONST %s %s\n" */
void load_Const_Translate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("movl", value(code), offset(code, 2)));
}

/* Puts in the file the translation of the GOTO_LABEL action */
void translateGotoLabel(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("jmp", getLabel(code,1), ""));
}

/* Puts in the file the translation of the GOTO_LABEL_CONDITION action */
void translateGotoLabelCondition(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("mov", offset(code,1), "%rax"));
	writeCodeInFile(file, translate("cmp", "$0", "%rax"));
	writeCodeInFile(file, translate("je", getLabel(code,2), ""));
}

/* Puts in the file the translation of the RETURN action */
void translateReturn(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("mov", "$0", "%rax"));
	writeCodeInFile(file, translate("leave","",""));
	writeCodeInFile(file, translate("ret","",""));
}

/* Puts in the file the translation of the RETURN_EXPR action */
void translateReturnExpression(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("mov", offset(code,1), "%rax"));
	writeCodeInFile(file, translate("leave","",""));
	writeCodeInFile(file, translate("ret","",""));
}

/* Puts in the file the translation of the MINUS_INT action */
void translateOr(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("mov", offset(code,1), "%rax"));
	writeCodeInFile(file, translate("or", offset(code,2), "%rax"));
	writeCodeInFile(file, translate("mov", "%rax", offset(code,3)));
}

/* Puts in the file the translation of the MINUS_INT action */
void translateAnd(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("mov", offset(code,1), "%rax"));
	writeCodeInFile(file, translate("and", offset(code,2), "%rax"));
	writeCodeInFile(file, translate("mov", "%rax", offset(code,3)));
}

/* Puts in the file the translation of the MINUS_INT action */
void translateNot(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("mov", offset(code,1), "%rax"));
	writeCodeInFile(file, translate("not", "%rax", ""));
	writeCodeInFile(file, translate("mov", "%rax", offset(code,2)));
}

/* Puts in the file the translation of the PRINT action */
void printOperation(FILE *file, Code3D *code)
{
    char* aux;
    sprintf(aux, "%d", getIntVal(getAttribute(code, 1)));
    writeCodeInFile(file, translate("pushq", "%rbp", ""));
    writeCodeInFile(file, translate("movl", concat(concat("$", aux), ", "), "%esi"));
    writeCodeInFile(file, translate("movl", concat(concat("$", ".INT"), ", "), "%edi"));
    writeCodeInFile(file, translate("call", "printf", ""));
    writeCodeInFile(file, translate("popq", "%rbp", ""));
    writeCodeInFile(file, translate("ret", "", ""));
}
            
/* Puts in the file the translation of the LABEL action */
void writeLabel(FILE *file, Code3D *code)
{
    writeCodeInFile(file, concat(getLabel(code,1), ":"));
}

/* Puts in the file the translation of the PARAM_ASSIGN action */
void translateParamAssign(FILE *file, Code3D *code)
{
    /* --------------------------------------- MUST BE IMPLEMENTED --------------------------------------- */
    /* --------------------------------------- MUST BE IMPLEMENTED --------------------------------------- */
    /* --------------------------------------- MUST BE IMPLEMENTED --------------------------------------- */
}

/* Puts in the file the translation of the LOAD_ARRAY action */
void translateLoadArray(FILE *file, Code3D *code)
{
    /* --------------------------------------- MUST BE IMPLEMENTED --------------------------------------- */
    /* --------------------------------------- MUST BE IMPLEMENTED --------------------------------------- */
    /* --------------------------------------- MUST BE IMPLEMENTED --------------------------------------- */
}

/* Puts in the file the translation of the GOTO_METHOD action */
/* "GOTO_METHOD %s\n" */
void goTo_Method (FILE* file, Code3D* code);
{
	writeCodeInFile(file, translate("call", getLabel(code,1), ""));
}



/********************************************************************************************/
/********************************* INT OPERATIONS TREATEMENT ********************************/
/********************************************************************************************/

/* Puts in the file the translation of the ASSIGNATION action */
void translateAssignationInt(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("mov", offset(code,1), "%rax"));
	writeCodeInFile(file, translate("mov", "%rax", offset(code,2)));
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
	writeCodeInFile(file, translate("movl", offset(code, 1), "%eax"));
	writeCodeInFile(file, translate("addl", offset(code, 2) ,"%eax"));
	writeCodeInFile(file, translate("movl", "%eax", offset(code, 3)));
}

/*-----------------------------------------------------------------------*/
/**"MULT_INT %s %s %s\n" */
void mult_Int_Translate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("movl", offset(code, 1), "%eax"));
	writeCodeInFile(file, translate("imull", offset(code, 2) ,"%eax"));
	writeCodeInFile(file, translate("movl", "%eax", offset(code, 3)));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_INT %s %s %s\n" */
void greater_IntTranslate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("movl", offset(code, 2), "%eax"));
	writeCodeInFile(file, translate("cmpl", offset(code, 1) ,"%eax"));
	writeCodeInFile(file, translate("setg", "%al", ""));
	writeCodeInFile(file, translate("movzbl", "%al", "%eax"));
	writeCodeInFile(file, translate("movl", "%eax", offset(code, 3)));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_ EQ_INT %s %s %s\n" */
void greater_Eq_IntTranslate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("movl", offset(code, 2), "%eax"));
	writeCodeInFile(file, translate("cmpl", offset(code, 1) ,"%eax"));
	writeCodeInFile(file, translate("setge", "%al", ""));
	writeCodeInFile(file, translate("movzbl", "%al", "%eax"));
	writeCodeInFile(file, translate("movl", "%eax", offset(code, 3)));
}

/* Puts in the file the translation of the MINUS_INT action */
void translateMinusInt(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("mov", offset(code,1), "%rax"));
	writeCodeInFile(file, translate("mov", offset(code,2), "%r10"));
	writeCodeInFile(file, translate("sub", "%rax", "%r10"));
	writeCodeInFile(file, translate("mov", "%r10", offset(code,3)));
}

/* Puts in the file the translation of the MOD_INT action */
void translateModInt(FILE* file, Code3D* code)
{
	/* it divides"rdx:rax" by "divisor". Stores quotient in rax and remainder in rdx */
	writeCodeInFile(file, translate("mov", "$0", "%rdx"));
	writeCodeInFile(file, translate("mov", "$0", "%rax"));
	writeCodeInFile(file, translate("mov", offset(code,1) ,"%rax"));
	writeCodeInFile(file, translate("idiv", offset(code,2), ""));
	writeCodeInFile(file, translate("mov", "%rdx", offset(code,3)));
}

/* Puts in the file the translation of the DIV_INT action */
void translateDivInt(FILE* file, Code3D* code)
{
	/* it divides"rdx:rax" by "divisor". Stores quotient in rax and remainder in rdx */
	writeCodeInFile(file, translate("mov", "$0", "%rdx"));
	writeCodeInFile(file, translate("mov", "$0", "%rax"));
	writeCodeInFile(file, translate("mov", offset(code,1) ,"%rax"));
	writeCodeInFile(file, translate("idiv", offset(code,2), ""));
	writeCodeInFile(file, translate("mov", "%rax", offset(code,3)));
}

/* Puts in the file the translation of the LESSER_INT action */
void translateLesserInt(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("mov", offset(code,2), "%rax"));
	writeCodeInFile(file, translate("cmp", offset(code,1) ,"%rax"));
	writeCodeInFile(file, translate("cmovl", "%rax", offset(code,3)));
}

/* Puts in the file the translation of the LESSER_EQ_INT action */
void translateLesserOrEqualInt(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("mov", offset(code,2), "%rax"));
	writeCodeInFile(file, translate("cmp", offset(code,1) ,"%rax"));
	writeCodeInFile(file, translate("cmovle", "%rax", offset(code,3)));
}

/* Puts in the file the translation of the EQ_INT action */
void translateEqualInt(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("mov", offset(code,2), "%rax"));
	writeCodeInFile(file, translate("cmp", offset(code,1) ,"%rax"));
	writeCodeInFile(file, translate("cmove", "%rax", offset(code,3)));
}

/* Puts in the file the translation of the DIST_INT action */
void translateDistinctInt(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("mov", offset(code,2), "%rax"));
	writeCodeInFile(file, translate("cmp", offset(code,1) ,"%rax"));
	writeCodeInFile(file, translate("cmovne", "%rax", offset(code,3)));
}

/********************************************************************************************/
/********************************* FLOAT OPERATIONS TREATEMENT ******************************/
/********************************************************************************************/

/*-----------------------------------------------------------------------*/
/**"ASSIGNATION_FLOAT %s %s\n" */
void assignation_FloatTranslate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("movss", offset(code,1), "%rax"));
	writeCodeInFile(file, translate("movss", "%rax", offset(code,2)));
}

/*-----------------------------------------------------------------------*/
/**"NEG_FLOAT %s %s\n" */
void neg_Float_Translate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("xorps", "%xmm0", "%xmm0"));
	writeCodeInFile(file, translate("ucomiss", offset(code,1), "%xmm0"));
	writeCodeInFile(file, translate("setp", "%dl", ""));
	writeCodeInFile(file, translate("movl", "$1", "%eax"));
	writeCodeInFile(file, translate("xorps", "%xmm0", "%xmm0"));
	writeCodeInFile(file, translate("ucomiss", offset(code,1), "%xmm0"));
	writeCodeInFile(file, translate("cmove", "%edx", "%eax"));
	writeCodeInFile(file, translate("movb", "%al", offset(code,2)));
}

/*-----------------------------------------------------------------------*/
/**"EQ_FLOAT %s %s %s\n" */
void eq_FloatTranslate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("movss", offset(code, 1), "%xmm0"));
	writeCodeInFile(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
	writeCodeInFile(file, translate("setnp", "%dl", ""));
	writeCodeInFile(file, translate("movl", "%0", "%eax"));
	writeCodeInFile(file, translate("movss", offset(code, 1), "%xmm0"));
	writeCodeInFile(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
	writeCodeInFile(file, translate("cmove", "%edx", "%eax"));
	writeCodeInFile(file, translate("movb", "%al", offset(code, 3)));
}


/**"DIST_FLOAT %s %s %s\n" */
void dist_FloatTranslate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("movss", offset(code, 1), "%xmm0"));
	writeCodeInFile(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
	writeCodeInFile(file, translate("setp", "%dl", ""));
	writeCodeInFile(file, translate("movl", "%1", "%eax"));
	writeCodeInFile(file, translate("movss", offset(code, 1), "%xmm0"));
	writeCodeInFile(file, translate("ucomiss", offset(code, 2) ,"%xmm0"));
	writeCodeInFile(file, translate("cmove", "%edx", "%eax"));
	writeCodeInFile(file, translate("movb", "%al", offset(code, 3)));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_FLOAT %s %s %s\n" */
void greater_FloatTranslate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("movss", offset(code, 2), "%xmm0"));
	writeCodeInFile(file, translate("ucomiss", offset(code, 1) ,"%xmm0"));
	writeCodeInFile(file, translate("seta", "%al", ""));
	writeCodeInFile(file, translate("movb", "%al", offset(code, 3)));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_ EQ_FLOAT %s %s %s\n" */
void greater_Eq_FloatTranslate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("movss", offset(code, 2), "%xmm0"));
	writeCodeInFile(file, translate("ucomiss", offset(code, 1) ,"%xmm0"));
	writeCodeInFile(file, translate("setae", "%al", ""));
	writeCodeInFile(file, translate("movb", "%al", offset(code, 3)));
}

/* Puts in the file the translation of the LESSER_EQ_FLOAT action */
void translateLesserOrEqualFloat(FILE *file, Code3D* code)
{
	writeCodeInFile(file, translate("movss", offset(code, 2), "%xmm0"));
	writeCodeInFile(file, translate("ucomiss", offset(code, 1) ,"%xmm0"));
	writeCodeInFile(file, translate("setbe", "%al", ""));
	writeCodeInFile(file, translate("movb", "%al", offset(code, 3)));
}

/* Puts in the file the translation of the LESSER_FLOAT action */
void translateLesserFloat(FILE *file, Code3D* code)
{
	writeCodeInFile(file, translate("movss", offset(code, 2), "%xmm0"));
	writeCodeInFile(file, translate("ucomiss", offset(code, 1) ,"%xmm0"));
	writeCodeInFile(file, translate("setb", "%al", ""));
	writeCodeInFile(file, translate("movb", "%al", offset(code, 3)));
}

/* Puts in the file the translation of the DIV_FLOAT action */
void translateDivFloat(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("movss", offset(code,2) ,"%xmm0"));
	writeCodeInFile(file, translate("divss", offset(code,1), "%xmm0"));
	writeCodeInFile(file, translate("movss", "%xmm0", offset(code,3)));
}

/* Puts in the file the translation of the MULT_FLOAT action */
void translateMultFloat(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("movss", offset(code,2) ,"%xmm0"));
	writeCodeInFile(file, translate("mulss", offset(code,1), "%xmm0"));
	writeCodeInFile(file, translate("movss", "%xmm0", offset(code,3)));
}

/* Puts in the file the translation of the ADD_FLOAT action */
void translateAddFloat(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("movss", offset(code,2) ,"%xmm0"));
	writeCodeInFile(file, translate("addss", offset(code,1), "%xmm0"));
	writeCodeInFile(file, translate("movss", "%xmm0", offset(code,3)));
}

/* Puts in the file the translation of the MINUS_FLOAT action */
void translateMinusFloat(FILE* file, Code3D* code)
{
	writeCodeInFile(file, translate("movss", offset(code,2) ,"%xmm0"));
	writeCodeInFile(file, translate("subss", offset(code,1), "%xmm0"));
	writeCodeInFile(file, translate("movss", "%xmm0", offset(code,3)));
}

