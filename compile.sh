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
gcc -o c-tds LexYacc/lex.yy.c LexYacc/y.tab.c SymbolsTable/SymbolsTable.c SymbolsTable/LinkedList.c SymbolsTable/Utils.c SymbolsTable/Attribute.c ErrorsQueue/ErrorsQueue.c SymbolsTable/StringStack.c Code3D/gencode3d.c Code3D/code3d.c Code3D/listc3d.c Code3D/nodec3d.c Stack/stack.c Stack/linknode.c Code3D/codespecs.c
echo 
echo   Fin de compilacion.          #Presione ENTER para terminar.
rm LexYacc/y.tab.c 
rm LexYacc/y.tab.h

#read
#clear
exit 0
