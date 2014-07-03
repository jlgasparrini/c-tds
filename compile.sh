#!/bin/bash

# Source code
LexYacc="../src/LexYacc/*.c"
SymbolsTable="../src/SymbolsTable/*.c"
ErrorsQueue="../src/ErrorsQueue/*.c"
Code3D="../src/Code3D/*.c"
Stack="../src/Stack/*.c"
ListMethod="../src/ListMethod/*.c"
Interpreter="../src/Interpreter/*.c"
Assembler="../src/Assembler/*.c"
Libs="../src/lib/*.c"

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
if gcc -o c-tds $LexYacc $SymbolsTable $ErrorsQueue $Code3D $Stack $ListMethod $Interpreter $Assembler; then
  echo 
  echo "Compilation finished...   c-tds compiler generated in bin/c-tds succesfully."
else
  echo
  echo "Failure. Error to compile c-tds compiler."
fi

# Clean all unnecessary files.
rm $LexYacc
rm ../src/LexYacc/*.h

exit 0
