#ifndef Utils_H
#define Utils_H
#include "Attribute.h"
#include "SymbolsTable.h"
#include "../ErrorsQueue/ErrorsQueue.h"
#include "../Code3D/gencode3d.h"
#include "../Code3D/codespecs.h"

/* Returns an attribute of ID "id" and Variable structure. Otherwise returns NULL */
Attribute* getVariableAttribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id);

/* Returns an attribute in the position "pos" of the ID "id" and Array structure. Otherwise returns NULL */
Attribute* getArrayAttribute(ErrorsQueue *eq, Attribute *attr, unsigned int pos);

/* Returns the ReturnType of the method with id "id" */
ReturnType methodReturnType(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id);

/* Returns the return attribute of the method with id "id" */
Attribute* getMethodReturnAttribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id);

/* Sets the return attribute of the method with id "id" */
void setMethodReturnAttribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id, StVariable *value);

/* Returns the respective variable attribute that the method return. "paramSize" is for checking if the amount of parameters is right */
Attribute* checkAndGetMethodRetAttribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char *id, unsigned char paramSize);

/* Returns the type of the attribute, although it is a variable, array or method */
ReturnType getAttributeType(Attribute *attr);

/* Returns the amount of digits that has the int "value" */
unsigned int digitAmount(int value);

/* Returns the string representation of the int "value" */
char* intToString(int value);

/* Returns 0 if the type parameter in "paramSize" position of the method's parameters is equal to the type of "var" 
   and the amount of params are equal.
	Returns 1 otherwise */
unsigned char correctParamBC(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, Attribute *attr, char* lastCalledMethod, unsigned char paramSize);

/* Returns 0 if the type parameter in "paramSize" position of the method's parameters is equal to the type of "var" 
   and paramSize <= than the amount of parameters of the method.
	Returns 1 otherwise */
unsigned char correctParamIC(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, Attribute *attr, char* lastCalledMethod, unsigned char paramSize);

/* Insert an error message if the attribute "attr" isn't a variable of type "type" */
/* Return 1 if ocurred one error, or 0 if all type is ok*/
unsigned char controlType(ErrorsQueue *eq, Attribute *attr, PrimitiveType type);

/* Insert an error message and return 1 if attributes "attr1" and "attr2" aren't of the same type and both variables or arrays
   Returns 0 otherwise */
unsigned char controlAssignation(ErrorsQueue *eq, Attribute *attr1, char* op, Attribute *attr2);

/* Insert an error message if the "lastUsedMethod" haven't got "void" return type */
void checkReturn(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* lastUsedMethod);

/* Insert an error message if the "lastUsedMethod" doesn't return "void" or if it has a different return type that the definition */
/* Return 0 if ocurred one error, or 1 if all type is ok*/
unsigned char checkReturnExpression(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* lastUsedMethod, Attribute *attr);

/* Returns the array at the position specified by attr.decl.variable.value.intValue if attr has "int" type
	Otherwise insert an error message because the attribute haven't got "int" type and create a default variable of "int" type */
Attribute* checkArrayPos(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id, Attribute* attr);

/* Checks if the program have a "main" method and it haven't got parameters */
void checkMain(ErrorsQueue *eq, SymbolsTable *aSymbolsTable);


/* -------------------------------Methods used to form expressions------------------------------ */

/* Return an attribute with the or operation applied to oper1 and oper2. */
/* Insert a new code3D Or in a list of Codes */
Attribute* returnOr(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes);

/* Return an attribute with the and operation applied to oper1 and oper2. */
/* Insert a new code3D And in a list of Codes */
Attribute* returnAnd(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes);

/* Return an attribute with the distinct operation applied to oper1 and oper2. */
/* Insert a new code3D Distinct in a list of Codes */
Attribute* returnDistinct(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes);

/* Return an attribute with the equal operation applied to oper1 and oper2. */
/* Insert a new code3D Equal in a list of Codes */
Attribute* returnEqual(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes);

/* Return an attribute with the minor comparison operation applied to oper1 and oper2. */
/* Insert a new code3D MinorComparison in a list of Codes */
Attribute* returnMinorComparison(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes);

/* Return an attribute with the major comparison operation applied to oper1 and oper2. */
/* Insert a new code3D MajorComparison in a list of Codes */
Attribute* returnMajorComparison(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes);

/* Return an attribute with the greater or equal comparison operation applied to oper1 and oper2. */
/* Insert a new code3D GEqualComparison in a list of Codes */
Attribute* returnGEqualComparison(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes);

/* Return an attribute with the less or equal comparison operation applied to oper1 and oper2. */
/* Insert a new code3D LEqualComparison in a list of Codes */
Attribute* returnLEqualComparison(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes);

/* Return an attribute with the add operation applied to oper1 and oper2. */
/* Insert a new code3D Add in a list of Codes */
Attribute* returnAdd(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes);

/* Return an attribute with the sub operation applied to oper1 and oper2. */
/* Insert a new code3D Sub in a list of Codes */
Attribute* returnSub(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes);

/* Return an attribute with the mod operation applied to oper1 and oper2. */
/* Insert a new code3D Mod in a list of Codes */
Attribute* returnMod(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes);

/* Return an attribute with the div operation applied to oper1 and oper2. */
/* Insert a new code3D Div in a list of Codes */
Attribute* returnDiv(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes);

/* Return an attribute with the mult operation applied to oper1 and oper2. */
/* Insert a new code3D Mult in a list of Codes */
Attribute* returnMult(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *oper2, Attribute *operRes);

/* Return an attribute with the not operation applied to oper1. */
/* Insert a new code3D Not in a list of Codes */
Attribute* returnNot(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *operRes);

/* Return an attribute with the neg operation applied to oper1. */
/* Insert a new code3D Neg in a list of Codes */
Attribute* returnNeg(ErrorsQueue *eq, LCode3D *lcode3d, Attribute *oper1, Attribute *operRes);

/* Return an attribute with the type equal to param type and value equal to  param oper1. */
/* Insert a new code3D Int or Float or Bool in a list of Codes */
Attribute* returnValue(LCode3D *lcode3d, PrimitiveType type, char *oper1, Attribute *operRes);

#endif
