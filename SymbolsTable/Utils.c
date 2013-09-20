#include <stdio.h>
#include "Attribute.h"
#include "SymbolsTable.h"
#include "Utils.h"

/* Returns an attribute of ID "id" and Variable structure. Otherwise returns NULL */
Attribute* getVariableAttribute(SymbolsTable *aSymbolsTable, char* id)
{
	Attribute *attr = searchIdInSymbolsTable(aSymbolsTable, id);
	if(attr == NULL) 
        printf("El identificador \"%s\" no esta definido.\n", id);
    else
		if((*attr).type != Variable)
		{
		     printf("El identificador \"%s\" no es una variable.\n", id);
			 return NULL;
		}
	return attr;
}

/* Returns an attribute in the position "pos" of the ID "id" and Array structure. Otherwise returns NULL */
Attribute* getArrayAttribute(SymbolsTable *aSymbolsTable, char* id, int pos)
{
	Attribute *attr = searchIdInSymbolsTable(aSymbolsTable, id);
	if(attr == NULL) 
        printf("El identificador \"%s\" no esta definido.\n", id);
    else
		if((*attr).type != Array)
		{
			printf("El identificador \"%s\" no es una arreglo.\n", id);
			return NULL;
		}
	return attr; /* ACA DEBERIA RETORNARSE LA VARIABLE QUE SE ENCUENTRA EN EL ARREGLO EN LA POSICION "pos"-------------------------------------- */
}


/* creates an attribute and assign it as a parameter of "method" containing the information included.
	Returns a pointer to the attribute if the parameter was created successful. Returns NULL otherwise. */
Attribute* arrangeParameter(SymbolsTable *aSymbolsTable, unsigned char paramSize, char* id, PrimitiveType type)  
{
	Attribute *aux = lastDefinedMethod(aSymbolsTable);
	if (searchIdInLevel(aSymbolsTable, id))
	{	
		aux = createParameter(aux, paramSize, id, type);
		pushElement(aSymbolsTable, aux);
		return aux;
	}
	printf("Error en el metodo \"%s\". El nombre del %d° parametro \"%s\", ya se encuentra utilizado..\n", (*aux).decl.method.id, paramSize, id);  
	return NULL;
}

/* ---------------------------------------expression and conjunction no-terminal---------------------------------------------- */

/* Return an attribute with the or operation applied to oper1 and oper2. */
Attribute* returnOr(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == (*oper2).decl.variable.type && ((*oper2).decl.variable.type == Bool))
        return createVariable("", (*oper1).decl.variable.type);
    return NULL;
}


/* Return an attribute with the and operation applied to oper1 and oper2. */
Attribute* returnAnd(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == (*oper2).decl.variable.type && ((*oper2).decl.variable.type == Bool))
        return createVariable("", (*oper1).decl.variable.type);
    return NULL;

}
/* ---------------------------------------expression and conjunction no-terminal ended-------------------------------------- */

/* ---------------------------------------inequality and comparison no-terminal-------------------------------------------- */

/* Return an attribute with the distinct operation applied to oper1 and oper2. */
Attribute* returnDistinct(Attribute *oper1, Attribute *oper2)
{
    return createVariable("", Bool);
}

/* Return an attribute with the equal operation applied to oper1 and oper2. */
Attribute* returnEqual(Attribute *oper1, Attribute *oper2)
{
    return createVariable("", Bool);
}
/* ------------------------------------inequality and comparison no-terminal ended---------------------------------------- */

/* ---------------------------------------relation no-terminal ------------------------------------------------ */

/* Return an attribute with the minor comparison operation applied to oper1 and oper2. */
Attribute* returnMinorComparison(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == Bool && (*oper2).decl.variable.type == Bool)
        return createVariable("", Bool); /* QUE HACER EN ESTE CASO? FALSE < TRUE == TRUE?? O DIRECTAMENTE MOSTRAR COMO SI ES UN ERROR? 
                                            EN CASO DE QUE SE MUESTRE COMO ERROR, ESTE IF DEBERIA ELIMINARSE --------------------------------*/

    if ((*oper1).decl.variable.type != Bool && (*oper2).decl.variable.type != Bool)
        return createVariable("", Bool);

    return NULL;
}

/* Return an attribute with the major comparison operation applied to oper1 and oper2. */
Attribute* returnMajorComparison(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == Bool && (*oper2).decl.variable.type == Bool)
        return createVariable("", Bool); /* QUE HACER EN ESTE CASO? FALSE > TRUE == FALSE?? O DIRECTAMENTE MOSTRAR COMO SI ES UN ERROR? 
                                            EN CASO DE QUE SE MUESTRE COMO ERROR, ESTE IF DEBERIA ELIMINARSE --------------------------------*/

    if ((*oper1).decl.variable.type != Bool && (*oper2).decl.variable.type != Bool)
        return createVariable("", Bool);

    return NULL;
}

/* Return an attribute with the greater or equal comparison operation applied to oper1 and oper2. */
Attribute* returnGEqualComparison(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == Bool && (*oper2).decl.variable.type == Bool)
        return createVariable("", Bool); /* QUE HACER EN ESTE CASO? FALSE >= TRUE == FALSE?? O DIRECTAMENTE MOSTRAR COMO SI ES UN ERROR? 
                                            EN CASO DE QUE SE MUESTRE COMO ERROR, ESTE IF DEBERIA ELIMINARSE --------------------------------*/

    if ((*oper1).decl.variable.type != Bool && (*oper2).decl.variable.type != Bool)
        return createVariable("", Bool); /*  EL CASO 3 >= 3.2 */

    return NULL;
}

/* Return an attribute with the less or equal comparison operation applied to oper1 and oper2. */
Attribute* returnLEqualComparison(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == Bool && (*oper2).decl.variable.type == Bool)
        return createVariable("", Bool); /* QUE HACER EN ESTE CASO? FALSE <= TRUE == TRUE?? O DIRECTAMENTE MOSTRAR COMO SI ES UN ERROR? 
                                            EN CASO DE QUE SE MUESTRE COMO ERROR, ESTE IF DEBERIA ELIMINARSE --------------------------------*/

    if ((*oper1).decl.variable.type != Bool && (*oper2).decl.variable.type != Bool)
        return createVariable("", Bool);

    return NULL;
}
/* ---------------------------------------relation no-terminal ended---------------------------------------- */

/* ---------------------------------------term no-terminal ------------------------------------------------ */

/* Return an attribute with the add operation. */
Attribute* returnAdd(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == (*oper2).decl.variable.type && ((*oper2).decl.variable.type != Bool))
        return createVariable("", (*oper1).decl.variable.type);
    return NULL;
}

/* Return an attribute with the sub operation. */
Attribute* returnSub(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == (*oper2).decl.variable.type && ((*oper2).decl.variable.type != Bool))
        return createVariable("", (*oper1).decl.variable.type);
    return NULL;
}

/* Return an attribute with the mod operation. */
Attribute* returnMod(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == (*oper2).decl.variable.type && ((*oper2).decl.variable.type != Bool))
        return createVariable("", (*oper1).decl.variable.type);
    return NULL;
}

/* Return an attribute with the div operation. */
Attribute* returnDiv(Attribute *oper1, Attribute *oper2)
{
    if ((*oper1).decl.variable.type == (*oper2).decl.variable.type && ((*oper2).decl.variable.type != Bool))
        return createVariable("", (*oper1).decl.variable.type);
    return NULL;
}

/* Return an attribute with the mult operation. */
Attribute* returnMult(Attribute *oper1, Attribute *oper2)
{
    if (((*oper1).decl.variable.type == (*oper2).decl.variable.type) && ((*oper2).decl.variable.type != Bool))
        return createVariable("", (*oper1).decl.variable.type);
    return NULL;
}

/* ---------------------------------------term no-terminal ended----------------------------------------- */
