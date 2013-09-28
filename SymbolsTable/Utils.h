#ifndef Utils_H
#define Utils_H
#include "Attribute.h"
#include "SymbolsTable.h"

#include "../ErrorsQueue/ErrorsQueue.h"
/* Returns an attribute of ID "id" and Variable structure. Otherwise returns NULL */
Attribute* getVariableAttribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id);

/* Returns an attribute in the position "pos" of the ID "id" and Array structure. Otherwise returns NULL */
Attribute* getArrayAttribute(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, Attribute *attr, unsigned int pos);

/* Returns the ReturnType of the method with id "id" */
ReturnType methodReturnType(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id);

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
void controlVariableType(ErrorsQueue *eq, Attribute *attr, PrimitiveType type);

/* Insert an error message if attributes "attr1" and "attr2" aren't of the same type and both variables or arrays */
void controlAssignation(ErrorsQueue *eq, Attribute *attr1, char* op, Attribute *attr2);

/* Insert an error message if the "lastUsedMethod" haven't got "void" return type */
void checkReturn(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* lastUsedMethod);

/* Insert an error message if the "lastUsedMethod" doesn't return "void" or if it has a different return type that the definition */
void checkReturnExpression(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* lastUsedMethod, Attribute *attr);

/* Returns the array at the position specified by attr.decl.variable.value.intValue if attr has "int" type
	Otherwise insert an error message because the attribute haven't got "int" type and create a default variable of "int" type */
Attribute* checkArrayPos(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char* id, Attribute* attr);

/* Checks if the program have a "main" method and it haven't got parameters */
void checkMain(ErrorsQueue *eq, SymbolsTable *aSymbolsTable);


/* -------------------------------Methods used to form expressions------------------------------ */

/* Return an attribute with the or operation applied to oper1 and oper2. */
Attribute* returnOr(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the and operation applied to oper1 and oper2. */
Attribute* returnAnd(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the distinct operation applied to oper1 and oper2. */
Attribute* returnDistinct(Attribute *oper1, Attribute *oper2);

/* Return an attribute with the equal operation applied to oper1 and oper2. */
Attribute* returnEqual(Attribute *oper1, Attribute *oper2);

/* Return an attribute with the minor comparison operation applied to oper1 and oper2. */
Attribute* returnMinorComparison(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the major comparison operation applied to oper1 and oper2. */
Attribute* returnMajorComparison(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the greater or equal comparison operation applied to oper1 and oper2. */
Attribute* returnGEqualComparison(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the less or equal comparison operation applied to oper1 and oper2. */
Attribute* returnLEqualComparison(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the add operation applied to oper1 and oper2. */
Attribute* returnAdd(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2);

/* Return an attribute with the sub operation applied to oper1 and oper2. */
Attribute* returnSub(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2); 

/* Return an attribute with the mod operation applied to oper1 and oper2. */
Attribute* returnMod(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2); 

/* Return an attribute with the div operation applied to oper1 and oper2. */
Attribute* returnDiv(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2); 

/* Return an attribute with the mult operation applied to oper1 and oper2. */
Attribute* returnMult(ErrorsQueue *eq, Attribute *oper1, Attribute *oper2);

#endif
