
#include "codespecs.h"

/**Metodo que retorna el string correspondiente a su respectivo comando*/
char* getCodeByID(int ID)
{
    switch (ID) {
        case 0 : return "LOAD_CONST";
        case 1 : return "LOAD_ARRAY";
        case 2 : return "PRINT";
        case 3 : return "RETURN";
        case 4 : return "RETURN_EXPR";
        case 5 : return "LABEL";
        case 6 : return "GOTO_LABEL";
        case 7 : return "GOTO_LABEL_COND";
        case 8 : return "GOTO_METHOD";

        case 9  : return "ASSIGNATION_INT";
        case 10 : return "PARAM_ASSIGN_INT";
        case 11 : return "MINUS_INT";
        case 12 : return "ADD_INT";
        case 13 : return "MULT_INT";
        case 14 : return "DIV_INT";
        case 15 : return "MOD_INT";
        case 16 : return "NEG_INT";
        case 17 : return "EQ_INT";
        case 18 : return "DIST_INT";
        case 19 : return "GREATER_INT";
        case 20 : return "LOWER_INT";
        case 21 : return "GEQ_INT";
        case 22 : return "LEQ_INT";

        case 23 : return "ASSIGNATION_FLOAT";
        case 24 : return "PARAM_ASSIGN_FLOAT";
        case 25 : return "MINUS_FLOAT";
        case 26 : return "ADD_FLOAT";
        case 27 : return "MULT_FLOAT";
        case 28 : return "DIV_FLOAT";
        case 29 : return "NEG_FLOAT";
        case 30 : return "EQ_FLOAT";
        case 31 : return "DIST_FLOAT";
        case 32 : return "GREATER_FLOAT";
        case 33 : return "LOWER_FLOAT";
        case 34 : return "GEQ_FLOAT";
        case 35 : return "LEQ_FLOAT";

        case 36 : return "ASSIGNATION_BOOL";
        case 37 : return "PARAM_ASSIGN_BOOL";
        case 38 : return "EQ_BOOL";
        case 39 : return "DIST_BOOL";
        case 40 : return "OR";
        case 41 : return "AND";
        case 42 : return "NOT";
        
        case 43 : return "EXTERNINVK";
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
