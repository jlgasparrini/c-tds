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

//Este podria tomar por separado las operaciones a meter en el archivo.
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
void load_Const_Translate(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmovl", value(code), offset(code, 2));
}

/* Puts in the file the translation of the GOTO_LABEL action */
void translateGotoLabel(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tjmp", getLabel(code,1), "");
}

/* Puts in the file the translation of the GOTO_LABEL_CONDITION action */
void translateGotoLabelCondition(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmov", offset(code,1), "%rax");
	writeCodeInFile(archivo, "\tcmp", "$0", "%rax");
	writeCodeInFile(archivo, "\tje", getLabel(code,2), "");
}

/* Puts in the file the translation of the ASSIGNATION action */
void translateAssignation(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmov", offset(code,1), "%rax");
	writeCodeInFile(archivo, "\tmov", "%rax", offset(code,2));
}

/* Puts in the file the translation of the RETURN action */
void translateReturn(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmov", "$0", "%rax");
	writeCodeInFile(archivo, "\tleave", "", "");
	writeCodeInFile(archivo, "\tret", "", "");
}

/* Puts in the file the translation of the RETURN_EXPR action */
void translateReturnExpression(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmov", offset(code,1), "%rax");
	writeCodeInFile(archivo, "\tleave", "", "");
	writeCodeInFile(archivo, "\tret", "", "");
}

/* Puts in the file the translation of the MINUS_INT action */
void translateOr(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmov", offset(code,1), "%rax");
	writeCodeInFile(archivo, "\tor", offset(code,2), "%rax");
	writeCodeInFile(archivo, "\tmov", "%rax", offset(code,3));
}

/* Puts in the file the translation of the MINUS_INT action */
void translateAnd(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmov", offset(code,1), "%rax");
	writeCodeInFile(archivo, "\tand", offset(code,2), "%rax");
	writeCodeInFile(archivo, "\tmov", "%rax", offset(code,3));
}

/* Puts in the file the translation of the MINUS_INT action */
void translateNot(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmov", offset(code,1), "%rax");
	writeCodeInFile(archivo, "\tnot", "%rax", "");
	writeCodeInFile(archivo, "\tmov", "%rax", offset(code,2));
}

/********************************************************************************************/
/********************************* INT OPERATIONS TREATEMENT ********************************/
/********************************************************************************************/

/*-----------------------------------------------------------------------*/
/**"NEG_INT %s %s\n" */
void neg_Int_Translate(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmovl", offset(code, 1), "%eax");
	writeCodeInFile(archivo, "\tnegl", "%eax", "");
	writeCodeInFile(archivo, "\tmovl", "%eax", offset(code, 2));
}

/*-----------------------------------------------------------------------*/
/**"ADD_INT %s %s %s\n" */
void add_Int_Translate(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmovl", offset(code, 1), "%eax");
	writeCodeInFile(archivo, "\taddl", offset(code, 2) ,"%eax");
	writeCodeInFile(archivo, "\tmovl", "%eax", offset(code, 3));
}

/*-----------------------------------------------------------------------*/
/**"MULT_INT %s %s %s\n" */
void mult_Int_Translate(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmovl", offset(code, 1), "%eax");
	writeCodeInFile(archivo, "\timull", offset(code, 2) ,"%eax");
	writeCodeInFile(archivo, "\tmovl", "%eax", offset(code, 3));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_INT %s %s %s\n" */
void greater_IntTranslate(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmovl", offset(code, 2), "%eax");
	writeCodeInFile(archivo, "\tcmpl", offset(code, 1) ,"%eax");
	writeCodeInFile(archivo, "\tsetg", "%al", "");
	writeCodeInFile(archivo, "\tmovzbl", "%al", "%eax");
	writeCodeInFile(archivo, "\tmovl", "%eax", offset(code, 3));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_ EQ_INT %s %s %s\n" */
void greater_Eq_IntTranslate(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmovl", offset(code, 2), "%eax");
	writeCodeInFile(archivo, "\tcmpl", offset(code, 1) ,"%eax");
	writeCodeInFile(archivo, "\tsetge", "%al", "");
	writeCodeInFile(archivo, "\tmovzbl", "%al", "%eax");
	writeCodeInFile(archivo, "\tmovl", "%eax", offset(code, 3));
}

/* Puts in the file the translation of the MINUS_INT action */
void translateMinusInt(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmov", offset(code,1), "%rax");
	writeCodeInFile(archivo, "\tmov", offset(code,2), "%r10");
	writeCodeInFile(archivo, "\tsub", "%rax", "%r10");
	writeCodeInFile(archivo, "\tmov", "%r10", offset(code,3));
}

/* Puts in the file the translation of the MOD_INT action */
void translateModInt(FILE* archivo, Code3D* code)
{
	/* it divides"rdx:rax" by "divisor". Stores quotient in rax and remainder in rdx */
	writeCodeInFile(archivo, "\tmov", "$0", "%rdx");
	writeCodeInFile(archivo, "\tmov", "$0", "%rax");
	writeCodeInFile(archivo, "\tmov", offset(code,1) ,"%rax");
	writeCodeInFile(archivo, "\tidiv", offset(code,2), "");
	writeCodeInFile(archivo, "\tmov", "%rdx", offset(code,3));
}

/* Puts in the file the translation of the DIV_INT action */
void translateDivInt(FILE* archivo, Code3D* code)
{
	/* it divides"rdx:rax" by "divisor". Stores quotient in rax and remainder in rdx */
	writeCodeInFile(archivo, "\tmov", "$0", "%rdx");
	writeCodeInFile(archivo, "\tmov", "$0", "%rax");
	writeCodeInFile(archivo, "\tmov", offset(code,1) ,"%rax");
	writeCodeInFile(archivo, "\tidiv", offset(code,2), "");
	writeCodeInFile(archivo, "\tmov", "%rax", offset(code,3));
}

/* Puts in the file the translation of the LESSER_INT action */
void translateLesserInt(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmov", offset(code,2), "%rax");
	writeCodeInFile(archivo, "\tcmp", offset(code,1) ,"%rax");
	writeCodeInFile(archivo, "\tcmovl", "%rax", offset(code,3));
}

/* Puts in the file the translation of the LESSER_EQ_INT action */
void translateLesserOrEqualInt(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmov", offset(code,2), "%rax");
	writeCodeInFile(archivo, "\tcmp", offset(code,1) ,"%rax");
	writeCodeInFile(archivo, "\tcmovle", "%rax", offset(code,3));
}

/* Puts in the file the translation of the EQ_INT action */
void translateEqualInt(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmov", offset(code,2), "%rax");
	writeCodeInFile(archivo, "\tcmp", offset(code,1) ,"%rax");
	writeCodeInFile(archivo, "\tcmove", "%rax", offset(code,3));
}

/* Puts in the file the translation of the DIST_INT action */
void translateDistinctInt(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmov", offset(code,2), "%rax");
	writeCodeInFile(archivo, "\tcmp", offset(code,1) ,"%rax");
	writeCodeInFile(archivo, "\tcmovne", "%rax", offset(code,3));
}

/********************************************************************************************/
/********************************* FLOAT OPERATIONS TREATEMENT ******************************/
/********************************************************************************************/

/*-----------------------------------------------------------------------*/
/**"GREATER_FLOAT %s %s %s\n" */
void greater_FloatTranslate(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmovss", offset(code, 2), "%xmm0");
	writeCodeInFile(archivo, "\tucomiss", offset(code, 1) ,"%xmm0");
	writeCodeInFile(archivo, "\tseta", "%al", "");
	writeCodeInFile(archivo, "\tmovb", "%al", offset(code, 3));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_ EQ_FLOAT %s %s %s\n" */
void greater_Eq_FloatTranslate(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "\tmovss", offset(code, 2), "%xmm0");
	writeCodeInFile(archivo, "\tucomiss", offset(code, 1) ,"%xmm0");
	writeCodeInFile(archivo, "\tsetae", "%al", "");
	writeCodeInFile(archivo, "\tmovb", "%al", offset(code, 3));
}

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
            
void writeLabel(FILE *file, Code3D *code)
{
    writeCodeInFile(file, concat(getLabel(code, 1), ":"), "", "");
}
