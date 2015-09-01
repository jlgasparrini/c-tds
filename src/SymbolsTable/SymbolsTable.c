#include <stdio.h>
#include <stdlib.h>
#include "SymbolsTable.h"

/* Initializes the SymbolsTable */
SymbolsTable* initialize_symbols_table()
{
	SymbolsTable *symbols_table = (SymbolsTable*) malloc(sizeof(SymbolsTable));
  symbols_table->top = NULL;
  symbols_table->current_level = 0;
  return symbols_table;
}

/* Searches for the id in the current level of the SymbolsTable.
 * Return Attribute* iff the id was't found. NULL if the id wasn't found.
 */
 Attribute* search_id_in_level(SymbolsTable *symbols_table, char *id)
 {
  SymbolsTableNode *runner = symbols_table->top;
  Attribute *attribute = search(runner->list, id);
  return attribute;
}

/* Insert a element in the current level of the SymbolsTable. */
void push_element(ErrorsQueue *eq, SymbolsTable *symbols_table, Attribute *at)
{
	if (symbols_table->current_level > 0)
	{
    if (at!=NULL)
    {
      if (search_id_in_level(symbols_table, get_id(at)) != NULL)
        insert_error(eq, add_line_column(to_string("El identificador \"", get_id(at), "\" ya se encuentra en uso.")));
      else
        insert(symbols_table->top->list, at);
    }
    else
      insert_error(eq, add_line_column(to_string("El atributo es NULL.","","")));
  }
  else
    printf("%s\n",add_line_column(to_string("SymbolsTable: push_element Warning: la tabla no tiene ningun nivel.","","")));
}

/* Insert a new level in the SymbolsTable. */
void push_level(SymbolsTable *symbols_table)
{
	SymbolsTableNode *new_level = (SymbolsTableNode*) malloc (sizeof(SymbolsTableNode));
	if (new_level)
  {
    new_level->list = initialize();
    new_level->next = symbols_table->top;
    symbols_table->top = new_level;
    symbols_table->current_level++;
  }
  else
    printf("%s\n",add_line_column(to_string("SymbolsTable: push_level Warning: Error al reservar espacio en memoria.","","")));
}

/* Remove the entire current level of the SymbolsTable. */
void pop_level(SymbolsTable *symbols_table)
{
  if (symbols_table->current_level > 0)
  {
    SymbolsTableNode *auxNode = symbols_table->top;
    symbols_table->top = symbols_table->top->next;
    delete_all(auxNode->list);
    free(auxNode);
    symbols_table->current_level--;
  }
  else
    printf("%s\n",add_line_column(to_string("SymbolsTable: pop_level Warning: Pila sin mas niveles que descartar.","","")));
}

/* Searches for the id in all levels of the SymbolsTable.
 * Return Attribute* iff the id was't found. NULL if the id wasn't found.
 */
Attribute* search_id_in_symbols_table(ErrorsQueue *eq, SymbolsTable *symbols_table, char *id)
{
	int i;
	SymbolsTableNode *runner = symbols_table->top;
	Attribute *attribute;
	for (i = symbols_table->current_level; i > 0; i--)
	{
		attribute = search((runner->list), id);
		if (attribute != NULL)
		 return attribute;
		runner = runner->next;
	}
	insert_error(eq, add_line_column(to_string("El identificador \"", id, "\" no esta definido.")));
	return NULL;
}

/* Print the elements the SymbolsTable. */
void symbols_table_print(SymbolsTable *symbols_table)
{
  SymbolsTableNode *runner = symbols_table->top;
  int i;
  for (i = 0; i < symbols_table->current_level; i++)
  {
    printf("%d° nivel:\n", symbols_table->current_level - i);
    print_list(runner->list);
    printf("---------------------------------------------\n");
    runner = runner->next;
  }
}
