

# Script for compile all project.

echo   Compilando lexer....
cd ..
cd LexYacc
lex lexC-TDS.l
echo
echo   Compilando parser....
yacc -d yaccC-TDS.y
echo
echo   Compilando c....
cd ..
#gcc -Wall -o c-tds LexYacc/lex.yy.c LexYacc/y.tab.c SymbolsTable/SymbolsTable.c SymbolsTable/LinkedList.c SymbolsTable/Utils.c SymbolsTable/Attribute.c ErrorsQueue/ErrorsQueue.c SymbolsTable/StringStack.c Code3D/nodec3d.c Code3D/code3d.c Code3D/codespecs.c Code3D/gencode3d.c Code3D/listc3d.c Stack/stack.c Stack/linknode.c ListMethod/genlistml.c ListMethod/listml.c ListMethod/nodeml.c ListMethod/methodl.c

#for interpreter
gcc -w -o c-tds LexYacc/lex.yy.c LexYacc/y.tab.c SymbolsTable/SymbolsTable.c SymbolsTable/LinkedList.c SymbolsTable/Utils.c SymbolsTable/Attribute.c ErrorsQueue/ErrorsQueue.c SymbolsTable/StringStack.c Code3D/nodec3d.c Code3D/code3d.c Code3D/codespecs.c Code3D/gencode3d.c Code3D/listc3d.c Stack/stack.c Stack/linknode.c ListMethod/genlistml.c ListMethod/listml.c ListMethod/nodeml.c ListMethod/methodl.c Interpreter/Interpreter.c

#for assembly 
#gcc -o c-tds LexYacc/lex.yy.c LexYacc/y.tab.c SymbolsTable/SymbolsTable.c SymbolsTable/LinkedList.c SymbolsTable/Utils.c SymbolsTable/Attribute.c ErrorsQueue/ErrorsQueue.c SymbolsTable/StringStack.c Code3D/nodec3d.c Code3D/code3d.c Code3D/codespecs.c Code3D/gencode3d.c Code3D/listc3d.c Stack/stack.c Stack/linknode.c ListMethod/genlistml.c ListMethod/listml.c ListMethod/nodeml.c ListMethod/methodl.c Assembler/Assembler.c Assembler/Translate.c


echo 
echo   Fin de compilacion.          #Presione ENTER para terminar.
rm LexYacc/lex.yy.c
rm LexYacc/y.tab.c 
rm LexYacc/y.tab.h

#read
#clear
exit 0
