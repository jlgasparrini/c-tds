
#include "codespecs.h"

/**Metodo que retorna el string correspondiente a su respectivo comando*/
char* getCodeByID(int ID)
{
    switch (ID) {
        case LOAD_CONST : return "LOAD_CONST";
        case LOAD_ARRAY : return "LOAD_ARRAY";
        case PRINT : return "PRINT";
        case RETURN : return "RETURN";
        case RETURN_EXPR : return "RETURN_EXPR";
        case LABEL : return "LABEL";
        case GOTO_LABEL : return "GOTO_LABEL";
        case GOTO_LABEL_COND : return "GOTO_LABEL_COND";
        case GOTO_METHOD : return "GOTO_METHOD";

        case ASSIGNATION_INT  : return "ASSIGNATION_INT";
        case PARAM_ASSIGN_INT : return "PARAM_ASSIGN_INT";
        case MINUS_INT : return "MINUS_INT";
        case ADD_INT : return "ADD_INT";
        case MULT_INT : return "MULT_INT";
        case DIV_INT : return "DIV_INT";
        case MOD_INT : return "MOD_INT";
        case NEG_INT : return "NEG_INT";
        case EQ_INT : return "EQ_INT";
        case DIST_INT : return "DIST_INT";
        case GREATER_INT : return "GREATER_INT";
        case LOWER_INT : return "LOWER_INT";
        case GEQ_INT : return "GEQ_INT";
        case LEQ_INT : return "LEQ_INT";

        case ASSIGNATION_FLOAT : return "ASSIGNATION_FLOAT";
        case PARAM_ASSIGN_FLOAT : return "PARAM_ASSIGN_FLOAT";
        case MINUS_FLOAT : return "MINUS_FLOAT";
        case ADD_FLOAT : return "ADD_FLOAT";
        case MULT_FLOAT : return "MULT_FLOAT";
        case DIV_FLOAT : return "DIV_FLOAT";
        case NEG_FLOAT : return "NEG_FLOAT";
        case EQ_FLOAT : return "EQ_FLOAT";
        case DIST_FLOAT : return "DIST_FLOAT";
        case GREATER_FLOAT : return "GREATER_FLOAT";
        case LOWER_FLOAT : return "LOWER_FLOAT";
        case GEQ_FLOAT : return "GEQ_FLOAT";
        case LEQ_FLOAT : return "LEQ_FLOAT";

        case ASSIGNATION_BOOL : return "ASSIGNATION_BOOL";
        case PARAM_ASSIGN_BOOL : return "PARAM_ASSIGN_BOOL";
        case EQ_BOOL : return "EQ_BOOL";
        case DIST_BOOL : return "DIST_BOOL";
        case OR : return "OR";
        case AND : return "AND";
        case NOT : return "NOT";
        
        case EXTERN_INVK : return "EXTERNINVK";
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
