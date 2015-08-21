
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
echo "**                            Corriendo Assembler tests . . .                    ** "                
echo "**                                                                               ** "
echo "**                                                                               ** "
echo "*********************************************************************************** "
echo "     " 
echo "     " 

comp="../../bin/c-tds"

files=`ls *.c-tds`
for file in $files ; do 
	echo "---------------- Test $file ... -------------------" 
        ./$comp $file -o $file
	echo "---------------------------------------------------" 
        echo "  "
        echo "  "
done

echo Press ENTER to continue.
read
exit 0

