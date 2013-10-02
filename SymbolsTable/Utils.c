#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utils.h"

/* Returns an attribute of ID "id" and Variable structure. Otherwise returns NULL */
Attribute* getVariableAttribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id)
{
	Attribute *attr = searchIdInSymbolsTable(eq, aSymbolsTable, id);
	if(attr != NULL) 
		if((*attr).type != Variable)
		{
			insertError(eq, toString("El identificador \"", id, "\" no corresponde a una variable."));
			return NULL;
		}
	return attr;
}

/* Returns an attribute in the position "pos" of the ID "id" and Array structure. Otherwise returns NULL */
Attribute* getArrayAttribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, Attribute *attr, unsigned int pos)
{
    if((*attr).type != Array)
        if((*attr).type == Method)
            insertError(eq, toString("El identificador \"", (*attr).decl.method.id, "\" no corresponde a un arreglo."));
        else
            insertError(eq, toString("El identificador \"", (*attr).decl.variable.id, "\" no corresponde a un arreglo."));
    else    
        if (pos < 0 || pos >= (*attr).decl.array.length)
        {
            insertError(eq, toString("Error. Indice fuera de rango para acceder al arreglo \"", (*attr).decl.array.id, "\".")); 
            return createVariable("",(*attr).decl.array.type);
        }
        else
                return createVariable("",(*attr).decl.array.type); /* ACA DEBERIA RETORNARSE LA VARIABLE QUE SE ENCUENTRA EN EL ARREGLO EN LA POSICION "pos"-------------------------------------- */
}

/* verificar si este metodo no tendria que retornar el valor de retorno del metodo!! ---------------------------------------------------------*/
/* Returns the respective variable attribute that the method return. "paramSize" is for checking if the amount of parameters is right */
Attribute* getMethodAttribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id, unsigned char paramSize)
{ 
	Attribute *attr = searchIdInSymbolsTable(eq, aSymbolsTable, id);
    if(attr != NULL) 
    {
        if((*attr).type != Method)
			insertError(eq,toString("El identificador \"", id,"\" no corresponde a un metodo."));
        else
        { 
            if ((*attr).decl.method.paramSize != paramSize) /* if the method doesn't have the same amount of parameters */
			{
		 		if ((*attr).decl.method.paramSize == 0)
					insertError(eq, toString("La llamada al metodo \"", id, "\" no debe contener parametros."));
				return createVariable("",(*attr).decl.method.type);
			}
			else
				return createVariable("",(*attr).decl.method.type);
        }
    }
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
	Attribute *attr = searchIdInSymbolsTable(eq, aSymbolsTable, id);
	if(attr != NULL) 
        if((*attr).type != Method)
			insertError(eq, toString("El identificador \"", id, "\" no corresponde a un metodo."));
		else
			return (*attr).decl.method.type;
	return RetInt; /* retorno por defecto el tipo int */
}

/* Returns the type of the attribute, although it is a variable, array or method */
ReturnType getAttributeType(Attribute *attr)
{
    if((*attr).type == Variable)
		return (*attr).decl.variable.type;
    if((*attr).type != Array)
		return (*attr).decl.array.type;
    if((*attr).type == Method)
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

/* Returns the amount of digits that has the int "value" */
unsigned int digitAmount(int value)
{
	int count = 0;
    while (value > 0)
    {
	    value = value/10;
        count++;
    }
    return count;
}

/* Returns the string representation of the int "value" */
char* intToString(int value)
{
   char *aux = (char*) malloc (digitAmount(value)*sizeof(char)); 
   sprintf(aux,"%d",value);
   return aux;
}

/* Returns 0 if the type parameter in "paramSize" position of the method's parameters is equal to the type of "var" 
   and the amount of params are equal.
	Returns 1 otherwise */
unsigned char correctParamBC(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, Attribute *attr, char* lastCalledMethod, unsigned char paramSize)
{
	Attribute *aux = searchIdInSymbolsTable(eq, aSymbolsTable, lastCalledMethod);
	if(aux != NULL) 
        if((*aux).type != Method)
			insertError(eq, toString("El identificador \"", lastCalledMethod, "\" no corresponde a un metodo."));
		else
		{
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
                if (paramSize < (*aux).decl.method.paramSize)
                    insertError(eq,toString("Error en llamada al metodo \"", lastCalledMethod, "\". Se tiene menor cantidad de parametros que en su declaracion."));  
                else
                    insertError(eq,toString("Error en llamada al metodo \"", lastCalledMethod, "\". Se tiene mayor cantidad de parametros que en su declaracion."));  
		}
	return 1;
}

/* Returns 0 if the type parameter in "paramSize" position of the method's parameters is equal to the type of "var" 
   and paramSize <= than the amount of parameters of the method.
	Returns 1 otherwise */
unsigned char correctParamIC(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, Attribute *attr, char* lastCalledMethod, unsigned char paramSize)
{
	Attribute *aux = searchIdInSymbolsTable(eq, aSymbolsTable, lastCalledMethod);
	if(aux != NULL) 
        if((*aux).type != Method)
			insertError(eq, toString("El identificador \"", lastCalledMethod, "\" no corresponde a un metodo."));
		else
        {
			if (paramSize <= (*aux).decl.method.paramSize) 
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
				insertError(eq,toString("Error en llamada al metodo \"", lastCalledMethod, "\". Se tiene mayor cantidad de parametros que en su declaracion."));  
        }
	return 1;
}

/* Insert an error message if the attribute "attr" isn't a variable of type "type" */
int controlVariableType(ErrorsQueue *eq, Attribute *attr, PrimitiveType type)
{
    if (getAttributeType(attr) != type)	
        insertError(eq, toString("La expresion no es del tipo \"", getType(type), "\"."));
}

/* Insert an error message if attributes "attr1" and "attr2" aren't of the same type and both variables or arrays */
void controlAssignation(ErrorsQueue *eq, Attribute *attr1, char* op, Attribute *attr2)
{
	if ((*attr1).type != Method)
	{
        if (getAttributeType(attr1) != getAttributeType(attr2))
            insertError(eq, toString("El lado derecho de la asignacion debe ser de tipo \"", getType(getAttributeType(attr1)), "\"."));
	}
	else
		insertError(eq, toString("El identificador izquierdo de la asignacion ", "", " no debe ser un metodo."));
}

/* Insert an error message if the "lastUsedMethod" haven't got "void" return type */
void checkReturn(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* lastUsedMethod)
{
	ReturnType rt = methodReturnType(eq, aSymbolsTable, lastUsedMethod);
	if (rt != RetVoid)
	{
		char* msg = (char*) malloc ((strlen("\" debe retornar una expresion de tipo \"")+strlen(getType(rt))+strlen("\"."))*sizeof(char));
		strcat(msg, "\" debe retornar una expresion de tipo \"");
		strcat(msg, getType(rt));
		strcat(msg, "\".");
		insertError(eq, toString("El metodo \"", lastUsedMethod, msg));
//		free(msg);
	}
}

/* Insert an error message if the "lastUsedMethod" doesn't return "void" or if it has a different return type that the definition */
void checkReturnExpression(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* lastUsedMethod, Attribute *attr)
{
	ReturnType rt = methodReturnType(eq, aSymbolsTable, lastUsedMethod);
	if (rt == RetVoid)
		insertError(eq,toString("El metodo \"",lastUsedMethod,"\" no puede retornar una expresion ya que retorna void."));
	else
		if (rt != getAttributeType(attr))
		{
			char* msg = (char*) malloc ((strlen("\" debe retornar una expresion de tipo \"")+strlen(getType(rt))+strlen("\", no de tipo \"")+strlen(getType(getAttributeType(attr)))+strlen("\"."))*sizeof(char));
			strcat(msg, "\" debe retornar una expresion de tipo \"");
			strcat(msg, getType(rt));
			strcat(msg, "\", no de tipo \"");
			strcat(msg, getType(getAttributeType(attr)));
			strcat(msg, "\".");
			insertError(eq, toString("El metodo \"", lastUsedMethod, msg));
	//		free(msg);
		}
}

/* Returns the array at the position specified by attr.decl.variable.value.intValue if attr has "int" type
	Otherwise insert an error message because the attribute haven't got "int" type and create a default variable of "int" type */
Attribute* checkArrayPos(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id, Attribute* attr)
{
    Attribute *aux = searchIdInSymbolsTable(eq,aSymbolsTable,id);
    if (aux != NULL)
    {
        if (getAttributeType(attr) == Int)
            return getArrayAttribute(eq,aSymbolsTable,aux,(*attr).decl.variable.value.intVal);
        else
        {
            insertError(eq, toString("La expresion para acceder a la posicion del arreglo \"", id, "\" debe ser de tipo int.")); 
            return createVariable("",(*aux).decl.array.type);
        }
    }
    else
        return createVariable("",Int);
}

/* Checks if the program have a "main" method and it haven't got parameters */
void checkMain(ErrorsQueue *eq, SymbolsTable *aSymbolsTable)
{
    Attribute *attr = searchIdInSymbolsTable(eq, aSymbolsTable,"main");
    if (attr == NULL)
        insertError(eq, "El programa no tiene un metodo \"main\".");
    else
        if ((*attr).type != Method)
            insertError(eq, "El identificador \"main\" solo puede ser un metodo.");
}

/* ---------------------------------------expression and conjunction no-terminal---------------------------------------------- */

/* Return an attribute with the or operation applied to oper1 and oper2. */
Attribute* returnOr(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) == Bool))
    {
        Attribute *aux = createVariable("", Bool);
        (*aux).decl.variable.value.boolVal = ((*oper1).decl.variable.value.boolVal) || ((*oper2).decl.variable.value.boolVal);
        return aux;
    }
    else
    {
		insertError(eq, toString("La expresion logica \"", "OR", "\" no tiene ambos operandos de tipo booleano.")); 
        return createVariable("", Bool);
    }
}


/* Return an attribute with the and operation applied to oper1 and oper2. */
Attribute* returnAnd(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) == Bool))
    {
        Attribute *aux = createVariable("", Bool);
        (*aux).decl.variable.value.boolVal = ((*oper1).decl.variable.value.boolVal) && ((*oper2).decl.variable.value.boolVal);
        return aux;
    }
    else
    {
		insertError(eq, toString("La expresion logica \"", "AND", "\" no tiene ambos operandos de tipo booleano.")); 
        return createVariable("", Bool);
    }

}
/* ---------------------------------------expression and conjunction no-terminal ended-------------------------------------- */

/* ---------------------------------------inequality and comparison no-terminal-------------------------------------------- */

/* Return an attribute with the distinct operation applied to oper1 and oper2. */
Attribute* returnDistinct(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == Bool) 
    {
        Attribute *aux = createVariable("", getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
            (*aux).decl.variable.value.boolVal = ((*oper1).decl.variable.value.floatVal) != ((*oper2).decl.variable.value.floatVal);
        if (getAttributeType(oper1) == Int)
            (*aux).decl.variable.value.boolVal = ((*oper1).decl.variable.value.intVal) != ((*oper2).decl.variable.value.intVal);
        if (getAttributeType(oper1) == Bool)
            (*aux).decl.variable.value.boolVal = ((*oper1).decl.variable.value.boolVal) != ((*oper2).decl.variable.value.boolVal);
        return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", "!=", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")); 
        return createVariable("", Bool);
    }
}

/* Return an attribute with the equal operation applied to oper1 and oper2. */
Attribute* returnEqual(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == Bool) 
    {
        Attribute *aux = createVariable("", getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
            (*aux).decl.variable.value.boolVal = ((*oper1).decl.variable.value.floatVal) == ((*oper2).decl.variable.value.floatVal);
        if (getAttributeType(oper1) == Int)
            (*aux).decl.variable.value.boolVal = ((*oper1).decl.variable.value.intVal) == ((*oper2).decl.variable.value.intVal);
        if (getAttributeType(oper1) == Bool)
            (*aux).decl.variable.value.boolVal = ((*oper1).decl.variable.value.boolVal) == ((*oper2).decl.variable.value.boolVal);
        return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", "==", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")); 
        return createVariable("", Bool);
    }
}
/* ------------------------------------inequality and comparison no-terminal ended---------------------------------------- */

/* ---------------------------------------relation no-terminal ------------------------------------------------ */

/* Return an attribute with the minor comparison operation applied to oper1 and oper2. */
Attribute* returnMinorComparison(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && getAttributeType(oper2) != Bool) 
    {
        Attribute *aux = createVariable("", Bool);
        if (getAttributeType(oper1) == Float)
            (*aux).decl.variable.value.boolVal = ((*oper1).decl.variable.value.floatVal) > ((*oper2).decl.variable.value.floatVal);
        if (getAttributeType(oper1) == Int)
            (*aux).decl.variable.value.boolVal = ((*oper1).decl.variable.value.intVal) > ((*oper2).decl.variable.value.intVal);
        return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", "<", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")); 
        return createVariable("", Bool);
    }
}

/* Return an attribute with the major comparison operation applied to oper1 and oper2. */
Attribute* returnMajorComparison(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && getAttributeType(oper2) != Bool) 
    {
        Attribute *aux = createVariable("", Bool);
        if (getAttributeType(oper1) == Float)
            (*aux).decl.variable.value.boolVal = ((*oper1).decl.variable.value.floatVal) < ((*oper2).decl.variable.value.floatVal);
        if (getAttributeType(oper1) == Int)
            (*aux).decl.variable.value.boolVal = ((*oper1).decl.variable.value.intVal) < ((*oper2).decl.variable.value.intVal);
        return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", ">", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")); 
        return createVariable("", Bool);
    }
}

/* Return an attribute with the greater or equal comparison operation applied to oper1 and oper2. */
Attribute* returnGEqualComparison(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && getAttributeType(oper2) != Bool) 
    {
        Attribute *aux = createVariable("", Bool);
        if (getAttributeType(oper1) == Float)
            (*aux).decl.variable.value.boolVal = ((*oper1).decl.variable.value.floatVal) >= ((*oper1).decl.variable.value.floatVal);
        if (getAttributeType(oper1) == Int)
            (*aux).decl.variable.value.boolVal = ((*oper1).decl.variable.value.intVal) >= ((*oper1).decl.variable.value.intVal);
        return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", ">=", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")); 
        return createVariable("", Bool);
    }
}

/* Return an attribute with the less or equal comparison operation applied to oper1 and oper2. */
Attribute* returnLEqualComparison(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && getAttributeType(oper2) != Bool) 
    {
        Attribute *aux = createVariable("", getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
            (*aux).decl.variable.value.floatVal = ((*oper1).decl.variable.value.floatVal) <= ((*oper2).decl.variable.value.floatVal);
        if (getAttributeType(oper1) == Int)
            (*aux).decl.variable.value.intVal = ((*oper1).decl.variable.value.intVal) <= ((*oper2).decl.variable.value.intVal);
        return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", "<=", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")); 
        return createVariable("", Bool);
    }
}
/* ---------------------------------------relation no-terminal ended---------------------------------------- */

/* ---------------------------------------term no-terminal ------------------------------------------------ */

/* Return an attribute with the add operation. */
Attribute* returnAdd(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) != Bool))
    {
        Attribute *aux = createVariable("", getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
            (*aux).decl.variable.value.floatVal = ((*oper1).decl.variable.value.floatVal) + ((*oper2).decl.variable.value.floatVal);
        if (getAttributeType(oper1) == Int)
            (*aux).decl.variable.value.intVal = ((*oper1).decl.variable.value.intVal) + ((*oper2).decl.variable.value.intVal);
        return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", "+", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")); 
        return createVariable("", Int);
    }
}

/* Return an attribute with the sub operation. */
Attribute* returnSub(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) != Bool))
    {
        Attribute *aux = createVariable("", getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
            (*aux).decl.variable.value.floatVal = ((*oper1).decl.variable.value.floatVal) - ((*oper2).decl.variable.value.floatVal);
        if (getAttributeType(oper1) == Int)
            (*aux).decl.variable.value.intVal = ((*oper1).decl.variable.value.intVal) - ((*oper2).decl.variable.value.intVal);
        return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", "-", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")); 
        return createVariable("", Int);
    }
}

/* Return an attribute with the mod operation. */
Attribute* returnMod(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) == Int))
    {
        Attribute *aux = createVariable("", getAttributeType(oper1));
        if (getAttributeType(oper1) == Int)
            (*aux).decl.variable.value.intVal = ((*oper1).decl.variable.value.intVal) % ((*oper2).decl.variable.value.intVal);
        return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", "%", "\" solo soporta tipo INT y/o no tiene ambos operandos del mismo tipo.")); 
        return createVariable("", Int);
    }
}

/* Return an attribute with the div operation. */
Attribute* returnDiv(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) != Bool))
    {
        Attribute *aux = createVariable("", getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
            (*aux).decl.variable.value.intVal = ((*oper1).decl.variable.value.floatVal) / ((*oper2).decl.variable.value.floatVal);
        if (getAttributeType(oper1) == Int)
            (*aux).decl.variable.value.intVal = ((*oper1).decl.variable.value.intVal) / ((*oper2).decl.variable.value.intVal);
        return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", "/", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")); 
        return createVariable("", Int);
    }
}

/* Return an attribute with the mult operation. */
Attribute* returnMult(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) != Bool))
    {
        Attribute *aux = createVariable("", getAttributeType(oper1));
        if (getAttributeType(oper1) == Int)
            (*aux).decl.variable.value.intVal = ((*oper1).decl.variable.value.intVal) * ((*oper2).decl.variable.value.intVal);
            (*aux).decl.variable.value.floatVal = ((*oper1).decl.variable.value.floatVal) * ((*oper2).decl.variable.value.floatVal);
        return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", "*", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")); 
        return createVariable("", Int);
    }
}

/* ---------------------------------------term no-terminal ended----------------------------------------- */
