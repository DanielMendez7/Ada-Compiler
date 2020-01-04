/**** record.c ***********************************************
 * Name: Daniel Mendez
 * Purpose: Contains the SPECIFICATION and IMPLEMENTATION of FOUR
 *          Data Structures used in the ada.y file. The Data Structures
 *          are needed in order to display the abstract machine instructions 
 *          output that result from the productions of the Ada grammar
 * 
 * 1) Struct
 *     - Used to "carry up" information from one production to another
 *       production regarding a local-variable, global variable or a 
 *       literal (i.e. literals can result from an expression as well)
 *     - local/global variable types are:
 *       integer, boolean, array of type boolean/integer and record types
 *     - Literals can be of type integer or boolean
 * 
 * 2) Linked List of Structs
 *     - Used to "carry up" information from one production to another 
 *       production regarding the parameters in an Ada read, Ada write,
 *       Ada array Ada procedure and Ada record with an array member variable
 * 
 * 3) Linked List
 *     - Used to "carry up" information from one production to another 
 *       production regarding the member variables of an Ada record, and
 *       the total amount of space an instance of an Ada record takes up.
 *     - Ada record can handle the following member variable types:
 *       integer, boolean, array of type boolean/integer and record types
 * 
 * 4) Struct
 *     - Needs to be global so that I may use it throughout the ada.y file
 *     - Used to refer to the current registerNumber, program counter line number,
 *       exception number, and the current offset of a variable in a procedure 
*****************************************************************/
#include <stdbool.h>
#include "binaryTree.h"






/*********************** 1) STRUCT **********************************************/
#ifndef RECORDS
#define RECORDS

//WARNING: This is already defined in binaryTree.h
//         The order you #include your files will matter
//         Make sure to #include binaryTree.h first then record.c
//enum typeOfVariable {not_declarable=-1, integer=0, boolean=1, array=2, record=3};

typedef struct Record {
    int offset;          // Offset of local variable from current base of AR  Ex: 4 + 0 means its first variable in procedure
    int registerNumber;  // Ex. r1, r2, r3, r4
    bool isRegister;     // Check if its a register
    bool isMemAddress;   // Check if its a memAddress
    enum typeOfVariable variableType;   // Need to check if read is a read_integer or read_boolean

    //Only used for an array on the right hand side of an assignment
    //Need it to handle expressions inside of arrays!!!
    int phantomOffSet;


    //This is to handle Ada records for Part 5
    char variableName[15];
    enum typeOfNode kind;
    

} *recordptr;


recordptr createRecord();


recordptr createRecord()
/***********************************************
Returns a pointer to a new record
Can either have a literal, local variable or non-local variable
************************************************/
{
    recordptr new_record;
    new_record = (recordptr) malloc(sizeof(struct Record));
    //Must have these
    new_record->offset = 0;              //Only local and non-local variables get an offset
    new_record->registerNumber = 0;      //Only non-local and literals get a register number
    new_record->isRegister = false;      //(false for local variables), (true for literals and non-local variables)
    new_record->isMemAddress = false;    // (false for literals),  (true for local variables and non-local variables)
    new_record->variableType = not_declarable;  // Need to check if read is a read_integer or read_boolean

    new_record->phantomOffSet = -1;      //Need this to keep track of the left hand side index of an array Ex. a(3);

    //new_record->variableName //Null initially
    new_record->kind = garbage; // enum is -1

    
    return new_record;
}

#endif






/*********************** 2) LINKED LIST OF STRUCTS **********************************************/

#ifndef LINKEDLISTOFRECORDS
#define LINKEDLISTOFRECORDS

typedef struct RecordNode {
    struct Record* record;    // A pointer to the actual record itself
    struct RecordNode* next;  // A pointer to a node that contains a record and a next pointer
} *RecordNodePtr;



// NOTE: If want to create an empty record then will need to
//       make a function that will allocate space for that record
//       But for now I just want to connect existing record together!

RecordNodePtr createRecordNode(recordptr ptrToRecord);
RecordNodePtr addToRecordList(RecordNodePtr newHead, RecordNodePtr currentHead);


RecordNodePtr createRecordNode(recordptr ptrToRecord)
/***********************************************
Return a pointer to the newly allocated Record Node
************************************************/   
{

    RecordNodePtr new_node;
    new_node = (RecordNodePtr) malloc(sizeof(struct RecordNode));

    new_node->record = ptrToRecord; //(recordptr) malloc(sizeof(struct Record));
    new_node->next = NULL;


    return new_node;
}

RecordNodePtr addToRecordList(RecordNodePtr newHead, RecordNodePtr currentHead)
/***********************************************
Adding a new Record Node to the front of the list.
************************************************/
{
    // Memory safety guard
    if (newHead != NULL) 
        newHead->next = currentHead;
    else
        printf("newHead dummy parameter in addToRecordList function was already NULL! Check record.c file");
    
    return newHead;
}

#endif






/*********************** 3) LINKED LIST **********************************************/
//THIS IS FOR HANDLING Ada records

#ifndef LINKEDLISTOFRECORDSVERSIONTWO
#define LINKEDLISTOFRECORDSVERSIONTWO

typedef struct RecordList {
    //MUST HAVE! This is to handle records in ada for Part 5
    char variableName[15];
    int offset;          // Offset of local variable from current base of AR  Ex: 4 + 0 means its first variable in procedure
    int memSpace;
    enum typeOfNode kind;
    struct RecordList* next;


    //NEED FOR SPECIAL CASES
    //Only used for an array on the right hand side of an assignment
    //Need it to handle expressions inside of arrays!!!
    int phantomOffSet;
    enum typeOfVariable variableType;   // Need to check if read is a read_integer or read_boolean
    

    //MAY NOT NEED
    struct node* parent_type;
    struct node* component_type;
    

} *RecordListPtr;



RecordListPtr initializeRecord(char nameOfVariable[]);
RecordListPtr combineRecordLists(RecordListPtr firstListHead, RecordListPtr secondListHead);
int returnMemSpace(RecordListPtr listHead);
void printSubVariables(RecordListPtr listHead);
//RecordListPtr searchRecordVariable(RecordListPtr listHead, char* targetVariable); //May not need



RecordListPtr initializeRecord(char nameOfVariable[])
/***********************************************
Returns a pointer to a new record
Can either have a literal, local variable or non-local variable
************************************************/
{
    RecordListPtr new_record;
    new_record = (RecordListPtr) malloc(sizeof(struct RecordList));

    //This is to handle records in ada for Part 5
    strcpy(new_record->variableName, nameOfVariable); //Null initially
    new_record->offset = 0;
    new_record->memSpace = 0;
    new_record->kind = garbage; // enum is -1
    new_record->next = NULL;

    
    //NEED FOR SPECIAL CASES
    new_record->phantomOffSet = -1; //Need this to keep track of the left hand side index of an array Ex. a(3);
    new_record->variableType = not_declarable;  // Need to check if read is a read_integer or read_boolean

    
    //MAY NOT NEED
    new_record->parent_type = NULL;    
    new_record->component_type = NULL; 

    
    return new_record;
}



RecordListPtr combineRecordLists(RecordListPtr firstListHead, RecordListPtr secondListHead)
/***********************************************
Combine two record lists together
************************************************/
{
    RecordListPtr temporaryPtr = firstListHead;

    //If first List has zero items
    if (temporaryPtr == NULL)
        firstListHead = secondListHead;
    
    //If first List has one item
    else if (temporaryPtr->next == NULL) 
        temporaryPtr->next = secondListHead;
    
    //If first List has multiple items
    else {
        while (temporaryPtr->next != NULL) { //Ensures you point to the very last node in the list
            temporaryPtr = temporaryPtr->next;
        }

         //Connect the end of the first list with the head of the second list
        temporaryPtr->next = secondListHead;
    }

    temporaryPtr = NULL; //Prevents dangling pointers
    
    return firstListHead; //Returns the head of the list
}



int returnMemSpace(RecordListPtr listHead)
/***********************************************
Return the total amount of space occupied by
the record which includes variable types such
as integer (1), boolean(1), 
array(size of array * space occupied by elements)
record (size of each individual variable added up) 
************************************************/
{
    int totalMemSpace = 0;

    //Add up memory space occupied by each variable declared in the record
    while (listHead != NULL) {
        totalMemSpace += listHead->memSpace;
        listHead = listHead->next;
    }

    return totalMemSpace;
}


void printSubVariables(RecordListPtr listHead)
/***********************************************
Prints out all the subVariables in an Ada Record type
************************************************/
{
    RecordListPtr traverseList = listHead;
    while (traverseList != NULL) {
        printf("%s, ", traverseList->variableName);

        traverseList = traverseList->next;
    }
    printf("\n");
    
}


/*
RecordListPtr searchRecordVariable(RecordListPtr listHead, char targetVariable []);
***********************************************
Returns a pointer to the variable of an 
Ada record 
************************************************
{
    RecordListPtr traverseList = listHead;
    while(traverseList != NULL) {
        if (strcmp(traverseList->variableName, targetVariable) == 0) {
            break; //Found record associated with targetVariable so return this record pointer
        }
        
        traverseList = traverseList->next;
    }

    //Could not find record associated with variable so return NULL
    //target variable is not a part of the Ada record variable field
    if (traverseList == NULL)
        return NULL;

    //Found variable of Ada record 
    return traverseList->record;
}
*/
#endif






/*********************** 4) STRUCT **********************************************/

#ifndef GLOBALRECORD
#define GLOBALRECORD

struct GlobalRecord {
    int pc;               //Abstract Machine Instruction Line 0: 1: 2: 3: 4:
    int offset;           //global offset to keep track of contents b, _ 
    int registerNumber;   //To know which register your currently handling

    //Need for exceptions
    int exceptionNumber;
    
};



int currentTop = 0;
int LIMITSIZE = 200;
int stackOffSet[200] = {0};

int atCapacity() { return currentTop == (LIMITSIZE-1); }

int isVacant() { return currentTop == -1; }

int returnOffSet(int stack[]) { return stack[currentTop]; }


void raiseOffSet(int stack[], int sizeOfVariable)
{
    int currentOffset = stack[currentTop];
    stack[currentTop] = currentOffset + sizeOfVariable;
}


void pushOffSet(int stack[])
{
    if (atCapacity()) {
        printf("StackOffSet is FULL. Unable to push new offset");
    }
    else {
        currentTop++;
        stack[currentTop] = 4;
    }
}

void popOffSet(int stack[])
{
    if (isVacant()){
        printf("StackOffSet is EMPTY. Cannot pop offset.\n");
    }
    else{
        stack[currentTop] = 0;
        currentTop--;
    }
        
}

#endif
