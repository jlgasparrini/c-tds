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
#define EQ               11
#define DIST             12
#define GT               13
#define LR               14
#define GEQ              15
#define LEQ              16
#define OR               17
#define AND              18
#define NOT              19
#define MARK             20
#define GOTOLABEL        21
#define GOTOLABEL_COND   22
#define RETURN           23
#define NEG_INT          24
#define NEG_FLOAT        25
#define PARAM_ASSIGN     26
#define PRINT            27

/* Returns the respective code of an ID */
char* getCodeByID(int ID);

/* Returns the respective type of attribute according to the type */
char* getTypeByID(int type);

#endif
