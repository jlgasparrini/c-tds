/*
	Implementation of Attribute.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Attribute.h"

static int globalVarOffset = -8;
static int globalParamOffset = 16;

/* Creates a StVariable with the respective type and initialized */
StVariable createStVariable(PrimitiveType type)
{
	StVariable var; 
	var.type = type;
	if (type == Int)
		var.value.intVal = 0;
	if (type == Float)
		var.value.floatVal = 0.0;
	if (type == Bool)
		var.value.boolVal = False;
	return var;
}

/* creates a variable attribute containing the information included in the parameters */
Attribute* createVariable(char *id, PrimitiveType type)
{
	Attribute *attr = (Attribute*) malloc (sizeof(Attribute)); 
	(*attr).type = Variable;
	(*attr).decl.variable = (StVariable*) malloc (sizeof(StVariable));
	*(*attr).decl.variable = createStVariable(type);
	(*(*attr).decl.variable).id = strdup(id);
	(*(*attr).decl.variable).offset = getGlobalVarOffset();
    printf("Offset of variable \"%s\": %d\n", id, getGlobalVarOffset());
    decreaseVarOffset();
	return attr;
}

/* creates an array attribute containing the information included in the parameters */
Attribute* createArray(char *id, PrimitiveType type, unsigned int length)
{
	Attribute *attr = (Attribute*) malloc (sizeof(Attribute)); 
	(*attr).type = Array;
	(*attr).decl.array.id = strdup(id);
	(*attr).decl.array.type = type; 
	(*attr).decl.array.length = length;
	(*attr).decl.array.arrayValues = (StVariable*) malloc (length*sizeof(StVariable)); /* creates the necessary memory for the array */
	int i;
    printf("Offsets of array \"%s\":\n", id);
	for(i = 0; i < length; i++)
	{	// Initializes all the values of the array
        printf("Offset of %d° position of array \"%s\": %d\n", i, id, getGlobalVarOffset());
		(*attr).decl.array.arrayValues[i] = createStVariable(type);
        (*attr).decl.array.arrayValues[i].offset = getGlobalVarOffset();
        decreaseVarOffset();
	}
	return attr;
}

/* creates a method attribute containing the information included in the parameters */
Attribute* createMethod(char *id, ReturnType type)
{
	Attribute *attr = (Attribute*) malloc (sizeof(Attribute)); 
	(*attr).type = Method;
	(*attr).decl.method.id = strdup(id);
	(*attr).decl.method.type = type; 
	(*attr).decl.method.paramSize = 0;
	(*attr).decl.method.parameters = NULL;
	return attr;
}

/* creates an attribute and assign it as a parameter of "method" containing the information included.
	Returns a pointer to the attribute if the parameter was created successful. Returns NULL otherwise. */
Attribute* createParameter(Attribute *attr, unsigned int pos, char *id, PrimitiveType type)
{
	if (attr != NULL && (*attr).type == Method)
	{
		StVariable **auxParameters = (StVariable**) realloc ((*attr).decl.method.parameters, (pos+1)*sizeof(StVariable*));
        // ver por que funciona de las dos maneras
		//StVariable **auxParameters = (StVariable**) realloc ((*attr).decl.method.parameters, (pos+1)*sizeof(StVariable));
		if (auxParameters != NULL)
		{
            printf("Offset of %d° variable parameter \"%s\": %d\n", pos, id, globalParamOffset);
			(*attr).decl.method.parameters = auxParameters;
			Attribute *aux = createVariable(id, type);
			(*(*aux).decl.variable).offset = globalParamOffset-4;;
			globalParamOffset += 4;
            (*attr).decl.method.parameters[pos] = (StVariable*) malloc(sizeof(StVariable));
			(*attr).decl.method.parameters[pos] = (*aux).decl.variable;
			return aux;
		}
	}
	return NULL; /* In case of non-desirable cases, Null is returned. This case is treated later. */
}

/* Sets the amount of parameters that will have the method attr */
void setAmountOfParameters(Attribute *attr, unsigned int amount)
{
    if ((*attr).type == Method)
		(*attr).decl.method.paramSize = amount;
}

/* Sets the value of the variable that contains "attr" with the respective "value" */
void setVariableValue(Attribute *attr, PrimitiveType type, char *value)
{
	if (type == Int)
		setIntVal(attr,atoi(value));
	if (type == Float)
		setFloatVal(attr,atof(value));
	if (type == Bool)
	{
		if (strcmp(value, "false") == 0)
			setBoolVal(attr,False);
		if (strcmp(value, "true") == 0)
			setBoolVal(attr,True);
	}
}

/* Returns the ID of the specified attribute */
char* getID(Attribute *attr)
{
	if ((*attr).type == Variable)
		return (*(*attr).decl.variable).id;
	if ((*attr).type == Method)
		return (*attr).decl.method.id;
	if ((*attr).type == Array)
		return (*attr).decl.array.id;
}

/* Returns the intVal of the attribute */
int getIntVal(Attribute *attr)
{
	if ((*attr).type == Variable)
		return (*(*attr).decl.variable).value.intVal;
	if ((*attr).type == Method)
		return (*attr).decl.method.returnValue.intVal;
}

/* Returns the floatVal of the attribute */
float getFloatVal(Attribute *attr)
{
	if ((*attr).type == Variable)
		return (*(*attr).decl.variable).value.floatVal;
	if ((*attr).type == Method)
		return (*attr).decl.method.returnValue.floatVal;
}

/* Returns the boolVal of the attribute */
Boolean getBoolVal(Attribute *attr)
{
	if ((*attr).type == Variable)
		return (*(*attr).decl.variable).value.boolVal;
	if ((*attr).type == Method)
		return (*attr).decl.method.returnValue.boolVal;
}

/* Returns the intVal of the array attribute in the "pos" position */
int getArrayIntVal(Attribute *attr, unsigned int pos)
{
	return (*attr).decl.array.arrayValues[pos].value.intVal;
}

/* Returns the floatVal of the array attribute in the "pos" position */
float getArrayFloatVal(Attribute *attr, unsigned int pos)
{
	return (*attr).decl.array.arrayValues[pos].value.floatVal;
}

/* Returns the boolVal of the array attribute in the "pos" position */
Boolean getArrayBoolVal(Attribute *attr, unsigned int pos)
{
	return (*attr).decl.array.arrayValues[pos].value.boolVal;
}

/* Returns the offset of the variable */
int getOffsetVal(Attribute *attr)
{
	return (*(*attr).decl.variable).offset;
}

/* Returns the offset of the array -the last position's offset- */
int getOffsetArray(Attribute *attr)
{
	return (*attr).decl.array.arrayValues[ (*attr).decl.array.length - 1 ].offset;
}

/* Sets the intVal of the attribute */
void setIntVal(Attribute *attr, int value)
{
	if ((*attr).type == Variable)
		(*(*attr).decl.variable).value.intVal = value;
	if ((*attr).type == Method)
		(*attr).decl.method.returnValue.intVal = value;
}

/* Sets the floatVal of the attribute */
void setFloatVal(Attribute *attr, float value)
{
	if ((*attr).type == Variable)
		(*(*attr).decl.variable).value.floatVal = value;
	if ((*attr).type == Method)
		(*attr).decl.method.returnValue.floatVal = value;
}

/* Sets the boolVal of the attribute */
void setBoolVal(Attribute *attr, Boolean value)
{
	if ((*attr).type == Variable)
		(*(*attr).decl.variable).value.boolVal = value;
	if ((*attr).type == Method)
		(*attr).decl.method.returnValue.boolVal = value;
}

/* Sets the intVal of the array attribute in the "pos" position */
void setArrayIntVal(Attribute *attr, unsigned int pos, int value)
{
	(*attr).decl.array.arrayValues[pos].value.intVal = value;
}

/* Sets the floatVal of the array attribute in the "pos" position */
void setArrayFloatVal(Attribute *attr, unsigned int pos, float value)
{
	(*attr).decl.array.arrayValues[pos].value.floatVal = value;
}

/* Sets the boolVal of the array attribute in the "pos" position */
void setArrayBoolVal(Attribute *attr, unsigned int pos, Boolean value)
{
	(*attr).decl.array.arrayValues[pos].value.boolVal = value;
}

/* Returns the global variable offset of the class */
int getGlobalVarOffset()
{
	return globalVarOffset;
}

/* Set the global variable offset of the class */
void setGlobalVarOffset(int newOffset)
{
	globalVarOffset = newOffset;
}

/* Set the global variable offset of the class in a -16 */
void resetGlobalVarOffset()
{
	globalVarOffset = -8;
}

/* Increases in 4 the variable's offset */
void increaseVarOffset()
{
    globalVarOffset += 4;
}

/* Decreases in 4 the variable's offset */
void decreaseVarOffset()
{
    globalVarOffset -= 4;
}

/* Returns the global parameters offset of the class */
int getGlobalParamOffset()
{
	return globalVarOffset;
}

/* Set the global parameters offset of the class */
void setGlobalParamOffset(int newOffset)
{
	globalVarOffset = newOffset;
}

/* Set the global parameters offset of the class in a 8 */
void resetGlobalParamOffset()
{
	globalVarOffset = 16;
}

/* Returns the structure type of the attribute.
 * Return 0 if it's a variable 
 * Return 1 if it's a method 
 * Return 2 if it's an array */
StructureType getStructureType(Attribute *attr)
{
    return (*attr).type;
}
