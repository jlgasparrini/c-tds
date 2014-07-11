/*
 * An errors queue implementation.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "errors_queue.h"
#include "../SymbolsTable/Utils.h"

extern line_numb;
extern column_numb;

/* Returns an initialized queue. */
ErrorsQueue* initialize_queue()
{
  ErrorsQueue* new_queue = (ErrorsQueue*) malloc(sizeof(ErrorsQueue));
  new_queue->firstIN = NULL;
  new_queue->lastIN = NULL;
  new_queue->size = 0;
  return new_queue;
}

/* Returns the string formed by putting together all the parameters */
char* to_string(char *init, char *id, char *message)
{
  char* error_msg = " Error in line: ";
  int length_msg = strlen(init) + strlen(id) + strlen(message) + strlen(error_msg);
  length_msg += digitAmount(line_numb) + strlen(".") + digitAmount(column_numb);
  char* msg = (char*) malloc(length_msg * sizeof(char));
  strcat(msg, init);
  strcat(msg, id);
  strcat(msg, message);
  strcat(msg, error_msg);
  char *numero = (char*) malloc(digitAmount(line_numb) * sizeof(char));
  sprintf(numero, "%d", line_numb);
  strcat(msg, numero);
  strcat(msg, ".");
  numero = (char*) malloc(digitAmount(column_numb) * sizeof(char));
  sprintf(numero, "%d", column_numb);
  strcat(msg, numero);
  return msg;
}

/* Insert an element in the end of the queue "q". */
void insert_error(ErrorsQueue *eq, char* message)
{
  ErrorNode *new_error_node;
  if (new_error_node = (ErrorNode*) malloc(sizeof(ErrorNode)))
  {
    new_error_node->error = message;
    new_error_node->next = NULL;
    if (eq->size == 0)
    {
      eq->firstIN = new_error_node;
      eq->lastIN = new_error_node;
    }
    else
    {
      eq->lastIN->next = new_error_node;
      eq->lastIN = new_error_node;
    }
    eq->size++;
  }
  else
    printf("ErrorsQueue.c: insert ERROR: Can't reserve memory space.");
}

/* Delete all the elements of the queue. */
void delete_all_errors(ErrorsQueue *eq)
{
  ErrorNode *new_error_node;
  int i = 0;
  while (i < eq->size)
  {
    new_error_node = eq->firstIN;
    eq->firstIN = new_error_node->next;
    free(new_error_node);
    i++;
  }
  eq->firstIN = NULL;
  eq->lastIN = NULL;
  eq->size = 0;
}

/* Print in display the elements of the queue. */
void printErrorList(ErrorsQueue *eq)
{
  if (eq->size == 0)
    printf("No semantics errors to compile.\n");
  else
  {
    ErrorNode *current_error_node = eq->firstIN;
    int i = 0;
    if (eq->size == 1)
      printf("-- %d semantic error to compile:\n",eq->size);
    else
      printf("-- %d semantic error to compile:\n",eq->size);
    while (i < eq->size)
    {
      printf("%d- %s\n", i+1, current_error_node->error);
      current_error_node = current_error_node->next;
      i++;
    }
  }
}
