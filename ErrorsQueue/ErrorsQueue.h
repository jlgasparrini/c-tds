
/*
 * A errors queue header.
 */
 
#ifndef ErrorsQueue_H
#define ErrorsQueue_H

/* Node of the queue. */
typedef struct E 
{
    char *error;
    /* Pointer of the next node. */
    struct E *next;
} ErrorNode;
 
/* Define type ErrorsQueue. */
typedef struct
{
    /* Pointer to first nodes of my queue. */
    ErrorNode *firstIN;
    /* Pointer to last nodes of my queue. */
    ErrorNode *lastIN;

    /* Size of the queue. */
    int size;
} ErrorsQueue;

/* Returns an initialized queue. */ 
ErrorsQueue* initializeQueue();

/* Returns the amount of digits that has an int value */
unsigned int digitAmount(int value);

/* Returns the string formed by putting together all the parameters */
char* toString(char *init, char *id, char *message);

/* Insert an element in the end of the queue "q". */
void insertError(ErrorsQueue *eq, char *message);
 
/* Delete all the elements of the queue. */
void deleteAllErrors(ErrorsQueue *eq);

/* Print in display the elements of the list. */
void printErrorList(ErrorsQueue *eq);

#endif
