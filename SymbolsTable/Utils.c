#include <stdio.h>
#include <math.h>
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
/* Return 1 if ocurred one error, or 0 if all type is ok*/
unsigned char controlType(ErrorsQueue *eq, Attribute *attr, PrimitiveType type)
{
    if (getAttributeType(attr) != type){
        insertError(eq, toString("La expresion no es del tipo \"", getType(type), "\"."));
		return 1;
	}
	return 0;
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
/* Return 1 if ocurred one error, or 0 if all type is ok*/
unsigned char checkReturnExpression(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* lastUsedMethod, Attribute *attr)
{
	ReturnType rt = methodReturnType(eq, aSymbolsTable, lastUsedMethod);
	if (rt == RetVoid)
    {
		insertError(eq,toString("El metodo \"",lastUsedMethod,"\" no puede retornar una expresion ya que retorna void."));
		return 1;
    }
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
			return 1;
	//		free(msg);
		}
		return 0;
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
/* Insert a new code3D OR in a list of Codes */
Attribute* returnOr(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) == Bool)) // TYPE CHECK
    {
        Code3D *codeOr = newCode(COM_OR);
		setCode3D(codeOr, oper1, oper2, operRes);
		add_code(lcode3d, codeOr); 
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
/* Insert a new code3D And in a list of Codes */
Attribute* returnAnd(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) == Bool))
    {
		Code3D *codeAnd = newCode(COM_AND);
		setCode3D(codeAnd, oper1, oper2, operRes);
		add_code(lcode3d, codeAnd); 
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
/* Insert a new code3D Distinct in a list of Codes */
Attribute* returnDistinct(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes)
{
    if (getAttributeType(oper1) == getAttributeType(oper2)) 
    {
        Code3D *codeDist = newCode(COM_DIST);
		setCode3D(codeDist, oper1, oper2, operRes);
		add_code(lcode3d, codeDist);
		Attribute *aux = createVariable("", Bool);
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
		insertError(eq, toString("El operador \"", "!=", "\" no tiene ambos operandos del mismo tipo.")); 
        return createVariable("", Bool);
    }
}

/* Return an attribute with the equal operation applied to oper1 and oper2. */
/* Insert a new code3D Equal in a list of Codes */
Attribute* returnEqual(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes)
{
    if (getAttributeType(oper1) == getAttributeType(oper2)) 
    {
        Code3D *codeEqual = newCode(COM_EQ);
		setCode3D(codeEqual, oper1, oper2, operRes);
		add_code(lcode3d, codeEqual); 
		Attribute *aux = createVariable("", Bool);
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
		insertError(eq, toString("El operador \"", "==", "\" no tiene ambos operandos del mismo tipo.")); 
        return createVariable("", Bool);
    }
}
/* ------------------------------------inequality and comparison no-terminal ended---------------------------------------- */

/* ---------------------------------------relation no-terminal ------------------------------------------------ */

/* Return an attribute with the minor comparison operation applied to oper1 and oper2. */
/* Insert a new code3D MinorComparison in a list of Codes */
Attribute* returnMinorComparison(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes)
{
    if ((getAttributeType(oper1) == getAttributeType(oper2)) && (getAttributeType(oper2) != Bool)) 
    {
		Code3D *codeMinor = newCode(COM_LR);
		setCode3D(codeMinor, oper1, oper2, operRes);
		add_code(lcode3d, codeMinor); 
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
/* Insert a new code3D MajorComparison in a list of Codes */
Attribute* returnMajorComparison(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes)
{
    if ((getAttributeType(oper1) == getAttributeType(oper2)) && (getAttributeType(oper2) != Bool))
    {
        Code3D *codeGreat = newCode(COM_GT);
		setCode3D(codeGreat, oper1, oper2, operRes);
		add_code(lcode3d, codeGreat); 
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
/* Insert a new code3D GEqualComparison in a list of Codes */
Attribute* returnGEqualComparison(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes)
{
    if ((getAttributeType(oper1) == getAttributeType(oper2)) && (getAttributeType(oper2) != Bool))
    {
        Code3D *codeGEqual = newCode(COM_GEQ);
		setCode3D(codeGEqual, oper1, oper2, operRes);
		add_code(lcode3d, codeGEqual);
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
/* Insert a new code3D LEqualComparison in a list of Codes */
Attribute* returnLEqualComparison(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes)
{
    if ((getAttributeType(oper1) == getAttributeType(oper2)) && (getAttributeType(oper2) != Bool))
    {
        Code3D *codeLEqual = newCode(COM_LEQ);
		setCode3D(codeLEqual, oper1, oper2, operRes);
		add_code(lcode3d, codeLEqual); 
		Attribute *aux = createVariable("", getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
            (*aux).decl.variable.value.boolVal = ((*oper1).decl.variable.value.floatVal) <= ((*oper2).decl.variable.value.floatVal);
        if (getAttributeType(oper1) == Int)
            (*aux).decl.variable.value.boolVal = ((*oper1).decl.variable.value.intVal) <= ((*oper2).decl.variable.value.intVal);
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
/* Insert a new code3D Add in a list of Codes */
Attribute* returnAdd(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes)
{
    if ((getAttributeType(oper1) == getAttributeType(oper2)) && (getAttributeType(oper2) != Bool))
    {
        Code3D *codeAdd;
        Attribute *aux = createVariable("", getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
		{
			codeAdd = newCode(COM_ADD_FLOAT);
            (*aux).decl.variable.value.floatVal = ((*oper1).decl.variable.value.floatVal) + ((*oper2).decl.variable.value.floatVal);
        }
		if (getAttributeType(oper1) == Int)
		{
			codeAdd = newCode(COM_ADD_INT);
            (*aux).decl.variable.value.intVal = ((*oper1).decl.variable.value.intVal) + ((*oper2).decl.variable.value.intVal);
        }
		setCode3D(codeAdd, oper1, oper2, operRes);
		add_code(lcode3d, codeAdd);
		return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", "+", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")); 
        return createVariable("", Int);
    }
}

/* Return an attribute with the sub operation. */
/* Insert a new code3D Sub in a list of Codes */
Attribute* returnSub(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) != Bool))
    {
        Code3D *codeSub;
        Attribute *aux = createVariable("", getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
        {    
			codeSub = newCode(COM_MINUS_FLOAT);
			(*aux).decl.variable.value.floatVal = ((*oper1).decl.variable.value.floatVal) - ((*oper2).decl.variable.value.floatVal);
        }
		if (getAttributeType(oper1) == Int)
        {
			codeSub = newCode(COM_MINUS_INT);											
			(*aux).decl.variable.value.intVal = ((*oper1).decl.variable.value.intVal) - ((*oper2).decl.variable.value.intVal);
        }
		setCode3D(codeSub, oper1, oper2, operRes);
		add_code(lcode3d, codeSub); 
		return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", "-", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")); 
        return createVariable("", Int);
    }
}

/* Return an attribute with the mod operation. */
/* Insert a new code3D Mod in a list of Codes */
Attribute* returnMod(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) != Bool)) // ver por que solamente toma int
    {
        Code3D *codeMod;
        Attribute *aux = createVariable("", getAttributeType(oper1));
		if (getAttributeType(oper1) == Float)
        {    
			codeMod = newCode(COM_MOD_FLOAT);
			(*aux).decl.variable.value.floatVal = fmod(((*oper1).decl.variable.value.floatVal), ((*oper2).decl.variable.value.floatVal));
        }
        if (getAttributeType(oper1) == Int)
        {
			codeMod = newCode(COM_MOD_INT);
			(*aux).decl.variable.value.intVal = ((*oper1).decl.variable.value.intVal) % ((*oper2).decl.variable.value.intVal);
        }
		setCode3D(codeMod, oper1, oper2, operRes);
		add_code(lcode3d, codeMod); 
		return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", "%", "\" solo soporta tipo INT y/o no tiene ambos operandos del mismo tipo."));//debe soportar el Float ahora
        return createVariable("", Int);
    }
}

/* Return an attribute with the div operation. */
/* Insert a new code3D Div in a list of Codes */
Attribute* returnDiv(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) != Bool))
    {
        Code3D *codeDiv;
        Attribute *aux = createVariable("", getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
        {    
			codeDiv = newCode(COM_DIV_FLOAT);
			(*aux).decl.variable.value.intVal = ((*oper1).decl.variable.value.floatVal) / ((*oper2).decl.variable.value.floatVal);
        }
		if (getAttributeType(oper1) == Int)
		{
			codeDiv = newCode(COM_DIV_INT);
            (*aux).decl.variable.value.intVal = ((*oper1).decl.variable.value.intVal) / ((*oper2).decl.variable.value.intVal);
        }
		setCode3D(codeDiv, oper1, oper2, operRes);
		add_code(lcode3d, codeDiv);
		return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", "/", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")); 
        return createVariable("", Int);
    }
}

/* Return an attribute with the mult operation. */
/* Insert a new code3D Mult in a list of Codes */
Attribute* returnMult(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) != Bool))
    {
        Code3D *codeMult;
        Attribute *aux = createVariable("", getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
		{
			codeMult = newCode(COM_MULT_FLOAT);
		    (*aux).decl.variable.value.floatVal = ((*oper1).decl.variable.value.floatVal) * ((*oper2).decl.variable.value.floatVal);
		}
		if (getAttributeType(oper1) == Int)
		{	
			codeMult = newCode(COM_MULT_INT);
            (*aux).decl.variable.value.intVal = ((*oper1).decl.variable.value.intVal) * ((*oper2).decl.variable.value.intVal);
        }
		setCode3D(codeMult, oper1, oper2, operRes);
		add_code(lcode3d, codeMult);
		return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", "*", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")); 
        return createVariable("", Int);
    }
}

/* Return an attribute with the not operation applied to oper1. */
/* Insert a new code3D Not in a list of Codes */
Attribute* returnNot(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *operRes)
{
    if (getAttributeType(oper1) == Bool)
    {
		Code3D *codeNot = newCode(COM_NOT);
		setCode2D(codeNot, oper1, operRes);
		add_code(lcode3d, codeNot); 
		Attribute *aux = createVariable("", Bool);			
		(*aux).decl.variable.value.boolVal = !((*oper1).decl.variable.value.floatVal);
		return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", "!", "\" no tiene el operando de tipo booleano.")); 
        return createVariable("", Bool);
    }
}

/* Return an attribute with the neg operation applied to oper1. */
/* Insert a new code3D Neg in a list of Codes */
Attribute* returnNeg(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *operRes)
{
    if (getAttributeType(oper1) == Int || getAttributeType(oper1) == Float)
    {
        Code3D *codeNeg;
        Attribute *aux = createVariable("", getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
		{
			codeNeg = newCode(COM_NEG_FLOAT);
		    (*aux).decl.variable.value.floatVal = -((*oper1).decl.variable.value.floatVal);
		}
		if (getAttributeType(oper1) == Int)
		{	
			codeNeg = newCode(COM_NEG_INT);
            (*aux).decl.variable.value.intVal = -((*oper1).decl.variable.value.intVal);
        }
		setCode2D(codeNeg, oper1, operRes);
		add_code(lcode3d, codeNeg);
		return aux;
    }
    else
    {
		insertError(eq, toString("El operador \"", "-", "\" no tiene el operando de tipo Int o Float.")); 
        return createVariable("", Int);
    }
}

/* ---------------------------------------term no-terminal ended----------------------------------------- */

/* ---------------------------------------term terminal ------------------------------------------------- */

/* Return an attribute with the type equal to param type and value equal to  param oper1. */
/* Insert a new code3D Int or Float or Bool in a list of Codes */
Attribute* returnValue(LCode3D *lcode3d, PrimitiveType type, char *oper1, Attribute *operRes)
{
	Code3D *codeValue = newCode(LOAD_CONST);
	if (type == Int)
		setInt(codeValue, 1, atoi(oper1));
	if (type == Float)
		setFloat(codeValue, 1, atof(oper1));
	if (type == Bool)
	{
		if (strcmp(oper1, "false") == 0)
			setBool(codeValue, 1, False);
		if (strcmp(oper1, "true") == 0)
			setBool(codeValue, 1, True);		
	}
	setAttribute(codeValue, 2, operRes);
	setNull(codeValue, 3);
	add_code(lcode3d, codeValue);	
	Attribute *aux = createVariable("", type); 
	setVariableValue(aux, type, oper1);
	return aux;
}

/* ---------------------------------------term terminal ended-------------------------------------------- */
