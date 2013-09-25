#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Attribute.h"
#include "SymbolsTable.h"
#include "Utils.h"
#include "../ErrorsQueue/ErrorsQueue.h"

/* Returns an attribute of ID "id" and Variable structure. Otherwise returns NULL */
Attribute* getVariableAttribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id)
{
	Attribute *attr = searchIdInSymbolsTable(aSymbolsTable, id);
	if(attr == NULL) 
		insertError(eq, toString("El identificador \"", id, "\" no esta definido."));
    else
		if((*attr).type != Variable)
		{
			insertError(eq, toString("El identificador \"", id, "\" no corresponde a una variable."));
			return NULL;
		}
	return attr;
}

/* Returns an attribute in the position "pos" of the ID "id" and Array structure. Otherwise returns NULL */
Attribute* getArrayAttribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id, int pos)
{
	Attribute *attr = searchIdInSymbolsTable(aSymbolsTable, id);
	if(attr == NULL) 
		insertError(eq, toString("El identificador \"", id, "\" no esta definido."));
    else
		if((*attr).type != Array)
		{
			insertError(eq, toString("El identificador \"", id, "\" no corresponde a un arreglo."));
			return NULL;
		}
	return attr; /* ACA DEBERIA RETORNARSE LA VARIABLE QUE SE ENCUENTRA EN EL ARREGLO EN LA POSICION "pos"-------------------------------------- */
}

/* verificar si este metodo no tendria que retornar el valor de retorno del metodo!! ---------------------------------------------------------*/
Attribute* getMethodAttribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id, unsigned char paramSize)
{ 
	Attribute *attr = searchIdInSymbolsTable(aSymbolsTable, id);
    if(attr == NULL) 
		insertError(eq,toString("El identificador \"", id, "\" no esta definido."));
    else
    {
        if((*attr).type != Method)
			insertError(eq,toString("El identificador \"", id,"\" no corresponde a un metodo."));
        else
        { 
            if ((*attr).decl.method.paramSize != paramSize) /* if the method doesn't have the same amount of parameters */
		 		if ((*attr).decl.method.paramSize == 0)
					insertError(eq, toString("La llamada al metodo \"", id, "\" no debe contener parametros."));
		 		else
				{
					char* number = (char*) malloc (digitAmount(paramSize)*sizeof(char));
					sprintf(number,"%d",paramSize);
					char* msg = (char*) malloc ((strlen("\" no contiene sus ")+strlen(number)+strlen(" parametros correspondientes."))*sizeof(char));
					strcat(msg, "\" no contiene sus ");
					strcat(msg, number);
					strcat(msg, " parametros correspondientes.");
					insertError(eq, toString("La llamada al metodo \"", id, msg));
			//		free(number);
				//	free(msg);
				}
        }
    }
}

/* creates an attribute and assign it as a parameter of "method" containing the information included.
	Returns a pointer to the attribute if the parameter was created successful. Returns NULL otherwise. */
Attribute* arrangeParameter(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, unsigned char paramSize, char* id, PrimitiveType type)  
{
	Attribute *aux = lastDefinedMethod(aSymbolsTable);
	if (searchIdInLevel(aSymbolsTable, id))
	{	
		aux = createParameter(aux, paramSize, id, type);
		pushElement(eq, aSymbolsTable, aux);
		return aux;
	}
	char* number = (char*) malloc (digitAmount(paramSize)*sizeof(char));
	sprintf(number,"%d",paramSize);
	char* msg = (char*) malloc ((strlen(". El identificador del ")+strlen(number)+strlen("° parametro \"")+strlen(id)+strlen("\", ya se encuentra utilizado."))*sizeof(char));
	strcat(msg,"\". El identificador del ");
	strcat(msg, number);
	strcat(msg,"° parametro \"");
	strcat(msg, id);
	strcat(msg,"\" ya se encuentra utilizado.");
	insertError(eq,toString("Error en el metodo \"", (*aux).decl.method.id, msg));  
//	free(number);
//	free(msg);
	return NULL;
}

/* Returns 0 if the type of the parameter on the position "pos" of the method "attr" is equal to the type of "var"
	Returns 1 otherwise */
unsigned char correctParameterType(StVariable *var, Attribute *attr, unsigned char pos)
{
	if ((*var).type == (*attr).decl.method.parameters[pos].type)
		return 0;
	return 1;
}

/* Returns the ReturnType of the method with id "id" */
ReturnType methodReturnType(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id)
{
	Attribute *attr = searchIdInSymbolsTable(aSymbolsTable, id);
	if(attr == NULL) 
		insertError(eq, toString("El identificador \"", id, "\" no esta definido."));
    else
        if((*attr).type != Method)
			insertError(eq, toString("El identificador \"", id, "\" no corresponde a un metodo."));
		else
			return (*attr).decl.method.type;
}

/* Returns the string corresponding to "type" */
char* getType(PrimitiveType type)
{
	if (type == Int)
		return "int";
	if (type == Float)
		return "float";
	if (type == Bool)
		return "boolean";
	return "incorrect type";
}

/* Returns 0 if the type parameter in "paramSize" position of the method's parameters is equal to the type of "var" 
   and the amount of params are equal.
	Returns 1 otherwise */
unsigned char correctParamBC(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, Attribute *attr, char* lastCalledMethod, unsigned char paramSize)
{
	Attribute *aux = searchIdInSymbolsTable(aSymbolsTable, lastCalledMethod);
	if(aux == NULL) 
		insertError(eq, toString("El identificador \"", lastCalledMethod, "\" no esta definido."));
    else
        if((*aux).type != Method)
			insertError(eq, toString("El identificador \"", lastCalledMethod, "\" no corresponde a un metodo."));
		else
			if (paramSize == (*aux).decl.method.paramSize) 
			{
				if (correctParameterType(&(*attr).decl.variable, aux, paramSize) == 0) 
					return 0;
				else
				{
					char* number = (char*) malloc (digitAmount(paramSize)*sizeof(char));
					sprintf(number,"%d",paramSize);
					char* f = (char*) malloc ((strlen("\". El ")+strlen(number)+strlen("° parametro no es del tipo \"")+strlen(getType((*aux).decl.method.parameters[paramSize].type)+strlen("\".")))*sizeof(char));
					strcat(f,"\". El ");
					strcat(f, number);
					strcat(f,"° parametro no es del tipo \"");
					strcat(f, getType((*aux).decl.method.parameters[paramSize].type));
					strcat(f, "\".");
					insertError(eq,toString("Error en llamada al metodo \"", lastCalledMethod, f));  
				//	free(number);
				//	free(f);
				}
			}
			else
				insertError(eq,toString("Error en llamada al metodo \"", lastCalledMethod, "\". No se tiene la misma cantidad de parametros que en su declaracion."));  
	return 1;
}

/* Returns 0 if the type parameter in "paramSize" position of the method's parameters is equal to the type of "var" 
   and paramSize <= than the amount of parameters of the method.
	Returns 1 otherwise */
unsigned char correctParamIC(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, Attribute *attr, char* lastCalledMethod, unsigned char paramSize)
{
	Attribute *aux = searchIdInSymbolsTable(aSymbolsTable, lastCalledMethod);
	if(aux == NULL) 
		insertError(eq, toString("El identificador \"", lastCalledMethod, "\" no esta definido."));
    else
        if((*aux).type != Method)
			insertError(eq, toString("El identificador \"", lastCalledMethod, "\" no corresponde a un metodo."));
		else
			if (paramSize == (*aux).decl.method.paramSize) 
				if (correctParameterType(&(*attr).decl.variable, aux, paramSize) == 0) 
					return 0;
				else
				{
					char* number = (char*) malloc (digitAmount(paramSize)*sizeof(char));
					sprintf(number,"%d",paramSize);
					char* f = (char*) malloc ((strlen("\". El ")+strlen(number)+strlen("° parametro no es del tipo \"")+strlen(getType((*aux).decl.method.parameters[paramSize].type)+strlen("\".")))*sizeof(char));
					strcat(f,"\". El ");
					strcat(f, number);
					strcat(f,"° parametro no es del tipo \"");
					strcat(f, getType((*aux).decl.method.parameters[paramSize].type));
					strcat(f, "\".");
					insertError(eq,toString("Error en llamada al metodo \"", lastCalledMethod, f));  
				//	free(number);
				//	free(f);
				}
			else
				insertError(eq,toString("Error en llamada al metodo \"", lastCalledMethod, "\". Se tiene mayor cantidad de parametros que en su declaracion."));  
	return 1;
}

/* ---------------------------------------expression and conjunction no-terminal---------------------------------------------- */

/* Return an attribute with the or operation applied to oper1 and oper2. */
Attribute* returnOr(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == (*oper2).decl.variable.type && ((*oper2).decl.variable.type == Bool))
        return createVariable("", (*oper1).decl.variable.type);
    return NULL;
}


/* Return an attribute with the and operation applied to oper1 and oper2. */
Attribute* returnAnd(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == (*oper2).decl.variable.type && ((*oper2).decl.variable.type == Bool))
        return createVariable("", (*oper1).decl.variable.type);
    return NULL;

}
/* ---------------------------------------expression and conjunction no-terminal ended-------------------------------------- */

/* ---------------------------------------inequality and comparison no-terminal-------------------------------------------- */

/* Return an attribute with the distinct operation applied to oper1 and oper2. */
Attribute* returnDistinct(Attribute *oper1, Attribute *oper2)
{
    return createVariable("", Bool);
}

/* Return an attribute with the equal operation applied to oper1 and oper2. */
Attribute* returnEqual(Attribute *oper1, Attribute *oper2)
{
    return createVariable("", Bool);
}
/* ------------------------------------inequality and comparison no-terminal ended---------------------------------------- */

/* ---------------------------------------relation no-terminal ------------------------------------------------ */

/* Return an attribute with the minor comparison operation applied to oper1 and oper2. */
Attribute* returnMinorComparison(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == Bool && (*oper2).decl.variable.type == Bool)
        return createVariable("", Bool); /* QUE HACER EN ESTE CASO? FALSE < TRUE == TRUE?? O DIRECTAMENTE MOSTRAR COMO SI ES UN ERROR? 
                                            EN CASO DE QUE SE MUESTRE COMO ERROR, ESTE IF DEBERIA ELIMINARSE --------------------------------*/

    if ((*oper1).decl.variable.type != Bool && (*oper2).decl.variable.type != Bool)
        return createVariable("", Bool);

    return NULL;
}

/* Return an attribute with the major comparison operation applied to oper1 and oper2. */
Attribute* returnMajorComparison(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == Bool && (*oper2).decl.variable.type == Bool)
        return createVariable("", Bool); /* QUE HACER EN ESTE CASO? FALSE > TRUE == FALSE?? O DIRECTAMENTE MOSTRAR COMO SI ES UN ERROR? 
                                            EN CASO DE QUE SE MUESTRE COMO ERROR, ESTE IF DEBERIA ELIMINARSE --------------------------------*/

    if ((*oper1).decl.variable.type != Bool && (*oper2).decl.variable.type != Bool)
        return createVariable("", Bool);

    return NULL;
}

/* Return an attribute with the greater or equal comparison operation applied to oper1 and oper2. */
Attribute* returnGEqualComparison(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == Bool && (*oper2).decl.variable.type == Bool)
        return createVariable("", Bool); /* QUE HACER EN ESTE CASO? FALSE >= TRUE == FALSE?? O DIRECTAMENTE MOSTRAR COMO SI ES UN ERROR? 
                                            EN CASO DE QUE SE MUESTRE COMO ERROR, ESTE IF DEBERIA ELIMINARSE --------------------------------*/

    if ((*oper1).decl.variable.type != Bool && (*oper2).decl.variable.type != Bool)
        return createVariable("", Bool); /*  EL CASO 3 >= 3.2 */

    return NULL;
}

/* Return an attribute with the less or equal comparison operation applied to oper1 and oper2. */
Attribute* returnLEqualComparison(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == Bool && (*oper2).decl.variable.type == Bool)
        return createVariable("", Bool); /* QUE HACER EN ESTE CASO? FALSE <= TRUE == TRUE?? O DIRECTAMENTE MOSTRAR COMO SI ES UN ERROR? 
                                            EN CASO DE QUE SE MUESTRE COMO ERROR, ESTE IF DEBERIA ELIMINARSE --------------------------------*/

    if ((*oper1).decl.variable.type != Bool && (*oper2).decl.variable.type != Bool)
        return createVariable("", Bool);

    return NULL;
}
/* ---------------------------------------relation no-terminal ended---------------------------------------- */

/* ---------------------------------------term no-terminal ------------------------------------------------ */

/* Return an attribute with the add operation. */
Attribute* returnAdd(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == (*oper2).decl.variable.type && ((*oper2).decl.variable.type != Bool))
        return createVariable("", (*oper1).decl.variable.type);
    return NULL;
}

/* Return an attribute with the sub operation. */
Attribute* returnSub(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == (*oper2).decl.variable.type && ((*oper2).decl.variable.type != Bool))
        return createVariable("", (*oper1).decl.variable.type);
    return NULL;
}

/* Return an attribute with the mod operation. */
Attribute* returnMod(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == (*oper2).decl.variable.type && ((*oper2).decl.variable.type != Bool))
        return createVariable("", (*oper1).decl.variable.type);
    return NULL;
}

/* Return an attribute with the div operation. */
Attribute* returnDiv(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == (*oper2).decl.variable.type && ((*oper2).decl.variable.type != Bool))
        return createVariable("", (*oper1).decl.variable.type);
    return NULL;
}

/* Return an attribute with the mult operation. */
Attribute* returnMult(Attribute *oper1, Attribute *oper2)
{
    if (((*oper1).decl.variable.type == (*oper2).decl.variable.type) && ((*oper2).decl.variable.type != Bool))
        return createVariable("", (*oper1).decl.variable.type);
    return NULL;
}

/* ---------------------------------------term no-terminal ended----------------------------------------- */
