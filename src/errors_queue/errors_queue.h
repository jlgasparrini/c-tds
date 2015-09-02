/*
 * Header errors queue.
 */

#ifndef ERRORS_QUEUE_H
#define ERRORS_QUEUE_H

/* Node of the queue. */
typedef struct E
{
  char *error;
  struct E *next; /* Pointer of the next node. */
} ErrorNode;

/* Define type ErrorsQueue. */
typedef struct
{
  ErrorNode *first; /* Pointer to first nodes of my queue. */
  ErrorNode *last; /* Pointer to last nodes of my queue. */
  int size; /* Size of the queue. */
} ErrorsQueue;

/* Returns an initialized queue. */
ErrorsQueue* initialize_queue();
/* Returns the string formed by putting together all the parameters */
char* to_string(char *init, char *id, char *message);
/* Inserts in the line and the column where the error is */
char* add_line_column(char *message);
/* Insert an element in the end of the queue "q". */
void insert_error(ErrorsQueue *eq, char *message);
/* Delete all the elements of the queue. */
void delete_all_errors(ErrorsQueue *eq);
/* Print in display the elements of the list. */
void print_error_list(ErrorsQueue *eq);

#endif
