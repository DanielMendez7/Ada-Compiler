#### For this whole project I wrote approximately 3700 lines of C source code which is found in multiple files from the three directories listed below.

- The *AdaSubset_Grammar* directory contains the main part of my project in these yacc and lex files that I wrote:
    1) *ada.y*
    2) *ada.l*
    3) *AMI_Output_Patched.out*   <--- This file contains the compiled code generated by my Ada compiler

- The Following directories contain C source code files that I wrote which are used in my *ada.y* file:
    1) *Data_Structures* directory
        - *binaryTree.c*
        - *binaryTree.h*
        - *listOfStructs.c*
        - *listOfStructs.h*
        - *patchDataStructures.c*
        - *record.c*
        - *stack.c*
        - *stack.h*
    2) *Test_Data_Structures* directory
        - *testListOfStructs.c*
        - *testStackOfBinaryTrees.c*

# License:
This project is licensed under the MIT License - see the *LICENSE.md* file for details
