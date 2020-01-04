/**** binaryTree.c ***********************************************
 * Name: Daniel Mendez
 * Date: 10/09/2019
 * Purpose: Definitions of functions for a Binary Tree data structure.
*****************************************************************/
#include "binaryTree.h"



Node* createNode(int givenValue, char nodeString [])
{
    Node* currentNode = (Node *)malloc(sizeof(Node)); //create node

    //strings
    strcpy(currentNode->symbol, nodeString); // name
    currentNode->mode = NULL;                //mode

    //enumerated types
    currentNode->kind = 0;                       //kind of node
    currentNode->variableType = not_declarable;  // Need to check if read is a read_integer or read_boolean

    //ints
    currentNode->val = givenValue;           //value
    currentNode->lower = 0;                  //lower
    currentNode->upper = 0;                  //upper

    //Pointers
    currentNode->left = NULL;                //left
    currentNode->right = NULL;               //right
    currentNode->parent_type = NULL;         //parent_type
    currentNode->component_type = NULL;      //component_type
    currentNode->next = NULL;                //next


    //Everything for records in assignments
    currentNode->offset = 0;
    currentNode->registerNumber = 0;
    //currentNode->isMemAddress = 0; //false

    //Everything for procedures part
    currentNode->procStart = 0;

    //Everything for records in Ada
    currentNode->listOfVariables = NULL; //Keeps track of the variables in the record
    currentNode->memorySpace = 0;

    //Everything for exceptions in Ada
    currentNode->exceptionNumber = 0;
    
    return currentNode;
}


Node* insert(Node* subRoot, int val, char nodeString [])
/***********************************************
Inserts new nodes into the binary tree according 
to string comparisons
************************************************/
{
    if (subRoot == NULL) {
        subRoot = createNode(val, nodeString);
        //printf("SUCCESSFULLY added symbol, (%d, %s) to topmost Binary Tree\n", val, nodeString);
    }
    else if (strcmp(nodeString, subRoot->symbol) < 0) {
        subRoot -> left = insert(subRoot->left, val, nodeString);
    }
    else if (strcmp(nodeString, subRoot->symbol) > 0) {
        subRoot -> right = insert(subRoot->right, val, nodeString);
    }

    return subRoot;
}


void printDFS(Node * current)
/***********************************************
Prints out all the node values of the topmost 
binary tree In Order Traversal
NOTE: I MODIFIED THIS EXISTING FUNCTION TO FIT MY NEEDS,
      LOOK AT README.md FILE
************************************************/
{
    if (current == NULL)         return;   // security measure 
    if (current->left != NULL)   printDFS(current->left);
    if (current != NULL)         printf("(%s,  %d,  %s,  %s)\n", current->symbol, (int)current->kind, current->parent_type->symbol, current->component_type->symbol);
    if (current->right != NULL)  printDFS(current->right);
}


void printBTNodesNextDFS(Node* current)
/***********************************************
Prints out all the node values of the topmost 
binary tree In Order Traversal according to the next pointer member variable
NOTE: I MODIFIED THIS EXISTING FUNCTION TO FIT MY NEEDS,
      LOOK AT README.md FILE
************************************************/
{
    if (current == NULL)
        return;   // security measure 
    else 
        while (current != NULL) {
           printf("(%s, %d, %s)\n", current->symbol, (int)current->kind, current->parent_type->symbol);
           current = current -> next;
        }    
}



void detachDuplicates(Node *firstNode)
/***********************************************
Starting from left to right of the list, the second
instance of a node with the same string will be 
removed from the list. 
NOTE: I MODIFIED THIS EXISTING FUNCTION TO FIT MY NEEDS,
       LOOK AT README.md FILE
************************************************/
{ 
    Node *traverseList, *ptr2, *duplicatePointer; 
    traverseList = firstNode; 
  
    // Pick elements one by one 
    while (traverseList != NULL && traverseList->next != NULL) { 
        ptr2 = traverseList; 
  
        //Compare the picked element with rest of the elements
        while (ptr2->next != NULL) {
            
            //Found duplicate so delete it
            if (strcmp(traverseList->symbol, ptr2->next->symbol) == 0) { 
                duplicatePointer = ptr2->next; 
                ptr2->next = ptr2->next->next; 
                free(duplicatePointer); 
            } 
            else
                ptr2 = ptr2->next; 
        } 
        traverseList = traverseList->next; 
    } 
} 
