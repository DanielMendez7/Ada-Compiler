/***************************** arrRecNest.ada works! Moving onto doing procedures with formal parameters 12_10_19 *********************/

%{
int yylex();
int yyerror(char*);
#include <stdio.h>
#include <string.h>
 
int MAXSIZE = 20;
int top = -1;

#include "listOfStructs.c" 
#include "stack.c"
#include "binaryTree.c"
#include "record.c"
#include "stackOfLinkedLists.c"
 
//GLOBAL VARIABLES 
TreeELEM stackOfTrees[20];
struct GlobalRecord globalRecord;
 
//Need both of these for if statements and loops
ListELEM stackOfLL[300]; //toPatch is a stack of Linked Lists //Handles loops and leave addresses for if statements
//ListELEM stackOfCondJumps[300]; // Handles cond jumps for if statements
ListNodePtr patchList;   // Patch List


 
FILE *output;      //Write to file so you can test output code with AMI
extern int lineno; //Line number here is the instruction for part 3
%}

%token IS BEG END PROCEDURE ID NUMBER TYPE ARRAY RAISE OTHERS
%token RECORD IN OUT RANGE CONSTANT ASSIGN EXCEPTION NULLWORD LOOP IF
%token THEN ELSEIF ELSE EXIT WHEN AND OR EQ NEQ LT GT GTE LTE TICK
%token NOT EXP ARROW OF DOTDOT ENDIF ENDREC ENDLOOP EXITWHEN

%type <integer>          NUMBER   constant    declarative_part    declarative_part_prime  main_begin   procedure_begin    loop_start   else_if_start   else_start   if_start   optional_else_if   else_if_section    else_if_stmt   optional_else   initial 
%type <var>              ID   type_name   mode   IN   OUT    adding_operation   multiplying_operation   relational_operation  boolean_operation  //name 
%type <listPointer>      identifier_list 
%type <nodePtr>          parameters   formal_parameter_part   procedure_specification    procedure_body_prime
%type <ptrToRecord>      primary   factor   term   simple_expression   relation   expression   condition   optional_assign   optional_array 
%type <ptrToRecordNode>  expression_list   optional_parameters   nested_record //If you get a segfault its probably from this data structure
%type <adaRecordsInfo>   record_object   component_list          //If you get a segfault its probably from this data structure

%union {
    int integer;
    char *var;
    struct idnode* listPointer;//pointer for the list of Ids
    struct node* nodePtr;
    struct Record* ptrToRecord;
    struct RecordNode* ptrToRecordNode; //Used to handle read and write with multiple expression lists
    struct RecordList* adaRecordsInfo;  //Used to handle Ada record types
}
%%

program                 : main_body                                       {
                                                                           printf ("\n*******\nDONE.\n*******\n");
                                                                          }
                        ;

main_body               : main_specification IS
                          declarative_part main_begin
                          sequence_of_statements
                          exception_part END ';'                          {
                                                                           //POP: Procedure if finished so don't need this Binary Tree anymore
                                                                           printf("\nPopping scope for main, so print tree\n");
                                                                           printDFS(stackOfTrees[top].rootPointer);
                                                                           pop(stackOfTrees); 

                                                                           //EPILOGUE for the main procedure
                                                                           //1)get return adress 2)get dynamic link and 3)update pc count
                                                                           fprintf(output, "%d: r%d := contents b, 1\n", globalRecord.pc++, globalRecord.registerNumber);
                                                                           fprintf(output, "%d: b := contents b, 3\n", globalRecord.pc++);
                                                                           fprintf(output, "%d: pc := r%d\n", globalRecord.pc++, globalRecord.registerNumber++);
                                                                           
                                                                           

                                                                           
                                                                           //NEW (MAIN PATCHLIST) update Patch List by including the pc count here
                                                                           ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                                                           
                                                                           // returnOffSet  gives size of main (i.e. 4 bookeeping plus any declared variables)
                                                                           // $4            is the pc line number when you see the keyword begin
                                                                           // gR.pc         is the start of mains AR (i.e. the pc number after the last AMI that currently prints out)
                                                                           
                                                                           fprintf(output, "******** MAIN SIZE: %d,  BEGIN SEQUENCE OF STATEMENTS AT: %d,  MAINS AR: %d ********\n",
                                                                                   returnOffSet(stackOffSet), $4, globalRecord.pc);
                                                                           
                                                                           
                                                                           
                                                                           //Order of these lines of code MATTERS because linked list was inserting into the FRONT
                                                                           //Ex. Patchline: 4, JumpNumber: 6
                                                                           patchList = appendToList(patchList, tempHead->patchLine, $4);
                                                                           tempHead = tempHead->next;
                                                                           
                                                                           //Ex. PatchLine: 1, JumpNumber: 32
                                                                           patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc + returnOffSet(stackOffSet)); 
                                                                           tempHead = tempHead->next;
                                                                           
                                                                           //Ex. PatchLine: 0, JumpNumber: 26
                                                                           patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc);
                                                                           tempHead = tempHead->next; //tempHead should be NULL after this line

                                                                           //Print out the ENITRE patch List from this whole program
                                                                           printf("Here is the updated patch list for main after its completely executed: \n");
                                                                           printAllNodes(patchList);

                                                                           popList(stackOfLL);     //Pop mains toPatch linked list
                                                                           popOffSet(stackOffSet); //POP: Procedure is finished so don't need this offset anymore
                                                                           
                                                                           
                                                                          } //Want to pop here because we're at the end of a statement 
                        ;

main_begin              : BEG       { $$ = globalRecord.pc; }               //START of Main Program (i.e pc line number when you see the keyword "begin");
                        ;

main_specification      : PROCEDURE ID                                    {
    
                                                                           push(stackOfTrees, $2);  //PUSH new binaryTree onto stack
                                                                           pushOffSet(stackOffSet); //PUSH new offset onto stack because of new procedure
                                                                           pushList(stackOfLL);     //NEW (MAIN PATCH) PUSH new linkedList of patches onto stack

                                                                           
                                                                           //ABSTRACT MACHINE INSTRUCTIONS
                                                                           //Order of putInToList matters! Linked List inserts to front
                                                                           putInToList(stackOfLL, globalRecord.pc); //NEW (MAIN PATCH) Need to patch this instruction line number
                                                                           fprintf(output, "%d: b := ?\n", globalRecord.pc++);

                                                                           putInToList(stackOfLL, globalRecord.pc); //NEW (MAIN PATCH) Need to patch this instruction line number
                                                                           fprintf(output, "%d: contents b, 0 := ?\n", globalRecord.pc++);
                                                                           fprintf(output, "%d: contents b, 1 := ?\n", globalRecord.pc++);

                                                                           putInToList(stackOfLL, globalRecord.pc); //NEW (MAIN PATCH) Need to patch this instruction line number
                                                                           fprintf(output, "%d: pc := ?\n", globalRecord.pc++);
                                                                           fprintf(output, "%d: halt\n", globalRecord.pc++);

                                                                           fprintf(output, "******* End of Prologue for Main ******\n");

                                                                          }
                        ;

procedure_body          : procedure_body_prime IS                         
                          declarative_part procedure_begin
                          sequence_of_statements
                          exception_part END ';'                          {
                                                                           struct node* ptrToProcedureNode = $1;

                                                                           //After all the declarations, this procedure has a pc line number at the keyword "begin"
                                                                           ptrToProcedureNode->procStart = $4;

                                                                           
                                                                           //POP: Procedure is finished so don't need this Binary Tree anymore
                                                                           printf("\nPopping scope for %s, so print tree\n", ptrToProcedureNode->symbol);
                                                                           printDFS(stackOfTrees[top].rootPointer);
                                                                           pop(stackOfTrees);  

                                                                           //NEED For AMI to calculate size of procedure //i.e. $3 is 4 bookeeping plus any other variables
                                                                           ptrToProcedureNode->offset = $3;  //REPLACED


                                                                           //TODO: Get actuals addr and copy formal parameter addres to a
                                                                           fprintf(output, "Check procedure_body production. Get actual addr and copy x's value to a\n");
                                                                           
                                                                           
                                                                           //EPLIOGUE for procedures in main 
                                                                           //1)get return adress 2)get dynamic link and 3)update pc count
                                                                           fprintf(output, "%d: r%d := contents b, 1\n", globalRecord.pc++, globalRecord.registerNumber);
                                                                           fprintf(output, "%d: b := contents b, 3\n", globalRecord.pc++);
                                                                           fprintf(output, "%d: pc := r%d\n", globalRecord.pc++, globalRecord.registerNumber++);

                                                                           //For printing out the information for the current procedure
                                                                           fprintf(output, "******** END OF PROCEDURE: %s,  SIZE: %d,  BEGIN SEQUENCE OF STATEMENTS AT: %d ********\n",
                                                                                   ptrToProcedureNode->symbol, returnOffSet(stackOffSet), $4);
                                                                           
                                                                           //POP: Procedure is finished so don't need this offset anymore
                                                                           popOffSet(stackOffSet);
                                                                           
                                                                           //Start of next procedures AMI, so print line
                                                                           //fprintf(output, "******** START OF AMI for PROCEDURE *******\n");

                                                                          }
                        ;
 
procedure_begin         : BEG      { $$ = globalRecord.pc; }   //START of procedure program (i.e pc line number when you see the keyword "begin");
                        ;

procedure_body_prime    : procedure_specification formal_parameter_part   {

                                                                           //Updated version accounts for duplicates and connects precedure node to the formal parameters in the next binary tree
                                                                            struct node* treeNodeList = $2;          // treeNodeList is not in the binary tree, its a copy    
                                                                            struct node* ptrToProcedureNode = $1;
                                                                            ptrToProcedureNode->next = treeNodeList; //connect Y1's next pointer to first formal parameter of the copy list//
                                                                            ptrToProcedureNode->kind = procedure;    //kind is a procedure so enum value is 2
                                                                                
                                                                            struct node* currentNode;
                                                                            while (treeNodeList != NULL){
                                                                               
                                                                                //Duplicate Found so don't add to topmost stack
                                                                                if (localSearch(stackOfTrees[top].rootPointer, treeNodeList->symbol) != NULL) { //A
                                                                                    printf("ERROR: Duplicate IDs name: %s, parent_type: %s, component_type: %s was not inserted into the symbol table\n",
                                                                                           treeNodeList->symbol, treeNodeList->parent_type->symbol, treeNodeList->component_type->symbol);

                                                                                }
                                                                                else {
                                                                                add(stackOfTrees, 0, treeNodeList->symbol);
                                                                                currentNode = localSearch(stackOfTrees[top].rootPointer, treeNodeList->symbol);
                                                                                currentNode->mode = (char*) malloc(sizeof(treeNodeList->symbol) + 1);   //allocate space for mode which is of type char* 
                                                                                strcpy(currentNode->mode, treeNodeList->symbol);
                                                                                currentNode->parent_type = treeNodeList->parent_type;
                                                                                currentNode->kind = treeNodeList->kind;        //These are all of kind variable so enum is 3
                                                                                //currentNode->next = treeNodeList->next;      //Don't need since I have the copy of list
                                                                                }

                                                                                treeNodeList = treeNodeList->next;
                                                                                
                                                                            }
                                                                            
                                                                            detachDuplicates(ptrToProcedureNode->next);    //Get rid of any duplicates found in the copy list of Binary Nodes
                                                                            printBTNodesNextDFS(ptrToProcedureNode->next); //Look at what nodes are still inside of your list of nodes
                                                                            
                                                                            $$ = ptrToProcedureNode; //REPLACED
                                                                            ptrToProcedureNode = NULL; //Don't need this pointer to reference the procedure node anymore so make NULL

                                                                            //NOTE: This part replaces the part right above it
                                                                            //Must have to fix pc count in AMI for walk backs
                                                                            //$$ = $1;                   //NEW
                                                                          }
                        ;

procedure_specification : PROCEDURE ID
                                          {
									          add(stackOfTrees, 0, $2); 
									          $$ = localSearch(stackOfTrees[top].rootPointer, $2); 
									          push(stackOfTrees, $2);  //Push new binaryTree onto stack
									          pushOffSet(stackOffSet); //Push new offset onto stack because of new procedure

                                        
                                             //NEED for AMI //Places current pc count into procedure Node in order to jump to it later
                                             struct node* procNodeInTree = globalSearch(stackOfTrees, $2); //REPLACED
                                             //procNodeInTree->procStart = globalRecord.pc;                  //REPLACED
                                             //$$ = procNodeInTree;  //Alternative

                                              //Must have to fix pc count in AMI for walk backs
                                              //$$ = $2;                                                       //NEW

                                          }
                                                                          
                        ;

formal_parameter_part   : '(' parameters ')'                              { $$ = $2; }
                        | %empty                                          { $$ = NULL; }
                        ;

parameters              : identifier_list ':' mode type_name ';' parameters {

                                                                           //SAME EXACT CODE AS THE PREVIOUS PRODUCTION WITH A FEW NEW THiNGS
                                                                           // 1) Make a list to create all the nodes
                                                                           struct idnode* linkedList = $1; //Linked List to traverse
                                                                           struct node* listToPassUp;      //list of binary Nodes to pass up
                                                                           
                                                                           struct node* currentNode = createNode(0, linkedList->name);//currently created node
                                                                           currentNode->mode = (char*) malloc(sizeof($3) + 1);        //allocate space for mode which is of type char* 
                                                                           strcpy(currentNode->mode, $3);
                                                                           currentNode->parent_type = globalSearch(stackOfTrees, $4); //w is the parent_type
                                                                           currentNode->kind = variable;                              //kind is variable, so enum is 3

                                                                           struct node* ptrToLastNode = currentNode;   //Connects the next pointer of the last node to point to the front node of 
                                                                           listToPassUp = currentNode;                                //Now I can have currentNode point to something else
                                                                           linkedList = linkedList->next;                             //if Null then currentNode->next = NULL
                                                                           
                                                                           while (linkedList != NULL){
                                                                               //Have the next of the previous node point to the newly created node
                                                                               currentNode->next = createNode(0, linkedList->name);
                                                                               ptrToLastNode = currentNode->next;                         //will point to the last node of the first half of nodes
                                                                               currentNode = currentNode->next;                           //update pointer of currentNode

                                                                               
                                                                               currentNode->mode = (char*) malloc(sizeof($3) + 1);
                                                                               strcpy(currentNode->mode, $3);
                                                                               currentNode->parent_type = globalSearch(stackOfTrees, $4); //w is the parent_type
                                                                               currentNode->kind = variable;                              //kind is variable, so enum is 3
                                                                               
                                                                               linkedList = linkedList->next;  // Go to the next node in the linked list
                                                                                 
                                                                               }
                                                                           // 2) Connect the end of the current list to the front of $6
                                                                            ptrToLastNode->next = $6;
                                                                            ptrToLastNode = NULL; //This prevents dangling pointers

                                                                            //CAN DELETE ANYTIME
                                                                           //ALTERNATIVE OPTION TO FIND LAST NODE IN THE FIRST HALF OF LIST
                                                                           //Pro: Easier To read the code
                                                                           //Con: Will have a longer runtime because it will have to traverse the list again to find the last node
                                                                           /*struct node* ptrToNextNode = listToPassUp;
                                                                           while(ptrToNextNode != NULL){
                                                                               if (ptrToNextNode->next == NULL)
                                                                                   ptrToNextNode->next = $6;
                                                                               
                                                                           }*/
                                                                           
                                                                           //Print out the current list of binary nodes
                                                                           //printBTNodesNextDFS(listToPassUp);
                                                                           $$ = listToPassUp;
    
                                                                             }
                        | identifier_list ':' mode type_name               {
                                                                           struct idnode* linkedList = $1; //Linked List to traverse
                                                                           struct node* listToPassUp;      //list of binary Nodes to pass up
                                                                           
                                                                           struct node* currentNode = createNode(0, linkedList->name); //currently created node
                                                                           currentNode->mode = (char*) malloc(sizeof($3) + 1);         //allocate space for mode which is of type char* 
                                                                           strcpy(currentNode->mode, $3);
                                                                           currentNode->parent_type = globalSearch(stackOfTrees, $4); //w is the parent_type
                                                                           currentNode->kind = variable;                              //kind is variable, so enum is 3

                                                                           listToPassUp = currentNode;                                //Now I can have currentNode point to something else
                                                                           linkedList = linkedList->next;                             //if Null then currentNode->next = NULL
                                                                           
                                                                           while (linkedList != NULL){
                                                                               //Have the next of the previous node point to the newly created node
                                                                               currentNode->next = createNode(0, linkedList->name);       
                                                                               currentNode = currentNode->next;                           //update pointer of currentNode
                                                                               currentNode->mode = (char*) malloc(sizeof($3) + 1);
                                                                               strcpy(currentNode->mode, $3);
                                                                               currentNode->parent_type = globalSearch(stackOfTrees, $4); //w is the parent_type
                                                                               currentNode->kind = variable;                              //kind is variable, so enum is 3 
                                                                               
                                                                               linkedList = linkedList->next;  // Go to the next node in the linked list
                                                                                 
                                                                               }

                                                                           //Print out the current list of binary nodes
                                                                           //printBTNodesNextDFS(listToPassUp);
                                                                           $$ = listToPassUp;
                                                                           }
                        ;

mode                    : IN       {$$ = "in";}
                        | OUT      {$$ = "out";}
                        | IN OUT   {$$ = "in out";}
                        | %empty   {$$ = "in";}
                        ;

identifier_list         : ID ',' identifier_list	{ $$ = addToList($3, $1); } //NOTE: Might be best to check for duplicates right here at the beginning
                        | ID				        { struct idnode* theList = initialize($1); $$ = theList; } 
                        ;			   

type_name               : ID 				        { $$ = $1; }
                        ;

//TODO: Calculates size of procedure. Might need to change
declarative_part        : objects ';' declarative_part      { $$ = returnOffSet(stackOffSet); } // Ex. a : integer
                        | types ';' declarative_part         { $$ = returnOffSet(stackOffSet); } // Ex. type r1 is record null end record;
                        | exceptions ';' declarative_part   { $$ = returnOffSet(stackOffSet); } // Ex.  
                        | declarative_part_prime            { $$ = $1; }
                        ;

//TODO: Calculates size of procedure. Might need to change
declarative_part_prime  : procedure_body declarative_part_prime    { $$ = returnOffSet(stackOffSet); }
                        | %empty                                   { $$ = returnOffSet(stackOffSet); }
                        ;

types                   : TYPE ID IS ARRAY  '(' constant DOTDOT constant ')' OF type_name  {

    
                                                                                            //Duplicates in the current tree
                                                                                            if (localSearch(stackOfTrees[top].rootPointer, $2) != NULL) {
                                                                                                printf("ERROR: Duplicate IDs\n");
                                                                                            }
                                                                                            else {
                                                                                                //Found variable type in the outer context so insert into topmost binary tree
                                                                                                Node* nodeType  = globalSearch(stackOfTrees, $11);
                                                                                                if (nodeType != NULL) {
                                                                                                    
                                                                                                    //Add the ID (array) to the stack
                                                                                                    add(stackOfTrees, 0, $2);
                                                                                                    Node* first = localSearch(stackOfTrees[top].rootPointer, $2);

                                                                                                    //QUESTION: Do I make the p_t, c_t or both be a pointer to the type_name? 
                                                                                                    first->component_type = nodeType;
                                                                                                    first->kind = type;  //kind is type so enum is 4
                                                                                                    
                                                                                                    //Number of elements in array is $8 - $6
                                                                                                    first->lower = $6;
                                                                                                    first->upper = $8;

                                                                                                    
                                                                                                    //NOTE: Need to calculate memspace of type_name right here
                                                                                                    //      Different cases for:
                                                                                                    //      array of ints or boolean, array of records, array of arrays, etc.
                                                                                                    // first->memSpace = nodeType->memorySpace;
                                                                                                   
                                                                                                    
                                                                                                }
                                                                                                else
                                                                                                    printf("Could not find type %s in the outer context\n", $11);
                                                                                            }


                                                                                            
                                                                                           }

                        | TYPE ID IS RECORD component_list ENDREC
                                                                             {

                                                                                 
                                                                                 //Duplicates in the current tree
                                                                                 if (localSearch(stackOfTrees[top].rootPointer, $2) != NULL) {
                                                                                     printf("ERROR: Duplicate IDs\n");
                                                                                 }
                                                                                 else {
                                                                                     // Dont need to find variable type in the outer context because record is not predefined
                                                                                     // nor does it have a type_name like integer or boolean
                                                                                     add(stackOfTrees, 0, $2);
                                                                                     Node* first = localSearch(stackOfTrees[top].rootPointer, $2);

                                                                                     // Record in Ada does not have a component_type or a parent_type
                                                                                     first->kind = type;          //kind is type so enum is 9

                                                                                     printf("This is printing out in the TYPE ID IS RECORD component_list ENDREC.\n");
                                                                                     printSubVariables($5);
                                                                                     printf("\n");
                                                                                     
                                                                                     first->listOfVariables = $5; // Contains all the variables inside of a record
                                                                                     first->memorySpace = returnMemSpace(first->listOfVariables); //total memory Space occupied by record
 
                                                                                  }
                                                                                 
                                                                             
                                                                             }
                        
                        | TYPE ID IS RANGE constant DOTDOT constant

                        {
                                                       //Duplicates in the current tree
                                                       if (localSearch(stackOfTrees[top].rootPointer, $2) != NULL) {
                                                           printf("ERROR: Duplicate IDs\n");
                                                       }
                                                       else {
                                                           //Found variable type in the outer context so insert into topmost binary tree
                                                           if (globalSearch(stackOfTrees, "integer") != NULL) {
                                                                                                    
                                                                 //Add range (ID) to the stack (example w)
                                                                 add(stackOfTrees, 0, $2);
                                                                 Node* first = localSearch(stackOfTrees[top].rootPointer, $2);

                                                                 //QUESTION: Do I make the p_t, c_t or both be a pointer to the type_name? //ANSWER: Just c_t
                                                                 //QUESTION: Can the range also go from a to z and not just 1 to 10, etc?  //ANSWER: ?
                                                                 first->component_type = globalSearch(stackOfTrees, "integer");
                                                                 first->kind = type;  // kind is type so enum is 4
                                                                 first->lower = $5;
                                                                 first->upper = $7;
                                                           }
                                                       }
                 
                        }
                        ;

component_list          : record_object ';' component_list { $$ = combineRecordLists($1, $3); } // can put record into symbol table but not its individual components
                        | record_object ';'                { $$ = $1; }
                        ;

record_object           : identifier_list ':' type_name
                                                               {
                                                                   //printRoutine($1);
                                                                   printf("\n");
                                                                   idnodeptr traverseList = $1; //List of variables that were declared

                                                                   //Offset, kind, memory space are extra pieces of information that need to be passed up to component_list 
                                                                   RecordListPtr recordListHead = NULL;
                                                                   
                                                                   //Search for the type_name in the outer context (ex. integer or boolean) or in the tree array or record type
                                                                   Node* varNodeType = globalSearch(stackOfTrees, $3);

                                                                   RecordListPtr currentRecord = NULL;

                                                                   //Parent type is found!
                                                                   if (varNodeType != NULL) {
                                                                       
                                                                   //Traverse through the whole list of declared variables of same type
                                                                   //Ex. a, b, c, : integer
                                                                       //For now assume that you dont' have duplicates, but will have to check that at some point
                                                                       while (traverseList != NULL) {

                                                                           //Create the record with all the information needed
                                                                           currentRecord = initializeRecord(traverseList->name);

                                                                           // printf("Found type? %s\n", strcmp(varNodeType->symbol, "integer") == 0 ? "true" : "false");
                                                                           //Used for simple types stored in records (ex. integer or boolean)
                                                                           if (strcmp(varNodeType->symbol, "integer") == 0 ||
                                                                               strcmp(varNodeType->symbol, "boolean") == 0) {
                                                                               
                                                                               //Create the record with all the information needed
                                                                               currentRecord->kind = variable;
                                                                               currentRecord->parent_type = varNodeType;

                                                                               //printf(" In if statement: %s,  %d    \n", currentRecord->variableName, currentRecord->kind);

                                                                               //May need to do a for loop to go to the parent type and get its size
                                                                               //May need to change from offset to memorySpace variable 
                                                                               currentRecord->memSpace = currentRecord->parent_type->memorySpace; //TODO: Changed from offset to memorySpace
                                                                           }

                                                                           //ARRAYS declared inside of RECORDS //FOR PART 2aii
                                                                             else if (varNodeType->component_type != NULL) {
                                                                                 //This is to do the left_hand side of an assignment which is an array variable
                                                                                 currentRecord->kind = array_type;       //kind is array_type variable so enum is 9
                                                                                 currentRecord->parent_type = varNodeType;
                                                                                 
                                                                                 //Find size of array to by multiplying the number of elements with the size of each element
                                                                                 int sizeOfArray = ((currentRecord->parent_type->upper - currentRecord->parent_type->lower) + 1) * currentRecord->parent_type->component_type->memorySpace;

                                                                                 //Need for arrays declared inside of records
                                                                                 currentRecord->memSpace = sizeOfArray; 
                                                                                     
                                                                                 //printf("*** current offset: %d *** \n", returnOffSet(stackOffSet));
                                                                                 
                                                                             }

                                                                           
                                                                           //TODO: records declared inside of records //FOR PART 2bii
                                                   
                                                                           //printSubVariables(newHead);
                                                                           
                                                                           recordListHead = combineRecordLists(recordListHead, currentRecord);
                                                                       
                                                                           traverseList = traverseList->next;
                                                                       }
                                                                   }
                                                                   else printf("VarNodeType is NULL. This is printing out in the record_object production!\n");

                                                                   varNodeType = NULL; // Not using anymore

                                                                   //printSubVariables(recordListHead);
                                                                   
                                                                   $$ = recordListHead;
                                                               } //end of production record_object
                        | NULLWORD         { $$ = NULL; }
                        ;

/*
component               : objects
                        ;
*/

objects                 : identifier_list ':' type_name 		{ 
                                                                 printf("line#:  %d - ", lineno);
                                                                 printRoutine($1);
                                                                 idnodeptr traverseList = $1;
                                                                 printf(": %s\n", $3);


                                                                 while (traverseList != NULL) {
                                                                     
                                                                     //Duplicates in the current tree
                                                                     if (localSearch(stackOfTrees[top].rootPointer, traverseList->name) != NULL) {
                                                                         printf("ERROR: Duplicate IDs\n");
                                                                     }
                                                                     else {
                                                                         Node* varNodeType = globalSearch(stackOfTrees, $3);
                                                                         
                                                                         //Found variable type in stack so insert variable node into topmost binary tree
                                                                         //Example  a : integer or x:boolean in outer context (offset of 1) OR
                                                                         //Example  type w is array(0..2) of integer;   d : w
                                                                         //Example  type R1 is record    first : integer;second : boolean;   end record
                                                                         if (varNodeType != NULL) {
                                                                             //Add the variable to the stack (example a)
                                                                             add(stackOfTrees, 0, traverseList->name);
                                                                             Node* first = localSearch(stackOfTrees[top].rootPointer, traverseList->name);

                                                                             //update variables from node struct
                                                                             first->parent_type = varNodeType;

                                                                             //For a : integer or b : boolean
                                                                             //integer and boolean are in the outer context and do not have a component type
                                                                             if (strcmp(first->parent_type->symbol, "integer") == 0 ||
                                                                                 strcmp(first->parent_type->symbol, "boolean") == 0) {

                                                                                 first->kind = variable;       //kind is variable so enum is 3
                                                                                 
                                                                                 //for read_integer or read_boolean
                                                                                 if (strcmp($3, "integer") == 0)
                                                                                     first->variableType = integer;  //enum of 0
                                                                             
                                                                                 else if (strcmp($3, "boolean") == 0)
                                                                                     first->variableType = boolean;  //enum is 1
                                                                                 //else
                                                                                 //fprintf(output, "Error: check in production object -> identifier_list type_name\n");
                                                                             
                                                                                 //Set outcome->offset equal to the current offset
                                                                                 first->offset = returnOffSet(stackOffSet);
                                                                                 //Increment globalOfsset by first->parent_type->offset
                                                                                 raiseOffSet(stackOffSet, first->parent_type->offset); //integer and boolean offset is 1
                                                                              }

                                                                             
                                                                             //For d : w where w is an array
                                                                             //w will have a component type
                                                                             //TODO: MUST HANDLE records inside of arrays //FOR PART 2aii
                                                                             else if (first->parent_type->component_type != NULL) {
                                                                                 //This is to do the left_hand side of an assignment which is an array variable
                                                                                 first->kind = array_type;       //kind is array_type variable so enum is 9
                                                                                 
                                                                                 //Find the phantom offset of the variable relative to curren AR, if have something like w is array(4..7)
                                                                                 first->offset = returnOffSet(stackOffSet) - first->parent_type->lower;
                                                                                 //printf("**** Name: %s,  Offset: %d ****\n", first->symbol, first->offset);
                                                                                 
                                                                                 //Find size of array to by multiplying the number of elements with the size of each element
                                                                                 int sizeOfArray = ((first->parent_type->upper - first->parent_type->lower) + 1) * first->parent_type->component_type->memorySpace;

                                                                                 //Need for arrays of arrays or array of records or record inside of array
                                                                                 first->memorySpace = sizeOfArray; 
                                                                                     
                                                                                 raiseOffSet(stackOffSet, sizeOfArray);
                                                                                 //printf("*** current offset: %d *** \n", returnOffSet(stackOffSet));
                                                                                 
                                                                             }

                                                                             
                                                                             //For e : y where y is a record
                                                                             //y will NOT have a component type
                                                                             else if (first->parent_type->component_type == NULL) {
                                                                                 
                                                                                 first->kind = record_type;     //kind is record_type variable so enum is 10
                                                                                 
                                                                                 //CHECK:
                                                                                 printSubVariables(varNodeType->listOfVariables);
                                                                                
                                                                                     
                                                                                 first->listOfVariables = varNodeType->listOfVariables;
                                                                                 first->offset = returnOffSet(stackOffSet);

                                                                                 //Records take up a varying amount of memory space
                                                                                 raiseOffSet(stackOffSet, first->parent_type->memorySpace);
                                                                                 
                                                                             }
                                                                             
                                                                         }
                                                                     } //end of else statement
                  
                                                                     traverseList = traverseList->next;
                                                                 }
                                                                 
                                                                 //Can erase anytime you want
                                                                 //(char*) malloc(sizeof($3)+1);
                                                                 //strcpy(first->kind, $3);
                                                                 //printDFS(stackOfTrees[top].rootPointer);
                                                                 
                                                                 } 

                        | identifier_list ':' CONSTANT ASSIGN constant_expression
                        ;

constant                : ID {$$ = 0;}
                        | NUMBER {$$ = $1;}
                        ;

constant_expression     : expression
                        ;

exceptions              : identifier_list ':' EXCEPTION {       //DO NOT add exception to the outer context
                                                                 printf("line#:  %d - ", lineno);
                                                                 printRoutine($1);
                                                                 printf(": exception\n");
                                                                 idnodeptr traverseList = $1;


                                                                 while (traverseList != NULL){
                                                                     
                                                                     //Duplicates in the current tree
                                                                     if (localSearch(stackOfTrees[top].rootPointer, traverseList->name) != NULL) {
                                                                         printf("ERROR: Duplicate IDs\n");
                                                                     }
                                                                     //Exception type is a special type that is not found in outer context
                                                                     else{
                                                                             //Add the variable to the stack (example bad)
                                                                             add(stackOfTrees, 0, traverseList->name);
                                                                             Node* first = localSearch(stackOfTrees[top].rootPointer, traverseList->name);

                                                                             first->kind = exception;   //kind is exception so enum is 6
                                                                             //printf("kind %d\n", (int)first->kind);
                                                                     }
                  
                                                                     traverseList = traverseList->next;
                                                                 }

                                                                 //Can erase anytime you want
                                                                 //(char*) malloc(sizeof($3)+1);
                                                                 //strcpy(first->kind, $3);
                                                                 //printDFS(stackOfTrees[top].rootPointer);
                                                        }
                        ;

sequence_of_statements  : statement_sequence_prime ';' sequence_of_statements
                        | %empty
                        ;


proc_read_write_arrays_assign : ID optional_parameters optional_assign
                                                               {
                                                                  struct node* variableInTree = globalSearch(stackOfTrees, $1);


                                                                  //KIND IS VARIABLE(enum 3):  An assignment statement with integer or boolean on the lefthand side
                                                                  if (variableInTree->kind == variable) {                                                                  
                                                                      int walkBackCount = countGlobalSearch(stackOfTrees, $1);
                                                                
                                                                      //Handles LOCAL variables in the LEFT-HAND side of an ASSIGNMENT
                                                                      if (walkBackCount == 0) {
                                                                          fprintf(output, "%d: contents b, %d := ", globalRecord.pc++, variableInTree->offset);
                                                                      }

                                                                
                                                                      //Handles NON-LOCAL variables in the LEFT_HAND side of an ASSIGNMENT
                                                                      else {
                                                                          struct node* nodeInTree = globalSearch(stackOfTrees, $1);
                                                                          if (nodeInTree != NULL) {

                                                                              //r2 := b
                                                                              fprintf(output, "%d: r%d := b\n", globalRecord.pc++, globalRecord.registerNumber);
                                                                        
                                                                              //Loop updates the register and static link  Ex. r2 := contents r2, 2
                                                                              while (walkBackCount != 0){
                                                                                  fprintf(output, "%d: r%d := contents r%d, 2\n",
                                                                                          globalRecord.pc++, globalRecord.registerNumber, globalRecord.registerNumber);
                                                                                  walkBackCount--;
                                                                              }

                                                                              //Ex. contents r2, 5 := contents b, 4  or contents r3, 5 := contents r2, 6
                                                                              fprintf(output, "%d: contents r%d, %d := ",
                                                                                      globalRecord.pc++, globalRecord.registerNumber++, nodeInTree->offset);
                                                                          }
                                                                          else
                                                                              printf("Error: Check your statement_sequence_prime -> ID ASSIGN expression production");
                                                                      }



                                                                      //For the RIGHT HAND side of an ASSIGNMENT
                                                                      // For global variables (true && true) on right hand side
                                                                      if ($3 != NULL){
                                                                          if ($3->isRegister && $3->isMemAddress)
                                                                              fprintf(output, "contents r%d, %d\n",
                                                                                      $3->registerNumber, ($3->variableType == array)? $3->phantomOffSet : $3->offset);
                                                                          
                                                                          // For local variables (false && true) on right hand side
                                                                          else if (!$3->isRegister && $3->isMemAddress) {
                                                                              if ($3->variableType == array)
                                                                                  fprintf(output, "contents b, r%d, %d\n", $3->registerNumber, $3->phantomOffSet);
                                                                              else //If its an integer or a boolean
                                                                                  fprintf(output, "contents b, %d\n", $3->offset);
                                                                                  
                                                                          }
                                                                          // For number and boolean literals (true && false) on the right hand side
                                                                          else if ($3->isRegister && !$3->isMemAddress) 
                                                                              fprintf(output, "r%d\n", $3->registerNumber);
                                                                      }

                                                                      
                                                                  } //end of variable case

                                                                  
                                                                  /*********************************************************************************************/
                                                                  //KIND IS array_type(enum 4): An assignment statement with array  on the lefthand side
                                                                  else if (variableInTree->kind == array_type) {
                                                                      int walkBackCount = countGlobalSearch(stackOfTrees, $1);
                                                                
                                                                      //Handles LOCAL variables in the LEFT-HAND side of an ASSIGNMENT
                                                                      if (walkBackCount == 0) {
                                                                          fprintf(output, "%d: contents b, r%d, %d := ",
                                                                                  globalRecord.pc++, $2->record->registerNumber, variableInTree->offset);
                                                                      }

                                                                
                                                                      //Handles NON-LOCAL variables in the LEFT_HAND side of an ASSIGNMENT
                                                                      else {
                                                                          struct node* nodeInTree = globalSearch(stackOfTrees, $1);
                                                                          if (nodeInTree != NULL) {

                                                                              //r2 := b
                                                                              fprintf(output, "%d: r%d := b\n", globalRecord.pc++, globalRecord.registerNumber);
                                                                        
                                                                              //Loop updates the register and static link  Ex. r2 := contents r2, 2
                                                                              while (walkBackCount != 0) {
                                                                                  fprintf(output, "%d: r%d := contents r%d, 2\n",
                                                                                          globalRecord.pc++, globalRecord.registerNumber, globalRecord.registerNumber);
                                                                                  walkBackCount--;
                                                                              }

                                                                              //Add the base address of current variable with offset of expression inside of the array
                                                                              fprintf(output, "%d: r%d := r%d + r%d\n",
                                                                                      globalRecord.pc++, globalRecord.registerNumber, globalRecord.registerNumber, $2->record->registerNumber);
                                                                              
                                                                              //Ex. contents r2, 5 := contents b, 4  or contents r3, 5 := contents r2, 6
                                                                              fprintf(output, "%d: contents r%d, %d := ",
                                                                                      globalRecord.pc++, globalRecord.registerNumber++, nodeInTree->offset);
                                                                          }
                                                                          else
                                                                              printf("Error: Check your statement_sequence_prime -> ID ASSIGN expression production");
                                                                      }
                                                                      
                                                                      

                                                                      //For the RIGHT HAND side of an ASSIGNMENT
                                                                      // For global variables (true && true) on right hand side
                                                                      if ($3 != NULL){
                                                                          if ($3->isRegister && $3->isMemAddress)
                                                                              if ($3->variableType == array)
                                                                                  fprintf(output, "contents r%d, %d\n", $3->registerNumber, $3->phantomOffSet);
                                                                              else
                                                                                  fprintf(output, "contents r%d, %d\n", $3->registerNumber, $3->offset);
                                                                          
                                                                          // For local variables (false && true) on right hand side
                                                                          else if (!$3->isRegister && $3->isMemAddress) {
                                                                              if ($3->variableType == array)
                                                                                  fprintf(output, "contents b, r%d, %d\n", $3->registerNumber, $3->phantomOffSet);
                                                                              else //If its an integer or a boolean
                                                                                  fprintf(output, "contents b, %d\n", $3->offset);
                                                                          }
                                                                          
                                                                          // For number and boolean literals (true && false) on the right hand side
                                                                          else if ($3->isRegister && !$3->isMemAddress) 
                                                                              fprintf(output, "r%d\n", $3->registerNumber);
                                                                      }

                                                                  } //end of array_type


                                                                  
                                                                  /*************************************************************************************************************/
                                                                  //KIND IS record_type(enum 10): An assignment statement with record on the lefthand side
                                                                  else if (variableInTree->kind == record_type) {
                                                                      fprintf(output, "THIS IS A RECORD TYPE\n");
                                                                      
                                                                      recordptr subVariableInfo = createRecord();
                                                                      
                                                                      //If the LEFT-HAND side of an ASSIGNMENT is accessing a variable from a record!
                                                                      recordptr variableInfo = $2->record; //This is the generic variable of Ada record type Ex.

                                                                      //fprintf(output, "Searching for: %s\n", $2->record->variableName);
                                                                      
                                                                      struct node* nodeInTree = globalSearch(stackOfTrees, $1); //Find node of Ada record type in binary Tree
                                                                      
                                                                      //Find the sub-variable inside of the Ada record type and calculate its offset
                                                                      int subVariableOffSet = 0;
                                                                      RecordListPtr traverseList = nodeInTree->listOfVariables;

                                                                      
                                                                      while( (traverseList != NULL) && !(strcmp(traverseList->variableName, variableInfo->variableName) == 0) ) {
                                                                          subVariableOffSet = subVariableOffSet + traverseList->memSpace;
                                                                          //printf("In primary production %s\n", traverseList->variableName); //TODO: Fix this error!
                                                             
                                                                          traverseList = traverseList->next; 
                                                                      }

                                                                      subVariableOffSet = nodeInTree->offset + subVariableOffSet;
                                                         
                                                                      //Found sub-variable inside of the Ada record type so continue
                                                                      if (traverseList != NULL) {
                                                                          //Add on the base offset of variable of type Ada record
                                                                          subVariableInfo->offset = subVariableOffSet;

                                                                          if (traverseList->kind == array_type){
                                                                              subVariableInfo->variableType = array;
                                                                          }
                                                                          else
                                                                              subVariableInfo->kind = traverseList->kind;
                                                                                  
                                                                          //subVariable->parent_type = traverseList->record->parent_type //May not need this line
                                                                          subVariableInfo->isRegister = false;    // local variables are NOT stored in a register
                                                                          subVariableInfo->isMemAddress = true;   // MUST DISPLAY contents b, 4 etc. for local variables

                                                                      }
                                                                      else 
                                                                          printf("Could not find the variable of this Ada record type! This is printing out in the ID opt_param opt_assign production.\n");


                                                                      //Start printing out AMI!!!
                                                                      int walkBackCount = countGlobalSearch(stackOfTrees, $1);
                                                                
                                                                      //Handles LOCAL variables in the LEFT-HAND side of an ASSIGNMENT
                                                                      if (walkBackCount == 0) {
                                                                          fprintf(output, "%d: contents b, %d := ", globalRecord.pc++, subVariableInfo->offset);
                                                                      }

                                                                      
                                                                      //Handles NON-LOCAL variables in the LEFT_HAND side of an ASSIGNMENT
                                                                      else {
                                                                          struct node* nodeInTree = globalSearch(stackOfTrees, $1);
                                                                          if (nodeInTree != NULL) {

                                                                              //r2 := b
                                                                              fprintf(output, "%d: r%d := b\n", globalRecord.pc++, globalRecord.registerNumber);
                                                                        
                                                                              //Loop updates the register and static link  Ex. r2 := contents r2, 2
                                                                              while (walkBackCount != 0){
                                                                                  fprintf(output, "%d: r%d := contents r%d, 2\n",
                                                                                          globalRecord.pc++, globalRecord.registerNumber, globalRecord.registerNumber);
                                                                                  walkBackCount--;
                                                                              }


                                                                              //Add the base address of current variable with offset of expression inside of the array
                                                                              if (subVariableInfo->variableType == array) {
                                                                                  fprintf(output, "%d: r%d := r%d + r%d\n",
                                                                                          globalRecord.pc++, globalRecord.registerNumber, globalRecord.registerNumber, $2->record->registerNumber);
                                                                              }

                                                                              
                                                                              //Ex. contents r2, 5 := contents b, 4  or contents r3, 5 := contents r2, 6
                                                                              fprintf(output, "%d: contents r%d, %d := ",
                                                                                      globalRecord.pc++, globalRecord.registerNumber++, subVariableInfo->offset);
                                                                          }
                                                                          else
                                                                              printf("Error: Check your statement_sequence_prime -> ID ASSIGN expression production");
                                                                      }
                                                                      



                                                                      //For the RIGHT HAND side of an ASSIGNMENT
                                                                      // For global variables (true && true) on right hand side
                                                                      if ($3 != NULL){
                                                                          if ($3->isRegister && $3->isMemAddress) {
                                                                              if ($3->variableType == array)
                                                                                  fprintf(output, "contents r%d, %d\n", $3->registerNumber, $3->phantomOffSet);
                                                                              else
                                                                                  fprintf(output, "contents r%d, %d\n", $3->registerNumber, $3->offset);
                                                                          }
                                                                          // For local variables (false && true) on right hand side
                                                                          else if (!$3->isRegister && $3->isMemAddress) {
                                                                              if ($3->variableType == array)
                                                                                  fprintf(output, "contents b, r%d, %d\n", $3->registerNumber, $3->phantomOffSet);
                                                                              else //If its an integer or a boolean
                                                                                  fprintf(output, "contents b, %d\n", $3->offset);
                                                                          }
                                                                          // For number and boolean literals (true && false) on the right hand side
                                                                          else if ($3->isRegister && !$3->isMemAddress) 
                                                                              fprintf(output, "r%d\n", $3->registerNumber);
                                                                      }
                                                                      
                                                                      
                                                                  } //end of record_type




                                                                  
                                                                  /*************************************************************************************************************/
                                                                  //KIND IS READ_ROUTINE(enum 7):
                                                                  else if (variableInTree->kind == read_routine) {
                                                                      RecordNodePtr traverseList = $2;

                                                                      //QUESTION: is read(a, g, h) possible? If not then replace while loop with if statement
                                                                      while (traverseList != NULL) {
                                                                          fprintf(output, "%d: ", globalRecord.pc++);
                                                                          
                                                                          if (traverseList->record->variableType == integer) //enum value of 0
                                                                              fprintf(output, "read_integer ");
                                                                          else if(traverseList->record->variableType == boolean) //enum value of 1
                                                                                   fprintf(output, "read_boolean ");
                                                                          else
                                                                              fprintf(output, "Error:variable type not found! Check production, proc_read_write_arrays_assign\n");

                                                                          //Make sure whatevers in read is a variable and not a literal!
                                                                          if (traverseList->record->isMemAddress) {
                                                                              if (!traverseList->record->isRegister) //For Local Variables
                                                                                  fprintf(output, "contents b, %d\n", traverseList->record->offset);
                                                                              else                                   //For Non-Local Variables
                                                                                  fprintf(output, "contents r%d, %d\n", traverseList->record->registerNumber, traverseList->record->offset);
                                                                          }
                                                                          else
                                                                              fprintf(output, "Error: A literal made its way into read(literal). Check production, proc_read_write_arrays_assign ");
                                                                                                                                                    
                                                                          traverseList = traverseList->next;
                                                                          
                                                                      }
                                                                  } //end of read case


                                                                  /*************************************************************************************************************/
                                                                  //KIND IS WRITE_ROUTINE(enum 8)
                                                                  else if (variableInTree->kind == write_routine) {
                                                                      RecordNodePtr traverseList = $2;
                                                                      
                                                                      while (traverseList != NULL) {
                                                                          fprintf(output, "%d: write ", globalRecord.pc++);
                                                                          
                                                                          if (traverseList->record->isRegister)
                                                                              fprintf(output, "r%d\n", traverseList->record->registerNumber);
                                                                          else if (!traverseList->record->isRegister)
                                                                              fprintf(output, "contents b, %d\n", traverseList->record->offset);
                                                                             

                                                                          traverseList = traverseList->next;
                                                                          
                                                                      }
                                                                  }//end of write case

                                                                  
                                                                  /*************************************************************************************************************/
                                                                  //KIND IS PROCEDURE(enum 2): a procedure so calculate static, dynamic, next base, and return address
                                                                  else if (variableInTree->kind == procedure) {
                                                                    
                                                                      //Jump to start of current Procedure AR to place in values for DL, SL,etc.
                                                                      fprintf(output, "%d: r%d := b\n", globalRecord.pc++, globalRecord.registerNumber);
                                                                      fprintf(output, "%d: b := contents r%d, 0 \n", globalRecord.pc++, globalRecord.registerNumber);

                                                                      //Dynamic Link
                                                                      fprintf(output, "%d: contents b, 3 := r%d\n", globalRecord.pc++, globalRecord.registerNumber);

                                                                    
                                                                      //Static Link //MUST DO AN IF STATEMENT THAT CHECKS THE STATIC LINK OF THE PROCEDURE
                                                                      int walkBackCount = countGlobalSearch(stackOfTrees, $1);
                                                                      if (walkBackCount == 0) {
                                                                          //fprintf(output, "%d: contents b, 2 := r%d\n", globalRecord.pc++, globalRecord.registerNumber++);
                                                                      }
                                                                      else {
                                                                          int registerHolder = globalRecord.registerNumber++;  //r4
                                                                          fprintf(output, "%d: r%d := contents r%d, 2\n",
                                                                                  globalRecord.pc++, globalRecord.registerNumber, registerHolder);
                                                                          walkBackCount--;
                                                                        
                                                                          while (walkBackCount != 0){
                                                                              fprintf(output, "%d: r%d := contents r%d, 2\n",
                                                                                      globalRecord.pc++, globalRecord.registerNumber, globalRecord.registerNumber);
                                                                              walkBackCount--;
                                                                          }

                                                                      }
                                                                      fprintf(output, "%d: contents b, 2 := r%d\n", globalRecord.pc++, globalRecord.registerNumber++);

                                                                    
                                                                      //Calculate next base of AR //Figure out the offset of the next procedure
                                                                      fprintf(output, "%d: r%d := %d**********\n", globalRecord.pc++, globalRecord.registerNumber, variableInTree->offset);
                                                                      fprintf(output, "%d: contents b, 0 := b + r%d\n", globalRecord.pc++, globalRecord.registerNumber++);



                                                                      //TODO: Fix in/in out parameters  Fix procedure call with parameters
                                                                      fprintf(output, "Check production proc_read_write_arrays_assign.   Fix in/in out parameters right here.\n");
                                                                      //variableInTree->next //Do something with the formal parameters right here


                                                                      
                                                                      //Return Address //Jump to pc count
                                                                      fprintf(output, "%d: r%d := %d\n", globalRecord.pc++, globalRecord.registerNumber, globalRecord.pc + 3);
                                                                      fprintf(output, "%d: contents b, 1 := r%d\n", globalRecord.pc++, globalRecord.registerNumber++);
                                                                    
                                                                      //Call to Nest //Place the offset of procedure inside of symbol Table node
                                                                      fprintf(output, "%d: pc := %d \n", globalRecord.pc++, variableInTree->procStart);

                                                                  } // end of else if (procNodeInTree->kind == procedure)

                                                                    
                                                                  
                                                                  
                                                               } //end of production 
                              ;

optional_parameters           : '(' expression_list ')'        {
                                                                   // Type is a RecordNodePtr
                                                                   $$ = $2;  // for read write and arrays with parameters
                                                               }
                              | %empty                         { $$ = NULL; }
                              | nested_record                  { $$ = $1;}
                              ;


nested_record                 : nested_record '.' ID
                                                               {
                                                                   $$ = NULL; //TODO: For nested records
                                                               }
                              | '.' ID
                                                               {
                                                                   recordptr temp = createRecord();
                                                                   strcpy(temp->variableName, $2);

                                                                   //fprintf(output, "BEFORE Searching for: %s\n", temp->variableName);
                                                                   
                                                                   RecordNodePtr subVariable = createRecordNode(temp);

                                                                   //fprintf(output, "AFTER Searching for: %s\n", subVariable->record->variableName);

                                                                   $$ = subVariable;
                                                                   
                                                               }

                              | '.' ID '(' expression ')'       //Used to handle arrays inside of expressions
                                                               {
                                                                   recordptr temp = createRecord();
                                                                   strcpy(temp->variableName, $2);
                                                                   temp->offset = $4->offset;
                                                                   temp->phantomOffSet = $4->phantomOffSet;
                                                                   temp->registerNumber = $4->registerNumber;
                                                                   //fprintf(output, "BEFORE Searching for: %s\n", temp->variableName);
                                                                   
                                                                   RecordNodePtr subVariable = createRecordNode(temp);

                                                                   //fprintf(output, "AFTER Searching for: %s\n", subVariable->record->variableName);

                                                                   $$ = subVariable;
                                                               }
                              ;

optional_assign               : ASSIGN expression
                                                               {
                                                                   // Type is a recordptr
                                                                   // expression can derive a literal, an Id, an ( expression ) or an array index or a combination of all of them
                                                                   $$ = $2;

                                                               }
                              | %empty                         {   $$ = NULL; } //This should already be checked by the grammar itself 
                              ;



statement_sequence_prime: NULLWORD
                        //TODO: EMIT a Store instruction
                        | proc_read_write_arrays_assign
                        | loop_part
                        | if_statement
                        | RAISE ID
                        
                                                                
                        /*
                        | ID ASSIGN expression                {
                                                                    
                                                              }
                        
                        */
                        /*                                     
                        | name                                {
                                                                //struct node* procNodeInTree = globalSearch(stackOfTrees, $1);              

                                                              }
                        */
                        ;

/*
name                    : ID                                  { $$ = $1; }
                        | ID '(' expression_list ')'          {
                                                                struct node* nodeInTree = globalSearch(stackOfTrees, $1);
                                                                //For READ and WRITE Routines
                                                                if (nodeInTree->kind == read_routine)  //enum is 7
                                                                    fprintf(output, "%d: read_boolean contents b, %d\n", globalRecord.pc++, returnOffSet(stackOffSet));
                                                                else if (nodeInTree->kind == write_routine) //enum is 8
                                                                    fprintf(output, "%d: write \n", globalRecord.pc++ );

                                                                //For PROCEDURES with PARAMETERS
                                                                else if (nodeInTree->kind == procedure)
                                                                    $$ = $1; 
                                                              }
                        ;
*/



//Accounts for where the loop begins and ends in the program
loop_part               : loop_start loop_stmt_list ENDLOOP
                                                                 {
                                                                     //UPDATE patch list by apending the patchlines from the topmost linked list AND the current pc
                                                                     printf("Here is the updated patch list (LOOP PRODUCTION) for this procedure: \n");
                                                                     ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                                                     while (tempHead != NULL) {
                                                                         patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc+1);
                                                                         tempHead = tempHead->next;
                                                                     }
                                                                     printAllNodes(patchList);

                                                                     
                                                                     //printf("Here is the patch list for this procedure: \n");
                                                                     //printAllNodes(stackOfLL[patchTopIndex].leaveAddressPtr);
                                                                     printf("\n\n");


                                                                     fprintf(output, "%d: pc := %d\n", globalRecord.pc++, $1);
                                                                     // POP: After patching all the forward references when leaving the loop
                                                                     popList(stackOfLL);
                                                                 }
                        ;
loop_start              : LOOP
                                                                 {
                                                                    pushList(stackOfLL); //Push a new linked list onto stack
                                                                    $$ = globalRecord.pc; // Remembers the pc number to jump back to the beginning of the loop
                                                                 }
                        ;
loop_stmt_list          : loop_stmt ';' loop_stmt_list
                                                                
                        | loop_stmt ';'
                        ;
loop_stmt               : statement_sequence_prime 
                        | when_condition
                        ;
when_condition          : EXITWHEN condition
                                                                 {
                                                                     //Print out the instruction line to jump to
                                                                     fprintf(output, "%d: pc := ? if r%d\n", globalRecord.pc, $2->registerNumber);
                                                                     putInToList(stackOfLL, globalRecord.pc++); //Place instruction counter to stack of linked list
                                                                 }
                        | EXIT
                                                                 {
                                                                     //Print out the instruction line to jump to
                                                                     fprintf(output, "%d: pc := ?\n", globalRecord.pc);
                                                                     putInToList(stackOfLL, globalRecord.pc++);
                                                                 }
                        ;


//Accounts for where the if statement begins and ends in the program

// GET A SEGMENTATION FAULT IN fourthHandout2.ada file which is combination of loop and a simple if statement
if_statement            : if_start  initial  THEN  sequence_of_statements  optional_else_if  optional_else ENDIF
                                        {

                                            if ($5 != -1) {
                                                ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                                while (tempHead != NULL){
                                                    patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc);
                                                    tempHead = tempHead->next;
                                                }
                                                
                                                popList(stackOfLL);
                                            }
                                            else if ($6 != -1) {
                                                ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                                if (tempHead != NULL){
                                                    patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc + 1);
                                                }
                                                
                                                popList(stackOfLL);
                                            }
                                            // May not need because this case is already taken care of at the top
                                            //HOWEVER must have in case optional-else_if and optional_else are both empty
                                            else {
                                                ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                                if (tempHead != NULL){
                                                    patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc + 1);
                                                }

                                                popList(stackOfLL); // Must use if file only contains a single if statement
                                                popList(stackOfLL);
                                            }
                                            // popList(stackOfLL);
                                            //popList(stackOfLL);
                                        }
                        ;

if_start                : IF            { pushList(stackOfLL);  $$ = globalRecord.pc; } //for Pc jumps
                        ;
//optional_else_if   else_if_section    else_if_stmt   else_if_start   optional_else   initial These need to be declared as var

optional_else_if        : else_if_section  { $$ = $1;}
                        | %empty           { $$ = -1;}
                        ;

else_if_section         : else_if_stmt  else_if_section  { $$ = $1; }
                        | else_if_stmt                   { $$ = $1; }
                        ;

else_if_stmt            : else_if_start initial THEN sequence_of_statements
                                        {
                                            $$ = $1;
                                        }
                        ;

else_if_start           : ELSEIF
                                        {
                                            //This is to patch the cond jumps
                                            ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                            if (tempHead != NULL){
                                                patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc + 1);
                                             }
                                            popList(stackOfLL);
                                            
                                                                                        
                                            putInToList(stackOfLL, globalRecord.pc);
                                            fprintf(output, "%d: pc := ?\n", globalRecord.pc++);
                                            //fprintf(output, "ELSEIF   "); 
                                            $$ = globalRecord.pc;   
                                        }
                        ;


optional_else           : else_start sequence_of_statements { $$ = $1; }
                        | %empty                            { $$ = -1; }
                        ;

else_start              : ELSE
                                        {
                                            //This is to patch the pc jumps
                                            ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                            if (tempHead != NULL){
                                                patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc + 1);
                                            }
                                            popList(stackOfLL);
                                            
                                                                                        
                                            putInToList(stackOfLL, globalRecord.pc);
                                            fprintf(output, "%d: pc := ?\n", globalRecord.pc++);
                                            // fprintf(output, "ELSE   ");
                                            $$ = globalRecord.pc;
                                        }
                        ;


initial                 : condition
                                        {
                                            pushList(stackOfLL);
                                            putInToList(stackOfLL, globalRecord.pc); // Need to patch the previous line
                                            
                                            // 
                                            fprintf(output, "%d: pc := ? if not r%d\n", globalRecord.pc++, $1->registerNumber);
                                            $$ = globalRecord.pc - 1;
                                        }
                        ;

condition               : expression 
                                        {
                                            $$ = $1;  //Pass up the ptr to the record  
                                        }
                        ;


//Expressions in Ada
//TODO: EMIT instructions
expression_list         : expression ',' expression_list                       { RecordNodePtr newListHead = createRecordNode($1);  $$ = addToRecordList(newListHead, $3); } 
                        | expression                                           { RecordNodePtr recordListHead = createRecordNode($1); $$ = recordListHead; }
                        ;

expression              : relation                                             { $$ = $1; } 
                        | expression  boolean_operation  relation              {

                            
                                                                                 recordptr resultInfo = createRecord();

                                                                                 //Want to push this register number up
                                                                                 //Its the right hand side so must assign it to something
                                                                                 resultInfo->registerNumber = globalRecord.registerNumber++;
                                                                                 resultInfo->isRegister = true;
                                                                                 resultInfo->isMemAddress = false;
                                                                                 fprintf(output, "%d: r%d := ", globalRecord.pc++, resultInfo->registerNumber);

                                                                                 //Handles left hand side of operation
                                                                                 if ($1->isMemAddress) { //can either be a local or a global variable
                                                                                     if ($1->isRegister)   fprintf(output, "contents r%d, %d ", $1->registerNumber, $1->offset); // Gloabl Variables
                                                                                     else                  fprintf(output, "contents b, %d ", $1->offset);                       // Local Variables
                                                                                 }
                                                                                 else {
                                                                                     if ($1->isRegister)    fprintf(output, "r%d ", $1->registerNumber); // Literals (boolean or ints etc.)
                                                                                     else                   fprintf(output, "ERROR in ada.y, expr : expr  b_o  rel\n");
                                                                                 }     
                                                                         
                                                                                 //Prints out a AND or OR
                                                                                 fprintf(output, "%s ", $2);
                                                                         
                                                                                 //Handles righthand side of operation
                                                                                 if ($3->isMemAddress) { //can either be a local or a global variable
                                                                                     if ($3->isRegister)   fprintf(output, "contents r%d, %d\n", $3->registerNumber, $3->offset); //Global Variables
                                                                                     else                  fprintf(output, "contents b, %d\n", $3->offset);                       //Local Variables
                                                                                 }
                                                                                 else {
                                                                                     if ($3->isRegister)    fprintf(output, "r%d\n", $3->registerNumber); // Literals (boolean or ints etc.)
                                                                                     else                   fprintf(output, "ERROR in ada.y, expr : expr  b_o  rel\n");
                                                                                 }

                            
                            

                                                                                  $$ = resultInfo;

                                                                               }             // Emit an argument arithmetic instruction
                        ;

relation                : simple_expression                                    { $$ = $1; }
                        | relation  relational_operation  simple_expression    {            //TODO: Emit an ALU arithmetic instruction

                                                                                 recordptr resultInfo = createRecord();
                                                                                 resultInfo->isRegister = true;
                                                                                 resultInfo->isMemAddress = false;
                                                                                
                                                                                 //fprintf(output, "left: %d,   right: %d\n\n", $1->registerNumber, $3->registerNumber);
                                                                                 //Must put $1 into register to do relational operations in AMI
                                                                                 int firstReg = $1->registerNumber; 
                                                                                 if ($1->isMemAddress) {
                                                                                     if (firstReg == 0) //If variable assignment does not exist then give a new registerNumber
                                                                                         firstReg = globalRecord.registerNumber++;
                                                                                     
                                                                                     fprintf(output, "%d: r%d := ", globalRecord.pc++, firstReg);
                                                                                     
                                                                                     if ($1->isRegister)  fprintf(output, "contents r%d, %d \n", firstReg, $1->offset); // Global Variables
                                                                                     else                 fprintf(output, "contents b, %d \n", $1->offset);             // Local Variables
                                                                                 }
                                                                                 
                                                                                 //Must put $3 into register to do relational operations in AMI
                                                                                 int secondReg = $3->registerNumber; 
                                                                                 if ($3->isMemAddress) {
                                                                                     if (secondReg == 0) //If variable assignment does not exist then give a new registerNumber
                                                                                         secondReg = globalRecord.registerNumber++;
                                                                                     
                                                                                     fprintf(output, "%d: r%d := ", globalRecord.pc++, secondReg);
                                                                                     
                                                                                     if ($3->isRegister)  fprintf(output, "contents r%d, %d \n", secondReg, $3->offset); // Global Variables
                                                                                     else                 fprintf(output, "contents b, %d \n", $3->offset);              // Local Variables
                                                                                 }

                                                                                 
                                                                                 //Left Hand Side of AMI
                                                                                 resultInfo->registerNumber = globalRecord.registerNumber++;
                                                                                 fprintf(output, "%d: r%d := ",  globalRecord.pc++, resultInfo->registerNumber);

                                                                                 //Right Hand Side of AMI
                                                                                 if (strcmp($2, ">") == 0)
                                                                                     fprintf(output, "r%d < r%d\n", secondReg, firstReg);

                                                                                 else if (strcmp($2, ">=") == 0) 
                                                                                     fprintf(output, "r%d <= r%d\n", secondReg, firstReg);
                                                                                    
                                                                                 else                         
                                                                                     fprintf(output, "r%d %s r%d\n", firstReg, $2, secondReg);
                                                                                 
                                                                                 
                                                                                 $$ = resultInfo;
                                                                               }
                        ;

simple_expression       : term                                        { $$ = $1; }
                        | '-' term                                    {
                                                                        //TODO: Emit an argument arithmetic instruction
                            
                                                                        recordptr resultInfo = createRecord();
                                                                        resultInfo->registerNumber = globalRecord.registerNumber++;
                                                                        resultInfo->isRegister = true;
                                                                        resultInfo->isMemAddress = false;
                                                                        
                                                                        fprintf(output, "%d: r%d := - ", globalRecord.pc++, resultInfo->registerNumber);
                                                                        
                                                                        //Right Hand side of AMI, either a Non-Local, Local or literal
                                                                         if ($2->isMemAddress) { //can either be a local or a global variable
                                                                             if ($2->isRegister)   fprintf(output, "contents r%d, %d\n", $2->registerNumber, $2->offset); //Non-Local Variable
                                                                             else                  fprintf(output, "contents b, %d\n", $2->offset);                       //Local Variable
                                                                         }
                                                                         else {
                                                                             if ($2->isRegister)   fprintf(output, "r%d\n", $2->registerNumber); // Literals (boolean or ints etc.)
                                                                             else                  fprintf(output, "ERROR in ada.y, s_e : - term\n");
                                                                         }

                                                                         
                                                                        $$ = resultInfo;
                                                                      }
                        | simple_expression  adding_operation  term   {

                                                                         recordptr resultInfo = createRecord();

                                                                         //Want to push this register number up
                                                                         //Its the right hand side so must assign it to something
                                                                         resultInfo->registerNumber = globalRecord.registerNumber++;
                                                                         resultInfo->isRegister = true;
                                                                         resultInfo->isMemAddress = false;
                                                                         fprintf(output, "%d: r%d := ", globalRecord.pc++, resultInfo->registerNumber);

                                                                         //Handles left hand side of operation
                                                                         if ($1->isMemAddress) { //can either be a Non-Local or a Local variable
                                                                             if ($1->isRegister)   fprintf(output, "contents r%d, %d ", $1->registerNumber, $1->offset); // Non-Local Variable
                                                                             else                  fprintf(output, "contents b, %d ", $1->offset);                       // Local Variable
                                                                         }
                                                                         else {
                                                                             if ($1->isRegister)    fprintf(output, "r%d ", $1->registerNumber); // Literals (boolean or ints etc.)
                                                                             else                   fprintf(output, "ERROR in ada.y, s_e : s_e a_o term factor\n");
                                                                         }     
                                                                         
                                                                         //Prints out a + or a -
                                                                         fprintf(output, "%s ", $2);
                                                                         
                                                                         //Handles righthand side of operation
                                                                         if ($3->isMemAddress) { //can either be a Non-Local or a Local variable
                                                                             if ($3->isRegister)   fprintf(output, "contents r%d, %d\n", $3->registerNumber, $3->offset); //Non-Local Variable
                                                                             else                  fprintf(output, "contents b, %d\n", $3->offset);                       //Local Variable
                                                                         }
                                                                         else {
                                                                             if ($3->isRegister)    fprintf(output, "r%d\n", $3->registerNumber); // Literals (boolean or ints etc.)
                                                                             else                   fprintf(output, "ERROR in ada.y, s_e : s_e a_o term factor\n");
                                                                         }
                                                                         
                                                                         $$ = resultInfo;
                                                                         
                                                                      }
                        ;

term                    : factor                                      { $$ = $1; }
                        | term  multiplying_operation  factor         {
                                                                       
                            
                                                                         recordptr resultInfo = createRecord();

                                                                         //Want to push this register number up
                                                                         //Its the right hand side so must assign it to something
                                                                         resultInfo->registerNumber = globalRecord.registerNumber++;
                                                                         resultInfo->isRegister = true;
                                                                         resultInfo->isMemAddress = false;
                                                                         fprintf(output, "%d: r%d := ", globalRecord.pc++, resultInfo->registerNumber);


                                                                         
                                                                         //Handles lefthand side of operation
                                                                         if ($1->isMemAddress) { //can either be a Non-Local or a Local variable
                                                                             if ($1->isRegister)   fprintf(output, "contents r%d, %d ", $1->registerNumber, $1->offset); // Non-Local Variable
                                                                             else                  fprintf(output, "contents b, %d ", $1->offset);                       // Local Variable
                                                                         }
                                                                         else {
                                                                             if ($1->isRegister)    fprintf(output, "r%d ", $1->registerNumber); // Literals (boolean or ints etc.)
                                                                             else                   fprintf(output, "ERROR in ada.y, term : term multiplying_operation factor\n");
                                                                         }     
                                                                         
                                                                         //Prints out a * or a /
                                                                         fprintf(output, "%s ", $2);
                                                                         
                                                                         //Handles righthand side of operation
                                                                         if ($3->isMemAddress) { //can either be a Non-Local or a Local variable
                                                                             if ($3->isRegister)   fprintf(output, "contents r%d, %d\n", $3->registerNumber, $3->offset); //Non-Local Variable
                                                                             else                  fprintf(output, "contents b, %d\n", $3->offset);               //Local Variable
                                                                         }
                                                                         else {
                                                                             if ($3->isRegister)    fprintf(output, "r%d\n", $3->registerNumber); // Literals (boolean or ints etc.)
                                                                             else                   fprintf(output, "ERROR in ada.y, term : term multiplying_operation factor\n");
                                                                         }
                            
                                                                         $$ = resultInfo;
                                                                      }
                        ;

factor                  : primary                    {
                                                         $$ = $1;   //printf("register number:%d, register offset:%d\n", $1->registerNumber, $1->offset);
                                                     }
                        | primary  EXP  primary      {
                                                         //TODO: Emit several Argument Arithmetic instructions
                                                         recordptr resultInfo = createRecord();
                                                         resultInfo->isRegister = true;
                                                         resultInfo->isMemAddress = false;
                                                                                
                                                         //fprintf(output, "left: %d,   right: %d\n\n", $1->registerNumber, $3->registerNumber);
                                                         //Must put $1 into register to do relational operations in AMI
                                                         int firstReg = $1->registerNumber; 
                                                         if ($1->isMemAddress) {
                                                             if (firstReg == 0) //If variable assignment does not exist then give a new registerNumber
                                                                 firstReg = globalRecord.registerNumber++;
                                                                                     
                                                             fprintf(output, "%d: r%d := ", globalRecord.pc++, firstReg);
                                                                                     
                                                             if ($1->isRegister)  fprintf(output, "contents r%d, %d \n", firstReg, $1->offset); // Global Variables
                                                             else                 fprintf(output, "contents b, %d \n", $1->offset);             // Local Variables
                                                         }
                                                                                 
                                                         //Must put $3 into register to do relational operations in AMI
                                                         int secondReg = $3->registerNumber; 
                                                         if ($3->isMemAddress) {
                                                             if (secondReg == 0) //If variable assignment does not exist then give a new registerNumber
                                                                 secondReg = globalRecord.registerNumber++;
                                                                                     
                                                             fprintf(output, "%d: r%d := ", globalRecord.pc++, secondReg);
                                                                                     
                                                             if ($3->isRegister)  fprintf(output, "contents r%d, %d \n", secondReg, $3->offset); // Global Variables
                                                             else                 fprintf(output, "contents b, %d \n", $3->offset);              // Local Variables
                                                         }

                                                         int productReg = globalRecord.registerNumber++;
                                                         resultInfo->registerNumber = productReg;
                                                         fprintf(output, "%d: r%d := 1\n", globalRecord.pc++, productReg);

                                                         int decrementReg = globalRecord.registerNumber++;
                                                         fprintf(output, "%d: r%d := 1\n", globalRecord.pc++, decrementReg);

                                                         int pcJumpLine = globalRecord.pc++;
                                                         fprintf(output, "%d: r%d := r%d * r%d\n", pcJumpLine, productReg, productReg, firstReg);

                                                         int compareReg = globalRecord.registerNumber++;
                                                         fprintf(output, "%d: r%d := r%d = r%d\n", globalRecord.pc++, compareReg, secondReg, decrementReg);

                                                         fprintf(output, "%d: r%d := r%d - r%d\n", globalRecord.pc++, secondReg, secondReg, decrementReg);

                                                         fprintf(output, "%d: pc := %d if not r%d\n", globalRecord.pc++, pcJumpLine, compareReg);
                                                       
                                                       $$ = resultInfo;
                                                     }
                        | NOT  primary               {

                                                      recordptr resultInfo = createRecord();
                                                      resultInfo->registerNumber = globalRecord.registerNumber++;
                                                      resultInfo->isRegister = true;
                                                      resultInfo->isMemAddress = false;
                                                                        
                                                      fprintf(output, "%d: r%d := not ", globalRecord.pc++, resultInfo->registerNumber);
                                                                        
                                                      //Right Hand side of AMI, either a Non-Local, Local or literal
                                                      if ($2->isMemAddress) { //can either be a Non-Local or a Local variable
                                                          if ($2->isRegister)   fprintf(output, "contents r%d, %d\n", $2->registerNumber, $2->offset); //Non-Local Variable
                                                          else                  fprintf(output, "contents b, %d\n", $2->offset);                       //Local Variable
                                                      }
                                                      else {
                                                          if ($2->isRegister)    fprintf(output, "r%d\n", $2->registerNumber); // Literals (boolean or ints etc.)
                                                          else                   fprintf(output, "ERROR in ada.y, factor : NOT primary\n");
                                                      }
                                                         
                            
                                                      $$ = resultInfo;
                                                     
                                                     }
                        ;

primary                 : NUMBER                     {
                                                       //fprintf(output, "************* name: %s *************", $1);
                                                       recordptr variableInfo = createRecord();
                                                       
                                                       //boolean is a literal that is not_declarable, default enum value is -1
                                                       //integer literals do not have an offset, BUT ONLY USE If number is used for INDEXING an array
                                                       variableInfo->offset = $1; 
                                                       variableInfo->registerNumber = globalRecord.registerNumber++;
                                                       variableInfo->isRegister = true;               //is a register so its a literal
                                                       variableInfo->isMemAddress = false;            //A literal so not a memory address  //NOt contents b, 4
                                                       
                                                       fprintf(output, "%d: r%d := %d\n", globalRecord.pc++, variableInfo->registerNumber, $1);
                                                       //fprintf(output, "%d: contents b, %d := r%d\n", globalRecord.pc++, variableInfo->offset, variableInfo->registerNumber);
                                                       //fprintf(output, "%d: contents b, %d := %d\n", globalRecord.pc++, variableInfo->offset, $1);
                                  
                                                       $$ = variableInfo;
                                                     }


                        | ID                         {

                                                       recordptr variableInfo = createRecord();
                                                       struct node* nodeInTree = globalSearch(stackOfTrees, $1);
                                                       //printf("%s has a value of %d\n", nodeInTree->symbol, nodeInTree->val);

                                                       int walkBackCount = countGlobalSearch(stackOfTrees, $1);

                                                       // Enumeration type IN YOUR RECORDS distinguishes between boolean and integers
                                                       //Handles true and false literals
                                                       if (nodeInTree->kind == value) { //value is an enum 5
                                                           //boolean is a literal that is not_declarable, default enum value is -1
                                                           //true and false do not have offset
                                                           variableInfo->registerNumber = globalRecord.registerNumber++; //ONLY KEEP THIS IF YOU WANT TO PUT TRUE INTO A REGISTER
                                                           variableInfo->isRegister = true;
                                                           variableInfo->isMemAddress = false;
                                                           //variableInfo->arrayIndex = -1; //Current Default value for indexing an array using a true or false boolean
                                                           
                                                           //if (variableInfo->registerNumber != 0)
                                                               fprintf(output, "%d: r%d := ", globalRecord.pc++, variableInfo->registerNumber);
                                                           
                                                           // accounts for true and false if statements in tree
                                                           if (strcmp(nodeInTree->symbol, "true") == 0)
                                                               fprintf(output, "true\n");  //variableInfo->value = 2; ALTERNATIVE IF DONT WANT TO PUT INTO REGISTER
                                                           else if (strcmp(nodeInTree->symbol, "false") == 0)
                                                               fprintf(output, "false\n");  //variableInfo->value = 1; ALTERNATIVE IF DONT WANT TO PUT INTO REGISTER
                                                           else
                                                               fprintf(output, "This is for maxint case with enum value");
                                                       }                                                      
                                                       
                                                       //Handles LOCAL variables in the right hand side of an assignment
                                                       else if (walkBackCount == 0) {
                                                           //fprintf(output, "************ name: %s,   variableType: %d **********\n", nodeInTree->symbol, nodeInTree->variableType);

                                                           //Put name into record. Need this for Ada records!
                                                           //variableInfo->variableName = (char*) malloc(sizeof($1) + 1);
                                                           strcpy(variableInfo->variableName, $1);                                                           
                                                               
                                                           variableInfo->variableType = nodeInTree->variableType; //need for read_boolean or read_integer
                                                           variableInfo->offset = nodeInTree->offset;
                                                           //local variables are not stored in a register
                                                           variableInfo->isRegister = false;         // local variables are NOT stored in a register
                                                           variableInfo->isMemAddress = true;        // MUST DISPLAY contents b, 4 etc. for local variables
                                                           //variableInfo->arrayIndex = -1; //Current Default value for indexing an array using a variable
                                                       }
                                                       //TODO: DOUBLE CHECK Handles GLOBAL variables in the right hand side of an assignment
                                                       else {
                                                           
                                                              variableInfo->variableType = nodeInTree->variableType;  //Need for read_boolean or read_integer
                                                              variableInfo->offset = nodeInTree->offset;
                                                              variableInfo->registerNumber = globalRecord.registerNumber;
                                                              variableInfo->isRegister = true;      // Want to walk back using a register  r2 := b then r2 := contents r2, 2
                                                              variableInfo->isMemAddress = true;    // THIS WILL BE STORED IN A REGISTER BECAUSE OF REQUIRED WALK BACK
                                                              //variableInfo->arrayIndex = -1; //Current Default value for indexing an array using a variable
                                                              fprintf(output, "**** name: %s **** offset: %d **** registerNumber: %d *****\n",
                                                                      nodeInTree->symbol, variableInfo->offset, variableInfo->registerNumber);

                                                              //r2 := b
                                                              fprintf(output, "%d: r%d := b\n", globalRecord.pc++, variableInfo->registerNumber);
                                                                        
                                                              //Loop updates the register and static link  Ex. r2 := contents r2, 2
                                                              while (walkBackCount != 0) {
                                                              fprintf(output, "%d: r%d := contents r%d, 2\n", globalRecord.pc++, variableInfo->registerNumber, variableInfo->registerNumber);
                                                                   walkBackCount--;
                                                              }
                                                              
                                                              //Update current regis
                                                              globalRecord.registerNumber++;
                                                            
                                                       }
                                                       
                                                       
                                                       $$ = variableInfo;
                                                       
                                                     }


                        | '(' expression ')'         {
                                                       $$ = $2;
                                                     }

                        | ID '(' expression ')'
                                                     {
                                                         //If the RIGHT-HAND side of an ASSIGNMENT has an array reference!
                                                         recordptr variableInfo = createRecord();
                                                         struct node* nodeInTree = globalSearch(stackOfTrees, $1);

                                                         if (nodeInTree != NULL) {
                                                             int walkBackCount = countGlobalSearch(stackOfTrees, $1);
                                                             
                                                             if (walkBackCount == 0) {
                                                                 //fprintf(output, "************ name: %s,   variableType: %d **********\n", nodeInTree->symbol, nodeInTree->variableType);
                                                                 
                                                                 //Put name into record. Need this for Ada records! Ex.   := arr(4).first 
                                                                 //variableInfo->variableName = (char*) malloc(sizeof($1) + 1);
                                                                 strcpy(variableInfo->variableName, $1);   
                                                                 
                                                                 variableInfo->variableType = array; //This is an array so enum is 2 //Probably dont need
                                                                 variableInfo->offset = nodeInTree->offset + $3->offset; // Ex: Index is from 4..7, so for c(7) its phantomoffset + 7 = 12
                                                                 //local variables are not stored in a register
                                                                 variableInfo->registerNumber = $3->registerNumber;
                                                                 variableInfo->isRegister = false;         // local variables are NOT stored in a register
                                                                 variableInfo->isMemAddress = true;        // MUST DISPLAY contents b, 4 etc. for local variables
                                                                 variableInfo->phantomOffSet = nodeInTree->offset; 
                                                             }
                                                             //TODO: DOUBLE CHECK Handles GLOBAL variables in the right hand side of an assignment
                                                             else {
                                                                 variableInfo->variableType = array; //This is an array so enum is 2 //Probably dont need
                                                                 variableInfo->offset = nodeInTree->offset + $3->offset; //Ex: Index is from 4..7, so for c(7) its phantomoffset + 7 = 12
                                                                 variableInfo->registerNumber = globalRecord.registerNumber;
                                                                 variableInfo->isRegister = true;      // Want to walk back using a register  r2 := b then r2 := contents r2, 2
                                                                 variableInfo->isMemAddress = true;    // THIS WILL BE STORED IN A REGISTER BECAUSE OF REQUIRED WALK BACK
                                                                 variableInfo->phantomOffSet = nodeInTree->offset;

                                                                 fprintf(output, "**** name: %s **** offset: %d **** registerNumber: %d *****\n",
                                                                         nodeInTree->symbol, variableInfo->offset, variableInfo->registerNumber);

                                                                 //r2 := b
                                                                 fprintf(output, "%d: r%d := b\n", globalRecord.pc++, variableInfo->registerNumber);
                                                                 
                                                                 //Loop updates the register and static link  Ex. r2 := contents r2, 2
                                                                 while (walkBackCount != 0) {
                                                                     fprintf(output, "%d: r%d := contents r%d, 2\n",
                                                                             globalRecord.pc++, variableInfo->registerNumber, variableInfo->registerNumber);
                                                                     walkBackCount--;
                                                                 }

                                                                            
                                                                 //Add the base address of current variable with offset of expression inside of the array
                                                                 fprintf(output, "%d: r%d := r%d + r%d\n",
                                                                         globalRecord.pc++, variableInfo->registerNumber, variableInfo->registerNumber, $3->registerNumber);
                                                                 
                                                                 //Update current register
                                                                 globalRecord.registerNumber++;
                                                            
                                                             }
                                                         }
                                                         else fprintf(output, "Error: Could not find variable. Check production: primary -> ID '(' expression ')' \n");
                                                       
                                                         $$ = variableInfo;
                                                         
                                                     } // To account for array

                          // primary should not be able to derive number and '(' expression ')'
                        | primary '.' ID  optional_array
                                                     {

                                                         
                                                         //This is the specific sub-variable inside of an Ada record type
                                                         //Ex. The specific sub-variable for one of many possible record instances
                                                         //Pass up information from already declared record into here!
                                                         recordptr subVariableInfo = createRecord();
                                                         
                                                         //If the RIGHT-HAND side of an ASSIGNMENT is accessing a variable from a record!
                                                         recordptr variableInfo = $1; //This is the generic variable of Ada record type Ex.
                                                         struct node* nodeInTree = globalSearch(stackOfTrees, variableInfo->variableName); //Find node of Ada record type in binary Tree

                                                         //Find the sub-variable inside of the Ada record type and calculate its offset
                                                         int subVariableOffSet = 0;
                                                         RecordListPtr traverseList = nodeInTree->listOfVariables;

                                                         printf("Searching for: %s\n", $3);
                                                         
                                                         while( (traverseList != NULL) &&  !(strcmp(traverseList->variableName, $3) == 0) ) {
                                                             subVariableOffSet = subVariableOffSet + traverseList->memSpace;
                                                             //fprintf(output, "In primary production %s\n", traverseList->variableName); //TODO: Fix this error!
                                                             
                                                             traverseList = traverseList->next; 
                                                         }

                                                         subVariableOffSet = nodeInTree->offset + subVariableOffSet;
                                                         
                                                         //Found sub-variable inside of the Ada record type so continue
                                                         if (traverseList != NULL) {

                                                              subVariableInfo->kind = traverseList->kind; // May be a variable array_type or record_type
                                                             //subVariable->parent_type = traverseList->record->parent_type //May not need this line
                                                             subVariableInfo->isRegister = false;    // local variables are NOT stored in a register
                                                             subVariableInfo->isMemAddress = true;   // MUST DISPLAY contents b, 4 etc. for local variables
                                                             
                                                            //Add on the base offset of variable of type Ada record
                                                             if ($4 == NULL)  //Not an array subVariable
                                                                 subVariableInfo->offset = subVariableOffSet;
                                                             else {            //Is an array subVariable
                                                                 subVariableOffSet = subVariableOffSet - traverseList->parent_type->lower; //Calculate phantom offset
                                                                 subVariableInfo->offset = subVariableOffSet + $4->offset;
                                                                 subVariableInfo->phantomOffSet = subVariableOffSet;
                                                                 subVariableInfo->variableType = array;
                                                                 subVariableInfo->registerNumber = $4->registerNumber;
                                                             }

                                                         }
                                                         else 
                                                             printf("Could not find the variable of this Ada record type! This is printing out in the primary production.\n");
                                                        
                     
                                                         $$ = subVariableInfo;
                                                         
                                                     } // To account for records
                        ;


optional_array          : '(' expression ')'      { $$ = $2; }
                        | %empty                  { $$ = NULL; }
                        ;

boolean_operation       : AND   { $$ = "and"; }
                        | OR    { $$ = "or"; }
                        ;

relational_operation    : EQ    { $$ = "="; }
                        | NEQ   { $$ = "/="; }
                        | LT    { $$ = "<"; }
                        | GT    { $$ = ">"; }
                        | GTE   { $$ = ">="; }
                        | LTE   { $$ = "<="; }
                        ;

adding_operation        : '+'   { $$ = "+"; }
                        | '-'   { $$ = "-"; }
                        ;

multiplying_operation   : '*'   { $$ = "*"; }
                        | '/'   { $$ = "/"; }
                        ;



//Accounts for where the exception occured in the program
exception_part          : exception_start exceptionList
                        | %empty
	                    ;

exception_start         : EXCEPTION
		                ;

exceptionList	        : exceptionList exceptHand
                        | exceptHand
	                   	;

exceptHand              : WHEN choice_sequence ARROW sequence_of_statements
                        ;

choice_sequence	        : choice_sequence '|' ID
                        | ID
		                | OTHERS
		                ;
%%
int main()
{
    //Ready to write to file
    output = fopen("AMI_Output.out", "w");

    //NOTE: First argument of add here does not matter. Get rid of it
    //stackOfTrees is initialized and declared at the top
    push(stackOfTrees, "O-C");
    add(stackOfTrees, 1, "integer");       //predefined
    add(stackOfTrees, 2, "boolean");       //predefined
    add(stackOfTrees, 3, "true");          //constant
    add(stackOfTrees, 4, "false");         //constant
    add(stackOfTrees, 5, "maxint");        //constant
    add(stackOfTrees, 6, "read");  //predefined (standard)
    add(stackOfTrees, 7, "write"); //predefined (standard)
    
    add(stackOfTrees, 8, "array");    //????

    Node* intNode = localSearch(stackOfTrees[top].rootPointer, "integer");
    Node* boolNode = localSearch(stackOfTrees[top].rootPointer, "boolean");
    Node* trueNode = localSearch(stackOfTrees[top].rootPointer, "true");
    Node* falseNode = localSearch(stackOfTrees[top].rootPointer, "false");
    Node* maxintNode = localSearch(stackOfTrees[top].rootPointer, "maxint");
    Node* readRoutineNode = localSearch(stackOfTrees[top].rootPointer, "read");
    Node* writeRoutineNode = localSearch(stackOfTrees[top].rootPointer, "write");
    
    Node* arrayTypeNode = localSearch(stackOfTrees[top].rootPointer, "array");  //???? May need to change


    intNode->kind =   type;   //enum 4
    boolNode->kind =  type;   //enum 4
    trueNode->kind =  value;  //enum 5 
    falseNode->kind = value;  //enum 5
    maxintNode->kind = value; //enum 5
    readRoutineNode->kind =  read_routine;    // enum 7
    writeRoutineNode->kind = write_routine;   //enum 8
    
    arrayTypeNode->kind = array_type;   // enum 9
    

    intNode->offset = 1;     //int takes up 1 piece of memory
    boolNode->offset = 1;    //bool takes up 1 piece of memory

    intNode->memorySpace = 1;
    boolNode->memorySpace = 1;
    
    trueNode->offset = 1;    //default
    falseNode->offset = 1;   //default
    maxintNode->offset = 1;  //default
    readRoutineNode->offset = 1;  //??? Amount of memory it takes up
    writeRoutineNode->offset = 1; //??? Amount of memory it takes up
    
    arrayTypeNode->offset = 1; //??? Must change later
    
    

    printf("Outer Context\nboolean - %s\n", returnKind(boolNode));
    printf("integer - %s\n", returnKind(intNode));
    printf("false - %s\n", returnKind(falseNode));
    printf("maxint - %s\n", returnKind(maxintNode));
    printf("true - %s\n", returnKind(trueNode));
    printf("read - %s\n", returnKind(readRoutineNode));
    printf("write - %s\n", returnKind(writeRoutineNode));
    
    printf("array - %s\n", returnKind(arrayTypeNode));


    //Record to keep track of all the counters, offsets
    globalRecord.pc = 0;      //start at r1
    globalRecord.registerNumber = 1;


    
    yyparse();

    //Ready to Close File
    fclose(output);
}










/*

//Alternative to current implementation of full else if statements
// Will need to use a separate stack for just cond jumps if you want to implement full else if statements using this
// grammar

if_statement            : if_start initial THEN sequence_of_statements else_if else ENDIF
                                        {
                                   
                                          //UPDATE patch list by apending the patchlines from the topmost linked list AND the current pc
                                            printf("Here is the updated patch list (FOR PRODUCTION) for this procedure: \n");
                                            ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                            while (tempHead != NULL) {
                                                patchList = appendToList(patchList, tempHead->patchLine, globalRecord.pc);
                                                tempHead = tempHead->next;
                                            }
                                            printAllNodes(patchList);
                                            
                                            
                                            popList(stackOfLL);
                                        }
                        ;

if_start                : IF //{ pushList(stackOfLL); } //pushList(stackOfLL); } //for Pc jumps
                        ;

initial                 : condition
                                        {
                                            pushList(stackOfLL);// For cond jumps
                                            
                                            putInToList(stackOfLL, globalRecord.pc); //NEW
                                            
                                            fprintf(output, "%d: pc := ? if not r%d\n", globalRecord.pc++, $1->registerNumber);
                                        }
                        ;

condition               : expression 
                                        {
                                            $$ = $1;  //Pass up the ptr to the record  
                                        }
                        ;
                        

else_if                 : else_if else_if_start initial THEN sequence_of_statements
                                        {

                                            This is to patch the pc jumps
                                            ListNodePtr tempHead = stackOfLL[patchTopIndex].leaveAddressPtr;
                                            if (tempHead != NULL){
                                            patchList = appendToList(patchList, tempHead->patchLine, $2);
                                                fprintf(output, "*@*#*$@#*$**#@$*");
                                             }
                                            
                                            
                                            //Tells you which pc line number to jump to once you successfully processed the sequence of statements
                                            //Should be at the very end of the if else if else clause
                                            //fprintf(output, "%d: pc := ?\n", globalRecord.pc++);
                                            popList(stackOfLL);
                                           
                                        }
                        | %empty
                        ;


else_if_start           : ELSEIF
                                        {                                                 
                                            putInToList(stackOfLL, globalRecord.pc);
                                            fprintf(output, "%d: pc := ?\n", globalRecord.pc++);
                                            $$ = globalRecord.pc; 
                                        }
                        ;


else                    : else_start sequence_of_statements
                                        {
                                            
                                        }
                        | %empty
                        ;


else_start              : ELSE
                                        {
                                            putInToList(stackOfLL, globalRecord.pc);
                                            fprintf(output, "%d: pc := ?\n", globalRecord.pc++);
                                            $$ = globalRecord.pc;
                                        }
                        ;

*/
