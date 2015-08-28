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
char* get_variable_name()
{
    char *name = (char*) malloc ((strlen(temp)+digit_amount(numberOfVariable))*sizeof(char));
    strcat(name,temp);
    
    strcat(name,int_to_string(numberOfVariable));
    numberOfVariable++;
    return name;
}

/* Returns an attribute of ID "id" and Variable structure. Otherwise returns NULL */
Attribute* get_variable_attribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id)
{
    Attribute *attr = search_id_in_symbols_table(eq, aSymbolsTable, id);
    if(attr != NULL)
    {
        if(get_structure_type(attr) != Variable)
            insert_error(eq, add_line_column(to_string("El identificador \"", id, "\" no corresponde a una variable.")));
        else
            return attr;
    }
    return create_variable(get_variable_name(),Int); // Returns an attribute with type Int to continue parsing
}

/* Returns the return attribute of the method with id "id" */
Attribute* get_method_return_attribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id)
{
    Attribute *attr = search_id_in_symbols_table(eq, aSymbolsTable, id);
    if(attr != NULL)
    {
        if(get_structure_type(attr) != Method)
            insert_error(eq,add_line_column(to_string("El identificador \"", id,"\" no corresponde a un metodo.")));
        else
        {
            if (get_attribute_type(attr) == RetVoid)
                insert_error(eq,add_line_column(to_string("El metodo \"", id,"\" retorna void, no puede setearse ningun atributo de retorno.")));
            else
            {
                Attribute *aux = create_variable(get_variable_name(), get_attribute_type(attr));
                switch (get_attribute_type(attr))
                {
                    case Int:   set_int_val(aux,get_int_val(attr)); break;
                    case Float: set_float_val(aux,get_float_val(attr)); break;
                    case Bool:  set_bool_val(aux,get_int_val(attr)); break;
                    default: break;
                }
                return aux;
            }
        }
    }
    return create_variable(get_variable_name(),Int); // Returns type Int by default in case of having errors
}

/* Sets the return attribute of the method with id "id" */
void set_method_return_attribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id, StVariable *value)
{
    Attribute *attr = search_id_in_symbols_table(eq, aSymbolsTable, id);
    if(attr != NULL)
    {
        if(get_structure_type(attr) != Method)
            insert_error(eq,add_line_column(to_string("El identificador \"", id,"\" no corresponde a un metodo.")));
        else
        {
            if (get_attribute_type(attr) == RetVoid)
                insert_error(eq,add_line_column(to_string("El metodo \"", id,"\" retorna void, no puede setearse ningun atributo de retorno.")));
            else
            {
                switch (value->type)
                {
                    case Int:   set_int_val(attr, value->value.intVal); break;
                    case Float: set_float_val(attr, value->value.floatVal); break;
                    case Bool:  set_bool_val(attr, value->value.boolVal); break;
                }    
            }
        }
    }
}

/* Returns the respective variable attribute that the method return. "paramSize" is for checking if the amount of parameters is right */
Attribute* check_get_method_ret_attribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, LCode3D *lcode3d, char *id, unsigned char paramSize)
{
    Attribute *attr = search_id_in_symbols_table(eq, aSymbolsTable, id);
    if (attr != NULL)
    {
        if (get_structure_type(attr) != Method)
            insert_error(eq,add_line_column(to_string("El identificador \"", id,"\" no corresponde a un metodo.")));
        else
        {
            if (attr->decl.method.paramSize != paramSize)
                insert_error(eq,add_line_column(to_string("El metodo \"", id,"\" no contiene la cantidad correspondiente de parametros.")));
            else
            {
                Attribute *aux = create_variable(get_variable_name(), get_attribute_type(attr));
                if (get_attribute_type(attr) != RetVoid)
                    add_assignation(lcode3d, attr, aux);
                return aux;
            }
        }
    }
    return create_variable(get_variable_name(),Int); // Returns type Int by default in case of having errors
}

/* Returns 0 if the type of the parameter on the position "pos" of the method "attr" is equal to the type of "var"
   Returns 1 otherwise */
unsigned char correct_parameter_type(StVariable *var, Attribute *attr, unsigned char pos)
{
    if (var->type == attr->decl.method.parameters[pos]->type)
        return 0;
    return 1;
}

/* Returns the ReturnType of the method with id "id" */
ReturnType method_return_type(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id)
{
    Attribute *attr = search_id_in_symbols_table(eq, aSymbolsTable, id);
    if(attr != NULL)
    {
        if(get_structure_type(attr) != Method)
            insert_error(eq, add_line_column(to_string("El identificador \"", id, "\" no corresponde a un metodo.")));
        else
            return get_attribute_type(attr);
    }
    return RetInt; /* retorno por defecto el tipo int */
}

/* Returns the amount of digits that has the int "value" */
unsigned int digit_amount(int value)
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
char* int_to_string(int value)
{
    char *aux = (char*) malloc (digit_amount(value)*sizeof(char));
    sprintf(aux,"%d",value);
    return aux;
}

/* Returns the string representation of the float "value" */
char* float_to_string(float value)
{
    char *aux = (char*) malloc (sizeof(char)*100);
    sprintf(aux, "%f", value);
    return aux;
}

/* Returns 0 if the type parameter in "paramSize" position of the method's parameters is equal to the type of "var"
   and the amount of params are equal.
   Returns 1 otherwise */
void correct_param_base_case(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, LCode3D *lcode3d, Attribute *attr, char* lastCalledMethod, unsigned char paramSize)
{
    Attribute *aux = search_id_in_symbols_table(eq, aSymbolsTable, lastCalledMethod);
    if(aux != NULL)
    {
        if(get_structure_type(aux) != Method)
            insert_error(eq, add_line_column(to_string("El identificador \"", lastCalledMethod, "\" no corresponde a un metodo.")));
        else
        {
            if (paramSize+1 == aux->decl.method.paramSize)
            {
                if (correct_parameter_type(attr->decl.variable, aux, paramSize) == 0)
                {
                    Attribute *param = (Attribute*) malloc (sizeof(Attribute));
                    param->decl.variable = aux->decl.method.parameters[paramSize]; // obtencion del parametro formal.
                    switch (get_attribute_type(attr))
                    {
                        case Int:   add_method_call(lcode3d, new_code(PARAM_ASSIGN_INT), attr, param); break;
                        case Float: add_method_call(lcode3d, new_code(PARAM_ASSIGN_FLOAT), attr, param); break;
                        case Bool:  add_method_call(lcode3d, new_code(PARAM_ASSIGN_BOOL), attr, param); break;
                        default: break;
                    }
                }
                else
                {
                    insert_error(eq,add_line_column(to_string("Error en llamada al método \"", lastCalledMethod, 
                        to_string("\". Se esperaba el ", int_to_string(paramSize+1), to_string("° argumento de tipo \"", 
                            get_type(aux->decl.method.parameters[paramSize]->type), to_string("\" pero se encontró de tipo \"", 
                                get_type(get_attribute_type(attr)), "\"."))))));
                    Attribute *param = (Attribute*) malloc (sizeof(Attribute));
                    param->decl.variable = aux->decl.method.parameters[paramSize]; // obtencion del parametro formal.
                    param->decl.variable->type = aux->decl.method.parameters[paramSize]->type;
                    switch (get_attribute_type(param))
                    {
                        case Int:   add_method_call(lcode3d, new_code(PARAM_ASSIGN_INT), create_variable("",Int), param); break;
                        case Float: add_method_call(lcode3d, new_code(PARAM_ASSIGN_FLOAT), create_variable("",Float), param); break;
                        case Bool:  add_method_call(lcode3d, new_code(PARAM_ASSIGN_BOOL), create_variable("",Bool), param); break;
                        default: break;
                    }
                }
            }
            else
                if (paramSize < aux->decl.method.paramSize)
                    insert_error(eq,add_line_column(to_string("Error en llamada al metodo \"", lastCalledMethod, "\". Se tiene menor cantidad de parametros que en su declaracion.")));
                else
                    insert_error(eq,add_line_column(to_string("Error en llamada al metodo \"", lastCalledMethod, "\". Se tiene mayor cantidad de parametros que en su declaracion.")));
        }
    }
}

/* Returns 0 if the type parameter in "paramSize" position of the method's parameters is equal to the type of "var"
   and paramSize <= than the amount of parameters of the method.
   Returns 1 otherwise */
void correct_param_inductive_case(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, LCode3D *lcode3d, Attribute *attr, char* lastCalledMethod, unsigned char paramSize)
{
    Attribute *aux = search_id_in_symbols_table(eq, aSymbolsTable, lastCalledMethod);
    if(aux != NULL)
    {
        if(get_structure_type(aux) != Method)
            insert_error(eq, add_line_column(to_string("El identificador \"", lastCalledMethod, "\" no corresponde a un metodo.")));
        else
        {
            if (paramSize < aux->decl.method.paramSize)
            {
                if (correct_parameter_type(attr->decl.variable, aux, paramSize) == 0)
                {
                    Attribute *param = (Attribute*) malloc (sizeof(Attribute));
                    param->decl.variable = aux->decl.method.parameters[paramSize]; // obtencion del parametro formal.
                    param->decl.variable->type = aux->decl.method.parameters[paramSize]->type;
                    switch (get_attribute_type(attr))
                    {
                        case Int:   add_method_call(lcode3d, new_code(PARAM_ASSIGN_INT), attr, param); break;
                        case Float: add_method_call(lcode3d, new_code(PARAM_ASSIGN_FLOAT), attr, param); break;
                        case Bool:  add_method_call(lcode3d, new_code(PARAM_ASSIGN_BOOL), attr, param); break;
                        default: break;
                    }
                }
                else {
                    insert_error(eq,add_line_column(to_string("Error en llamada al método \"", lastCalledMethod, 
                        to_string("\". Se esperaba el ", int_to_string(paramSize+1), to_string("° argumento de tipo \"", 
                            get_type(aux->decl.method.parameters[paramSize]->type), to_string("\" pero se encontró de tipo \"", 
                                get_type(get_attribute_type(attr)), "\"."))))));
                    Attribute *param = (Attribute*) malloc (sizeof(Attribute));
                    param->decl.variable = aux->decl.method.parameters[paramSize]; // obtencion del parametro formal.
                    param->decl.variable->type = aux->decl.method.parameters[paramSize]->type;
                    switch (get_attribute_type(param))
                    {
                        case Int:   add_method_call(lcode3d, new_code(PARAM_ASSIGN_INT), create_variable("",Int), param); break;
                        case Float: add_method_call(lcode3d, new_code(PARAM_ASSIGN_FLOAT), create_variable("",Float), param); break;
                        case Bool:  add_method_call(lcode3d, new_code(PARAM_ASSIGN_BOOL), create_variable("",Bool), param); break;
                        default: break;
                    }
                }
            }
        }
    }
}

void extern_param_assign(LCode3D *lcode3d, Attribute *param, unsigned char paramNumber)
{
    switch (get_attribute_type(param))
    {
        case Int:   add_param_externinvk(lcode3d, new_code(EXTERN_PARAM_ASSIGN_INT), param, paramNumber); break;
        case Float: add_param_externinvk(lcode3d, new_code(EXTERN_PARAM_ASSIGN_FLOAT), param, paramNumber); break;
        case Bool:  add_param_externinvk(lcode3d, new_code(EXTERN_PARAM_ASSIGN_BOOL), param, paramNumber); break;
        default: break;
    }
}

/* Insert an error message if the attribute "attr" isn't a variable of type "type" */
/* Return 1 if ocurred one error, or 0 if all type is ok*/
unsigned char control_type(ErrorsQueue *eq, Attribute *attr, PrimitiveType type, char *operation, int numberOfExpression)
{
    if (get_attribute_type(attr) != type)
    {
        if (numberOfExpression == 1)
        {
            char* f = (char*) malloc ((strlen("La expresion de la sentencia \"")+strlen(operation)+strlen("\" no es del tipo \""))*sizeof(char));
            strcat(f,"La expresion de la sentencia \"");
            strcat(f, operation);
            strcat(f,"\" no es del tipo \"");
            insert_error(eq, add_line_column(to_string(f, get_type(type), "\".")));
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
            insert_error(eq, add_line_column(to_string(f, get_type(type), "\".")));
        }
        return 1;
    }
    return 0;
}

/* Insert an error message and return 1 if attributes "attr1" and "attr2" aren't of the same type and both variables or arrays
   Returns 0 otherwise */
unsigned char control_assignation(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *attr1, char* op, Attribute *attr2)
{
    if (get_structure_type(attr1) != Method)
    {
        if (get_attribute_type(attr1) != get_attribute_type(attr2))
            insert_error(eq, add_line_column(to_string("El lado derecho de la asignacion debe ser de tipo \"", get_type(get_attribute_type(attr1)), "\".")));
        else
        {
            Code3D *add;
            if (strcmp(op, "=") == 0)
				add_assignation(lcode3d, attr2, attr1);
            else
            {
                if (strcmp(op, "+=") == 0)
                {
                    if (get_attribute_type(attr1) == Int)
                        add = new_code(ADD_INT);
                    if (get_attribute_type(attr1) == Float)
                        add = new_code(ADD_FLOAT);
                }
                if (strcmp(op, "-=") == 0)
                {
                    if (get_attribute_type(attr1) == Int)
                        add = new_code(MINUS_INT);
                    if (get_attribute_type(attr1) == Float)
                        add = new_code(MINUS_FLOAT);
                }
                Attribute *res = create_variable(get_variable_name(), get_attribute_type(attr1));
                set_c3D(add, attr1, attr2, res);
                add_code(lcode3d, add);
				add_assignation(lcode3d, res, attr1);
            }
            return 0;
        }
    }
    else
        insert_error(eq, add_line_column(to_string("El identificador izquierdo de la asignacion ", "", " no debe ser un metodo.")));
    return 1;
}

/* Insert an error message if the "lastUsedMethod" haven't got "void" return type */
unsigned char check_return(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* lastUsedMethod)
{
    ReturnType rt = method_return_type(eq, aSymbolsTable, lastUsedMethod);
    if (rt != RetVoid)
    {
        char* msg = (char*) malloc ((strlen("\" debe retornar una expresion de tipo \"")+strlen(get_type(rt))+strlen("\"."))*sizeof(char));
        strcat(msg, "\" debe retornar una expresion de tipo \"");
        strcat(msg, get_type(rt));
        strcat(msg, "\".");
        insert_error(eq, add_line_column(to_string("El metodo \"", lastUsedMethod, msg))); 
        return 1;
    }
    return 0;
}

/* Insert an error message if the "lastUsedMethod" doesn't return "void" or if it has a different return type that the definition */
/* Return 1 if ocurred one error, or 0 if all type is ok*/
unsigned char check_return_expression(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* lastUsedMethod, Attribute *attr)
{
    ReturnType rt = method_return_type(eq, aSymbolsTable, lastUsedMethod);
    if (rt == RetVoid)
    {
        insert_error(eq, add_line_column(to_string("El metodo \"",lastUsedMethod,"\" no puede retornar una expresion ya que retorna void.")));
        return 1;
    }
    else
        if (rt != get_attribute_type(attr))
        {
            char* msg = (char*) malloc ((strlen("\" debe retornar una expresion de tipo \"")+strlen(get_type(rt))+strlen("\", no de tipo \"")+strlen(get_type(get_attribute_type(attr)))+strlen("\"."))*sizeof(char));
            strcat(msg, "\" debe retornar una expresion de tipo \"");
            strcat(msg, get_type(rt));
            strcat(msg, "\", no de tipo \"");
            strcat(msg, get_type(get_attribute_type(attr)));
            strcat(msg, "\".");
            insert_error(eq, add_line_column(to_string("El metodo \"", lastUsedMethod, msg)));
            return 1;
        }
        else
            // assign the expression in attribute to the method return expression
            set_method_return_attribute(eq,aSymbolsTable, lastUsedMethod, attr->decl.variable);
    return 0;
}

/* Returns the array at the position specified by attr.decl.variable.value.intValue if attr has "int" type
   Otherwise insert an error message because the attribute haven't got "int" type and create a default variable of "int" type */
Attribute* check_array_pos(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, LCode3D *lcode3d, char* id, Attribute* attr)
{
    Attribute *aux = search_id_in_symbols_table(eq,aSymbolsTable,id);
    if (aux != NULL)
    {
        if(get_structure_type(aux) != Array)
            insert_error(eq, add_line_column(to_string("El identificador \"", id, "\" no corresponde a un arreglo.")));
        else
        {
            if (get_attribute_type(attr) == Int)
            {
                if (get_int_val(attr) >= 0 && get_int_val(attr) < aux->decl.array.length)
                {
                    Attribute *variable = create_variable(get_variable_name(), get_attribute_type(aux));
                    increase_var_offset();
                    variable->decl.variable->offset = get_offset_array(aux) + (get_int_val(attr)*4);
                   // variable->decl.variable->offset = aux->decl.array.arrayValues[get_int_val(attr)].offset;
                    Code3D *codeArrayValue = new_code(LOAD_ARRAY);
                    set_attribute(codeArrayValue, 1, attr);
                    set_attribute(codeArrayValue, 2, aux);
                    set_attribute(codeArrayValue, 3, variable);
                    add_code(lcode3d, codeArrayValue);
                    return variable;
                }
                else
                    insert_error(eq, add_line_column(to_string("La expresion para acceder al arreglo \"", id, "\" se encuentra fuera de rango.")));
            }
            else
                insert_error(eq, add_line_column(to_string("La expresion para acceder a la posicion del arreglo \"", id, "\" debe ser de tipo \"int\".")));
        }
    }
    return create_variable(get_variable_name(),Int);
}

/* Checks if the program have a "main" method and it haven't got parameters */
void check_main(ErrorsQueue *eq, SymbolsTable *aSymbolsTable)
{
    Attribute *attr = search_id_in_symbols_table(eq, aSymbolsTable,"main");
    if (attr == NULL)
        insert_error(eq, "El programa no tiene un metodo \"main\".");
    else
        if (get_structure_type(attr) != Method)
            insert_error(eq, "El identificador \"main\" solo puede ser un metodo.");
}

/* ---------------------------------------expression and conjunction no-terminal---------------------------------------------- */

/* Return an attribute with the or operation applied to oper1 and oper2. */
/* Insert a new code3D OR in a list of Codes */
Attribute* return_or(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if (get_attribute_type(oper1) == get_attribute_type(oper2) && (get_attribute_type(oper2) == Bool))
    {
        Attribute *aux = create_variable(get_variable_name(), Bool);
        Code3D *codeOr = new_code(OR);
        set_c3D(codeOr, oper1, oper2, aux);
        add_code(lcode3d, codeOr);
        return aux;
    }
    else
    {
        insert_error(eq, add_line_column(to_string("La expresion logica \"", "OR", "\" no tiene ambos operandos de tipo booleano.")));
        return create_variable(get_variable_name(), Bool);
    }
}


/* Return an attribute with the and operation applied to oper1 and oper2. */
/* Insert a new code3D And in a list of Codes */
Attribute* return_and(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if (get_attribute_type(oper1) == get_attribute_type(oper2) && (get_attribute_type(oper2) == Bool))
    {
        Attribute *aux = create_variable(get_variable_name(), Bool);
        Code3D *codeAnd = new_code(AND);
        set_c3D(codeAnd, oper1, oper2, aux);
        add_code(lcode3d, codeAnd);
        return aux;
    }
    else
    {
        insert_error(eq, add_line_column(to_string("La expresion logica \"", "AND", "\" no tiene ambos operandos de tipo booleano.")));
        return create_variable(get_variable_name(), Bool);
    }
}
/* ---------------------------------------expression and conjunction no-terminal ended-------------------------------------- */

/* ---------------------------------------inequality and comparison no-terminal-------------------------------------------- */

/* Return an attribute with the distinct operation applied to oper1 and oper2. */
/* Insert a new code3D Distinct in a list of Codes */
Attribute* return_distinct(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if (get_attribute_type(oper1) == get_attribute_type(oper2))
    {
        Attribute *aux = create_variable(get_variable_name(), Bool);
        Code3D *codeDist;
        switch (get_attribute_type(oper1))
        {
            case Int:   codeDist = new_code(DIST_INT); break;
            case Float: codeDist = new_code(DIST_FLOAT); break;
            case Bool:  codeDist = new_code(DIST_BOOL); break;
            default: break;
        }
        set_c3D(codeDist, oper1, oper2, aux);
        add_code(lcode3d, codeDist);
        return aux;
    }
    else
    {
        insert_error(eq, add_line_column(to_string("El operador \"", "!=", "\" no tiene ambos operandos del mismo tipo.")));
        return create_variable(get_variable_name(), Bool);
    }
}

/* Return an attribute with the equal operation applied to oper1 and oper2. */
/* Insert a new code3D Equal in a list of Codes */
Attribute* return_equal(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if (get_attribute_type(oper1) == get_attribute_type(oper2))
    {
        Attribute *aux = create_variable(get_variable_name(), Bool);
        Code3D *codeEqual;
        switch (get_attribute_type(oper1))
        {
            case Int:   codeEqual = new_code(EQ_INT); break;
            case Float: codeEqual = new_code(EQ_FLOAT); break;
            case Bool:  codeEqual = new_code(EQ_BOOL); break;
            default: break;
        }
        set_c3D(codeEqual, oper1, oper2, aux);
        add_code(lcode3d, codeEqual);
        return aux;
    }
    else
    {
        insert_error(eq, add_line_column(to_string("El operador \"", "==", "\" no tiene ambos operandos del mismo tipo.")));
        return create_variable(get_variable_name(), Bool);
    }
}
/* ------------------------------------inequality and comparison no-terminal ended---------------------------------------- */

/* ---------------------------------------relation no-terminal ------------------------------------------------ */

/* Return an attribute with the minor comparison operation applied to oper1 and oper2. */
/* Insert a new code3D MinorComparison in a list of Codes */
Attribute* return_minor_comparison(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if ((get_attribute_type(oper1) == get_attribute_type(oper2)) && (get_attribute_type(oper2) != Bool))
    {
        Attribute *aux = create_variable(get_variable_name(), Bool);
        Code3D *codeMinor;
        if (get_attribute_type(oper1) == Float)
            codeMinor = new_code(LOWER_FLOAT);
        else
            codeMinor = new_code(LOWER_INT);
        set_c3D(codeMinor, oper1, oper2, aux);
        add_code(lcode3d, codeMinor);
        return aux;
    }
    else
    {
        insert_error(eq, add_line_column(to_string("El operador \"", "<", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")));
        return create_variable(get_variable_name(), Bool);
    }
}

/* Return an attribute with the major comparison operation applied to oper1 and oper2. */
/* Insert a new code3D MajorComparison in a list of Codes */
Attribute* return_major_comparison(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if ((get_attribute_type(oper1) == get_attribute_type(oper2)) && (get_attribute_type(oper2) != Bool))
    {
        Attribute *aux = create_variable(get_variable_name(), Bool);
        Code3D *codeGreat;
        if (get_attribute_type(oper1) == Float)
            codeGreat = new_code(GREATER_FLOAT);
        else
            codeGreat = new_code(GREATER_INT);
        set_c3D(codeGreat, oper1, oper2, aux);
        add_code(lcode3d, codeGreat);
        return aux;
    }
    else
    {
        insert_error(eq, add_line_column(to_string("El operador \"", ">", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")));
        return create_variable(get_variable_name(), Bool);
    }
}

/* Return an attribute with the greater or equal comparison operation applied to oper1 and oper2. */
/* Insert a new code3D GEqualComparison in a list of Codes */
Attribute* return_g_equal_comparison(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if ((get_attribute_type(oper1) == get_attribute_type(oper2)) && (get_attribute_type(oper2) != Bool))
    {
        Attribute *aux = create_variable(get_variable_name(), Bool);
        Code3D *codeGEqual;
        if (get_attribute_type(oper1) == Float)
            codeGEqual = new_code(GEQ_FLOAT);
        else
            codeGEqual = new_code(GEQ_INT);
        set_c3D(codeGEqual, oper1, oper2, aux);
        add_code(lcode3d, codeGEqual);
        return aux;
    }
    else
    {
        insert_error(eq, add_line_column(to_string("El operador \"", ">=", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")));
        return create_variable(get_variable_name(), Bool);
    }
}

/* Return an attribute with the less or equal comparison operation applied to oper1 and oper2. */
/* Insert a new code3D LEqualComparison in a list of Codes */
Attribute* return_l_equal_comparison(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if ((get_attribute_type(oper1) == get_attribute_type(oper2)) && (get_attribute_type(oper2) != Bool))
    {
        Attribute *aux = create_variable(get_variable_name(), Bool);
        Code3D *codeLEqual;
        if (get_attribute_type(oper1) == Float)
            codeLEqual = new_code(LEQ_FLOAT);
        else
            codeLEqual = new_code(LEQ_INT);
        set_c3D(codeLEqual, oper1, oper2, aux);
        add_code(lcode3d, codeLEqual);
        return aux;
    }
    else
    {
        insert_error(eq, add_line_column(to_string("El operador \"", "<=", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")));
        return create_variable(get_variable_name(), Bool);
    }
}
/* ---------------------------------------relation no-terminal ended---------------------------------------- */

/* ---------------------------------------term no-terminal ------------------------------------------------ */

/* Return an attribute with the add operation. */
/* Insert a new code3D Add in a list of Codes */
Attribute* return_add(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if ((get_attribute_type(oper1) == get_attribute_type(oper2)) && (get_attribute_type(oper2) != Bool))
    {
        Code3D *codeAdd;
        Attribute *aux = create_variable(get_variable_name(), get_attribute_type(oper1));
        if (get_attribute_type(oper1) == Float)
            codeAdd = new_code(ADD_FLOAT);
        else
            codeAdd = new_code(ADD_INT);
        set_c3D(codeAdd, oper1, oper2, aux);
        add_code(lcode3d, codeAdd);
        return aux;
    }
    else
    {
        insert_error(eq, add_line_column(to_string("El operador \"", "+", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")));
        return create_variable(get_variable_name(), Int);
    }
}

/* Return an attribute with the sub operation. */
/* Insert a new code3D Sub in a list of Codes */
Attribute* return_sub(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if (get_attribute_type(oper1) == get_attribute_type(oper2) && (get_attribute_type(oper2) != Bool))
    {
        Code3D *codeSub;
        Attribute *aux = create_variable(get_variable_name(), get_attribute_type(oper1));
        if (get_attribute_type(oper1) == Float)
            codeSub = new_code(MINUS_FLOAT);
        else
            codeSub = new_code(MINUS_INT);
        set_c3D(codeSub, oper1, oper2, aux);
        add_code(lcode3d, codeSub);
        return aux;
    }
    else
    {
        insert_error(eq, add_line_column(to_string("El operador \"", "-", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")));
        return create_variable(get_variable_name(), Int);
    }
}

/* Return an attribute with the mod operation. */
/* Insert a new code3D Mod in a list of Codes */
Attribute* return_mod(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if (get_attribute_type(oper1) == get_attribute_type(oper2) && (get_attribute_type(oper2) == Int))
    {
        Attribute *aux = create_variable(get_variable_name(), get_attribute_type(oper1));
        Code3D *codeMod;
        codeMod = new_code(MOD_INT);
        set_c3D(codeMod, oper1, oper2, aux);
        add_code(lcode3d, codeMod);
        return aux;
    }
    else
    {
        insert_error(eq, add_line_column(to_string("El operador \"", "%", "\" solo soporta tipo INT y/o no tiene ambos operandos del mismo tipo.")));
        return create_variable(get_variable_name(), Int);
    }
}

/* Return an attribute with the div operation. */
/* Insert a new code3D Div in a list of Codes */
Attribute* return_div(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if (get_attribute_type(oper1) == get_attribute_type(oper2) && (get_attribute_type(oper2) != Bool))
    {
        Code3D *codeDiv;
        Attribute *aux = create_variable(get_variable_name(), get_attribute_type(oper1));
        if (get_attribute_type(oper1) == Float)
            codeDiv = new_code(DIV_FLOAT);
        else
            codeDiv = new_code(DIV_INT);
        set_c3D(codeDiv, oper1, oper2, aux);
        add_code(lcode3d, codeDiv);
        return aux;
    }
    else
    {
        insert_error(eq, add_line_column(to_string("El operador \"", "/", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")));
        return create_variable(get_variable_name(), Int);
    }
}

/* Return an attribute with the mult operation. */
/* Insert a new code3D Mult in a list of Codes */
Attribute* return_mult(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2)
{
    if (get_attribute_type(oper1) == get_attribute_type(oper2) && (get_attribute_type(oper2) != Bool))
    {
        Code3D *codeMult;
        Attribute *aux = create_variable(get_variable_name(), get_attribute_type(oper1));
        if (get_attribute_type(oper1) == Float)
            codeMult = new_code(MULT_FLOAT);
        else
            codeMult = new_code(MULT_INT);
        set_c3D(codeMult, oper1, oper2, aux);
        add_code(lcode3d, codeMult);
        return aux;
    }
    else
    {
        insert_error(eq, add_line_column(to_string("El operador \"", "*", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")));
        return create_variable(get_variable_name(), Int);
    }
}

/* Return an attribute with the not operation applied to oper1. */
/* Insert a new code3D Not in a list of Codes */
Attribute* return_not(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1)
{
    if (get_attribute_type(oper1) == Bool)
    {
        Attribute *aux = create_variable(get_variable_name(), Bool);
        Code3D *codeNot = new_code(NOT);
        set_c2D(codeNot, oper1, aux);
        add_code(lcode3d, codeNot);
        return aux;
    }
    else
    {
        insert_error(eq, add_line_column(to_string("El operador \"", "!", "\" no tiene el operando de tipo booleano.")));
        return create_variable(get_variable_name(), Bool);
    }
}

/* Return an attribute with the neg operation applied to oper1. */
/* Insert a new code3D Neg in a list of Codes */
Attribute* return_neg(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1)
{
    if (get_attribute_type(oper1) == Int || get_attribute_type(oper1) == Float)
    {
        Code3D *codeNeg;
        Attribute *aux = create_variable(get_variable_name(), get_attribute_type(oper1));
        if (get_attribute_type(oper1) == Float)
            codeNeg = new_code(NEG_FLOAT);
        else
            codeNeg = new_code(NEG_INT);
        set_c2D(codeNeg, oper1, aux);
        add_code(lcode3d, codeNeg);
        return aux;
    }
    else
    {
        insert_error(eq, add_line_column(to_string("El operador \"", "-", "\" no tiene el operando de tipo Int o Float.")));
        return create_variable(get_variable_name(), Int);
    }
}

/* ---------------------------------------term no-terminal ended----------------------------------------- */

/* ---------------------------------------term terminal ------------------------------------------------- */

/* Return an attribute with the type equal to param type and value equal to  param oper1. */
/* Insert a new code3D Int or Float or Bool in a list of Codes */
Attribute* return_value(LCode3D *lcode3d, PrimitiveType type, char *oper1)
{
    Attribute *aux = create_variable(get_variable_name(), type);
    set_variable_value(aux, type, oper1);

    Code3D *codeValue = new_code(LOAD_CONST);
    switch (type)
    {
        case Int:   set_int(codeValue, 1, atoi(oper1)); break;
        case Float: set_float(codeValue, 1, atof(oper1)); break;
        case Bool:  if (strcmp(oper1, "false") == 0)
                        set_bool(codeValue, 1, False);
                    if (strcmp(oper1, "true") == 0)
                        set_bool(codeValue, 1, True);
                    break;
    }
    set_attribute(codeValue, 2, aux);
    set_null(codeValue, 3);
    add_code(lcode3d, codeValue);
    return aux;
}

/* ---------------------------------------term terminal ended-------------------------------------------- */
