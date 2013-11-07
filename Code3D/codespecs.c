
#include "codespecs.h"

/**Metodo que retorna el string correspondiente a su respectivo comando*/
char* getCodeByID(int ID)
{
    switch (ID) {
		case  0: return "LOAD_CONST";
		case  1: return "ASSIGNATION";
		case  2: return "MINUS_INT";
		case  3: return "ADD_INT";
		case  4: return "MULT_INT";
		case  5: return "DIV_INT";
		case  6: return "MOD_INT";
        case  7: return "MINUS_FLOAT";
        case  8: return "ADD_FLOAT";
        case  9: return "MULT_FLOAT";
        case 10: return "DIV_FLOAT";
        case 11: return "EQ_INT";
        case 12: return "DIST_INT";
        case 13: return "GT_INT";
        case 14: return "LR_INT";
        case 15: return "GEQ_INT";
        case 16: return "LEQ_INT";
        case 17: return "OR";
        case 18: return "AND";
        case 19: return "NOT";
        case 20: return "LABEL";
        case 21: return "GOTO_LABEL";
        case 22: return "GOTO_LABEL_COND";
        case 23: return "RETURN";
        case 24: return "NEG_INT";
        case 25: return "NEG_FLOAT";
		case 26: return "PARAM_ASSIGN";
		case 27: return "PRINT";
		case 28: return "LOAD_ARRAY";
		case 29: return "RETURN_EXPR";
		case 30: return "GOTO_METHOD";
		case 31: return "EQ_FLOAT";         
		case 32: return "DIST_FLOAT";       
		case 33: return "GREATER_FLOAT";    
		case 34: return "LOWER_FLOAT";      
		case 35: return "GEQ_FLOAT";        
		case 36: return "LEQ_FLOAT";
		case 37: return "ASSIGNATION_FLOAT"; 
		case 38: return "PARAM_ASSIGN_FLOAT";        
    }
    return "NULL!";
}

/**Metodo que retorna el string correspondiente a su respectivo tipo*/
char* getTypeByID(int type)
{
    switch (type)
    {
        case -1 : return "void";
        case  0 : return "Attribute";
        case  1 : return "label";
        case  2 : return "Integer";
        case  3 : return "Float";
        case  4 : return "Bool" ;
    }
    return "NULL!";
}
