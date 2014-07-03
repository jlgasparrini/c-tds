# include <stdio.h>
//Test library.

// External invocation without parameters.
void pepe()
{
  printf("Invoque a pepe sin parametros.\n");
  printf("\n");
}

// External invocation with int param.
void int_number(int number)
{
  printf("Invoque a int_number con el parametro %d\n", number);
  printf("\n");
}

// External invocation with six int of param.
void int_six_numbers(int n1, int n2, int n3, int n4, int n5, int n6)
{
  printf("Invoque a int_six_numbers con los parametros %d, %d, %d, %d, %d, %d.... \n", n1,n2,n3,n4,n5,n6);
  printf("\n");
}

// External invocation with ten int of param.
void int_ten_numbers(int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9, int n10)
{
  printf("Invoque a int_ten_numbers con los parametros %d, %d, %d, %d, %d, %d, %d, %d, %d, %d.... \n", n1,n2,n3,n4,n5,n6,n7,n8,n9,n10);
  printf("\n");
}

// External invocation with string param.
void string_function(char* string)
{
  printf("Invoque a string_name con el parametro %s\n", string);
  printf("\n");
}

// External invocation with int param.
void float_number(float number)
{
  printf("Invoque a float_number con el parametro %f\n", number);
  printf("\n");
}

// External invocation with six int of param.
void float_six_numbers(float n1, float n2, float n3, float n4, float n5, float n6)
{
  printf("Invoque a float_six_numbers con los parametros %f, %f, %f, %f, %f, %f.... \n", n1,n2,n3,n4,n5,n6);
  printf("\n");
}

// External invocation with ten int of param.
void float_ten_numbers(float n1, float n2, float n3, float n4, float n5, float n6, float n7, float n8, float n9, float n10)
{
  printf("Invoque a float_ten_numbers con los parametros %f, %f, %f, %f, %f, %f, %f, %f, %f, %f.... \n", n1,n2,n3,n4,n5,n6,n7,n8,n9,n10);
  printf("\n");
}

// External invocation with a bool param.
void bool_value(int value)
{
  if (value)
    printf("Invoque a bool_value con el parametro true...\n");
  else
    printf("Invoque a bool_value con el parametro false....\n");
  printf("\n");
}

// External invocation with six bool of param.
void bool_six_values(int n1, int n2, int n3, int n4, int n5, int n6)
{
  printf("Bool values:   ");
  bool_value(n1);
  bool_value(n2);
  bool_value(n3);
  bool_value(n4);
  bool_value(n5);
  bool_value(n6);
  printf("\n");
}

// External invocation with ten bool of param.
void bool_ten_values(int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9, int n10)
{
  printf("Bool values:   ");
  bool_value(n1);
  bool_value(n2);
  bool_value(n3);
  bool_value(n4);
  bool_value(n5);
  bool_value(n6);
  bool_value(n7);
  bool_value(n8);
  bool_value(n9);
  bool_value(n10);
  printf("\n");
}
