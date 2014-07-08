#!/bin/bash

# Source code
lex_yacc="../src/lex_yacc/*.c"
symbols_table="../src/SymbolsTable/*.c"
errors_queue="../src/errors_queue/*.c"
code_3d="../src/code_3d/*.c"
stack="../src/stack/*.c"
method_list="../src/method_list/*.c"
interpreter="../src/interpreter/*.c"
assembler="../src/assembler/*.c"
libs="../src/lib/*.c"

# Compile lex and yacc files
echo
echo "Compiling Lex File..."
cd src/lex_yacc/
lex *.l
echo
echo "Compiling Yacc File..."
yacc -d *.y

# Compile c-tds and check it compilation.
echo
echo "Compiling source code..."
cd ../../bin/
if gcc -o c-tds $lex_yacc $symbols_table $errors_queue $code_3d $stack $method_list $interpreter $assembler; then
  echo "Compilation finished...   c-tds compiler generated in bin/c-tds succesfully."
  # Clean all unnecessary files.
  rm $lex_yacc
  rm ../src/lex_yacc/*.h
else
  echo
  echo "Failure. Error to compile c-tds compiler."
fi

exit 0
