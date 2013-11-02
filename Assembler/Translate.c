#include "Translate.h"

//Retorna la contatenacion de dos cadenas.
char* concat(char* str1, char* str2)
{ char* result = malloc(strlen(str1)+strlen(str2)+1);
    strcpy(result, str1);
    strcat(result, str2);
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
	char result = (char*) malloc(sizeof(char)); /* CHECK OUT THIS CASE BECAUSE sizeof(char) ONLY STORES MEMORY FOR ONLY ONE CHARACTER! */
	if (isInt(code, 1))							/* IF THE NUMBER HAS MORE THAN ONE DIGIT (CHARACTER) IT WILL BROKE! */
			result = getInt(code, 1);
	if (isFloat(code, 1))
			result = getFloat(code, 1);
	if (isBool(code, 1))
			result = getBool(codeValue, 1);	
	return concat("$", result);		
}

/**Metodo para la obtencion del offset de una variable*/
char* offset(Code3D* code, int param)
{
	char result = (char*) malloc(sizeof(char));
	result = getOffset(code, param);
	return concat (result, "(%rbp)");
}


/*-----------------------------------------------------------------------*/
/**"LOAD_CONST %s %s\n" */
void load_Const_Translate(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "   movl", value(code), offset(code, 2));
}

/* Puts in the file the translation of the GOTO_LABEL action */
void translateGotoLabel(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "jmp", getLabel(code,1), "");
}

/* Puts in the file the translation of the GOTO_LABEL_CONDITION action */
void translateGotoLabelCondition(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "mov", offset(code,1), "%rax");
	writeCodeInFile(archivo, "cmp", "$0", "%rax");
	writeCodeInFile(archivo, "je", getLabel(code,2), "");
}

/* Puts in the file the translation of the ASSIGNATION action */
void translateAssignation(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "mov", offset(code,1), "%rax");
	writeCodeInFile(archivo, "mov", "%rax", offset(code,2));
}

/* Puts in the file the translation of the RETURN action */
void translateReturn(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "mov", "$0", "%rax");
	writeCodeInFile(archivo, "leave", "", "");
	writeCodeInFile(archivo, "ret", "", "");
}

/* Puts in the file the translation of the RETURN_EXPR action */
void translateReturnExpression(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "mov", offset(code,1), "%rax");
	writeCodeInFile(archivo, "leave", "", "");
	writeCodeInFile(archivo, "ret", "", "");
}

/********************************************************************************************/
/********************************* INT OPERATIONS TREATEMENT ********************************/
/********************************************************************************************/

/*-----------------------------------------------------------------------*/
/**"NEG_INT %s %s\n" */
void neg_Int_Translate(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "   movl", offset(code, 1), "%eax");
	writeCodeInFile(archivo, "   negl", "%eax", "");
	writeCodeInFile(archivo, "   movl", "%eax", offset(code, 2));
}

/*-----------------------------------------------------------------------*/
/**"ADD_INT %s %s %s\n" */
void add_Int_Translate(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "   movl", offset(code, 1), "%eax");
	writeCodeInFile(archivo, "   addl", offset(code, 2) ,"%eax");
	writeCodeInFile(archivo, "   movl", "%eax", offset(code, 3));
}

/*-----------------------------------------------------------------------*/
/**"MULT_INT %s %s %s\n" */
void mult_Int_Translate(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "   movl", offset(code, 1), "%eax");
	writeCodeInFile(archivo, "   imull", offset(code, 2) ,"%eax");
	writeCodeInFile(archivo, "   movl", "%eax", offset(code, 3));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_INT %s %s %s\n" */
void greater_IntTranslate(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "   movl", offset(code, 2), "%eax");
	writeCodeInFile(archivo, "   cmpl", offset(code, 1) ,"%eax");
	writeCodeInFile(archivo, "   setg", "%al", "");
	writeCodeInFile(archivo, "   movzbl", "%al", "%eax");
	writeCodeInFile(archivo, "   movl", "%eax", offset(code, 3));
}

/*-----------------------------------------------------------------------*/
/**"GREATER_ EQ_INT %s %s %s\n" */
void greater_Eq_IntTranslate(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "   movl", offset(code, 2), "%eax");
	writeCodeInFile(archivo, "   cmpl", offset(code, 1) ,"%eax");
	writeCodeInFile(archivo, "   setge", "%al", "");
	writeCodeInFile(archivo, "   movzbl", "%al", "%eax");
	writeCodeInFile(archivo, "   movl", "%eax", offset(code, 3));
}

/* Puts in the file the translation of the MINUS_INT action */
void translateMinusInt(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "mov", offset(code,1), "%rax");
	writeCodeInFile(archivo, "mov", offset(code,2), "%r10");
	writeCodeInFile(archivo, "sub", "%rax", "%r10");
	writeCodeInFile(archivo, "mov", "%r10", offset(code,3));
}

/* Puts in the file the translation of the MOD_INT action */
void translateModInt(FILE* archivo, Code3D* code)
{
	/* it divides"rdx:rax" by "divisor". Stores quotient in rax and remainder in rdx */
	writeCodeInFile(archivo, "mov", "$0", "%rdx");
	writeCodeInFile(archivo, "mov", "$0", "%rax");
	writeCodeInFile(archivo, "mov", offset(code,1) ,"%rax");
	writeCodeInFile(archivo, "idiv", offset(code,2), "");
	writeCodeInFile(archivo, "mov", "%rdx", offset(code,3));
}

/* Puts in the file the translation of the LESSER_INT action */
void translateLesserInt(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "mov", offset(code,2), "%rax");
	writeCodeInFile(archivo, "cmp", offset(code,1) ,"%rax");
	writeCodeInFile(archivo, "cmovl", "%rax", offset(code,3));
}

/* Puts in the file the translation of the LESSER_EQ_INT action */
void translateLesserOrEqualInt(FILE* archivo, Code3D* code)
{
	writeCodeInFile(archivo, "mov", offset(code,2), "%rax");
	writeCodeInFile(archivo, "cmp", offset(code,1) ,"%rax");
	writeCodeInFile(archivo, "cmovle", "%rax", offset(code,3));
}

/********************************************************************************************/
/********************************* FLOAT OPERATIONS TREATEMENT ******************************/
/********************************************************************************************/

/*-----------------------------------------------------------------------*/
/**"GREATER_FLOAT %s %s %s\n" */
void greater_FloatTranslate(FILE* archivo, Code3D* code)
{
	//ToDo
}

/*-----------------------------------------------------------------------*/
/**"GREATER_ EQ_FLOAT %s %s %s\n" */
void greater_Eq_FloatTranslate(FILE* archivo, Code3D* code)
{
	//ToDo
}

void printOperation(FILE *file, Code3D *code)
{
    isInt(code, 1)
