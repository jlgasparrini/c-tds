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
StringStack* initialize_string_stack();

/* Insert an element in the stack "s". */
void push_string(StringStack *s, char *value);

/* Return and removes the value of the last pushed string in the stack "s". */
char* pop_string(StringStack *s);

/* Return the top string of the stack "s". */
char* top_string(StringStack *s);

/* Prints the stack in the correct order */
void print_correct_order(StringStack *s);

/* Prints the stack in the inverse order */
void print_inverse_order(StringStack *s);

#endif
