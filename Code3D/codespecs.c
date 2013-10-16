
#include "codespecs.h"

char* getCodeByID(int ID)
{
    char *aux;
    switch (ID)
    {
        case 0: aux = "LOAD_CONST"; break;
        case 1: aux = "LOAD_MEM"; break;
        case 2: aux = "STORE_CONST"; break;
        case 3: aux = "STORE_MEM"; break;
        case 4: aux = "COM_MINUS_INT"; break;
        case 5: aux = "COM_ADD_INT"; break;
        case 6: aux = "COM_SUB_INT"; break;
        case 7: aux = "COM_MULT_INT"; break;
        case 8: aux = "COM_DIV_INT"; break;
        case 9: aux = "COM_MOD_INT"; break;
        case 10:aux = "COM_PLUSEQ_INT"; break; 
        case 11:aux = "COM_MINUSEQ_INT"; break; 
        case 12:aux = "COM_MINUS_FLOAT"; break;
        case 13:aux = "COM_ADD_FLOAT"; break;
        case 14:aux = "COM_SUB_FLOAT"; break;
        case 15:aux = "COM_MULT_FLOAT"; break;
        case 16:aux = "COM_DIV_FLOAT"; break;
        case 17:aux = "COM_MOD_FLOAT"; break;
        case 18:aux = "COM_PLUSEQ_FLOAT"; break; 
        case 19:aux = "COM_MINUSEQ_FLOAT"; break; 
        case 20:aux = "COM_EQ"; break;
        case 21:aux = "COM_DIST"; break;
        case 22:aux = "COM_GT"; break;
        case 23:aux = "COM_LR"; break;
        case 24:aux = "COM_GEQ"; break;
        case 25:aux = "COM_LEQ"; break;
        case 26:aux = "COM_OR"; break;
        case 27:aux = "COM_AND"; break;
        case 28:aux = "COM_NOT"; break;
        case 29:aux = "COM_MARK"; break;
        case 30:aux = "GOTOLABEL"; break;
        case 31:aux = "GOTOLABEL_COND"; break;
        case 32:aux = "COM_RETURN"; break;
        case 33:aux = "COM_NEG_INT"; break;
        case 34:aux = "COM_NEG_FLOAT"; break;
    }
    return aux;
}

char* getTypeByID(int type)
{
    char *aux;
    switch (type)
    {
        case -1 : aux = "void"; break;
        case  0 : aux = "Attribute"; break;
        case  1 : aux = "label";break;
        case  2 : aux = "Integer"; break;
        case  3 : aux = "Float"; break;
        case  4 : aux = "Bool" ; break;
    }
    return aux;
}
