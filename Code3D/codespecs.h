/**************************************************************************************                                                                   *
*Este header define constantes que indican los distintos comandos usados, 			  *
*cada comando tiene definido que va en cada parametro           					  *
**************************************************************************************/

#ifndef CODE_SPECS_H
#define CODE_SPECS_H

#include "code3d.h"


#define LOAD_CONST          0
#define LOAD_MEM            1
#define STORE_CONST         2
#define STORE_MEM           3
#define COM_MINUS_INT       4
#define COM_ADD_INT         5
#define COM_SUB_INT         6
#define COM_MULT_INT        7
#define COM_DIV_INT         8
#define COM_MOD_INT         9
#define COM_PLUSEQ_INT      10 
#define COM_MINUSEQ_INT     11 
#define COM_MINUS_FLOAT     12
#define COM_ADD_FLOAT       13
#define COM_SUB_FLOAT       14
#define COM_MULT_FLOAT      15
#define COM_DIV_FLOAT       16
#define COM_MOD_FLOAT       17
#define COM_PLUSEQ_FLOAT    18 
#define COM_MINUSEQ_FLOAT   19 
#define COM_EQ          	20
#define COM_DIST        	21
#define COM_GT          	22
#define COM_LR          	23
#define COM_GEQ         	24
#define COM_LEQ         	25
#define COM_OR              26
#define COM_AND             27
#define COM_NOT             28
#define COM_MARK            29
#define GOTOLABEL           30
#define GOTOLABEL_COND      31
#define COM_RETURN          32
#define COM_NEG_INT         33
#define COM_NEG_FLOAT       34

#endif

