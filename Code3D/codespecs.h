/**************************************************************************************                                                                   *
*Este header define constantes que indican los distintos comandos usados, 			  *
*cada comando tiene definido que va en cada parametro           					  *
**************************************************************************************/

#ifndef CODE_SPECS_H
#define CODE_SPECS_H

#include "code3d.h"

#define LOAD_CONST       0 
#define ASSIGNATION      1 
#define MINUS_INT        2 
#define ADD_INT          3 
#define MULT_INT         4 
#define DIV_INT          5 
#define MOD_INT          6 
#define MINUS_FLOAT	     7
#define ADD_FLOAT        8
#define MULT_FLOAT       9
#define DIV_FLOAT        10
#define EQ_INT	         11
#define DIST_INT         12
#define GREATER_INT      13
#define LOWER_INT        14
#define GEQ_INT          15
#define LEQ_INT          16
#define OR               17
#define AND              18
#define NOT              19
#define LABEL            20
#define GOTO_LABEL       21
#define GOTO_LABEL_COND  22
#define RETURN           23
#define NEG_INT          24
#define NEG_FLOAT        25
#define PARAM_ASSIGN     26
#define PRINT            27
#define LOAD_ARRAY       28
#define RETURN_EXPR      29
#define GOTO_METHOD      30
#define EQ_FLOAT         31
#define DIST_FLOAT       32
#define GREATER_FLOAT    33
#define LOWER_FLOAT      34
#define GEQ_FLOAT        35
#define LEQ_FLOAT        36

/**Returns the respective code of an ID */
char* getCodeByID(int ID);

/**Returns the respective type of attribute according to the type */
char* getTypeByID(int type);

#endif
