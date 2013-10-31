#include "Translate.h"

//Retorna la contatenacion de dos cadenas.
char* concat(char* str1, char* str2)
{
    char* result = malloc(strlen(str1)+strlen(str2)+1);
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
