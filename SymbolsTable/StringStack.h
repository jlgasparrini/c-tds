/*
 * A stack of numbers header.
 */
 
#ifndef StringStack_H
#define StringStack_H

/* Node of the stack of numbers. */
typedef struct S 
{
    char* val;
    /* Pointer of the next node. */
    struct S *next;
} SNode;
 
/* Define type StringStack. */
typedef struct
{
    /* Pointer to first nodes of the stack. */
    SNode *first;
    /* Size of the stack. */
    int size;
} StringStack;

/* Returns an initialized StringStack. */ 
StringStack* initializeSS();

/* Insert an element in the stack "s". */
void insertString(StringStack *s, char *value);

/* Return and removes the value of the last pushed string in the stack "s". */
char* removeLastString(StringStack *s);

/* Return the top string of the stack "s". */
char* topString(StringStack *s);

#endif