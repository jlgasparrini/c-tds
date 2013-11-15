/**************************************************************************************                                                                   *
*Este header define constantes que indican los distintos comandos usados, 			  *
*cada comando tiene definido que va en cada parametro           					  *
**************************************************************************************/

#ifndef CODE_SPECS_H
#define CODE_SPECS_H

#include "code3d.h"

/********************************* GENERAL OPERATIONS ******************************/
#define LOAD_CONST         0 
#define LOAD_ARRAY         1
#define PRINT              2
#define RETURN             3
#define RETURN_EXPR        4
#define LABEL              5
#define GOTO_LABEL         6
#define GOTO_LABEL_COND    7
#define GOTO_METHOD        8

/********************************* INT OPERATIONS **********************************/
#define ASSIGNATION_INT    9 
#define PARAM_ASSIGN_INT   10
#define MINUS_INT          11 
#define ADD_INT            12 
#define MULT_INT           13 
#define DIV_INT            14 
#define MOD_INT            15 
#define NEG_INT            16
#define EQ_INT	           17
#define DIST_INT           18
#define GREATER_INT        19
#define LOWER_INT          20
#define GEQ_INT            21
#define LEQ_INT            22

/********************************* FLOAT OPERATIONS ******************************/
#define ASSIGNATION_FLOAT  23 
#define PARAM_ASSIGN_FLOAT 24
#define MINUS_FLOAT	       25
#define ADD_FLOAT          26
#define MULT_FLOAT         27
#define DIV_FLOAT          28
#define NEG_FLOAT          29
#define EQ_FLOAT           30
#define DIST_FLOAT         31
#define GREATER_FLOAT      32
#define LOWER_FLOAT        33
#define GEQ_FLOAT          34
#define LEQ_FLOAT          35

/********************************* BOOLEAN OPERATIONS ******************************/
#define ASSIGNATION_BOOL   36 
#define PARAM_ASSIGN_BOOL  37
#define EQ_BOOL            38
#define DIST_BOOL          39
#define OR                 40
#define AND                41
#define NOT                42

/******************************** EXTERNAL OPERATIONS *****************************/
#define EXTERN_INVK  43

/**Returns the respective code of an ID */
char* getCodeByID(int ID);
/**Returns the respective type of attribute according to the type */
char* getTypeByID(int type);

#endif
