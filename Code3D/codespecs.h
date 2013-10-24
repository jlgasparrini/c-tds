/**************************************************************************************                                                                   *
*Este header define constantes que indican los distintos comandos usados, 			  *
*cada comando tiene definido que va en cada parametro           					  *
**************************************************************************************/

#ifndef CODE_SPECS_H
#define CODE_SPECS_H

#include "code3d.h"

#define LOAD_CONST        0 
#define STORE_MEM         1 
#define COM_MINUS_INT     2 
#define COM_ADD_INT       3 
#define COM_MULT_INT      4 
#define COM_DIV_INT       5 
#define COM_MOD_INT       6 
#define COM_MINUS_FLOAT	  7
#define COM_ADD_FLOAT     8
#define COM_MULT_FLOAT    9
#define COM_DIV_FLOAT    10
#define COM_EQ           11
#define COM_DIST         12
#define COM_GT           13
#define COM_LR           14
#define COM_GEQ          15
#define COM_LEQ          16
#define COM_OR           17
#define COM_AND          18
#define COM_NOT          19
#define COM_MARK         20
#define GOTOLABEL        21
#define GOTOLABEL_COND   22
#define COM_RETURN       23
#define COM_NEG_INT      24
#define COM_NEG_FLOAT    25
#define STORE_MEM_METHOD 26

/* Returns the respective code of an ID */
char* getCodeByID(int ID);

/* Returns the respective type of attribute according to the type */
char* getTypeByID(int type);

#endif
