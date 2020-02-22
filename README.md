# Implementing-Quick-Shell-and-Merge-Sort-on-Dynamic-Array-
Add a large list of numbers from a text file that can be any positive value into a dynamic array, and Sort the list of numbers in ascending order or descending order with three different sorting methods(merge,quick,shell) as specified by the command file.
# Assumptions:
- The input file is a text file; no need to handle binary files.
- Characters are case sensitive.
- The command file contains one line in the same order of "sort method ascending/descending and indexes to select from input file array for sorting"

# Notes
- The 9 "input2x.txt" files are the 9 input files that were used to test this code
- The 9 "output2x.txt" files are the files outputted by the program.
- The 9 "ans2x.txt" files are files containing the correct output that should occur from each corresponding input file, and are available
for comparison to the outputs files to ensure correct output. 
- The 9 "command2x.txt" files contain the command the code must parse through and execute.
- This code was tested on the University of Houston's Linux server and passed all the test cases.
- The "ArgumentManager.h" file parses arguments to sequentially open the 9 input files to automatically test the code on the server.
- The "test.sh" file is a SHELL script for automatically testing the input files on the Linux server.
- The "compile.sh" file is  SHELL script for automatically compiling the code on the Linux server before running the tests.

# Resources:

www.geeksforgeeks.org/3-way-quicksort-dutch-national-flag/
