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
	VarValue return_value;   /* The return value of the current method						*/
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
Attribute* create_variable(char* id, PrimitiveType type);

/* creates an array attribute containing the information included in the parameters */
Attribute* create_array(char* id, PrimitiveType type, unsigned int length);

/* creates a method attribute containing the information included in the parameters */
Attribute* create_method(char* id, ReturnType type);

/* creates an attribute and assign it as a parameter of "method" containing the information included.
	Returns a pointer to the attribute if the parameter was created successful. Returns NULL otherwise. */
Attribute* create_parameter(Attribute *attr, unsigned int pos, char* id, PrimitiveType type);

/* Sets the amount of parameters that will have the method attr */
void set_amount_of_parameters(Attribute *attr, unsigned int amount);

/* Sets the value of the variable that contains "attr" with the respective "value" */
void set_variable_value(Attribute *attr, PrimitiveType type, char *value);

/* Returns the ID of the specified attribute */
char* get_id(Attribute *attr);

/* Returns the intVal of the attribute */
int get_int_val(Attribute *attr);

/* Returns the floatVal of the attribute */
float get_float_val(Attribute *attr);

/* Returns the boolVal of the attribute */
Boolean get_bool_val(Attribute *attr);

/* Returns the intVal of the array attribute in the "pos" position */
int get_array_int_val(Attribute *attr, unsigned int pos);

/* Returns the floatVal of the array attribute in the "pos" position */
float get_array_float_val(Attribute *attr, unsigned int pos);

/* Returns the boolVal of the array attribute in the "pos" position */
Boolean get_array_bool_val(Attribute *attr, unsigned int pos);

/* Returns the offset of the variable */
int get_offset_val(Attribute *attr);

/* Returns the offset of the array */
int get_offset_array(Attribute *attr);

/* Sets the intVal of the attribute */
void set_int_val(Attribute *attr, int value);

/* Sets the floatVal of the attribute */
void set_float_val(Attribute *attr, float value);

/* Sets the boolVal of the attribute */
void set_bool_val(Attribute *attr, Boolean value);

/* Sets the intVal of the array attribute in the "pos" position */
void set_array_int_val(Attribute *attr, unsigned int pos, int value);

/* Sets the floatVal of the array attribute in the "pos" position */
void set_array_float_val(Attribute *attr, unsigned int pos, float value);

/* Sets the boolVal of the array attribute in the "pos" position */
void set_array_bool_val(Attribute *attr, unsigned int pos, Boolean value);

/* Returns the global offset of the class */
int get_global_var_offset();

/* Set the global offset of the class */
void set_global_var_offset(int newOffset);

/* Set the global offset of the class in a -16 */
void reset_global_var_offset();

/* Returns the global parameters offset of the class */
int get_global_param_offset();

/* Set the global parameters offset of the class */
void set_global_param_offset(int newOffset);

/* Set the global parameters offset of the class in a 8 */
void reset_global_param_offset();

/* Returns the structure type of the attribute.
 * Return 0 if it's a variable 
 * Return 1 if it's a method 
 * Return 2 if it's an array */
StructureType get_structure_type(Attribute *attr);

/* Returns the type of the attribute, although it is a variable, array or method */
ReturnType get_attribute_type(Attribute *attr);

/* Returns the string corresponding to "type" */
char* get_type(PrimitiveType type);

/* Decreases in 4 the offset for variables */
void decrease_var_offset();

/* Increases in 4 the offset for variables */
void increase_var_offset();

#endif
