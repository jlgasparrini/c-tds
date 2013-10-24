
#include "codespecs.h"

char* getCodeByID(int ID)
{
    switch (ID) {
		case  0: return "LOAD_CONST";
		case  1: return "STORE_MEM";
		case  2: return "COM_MINUS_INT";
		case  3: return "COM_ADD_INT";
		case  4: return "COM_MULT_INT";
		case  5: return "COM_DIV_INT";
		case  6: return "COM_MOD_INT";
        case  7: return "COM_MINUS_FLOAT";
        case  8: return "COM_ADD_FLOAT";
        case  9: return "COM_MULT_FLOAT";
        case 10: return "COM_DIV_FLOAT";
        case 11: return "COM_EQ";
        case 12: return "COM_DIST";
        case 13: return "COM_GT";
        case 14: return "COM_LR";
        case 15: return "COM_GEQ";
        case 16: return "COM_LEQ";
        case 17: return "COM_OR";
        case 18: return "COM_AND";
        case 19: return "COM_NOT";
        case 20: return "COM_MARK";
        case 21: return "GOTOLABEL";
        case 22: return "GOTOLABEL_COND";
        case 23: return "COM_RETURN";
        case 24: return "COM_NEG_INT";
        case 25: return "COM_NEG_FLOAT";
		case 26: return "STORE_MEM_METHOD";
    }
    return "";
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
    return "";
}
