
/*
 * A errors queue header.
 */
 
#ifndef ErrorsQueue_H
#define ErrorsQueue_H

typedef struct
{
    char *id;
    char *message;
    int line;
    int column;
} Error;

/* Node of the queue. */
typedef struct N 
{
    Error *error;
    /* Pointer of the next node. */
    struct N *next;
} Node;
 
/* Define type ErrorsQueue. */
typedef struct
{
    /* Pointer to first nodes of my queue. */
    Node *firstIN;
    /* Pointer to last nodes of my queue. */
    Node *lastIN;

    /* Size of the queue. */
    int size;
} ErrorsQueue;

/* Returns an initialized queue. */ 
ErrorsQueue* initializeQueue();

/* Insert an element in the end of the queue "q". */
void insert(ErrorsQueue *q, char *id, char *message, int line, int column);
 
/* Delete all the elements of the list. */
void deleteAll(ErrorsQueue *q);

/* Print in display the elements of the list. */
void print_list(ErrorsQueue *q);

#endif
