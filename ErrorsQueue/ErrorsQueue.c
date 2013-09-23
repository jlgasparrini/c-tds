

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

/* Insert an element in the queue "q". */
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
        (*l).firstIN.next = newNode;
        (*l).firstIN = newNode;
        if ((*l).size == 0)
            (*l).lastIN = newNode;
        (*l).size++;
    }
    else 
    {
        printf("ErrorsQueue.c: insert ERROR: Can't reserve space in memory.");
    }
}


/* Delete all the elements of the queue. */
void deleteAllErrors(LinkedList *l)
{
    Node *aux;
    int i = 0;
    while (i < (*l).size)
    {
        aux = (*l).first; 
        (*l).firstIN = (*aux).next;
        free(aux);
        i++;
    }
    (*l).firstIN = NULL;
    (*l).size = 0;
}



/* Print in display the elements of the queue. */
void printErrors(ErrorsQueue *q)
{
    Node *aux = (*l).first; 
    int i = 0;
    printf("Errores al compilar:\n\n");
    while (i < (*l).size)
    {
        printf(" \n");
        i++;
    }
}
