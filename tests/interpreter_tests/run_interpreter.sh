#!/bin/bash
#*****************************     Tests     ********************************
#**                                                                        **
#** Description: This script run all tests case for check that interpreter **
#** it's working correctly.                                                **
#**              tests. cada test tiene su propio main.                    **
#**                                                                        **
#****************************************************************************
echo "*********************************************************************************** "
echo "**                                                                               ** "
echo "**                            Running interpreter tests . . .                    ** "
echo "**                                                                               ** "
echo "*********************************************************************************** "
echo "     "
echo "     "

compiler="../../bin/c-tds -target interpreter"

# tests files.
files=`ls *.c-tds`

for each_file in $files; do
	echo "---------------- Test $each_file ... --------------"
        ./$compiler $each_file
	echo "---------------------------------------------------"
        echo
        echo
done

exit 0
