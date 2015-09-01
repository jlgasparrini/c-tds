/*
 * MISSING DOCUMENTATION!
*/

#ifndef Utils_H
#define Utils_H

#include "SymbolsTable.h"
#include "../errors_queue/errors_queue.h"
#include "../code_3d/gencode3d.h"
#include "../code_3d/operations_code.h"

/* Creates a name for a temporary variable */
char* get_variable_name();

/* Returns an attribute of ID "id" and Variable structure. Otherwise returns NULL */
Attribute* get_variable_attribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id);

/* Returns the ReturnType of the method with id "id" */
ReturnType method_return_type(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id);

/* Returns the return attribute of the method with id "id" */
Attribute* get_method_return_attribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id);

/* Sets the return attribute of the method with id "id" */
void set_method_return_attribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id, StVariable *value);

/* Returns the respective variable attribute that the method return. "paramSize" is for checking if the amount of parameters is right */
Attribute* check_get_method_ret_attribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, ListC3D *list, char *id, unsigned char paramSize);

/* Returns the type of the attribute, although it is a variable, array or method */
ReturnType get_attribute_type(Attribute *attr);

/* Returns the amount of digits that has the int "value" */
unsigned int digit_amount(int value);

/* Returns the string representation of the int "value" */
char* int_to_string(int value);

/* Returns the string representation of the float "value" */
char* float_to_string(float value);

/* Checks if the type parameter in "paramSize" position of the method's parameters is equal to the type of "var"
   and the amount of params are equal. */
void correct_param_base_case(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, ListC3D *list, Attribute *attr, char* lastCalledMethod, unsigned char paramSize);

/* Checks if if the type parameter in "paramSize" position of the method's parameters is equal to the type of "var"
   and paramSize <= than the amount of parameters of the method. */
void correct_param_inductive_case(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, ListC3D *list, Attribute *attr, char* lastCalledMethod, unsigned char paramSize);

/**/
void extern_param_assign(ListC3D *list, Attribute *param, unsigned char paramNumber);

/* Insert an error message if the attribute "attr" isn't a variable of type "type" */
/* Return 1 if ocurred one error, or 0 if all type is ok*/
unsigned char control_type(ErrorsQueue *eq, Attribute *attr, PrimitiveType type, char *operation, int numberOfExpression);

/* Insert an error message and return 1 if attributes "attr1" and "attr2" aren't of the same type and both variables or arrays
   Returns 0 otherwise */
unsigned char control_assignation(ErrorsQueue *eq, ListC3D *list, Attribute *attr1, char* op, Attribute *attr2);

/* Insert an error message if the "lastUsedMethod" haven't got "void" return type */
unsigned char check_return(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* lastUsedMethod);

/* Insert an error message if the "lastUsedMethod" doesn't return "void" or if it has a different return type that the definition */
/* Return 0 if ocurred one error, or 1 if all type is ok*/
unsigned char check_return_expression(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* lastUsedMethod, Attribute *attr);

/* Returns the array at the position specified by attr.decl.variable.value.intValue if attr has "int" type
	Otherwise insert an error message because the attribute haven't got "int" type and create a default variable of "int" type */
Attribute* check_array_pos(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, ListC3D *list, char* id, Attribute* attr);

/* Checks if the program have a "main" method and it haven't got parameters */
void check_main(ErrorsQueue *eq, SymbolsTable *aSymbolsTable);


/* -------------------------------Methods used to form expressions------------------------------ */

/* Return an attribute with the or operation applied to oper1 and oper2. */
/* Insert a new code3D Or in a list of Codes */
Attribute* return_or(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the and operation applied to oper1 and oper2. */
/* Insert a new code3D And in a list of Codes */
Attribute* return_and(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the distinct operation applied to oper1 and oper2. */
/* Insert a new code3D Distinct in a list of Codes */
Attribute* return_distinct(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the equal operation applied to oper1 and oper2. */
/* Insert a new code3D Equal in a list of Codes */
Attribute* return_equal(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the minor comparison operation applied to oper1 and oper2. */
/* Insert a new code3D MinorComparison in a list of Codes */
Attribute* return_minor_comparison(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the major comparison operation applied to oper1 and oper2. */
/* Insert a new code3D MajorComparison in a list of Codes */
Attribute* return_major_comparison(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the greater or equal comparison operation applied to oper1 and oper2. */
/* Insert a new code3D GEqualComparison in a list of Codes */
Attribute* return_g_equal_comparison(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the less or equal comparison operation applied to oper1 and oper2. */
/* Insert a new code3D LEqualComparison in a list of Codes */
Attribute* return_l_equal_comparison(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the add operation applied to oper1 and oper2. */
/* Insert a new code3D Add in a list of Codes */
Attribute* return_add(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the sub operation applied to oper1 and oper2. */
/* Insert a new code3D Sub in a list of Codes */
Attribute* return_sub(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the mod operation applied to oper1 and oper2. */
/* Insert a new code3D Mod in a list of Codes */
Attribute* return_mod(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the div operation applied to oper1 and oper2. */
/* Insert a new code3D Div in a list of Codes */
Attribute* return_div(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the mult operation applied to oper1 and oper2. */
/* Insert a new code3D Mult in a list of Codes */
Attribute* return_mult(ErrorsQueue *eq, ListC3D *list, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the not operation applied to oper1. */
/* Insert a new code3D Not in a list of Codes */
Attribute* return_not(ErrorsQueue *eq, ListC3D *list, Attribute *oper1);

/* Return an attribute with the neg operation applied to oper1. */
/* Insert a new code3D Neg in a list of Codes */
Attribute* return_neg(ErrorsQueue *eq, ListC3D *list, Attribute *oper1);

/* Return an attribute with the type equal to param type and value equal to  param oper1. */
/* Insert a new code3D Int or Float or Bool in a list of Codes */
Attribute* return_value(ListC3D *list, PrimitiveType type, char *oper1);

#endif
