%{

  /* Necessary functions definitions for avoiding warnings */
  int yylex(void);
  int yyparse(void);

  /*
   *  MISSING DOCUMENTATION!
   */
  #include <stdio.h>
  #include <ctype.h>
  #include <string.h>
  #include <stdlib.h>
  #include "../SymbolsTable/StringStack.h"
  #include "../SymbolsTable/Utils.h"
  #include <unistd.h>
  #include "../stack/stack.h"
  #include "../stack/stackOffset.h"
  #include "../method_list/genlistml.h"
  #include "../assembler/assembler.h"
  #include "../interpreter/interpreter.h"
  #include "../code_3d/gencode3d.h"

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

  static inline void set_up_method_creation(char *name, ReturnType type) {
    last_def_method = name;
    push_element(error_q, symbols_table, create_method(name, type));
    push_level(symbols_table);
    returns = 0;
  }

  // Variables used for 3D code
  ListC3D *l_code3d;
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
  char* output_name = "a.out";
  char* action_input = "";
  bool executable = false;

  // abre el archivo a tratar (entrada)
  int open_input(char* name)
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

  int validate_args(char* argv[],int argc)
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
          printf("Arguments error");
          printf("\tOnly allowed: -target parse | show | interpreter | assembly | compile\n");
          return 0;
        }
        else
        {
          // Check extension files. Only allowed .ctds or .c-tds
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
      {
        output_name = argv[i];
        if(i == argc - 1)
        {
          printf("Incorrect output name.\n");
          return 0;
        }
      }
    }
    return 1;
  }

  void initialize_structures()
  {
      amount_extern_params = 0;
      error_q = initialize_queue();
      symbols_table = initialize_symbols_table();
      params_stack = initialize_string_stack();
      methods_id_stack = initialize_string_stack();
      labels_CYC = new_stack();
      labels_while = new_stack();
      return_stack = new_stack();
      labels_for = new_stack();
      max_method_offset = new_stack();
      offsets_var = new_stack_offset();
      offsets_param = new_stack_offset();
      list_meth_label = init_list_m();
      l_code3d = init_list_c3D();
  }

  void compile(char *main_file, char **linked_files, int size)
  {
    init_assembler(list_meth_label, l_code3d, file_name);
    char** args = malloc(sizeof(char*)* (6 + size));
    if (executable)
      args[0] = "gcc";
    else
      args[0] = "gcc -c";
    args[1] = main_file;
    args[1] = strcat(args[1], ".s");
    int i;
    if(linked_files != NULL)
      for(i=0;i<size;i++)
        args[2+i] = linked_files[i];
    if (executable)
      printf("Built executable file %s\n", output_name);
    pid_t child_pid = fork();
    if (child_pid == 0)
      execvp(args[0], args);    // Execute GCC compilation command.
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
  char* get_name(char* file)
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
    for(i = pos_barra + 1; i < pos_punto; i++)
      res[i - pos_barra -1] = file[i];
    return res;
  }


  int main(int argc,char **argv)
  {
    arguments_c = argc;
    arguments_v = argv;
    initialize_structures();
    if(validate_args(argv, argc) == 0)
      return EXIT_FAILURE;
    else if(strcmp(argv[1], "-target") == 0)
    {
      // Get file name.
      file_name = get_name(argv[3]);
      // Open input file.
      if(open_input(argv[3]) == EXIT_FAILURE)
        return EXIT_FAILURE;
      // Parse the input and load target.
      action_input = argv[2];
      yyparse();
    }
    else
    {
      flag_target = 0;
      // Obtengo el nombre del archivo.
      file_name = get_name(argv[1]);
      // Abro archivo de entrada.
      if(open_input(argv[1]) == EXIT_FAILURE)
        return EXIT_FAILURE;
      // Parse the input and by default load set target with "compile".
      action_input = "compile";
      executable = true;
      yyparse();
    }
    return 0;
  }

  //Al finalizar el parseo verifico si hubo errores, de lo contrario realizo la accion correspondiente al target.
  void parser_finalized()
  {
    if (error_q->size > 0)
      print_error_list(error_q);
    else
    {
      if(strcmp(action_input,"parse") == 0)
        printf("Parse finished.\n");
      else if(strcmp(action_input,"show") == 0)
      {
        printf("Showing the three-address code...");
        show_c3D(l_code3d); //Muestro el codigo 3D por terminal.
        printf("Intermediate code generated.\n");
      }
      else if(strcmp(action_input,"interpreter") == 0)
      {
        printf("Interpreting code...\n");
        init_interpreter(list_meth_label, l_code3d); //Llamo al interpreter del codigo de entrada.
        printf("Interpretation finish.\n");
      }
      else if(strcmp(action_input,"assembly") == 0)
      {
        printf("Generating assembly code...\n");
        init_assembler(list_meth_label, l_code3d, file_name); //Llamo al generador del codigo assembly y lo genero.
        printf("Assembly code generated. File's name: %s\n", file_name);
      }
      else if(strcmp(action_input,"compile") == 0)
      {
        printf("Compiling code...\n");
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
        printf("Compilation finished.\n");
      }
    }
  }

  /*Create new Label*/
  char* new_label_name(char* msg)
  {
    char *labelName = malloc(sizeof(char)*(digit_amount(label_count)+strlen("%d_label_")+strlen(msg)));
    sprintf(labelName, label_ID, label_count);
    strcat(labelName,msg);
    label_count++;
    return labelName;
  }

  int yydebug = 1;

  int yyerror (char *str)
  {
    print_error_list(error_q);
    delete_all_errors(error_q);
    if (strcmp(str, "syntax error") == 0)
      printf("%s\n",add_line_column(to_string("Gramatical error.","","")));
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
program:  CLASS ID '{' '}' { parser_finalized(); }
       |  CLASS ID '{' { push_level(symbols_table); }
          body {
            check_main(error_q,symbols_table);
            pop_level(symbols_table);
            parser_finalized(); }
          '}'
       ;
body:  fields_decls method_decl
    |  method_decl
    ;

fields_decls:  type fields ';'
            |  fields_decls type fields ';'
            ;

fields:  field
      |  fields ',' field
      ;

field:  ID { push_element(error_q, symbols_table, create_variable($1, var_type)); }
     |  ID '[' INTEGER { if (atoi($3) <= 0)
                       {   insert_error(error_q,add_line_column(to_string("Error en definicion del arreglo \"",$1,"\". El tamaño del arreglo debe ser un entero mayor que 0.")));
                           push_element(error_q, symbols_table, create_array($1, var_type, 10)); /* Array size of 10 in case of error */
                       }
                         else
                           push_element(error_q, symbols_table, create_array($1, var_type, atoi($3)));
                       }
           ']'
     ;

type:  INT_WORD		 {var_type = Int; method_type = RetInt;}
    |  FLOAT_WORD	 {var_type = Float; method_type = RetFloat;}
    |  BOOLEAN_WORD {var_type = Bool; method_type = RetBool;}
    ;

method_decl:  type ID {
                        push_offset(offsets_var, get_global_var_offset());/////////////////////////////////
                        reset_global_var_offset();////////////////////////////
                        set_up_method_creation($2, method_type);
                        add_code_label(l_code3d, new_code(LABEL), $2); // Mark to Label of Init of Method
                        push(max_method_offset, int_to_string(code_size(l_code3d)));
                        insert_method_list(list_meth_label, $2, $2);
                      } param block {
                        int pos = atoi(pop(max_method_offset));
                        set_code_int(l_code3d, pos - 1, 2, get_global_var_offset());
                        set_global_var_offset(pop_offset(offsets_var));//////////////////////////////////////////
                        if(returns==0) insert_error(error_q,add_line_column(to_string("El metodo \"",$2,"\" debe tener al menos un return.")));
                        pop_level(symbols_table);
                      }
           |		method_decl type ID {
                        push_offset(offsets_var, get_global_var_offset());
                        reset_global_var_offset();
                        set_up_method_creation($3, method_type);
                        add_code_label(l_code3d, new_code(LABEL), $3); // Mark to Label of Init of Method
                        push(max_method_offset, int_to_string(code_size(l_code3d)));
                        insert_method_list(list_meth_label, $3, $3);
                    } param block {
                        int pos = atoi(pop(max_method_offset));
                        set_code_int(l_code3d, pos - 1, 2, get_global_var_offset());
                        set_global_var_offset(pop_offset(offsets_var));
                        if(returns==0) insert_error(error_q,add_line_column(to_string("El metodo \"",$3,"\" debe tener al menos un return.")));
                        pop_level(symbols_table);
                    }
           |     VOID ID {
                      push_offset(offsets_var, get_global_var_offset());
                      reset_global_var_offset();
                      set_up_method_creation($2, RetVoid);
                      add_code_label(l_code3d, new_code(LABEL), $2); // Mark to Label of Init of Method
                      push(max_method_offset, int_to_string(code_size(l_code3d)));
                      insert_method_list(list_meth_label, $2, $2);
                  } param block {
                      int pos = atoi(pop(max_method_offset));
                      set_code_int(l_code3d, pos - 1, 2, get_global_var_offset());
                      set_global_var_offset(pop_offset(offsets_var));
                      if(returns==0) insert_error(error_q,add_line_column(to_string("El metodo \"",$2,"\" debe tener al menos un return.")));
                      pop_level(symbols_table);
                  }
           |  method_decl VOID ID {
                push_offset(offsets_var, get_global_var_offset());
                reset_global_var_offset();
                set_up_method_creation($3, RetVoid);
                add_code_label(l_code3d, new_code(LABEL), $3); // Mark to Label of Init of Method
                push(max_method_offset, int_to_string(code_size(l_code3d)));
                insert_method_list(list_meth_label, $3, $3);
              } param block {
                int pos = atoi(pop(max_method_offset));
                set_code_int(l_code3d, pos - 1, 2, get_global_var_offset());
                set_global_var_offset(pop_offset(offsets_var));
                if(returns==0) insert_error(error_q,add_line_column(to_string("El metodo \"",$3,"\" debe tener al menos un return.")));
                pop_level(symbols_table);
              }
           ;

param		      :    '(' {cant_params = 0; set_amount_of_parameters(search_id_in_symbols_table(error_q,symbols_table,last_def_method),0);} ')'
              |    '(' {if (strcmp(last_def_method,"main") == 0)
                            insert_error(error_q,add_line_column(to_string("El metodo \"main\" no debe contener parametros.","","")));
                        cant_params = 0;
						            push_offset(offsets_param, get_global_param_offset());////////////////////////////
						            reset_global_param_offset();////////////////////////////
                        }
                    parameters {
                                set_amount_of_parameters(search_id_in_symbols_table(error_q,symbols_table,last_def_method),cant_params);
								                set_global_param_offset(pop_offset(offsets_param));/////////////////////////////////////
                               }
                    ')'
              ;

parameters    :		type ID {
                           Attribute *aux = create_parameter(search_id_in_symbols_table(error_q,symbols_table,last_def_method),cant_params,$2,var_type);
                           if (aux != NULL) {push_element(error_q,symbols_table,aux); cant_params++;}
                           else insert_error(error_q,add_line_column(to_string("El identificador \"",$2,"\" no puede contener parametros/esa cantidad de parametros.")));
                          }

              |		type ID {
                           Attribute *aux = create_parameter(search_id_in_symbols_table(error_q,symbols_table,last_def_method),cant_params,$2,var_type);
                           if (aux != NULL) {push_element(error_q,symbols_table,aux); cant_params++;}
                           else insert_error(error_q,add_line_column(to_string("El identificador \"",$2,"\" no puede contener parametros/esa cantidad de parametros.")));
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
              |    {push_level(symbols_table);} block {pop_level(symbols_table);}
              |    PRINTT expression ';' {add_print(l_code3d, new_code(PRINT), $2);}
              ;

action        :
              |    BREAK {
                            if (is_empty(labels_while) && is_empty(labels_for))
                                insert_error(error_q,add_line_column(to_string("Error. Solo se puede usar la sentencia \"break\" dentro de un ciclo.","","")));
                            else{
                                char* aux = pop(labels_while);
                                char* aux2 = pop(labels_while);
                                add_code_label(l_code3d, new_code(GOTO_LABEL), peek(labels_while)); //Go to char of End of While
                                push(labels_while, aux2);
                                push(labels_while, aux);
                                }
                    }
              |    CONTINUE {
                            if (is_empty(labels_while) && is_empty(labels_for))
                                insert_error(error_q,add_line_column(to_string("Error. Solo se puede usar la sentencia \"continue\" dentro de un ciclo.","","")));
                            else
                            {
                                char *posLabel = pop(labels_while); //Label of End of While
                                add_code_label(l_code3d, new_code(GOTO_LABEL), peek(labels_while)); //Go to char of Init of While
                                push(labels_while, posLabel);
                            }
                    }
              |	   RETURNN {
                            returns++;
                            if ((id_not_found == False) && (check_return(error_q,symbols_table,last_def_method) == 0))
                            {
                                Code3D *ret = new_code(RETURN);
                                set_code_label(ret, "   -   ");  /* Label "    -    " is added because there are no arguments */
                                add_code(l_code3d, ret);
                            }
                    }
              |	   RETURNN expression {
                                    returns++;
                                    if (id_not_found == False && check_return_expression(error_q,symbols_table,last_def_method,$2) == 0)
                                    {
                                        Code3D *ret = new_code(RETURN_EXPR);
                                        set_c2D(ret, $2, search_id_in_symbols_table(error_q,symbols_table,last_def_method));
                                        add_code(l_code3d, ret);
                                    }
                    }
              |    asignation
              |    method_call
              ;

asignation    :     location assig_op expression {
                        control_assignation(error_q,l_code3d,$1,$2,$3);
                    }
              ;

assig_op      :    '=' {$$ = "=";}
              |    PLUSEQUAL {$$ = "+=";}
              |    MINUSEQUAL {$$ = "-=";}
              ;

/* -------------------- END OF STATEMENTS ------------------------------- */

/* -------------------- CONDITIONALS AND CICLES ------------------------------ */

conditional   :     IF '(' {
                        add_code_label(l_code3d, new_code(LABEL), new_label_name("if"));
                    } expression {
                        control_type(error_q,$4,Bool,"if",1);
                        char *else_label = new_label_name("else");
                        add_code_label_cond(l_code3d, new_code(GOTO_LABEL_COND), $4, else_label);
                        push(labels_CYC, new_label_name("end_if"));
                        push(labels_CYC, else_label);
                    } ')' block optional
              ;

optional	  :		{
                        add_code_label(l_code3d, new_code(LABEL), pop(labels_CYC)); // Mark to char of End
                        push(return_stack, pop(labels_CYC));
                    }
              |	   	ELSE {
                        char* else_label = pop(labels_CYC);
                        add_code_label(l_code3d, new_code(GOTO_LABEL), peek(labels_CYC)); //Go to char of Else
                        add_code_label(l_code3d, new_code(LABEL), else_label); // Mark to char of Else
                    } block {
                        char* aux = pop(labels_CYC);
                        add_code_label(l_code3d, new_code(LABEL), aux); // Mark to char of End
                        push(return_stack, aux);
                    }
              ;

iteration     :    WHILE {
                        char *while_label = new_label_name("while");
                        add_code_label(l_code3d, new_code(LABEL), while_label); // label of While
                        push(labels_while, while_label);
                        push(labels_while, int_to_string(code_size(l_code3d)));
                    }
                   expression {
                        char *endWhile = new_label_name("end_while");
                        char *pos = pop(labels_while);
                        char *while_label = pop(labels_while);
                        push(labels_while, endWhile);
                        push(labels_while, while_label);
                        push(labels_while, pos);
                        control_type(error_q,$3,Bool,"while",1);
                        add_code_label_cond(l_code3d, new_code(GOTO_LABEL_COND), $3, endWhile); // Go to label of Expression
                    } block {
                        add_code(l_code3d, get_code(l_code3d, atoi(pop(labels_while))+1));
                        add_code_label(l_code3d, new_code(GOTO_LABEL), pop(labels_while)); // Go to label of while
                        add_code_label(l_code3d, new_code(LABEL), pop(labels_while)); // label_end of while
                    }
              |    FOR ID {
                        if (get_attribute_type(get_variable_attribute(error_q,symbols_table,$2)) != Int)
                            insert_error(error_q,add_line_column(to_string("El identificador \"", $2, "\" no pertenece a una variable de tipo \"int\"")));
                        /* It musn't have the same treatment that while? */
                    } '=' expression ',' expression {
                            control_type(error_q,$5,Int,"for",2); control_type(error_q,$7,Int,"for",3);
                            char *for_label = new_label_name("for");
                            char *end_label = new_label_name("end_for");
                            push(labels_for, end_label);
                            push(labels_for, for_label);
                            push(labels_for, int_to_string(code_size(l_code3d)));
                            add_assignation(l_code3d, $5, get_variable_attribute(error_q, symbols_table, $2));
                            Attribute *res = return_minor_comparison(error_q, l_code3d, get_variable_attribute(error_q, symbols_table, $2), $7);
                            add_code_label(l_code3d, new_code(LABEL), for_label);
                            add_code_label_cond(l_code3d, new_code(GOTO_LABEL_COND), res, end_label); // Go to label of Expression
                    } block {
                            control_assignation(error_q,l_code3d,get_variable_attribute(error_q,symbols_table,$2),"+=",return_value(l_code3d,Int,"1"));
                            add_code(l_code3d, get_code(l_code3d, atoi(pop(labels_for))+1));
                            add_code_label(l_code3d, new_code(GOTO_LABEL), pop(labels_for)); // Go to label of For
                            add_code_label(l_code3d, new_code(LABEL), pop(labels_for)); // label_end of For
                    }
              ;

/* -------------------- END OF CONDITIONALS AND CICLES ------------------------------- */

/* -------------------- EXPRESSIONS ------------------------------- */

location      :    ID {$$ = get_variable_attribute(error_q, symbols_table, $1);}
              |    ID '[' expression ']' {$$ = check_array_pos(error_q,symbols_table,l_code3d,$1,$3);}
              ;

method_call   :	   ID '(' ')' {
                        cant_params=0;
                        last_called_method=$1;
                        add_code_label(l_code3d, new_code(GOTO_METHOD), get_label_ml(list_meth_label, $1)); //Go to char of Init of Method
                        $$ = check_get_method_ret_attribute(error_q,symbols_table,l_code3d,$1,0);
                    }

				|    ID '(' { if (search_id_in_symbols_table(error_q,symbols_table,$1) == NULL)
                          id_not_found = True;
                      else
                      {
                          push_string(params_stack,int_to_string(cant_params));
                          cant_params = 0;
                          push_string(methods_id_stack,last_called_method);
                          last_called_method = $1;
                      }
                    } expression_aux ')' {
                            if (id_not_found == False)
                            {
                                set_code_int(l_code3d, flag_first_param - 1, 3, cant_params);
                                flag_first_param = 0;
                                add_code_label(l_code3d, new_code(GOTO_METHOD), get_label_ml(list_meth_label, $1)); //Go to char of Init of Method
                                $$ = check_get_method_ret_attribute(error_q,symbols_table,l_code3d,$1,cant_params);
                                cant_params=atoi(pop_string(params_stack));
                            }
                            else
                            {
                                $$ = create_variable((char*) get_variable_name(),Int);
                                id_not_found = False;
                            }
                    }

				|    EXTERNINVK '(' STRING ',' typevoid ')' {
                        amount_extern_params = 0;
                        Attribute* res;
                        if (method_type != RetVoid)
                            res = create_variable("",method_type);
                        else
                            res = create_variable((char*) get_variable_name(),Int);
                        char token[2] = "\"";
                        add_code_externinvk(l_code3d, new_code(EXTERN_INVK), strtok($3, token), $5);
                        $$ = res;
                    }
				|    EXTERNINVK '(' STRING ',' typevoid ',' { amount_extern_params = 0; } externinvk_arg ')' {
                        Attribute* res;
                        char token[2] = "\"";
                        if (method_type != RetVoid)
                        {
                            res = create_variable("", method_type);
                            add_code_externinvk(l_code3d, new_code(EXTERN_INVK), strtok($3, token), $5);
                        }
                        else
                        {
                            res = create_variable((char*) get_variable_name(), Int);
                            add_code_externinvk(l_code3d, new_code(EXTERN_INVK), strtok($3, token), "int");
                        }
                        $$ = res;
                    }
				;

expression_aux:    expression {
                        if (id_not_found == False)
                        {
                            correct_param_base_case(error_q,symbols_table,l_code3d,$1,last_called_method,cant_params);
                            if (flag_first_param == 0)
                                flag_first_param = code_size(l_code3d);
                            cant_params++;
                        }
                    }
              |    expression {
                        if (id_not_found == False)
                        {
                            correct_param_inductive_case(error_q,symbols_table,l_code3d,$1,last_called_method,cant_params);
                            if (flag_first_param == 0)
                                flag_first_param = code_size(l_code3d);
                            cant_params++;
                        }
                   } ',' expression_aux
              ;

typevoid      :    type {switch (method_type)
                        {
                            case RetInt:   $$ = "int"; break;
                            case RetFloat: $$ = "float"; break;
                            case RetBool:  $$ = "bool"; break;
                            case RetVoid:  $$ = "void"; break;
                        }
                   }
              |    VOID {method_type = RetVoid; $$ = "void";}
              ;

externinvk_arg:    arg                    {amount_extern_params++; extern_param_assign(l_code3d, $1, amount_extern_params);}
              |    externinvk_arg ',' arg {amount_extern_params++; extern_param_assign(l_code3d, $3, amount_extern_params);}
              ;

arg           :    expression {$$ = $1;}
              |    STRING     {$$ = create_variable("", Int);} // {$$ = $1;}
              ;               // I commented this because extern_param_assign expects an Attribute and STRING doesn't provide one

expression    :    conjunction					{$$ = $1;}
              |    expression ORR conjunction	{$$ = return_or(error_q, l_code3d, $1, $3);}
              ;

conjunction   :    inequality                   {$$ = $1;}
              |    conjunction ANDD inequality	{$$ = return_and(error_q, l_code3d, $1, $3);}
              ;

inequality    :    comparison                       {$$ = $1;}
              |    inequality DISTINCT comparison   {$$ = return_distinct(error_q, l_code3d, $1, $3);}
              ;

comparison    :    relation                   {$$ = $1;}
              |    relation EQUAL relation    {$$ = return_equal(error_q, l_code3d, $1, $3);}
              ;

relation      :    term                 {$$ = $1;}
              |    term '<' term        {$$ = return_minor_comparison(error_q, l_code3d, $1, $3);}
              |    term '>' term        {$$ = return_major_comparison(error_q, l_code3d, $1, $3);}
              |    term GEQUAL term     {$$ = return_g_equal_comparison(error_q, l_code3d, $1, $3);}
              |    term LEQUAL term     {$$ = return_l_equal_comparison(error_q, l_code3d, $1, $3);}
              ;

term          :    factor1			    {$$ = $1;}
              |    factor1 '+' term	    {$$ = return_add(error_q, l_code3d, $1, $3);}
              |    factor1 '-' term	    {$$ = return_sub(error_q, l_code3d, $1, $3);}
              ;

factor1       :    factor			    {$$ = $1;}
              |    factor '*' factor1	{$$ = return_mult(error_q, l_code3d, $1, $3);}
              |    factor '/' factor1	{$$ = return_div(error_q, l_code3d, $1, $3);}
              |    factor '%' factor1	{$$ = return_mod(error_q, l_code3d, $1, $3);}
              ;

factor        :    primary		{$$ = $1;}
              |    '!' factor	{$$ = return_not(error_q, l_code3d, $2);}
              |    '-' factor	{$$ = return_neg(error_q, l_code3d, $2);}
              ;

primary       :    INTEGER			{$$ = return_value(l_code3d, Int, $1);}
              |    FLOAT            {$$ = return_value(l_code3d, Float, $1);}
              |    BOOLEAN          {$$ = return_value(l_code3d, Bool, $1);}
              |    ID				{$$ = get_variable_attribute(error_q,symbols_table,$1);}
              |    ID '[' expression ']'  {$$ = check_array_pos(error_q,symbols_table,l_code3d,$1,$3);}
              |    '(' expression ')' {$$ = $2;}
              |    method_call      { if (method_return_type(error_q,symbols_table,last_called_method) == RetVoid)
                                      {	insert_error(error_q,add_line_column(to_string("El metodo \"",last_called_method,"\" no puede ser usado en una expresion ya que retorna void.")));
                                          $$ = create_variable("",Int); /* creamos variables int por defecto para que podamos seguir parseando el codigo */
                                      }
                                      else $$ = $1;
                                      last_called_method=pop_string(methods_id_stack); }
              ;

/* ------------------------- END OF EXPRESSIONS ------------------------------- */

%%
