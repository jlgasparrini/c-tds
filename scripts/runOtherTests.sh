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
echo "**                   Corriendo casos de prueba.                                  ** "
echo "**                                                                               ** "
echo "*********************************************************************************** "
echo "     " 
echo "     " 


comp="c-tds"
files=`ls tests/oldTests/*.c-tds`

for file in $files ; do 
	echo "---------------- Test $file ... -------------------" 
        ./$comp $file 
	echo "---------------------------------------------------" 
        echo "  "
        echo "  "
done
echo Fin de compilacion.        #Presione ENTER para terminar.
#read
#clear
exit 0

