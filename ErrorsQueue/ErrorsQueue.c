#include "ErrorsQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*
 * An errors queue implementation.
 */
 
/* Returns an initialized queue. */ 
ErrorsQueue* initializeQueue()
{
    ErrorsQueue *aux = (ErrorsQueue*) malloc(sizeof(ErrorsQueue));
    (*aux).firstIN = NULL;
    (*aux).lastIN = NULL;
    (*aux).size = 0;
    return aux;
}

/* Insert an element in the end of the queue "q". */
void insert(ErrorsQueue *q, char *id, char *message, int line, int column)
{
    Node *newNode;
    Error *error;
    if ((newNode = (Node*) malloc(sizeof(Node))) &&  (error = (Error*) malloc(sizeof(Error))))
    {
        (*error).id = strdup(id);
        (*error).message = strdup(message);
        (*error).line = line;
        (*error).column = column;
        (*newNode).error = error;
        (*newNode).next = NULL;
		
		if ((*q).size == 0)
		{
            (*q).firstIN = newNode;
            (*q).lastIN = newNode;
		} 
		else
		{
			(*(*q).lastIN).next = newNode;
	        (*q).lastIN = newNode;
		}
        (*q).size++;
    }
    else 
    {
        printf("ErrorsQueue.c: insert ERROR: No se puede reservar espacio en memoria.");
    }
}

/* Delete all the elements of the queue. */
void deleteAllErrors(ErrorsQueue *q)
{
    Node *aux;
    int i = 0;
    while (i < (*q).size)
    {
        aux = (*q).firstIN; 
        (*q).firstIN = (*aux).next;
        free(aux);
        i++;
    }
    (*q).firstIN = NULL;
    (*q).size = 0;
}

/* Print in display the elements of the queue. */
void printErrors(ErrorsQueue *q)
{
    Node *aux = (*q).firstIN; 
    int i = 0;
    printf("Errores al compilar:\n\n");
    while (i < (*q).size)
    {
        printf("El identificador %s %s  en linea %d.%d.\n\n", (*(*aux).error).id, (*(*aux).error).message, (*(*aux).error).line, (*(*aux).error).column);
        if ((*(*aux).error).column != 0)
            printf(", %d", (*(*aux).error).column);
        printf("");
        i++;
    }
}
