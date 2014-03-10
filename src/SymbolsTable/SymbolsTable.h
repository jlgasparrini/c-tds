/**
* HEADER
* 
* Contiene una estructura similar a una PILA con métodos para operarla
*/

#ifndef SymbolsTable_H
#define SymbolsTable_H

#include "LinkedList.h"
#include "../ErrorsQueue/ErrorsQueue.h"
 
typedef struct SNode  
{
	/* Reference to a list. */
	LinkedList *list;
	/* Reference to the next node of the SymbolsTable */	
	struct SNode *next;
} SymbolsTableNode;

/* Define type SymbolsTable. */
typedef struct
{
    /* Reference to the top of the SymbolsTable. */
    SymbolsTableNode *top;
    /* Current currentLevel of the SymbolsTable. */
    int currentLevel;
} SymbolsTable;

/* Initializes the SymbolsTable */
SymbolsTable* initializeSymbolsTable();

/* Insert a element in the current level of the SymbolsTable. */
void pushElement(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, Attribute *at);

/* Insert a new level in the SymbolsTable. */
void pushLevel(SymbolsTable *aSymbolsTable);
 
/* Remove the entire current level of the SymbolsTable. */
void popLevel(SymbolsTable *aSymbolsTable);

/* Searches for the element in all levels of the SymbolsTable. */
Attribute* searchIdInSymbolsTable(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char *id);

/* Searches for the id in the current level of the SymbolsTable. */ 
Attribute* searchIdInLevel(SymbolsTable *aSymbolsTable, char *id); 
 
/* Print the elements the SymbolsTable. */
void SymbolsTable_print(SymbolsTable *aSymbolsTable);

#endif
