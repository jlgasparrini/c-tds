#ifndef Utils_H
#define Utils_H

/* Returns an attribute of ID "id" and Variable structure. Otherwise returns NULL */
Attribute* getVariableAttribute(SymbolsTable *aSymbolsTable, char* id);

/* Returns an attribute in the position "pos" of the ID "id" and Array structure. Otherwise returns NULL */
Attribute* getArrayAttribute(SymbolsTable *aSymbolsTable, char* id, int pos);

/* creates an attribute and assign it as a parameter of "method" containing the information included.
	Returns a pointer to the attribute if the parameter was created successful. Returns NULL otherwise. */
Attribute* arrangeParameter(SymbolsTable *aSymbolsTable, unsigned char paramSize, char* id, PrimitiveType type); 

/* Returns the ReturnType of the method with id "id" */
ReturnType methodReturnType(SymbolsTable *aSymbolsTable, char* id);

/* Returns 0 if the type parameter in "paramSize" position of the method's parameters is equal to the type of "var" 
   and the amount of params are equal.
	Returns 1 otherwise */
unsigned char correctParamBC(SymbolsTable *aSymbolsTable, Attribute *attr, char* lastCalledMethod, unsigned char paramSize);

/* Returns 0 if the type parameter in "paramSize" position of the method's parameters is equal to the type of "var" 
   and paramSize <= than the amount of parameters of the method.
	Returns 1 otherwise */
unsigned char correctParamIC(SymbolsTable *aSymbolsTable, Attribute *attr, char* lastCalledMethod, unsigned char paramSize);

/* -------------------------------Methods used to form expressions------------------------------ */

/* Return an attribute with the or operation applied to oper1 and oper2. */
Attribute* returnOr(Attribute *oper1, Attribute *oper2);

/* Return an attribute with the and operation applied to oper1 and oper2. */
Attribute* returnAnd(Attribute *oper1, Attribute *oper2);

/* Return an attribute with the distinct operation applied to oper1 and oper2. */
Attribute* returnDistinct(Attribute *oper1, Attribute *oper2);

/* Return an attribute with the equal operation applied to oper1 and oper2. */
Attribute* returnEqual(Attribute *oper1, Attribute *oper2);

/* Return an attribute with the minor comparison operation applied to oper1 and oper2. */
Attribute* returnMinorComparison(Attribute *oper1, Attribute *oper2);

/* Return an attribute with the major comparison operation applied to oper1 and oper2. */
Attribute* returnMajorComparison(Attribute *oper1, Attribute *oper2);

/* Return an attribute with the greater or equal comparison operation applied to oper1 and oper2. */
Attribute* returnGEqualComparison(Attribute *oper1, Attribute *oper2);

/* Return an attribute with the less or equal comparison operation applied to oper1 and oper2. */
Attribute* returnLEqualComparison(Attribute *oper1, Attribute *oper2);

/* Return an attribute with the add operation applied to oper1 and oper2. */
Attribute* returnAdd(Attribute *oper1, Attribute *oper2);

/* Return an attribute with the sub operation applied to oper1 and oper2. */
Attribute* returnSub(Attribute *oper1, Attribute *oper2); 

/* Return an attribute with the mod operation applied to oper1 and oper2. */
Attribute* returnMod(Attribute *oper1, Attribute *oper2); 

/* Return an attribute with the div operation applied to oper1 and oper2. */
Attribute* returnDiv(Attribute *oper1, Attribute *oper2); 

/* Return an attribute with the mult operation applied to oper1 and oper2. */
Attribute* returnMult(Attribute *oper1, Attribute *oper2);

#endif
