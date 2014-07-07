#!/bin/bash

# Source code
lex_yacc="../src/LexYacc/*.c"
symbols_table="../src/SymbolsTable/*.c"
errors_queue="../src/ErrorsQueue/*.c"
code_3d="../src/code_3d/*.c"
stack="../src/Stack/*.c"
list_method="../src/ListMethod/*.c"
interpreter="../src/Interpreter/*.c"
assembler="../src/Assembler/*.c"
libs="../src/lib/*.c"

# Compile lex and yacc files
echo
echo "Compiling Lex File..."
cd src/LexYacc/
lex lexC-TDS.l
echo
echo "Compiling Yacc File..."
yacc -d yaccC-TDS.y

# Compile c-tds and check it compilation.
echo
echo "Compiling source code..."
cd ../../bin/
if gcc -o c-tds $lex_yacc $symbols_table $errors_queue $code_3d $stack $list_method $interpreter $assembler; then
  echo "Compilation finished...   c-tds compiler generated in bin/c-tds succesfully."
  # Clean all unnecessary files.
  rm $lex_yacc
  rm ../src/LexYacc/*.h
else
  echo
  echo "Failure. Error to compile c-tds compiler."
fi

exit 0
