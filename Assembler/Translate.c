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
void writeCodeInFile(FILE* file, char* operation, char* code1, char* code2)
{
    char* backSlashN = strdup("\n");
    char* blank = strdup(" ");
    char *result = malloc(strlen(operation)+strlen(code1)+strlen(code2)+4);
    strcpy(result, operation);
    strcat(result, blank);
    strcat(result, code1);
    strcat(result, blank);
    strcat(result, code2);
    strcat(result, backSlashN);
    fprintf(file,"%s", result);
}

void writeBlank(FILE* file)
{
    fprintf(file, "\n");
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
	writeCodeInFile(file, "\tmovl", value(code), offset(code, 2));
}

/* Puts in the file the translation of the GOTO_LABEL action */
void translateGotoLabel(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tjmp", getLabel(code,1), "");
}

/* Puts in the file the translation of the GOTO_LABEL_CONDITION action */
void translateGotoLabelCondition(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmov", offset(code,1), "%rax");
	writeCodeInFile(file, "\tcmp", "$0", "%rax");
	writeCodeInFile(file, "\tje", getLabel(code,2), "");
}

/* Puts in the file the translation of the ASSIGNATION action */
void translateAssignation(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmov", offset(code,1), "%rax");
	writeCodeInFile(file, "\tmov", "%rax", offset(code,2));
}

/* Puts in the file the translation of the RETURN action */
void translateReturn(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmov", "$0", "%rax");
	writeCodeInFile(file, "\tleave", "", "");
	writeCodeInFile(file, "\tret", "", "");
}

/* Puts in the file the translation of the RETURN_EXPR action */
void translateReturnExpression(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmov", offset(code,1), "%rax");
	writeCodeInFile(file, "\tleave", "", "");
	writeCodeInFile(file, "\tret", "", "");
}

/* Puts in the file the translation of the MINUS_INT action */
void translateOr(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmov", offset(code,1), "%rax");
	writeCodeInFile(file, "\tor", offset(code,2), "%rax");
	writeCodeInFile(file, "\tmov", "%rax", offset(code,3));
}

/* Puts in the file the translation of the MINUS_INT action */
void translateAnd(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmov", offset(code,1), "%rax");
	writeCodeInFile(file, "\tand", offset(code,2), "%rax");
	writeCodeInFile(file, "\tmov", "%rax", offset(code,3));
}

/* Puts in the file the translation of the MINUS_INT action */
void translateNot(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmov", offset(code,1), "%rax");
	writeCodeInFile(file, "\tnot", "%rax", "");
	writeCodeInFile(file, "\tmov", "%rax", offset(code,2));
}

/* Puts in the file the translation of the PRINT action */
void printOperation(FILE *file, Code3D *code)
{
    char* aux;
    sprintf(aux, "%d", getIntVal(getAttribute(code, 1)));
    writeCodeInFile(file, "\tpushq", "%rbp", "");
    writeCodeInFile(file, "\tmovl", concat(concat("$", aux), ", "), "%esi");
    writeCodeInFile(file, "\tmovl", concat(concat("$", ".INT"), ", "), "%edi");
    writeCodeInFile(file, "\tcall", "printf", "");
    writeCodeInFile(file, "\tpopq", "%rbp", "");
    writeCodeInFile(file, "\tret", "", "");
}
            
/* Puts in the file the translation of the LABEL action */
void writeLabel(FILE *file, Code3D *code)
{
    writeCodeInFile(file, concat(getLabel(code, 1), ":"), "", "");
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
void translateGotoMethod(FILE *file, Code3D *code)
{
    /* --------------------------------------- MUST BE IMPLEMENTED --------------------------------------- */
    /* --------------------------------------- MUST BE IMPLEMENTED --------------------------------------- */
    /* --------------------------------------- MUST BE IMPLEMENTED --------------------------------------- */
}



/********************************************************************************************/
/********************************* INT OPERATIONS TREATEMENT ********************************/
/********************************************************************************************/

/*-----------------------------------------------------------------------*/
/**"NEG_INT %s %s\n" */
void neg_Int_Translate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmovl", offset(code, 1), "%eax");
	writeCodeInFile(file, "\tnegl", "%eax", "");
	writeCodeInFile(file, "\tmovl", "%eax", offset(code, 2));
}

/*-----------------------------------------------------------------------*/
/**"ADD_INT %s %s %s\n" */
void add_Int_Translate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmovl", offset(code, 1), "%eax");
	writeCodeInFile(file, "\taddl", offset(code, 2) ,"%eax");
	writeCodeInFile(file, "\tmovl", "%eax", offset(code, 3));
}

/*-----------------------------------------------------------------------*/
/**"MULT_INT %s %s %s\n" */
void mult_Int_Translate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmovl", offset(code, 1), "%eax");
	writeCodeInFile(file, "\timull", offset(code, 2) ,"%eax");
	writeCodeInFile(file, "\tmovl", "%eax", offset(code, 3));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_INT %s %s %s\n" */
void greater_IntTranslate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmovl", offset(code, 2), "%eax");
	writeCodeInFile(file, "\tcmpl", offset(code, 1) ,"%eax");
	writeCodeInFile(file, "\tsetg", "%al", "");
	writeCodeInFile(file, "\tmovzbl", "%al", "%eax");
	writeCodeInFile(file, "\tmovl", "%eax", offset(code, 3));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_ EQ_INT %s %s %s\n" */
void greater_Eq_IntTranslate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmovl", offset(code, 2), "%eax");
	writeCodeInFile(file, "\tcmpl", offset(code, 1) ,"%eax");
	writeCodeInFile(file, "\tsetge", "%al", "");
	writeCodeInFile(file, "\tmovzbl", "%al", "%eax");
	writeCodeInFile(file, "\tmovl", "%eax", offset(code, 3));
}

/* Puts in the file the translation of the MINUS_INT action */
void translateMinusInt(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmov", offset(code,1), "%rax");
	writeCodeInFile(file, "\tmov", offset(code,2), "%r10");
	writeCodeInFile(file, "\tsub", "%rax", "%r10");
	writeCodeInFile(file, "\tmov", "%r10", offset(code,3));
}

/* Puts in the file the translation of the MOD_INT action */
void translateModInt(FILE* file, Code3D* code)
{
	/* it divides"rdx:rax" by "divisor". Stores quotient in rax and remainder in rdx */
	writeCodeInFile(file, "\tmov", "$0", "%rdx");
	writeCodeInFile(file, "\tmov", "$0", "%rax");
	writeCodeInFile(file, "\tmov", offset(code,1) ,"%rax");
	writeCodeInFile(file, "\tidiv", offset(code,2), "");
	writeCodeInFile(file, "\tmov", "%rdx", offset(code,3));
}

/* Puts in the file the translation of the DIV_INT action */
void translateDivInt(FILE* file, Code3D* code)
{
	/* it divides"rdx:rax" by "divisor". Stores quotient in rax and remainder in rdx */
	writeCodeInFile(file, "\tmov", "$0", "%rdx");
	writeCodeInFile(file, "\tmov", "$0", "%rax");
	writeCodeInFile(file, "\tmov", offset(code,1) ,"%rax");
	writeCodeInFile(file, "\tidiv", offset(code,2), "");
	writeCodeInFile(file, "\tmov", "%rax", offset(code,3));
}

/* Puts in the file the translation of the LESSER_INT action */
void translateLesserInt(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmov", offset(code,2), "%rax");
	writeCodeInFile(file, "\tcmp", offset(code,1) ,"%rax");
	writeCodeInFile(file, "\tcmovl", "%rax", offset(code,3));
}

/* Puts in the file the translation of the LESSER_EQ_INT action */
void translateLesserOrEqualInt(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmov", offset(code,2), "%rax");
	writeCodeInFile(file, "\tcmp", offset(code,1) ,"%rax");
	writeCodeInFile(file, "\tcmovle", "%rax", offset(code,3));
}

/* Puts in the file the translation of the EQ_INT action */
void translateEqualInt(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmov", offset(code,2), "%rax");
	writeCodeInFile(file, "\tcmp", offset(code,1) ,"%rax");
	writeCodeInFile(file, "\tcmove", "%rax", offset(code,3));
}

/* Puts in the file the translation of the DIST_INT action */
void translateDistinctInt(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmov", offset(code,2), "%rax");
	writeCodeInFile(file, "\tcmp", offset(code,1) ,"%rax");
	writeCodeInFile(file, "\tcmovne", "%rax", offset(code,3));
}

/********************************************************************************************/
/********************************* FLOAT OPERATIONS TREATEMENT ******************************/
/********************************************************************************************/

/*-----------------------------------------------------------------------*/
/**"NEG_FLOAT %s %s\n" */
void neg_Float_Translate(FILE* file, Code3D* code)
{
writeCodeInFile(file, "\txorps", "%xmm0", "%xmm0");
writeCodeInFile(file, "\tucomiss", offset(code,1), "%xmm0");
writeCodeInFile(file, "\tsetp", "%dl", "");
writeCodeInFile(file, "\tmovl", "$1", "%eax");
writeCodeInFile(file, "\txorps", "%xmm0", "%xmm0");
writeCodeInFile(file, "\tucomiss", offset(code,1), "%xmm0");
writeCodeInFile(file, "\tcmove", "%edx", "%eax");
writeCodeInFile(file, "\tmovb", "%al", offset(code,2));
}

/*-----------------------------------------------------------------------*/
/**"EQ_FLOAT %s %s %s\n" */
void eq_FloatTranslate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmovss", offset(code, 1), "%xmm0");
	writeCodeInFile(file, "\tucomiss", offset(code, 2) ,"%xmm0");
	writeCodeInFile(file, "\tsetnp", "%dl", "");
	writeCodeInFile(file, "\tmovl", "%0", "%eax");
	writeCodeInFile(file, "\tmovss", offset(code, 1), "%xmm0");
	writeCodeInFile(file, "\tucomiss", offset(code, 2) ,"%xmm0");
	writeCodeInFile(file, "\tcmove", "%edx", "%eax");
	writeCodeInFile(file, "\tmovb", "%al", offset(code, 3));
}


/**"DIST_FLOAT %s %s %s\n" */
void dist_FloatTranslate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmovss", offset(code, 1), "%xmm0");
	writeCodeInFile(file, "\tucomiss", offset(code, 2) ,"%xmm0");
	writeCodeInFile(file, "\tsetp", "%dl", "");
	writeCodeInFile(file, "\tmovl", "%1", "%eax");
	writeCodeInFile(file, "\tmovss", offset(code, 1), "%xmm0");
	writeCodeInFile(file, "\tucomiss", offset(code, 2) ,"%xmm0");
	writeCodeInFile(file, "\tcmove", "%edx", "%eax");
	writeCodeInFile(file, "\tmovb", "%al", offset(code, 3));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_FLOAT %s %s %s\n" */
void greater_FloatTranslate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmovss", offset(code, 2), "%xmm0");
	writeCodeInFile(file, "\tucomiss", offset(code, 1) ,"%xmm0");
	writeCodeInFile(file, "\tseta", "%al", "");
	writeCodeInFile(file, "\tmovb", "%al", offset(code, 3));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_ EQ_FLOAT %s %s %s\n" */
void greater_Eq_FloatTranslate(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmovss", offset(code, 2), "%xmm0");
	writeCodeInFile(file, "\tucomiss", offset(code, 1) ,"%xmm0");
	writeCodeInFile(file, "\tsetae", "%al", "");
	writeCodeInFile(file, "\tmovb", "%al", offset(code, 3));
}

/* Puts in the file the translation of the LESSER_EQ_FLOAT action */
void translateLesserOrEqualFloat(FILE *file, Code3D* code)
{
	writeCodeInFile(file, "\tmovss", offset(code, 2), "%xmm0");
	writeCodeInFile(file, "\tucomiss", offset(code, 1) ,"%xmm0");
	writeCodeInFile(file, "\tsetbe", "%al", "");
	writeCodeInFile(file, "\tmovb", "%al", offset(code, 3));
}

/* Puts in the file the translation of the LESSER_FLOAT action */
void translateLesserFloat(FILE *file, Code3D* code)
{
	writeCodeInFile(file, "\tmovss", offset(code, 2), "%xmm0");
	writeCodeInFile(file, "\tucomiss", offset(code, 1) ,"%xmm0");
	writeCodeInFile(file, "\tsetb", "%al", "");
	writeCodeInFile(file, "\tmovb", "%al", offset(code, 3));
}

/* Puts in the file the translation of the DIV_FLOAT action */
void translateDivFloat(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmovss", offset(code,2) ,"%xmm0");
	writeCodeInFile(file, "\tdivss", offset(code,1), "%xmm0");
	writeCodeInFile(file, "\tmovss", "%xmm0", offset(code,3));
}

/* Puts in the file the translation of the MULT_FLOAT action */
void translateMultFloat(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmovss", offset(code,2) ,"%xmm0");
	writeCodeInFile(file, "\tmulss", offset(code,1), "%xmm0");
	writeCodeInFile(file, "\tmovss", "%xmm0", offset(code,3));
}

/* Puts in the file the translation of the ADD_FLOAT action */
void translateAddFloat(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmovss", offset(code,2) ,"%xmm0");
	writeCodeInFile(file, "\taddss", offset(code,1), "%xmm0");
	writeCodeInFile(file, "\tmovss", "%xmm0", offset(code,3));
}

/* Puts in the file the translation of the MINUS_FLOAT action */
void translateMinusFloat(FILE* file, Code3D* code)
{
	writeCodeInFile(file, "\tmovss", offset(code,2) ,"%xmm0");
	writeCodeInFile(file, "\tsubss", offset(code,1), "%xmm0");
	writeCodeInFile(file, "\tmovss", "%xmm0", offset(code,3));
}

