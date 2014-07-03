//Parser.
%{
  #include <stdio.h>
  #include <ctype.h>
  #include <string.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include "../SymbolsTable/StringStack.h"
  #include "../SymbolsTable/Utils.h"
  #include "../Stack/stack.h"
  #include "../Stack/stackOffset.h"
  #include "../ListMethod/genlistml.h" 

  extern FILE *yyin;
  SymbolsTable *symbols_table;	// Symbols Table Definition.
  ErrorsQueue *error_q; // Errors Queue definition.
  StringStack *params_stack, *methods_id_stack; /* StringStack containing the amount
                                             of parameters and last_called_methods
                                             in each level of method_call */
  unsigned char cant_params = 0, returns; /* Amount of parameters and amount
                                         of returns that a method will have. */
  PrimitiveType var_type;	// Type of the variable or array
  ReturnType method_type;	// Return type of the method
  char *last_def_method, *last_called_method = "";/* Name of the last defined method (last_def_method) and the last called method (last_called_method) */
  Boolean id_not_found;

  static inline void setUpMethodCreation(char *name, ReturnType type) {
    last_def_method = name; 
    pushElement(error_q, symbols_table, createMethod(name, type)); 
    pushLevel(symbols_table);
    returns = 0;
  }
  
  // Variables used for 3D code
  LCode3D *l_code3d;
  char *label_ID = "label_%d_";
  int label_count = 0;
  
  Stack *labels_CYC;
  Stack *labels_while;
  Stack *labels_for;
  Stack *return_stack;//Utilizada para los saltos en el interpreter!
  Stack *max_method_offset;
  StackOffset *offsets_var;
  StackOffset *offsets_param;
  ListMLabel *list_meth_label;
  
  //Assembly
  char* file_name; //String para almacenar el nombre del archivo sin extension.
  int flag_target = 1; //Bandera utilizada para manejar si en la linea de entrada de mis argumentos, tengo un "-target".
  int flag_first_param = 0; //Bandera utilizada para manejar la cantidad de parametros por adelantado.
  int amount_extern_params; //Contador de parametros para las invocaciones externas.
  
  //Main parameters
  int arguments_c;
  char **arguments_v;
  //Target input
  char* action_input = "";

  // abre el archivo a tratar (entrada)
  int openInput(char* name)
  {
    yyin = fopen(name,"r");
    if(yyin == NULL)
    {
      printf("File and / or arguments invalid.\n");
      printf("Use mode:\n");
      printf("\t./c-tds [-target (parse | show | interpreter | assembly | compile)] input [extern_file]+ [-o output_name]\n");
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
  }
  
  int validateArgs(char* argv[],int argc)
  {
    // Debe ingresar argumentos
    if(argc == 1)
    {
       printf("Few arguments.\n");
       printf("Use mode:\n\t");
       printf("./c-tds [-target (parse | show | interpreter | assembly | compile)] input [extern_file]+ [-o output_name]\n");
       return 0;
    }
    // Analizo los comandos de entrada
    int i;
    for(i=1;i<argc;i++)
    {
      // Compruebo target
      if(strcmp(argv[i],"-target") == 0)
      {
        // Compruebo cantidad de argumentos
        if(argc<=3)
        {
          printf("Few arguments.\n");
          printf("Use mode:\t");
          printf("./c-tds [-target parse | show | interpreter | assembly | compile] input [extern_file]+ [-o output_name]\n");
          return 0;
        }
        // Compruebo etapa de compilacion
        if(strcmp(argv[i+1],"parse")  && strcmp(argv[i+1],"show")  
          && strcmp(argv[i+1],"interpreter")  && strcmp(argv[i+1],"assembly")  && strcmp(argv[i+1],"compile") )
        {
          printf("Error en los argumentos");
          printf("\tSolo se permite: -target parse | show | interpreter | assembly | compile\n");
          return 0;  
        }
        else 
        {
          // Compruebo validez archivo entrada .c-tds y .ctds
          char* entrada = argv[i + 2];
          int length = strlen(entrada);
          if(length < 6)
          {
            printf("Invalid input file.\n");
            return 0;  
          }                
          int index;
          int pos_punto;
          for(index = length - 1; index > 0; index--)
            if(entrada[index] == '.')
            {
              pos_punto = index;
              break;
            }
          char* extension = calloc(sizeof(char)*(length - pos_punto), sizeof(char));
          int j = 0;
          for(index = pos_punto + 1; index < length; index++)
          {
            extension[j] = entrada[index];
            j++;
          }
          if(strcmp(extension, "ctds")  && strcmp(extension, "c-tds") )
          {
            printf("Invalid file extension, use: .c-tds || .ctds\n");
            return 0;  
          }
        }
      }
      // Check the argument "output name".
      if(strcmp(argv[i], "-o") == 0)
        if(i == argc - 1)
        {
          printf("Incorrect output name.\n");
          return 0;
        }
    }
    return 1;
  }
  
  void initializeStructures()
  {
      amount_extern_params = 0;
      error_q = initializeQueue();
      symbols_table = initializeSymbolsTable(); 
      l_code3d = initLCode3D();
      params_stack = initializeSS(); 
      methods_id_stack = initializeSS();
      labels_CYC = newStack();
      labels_while = newStack();
      return_stack = newStack();
      labels_for = newStack();
      max_method_offset = newStack();
      offsets_var = newStackOffset();
      offsets_param = newStackOffset();
      list_meth_label = initL();
      l_code3d = initLCode3D();
  }
  
  void compile(char *main_file, char **linked_files, int size)
  {
    InitAssembler(list_meth_label, l_code3d, return_stack, file_name);
    char** args = malloc(sizeof(char*)* (6 + size));
    args[0] = "gcc";
    args[1] = main_file;
    args[1] = strcat(args[1], ".s");
    int i;
    if(linked_files != NULL)
      for(i=0;i<size;i++)
        args[2+i] = linked_files[i];
    int status;
    pid_t child_pid = fork();
    if (child_pid == 0) 
    {
      printf("Built executable file.");
      // Execute GCC compilation command.
      execvp(args[0], args);    
      // Fail iff execvp return.
      printf("Incorrect commands.\n");
      exit(0);
    }
    /**** We can't delete temporary assembly ****/
    //else
    //{
    //  while (wait(&status) != child_pid);
    //  printf("Deleting temporary assembly.\n");
    //  remove(main_file);
    //  printf("Finished compilation.\n");               
    //}
  }
  
  // Get only filename without extension or path.
  char* getName(char* file)
  {
    int length = strlen(file);
    int i;
    int pos_punto = 0;
    int pos_barra = -1;
    for(i = length - 1; i > 0; i--)
    {
      if(file[i] == '.' && pos_punto == 0)
        pos_punto = i;
      if(file[i] == '/')
      {
        pos_barra = i;
        break;
      }
    }
    char* res = malloc(sizeof(char)* (pos_punto - pos_barra - 1));
    int j = 0;
    for(i = pos_barra + 1; i < pos_punto; i++)
      res[i - pos_barra -1] = file[i];
    return strdup(res);
  }
  
  
  int main(int argc,char **argv)
  { 
    arguments_c = argc;
    arguments_v = argv;
    initializeStructures();
    if(validateArgs(argv, argc) == 0) 
      return EXIT_FAILURE;
    else if(strcmp(argv[1], "-target") == 0)
    {
      // Get file name.
      file_name = getName(argv[3]);
      // Open input file.
      if(openInput(argv[3]) == EXIT_FAILURE)
        return EXIT_FAILURE;
      // Parse the input and load target.
      action_input = argv[2];
      yyparse();
    }
    else
    {
      flag_target = 0;
      // Obtengo el nombre del archivo.
      file_name = getName(argv[1]);
      // Abro archivo de entrada.
      if(openInput(argv[1]) == EXIT_FAILURE)
        return EXIT_FAILURE;
      // Parse the input and by default load set target with "compile".
      action_input = "compile";
      yyparse();
    }
  }
  
  //Al finalizar el parseo verifico si hubo errores, de lo contrario realizo la accion correspondiente al target.
  void finalize()
  {
    if ((*error_q).size > 0)
      printErrorList(error_q);
    else
    {
      if(strcmp(action_input,"parse") == 0)
        printf("Code parsed correctly.\n"); //Unicamente informa que el codigo se parsea correctamente.
      else if(strcmp(action_input,"show") == 0)
      {
        printf("Intermediate code:\n");
        show3DCode(l_code3d); //Muestro el codigo 3D por terminal.
      }
      else if(strcmp(action_input,"interpreter") == 0)
      {
        printf("Interpreting code:\n");
        InitInterpreter(list_meth_label, l_code3d); //Llamo al interpreter del codigo de entrada.
      }
      else if(strcmp(action_input,"assembly") == 0)
        InitAssembler(list_meth_label, l_code3d, return_stack, file_name); //Llamo al generador del codigo assembly y lo genero.
      else if(strcmp(action_input,"compile") == 0)
      {
        int i, j, start = 0;
        int end = arguments_c;
        if(flag_target==0 && arguments_c >= 2)
        {
          start = 2;
          j = 0;
          char **linked_files = malloc(sizeof(char*) * (end - start));
          for(i = start; i < end; i++){
            linked_files[j] = arguments_v[i+1];
            j++;
        }
          compile(file_name, linked_files, end - start); //Genero el codigo assembly y lo compilo para generar el ejecutable.
        }
        if (flag_target == 1 && arguments_c >= 5)
        {
          start = 5;
          j = 0;
          char **linked_files = malloc(sizeof(char*) * (end - start));
          for(i = start; i < end; i++){
            linked_files[j] = arguments_v[i];
            j++;
          }
          //Genero el codigo assembly y lo compilo para generar el ejecutable.
          compile(file_name, linked_files, end - start);
        }
      }
    }
  }
  
  /*Create new Label*/
  char* newLabelName(char* msg) 
  {
    char *labelName = malloc(sizeof(char)*(digitAmount(label_count)+strlen("%d_label_")+strlen(msg)));
    sprintf(labelName, label_ID, label_count);
    strcat(labelName,msg);
    label_count++;
    return labelName;
  }
  
  int yydebug = 1;
  
  int yyerror (char *str)
  {
    printErrorList(error_q);
    deleteAllErrors(error_q);
    if (strcmp(str, "syntax error") == 0)
      printf("%s\n",toString("GRAMATICAL Error.","",""));
    else
      printf("%s\n","Unknow error.");
    return 0;
  }
  
  int yywrap()
  {
    return 1;
  } 
%}

%union
{
  char *string_value;
  Attribute *at;
}

%start program

/* %token<string_value> utilizado para definir el tipo de los tokens devueltos desde Lex*/
%token<string_value> FLOAT INTEGER BOOLEAN INT_WORD FLOAT_WORD BOOLEAN_WORD ID PLUSEQUAL MINUSEQUAL STRING
%token EQUAL DISTINCT GEQUAL LEQUAL ORR ANDD 
%token BREAK IF CONTINUE ELSE RETURNN WHILE CLASS FOR VOID EXTERNINVK PRINTT
%nonassoc '<' '>' EQUAL DISTINCT GEQUAL LEQUAL
%left '+' '-'
%left '*' '/'
%left '%'
%type<at> expression conjunction inequality comparison relation term factor primary method_call location factor1 arg
%type<string_value> assig_op typevoid
/* %type<at> para definir los tipos de los no-terminales */

%%      /*  beginning  of  rules  section  */

/* ------------------- PROGRAM -------------------- */
program       :    CLASS ID '{' '}' {finalize();}
              |    CLASS ID '{' {pushLevel(symbols_table);} 
                   body {checkMain(error_q,symbols_table);
                         popLevel(symbols_table);
                         finalize();} 
                   '}' 
              ;
body          :    fields_decls method_decl 
              |    method_decl
              ;

fields_decls  :    type fields ';' 			
              |    fields_decls type fields ';' 	
              ;

fields        :    field
              |    fields ',' field
              ;

field         :    ID {pushElement(error_q, symbols_table, createVariable($1, var_type));}
              |    ID '[' INTEGER {if (atoi($3) <= 0) 
                                    {	insertError(error_q,toString("Error en definicion del arreglo \"",$1,"\". El tamaño del arreglo debe ser un entero mayor que 0."));
                                        pushElement(error_q, symbols_table, createArray($1, var_type, 10)); /* Array size of 10 in case of error */
                                    }
                                    else
                                        pushElement(error_q, symbols_table, createArray($1, var_type, atoi($3)));
                                  } 
                   ']'	
              ;

type          :		INT_WORD		 {var_type = Int; method_type = RetInt;} 
              |		FLOAT_WORD	 {var_type = Float; method_type = RetFloat;}
              |		BOOLEAN_WORD {var_type = Bool; method_type = RetBool;}
              ;

method_decl   :     type ID {
                        pushOffset(offsets_var, getGlobalVarOffset());/////////////////////////////////
                        resetGlobalVarOffset();////////////////////////////
                        setUpMethodCreation($2, method_type);
                        add_CodeLabel(l_code3d, newCode(LABEL), $2); // Mark to Label of Init of Method
                        push(max_method_offset, intToString(codeSize(l_code3d)));
                        insert_MethodL(list_meth_label, $2, $2);
                    } param block {
                        int pos = atoi(pop(max_method_offset));
                        set_code_int(l_code3d, pos, 2, getGlobalVarOffset());
                        setGlobalVarOffset(popOffset(offsets_var));//////////////////////////////////////////
                        if(returns==0) insertError(error_q,toString("El metodo \"",$2,"\" debe tener al menos un return."));
                        popLevel(symbols_table);
                    }
              |		method_decl type ID {
                        pushOffset(offsets_var, getGlobalVarOffset());
                        resetGlobalVarOffset();
                        setUpMethodCreation($3, method_type);
                        add_CodeLabel(l_code3d, newCode(LABEL), $3); // Mark to Label of Init of Method
                        push(max_method_offset, intToString(codeSize(l_code3d)));
                        insert_MethodL(list_meth_label, $3, $3);
                    } param block {
                        int pos = atoi(pop(max_method_offset));
                        set_code_int(l_code3d, pos, 2, getGlobalVarOffset());
                        setGlobalVarOffset(popOffset(offsets_var));
                        if(returns==0) insertError(error_q,toString("El metodo \"",$3,"\" debe tener al menos un return."));
                        popLevel(symbols_table);
                    }
              |     VOID ID {
                        pushOffset(offsets_var, getGlobalVarOffset());
                        resetGlobalVarOffset();
                        setUpMethodCreation($2, RetVoid);
                        add_CodeLabel(l_code3d, newCode(LABEL), $2); // Mark to Label of Init of Method
                        push(max_method_offset, intToString(codeSize(l_code3d)));
                        insert_MethodL(list_meth_label, $2, $2);
                    } param block {
                        int pos = atoi(pop(max_method_offset));
                        set_code_int(l_code3d, pos, 2, getGlobalVarOffset());
                        setGlobalVarOffset(popOffset(offsets_var));
                        if(returns==0) insertError(error_q,toString("El metodo \"",$2,"\" debe tener al menos un return."));
                        popLevel(symbols_table);
                    }
              |	    method_decl VOID ID {
                        pushOffset(offsets_var, getGlobalVarOffset());
                        resetGlobalVarOffset();
                        setUpMethodCreation($3, RetVoid);
                        add_CodeLabel(l_code3d, newCode(LABEL), $3); // Mark to Label of Init of Method
                        push(max_method_offset, intToString(codeSize(l_code3d)));
                        insert_MethodL(list_meth_label, $3, $3);
                    } param block {
                        int pos = atoi(pop(max_method_offset));
                        set_code_int(l_code3d, pos, 2, getGlobalVarOffset());
                        setGlobalVarOffset(popOffset(offsets_var));
                        if(returns==0) insertError(error_q,toString("El metodo \"",$3,"\" debe tener al menos un return."));
                        popLevel(symbols_table);
                    }
              ;

param		      :    '(' {cant_params = 0; setAmountOfParameters(searchIdInSymbolsTable(error_q,symbols_table,last_def_method),0);} ')' 
              |    '(' {if (strcmp(last_def_method,"main") == 0)
                            insertError(error_q,toString("El metodo \"main\" no debe contener parametros.","",""));
                        cant_params = 0;
						            pushOffset(offsets_param, getGlobalParamOffset());////////////////////////////
						            resetGlobalParamOffset();////////////////////////////
                        }
                    parameters {
                                setAmountOfParameters(searchIdInSymbolsTable(error_q,symbols_table,last_def_method),cant_params);
								                setGlobalParamOffset(popOffset(offsets_param));/////////////////////////////////////
                               }
                    ')'
              ;

parameters    :		type ID {
                           Attribute *aux = createParameter(searchIdInSymbolsTable(error_q,symbols_table,last_def_method),cant_params,$2,var_type);
                           if (aux != NULL) {pushElement(error_q,symbols_table,aux); cant_params++;}
                           else insertError(error_q,toString("El identificador \"",$2,"\" no puede contener parametros/esa cantidad de parametros."));
                          }

              |		type ID {
                           Attribute *aux = createParameter(searchIdInSymbolsTable(error_q,symbols_table,last_def_method),cant_params,$2,var_type);
                           if (aux != NULL) {pushElement(error_q,symbols_table,aux); cant_params++;}
                           else insertError(error_q,toString("El identificador \"",$2,"\" no puede contener parametros/esa cantidad de parametros."));
                          }
                            ',' parameters 
              ;

block         :    '{' '}'
              |    '{' codeBlock '}' 
              ;

codeBlock     :    fields_decls statements 
              |    statements
              |    fields_decls 
              ;

statements    :    statement
              |    statements statement
              ;

/* -------------------- END OF PROGRAM ------------------------------- */

/* -------------------- STATEMENTS ------------------------------- */

statement     :    conditional 
              |    iteration 
              |    action ';'     
              |    {pushLevel(symbols_table);} block {popLevel(symbols_table);}
              |    PRINTT expression ';' {add_Print(l_code3d, newCode(PRINT), $2);}
              ;

action        :
              |    BREAK {
                            if (isEmpty(labels_while) && isEmpty(labels_for))
                                insertError(error_q,toString("Error. Solo se puede usar la sentencia \"break\" dentro de un ciclo.","",""));
                            else{
                                char* aux = pop(labels_while);
                                char* aux2 = pop(labels_while);
                                add_CodeLabel(l_code3d, newCode(GOTO_LABEL), peek(labels_while)); //Go to char of End of While
                                push(labels_while, aux2);
                                push(labels_while, aux);
                                }
                    }
              |    CONTINUE {
                            if (isEmpty(labels_while) && isEmpty(labels_for))
                                insertError(error_q,toString("Error. Solo se puede usar la sentencia \"continue\" dentro de un ciclo.","",""));
                            else
                            {
                                char *posLabel = pop(labels_while); //Label of End of While
                                add_CodeLabel(l_code3d, newCode(GOTO_LABEL), peek(labels_while)); //Go to char of Init of While
                                push(labels_while, posLabel);
                            } 
                    }
              |	   RETURNN {
                            returns++; 
                            if ((id_not_found == False) && (checkReturn(error_q,symbols_table,last_def_method) == 0))
                            {
                                Code3D *ret = newCode(RETURN);
                                setCodeLabel(ret, "   -   ");  /* Label "    -    " is added because there are no arguments */
                                add_code(l_code3d, ret);
                            }
                    }   
              |	   RETURNN expression {
                                    returns++; 									
                                    if (id_not_found == False && checkReturnExpression(error_q,symbols_table,last_def_method,$2) == 0)
                                    { 
                                        Code3D *ret = newCode(RETURN_EXPR);
                                        setCode2D(ret, $2, searchIdInSymbolsTable(error_q,symbols_table,last_def_method)); 
                                        add_code(l_code3d, ret);  
                                    }                           
                    }
              |    asignation 
              |    method_call                        
              ;

asignation    :     location assig_op expression {
                        controlAssignation(error_q,l_code3d,$1,$2,$3);
                    }
              ;

assig_op      :    '=' {$$ = "=";} 
              |    PLUSEQUAL {$$ = "+=";}
              |    MINUSEQUAL {$$ = "-=";}
              ;

/* -------------------- END OF STATEMENTS ------------------------------- */

/* -------------------- CONDITIONALS AND CICLES ------------------------------ */

conditional   :     IF '(' {
                        add_CodeLabel(l_code3d, newCode(LABEL), newLabelName("if"));
                    } expression { 
                        controlType(error_q,$4,Bool,"if",1);
                        char *elseLabel = newLabelName("else");
                        add_CodeLabelCond(l_code3d, newCode(GOTO_LABEL_COND), $4, elseLabel); 
                        push(labels_CYC, newLabelName("end_if"));
                        push(labels_CYC, elseLabel);
                    } ')' block optional 
              ;

optional	  :		{
                        add_CodeLabel(l_code3d, newCode(LABEL), pop(labels_CYC)); // Mark to char of End
                        push(return_stack, pop(labels_CYC));
                    }
              |	   	ELSE {
                        char* elseLabel = pop(labels_CYC);
                        add_CodeLabel(l_code3d, newCode(GOTO_LABEL), peek(labels_CYC)); //Go to char of Else
                        add_CodeLabel(l_code3d, newCode(LABEL), elseLabel); // Mark to char of Else
                    } block {	
                        char* aux = pop(labels_CYC);
                        add_CodeLabel(l_code3d, newCode(LABEL), aux); // Mark to char of End
                        push(return_stack, aux);
                    }
              ;
                                
iteration     :    WHILE {
                        char *whileLabel = newLabelName("while"); 
                        add_CodeLabel(l_code3d, newCode(LABEL), whileLabel); // label of While
                        push(labels_while, whileLabel);
                        push(labels_while, intToString(codeSize(l_code3d)));
                    } 
                   expression { 
                        char *endWhile = newLabelName("end_while");
                        char *pos = pop(labels_while);
                        char *whileLabel = pop(labels_while);
                        push(labels_while, endWhile);
                        push(labels_while, whileLabel); 
                        push(labels_while, pos);
                        controlType(error_q,$3,Bool,"while",1);
                        add_CodeLabelCond(l_code3d, newCode(GOTO_LABEL_COND), $3, endWhile); // Go to label of Expression
                    } block {							
                        add_code(l_code3d, get_code(l_code3d, atoi(pop(labels_while))+1));
                        add_CodeLabel(l_code3d, newCode(GOTO_LABEL), pop(labels_while)); // Go to label of while
                        add_CodeLabel(l_code3d, newCode(LABEL), pop(labels_while)); // label_end of while
                    }
              |    FOR ID {
                        if (getAttributeType(getVariableAttribute(error_q,symbols_table,$2)) != Int)
                            insertError(error_q,toString("El identificador \"", $2, "\" no pertenece a una variable de tipo \"int\""));
                        /* It musn't have the same treatment that while? */
                    } '=' expression ',' expression {
                            controlType(error_q,$5,Int,"for",2); controlType(error_q,$7,Int,"for",3); 
                            char *forLabel = newLabelName("for");
                            char *endLabel = newLabelName("end_for");
                            push(labels_for, endLabel);
                            push(labels_for, forLabel);
                            push(labels_for, intToString(codeSize(l_code3d)));
                            add_Assignation(l_code3d, $5, getVariableAttribute(error_q, symbols_table, $2));
                            Attribute *res = returnMinorComparison(error_q, l_code3d, getVariableAttribute(error_q, symbols_table, $2), $7);
                            add_CodeLabel(l_code3d, newCode(LABEL), forLabel);
                            add_CodeLabelCond(l_code3d, newCode(GOTO_LABEL_COND), res, endLabel); // Go to label of Expression
                    } block {
                            controlAssignation(error_q,l_code3d,getVariableAttribute(error_q,symbols_table,$2),"+=",returnValue(l_code3d,Int,"1"));
                            add_code(l_code3d, get_code(l_code3d, atoi(pop(labels_for))+1));
                            add_CodeLabel(l_code3d, newCode(GOTO_LABEL), pop(labels_for)); // Go to label of For
                            add_CodeLabel(l_code3d, newCode(LABEL), pop(labels_for)); // label_end of For
                    }
              ;                                                               

/* -------------------- END OF CONDITIONALS AND CICLES ------------------------------- */

/* -------------------- EXPRESSIONS ------------------------------- */

location      :    ID {$$ = getVariableAttribute(error_q, symbols_table, $1);}
              |    ID '[' expression ']' {$$ = checkArrayPos(error_q,symbols_table,l_code3d,$1,$3);}
              ;

method_call   :	   ID '(' ')' {
                        cant_params=0; 
                        last_called_method=$1; 
                        add_CodeLabel(l_code3d, newCode(GOTO_METHOD), get_Label(list_meth_label, $1)); //Go to char of Init of Method
                        $$ = checkAndGetMethodRetAttribute(error_q,symbols_table,l_code3d,$1,0);
                    }

				|    ID '(' {if (searchIdInSymbolsTable(error_q,symbols_table,$1) == NULL) 
                                id_not_found = True; 
                            else
                            {
                                pushString(params_stack,intToString(cant_params));
                                cant_params=0;								
                                pushString(methods_id_stack,last_called_method);
                                last_called_method = $1;
                            }
                    } expression_aux ')' {
                            if (id_not_found != True)
                            {
                                set_code_int(l_code3d, flag_first_param, 3, cant_params);
                                flag_first_param = 0;
                                add_CodeLabel(l_code3d, newCode(GOTO_METHOD), get_Label(list_meth_label, $1)); //Go to char of Init of Method 
                                $$ = checkAndGetMethodRetAttribute(error_q,symbols_table,l_code3d,$1,cant_params); 
                                cant_params=atoi(popString(params_stack));
                            }
                            else
                            {
                                $$ = createVariable((char*) getVariableName(),Int); 
                                id_not_found = False;
                            }
                    } 

				|    EXTERNINVK '(' STRING ',' typevoid ')' {
                        Attribute* res;
                        if (method_type != RetVoid) 
                            res = createVariable("",method_type);
                        else
                            res = createVariable((char*) getVariableName(),Int);
                        char token[2] = "\"";
                        add_CodeExternInvk(l_code3d, newCode(EXTERN_INVK), strtok($3, token), $5);
                        $$ = res;
                    }
				|    EXTERNINVK '(' STRING ',' typevoid ',' externinvk_arg ')' {
                        amount_extern_params = 0;
                        Attribute* res;
                        if (method_type != RetVoid) 
                            res = createVariable("",method_type);
                        else
                            res = createVariable((char*) getVariableName(),Int);
                        char token[2] = "\"";
                        add_CodeExternInvk(l_code3d, newCode(EXTERN_INVK), strtok($3, token), $5);
                        $$ = res;
                    }
				;

expression_aux:    expression {
                        if (id_not_found != True)
                        {
                            correctParamBC(error_q,symbols_table,l_code3d,$1,last_called_method,cant_params); 
                            if (flag_first_param == 0)
                                flag_first_param = codeSize(l_code3d);
                            cant_params++;
                        }
                    }
              |    expression {
                        if (id_not_found != True)
                        {
                            correctParamIC(error_q,symbols_table,l_code3d,$1,last_called_method,cant_params); 
                                if (flag_first_param == 0)
                                    flag_first_param = codeSize(l_code3d);
                            cant_params++;
                        } 
                   } ',' expression_aux 
              ;

typevoid      :    type {switch (method_type)
                        {
                            case RetInt: $$=strdup("int");
                                            break;
                            case RetFloat: $$=strdup("float");
                                            break;
                            case RetBool: $$=strdup("bool");
                                            break;
                        } 
                   }
              |    VOID {method_type = RetVoid; $$=strdup("void");} 
              ;

externinvk_arg:    arg                    {amount_extern_params++; externParamAssign(l_code3d, $1, amount_extern_params);}
              |    externinvk_arg ',' arg {amount_extern_params++; externParamAssign(l_code3d, $3, amount_extern_params);}
              ;

arg           :    expression {$$ = $1;}
              |    STRING     {$$ = $1;}
              ;

expression    :    conjunction					{$$ = $1;}                             
              |    expression ORR conjunction	{$$ = returnOr(error_q, l_code3d, $1, $3);}
              ;

conjunction   :    inequality                   {$$ = $1;}                                
              |    conjunction ANDD inequality	{$$ = returnAnd(error_q, l_code3d, $1, $3);}
              ;

inequality    :    comparison                       {$$ = $1;}                             
              |    inequality DISTINCT comparison   {$$ = returnDistinct(error_q, l_code3d, $1, $3);}
              ;

comparison    :    relation                   {$$ = $1;} 
              |    relation EQUAL relation    {$$ = returnEqual(error_q, l_code3d, $1, $3);}
              ;

relation      :    term                 {$$ = $1;}
              |    term '<' term        {$$ = returnMinorComparison(error_q, l_code3d, $1, $3);}
              |    term '>' term        {$$ = returnMajorComparison(error_q, l_code3d, $1, $3);}
              |    term GEQUAL term     {$$ = returnGEqualComparison(error_q, l_code3d, $1, $3);}
              |    term LEQUAL term     {$$ = returnLEqualComparison(error_q, l_code3d, $1, $3);}
              ;

term          :    factor1			    {$$ = $1;}
              |    factor1 '+' term	    {$$ = returnAdd(error_q, l_code3d, $1, $3);}
              |    factor1 '-' term	    {$$ = returnSub(error_q, l_code3d, $1, $3);}
              ;

factor1       :    factor			    {$$ = $1;}
              |    factor '*' factor1	{$$ = returnMult(error_q, l_code3d, $1, $3);}
              |    factor '/' factor1	{$$ = returnDiv(error_q, l_code3d, $1, $3);}
              |    factor '%' factor1	{$$ = returnMod(error_q, l_code3d, $1, $3);}
              ;

factor        :    primary		{$$ = $1;}  
              |    '!' factor	{$$ = returnNot(error_q, l_code3d, $2);}
              |    '-' factor	{$$ = returnNeg(error_q, l_code3d, $2);}
              ;

primary       :    INTEGER			{$$ = returnValue(l_code3d, Int, $1);}
              |    FLOAT            {$$ = returnValue(l_code3d, Float, $1);}
              |    BOOLEAN          {$$ = returnValue(l_code3d, Bool, $1);}
              |    ID				{$$ = getVariableAttribute(error_q,symbols_table,$1);}
              |    ID '[' expression ']'  {$$ = checkArrayPos(error_q,symbols_table,l_code3d,$1,$3);}
              |    '(' expression ')' {$$ = $2;}
              |    method_call      { if (methodReturnType(error_q,symbols_table,last_called_method) == RetVoid)
                                      {	insertError(error_q,toString("El metodo \"",last_called_method,"\" no puede ser usado en una expresion ya que retorna void."));
                                          $$ = createVariable("",Int); /* creamos variables int por defecto para que podamos seguir parseando el codigo */
                                      }
                                      else $$ = $1;
                                      last_called_method=popString(methods_id_stack); }
              ;

/* ------------------------- END OF EXPRESSIONS ------------------------------- */

%%
