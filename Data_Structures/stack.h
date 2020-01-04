/**** stack.h ***********************************************
 * Name: Daniel Mendez
 * Date: 10/09/2019
 * Purpose: Specification of functions and element struct 
 *          for a stack data structure 
************************************************************/

#include "binaryTree.h"

extern int MAXSIZE; //Maximum number of Binary Trees in the stack
extern int top;     //Index for the stack of Binary Trees

#ifndef STACK
#define STACK

    typedef struct treeElement {
        char name[8];
        Node* rootPointer;
    } TreeELEM;


    int isFull();
    int isEmpty();
    int topIndex();
    void push(TreeELEM stack[], char treeName[]);
    void pop(TreeELEM stack[]);
    void add(TreeELEM stack[], int val, char nodeString[]);
    Node* localSearch(Node* binaryTreeRoot, char targetString []); // NOTE: I MODIFIED THE CODE FOR THE search FUNCTION
                                                                   // from a website I mentioned in the binTree.c file
    Node* globalSearch(TreeELEM stack[], char targetString []);
    void quit();

    char* returnKind(Node* currentNode);
    int countGlobalSearch(TreeELEM stack[], char targetString []);


#endif
