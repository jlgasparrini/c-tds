/*
	Implementation of Attribute.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Attribute.h"

static int globalVarOffset = -8;
static int globalParamOffset = 24;

/* Creates a StVariable with the respective type and initialized */
StVariable create_st_variable(PrimitiveType type)
{
	StVariable var; 
	var.type = type;
	switch (type) {
	    case Int: var.value.intVal = 0;
	              break;
	    case Float: var.value.floatVal = 0.0;
	                break;
	    case Bool: var.value.boolVal = False;
	               break;
  	}
	return var;
}

/* creates a variable attribute containing the information included in the parameters */
Attribute* create_variable(char *id, PrimitiveType type)
{
	Attribute *attr = (Attribute*) malloc (sizeof(Attribute)); 
	attr->type = Variable;
	attr->decl.variable = (StVariable*) malloc (sizeof(StVariable));
	*attr->decl.variable = create_st_variable(type);
	attr->id = strdup(id);
	attr->decl.variable->offset = get_global_var_offset();
  	decrease_var_offset();
	return attr;
}

/* creates an array attribute containing the information included in the parameters */
Attribute* create_array(char *id, PrimitiveType type, unsigned int length)
{
	Attribute *attr = (Attribute*) malloc (sizeof(Attribute)); 
	attr->type = Array;
	attr->id = strdup(id);
	attr->decl.array.type = type; 
	attr->decl.array.length = length;
	attr->decl.array.arrayValues = (StVariable*) malloc (length*sizeof(StVariable)); /* creates the necessary memory for the array */
	int i;
	for(i = 0; i < length; i++)
	{	// Initializes all the values of the array
		attr->decl.array.arrayValues[i] = create_st_variable(type);
        attr->decl.array.arrayValues[i].offset = get_global_var_offset();
        decrease_var_offset();
	}
	return attr;
}

/* creates a method attribute containing the information included in the parameters */
Attribute* create_method(char *id, ReturnType type)
{
	Attribute *attr = (Attribute*) malloc (sizeof(Attribute)); 
	attr->type = Method;
	attr->id = strdup(id);
	attr->decl.method.type = type; 
	attr->decl.method.paramSize = 0;
	attr->decl.method.parameters = NULL;
	return attr;
}

/* creates an attribute and assign it as a parameter of "method" containing the information included.
	Returns a pointer to the attribute if the parameter was created successful. Returns NULL otherwise. */
Attribute* create_parameter(Attribute *attr, unsigned int pos, char *id, PrimitiveType type)
{
	if (attr != NULL && attr->type == Method)
	{
		StVariable **auxParameters = (StVariable**) realloc (attr->decl.method.parameters, (pos+1)*sizeof(StVariable*));
		if (auxParameters != NULL)
		{
			attr->decl.method.parameters = auxParameters;
			attr->decl.method.paramSize++;
			Attribute *aux = create_variable(id, type);
			aux->decl.variable->offset = globalParamOffset-4;;
			globalParamOffset += 4;
      		attr->decl.method.parameters[pos] = (StVariable*) malloc(sizeof(StVariable));
			attr->decl.method.parameters[pos] = aux->decl.variable;
			return aux;
		}
	}
	return NULL; /* In case of non-desirable cases, Null is returned. This case is treated later. */
}

/* Sets the amount of parameters that will have the method attr */
void set_amount_of_parameters(Attribute *attr, unsigned int amount)
{
    if (attr->type == Method)
		attr->decl.method.paramSize = amount;
}

/* Sets the value of the variable that contains "attr" with the respective "value" */
void set_variable_value(Attribute *attr, PrimitiveType type, char *value)
{
  switch (type) {
    case Int:	set_int_val(attr,atoi(value));
              break;
    case Float:	set_float_val(attr,atof(value));
                break;
    case Bool:	if (strcmp(value, "false") == 0)
                    set_bool_val(attr,False);
             		if (strcmp(value, "true") == 0)
               			set_bool_val(attr,True);
                break;
  }
}

/* Returns the ID of the specified attribute */
char* get_id(Attribute *attr)
{
  switch (attr->type) {
    case Variable: return attr->id;
    case Method: return attr->id;
	case Array:	return attr->id;
	default: return NULL;
  }
}

/* Returns the intVal of the attribute */
int get_int_val(Attribute *attr)
{
  switch (attr->type) {
    case Variable: return attr->decl.variable->value.intVal;
    case Method: return attr->decl.method.return_value.intVal;
    default: return -1;
  }
}

/* Returns the floatVal of the attribute */
float get_float_val(Attribute *attr)
{
	if (attr->type == Variable)
		return attr->decl.variable->value.floatVal;
	if (attr->type == Method)
		return attr->decl.method.return_value.floatVal;
	return -1;
}

/* Returns the boolVal of the attribute */
Boolean get_bool_val(Attribute *attr)
{
	if (attr->type == Variable)
		return attr->decl.variable->value.boolVal;
	if (attr->type == Method)
		return attr->decl.method.return_value.boolVal;
	return False;
}

/* Returns the intVal of the array attribute in the "pos" position */
int get_array_int_val(Attribute *attr, unsigned int pos)
{
	return attr->decl.array.arrayValues[pos].value.intVal;
}

/* Returns the floatVal of the array attribute in the "pos" position */
float get_array_float_val(Attribute *attr, unsigned int pos)
{
	return attr->decl.array.arrayValues[pos].value.floatVal;
}

/* Returns the boolVal of the array attribute in the "pos" position */
Boolean get_array_bool_val(Attribute *attr, unsigned int pos)
{
	return attr->decl.array.arrayValues[pos].value.boolVal;
}

/* Returns the offset of the variable */
int get_offset_val(Attribute *attr)
{
	return attr->decl.variable->offset;
}

/* Returns the offset of the array -the last position's offset- */
int get_offset_array(Attribute *attr)
{
	return attr->decl.array.arrayValues[ attr->decl.array.length - 1 ].offset;
}

/* Sets the intVal of the attribute */
void set_int_val(Attribute *attr, int value)
{
	if (attr->type == Variable)
		attr->decl.variable->value.intVal = value;
	if (attr->type == Method)
		attr->decl.method.return_value.intVal = value;
}

/* Sets the floatVal of the attribute */
void set_float_val(Attribute *attr, float value)
{
	if (attr->type == Variable)
		attr->decl.variable->value.floatVal = value;
	if (attr->type == Method)
		attr->decl.method.return_value.floatVal = value;
}

/* Sets the boolVal of the attribute */
void set_bool_val(Attribute *attr, Boolean value)
{
	if (attr->type == Variable)
		attr->decl.variable->value.boolVal = value;
	if (attr->type == Method)
		attr->decl.method.return_value.boolVal = value;
}

/* Sets the intVal of the array attribute in the "pos" position */
void set_array_int_val(Attribute *attr, unsigned int pos, int value)
{
	attr->decl.array.arrayValues[pos].value.intVal = value;
}

/* Sets the floatVal of the array attribute in the "pos" position */
void set_array_float_val(Attribute *attr, unsigned int pos, float value)
{
	attr->decl.array.arrayValues[pos].value.floatVal = value;
}

/* Sets the boolVal of the array attribute in the "pos" position */
void set_array_bool_val(Attribute *attr, unsigned int pos, Boolean value)
{
	attr->decl.array.arrayValues[pos].value.boolVal = value;
}

/* Returns the global variable offset of the class */
int get_global_var_offset()
{
	return globalVarOffset;
}

/* Set the global variable offset of the class */
void set_global_var_offset(int newOffset)
{
	globalVarOffset = newOffset;
}

/* Set the global variable offset of the class in a -16 */
void reset_global_var_offset()
{
	globalVarOffset = -4;
}

/* Increases in 4 the variable's offset */
void increase_var_offset()
{
    globalVarOffset += 4;
}

/* Decreases in 4 the variable's offset */
void decrease_var_offset()
{
    globalVarOffset -= 4;
}

/* Returns the global parameters offset of the class */
int get_global_param_offset()
{
	return globalVarOffset;
}

/* Set the global parameters offset of the class */
void set_global_param_offset(int newOffset)
{
	globalVarOffset = newOffset;
}

/* Set the global parameters offset of the class in a 8 */
void reset_global_param_offset()
{
	globalVarOffset = 16;
}

/* Returns the structure type of the attribute.
 * Return 0 if it's a variable 
 * Return 1 if it's a method 
 * Return 2 if it's an array */
StructureType get_structure_type(Attribute *attr)
{
    return attr->type;
}

/* Returns the type of the attribute, although it is a variable, array or method */
ReturnType get_attribute_type(Attribute *attr)
{
    switch (get_structure_type(attr))
    {
        case Variable:  return attr->decl.variable->type;
        case Array:     return attr->decl.array.type;
        case Method:    return attr->decl.method.type;
        default:        return RetInt;
    }
}

/* Returns the string corresponding to "type" */
char* get_type(PrimitiveType type)
{
    switch (type)
    {
        case Int:   return "int";
        case Float: return "float";
        case Bool:  return "bool";
        default:    return "wrong type"; // This is returned when it's not a primitive type
    }
}
