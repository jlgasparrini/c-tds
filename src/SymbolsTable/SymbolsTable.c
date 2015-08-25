#include <stdio.h>
#include <stdlib.h>
#include "SymbolsTable.h"

/* Initializes the SymbolsTable */
SymbolsTable* initializeSymbolsTable()
{
	SymbolsTable *aSymbolsTable = (SymbolsTable*) malloc(sizeof(SymbolsTable));
    aSymbolsTable->top = NULL;
	aSymbolsTable->currentLevel = 0;
	return aSymbolsTable;
}

/* Insert a element in the current level of the SymbolsTable. */
void pushElement(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, Attribute *at)
{
	if (aSymbolsTable->currentLevel > 0)
	{
        if (at!=NULL)
        {
            if (searchIdInLevel(aSymbolsTable, getID(at)) != NULL)
                insert_error(eq, to_string("El identificador \"", getID(at), "\" ya se encuentra en uso."));
            else
                insert(aSymbolsTable->top->list, at);
        }
			else
                insert_error(eq, to_string("El atributo es NULL.","",""));
	}
	else
		printf("%s\n",to_string("SymbolsTable: pushElement Warning: la tabla no tiene ningun nivel.","",""));
}

/* Insert a new level in the SymbolsTable. */
void pushLevel(SymbolsTable *aSymbolsTable)
{
	SymbolsTableNode *newLevel = (SymbolsTableNode*) malloc (sizeof(SymbolsTableNode));
	if (newLevel)
    {
        newLevel->list = initialize();
		    newLevel->next = aSymbolsTable->top;
		    aSymbolsTable->top = newLevel;
		    aSymbolsTable->currentLevel++;
    }
    else
        printf("%s\n",to_string("SymbolsTable: pushLevel Warning: Error al reservar espacio en memoria.","",""));
}

/* Remove the entire current level of the SymbolsTable. */
void popLevel(SymbolsTable *aSymbolsTable)
{
    if (aSymbolsTable->currentLevel > 0)
    {
		SymbolsTableNode *auxNode = aSymbolsTable->top;
        aSymbolsTable->top = aSymbolsTable->top->next;
        deleteAll(auxNode->list);
        free(auxNode);
		aSymbolsTable->currentLevel--;
    }
    else
		printf("%s\n",to_string("SymbolsTable: popLevel Warning: Pila sin mas niveles que descartar.","",""));
}

/* Searches for the id in all levels of the SymbolsTable.
 * Return Attribute* iff the id was't found. NULL if the id wasn't found.
 */
Attribute* searchIdInSymbolsTable(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char *id)
{
	int i;
	SymbolsTableNode *auxTop = aSymbolsTable->top;
    Attribute *auxAttr;
	for (i = aSymbolsTable->currentLevel; i > 0; i--)
	{
        auxAttr = search((auxTop->list), id);
		if (auxAttr != NULL)
			return auxAttr;
		auxTop = auxTop->next;
	}
	insert_error(eq, to_string("El identificador \"", id, "\" no esta definido."));
    return NULL;
}

/* Searches for the id in the current level of the SymbolsTable.
 * Return Attribute* iff the id was't found. NULL if the id wasn't found.
 */
Attribute* searchIdInLevel(SymbolsTable *aSymbolsTable, char *id)
{
    SymbolsTableNode *auxTop = aSymbolsTable->top;
    Attribute *auxAttr = search(auxTop->list, id);
    return auxAttr;
}

/* Print the elements the SymbolsTable. */
void SymbolsTable_print(SymbolsTable *aSymbolsTable)
{
    SymbolsTableNode *aux = aSymbolsTable->top;
    int i;
    for (i = 0; i < aSymbolsTable->currentLevel; i++)
    {
        printf("%d° nivel:\n", aSymbolsTable->currentLevel - i);
		print_list(aux->list);
        printf("---------------------------------------------\n");
        aux = aux->next;
    }
}
