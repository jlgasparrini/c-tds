/*
 * MISSING DOCUMENTATION!
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "Utils.h"

#define temp ".temp"
unsigned int numberOfVariable = 0;

/* Creates a name for a temporary variable */
char* getVariableName()
{
    char *name = (char*) malloc ((strlen(temp)+digitAmount(numberOfVariable))*sizeof(char));
    strcat(name,temp);
    strcat(name,intToString(numberOfVariable));
    numberOfVariable++;
    return name;
}

/* Returns an attribute of ID "id" and Variable structure. Otherwise returns NULL */
Attribute* getVariableAttribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id)
{
    Attribute *attr = searchIdInSymbolsTable(eq, aSymbolsTable, id);
    if(attr != NULL)
    {
        if(getStructureType(attr) != Variable)
            insert_error(eq, to_string("El identificador \"", id, "\" no corresponde a una variable."));
        else
            return attr;
    }
    return createVariable(getVariableName(),Int); // Returns an attribute with type Int to continue parsing
}

/* Returns the return attribute of the method with id "id" */
Attribute* getMethodReturnAttribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id)
{
    Attribute *attr = searchIdInSymbolsTable(eq, aSymbolsTable, id);
    if(attr != NULL)
    {
        if(getStructureType(attr) != Method)
            insert_error(eq,to_string("El identificador \"", id,"\" no corresponde a un metodo."));
        else
        {
            if (getAttributeType(attr) == RetVoid)
                insert_error(eq,to_string("El metodo \"", id,"\" retorna void, no puede setearse ningun atributo de retorno."));
            else
            {
                Attribute *aux = createVariable(getVariableName(), getAttributeType(attr));
                if (getAttributeType(attr) == Int)
                    setIntVal(aux,getIntVal(attr));
                if (getAttributeType(attr) == Float)
                    setFloatVal(aux,getFloatVal(attr));
                if (getAttributeType(attr) == Bool)
                    setBoolVal(aux,getIntVal(attr));
                return aux;
            }
        }
    }
    return createVariable(getVariableName(),Int); // Returns type Int by default in case of having errors
}

/* Sets the return attribute of the method with id "id" */
void setMethodReturnAttribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id, StVariable *value)
{
    Attribute *attr = searchIdInSymbolsTable(eq, aSymbolsTable, id);
    if(attr != NULL)
    {
        if(getStructureType(attr) != Method)
            insert_error(eq,to_string("El identificador \"", id,"\" no corresponde a un metodo."));
        else
        {
            if (getAttributeType(attr) == RetVoid)
                insert_error(eq,to_string("El metodo \"", id,"\" retorna void, no puede setearse ningun atributo de retorno."));
            else
            {
                if ((*value).type == Int)
                    setIntVal(attr, (*value).value.intVal);
                if ((*value).type == Float)
                    setFloatVal(attr, (*value).value.floatVal);
                if ((*value).type == Bool)
                    setBoolVal(attr, (*value).value.boolVal);
            }
        }
    }
}

/* Returns the respective variable attribute that the method return. "paramSize" is for checking if the amount of parameters is right */
Attribute* checkAndGetMethodRetAttribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, LCode3D *lcode3d, char *id, unsigned char paramSize)
{
    Attribute *attr = searchIdInSymbolsTable(eq, aSymbolsTable, id);
    if (attr != NULL)
    {
        if (getStructureType(attr) != Method)
            insert_error(eq,to_string("El identificador \"", id,"\" no corresponde a un metodo."));
        else
        {
            if ((*attr).decl.method.paramSize != paramSize)
                insert_error(eq,to_string("El metodo \"", id,"\" no contiene la cantidad correspondiente de parametros."));
            else
            {
                Attribute *aux = createVariable(getVariableName(), getAttributeType(attr));
                if (getAttributeType(attr) != RetVoid)
                    add_Assignation(lcode3d, attr, aux);
                return aux;
            }
        }
    }
    return createVariable(getVariableName(),Int); // Returns type Int by default in case of having errors
}

/* Returns 0 if the type of the parameter on the position "pos" of the method "attr" is equal to the type of "var"
   Returns 1 otherwise */
unsigned char correctParameterType(StVariable *var, Attribute *attr, unsigned char pos)
{
    if ((*var).type == (*attr).decl.method.parameters[pos]->type)
        return 0;
    return 1;
}

/* Returns the ReturnType of the method with id "id" */
ReturnType methodReturnType(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id)
{
    Attribute *attr = searchIdInSymbolsTable(eq, aSymbolsTable, id);
    if(attr != NULL)
        if(getStructureType(attr) != Method)
            insert_error(eq, to_string("El identificador \"", id, "\" no corresponde a un metodo."));
        else
            return getAttributeType(attr);
    return RetInt; /* retorno por defecto el tipo int */
}

/* Returns the type of the attribute, although it is a variable, array or method */
ReturnType getAttributeType(Attribute *attr)
{
    if(getStructureType(attr) == Variable)
        return (*(*attr).decl.variable).type;
    if(getStructureType(attr) == Array)
        return (*attr).decl.array.type;
    if(getStructureType(attr) == Method)
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
    return "wrong type"; // This is returned when it's not a primitive type
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

/* Returns the string representation of the float "value" */
char* floatToString(float value)
{
    char *aux = (char*) malloc (sizeof(char)*100);
    sprintf(aux, "%f", value);
    return aux;
}

/* Returns 0 if the type parameter in "paramSize" position of the method's parameters is equal to the type of "var"
   and the amount of params are equal.
   Returns 1 otherwise */
void correctParamBC(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, LCode3D *lcode3d, Attribute *attr, char* lastCalledMethod, unsigned char paramSize)
{
    Attribute *aux = searchIdInSymbolsTable(eq, aSymbolsTable, lastCalledMethod);
    if(aux != NULL)
        if(getStructureType(aux) != Method)
            insert_error(eq, to_string("El identificador \"", lastCalledMethod, "\" no corresponde a un metodo."));
        else
        {
            if (paramSize+1 == (*aux).decl.method.paramSize)
            {
                if (correctParameterType((*attr).decl.variable, aux, paramSize) == 0)
                {
                    Attribute *param = (Attribute*) malloc (sizeof(Attribute));
                    param->decl.variable = (*aux).decl.method.parameters[paramSize]; // obtencion del parametro formal.
                    if (getAttributeType(attr) == Float)
                        add_MethodCall(lcode3d, newCode(PARAM_ASSIGN_FLOAT), attr, param);
                    if (getAttributeType(attr) == Int)
                        add_MethodCall(lcode3d, newCode(PARAM_ASSIGN_INT), attr, param);
                    if (getAttributeType(attr) == Bool)
                        add_MethodCall(lcode3d, newCode(PARAM_ASSIGN_BOOL), attr, param);
                }
                else
                {
                    char* number = (char*) malloc (digitAmount(paramSize+1)*sizeof(char));
                    sprintf(number,"%d",paramSize+1);
                    char* f = (char*) malloc ((strlen("\". El ")+strlen(number)+strlen("° parametro no es del tipo \"")+strlen(getType((*aux).decl.method.parameters[paramSize]->type)+strlen("\".")))*sizeof(char));
                    strcat(f,"\". El ");
                    strcat(f, number);
                    strcat(f,"° parametro no es del tipo \"");
                    strcat(f, getType((*aux).decl.method.parameters[paramSize]->type));
                    strcat(f, "\".");
                    insert_error(eq,to_string("Error en llamada al metodo \"", lastCalledMethod, f));
                    //	free(number);
                    //	free(f);
                }
            }
            else
                if (paramSize < (*aux).decl.method.paramSize)
                    insert_error(eq,to_string("Error en llamada al metodo \"", lastCalledMethod, "\". Se tiene menor cantidad de parametros que en su declaracion."));
                else
                    insert_error(eq,to_string("Error en llamada al metodo \"", lastCalledMethod, "\". Se tiene mayor cantidad de parametros que en su declaracion."));
        }
}

/* Returns 0 if the type parameter in "paramSize" position of the method's parameters is equal to the type of "var"
   and paramSize <= than the amount of parameters of the method.
   Returns 1 otherwise */
void correctParamIC(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, LCode3D *lcode3d, Attribute *attr, char* lastCalledMethod, unsigned char paramSize)
{
    Attribute *aux = searchIdInSymbolsTable(eq, aSymbolsTable, lastCalledMethod);
    if(aux != NULL)
        if(getStructureType(aux) != Method)
            insert_error(eq, to_string("El identificador \"", lastCalledMethod, "\" no corresponde a un metodo."));
        else
        {
            if (paramSize < (*aux).decl.method.paramSize)
            {
                if (correctParameterType((*attr).decl.variable, aux, paramSize) == 0)
                {
                    Attribute *param = (Attribute*) malloc (sizeof(Attribute));
                    param->decl.variable = (*aux).decl.method.parameters[paramSize]; // obtencion del parametro formal.
                    if (getAttributeType(attr) == Float)
                        add_MethodCall(lcode3d, newCode(PARAM_ASSIGN_FLOAT), attr, param);
                    if (getAttributeType(attr) == Int)
                        add_MethodCall(lcode3d, newCode(PARAM_ASSIGN_INT), attr, param);
                    if (getAttributeType(attr) == Bool)
                        add_MethodCall(lcode3d, newCode(PARAM_ASSIGN_BOOL), attr, param);
                }
            }
        }
}

void externParamAssign(LCode3D *lcode3d, Attribute *param, unsigned char paramNumber)
{
    if (getAttributeType(param) == Float)
        addParamExternInvk(lcode3d, newCode(EXTERN_PARAM_ASSIGN_FLOAT), param, paramNumber);
    if (getAttributeType(param) == Int)
        addParamExternInvk(lcode3d, newCode(EXTERN_PARAM_ASSIGN_INT), param, paramNumber);
    if (getAttributeType(param) == Bool)
        addParamExternInvk(lcode3d, newCode(EXTERN_PARAM_ASSIGN_BOOL), param, paramNumber);
}

/* Insert an error message if the attribute "attr" isn't a variable of type "type" */
/* Return 1 if ocurred one error, or 0 if all type is ok*/
unsigned char controlType(ErrorsQueue *eq, Attribute *attr, PrimitiveType type, char *operation, int numberOfExpression)
{
    if (getAttributeType(attr) != type){
        if (numberOfExpression == 1)
        {
            char* f = (char*) malloc ((strlen("La expresion de la sentencia \"")+strlen(operation)+strlen("\" no es del tipo \""))*sizeof(char));
            strcat(f,"La expresion de la sentencia \"");
            strcat(f, operation);
            strcat(f,"\" no es del tipo \"");
            insert_error(eq, to_string(f, getType(type), "\"."));
        }
        else
        {
            char* number = (char*) malloc (sizeof(char));
            sprintf(number,"%d",numberOfExpression);

            char* f = (char*) malloc ((strlen("La  ° expresion de la sentencia \"")+strlen(operation)+strlen("\" no es del tipo \""))*sizeof(char));
            strcat(f,"La ");
            strcat(f, number);
            strcat(f,"° expresion de la sentencia \"");
            strcat(f, operation);
            strcat(f,"\" no es del tipo \"");
            insert_error(eq, to_string(f, getType(type), "\"."));
        }
        return 1;
    }
    return 0;
}

/* Insert an error message and return 1 if attributes "attr1" and "attr2" aren't of the same type and both variables or arrays
   Returns 0 otherwise */
unsigned char controlAssignation(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *attr1, char* op, Attribute *attr2)
{
    if (getStructureType(attr1) != Method)
    {
        if (getAttributeType(attr1) != getAttributeType(attr2))
            insert_error(eq, to_string("El lado derecho de la asignacion debe ser de tipo \"", getType(getAttributeType(attr1)), "\"."));
        else
        {
            Code3D *add;
            if (strcmp(op, "=") == 0)
				add_Assignation(lcode3d, attr2, attr1);
            else
            {
                if (strcmp(op, "+=") == 0)
                {
                    if (getAttributeType(attr1) == Int)
                        add = newCode(ADD_INT);
                    if (getAttributeType(attr1) == Float)
                        add = newCode(ADD_FLOAT);
                }
                if (strcmp(op, "-=") == 0)
                {
                    if (getAttributeType(attr1) == Int)
                        add = newCode(MINUS_INT);
                    if (getAttributeType(attr1) == Float)
                        add = newCode(MINUS_FLOAT);
                }
                Attribute *res = createVariable(getVariableName(), getAttributeType(attr1));
                setCode3D(add, attr1, attr2, res);
                add_code(lcode3d, add);
				add_Assignation(lcode3d, res, attr1);
            }
            return 0;
        }
    }
    else
        insert_error(eq, to_string("El identificador izquierdo de la asignacion ", "", " no debe ser un metodo."));
    return 1;
}

/* Insert an error message if the "lastUsedMethod" haven't got "void" return type */
unsigned char checkReturn(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* lastUsedMethod)
{
    ReturnType rt = methodReturnType(eq, aSymbolsTable, lastUsedMethod);
    if (rt != RetVoid)
    {
        char* msg = (char*) malloc ((strlen("\" debe retornar una expresion de tipo \"")+strlen(getType(rt))+strlen("\"."))*sizeof(char));
        strcat(msg, "\" debe retornar una expresion de tipo \"");
        strcat(msg, getType(rt));
        strcat(msg, "\".");
        insert_error(eq, to_string("El metodo \"", lastUsedMethod, msg));
        //		free(msg);
        return 1;
    }
    return 0;
}

/* Insert an error message if the "lastUsedMethod" doesn't return "void" or if it has a different return type that the definition */
/* Return 1 if ocurred one error, or 0 if all type is ok*/
unsigned char checkReturnExpression(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* lastUsedMethod, Attribute *attr)
{
    ReturnType rt = methodReturnType(eq, aSymbolsTable, lastUsedMethod);
    if (rt == RetVoid)
    {
        insert_error(eq,to_string("El metodo \"",lastUsedMethod,"\" no puede retornar una expresion ya que retorna void."));
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
            insert_error(eq, to_string("El metodo \"", lastUsedMethod, msg));
            return 1;
            //		free(msg);
        }
        else
        {
            // assign the expression in attribute to the method return expression
            setMethodReturnAttribute(eq,aSymbolsTable, lastUsedMethod, (*attr).decl.variable);
        }
    return 0;
}

/* Returns the array at the position specified by attr.decl.variable.value.intValue if attr has "int" type
   Otherwise insert an error message because the attribute haven't got "int" type and create a default variable of "int" type */
Attribute* checkArrayPos(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, LCode3D *lcode3d, char* id, Attribute* attr)
{
    Attribute *aux = searchIdInSymbolsTable(eq,aSymbolsTable,id);
    if (aux != NULL)
    {
        if(getStructureType(aux) != Array)
            insert_error(eq, to_string("El identificador \"", id, "\" no corresponde a un arreglo."));
        else
        {
            if (getAttributeType(attr) == Int)
            {
                if (getIntVal(attr) >= 0 && getIntVal(attr) < (*aux).decl.array.length)
                {
                    Attribute *variable = createVariable(getVariableName(), getAttributeType(aux));
                    increaseVarOffset();
                    (*(*variable).decl.variable).offset = getOffsetArray(aux) + (getIntVal(attr)*4);
                   // (*(*variable).decl.variable).offset = (*aux).decl.array.arrayValues[getIntVal(attr)].offset;
                    Code3D *codeArrayValue = newCode(LOAD_ARRAY);
                    setAttribute(codeArrayValue, 1, attr);
                    setAttribute(codeArrayValue, 2, aux);
                    setAttribute(codeArrayValue, 3, variable);
                    add_code(lcode3d, codeArrayValue);
                    return variable;
                }
                else
                    insert_error(eq, to_string("La expresion para acceder al arreglo \"", id, "\" se encuentra fuera de rango."));
            }
            else
                insert_error(eq, to_string("La expresion para acceder a la posicion del arreglo \"", id, "\" debe ser de tipo \"int\"."));
        }
    }
    return createVariable(getVariableName(),Int);
}

/* Checks if the program have a "main" method and it haven't got parameters */
void checkMain(ErrorsQueue *eq, SymbolsTable *aSymbolsTable)
{
    Attribute *attr = searchIdInSymbolsTable(eq, aSymbolsTable,"main");
    if (attr == NULL)
        insert_error(eq, "El programa no tiene un metodo \"main\".");
    else
        if (getStructureType(attr) != Method)
            insert_error(eq, "El identificador \"main\" solo puede ser un metodo.");
}

/* ---------------------------------------expression and conjunction no-terminal---------------------------------------------- */

/* Return an attribute with the or operation applied to oper1 and oper2. */
/* Insert a new code3D OR in a list of Codes */
Attribute* returnOr(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) == Bool))
    {
        Attribute *aux = createVariable(getVariableName(), Bool);
        Code3D *codeOr = newCode(OR);
        setCode3D(codeOr, oper1, oper2, aux);
        add_code(lcode3d, codeOr);
        return aux;
    }
    else
    {
        insert_error(eq, to_string("La expresion logica \"", "OR", "\" no tiene ambos operandos de tipo booleano."));
        return createVariable(getVariableName(), Bool);
    }
}


/* Return an attribute with the and operation applied to oper1 and oper2. */
/* Insert a new code3D And in a list of Codes */
Attribute* returnAnd(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) == Bool))
    {
        Attribute *aux = createVariable(getVariableName(), Bool);
        Code3D *codeAnd = newCode(AND);
        setCode3D(codeAnd, oper1, oper2, aux);
        add_code(lcode3d, codeAnd);
        return aux;
    }
    else
    {
        insert_error(eq, to_string("La expresion logica \"", "AND", "\" no tiene ambos operandos de tipo booleano."));
        return createVariable(getVariableName(), Bool);
    }
}
/* ---------------------------------------expression and conjunction no-terminal ended-------------------------------------- */

/* ---------------------------------------inequality and comparison no-terminal-------------------------------------------- */

/* Return an attribute with the distinct operation applied to oper1 and oper2. */
/* Insert a new code3D Distinct in a list of Codes */
Attribute* returnDistinct(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2))
    {
        Attribute *aux = createVariable(getVariableName(), Bool);
        Code3D *codeDist;
        if (getAttributeType(oper1) == Float)
            codeDist = newCode(DIST_FLOAT);
        if (getAttributeType(oper1) == Int)
            codeDist = newCode(DIST_INT);
        if (getAttributeType(oper1) == Bool)
            codeDist = newCode(DIST_BOOL);
        setCode3D(codeDist, oper1, oper2, aux);
        add_code(lcode3d, codeDist);
        return aux;
    }
    else
    {
        insert_error(eq, to_string("El operador \"", "!=", "\" no tiene ambos operandos del mismo tipo."));
        return createVariable(getVariableName(), Bool);
    }
}

/* Return an attribute with the equal operation applied to oper1 and oper2. */
/* Insert a new code3D Equal in a list of Codes */
Attribute* returnEqual(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2))
    {
        Attribute *aux = createVariable(getVariableName(), Bool);
        Code3D *codeEqual;
        if (getAttributeType(oper1) == Float)
            codeEqual = newCode(EQ_FLOAT);
        if (getAttributeType(oper1) == Int)
            codeEqual = newCode(EQ_INT);
        if (getAttributeType(oper1) == Bool)
            codeEqual = newCode(EQ_BOOL);
        setCode3D(codeEqual, oper1, oper2, aux);
        add_code(lcode3d, codeEqual);
        return aux;
    }
    else
    {
        insert_error(eq, to_string("El operador \"", "==", "\" no tiene ambos operandos del mismo tipo."));
        return createVariable(getVariableName(), Bool);
    }
}
/* ------------------------------------inequality and comparison no-terminal ended---------------------------------------- */

/* ---------------------------------------relation no-terminal ------------------------------------------------ */

/* Return an attribute with the minor comparison operation applied to oper1 and oper2. */
/* Insert a new code3D MinorComparison in a list of Codes */
Attribute* returnMinorComparison(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if ((getAttributeType(oper1) == getAttributeType(oper2)) && (getAttributeType(oper2) != Bool))
    {
        Attribute *aux = createVariable(getVariableName(), Bool);
        Code3D *codeMinor;
        if (getAttributeType(oper1) == Float)
            codeMinor = newCode(LOWER_FLOAT);
        else
            codeMinor = newCode(LOWER_INT);
        setCode3D(codeMinor, oper1, oper2, aux);
        add_code(lcode3d, codeMinor);
        return aux;
    }
    else
    {
        insert_error(eq, to_string("El operador \"", "<", "\" no tiene ambos operandos de tipo correcto o del mismo tipo."));
        return createVariable(getVariableName(), Bool);
    }
}

/* Return an attribute with the major comparison operation applied to oper1 and oper2. */
/* Insert a new code3D MajorComparison in a list of Codes */
Attribute* returnMajorComparison(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if ((getAttributeType(oper1) == getAttributeType(oper2)) && (getAttributeType(oper2) != Bool))
    {
        Attribute *aux = createVariable(getVariableName(), Bool);
        Code3D *codeGreat;
        if (getAttributeType(oper1) == Float)
            codeGreat = newCode(GREATER_FLOAT);
        else
            codeGreat = newCode(GREATER_INT);
        setCode3D(codeGreat, oper1, oper2, aux);
        add_code(lcode3d, codeGreat);
        return aux;
    }
    else
    {
        insert_error(eq, to_string("El operador \"", ">", "\" no tiene ambos operandos de tipo correcto o del mismo tipo."));
        return createVariable(getVariableName(), Bool);
    }
}

/* Return an attribute with the greater or equal comparison operation applied to oper1 and oper2. */
/* Insert a new code3D GEqualComparison in a list of Codes */
Attribute* returnGEqualComparison(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if ((getAttributeType(oper1) == getAttributeType(oper2)) && (getAttributeType(oper2) != Bool))
    {
        Attribute *aux = createVariable(getVariableName(), Bool);
        Code3D *codeGEqual;
        if (getAttributeType(oper1) == Float)
            codeGEqual = newCode(GEQ_FLOAT);
        else
            codeGEqual = newCode(GEQ_INT);
        setCode3D(codeGEqual, oper1, oper2, aux);
        add_code(lcode3d, codeGEqual);
        return aux;
    }
    else
    {
        insert_error(eq, to_string("El operador \"", ">=", "\" no tiene ambos operandos de tipo correcto o del mismo tipo."));
        return createVariable(getVariableName(), Bool);
    }
}

/* Return an attribute with the less or equal comparison operation applied to oper1 and oper2. */
/* Insert a new code3D LEqualComparison in a list of Codes */
Attribute* returnLEqualComparison(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if ((getAttributeType(oper1) == getAttributeType(oper2)) && (getAttributeType(oper2) != Bool))
    {
        Attribute *aux = createVariable(getVariableName(), Bool);
        Code3D *codeLEqual;
        if (getAttributeType(oper1) == Float)
            codeLEqual = newCode(LEQ_FLOAT);
        else
            codeLEqual = newCode(LEQ_INT);
        setCode3D(codeLEqual, oper1, oper2, aux);
        add_code(lcode3d, codeLEqual);
        return aux;
    }
    else
    {
        insert_error(eq, to_string("El operador \"", "<=", "\" no tiene ambos operandos de tipo correcto o del mismo tipo."));
        return createVariable(getVariableName(), Bool);
    }
}
/* ---------------------------------------relation no-terminal ended---------------------------------------- */

/* ---------------------------------------term no-terminal ------------------------------------------------ */

/* Return an attribute with the add operation. */
/* Insert a new code3D Add in a list of Codes */
Attribute* returnAdd(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if ((getAttributeType(oper1) == getAttributeType(oper2)) && (getAttributeType(oper2) != Bool))
    {
        Code3D *codeAdd;
        Attribute *aux = createVariable(getVariableName(), getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
            codeAdd = newCode(ADD_FLOAT);
        else
            codeAdd = newCode(ADD_INT);
        setCode3D(codeAdd, oper1, oper2, aux);
        add_code(lcode3d, codeAdd);
        return aux;
    }
    else
    {
        insert_error(eq, to_string("El operador \"", "+", "\" no tiene ambos operandos de tipo correcto o del mismo tipo."));
        return createVariable(getVariableName(), Int);
    }
}

/* Return an attribute with the sub operation. */
/* Insert a new code3D Sub in a list of Codes */
Attribute* returnSub(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) != Bool))
    {
        Code3D *codeSub;
        Attribute *aux = createVariable(getVariableName(), getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
            codeSub = newCode(MINUS_FLOAT);
        else
            codeSub = newCode(MINUS_INT);
        setCode3D(codeSub, oper1, oper2, aux);
        add_code(lcode3d, codeSub);
        return aux;
    }
    else
    {
        insert_error(eq, to_string("El operador \"", "-", "\" no tiene ambos operandos de tipo correcto o del mismo tipo."));
        return createVariable(getVariableName(), Int);
    }
}

/* Return an attribute with the mod operation. */
/* Insert a new code3D Mod in a list of Codes */
Attribute* returnMod(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) == Int))
    {
        Attribute *aux = createVariable(getVariableName(), getAttributeType(oper1));
        Code3D *codeMod;
        codeMod = newCode(MOD_INT);
        setCode3D(codeMod, oper1, oper2, aux);
        add_code(lcode3d, codeMod);
        return aux;
    }
    else
    {
        insert_error(eq, to_string("El operador \"", "%", "\" solo soporta tipo INT y/o no tiene ambos operandos del mismo tipo."));
        return createVariable(getVariableName(), Int);
    }
}

/* Return an attribute with the div operation. */
/* Insert a new code3D Div in a list of Codes */
Attribute* returnDiv(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) != Bool))
    {
        Code3D *codeDiv;
        Attribute *aux = createVariable(getVariableName(), getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
            codeDiv = newCode(DIV_FLOAT);
        else
            codeDiv = newCode(DIV_INT);
        setCode3D(codeDiv, oper1, oper2, aux);
        add_code(lcode3d, codeDiv);
        return aux;
    }
    else
    {
        insert_error(eq, to_string("El operador \"", "/", "\" no tiene ambos operandos de tipo correcto o del mismo tipo."));
        return createVariable(getVariableName(), Int);
    }
}

/* Return an attribute with the mult operation. */
/* Insert a new code3D Mult in a list of Codes */
Attribute* returnMult(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if (getAttributeType(oper1) == getAttributeType(oper2) && (getAttributeType(oper2) != Bool))
    {
        Code3D *codeMult;
        Attribute *aux = createVariable(getVariableName(), getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
            codeMult = newCode(MULT_FLOAT);
        else
            codeMult = newCode(MULT_INT);
        setCode3D(codeMult, oper1, oper2, aux);
        add_code(lcode3d, codeMult);
        return aux;
    }
    else
    {
        insert_error(eq, to_string("El operador \"", "*", "\" no tiene ambos operandos de tipo correcto o del mismo tipo."));
        return createVariable(getVariableName(), Int);
    }
}

/* Return an attribute with the not operation applied to oper1. */
/* Insert a new code3D Not in a list of Codes */
Attribute* returnNot(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1)
{
    if (getAttributeType(oper1) == Bool)
    {
        Attribute *aux = createVariable(getVariableName(), Bool);
        Code3D *codeNot = newCode(NOT);
        setCode2D(codeNot, oper1, aux);
        add_code(lcode3d, codeNot);
        return aux;
    }
    else
    {
        insert_error(eq, to_string("El operador \"", "!", "\" no tiene el operando de tipo booleano."));
        return createVariable(getVariableName(), Bool);
    }
}

/* Return an attribute with the neg operation applied to oper1. */
/* Insert a new code3D Neg in a list of Codes */
Attribute* returnNeg(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1)
{
    if (getAttributeType(oper1) == Int || getAttributeType(oper1) == Float)
    {
        Code3D *codeNeg;
        Attribute *aux = createVariable(getVariableName(), getAttributeType(oper1));
        if (getAttributeType(oper1) == Float)
            codeNeg = newCode(NEG_FLOAT);
        else
            codeNeg = newCode(NEG_INT);
        setCode2D(codeNeg, oper1, aux);
        add_code(lcode3d, codeNeg);
        return aux;
    }
    else
    {
        insert_error(eq, to_string("El operador \"", "-", "\" no tiene el operando de tipo Int o Float."));
        return createVariable(getVariableName(), Int);
    }
}

/* ---------------------------------------term no-terminal ended----------------------------------------- */

/* ---------------------------------------term terminal ------------------------------------------------- */

/* Return an attribute with the type equal to param type and value equal to  param oper1. */
/* Insert a new code3D Int or Float or Bool in a list of Codes */
Attribute* returnValue(LCode3D *lcode3d, PrimitiveType type, char *oper1)
{
    Attribute *aux = createVariable(getVariableName(), type);
    setVariableValue(aux, type, oper1);

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

    setAttribute(codeValue, 2, aux);
    setNull(codeValue, 3);
    add_code(lcode3d, codeValue);
    return aux;
}

/* ---------------------------------------term terminal ended-------------------------------------------- */
