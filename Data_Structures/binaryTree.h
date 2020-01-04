/**** binaryTree.h ***********************************************
 * Name: Daniel Mendez
 * Date: 10/09/2019
 * Purpose: Specification of functions and Node struct for a 
 *          Binary Tree data structure
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef BINARYTREE
#define BINARYTREE

enum typeOfNode {garbage=-1, parameter=0, predefined=1, procedure=2, variable=3, type=4, value=5, exception=6, read_routine=7, write_routine=8, array_type=9, record_type=10};

enum typeOfVariable {not_declarable=-1, integer=0, boolean=1, array=2, record=3};

    typedef struct node
    {

        //strings
        char symbol[20];
        char* mode;

        //enumerated types
        enum typeOfNode kind;
        enum typeOfVariable variableType;   // Need to check if read is a read_integer or read_boolean
        
        //ints
        int val;    //Unused for part 3 and for right now
        int lower;
        int upper;

        //pointers
        struct node* left;
        struct node* right;
        struct node* parent_type;
        struct node* component_type;
        struct node* next;


        //Everything for records in assignments 
        int offset; 
        int registerNumber;

        //Everything for procedures part
        int procStart;

        //Everything for records in Ada
        struct RecordList*  listOfVariables;
        int memorySpace;

        //Everything for exceptions in Ada
        int exceptionNumber;
        
    } Node;


    Node* createNode(int givenValue, char nodeString []);
    Node* insert(Node* subRoot, int val, char nodeString []);
    void printDFS(Node * current); // NOTE: CODE FOR THE printDFS FUNCTION DOES NOT BELONG TO ME
    void printBTNodesNextDFS(Node* current);

void detachDuplicates(Node *firstNode);


#endif
