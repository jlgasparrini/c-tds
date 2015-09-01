/*
 * MISSING DOCUMENTATION!
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "Utils.h"

#define temp ".temp"
unsigned int number_of_variable = 0;

/* Creates a name for a temporary variable */
char* get_variable_name()
{
  char *name = (char*) malloc ((strlen(temp)+digit_amount(number_of_variable))*sizeof(char));
  strcat(name,temp);
  
  strcat(name,int_to_string(number_of_variable));
  number_of_variable++;
  return name;
}

/* Returns an attribute of ID "id" and Variable structure. Otherwise returns NULL */
Attribute* get_variable_attribute(ErrorsQueue *eq, SymbolsTable *symbols_table, char* id)
{
  Attribute *attribute = search_id_in_symbols_table(eq, symbols_table, id);
  if(attribute != NULL)
  {
    if(get_structure_type(attribute) != Variable)
      insert_error(eq, add_line_column(to_string("El identificador \"", id, "\" no corresponde a una variable.")));
    else
      return attribute;
  }
  return create_variable(get_variable_name(),Int); // Returns an attribute with type Int to continue parsing
}

/* Returns the return attribute of the method with id "id" */
Attribute* get_method_return_attribute(ErrorsQueue *eq, SymbolsTable *symbols_table, char* id)
{
  Attribute *attribute = search_id_in_symbols_table(eq, symbols_table, id);
  if(attribute != NULL)
  {
    if(get_structure_type(attribute) != Method)
      insert_error(eq,add_line_column(to_string("El identificador \"", id,"\" no corresponde a un metodo.")));
    else
    {
      if (get_attribute_type(attribute) == RetVoid)
        insert_error(eq,add_line_column(to_string("El metodo \"", id,"\" retorna void, no puede setearse ningun atributo de retorno.")));
      else
      {
        Attribute *new_attribute = create_variable(get_variable_name(), get_attribute_type(attribute));
        switch (get_attribute_type(attribute))
        {
          case Int:   set_int_val(new_attribute,get_int_val(attribute)); break;
          case Float: set_float_val(new_attribute,get_float_val(attribute)); break;
          case Bool:  set_bool_val(new_attribute,get_int_val(attribute)); break;
          default: break;
        }
        return new_attribute;
      }
    }
  }
  return create_variable(get_variable_name(),Int); // Returns type Int by default in case of having errors
}

/* Sets the return attribute of the method with id "id" */
void set_method_return_attribute(ErrorsQueue *eq, SymbolsTable *symbols_table, char* id, StVariable *value)
{
  Attribute *attribute = search_id_in_symbols_table(eq, symbols_table, id);
  if(attribute != NULL)
  {
    if(get_structure_type(attribute) != Method)
      insert_error(eq,add_line_column(to_string("El identificador \"", id,"\" no corresponde a un metodo.")));
    else
    {
      if (get_attribute_type(attribute) == RetVoid)
        insert_error(eq,add_line_column(to_string("El metodo \"", id,"\" retorna void, no puede setearse ningun atributo de retorno.")));
      else
      {
        switch (value->type)
        {
          case Int:   set_int_val(attribute, value->value.int_val); break;
          case Float: set_float_val(attribute, value->value.float_val); break;
          case Bool:  set_bool_val(attribute, value->value.bool_val); break;
        }  
      }
    }
  }
}

/* Returns the respective variable attribute that the method return. "param_size" is for checking if the amount of parameters is right */
Attribute* check_get_method_ret_attribute(ErrorsQueue *eq, SymbolsTable *symbols_table, ListC3D *list, char *id, unsigned char param_size)
{
  Attribute *attribute = search_id_in_symbols_table(eq, symbols_table, id);
  if (attribute != NULL)
  {
    if (get_structure_type(attribute) != Method)
      insert_error(eq,add_line_column(to_string("El identificador \"", id,"\" no corresponde a un metodo.")));
    else
    {
      if (attribute->decl.method.param_size != param_size)
        insert_error(eq,add_line_column(to_string("El metodo \"", id,"\" no contiene la cantidad correspondiente de parametros.")));
      else
      {
        Attribute *new_attribute = create_variable(get_variable_name(), get_attribute_type(attribute));
        if (get_attribute_type(attribute) != RetVoid)
          add_assignation(list, attribute, new_attribute);
        return new_attribute;
      }
    }
  }
  return create_variable(get_variable_name(),Int); // Returns type Int by default in case of having errors
}

/* Returns 0 if the type of the parameter on the position "pos" of the method "attribute" is equal to the type of "var"
   Returns 1 otherwise */
unsigned char correct_parameter_type(StVariable *var, Attribute *attribute, unsigned char pos)
{
  if (var->type == attribute->decl.method.parameters[pos]->type)
    return 0;
  return 1;
}

/* Returns the ReturnType of the method with id "id" */
ReturnType method_return_type(ErrorsQueue *eq, SymbolsTable *symbols_table, char* id)
{
  Attribute *attribute = search_id_in_symbols_table(eq, symbols_table, id);
  if(attribute != NULL)
  {
    if(get_structure_type(attribute) != Method)
      insert_error(eq, add_line_column(to_string("El identificador \"", id, "\" no corresponde a un metodo.")));
    else
      return get_attribute_type(attribute);
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
  char *string = (char*) malloc (digit_amount(value)*sizeof(char));
  sprintf(string,"%d",value);
  return string;
}

/* Returns the string representation of the float "value" */
char* float_to_string(float value)
{
  char *string = (char*) malloc (sizeof(char)*100);
  sprintf(string, "%f", value);
  return string;
}

/* Returns 0 if the type parameter in "param_size" position of the method's parameters is equal to the type of "var"
   and the amount of params are equal.
   Returns 1 otherwise */
void correct_param_base_case(ErrorsQueue *eq, SymbolsTable *symbols_table, ListC3D *list, Attribute *attribute, char* last_called_method, unsigned char param_size)
{
  Attribute *attr = search_id_in_symbols_table(eq, symbols_table, last_called_method);
  if(attr != NULL)
  {
    if(get_structure_type(attr) != Method)
      insert_error(eq, add_line_column(to_string("El identificador \"", last_called_method, "\" no corresponde a un metodo.")));
    else
    {
      if (param_size+1 == attr->decl.method.param_size)
      {
        if (correct_parameter_type(attribute->decl.variable, attr, param_size) == 0)
        {
          Attribute *param = (Attribute*) malloc (sizeof(Attribute));
          param->decl.variable = attr->decl.method.parameters[param_size]; // obtencion del parametro formal.
          switch (get_attribute_type(attribute))
          {
            case Int:   add_method_call(list, new_code(PARAM_ASSIGN_INT), attribute, param); break;
            case Float: add_method_call(list, new_code(PARAM_ASSIGN_FLOAT), attribute, param); break;
            case Bool:  add_method_call(list, new_code(PARAM_ASSIGN_BOOL), attribute, param); break;
            default: break;
          }
        }
        else
        {
          insert_error(eq,add_line_column(to_string("Error en llamada al método \"", last_called_method, 
            to_string("\". Se esperaba el ", int_to_string(param_size+1), to_string("° argumento de tipo \"", 
              get_type(attr->decl.method.parameters[param_size]->type), to_string("\" pero se encontró de tipo \"", 
                get_type(get_attribute_type(attribute)), "\"."))))));
          Attribute *param = (Attribute*) malloc (sizeof(Attribute));
          param->decl.variable = attr->decl.method.parameters[param_size]; // obtencion del parametro formal.
          param->decl.variable->type = attr->decl.method.parameters[param_size]->type;
          switch (get_attribute_type(param))
          {
            case Int:   add_method_call(list, new_code(PARAM_ASSIGN_INT), create_variable("",Int), param); break;
            case Float: add_method_call(list, new_code(PARAM_ASSIGN_FLOAT), create_variable("",Float), param); break;
            case Bool:  add_method_call(list, new_code(PARAM_ASSIGN_BOOL), create_variable("",Bool), param); break;
            default: break;
          }
        }
      }
      else
        if (param_size < attr->decl.method.param_size)
          insert_error(eq,add_line_column(to_string("Error en llamada al metodo \"", last_called_method, "\". Se tiene menor cantidad de parametros que en su declaracion.")));
        else
          insert_error(eq,add_line_column(to_string("Error en llamada al metodo \"", last_called_method, "\". Se tiene mayor cantidad de parametros que en su declaracion.")));
    }
  }
}

/* Returns 0 if the type parameter in "param_size" position of the method's parameters is equal to the type of "var"
   and param_size <= than the amount of parameters of the method.
   Returns 1 otherwise */
void correct_param_inductive_case(ErrorsQueue *eq, SymbolsTable *symbols_table, ListC3D *list, Attribute *attribute, char* last_called_method, unsigned char param_size)
{
  Attribute *attr = search_id_in_symbols_table(eq, symbols_table, last_called_method);
  if(attr != NULL)
  {
    if(get_structure_type(attr) != Method)
      insert_error(eq, add_line_column(to_string("El identificador \"", last_called_method, "\" no corresponde a un metodo.")));
    else
    {
      if (param_size < attr->decl.method.param_size)
      {
        if (correct_parameter_type(attribute->decl.variable, attr, param_size) == 0)
        {
          Attribute *param = (Attribute*) malloc (sizeof(Attribute));
          param->decl.variable = attr->decl.method.parameters[param_size]; // obtencion del parametro formal.
          param->decl.variable->type = attr->decl.method.parameters[param_size]->type;
          switch (get_attribute_type(attribute))
          {
            case Int:   add_method_call(list, new_code(PARAM_ASSIGN_INT), attribute, param); break;
            case Float: add_method_call(list, new_code(PARAM_ASSIGN_FLOAT), attribute, param); break;
            case Bool:  add_method_call(list, new_code(PARAM_ASSIGN_BOOL), attribute, param); break;
            default: break;
          }
        }
        else
        {
          insert_error(eq,add_line_column(to_string("Error en llamada al método \"", last_called_method, 
            to_string("\". Se esperaba el ", int_to_string(param_size+1), to_string("° argumento de tipo \"", 
              get_type(attr->decl.method.parameters[param_size]->type), to_string("\" pero se encontró de tipo \"", 
                get_type(get_attribute_type(attribute)), "\"."))))));
          Attribute *param = (Attribute*) malloc (sizeof(Attribute));
          param->decl.variable = attr->decl.method.parameters[param_size]; // obtencion del parametro formal.
          param->decl.variable->type = attr->decl.method.parameters[param_size]->type;
          switch (get_attribute_type(param))
          {
            case Int:   add_method_call(list, new_code(PARAM_ASSIGN_INT), create_variable("",Int), param); break;
            case Float: add_method_call(list, new_code(PARAM_ASSIGN_FLOAT), create_variable("",Float), param); break;
            case Bool:  add_method_call(list, new_code(PARAM_ASSIGN_BOOL), create_variable("",Bool), param); break;
            default: 		break;
          }
        }
      }
    }
  }
}

void extern_param_assign(ListC3D *list, Attribute *param, unsigned char paramNumber)
{
  switch (get_attribute_type(param))
  {
    case Int:   add_param_externinvk(list, new_code(EXTERN_PARAM_ASSIGN_INT), param, paramNumber); break;
    case Float: add_param_externinvk(list, new_code(EXTERN_PARAM_ASSIGN_FLOAT), param, paramNumber); break;
    case Bool:  add_param_externinvk(list, new_code(EXTERN_PARAM_ASSIGN_BOOL), param, paramNumber); break;
    default: 		break;
  }
}

/* Insert an error message if the attribute "attribute" isn't a variable of type "type" */
/* Return 1 if ocurred one error, or 0 if all type is ok*/
unsigned char control_type(ErrorsQueue *eq, Attribute *attribute, PrimitiveType type, char *operation, int number_of_expression)
{
  if (get_attribute_type(attribute) != type)
  {
    if (number_of_expression == 1)
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
      sprintf(number,"%d",number_of_expression);

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
unsigned char control_assignation(ErrorsQueue *eq, ListC3D *list, Attribute *attr1, char* op, Attribute *attr2)
{
  if (get_structure_type(attr1) != Method)
  {
    if (get_attribute_type(attr1) != get_attribute_type(attr2))
      insert_error(eq, add_line_column(to_string("El lado derecho de la asignacion debe ser de tipo \"", get_type(get_attribute_type(attr1)), "\".")));
    else
    {
      Code3D *add;
      if (strcmp(op, "=") == 0)
				add_assignation(list, attr2, attr1);
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
        Attribute *result = create_variable(get_variable_name(), get_attribute_type(attr1));
        set_c3D(add, attr1, attr2, result);
        add_code(list, add);
				add_assignation(list, result, attr1);
      }
      return 0;
    }
  }
  else
    insert_error(eq, add_line_column(to_string("El identificador izquierdo de la asignacion ", "", " no debe ser un metodo.")));
  return 1;
}

/* Insert an error message if the "last_used_method" haven't got "void" return type */
unsigned char check_return(ErrorsQueue *eq, SymbolsTable *symbols_table, char* last_used_method)
{
  ReturnType return_type = method_return_type(eq, symbols_table, last_used_method);
  if (return_type != RetVoid)
  {
    char* msg = (char*) malloc ((strlen("\" debe retornar una expresion de tipo \"")+strlen(get_type(return_type))+strlen("\"."))*sizeof(char));
    strcat(msg, "\" debe retornar una expresion de tipo \"");
    strcat(msg, get_type(return_type));
    strcat(msg, "\".");
    insert_error(eq, add_line_column(to_string("El metodo \"", last_used_method, msg))); 
    return 1;
  }
  return 0;
}

/* Insert an error message if the "last_used_method" doesn't return "void" or if it has a different return type that the definition */
/* Return 1 if ocurred one error, or 0 if all type is ok*/
unsigned char check_return_expression(ErrorsQueue *eq, SymbolsTable *symbols_table, char* last_used_method, Attribute *attribute)
{
  ReturnType return_type = method_return_type(eq, symbols_table, last_used_method);
  if (return_type == RetVoid)
  {
    insert_error(eq, add_line_column(to_string("El metodo \"",last_used_method,"\" no puede retornar una expresion ya que retorna void.")));
    return 1;
  }
  else
    if (return_type != get_attribute_type(attribute))
    {
      char* msg = (char*) malloc ((strlen("\" debe retornar una expresion de tipo \"")+strlen(get_type(return_type))+strlen("\", no de tipo \"")+strlen(get_type(get_attribute_type(attribute)))+strlen("\"."))*sizeof(char));
      strcat(msg, "\" debe retornar una expresion de tipo \"");
      strcat(msg, get_type(return_type));
      strcat(msg, "\", no de tipo \"");
      strcat(msg, get_type(get_attribute_type(attribute)));
      strcat(msg, "\".");
      insert_error(eq, add_line_column(to_string("El metodo \"", last_used_method, msg)));
      return 1;
    }
    else
      // assign the expression in attribute to the method return expression
      set_method_return_attribute(eq,symbols_table, last_used_method, attribute->decl.variable);
  return 0;
}

/* Returns the array at the position specified by attribute.decl.variable.value.intValue if attribute has "int" type
   Otherwise insert an error message because the attribute haven't got "int" type and create a default variable of "int" type */
Attribute* check_array_pos(ErrorsQueue *eq, SymbolsTable *symbols_table, ListC3D *list, char* id, Attribute* attribute)
{
  Attribute *attr = search_id_in_symbols_table(eq,symbols_table,id);
  if (attr != NULL)
  {
    if(get_structure_type(attr) != Array)
      insert_error(eq, add_line_column(to_string("El identificador \"", id, "\" no corresponde a un arreglo.")));
    else
    {
      if (get_attribute_type(attribute) == Int)
      {
        if (get_int_val(attribute) >= 0 && get_int_val(attribute) < attr->decl.array.length)
        {
          Attribute *variable = create_variable(get_variable_name(), get_attribute_type(attr));
          increase_var_offset();
          variable->decl.variable->offset = get_offset_array(attr) + (get_int_val(attribute)*4);
           // variable->decl.variable->offset = attr->decl.array.arrayValues[get_int_val(attribute)].offset;
          Code3D *codeArrayValue = new_code(LOAD_ARRAY);
          set_attribute(codeArrayValue, 1, attribute);
          set_attribute(codeArrayValue, 2, attr);
          set_attribute(codeArrayValue, 3, variable);
          add_code(list, codeArrayValue);
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
void check_main(ErrorsQueue *eq, SymbolsTable *symbols_table)
{
  Attribute *attribute = search_id_in_symbols_table(eq, symbols_table,"main");
  if (attribute == NULL)
    insert_error(eq, "El programa no tiene un metodo \"main\".");
  else
    if (get_structure_type(attribute) != Method)
      insert_error(eq, "El identificador \"main\" solo puede ser un metodo.");
}

/* ---------------------------------------expression and conjunction no-terminal---------------------------------------------- */

/* Return an attribute with the or operation applied to oper1 and oper2. */
/* Insert a new code3D OR in a list of Codes */
Attribute* return_or(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2)
{
  if (get_attribute_type(oper1) == get_attribute_type(oper2) && (get_attribute_type(oper2) == Bool))
  {
    Attribute *attr = create_variable(get_variable_name(), Bool);
    Code3D *code_or = new_code(OR);
    set_c3D(code_or, oper1, oper2, attr);
    add_code(list, code_or);
    return attr;
  }
  else
  {
    insert_error(eq, add_line_column(to_string("La expresion logica \"", "OR", "\" no tiene ambos operandos de tipo booleano.")));
    return create_variable(get_variable_name(), Bool);
  }
}


/* Return an attribute with the and operation applied to oper1 and oper2. */
/* Insert a new code3D And in a list of Codes */
Attribute* return_and(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2)
{
  if (get_attribute_type(oper1) == get_attribute_type(oper2) && (get_attribute_type(oper2) == Bool))
  {
    Attribute *attr = create_variable(get_variable_name(), Bool);
    Code3D *code_and = new_code(AND);
    set_c3D(code_and, oper1, oper2, attr);
    add_code(list, code_and);
    return attr;
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
Attribute* return_distinct(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2)
{
  if (get_attribute_type(oper1) == get_attribute_type(oper2))
  {
    Attribute *attr = create_variable(get_variable_name(), Bool);
    Code3D *code_dist;
    switch (get_attribute_type(oper1))
    {
      case Int:   code_dist = new_code(DIST_INT); break;
      case Float: code_dist = new_code(DIST_FLOAT); break;
      case Bool:  code_dist = new_code(DIST_BOOL); break;
      default: 		break;
    }
    set_c3D(code_dist, oper1, oper2, attr);
    add_code(list, code_dist);
    return attr;
  }
  else
  {
    insert_error(eq, add_line_column(to_string("El operador \"", "!=", "\" no tiene ambos operandos del mismo tipo.")));
    return create_variable(get_variable_name(), Bool);
  }
}

/* Return an attribute with the equal operation applied to oper1 and oper2. */
/* Insert a new code3D Equal in a list of Codes */
Attribute* return_equal(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2)
{
  if (get_attribute_type(oper1) == get_attribute_type(oper2))
  {
    Attribute *attr = create_variable(get_variable_name(), Bool);
    Code3D *code_equal;
    switch (get_attribute_type(oper1))
    {
      case Int:   code_equal = new_code(EQ_INT); break;
      case Float: code_equal = new_code(EQ_FLOAT); break;
      case Bool:  code_equal = new_code(EQ_BOOL); break;
      default: 		break;
    }
    set_c3D(code_equal, oper1, oper2, attr);
    add_code(list, code_equal);
    return attr;
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
Attribute* return_minor_comparison(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2)
{
  if ((get_attribute_type(oper1) == get_attribute_type(oper2)) && (get_attribute_type(oper2) != Bool))
  {
    Attribute *attr = create_variable(get_variable_name(), Bool);
    Code3D *code_minor;
    if (get_attribute_type(oper1) == Float)
      code_minor = new_code(LOWER_FLOAT);
    else
      code_minor = new_code(LOWER_INT);
    set_c3D(code_minor, oper1, oper2, attr);
    add_code(list, code_minor);
    return attr;
  }
  else
  {
    insert_error(eq, add_line_column(to_string("El operador \"", "<", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")));
    return create_variable(get_variable_name(), Bool);
  }
}

/* Return an attribute with the major comparison operation applied to oper1 and oper2. */
/* Insert a new code3D MajorComparison in a list of Codes */
Attribute* return_major_comparison(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2)
{
  if ((get_attribute_type(oper1) == get_attribute_type(oper2)) && (get_attribute_type(oper2) != Bool))
  {
    Attribute *attr = create_variable(get_variable_name(), Bool);
    Code3D *code_great;
    if (get_attribute_type(oper1) == Float)
      code_great = new_code(GREATER_FLOAT);
    else
      code_great = new_code(GREATER_INT);
    set_c3D(code_great, oper1, oper2, attr);
    add_code(list, code_great);
    return attr;
  }
  else
  {
    insert_error(eq, add_line_column(to_string("El operador \"", ">", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")));
    return create_variable(get_variable_name(), Bool);
  }
}

/* Return an attribute with the greater or equal comparison operation applied to oper1 and oper2. */
/* Insert a new code3D GEqualComparison in a list of Codes */
Attribute* return_g_equal_comparison(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2)
{
  if ((get_attribute_type(oper1) == get_attribute_type(oper2)) && (get_attribute_type(oper2) != Bool))
  {
    Attribute *attr = create_variable(get_variable_name(), Bool);
    Code3D *code_g_equal;
    if (get_attribute_type(oper1) == Float)
      code_g_equal = new_code(GEQ_FLOAT);
    else
      code_g_equal = new_code(GEQ_INT);
    set_c3D(code_g_equal, oper1, oper2, attr);
    add_code(list, code_g_equal);
    return attr;
  }
  else
  {
    insert_error(eq, add_line_column(to_string("El operador \"", ">=", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")));
    return create_variable(get_variable_name(), Bool);
  }
}

/* Return an attribute with the less or equal comparison operation applied to oper1 and oper2. */
/* Insert a new code3D LEqualComparison in a list of Codes */
Attribute* return_l_equal_comparison(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2)
{
  if ((get_attribute_type(oper1) == get_attribute_type(oper2)) && (get_attribute_type(oper2) != Bool))
  {
    Attribute *attr = create_variable(get_variable_name(), Bool);
    Code3D *code_l_equal;
    if (get_attribute_type(oper1) == Float)
      code_l_equal = new_code(LEQ_FLOAT);
    else
      code_l_equal = new_code(LEQ_INT);
    set_c3D(code_l_equal, oper1, oper2, attr);
    add_code(list, code_l_equal);
    return attr;
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
Attribute* return_add(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2)
{
  if ((get_attribute_type(oper1) == get_attribute_type(oper2)) && (get_attribute_type(oper2) != Bool))
  {
    Code3D *code_add;
    Attribute *attr = create_variable(get_variable_name(), get_attribute_type(oper1));
    if (get_attribute_type(oper1) == Float)
      code_add = new_code(ADD_FLOAT);
    else
      code_add = new_code(ADD_INT);
    set_c3D(code_add, oper1, oper2, attr);
    add_code(list, code_add);
    return attr;
  }
  else
  {
    insert_error(eq, add_line_column(to_string("El operador \"", "+", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")));
    return create_variable(get_variable_name(), Int);
  }
}

/* Return an attribute with the sub operation. */
/* Insert a new code3D Sub in a list of Codes */
Attribute* return_sub(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2)
{
  if (get_attribute_type(oper1) == get_attribute_type(oper2) && (get_attribute_type(oper2) != Bool))
  {
    Code3D *code_sub;
    Attribute *attr = create_variable(get_variable_name(), get_attribute_type(oper1));
    if (get_attribute_type(oper1) == Float)
      code_sub = new_code(MINUS_FLOAT);
    else
      code_sub = new_code(MINUS_INT);
    set_c3D(code_sub, oper1, oper2, attr);
    add_code(list, code_sub);
    return attr;
  }
  else
  {
    insert_error(eq, add_line_column(to_string("El operador \"", "-", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")));
    return create_variable(get_variable_name(), Int);
  }
}

/* Return an attribute with the mod operation. */
/* Insert a new code3D Mod in a list of Codes */
Attribute* return_mod(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2)
{
  if (get_attribute_type(oper1) == get_attribute_type(oper2) && (get_attribute_type(oper2) == Int))
  {
    Attribute *attr = create_variable(get_variable_name(), get_attribute_type(oper1));
    Code3D *code_mod;
    code_mod = new_code(MOD_INT);
    set_c3D(code_mod, oper1, oper2, attr);
    add_code(list, code_mod);
    return attr;
  }
  else
  {
    insert_error(eq, add_line_column(to_string("El operador \"", "%", "\" solo soporta tipo INT y/o no tiene ambos operandos del mismo tipo.")));
    return create_variable(get_variable_name(), Int);
  }
}

/* Return an attribute with the div operation. */
/* Insert a new code3D Div in a list of Codes */
Attribute* return_div(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2)
{
  if (get_attribute_type(oper1) == get_attribute_type(oper2) && (get_attribute_type(oper2) != Bool))
  {
    Code3D *code_div;
    Attribute *attr = create_variable(get_variable_name(), get_attribute_type(oper1));
    if (get_attribute_type(oper1) == Float)
      code_div = new_code(DIV_FLOAT);
    else
      code_div = new_code(DIV_INT);
    set_c3D(code_div, oper1, oper2, attr);
    add_code(list, code_div);
    return attr;
  }
  else
  {
    insert_error(eq, add_line_column(to_string("El operador \"", "/", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")));
    return create_variable(get_variable_name(), Int);
  }
}

/* Return an attribute with the mult operation. */
/* Insert a new code3D Mult in a list of Codes */
Attribute* return_mult(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2)
{
  if (get_attribute_type(oper1) == get_attribute_type(oper2) && (get_attribute_type(oper2) != Bool))
  {
    Code3D *code_mult;
    Attribute *attr = create_variable(get_variable_name(), get_attribute_type(oper1));
    if (get_attribute_type(oper1) == Float)
      code_mult = new_code(MULT_FLOAT);
    else
      code_mult = new_code(MULT_INT);
    set_c3D(code_mult, oper1, oper2, attr);
    add_code(list, code_mult);
    return attr;
  }
  else
  {
    insert_error(eq, add_line_column(to_string("El operador \"", "*", "\" no tiene ambos operandos de tipo correcto o del mismo tipo.")));
    return create_variable(get_variable_name(), Int);
  }
}

/* Return an attribute with the not operation applied to oper1. */
/* Insert a new code3D Not in a list of Codes */
Attribute* return_not(ErrorsQueue *eq, ListC3D *list, Attribute *oper1)
{
  if (get_attribute_type(oper1) == Bool)
  {
    Attribute *attr = create_variable(get_variable_name(), Bool);
    Code3D *code_not = new_code(NOT);
    set_c2D(code_not, oper1, attr);
    add_code(list, code_not);
    return attr;
  }
  else
  {
    insert_error(eq, add_line_column(to_string("El operador \"", "!", "\" no tiene el operando de tipo booleano.")));
    return create_variable(get_variable_name(), Bool);
  }
}

/* Return an attribute with the neg operation applied to oper1. */
/* Insert a new code3D Neg in a list of Codes */
Attribute* return_neg(ErrorsQueue *eq, ListC3D *list, Attribute *oper1)
{
  if (get_attribute_type(oper1) == Int || get_attribute_type(oper1) == Float)
  {
    Code3D *code_neg;
    Attribute *attr = create_variable(get_variable_name(), get_attribute_type(oper1));
    if (get_attribute_type(oper1) == Float)
      code_neg = new_code(NEG_FLOAT);
    else
      code_neg = new_code(NEG_INT);
    set_c2D(code_neg, oper1, attr);
    add_code(list, code_neg);
    return attr;
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
Attribute* return_value(ListC3D *list, PrimitiveType type, char *oper1)
{
  Attribute *attr = create_variable(get_variable_name(), type);
  set_variable_value(attr, type, oper1);

  Code3D *code_value = new_code(LOAD_CONST);
  switch (type)
  {
    case Int:   set_int(code_value, 1, atoi(oper1)); break;
    case Float: set_float(code_value, 1, atof(oper1)); break;
    case Bool:  if (strcmp(oper1, "false") == 0)
                  set_bool(code_value, 1, False);
                if (strcmp(oper1, "true") == 0)
                  set_bool(code_value, 1, True);
                break;
  }
  set_attribute(code_value, 2, attr);
  set_null(code_value, 3);
  add_code(list, code_value);
  return attr;
}

/* ---------------------------------------term terminal ended-------------------------------------------- */
