/**** patchDataStructures.c ***********************************************
 * Name: Daniel Mendez
 * Purpose: Contains the SPECIFICATION and IMPLEMENTATION of FIVE
 *          Data Structures used in the ada.y file. The Data Structures are used 
 *          in order to patch the program counter line numbers resulting from the 
 *          Abstract Machine Instruction output of Ada Loops, Ada Case statements,
 *          Ada if, else if, else statements, and  Ada Exceptions
 *          
 * 
 * 1) Linked List 
 *     - Needed for Ada Loops, Ada Case statements, Ada if, else if, else statements, and Ada Exceptions
 *     - Used to patch the program counter line numbers
 * 
 * 2) Stack Of Linked Lists 
 *     - Needed for Ada Loops, Ada Case statements, and Ada if, else if, else statements
 *     - Used to know which program counter line numbers to patch
 * 
 * 3) Stack of Linked Lists 
 *     - Needed for Ada Exceptions
 *     - Used to know which program counter line numbers to patch
 * 
 * 4) Stack of ints
 *     - Needed for Ada Case Statements
 *     - Used to remember the register number that holds the value of the expression in a case statement
 *     - Example: "20: r3 := contents b, 8"   <-- 3 is the register number in this case
 * 
 * 5) Linked List 
 *     - Needed for Ada When Statements with single or multiple expressions
 *     - Used to know which program counter line numbers to patch
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef PATCHDATASTRUCTURES
#define PATCHDATASTRUCTURES

/*********************** 1) LINKED LIST **********************************************/
// Needed for Ada Loops, Ada Case statements, Ada if, else if, else statements, and Ada Exceptions

    // PatchList
    typedef struct  listNode {
        struct listNode *next;
        int patchLine;    // Program Counter Line Number that needs patching
        int jumpNumber;   // Program Counter Line Number to jump to
    } *ListNodePtr;

    ListNodePtr allocateMemory(int lineToPatch, int numberToJump);
    ListNodePtr appendToList(ListNodePtr listHead, int lineToPatch, int numberToJump);
    void printAllNodes(ListNodePtr list);
    void sortLinkedList(ListNodePtr listHead);




ListNodePtr allocateMemory(int lineToPatch, int numberToJump)
/***********************************************
Return a pointer to the newly allocated node
************************************************/
{
    ListNodePtr new_node;
    new_node = (ListNodePtr) malloc(sizeof(ListNodePtr));
    new_node->patchLine = lineToPatch;
    new_node->jumpNumber = numberToJump;
    new_node->next = NULL;
    return new_node;
}


ListNodePtr appendToList(ListNodePtr listHead, int lineToPatch, int numberToJump)
/***********************************************
Adding a new node to the front of the list.
************************************************/
{
    
    ListNodePtr newHead = allocateMemory(lineToPatch, numberToJump); 
    newHead->next = listHead;
    return newHead;

} //end of addToList


void printAllNodes(ListNodePtr list)
/***********************************************
Prints the name field of each struct in the List 
************************************************/
{
    ListNodePtr current = list;
    
    if (current == NULL)
        printf("Your list is currently empty\n\n");
    
    else 
        while (current != NULL) {
            printf("(PatchLine: %d, JumpNumber: %d)\n", current->patchLine, current->jumpNumber);
            current = current -> next;
        }
}


void swap(ListNodePtr a, ListNodePtr b) 
/***********************************************
 Replace the contents of a node with another node
 NOTE: I MODIFIED THIS EXISTING FUNCTION TO FIT MY NEEDS,
       LOOK AT README.md FILE
************************************************/
{ 
    int temp = a->patchLine;
    int temp2 = a->jumpNumber;
    
    a->patchLine = b->patchLine;
    a->jumpNumber = b->jumpNumber;
    
    b->patchLine = temp; 
    b->jumpNumber = temp2;
} 


void bubbleSort(ListNodePtr start)
/***********************************************
 Sorts a single linked list into increasing order
 NOTE: I MODIFIED THIS EXISTING FUNCTION TO FIT MY NEEDS,
       LOOK AT README.md FILE
************************************************/
{
    int swapped, i; 
    ListNodePtr ptr1; 
    ListNodePtr lptr = NULL; 
  
    /* Checking for empty list */
    if (start == NULL) 
        return; 
  
    do
    { 
        swapped = 0; 
        ptr1 = start; 
  
        while (ptr1->next != lptr) 
        { 
            if (ptr1->patchLine > ptr1->next->patchLine) 
            {  
                swap(ptr1, ptr1->next); 
                swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
}



/******************** 2) STACK OF LINKED LISTS ************************************************/
// Needed for Ada Loops, Ada Case statements, and Ada if, else if, else statements

int patchTopIndex = -1;
int PATCHMAXIMUM = 100;


    // Stack to Patch
    typedef struct listElement {
        struct listNode* leaveAddressPtr; //Refers to the front of the linked list
        int registerNumber; //Garbage value initially
    } ListELEM;

    
    int stackIsFull();
    int stackIsEmpty();
    int topIndex();
    void pushList(ListELEM stack[]);
    void popList(ListELEM stack[]);
    void putInToList(ListELEM stack[], int lineToPatch);


int stackIsFull() { return patchTopIndex == (PATCHMAXIMUM-1); }

int stackIsEmpty() { return patchTopIndex == -1; }

void pushList(ListELEM stack[])
{
    if (stackIsFull()) {
        printf("StackOfLists is FULL. Unable to push new List");
    }
    else {
        patchTopIndex++;
        stack[patchTopIndex].leaveAddressPtr = NULL;
    }
}


void popList(ListELEM stack[])
{
    if (stackIsEmpty()) {
        printf("Stack of Lists is EMPTY. Cannot pop.\n\n\n");
    }
    else {
        stack[patchTopIndex].leaveAddressPtr = NULL;
        patchTopIndex--;
    }
}


void putInToList(ListELEM stack[], int lineToPatch)
{
    if (stackIsEmpty()) {
        printf("EMPTY stack of lists. Cannot add symbol");
    }
    //Do not need to handle duplicate numbers because pc number is always different
    else {
        ListNodePtr head = stack[patchTopIndex].leaveAddressPtr;
        stack[patchTopIndex].leaveAddressPtr = appendToList(head, lineToPatch, -1);
    }
    
}






/******************** 3) STACK OF LINKED LISTS ************************************************/
//Needed for Ada Exceptions

int excepTopIndex = -1;
int EXCEPTIONMAXIMUM = 100;


    // Stack to Patch the exceptions in Ada
    typedef struct exceplistElement {
        struct listNode* leaveAddressPtr; //Refers to the front of the linked list
    } ExceptionListELEM;

    
    int excepStackIsFull();
    int excepStackIsEmpty();
    void excepPushList(ExceptionListELEM stack[]);
    void excepPopList(ExceptionListELEM stack[]);
    void excepPutInToList(ExceptionListELEM stack[], int lineToPatch);


int excepStackIsFull() { return excepTopIndex == (EXCEPTIONMAXIMUM-1); }

int excepStackIsEmpty() { return excepTopIndex == -1; }

void excepPushList(ExceptionListELEM stack[])
{
    if (excepStackIsFull()) {
        printf("\nStack of Exception Lists is FULL. Unable to push new exception List.\n");
    }
    else {
        excepTopIndex++;
        stack[excepTopIndex].leaveAddressPtr = NULL;
    }
}


void excepPopList(ExceptionListELEM stack[])
{
    if (excepStackIsEmpty()) {
        printf("\nStack of Exception Lists is EMPTY. Cannot pop.\n\n\n");
    }
    else {
        stack[excepTopIndex].leaveAddressPtr = NULL;
        excepTopIndex--;
        //printf("%d\n", excepTopIndex);
    }
}


void excepPutInToList(ExceptionListELEM stack[], int lineToPatch)
{
    if (excepStackIsEmpty()) {
        printf("\nEMPTY Stack of Exception Lists. No exception list to put into.\n");
    }
    //Do not need to handle duplicate numbers because program counter number is always different
    else {
        ListNodePtr head = stack[excepTopIndex].leaveAddressPtr;
        stack[excepTopIndex].leaveAddressPtr = appendToList(head, lineToPatch, -1);
    }
}






/******************** 4) STACK OF INTS ************************************************/
//Needed for Ada Case Statements


int regTopIndex = -1;
int REGISTERMAXIMUM = 100;


    typedef struct  registerStack {
        int registerNumber;   // Number to patch
    } RegisterStack;

    int regStackIsFull();
    int regStackIsEmpty();
    void pushRegNum(RegisterStack stack[], int current);
    void popRegNum(RegisterStack stack[]);


int regStackIsFull() { return regTopIndex == (REGISTERMAXIMUM-1); }

int regStackIsEmpty() { return regTopIndex == -1; }

void pushRegNum(RegisterStack stack[], int current)
{
    if (regStackIsFull()) 
        printf("StackOfLists is FULL. Unable to push new List");
    
    else {
        regTopIndex++;
        stack[regTopIndex].registerNumber = current;
    }
}

void popRegNum(RegisterStack stack[])
{
    if (regStackIsEmpty()) 
        printf("Stack of Lists is EMPTY. Cannot pop.\n\n\n");
    
    else 
        regTopIndex--;
}






/*********************** 5) LINKED LIST ************************************************/
//Needed for Ada When Statements with single or multiple expressions

    typedef struct  numListNode {
        int value;   // Number to compare
        struct numListNode* next;
    } *NumListNodePtr;


    //Specification
    NumListNodePtr initNumNode(int expressionValue);
    NumListNodePtr addNumToList(NumListNodePtr listHead, NumListNodePtr oldHead);
    int sizeOfList(NumListNodePtr listHead);
    void printNumList(NumListNodePtr list);



NumListNodePtr initNumNode(int expressionValue)
/***********************************************
Return a pointer to the newly allocated node
************************************************/
{
    NumListNodePtr new_node;
    new_node = (NumListNodePtr) malloc(sizeof(struct numListNode));
    new_node->value = expressionValue;
    new_node->next = NULL;
    return new_node;
    
}

NumListNodePtr addNumToList(NumListNodePtr listHead, NumListNodePtr oldHead) 
/***********************************************
Connect the end of a list to the beginning of 
another list. Returns a pointer to this connected
list which is now a single list
************************************************/
{
    //Create a new node 
    NumListNodePtr newHead = listHead;
    newHead->next = oldHead;
    return newHead;

}

int sizeOfList(NumListNodePtr listHead) 
/***********************************************
Returns the number of nodes in a list
************************************************/
{
    
    int counter = 0;
    NumListNodePtr temp = listHead;
    while (temp != NULL) {
        counter++;
        temp = temp->next;
    }
    return counter;

}

void printNumList(NumListNodePtr list)
/***********************************************
* Prints out the program counter line numbers
* that need to be patched
* Example "10: pc := ?\n" 
* in this case "10" will be printed out
************************************************/
{
    NumListNodePtr current = list;
    if (current == NULL)
        printf("Your list is currently empty\n\n");
    
    else 
        while (current != NULL) {
            printf("%d ", current->value);
            current = current -> next;
        }    
}


#endif

/*
// Need to test stack Of Linked Lists
int main(){
    ;
}
*/
