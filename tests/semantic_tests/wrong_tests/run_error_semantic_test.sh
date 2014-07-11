#!/bin/bash

# *****************************     test     **********************************
# **                                                                         **
# ** Description : This script run all tests case for check that c-tds parse **
# **               code correctly.                                           **
# **                                                                         **
# *****************************************************************************
echo
echo "*********************************************************************************** "
echo "**                                                                               ** "
echo "**                  Run wrong semantics tests . . .                              ** "
echo "**                                                                               ** "
echo "*********************************************************************************** "
echo

# c-tds compiler.
compiler="../../../bin/c-tds -target parse"

# Tests files.
tests=`ls *.c-tds`

for each_file in $tests ; do
	echo "---------------- Test $each_file ------------------"
        ./$compiler $each_file
	echo "---------------------------------------------------"
  echo
done

exit 0
