#!/bin/bash

#
#                           ******************                           
#*****************************     test     ****************************************
#**                         ******************                                    **
#**                                                                               **
#**Descripcion : Script que corre los casos de prueba definidos en la carpeta     **
#**              tests. cada test tiene su propio main.                          **
#**                                                                               **
#***********************************************************************************   
echo "*********************************************************************************** "
echo "**                                                                               ** " 
echo "**                  Corriendo casos de prueba correctos . . .                    ** "                
echo "**                                                                               ** "
echo "**                                                                               ** "
echo "*********************************************************************************** "
echo "     " 
echo "     " 
comp="../c-tds"

echo "///////////////////////// TESTS CORRECTOS ////////////////////////////////////////" 
files=`ls ../tests/semanticos/test_correctos/*.c-tds`


for file in $files ; do 
	echo "---------------- Test $file ... -------------------" 
        ./$comp $file 
	echo "---------------------------------------------------" 
        echo "  "
        echo "  "
done
echo Press ENTER to continue.
read
exit 0

