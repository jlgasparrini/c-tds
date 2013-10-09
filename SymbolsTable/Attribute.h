#ifndef Attribute_H
#define	Attribute_H
#define MAX_PARAMS 20

typedef enum {Int, Float, Bool} PrimitiveType;
typedef enum {False, True} Boolean;
typedef enum {Variable, Method, Array} StructureType;
typedef enum {RetInt, RetFloat, RetBool, RetVoid} ReturnType;

typedef union               /* The value that a variable may take can be:                           */
{				
	int intVal; 			/* An int value 														*/
    float floatVal;			/* A float value 														*/
    Boolean boolVal;		/* A bool value: it will has 0 for False and 1 for True                */
} VarValue;

typedef struct               /* An array has                                                        */
{
    char *id;               /* The "id" of the array     											*/
    PrimitiveType type;     /* A "type" (int, float, boolean) (the word, name of the type) 	    	*/
    int length;             /* The length of the array                                              */
} StArray;

typedef struct              /* A variable has:														*/ 
{			
	char *id;				/* The "id" of the variable 											*/
	PrimitiveType type;		/* A "type" (int, float, boolean) (the word, name of the type) 	    	*/
	VarValue value;			/* A "value" (int, float, true, false) (variable's value') 			    */
} StVariable;

typedef struct               /* A method has: 				       									*/
{			 
	char *id;				 /* The "id" of the method												*/
	ReturnType type; 		 /* A "return type" (int, float, boolean, void) 					    */
	unsigned char paramSize; /* An attribute indicating the number of parameters of the method      */
	StVariable parameters[MAX_PARAMS];/* An array with the parameters, in case of having them  		*/
	VarValue returnValue;    /* The return value of the current method								*/
} StMethod;

typedef union               /* A declaration is: 													*/
{				
    StVariable variable;	/* A variable    														*/
    StMethod method;		/* A method 															*/
    StArray array;          /* An array                                                             */
} Declaration;

/*-----------------------   ATTRIBUTE   -------------------------------------------------------*/

typedef struct              /* An attribute has:                									*/
{			
    StructureType type;		/* type = 0, the attribute is a variable, type = 1, is a method 		*/
    Declaration decl;		/* Attribute's value 													*/
} Attribute;

/*------------------------------    METHODS    ---------------------------------------------*/

/* creates a variable attribute containing the information included in the parameters */
Attribute* createVariable(char* id, PrimitiveType type);

/* creates an array attribute containing the information included in the parameters */
Attribute* createArray(char* id, PrimitiveType type, unsigned int length);

/* creates a method attribute containing the information included in the parameters */
Attribute* createMethod(char* id, ReturnType type, unsigned char paramAmount);

/* creates an attribute and assign it as a parameter of "method" containing the information included.
	Returns a pointer to the attribute if the parameter was created successful. Returns NULL otherwise. */
Attribute* createParameter(Attribute *attr, unsigned char pos, char* id, PrimitiveType type);

/* Adds the "var" variable in the position "pos" of the method "method" */
void addParameter(StMethod *method, StVariable *var, unsigned char pos);

/* Sets the amount of parameters that will have the method attr */
void setAmountOfParameters(Attribute *attr, unsigned char amount);

/* Sets the value of the variable that contains "attr" with the respective "value" */
void setVariableValue(Attribute *attr, PrimitiveType type, char *value);

/* Returns the ID of the specified attribute */
char* getID(Attribute *attr);

/* Returns the intVal of the attribute */
int getIntVal(Attribute *attr);

/* Returns the floatVal of the attribute */
float getFloatVal(Attribute *attr);

/* Returns the boolVal of the attribute */
Boolean getBoolVal(Attribute *attr);

/* Sets the intVal of the attribute */
void setIntVal(Attribute *attr, int value);

/* Sets the floatVal of the attribute */
void setFloatVal(Attribute *attr, float value);

/* Sets the boolVal of the attribute */
void setBoolVal(Attribute *attr, Boolean value);

#endif
