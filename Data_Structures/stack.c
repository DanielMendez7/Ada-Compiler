/**** stack.c ***********************************************
 * Name: Daniel Mendez
 * Date Created: 10/09/2019
 * Purpose: Definition of functions for a Stack data structure 
************************************************************/

#include "stack.h"


int isFull() 
/***********************************************
Stack is full when top is equal to the last index 
in the array of Binary Trees
************************************************/
{
    return top == (MAXSIZE-1);
}


int isEmpty() 
/***********************************************
Stack is empty when top is equal to -1 
************************************************/
{
    return top == -1;
}


void push(TreeELEM stack[], char treeName[])
/***********************************************
Pushes a new empty binary tree onto the stack
NOTE: Each Binary Tree is associated with a newly 
      declared Ada procedure that may or may not 
      contain parameters
************************************************/
{
    if (isFull()) {
        printf("Stack is FULL. Unable to push new Binary Tree.");
    }
    else{
        top++;
        strcpy(stack[top].name, treeName);
        stack[top].rootPointer = NULL;
            printf("\nPushing new scope for %s\n", treeName);
    }
}


void pop(TreeELEM stack[])
/***********************************************
Pops a binary tree off of the stack
NOTE: I did NOT free the dynamically allocated 
      memory (i.e. the nodes of the Binary Tree).
      The nodes of the popped Binary Tree may
      contain the parameters of an Ada procedure. 
      Therefore, these nodes must remain in memory 
      in order to reference them later in the program
************************************************/
{
    if (isEmpty()) 
        printf("Stack is EMPTY. Cannot pop.\n\n\n");
    
    else { 
        stack[top].rootPointer = NULL;
        printf("Binary Tree at index  with name \"%s\" popped off Stack\n\n\n", stack[top--].name);
    }
}


void add(TreeELEM stack[], int val, char nodeString[])
/***********************************************
Add a new node with the given string to the binary tree 
that is located at the top of the stack.
Else if string is already at that Binary Tree 
(i.e. duplicate), then do NOT add
************************************************/
{

    //Adding symbol to binary tree at the top of stack
    if (isEmpty())
        printf("EMPTY stack of binary trees. Cannot add symbol");
    else {
        if (localSearch(stack[top].rootPointer, nodeString) == NULL)
            stack[top].rootPointer = insert(stack[top].rootPointer, val, nodeString);       
        else    //Duplicate, so do not insert symbol into binary tree 
            printf("String, \"%s\" is already in the topMost binary tree.\n", nodeString);
      
    }

    //Prints current nodes in the topmost binary tree
    //printf("In order traversal of Binary Tree \"%s\"\n", stack[top].name);
    //printDFS(stack[top].rootPointer);
}


Node* localSearch(Node* binaryTreeRoot, char targetString [])
/***********************************************
Search for a string in a single Binary Tree on the
Stack of Binary Trees. If found then return a 
pointer to the node that contains that string. 
Else return NULL
************************************************/
{
    Node* subRoot = binaryTreeRoot;

    //Search for target string until the root reaches NULL
    while(subRoot != NULL) {  
        if (strcmp(targetString, subRoot->symbol) < 0) {
            subRoot = subRoot -> left;
        }
        else if (strcmp(targetString, subRoot->symbol) > 0) {
            subRoot = subRoot -> right;
        }
        else {   //The string being searched is found!
            return subRoot;
        }
    }
    return NULL; //The string being searched is not found
}



Node* globalSearch(TreeELEM stack[], char targetString [])
/**********************************************
Search for a string in the Stack of Binary Trees
starting from the topmost Binary Tree on the Stack
and moving downwards on the Stack. If string is 
found then return a pointer to the node that 
contains that string. Else return NULL
************************************************/
{
    Node* targetNode = NULL;
    for (int i=top; i>=0; i--) {
        targetNode = localSearch(stack[i].rootPointer, targetString);
            if (targetNode != NULL){
                //printf("\nString \"%s\" FOUND!\nNumber of searched trees: %d\nFound in Binary Tree with Name: \"%s\"\n\n\n",
                //targetNode->symbol, searchCount, stack[i].name);
               break;
            }
    }

            
    //Symbol is not found so display eror message to user
    if (targetNode == NULL){
        printf("The string \"%s\" is NOT found on any tree in the stack.\n\n\n", targetString);
    }
    return targetNode;
}



void quit()
/***********************************************
Quits the whole program
NOTE: May have to free all allocated memory on the
      heap before termination of program.
************************************************/
{
    exit(1);
}



char* returnKind(Node* currentNode)
/***********************************************
Returns the kind of a node in a given binary tree
************************************************/
{
    switch (currentNode->kind)
    {
    case -1:
        return "garbage";
        break;
    case 0:
        return "parameter";
        break;
    case 1:
        return "predefined";
        break;
    case 2:
        return "procedure";
        break;
    case 3:
        return "variable";
        break;
    case 4: //type
        return "type";
        break;
    case 5: //value
        return "value";
        break;
    case 6: //exception
        if (!strcmp(currentNode->symbol, "constraint_error"))
            return "exception";
        else if (!strcmp(currentNode->symbol, "numeric_error"))
            return "exception";
        break;
    case 7: //read_routine
        return "read_routine";
        break;
    case 8: //write_routine
        return "write_routine";
        break;
    case 9: //array_type
        return "array_type";
        break;
    case 10: //record_type
        return "record_type";
        break;
    }
    
    printf("There is a runtime error. Look inside your returnKind function");
    return "";
}



int countGlobalSearch(TreeELEM stack[], char targetString [])
/***********************************************
Searches for the desired string in the stack of
binary trees. Starts at the top of the stack and 
goes towards the bottom of the stack. If string
is found on the topmost binary tree on the stack 
then return 0 else return the number of binary 
trees searched minus one. 
************************************************/
{
    Node* targetNode = NULL;
    int searchCount = 0;
    for (int i=top; i>=0; i--) {
        targetNode = localSearch(stack[i].rootPointer, targetString);
            if (targetNode != NULL){
                //printf("\nString \"%s\" FOUND!\nNumber of searched trees: %d\nFound in Binary Tree with Name: \"%s\"\n\n\n",
                //targetNode->symbol, searchCount, stack[i].name);
               break;
            }
            searchCount++;
    }

            
    //Symbol is not found so display eror message to user
    if (targetNode == NULL){
        printf("The string \"%s\" is NOT found on any tree in the stack.\n\n\n", targetString);
    }
    return searchCount;
}
