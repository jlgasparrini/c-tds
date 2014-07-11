#!/bin/bash

# *****************************     test     **********************************
# **                                                                         **
# ** Description : This script run all scripts tests case for check          **
# **               that c-tds parse code correctly and incorrectly.          **
# **                                                                         **
# *****************************************************************************

echo
echo "///////////////////////// RIGHT TESTS ///////////////////////////////////////"
# Check that compiler parse code correctly.
cd 'right_tests'
sh 'run_right_semantic_tests.sh'
cd ..

echo
echo "///////////////////////// FAIL TESTS ////////////////////////////////////////"
# Check that compiler parse code errors correctly.
cd 'wrong_tests'
sh 'run_error_semantic_test.sh'
cd ..

exit 0
