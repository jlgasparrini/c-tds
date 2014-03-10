#!/bin/bash
# Script for compile all project.
echo
echo "Compiling Lex File..."
cd src/LexYacc/
lex lexC-TDS.l
echo
echo "Compiling Yacc File..."
yacc -d yaccC-TDS.y
echo
echo "Compiling source code..."
cd ../../src/
gcc -w -o c-tds LexYacc/*.c SymbolsTable/*.c ErrorsQueue/*.c Code3D/*.c Stack/*.c ListMethod/*.c Interpreter/*.c Assembler/*.c
echo 
echo "Compilation finished...   c-tds compiler generated succesfully."
# Clean all unnecessary files.
rm src/LexYacc/*.c
rm src/LexYacc/*.h
echo
echo "Press any key to continue..."
read
clear
exit 0
