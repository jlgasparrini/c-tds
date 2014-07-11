#!/bin/bash

# ************************     Test suite    ***************************
# **                                                                  **
# ** Description: This script run all tests case for check that c-tds **
# **              it's working correctly in all modes.                **
# **                                                                  **
# **********************************************************************

echo
echo "******************************************************************************* "
echo "******************************************************************************* "
echo "**                              TEST SUITE                                   ** "
echo "**                        RUNNING ALL TESTS CASES . . .                      ** "
echo "******************************************************************************* "
echo "******************************************************************************* "
echo

# Check that compiler it's working correctly.
cd 'semantic_tests'
sh 'run_semantic_tests.sh'
cd ..

# Check that interpreter it's working correctly.
cd 'interpreter_tests'
sh 'run_interpreter_tests.sh'
cd ..

exit 0
