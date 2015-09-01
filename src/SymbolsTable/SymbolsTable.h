/**
* HEADER
*
* Contiene una estructura similar a una PILA con métodos para operarla
*/

#ifndef SymbolsTable_H
#define SymbolsTable_H

#include "LinkedList.h"
#include "../errors_queue/errors_queue.h"

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
  /* Current current_level of the SymbolsTable. */
  int current_level;
} SymbolsTable;

/* Initializes the SymbolsTable */
SymbolsTable* initialize_symbols_table();

/* Insert a element in the current level of the SymbolsTable. */
void push_element(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, Attribute *at);

/* Insert a new level in the SymbolsTable. */
void push_level(SymbolsTable *aSymbolsTable);

/* Remove the entire current level of the SymbolsTable. */
void pop_level(SymbolsTable *aSymbolsTable);

/* Searches for the element in all levels of the SymbolsTable. */
Attribute* search_id_in_symbols_table(ErrorsQueue *eq, SymbolsTable *aSymbolsTable, char *id);

/* Print the elements the SymbolsTable. */
void symbols_table_print(SymbolsTable *aSymbolsTable);

#endif
