/*
 * An errors queue implementation.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "errors_queue.h"
#include "../SymbolsTable/Utils.h"

extern int line_numb;
extern int column_numb;

#define error_msg " Error in line: "

/* Returns an initialized queue. */
ErrorsQueue* initialize_queue()
{
  ErrorsQueue* new_queue = (ErrorsQueue*) malloc(sizeof(ErrorsQueue));
  new_queue->first = NULL;
  new_queue->last = NULL;
  new_queue->size = 0;
  return new_queue;
}

/* Returns the string formed by putting together all the parameters */
char* to_string(char *init, char *id, char *message)
{
  int length_msg = strlen(init) + strlen(id) + strlen(message);
  length_msg += digit_amount(line_numb) + strlen(".") + digit_amount(column_numb)  + strlen(error_msg);
  char* msg = (char*) malloc(length_msg * sizeof(char));
  strcat(msg, init);
  strcat(msg, id);
  strcat(msg, message);
  return msg;
}

/* Inserts in the line and the column where the error is */
char* add_line_column(char *message)
{
  strcat(message, error_msg);
  char *number = (char*) malloc(digit_amount(line_numb) * sizeof(char));
  sprintf(number, "%d", line_numb);
  strcat(message, number);
  strcat(message, ".");
  number = (char*) malloc(digit_amount(column_numb) * sizeof(char));
  sprintf(number, "%d", column_numb);
  strcat(message, number);
  return message;
}

/* Insert an element in the end of the queue "q". */
void insert_error(ErrorsQueue *eq, char* message)
{
  ErrorNode *new_error_node;
  if ((new_error_node = (ErrorNode*) malloc(sizeof(ErrorNode))))
  {
    new_error_node->error = message;
    new_error_node->next = NULL;
    if (eq->size == 0)
    {
      eq->first = new_error_node;
      eq->last = new_error_node;
    }
    else
    {
      eq->last->next = new_error_node;
      eq->last = new_error_node;
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
    new_error_node = eq->first;
    eq->first = new_error_node->next;
    free(new_error_node);
    i++;
  }
  eq->first = NULL;
  eq->last = NULL;
  eq->size = 0;
}

/* Print in display the elements of the queue. */
void print_error_list(ErrorsQueue *eq)
{
  if (eq->size == 0)
    printf("No semantics errors to compile.\n");
  else
  {
    ErrorNode *current_error_node = eq->first;
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
