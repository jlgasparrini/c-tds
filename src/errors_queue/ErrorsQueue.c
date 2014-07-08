/*
 * An errors queue implementation.
 */

#include "ErrorsQueue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../SymbolsTable/Utils.h"

extern line_numb;
extern column_numb;

/* Returns an initialized queue. */ 
ErrorsQueue* initializeQueue()
{
  ErrorsQueue *aux = (ErrorsQueue*) malloc(sizeof(ErrorsQueue));
  (*aux).firstIN = NULL;
  (*aux).lastIN = NULL;
  (*aux).size = 0;
  return aux;
}

/* Returns the string formed by putting together all the parameters */
char* toString(char *init, char *id, char *message)
{																						   
  char* msg = (char*) malloc ((strlen(init)+strlen(id)+strlen(message)+strlen(" Error en linea: ")+digitAmount(line_numb)+strlen(".")+digitAmount(column_numb))*sizeof(char));
  strcat(msg,init);  
  strcat(msg,id); 
  strcat(msg,message);
  strcat(msg," Error en linea: ");
  char *numero = (char*) malloc (digitAmount(line_numb)*sizeof(char));
  sprintf(numero, "%d", line_numb);
  strcat(msg,numero);
  //	free(numero);
  strcat(msg,".");
  numero = (char*) malloc (digitAmount(column_numb)*sizeof(char));
  sprintf(numero, "%d", column_numb);
  strcat(msg,numero);
  //	free(numero);
  return msg;
}

/* Insert an element in the end of the queue "q". */
void insertError(ErrorsQueue *eq, char* message)
{
  ErrorNode *newErrorNode;
  if (newErrorNode = (ErrorNode*) malloc(sizeof(ErrorNode)))
  {
    (*newErrorNode).error = message;
    (*newErrorNode).next = NULL;

    if ((*eq).size == 0)
    {
      (*eq).firstIN = newErrorNode;
      (*eq).lastIN = newErrorNode;
    } 
    else
    {
      (*(*eq).lastIN).next = newErrorNode;
      (*eq).lastIN = newErrorNode;
    }
    (*eq).size++;
  }
  else 
  {
    printf("ErrorsQueue.c: insert ERROR: No se puede reservar espacio en memoria.");
  }
}

/* Delete all the elements of the queue. */
void deleteAllErrors(ErrorsQueue *eq)
{
  ErrorNode *aux;
  int i = 0;
  while (i < (*eq).size)
  {
    aux = (*eq).firstIN; 
    (*eq).firstIN = (*aux).next;
    free(aux);
    i++;
  }
  (*eq).firstIN = NULL;
  (*eq).lastIN = NULL;
  (*eq).size = 0;
}

/* Print in display the elements of the queue. */
void printErrorList(ErrorsQueue *eq)
{
  if ((*eq).size == 0)
    printf("Sin errores semanticos al compilar.\n");
  else
  {
    ErrorNode *aux = (*eq).firstIN; 
    int i = 0;
    if ((*eq).size == 1)
      printf("-- %d error semantico al compilar:\n",(*eq).size);
    else
      printf("-- %d errores semanticos al compilar:\n",(*eq).size);
    while (i < (*eq).size)
    {
      printf("%d- %s\n", i+1, (*aux).error);
      aux = (*aux).next;
      i++;
    }
  }
}
