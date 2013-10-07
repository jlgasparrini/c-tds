#!/bin/bash

# Script for compile all project.

echo   Compilando lexer....
cd LexYacc
lex lexC-TDS.l
echo
echo   Compilando parser....
yacc -d yaccC-TDS.y
echo
echo   Compilando c....
cd ..
gcc -o c-tds LexYacc/lex.yy.c LexYacc/y.tab.c SymbolsTable/SymbolsTable.c SymbolsTable/LinkedList.c SymbolsTable/Utils.c SymbolsTable/Attribute.c ErrorsQueue/ErrorsQueue.c SymbolsTable/StringStack.c 
echo 
echo   Fin de compilacion.          #Presione ENTER para terminar.
#read
#clear
exit 0
