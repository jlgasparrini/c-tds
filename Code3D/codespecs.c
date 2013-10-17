
#include "codespecs.h"

char* getCodeByID(int ID)
{
    switch (ID)
    {
        case 0: return "LOAD_CONST";
        case 1: return "LOAD_MEM";
        case 2: return "STORE_CONST";
        case 3: return "STORE_MEM";
        case 4: return "COM_MINUS_INT";
        case 5: return "COM_ADD_INT";
        case 6: return "COM_SUB_INT";
        case 7: return "COM_MULT_INT";
        case 8: return "COM_DIV_INT";
        case 9: return "COM_MOD_INT";
        case 10: return "COM_PLUSEQ_INT"; 
        case 11: return "COM_MINUSEQ_INT"; 
        case 12: return "COM_MINUS_FLOAT";
        case 13: return "COM_ADD_FLOAT";
        case 14: return "COM_SUB_FLOAT";
        case 15: return "COM_MULT_FLOAT";
        case 16: return "COM_DIV_FLOAT";
        case 17: return "COM_MOD_FLOAT";
        case 18: return "COM_PLUSEQ_FLOAT"; 
        case 19: return "COM_MINUSEQ_FLOAT"; 
        case 20: return "COM_EQ";
        case 21: return "COM_DIST";
        case 22: return "COM_GT";
        case 23: return "COM_LR";
        case 24: return "COM_GEQ";
        case 25: return "COM_LEQ";
        case 26: return "COM_OR";
        case 27: return "COM_AND";
        case 28: return "COM_NOT";
        case 29: return "COM_MARK";
        case 30: return "GOTOLABEL";
        case 31: return "GOTOLABEL_COND";
        case 32: return "COM_RETURN";
        case 33: return "COM_NEG_INT";
        case 34: return "COM_NEG_FLOAT";
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
    }
    return "";
}
