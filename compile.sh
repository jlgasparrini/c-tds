#!/bin/bash
# Script for compile all project.
LexYacc="../src/LexYacc/*.c"
SymbolsTable="../src/SymbolsTable/*.c"
ErrorsQueue="../src/ErrorsQueue/*.c"
Code3D="../src/Code3D/*.c"
Stack="../src/Stack/*.c"
ListMethod="../src/ListMethod/*.c"
Interpreter="../src/Interpreter/*.c"
Assembler="../src/Assembler/*.c"
Libs="../src/lib/*.c"
echo
echo "Compiling Lex File..."
cd src/LexYacc/
lex lexC-TDS.l
echo
echo "Compiling Yacc File..."
yacc -d yaccC-TDS.y
echo
echo "Compiling source code..."
cd ../../bin/
gcc -w -o c-tds $LexYacc $SymbolsTable $ErrorsQueue $Code3D $Stack $ListMethod $Interpreter $Assembler
echo 
echo "Compilation finished...   c-tds compiler generated succesfully."
# Clean all unnecessary files.
rm $LexYacc
rm ../src/LexYacc/*.h
echo
echo "Press ENTER key to continue..."
read
clear
exit 0
