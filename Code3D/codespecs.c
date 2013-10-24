
#include "codespecs.h"

char* getCodeByID(int ID)
{
    switch (ID) {
		case  0: return "LOAD_CONST";
		case  1: return "STORE_MEM";
		case  2: return "MINUS_INT";
		case  3: return "ADD_INT";
		case  4: return "MULT_INT";
		case  5: return "DIV_INT";
		case  6: return "MOD_INT";
        case  7: return "MINUS_FLOAT";
        case  8: return "ADD_FLOAT";
        case  9: return "MULT_FLOAT";
        case 10: return "DIV_FLOAT";
        case 11: return "EQ";
        case 12: return "DIST";
        case 13: return "GT";
        case 14: return "LR";
        case 15: return "GEQ";
        case 16: return "LEQ";
        case 17: return "OR";
        case 18: return "AND";
        case 19: return "NOT";
        case 20: return "LABEL";
        case 21: return "GOTO_LABEL";
        case 22: return "GOTO_LABEL_COND";
        case 23: return "RETURN";
        case 24: return "NEG_INT";
        case 25: return "NEG_FLOAT";
		case 26: return "STORE_MEM_METHOD";
		case 27: return "PRINT";
    }
    return "NULL!";
}

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
		case  5 : return "Variable";
    }
    return "NULL!";
}
