#ifndef Attribute_H
#define	Attribute_H

typedef enum {Int, Float, Bool} PrimitiveType;
typedef enum {False, True} Boolean;
typedef enum {Variable, Method, Array} StructureType;
typedef enum {RetInt, RetFloat, RetBool, RetVoid} ReturnType;

typedef union               /* The value that a variable may take can be:                   */
{				
	int intVal; 			/* An int value 											    */
    float floatVal;			/* A float value 											    */
    Boolean boolVal;		/* A bool value: it will has 0 for False and 1 for True         */
} VarValue;

typedef struct              /* A variable has:											    */ 
{			
	char *id;				/* The "id" of the variable 								    */
	PrimitiveType type;		/* A "type" (int, float, boolean) (the word, name of the type)  */
	VarValue value;			/* A "value" (int, float, true, false) (variable's value') 	    */
    int offset;				/* A "offset" of the variable									*/
} StVariable;

typedef struct              /* An array has                                                 */
{
    char *id;               /* The "id" of the array     									*/
    PrimitiveType type;     /* A "type" (int, float, boolean) (the word, name of the type) 	*/
    unsigned int length;    /* The length of the array                                      */
	StVariable *arrayValues;/* The values of every array position							*/
} StArray;

typedef struct              /* A method has: 				       							*/
{			
	char *id;				/* The "id" of the method										*/
	ReturnType type; 		/* A "return type" (int, float, boolean, void) 				    */
	unsigned int paramSize; /* An int value indicating the number of parameters			    */
	StVariable **parameters; /* An array with the parameters, in case of having them		*/
	VarValue returnValue;   /* The return value of the current method						*/
} StMethod;

typedef union               /* A declaration is: 											*/
{			
    StVariable *variable;	/* A variable    												*/
    StMethod method;		/* A method 													*/
    StArray array;          /* An array                                                     */
} Declaration;

/*-----------------------   ATTRIBUTE   ----------------------------------------------------*/

typedef struct              /* An attribute has:                							*/
{		
    StructureType type;		/* type = 0, the attribute is a variable, type = 1, is a method, type = 2, is an array	*/
    Declaration decl;		/* Attribute's value 											*/
} Attribute;

/*------------------------------    METHODS    ---------------------------------------------*/

/* creates a variable attribute containing the information included in the parameters */
Attribute* createVariable(char* id, PrimitiveType type);

/* creates an array attribute containing the information included in the parameters */
Attribute* createArray(char* id, PrimitiveType type, unsigned int length);

/* creates a method attribute containing the information included in the parameters */
Attribute* createMethod(char* id, ReturnType type);

/* creates an attribute and assign it as a parameter of "method" containing the information included.
	Returns a pointer to the attribute if the parameter was created successful. Returns NULL otherwise. */
Attribute* createParameter(Attribute *attr, unsigned int pos, char* id, PrimitiveType type);

/* Sets the amount of parameters that will have the method attr */
void setAmountOfParameters(Attribute *attr, unsigned int amount);

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

/* Returns the intVal of the array attribute in the "pos" position */
int getArrayIntVal(Attribute *attr, unsigned int pos);

/* Returns the floatVal of the array attribute in the "pos" position */
float getArrayFloatVal(Attribute *attr, unsigned int pos);

/* Returns the boolVal of the array attribute in the "pos" position */
Boolean getArrayBoolVal(Attribute *attr, unsigned int pos);

/* Returns the offset of the variable */
int getOffsetVal(Attribute *attr);

/* Returns the offset of the array */
int getOffsetArray(Attribute *attr);

/* Sets the intVal of the attribute */
void setIntVal(Attribute *attr, int value);

/* Sets the floatVal of the attribute */
void setFloatVal(Attribute *attr, float value);

/* Sets the boolVal of the attribute */
void setBoolVal(Attribute *attr, Boolean value);

/* Sets the intVal of the array attribute in the "pos" position */
void setArrayIntVal(Attribute *attr, unsigned int pos, int value);

/* Sets the floatVal of the array attribute in the "pos" position */
void setArrayFloatVal(Attribute *attr, unsigned int pos, float value);

/* Sets the boolVal of the array attribute in the "pos" position */
void setArrayBoolVal(Attribute *attr, unsigned int pos, Boolean value);

/* Returns the global offset of the class */
int getGlobalVarOffset();

/* Set the global offset of the class */
void setGlobalVarOffset(int newOffset);

/* Set the global offset of the class in a -16 */
void resetGlobalVarOffset();

/* Returns the global parameters offset of the class */
int getGlobalParamOffset();

/* Set the global parameters offset of the class */
void setGlobalParamOffset(int newOffset);

/* Set the global parameters offset of the class in a 8 */
void resetGlobalParamOffset();

/* Returns the structure type of the attribute.
 * Return 0 if it's a variable 
 * Return 1 if it's a method 
 * Return 2 if it's an array */
StructureType getStructureType(Attribute *attr);

/* Decreases in 4 the offset for variables */
void decreaseVarOffset();

/* Increases in 4 the offset for variables */
void increaseVarOffset();

#endif
