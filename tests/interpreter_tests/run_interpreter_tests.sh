#!/bin/bash

# *****************************     Tests     ********************************
# **                                                                        **
# ** Description: This script run all tests case for check that interpreter **
# **              it's working correctly.                                   **
# **                                                                        **
# ****************************************************************************

echo
echo "**************************************************************************** "
echo "**                                                                        ** "
echo "**                     Running interpreter tests . . .                    ** "
echo "**                                                                        ** "
echo "**************************************************************************** "
echo

# c-tds interpreter.
interpreter="../../bin/c-tds -target interpreter"

# Tests files.
tests=`ls *.c-tds`

for each_file in $tests; do
	echo "---------------- Test $each_file ------------------"
        ./$interpreter $each_file
	echo "---------------------------------------------------"
  echo
done

exit 0
