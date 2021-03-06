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
ListELEM stackOfLL[200]; //toPatch is a stack of Linked Lists
ListNodePtr patchList;   // Patch List


 
FILE *output;      //Write to file so you can test output code with AMI
extern int lineno; //Line number here is the instruction for part 3
%}

%token IS BEG END PROCEDURE ID NUMBER TYPE ARRAY RAISE OTHERS
%token RECORD IN OUT RANGE CONSTANT ASSIGN EXCEPTION NULLWORD LOOP IF
%token THEN ELSEIF ELSE EXIT WHEN AND OR EQ NEQ LT GT GTE LTE TICK
%token NOT EXP ARROW OF DOTDOT ENDIF ENDREC ENDLOOP EXITWHEN

%type <integer>         NUMBER   constant    declarative_part    declarative_part_prime  main_begin   procedure_begin    loop_start
%type <var>             ID   type_name   mode   IN   OUT    adding_operation   multiplying_operation   relational_operation  boolean_operation  name 
%type <listPointer>     identifier_list 
%type <nodePtr>         parameters   formal_parameter_part   procedure_specification    procedure_body_prime
%type <argumentRecord>  primary  factor  term  simple_expression  relation  expression   expression_list   condition

%union {
    int integer;
    char *var;
    struct idnode* listPointer;//pointer for the list of Ids
    struct node* nodePtr;
    struct Record* argumentRecord;
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
declarative_part        : objects ';' declarative_part      { $$ = returnOffSet(stackOffSet); }
                        | types ';' declarative_part        { $$ = returnOffSet(stackOffSet); }
                        | exceptions ';' declarative_part   { $$ = returnOffSet(stackOffSet); }
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
                                                                                                if (globalSearch(stackOfTrees, $11) != NULL) {
                                                                                                    
                                                                                                    //Add the ID (array) to the stack
                                                                                                    add(stackOfTrees, 0, $2);
                                                                                                    Node* first = localSearch(stackOfTrees[top].rootPointer, $2);

                                                                                                    //QUESTION: Do I make the p_t, c_t or both be a pointer to the type_name? 
                                                                                                    first->component_type = globalSearch(stackOfTrees, $11);
                                                                                                    first->kind = type;  //enum is type
                                                                                                    first->lower = $6;
                                                                                                    first->upper = $8;
                                                                                                }
                                                                                            }


                                                                                            
                                                                                           }
                        | TYPE ID IS RECORD component_list ENDREC
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

component_list          : component ';' component_list
                        | component ';'
                        ;

component               : objects
                        ;

objects                 : identifier_list ':' type_name 		{ 
                                                                 printf("line#:  %d - ", lineno);
                                                                 printRoutine($1);
                                                                 idnodeptr traverseList = $1;
                                                                 printf(": %s\n", $3);


                                                                 while (traverseList != NULL){
                                                                     
                                                                     //Duplicates in the current tree
                                                                     if (localSearch(stackOfTrees[top].rootPointer, traverseList->name) != NULL) {
                                                                         printf("ERROR: Duplicate IDs\n");
                                                                     }
                                                                     else{
                                                                         //Found variable type in the outer context so insert into topmost binary tree
                                                                         if (globalSearch(stackOfTrees, $3) != NULL) {
                                                                             //Add the variable to the stack (example a)
                                                                             add(stackOfTrees, 0, traverseList->name);
                                                                             Node* first = localSearch(stackOfTrees[top].rootPointer, traverseList->name);

                                                                             //update variables from node struct
                                                                             first->parent_type = globalSearch(stackOfTrees, $3);
                                                                             first->kind = variable;       //kind is variable so enum is 3
                                                                             
                                                                             //Will have to do two lines and incrememnt by parent_type->offset
                                                                             //first->offset = globalRecord.offset++;  
																
                                                                             //Set outcome->offset equal to the current offset
                                                                             first->offset = returnOffSet(stackOffSet);
                                                                             //Increment globalOfsset by first->parent_type->offset
                                                                             raiseOffSet(stackOffSet, first->parent_type->offset);
                                                                             
                                                                         }
                                                                     }
                  
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

statement_sequence_prime: NULLWORD
                        //TODO: EMIT a Store instruction
                        | ID ASSIGN expression                {
                                                                
                                                                struct node* variableInTree = globalSearch(stackOfTrees, $1);
                                                                int walkBackCount = countGlobalSearch(stackOfTrees, $1);

                                                                
                                                                //Handles LOCAL variables in the LEFT-HAND side of an ASSIGNMENT
                                                                if (walkBackCount == 0) {
                                                                    //******** Maybe do this instead of the line below it **********/
                                                                    //Do nothing!
                                                                    //variableInTree->registerNumber = $3->registerNumber;    //NEW: to account for EXP and rel_op

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
                                                                            fprintf(output, "%d: r%d := contents r%d, 2\n", globalRecord.pc++, globalRecord.registerNumber, globalRecord.registerNumber);
                                                                            walkBackCount--;
                                                                        }

                                                                        //Ex. contents r2, 5 := contents b, 4  or contents r3, 5 := contents r2, 6
                                                                        fprintf(output, "%d: contents r%d, %d := ", globalRecord.pc++, globalRecord.registerNumber++, nodeInTree->offset);
                                                                    }
                                                                    else
                                                                        printf("Error: Check your statement_sequence_prime -> ID ASSIGN expression production");
                                                                }


                                                                //For the RIGHT HAND side of an ASSIGNMENT
                                                                // For global variables (true && true) on right hand side
                                                                if ($3->isRegister && $3->isMemAddress)
                                                                    fprintf(output, "contents r%d, %d\n", $3->registerNumber, $3->offset);
                                                                // For local variables (false && true) on right hand side
                                                                else if (!$3->isRegister && $3->isMemAddress)
                                                                    fprintf(output, "contents b, %d\n", $3->offset);
                                                                // For number and boolean literals (true && false) on the right hand side
                                                                else if ($3->isRegister && !$3->isMemAddress) {
                                                                    fprintf(output, "r%d\n", $3->registerNumber);
                                                                    /*
                                                                    if      ($3->value == 2)  fprintf(output, "true\n");
                                                                    else if ($3->value == 1)  fprintf(output, "false\n");
                                                                    else                      fprintf(output, "r%d\n", $3->registerNumber);
                                                                    */
                                                                           
                                                                }
                                                              

                                                                
                                                              } //end of production

                        | name                                {
                                                                struct node* procNodeInTree = globalSearch(stackOfTrees, $1);
                                                                //fprintf(output, "************* %s ***************\n", procNodeInTree->symbol);

                                                                //a read or write routine
                                                                if (procNodeInTree->kind == read_routine || procNodeInTree->kind == write_routine) {
                                                                     //Do nothing
                                                                }

                                                                // a procedure so calculate static, dynamic, next base, and return address
                                                                else if (procNodeInTree->kind == procedure) {
                                                                    
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
                                                                        fprintf(output, "%d: r%d := contents r%d, 2\n", globalRecord.pc++, globalRecord.registerNumber, registerHolder);
                                                                        walkBackCount--;
                                                                        
                                                                        while (walkBackCount != 0){
                                                                            fprintf(output, "%d: r%d := contents r%d, 2\n",  globalRecord.pc++, globalRecord.registerNumber, globalRecord.registerNumber);
                                                                            walkBackCount--;
                                                                        }
                                                                        //fprintf(output, "%d: contents b, 2 := r%d\n", globalRecord.pc++, globalRecord.registerNumber++);
                                                                    }
                                                                    fprintf(output, "%d: contents b, 2 := r%d\n", globalRecord.pc++, globalRecord.registerNumber++);

                                                                    
                                                                    //Calculate next base of AR //Figure out the offset of the next procedure
                                                                    fprintf(output, "%d: r%d := %d**********\n", globalRecord.pc++, globalRecord.registerNumber, procNodeInTree->offset);
                                                                    fprintf(output, "%d: contents b, 0 := b + r%d\n", globalRecord.pc++, globalRecord.registerNumber++);                                                                    
                                                                    //Return Address //Jump to pc count
                                                                    fprintf(output, "%d: r%d := %d\n", globalRecord.pc++, globalRecord.registerNumber, globalRecord.pc + 3);
                                                                    fprintf(output, "%d: contents b, 1 := r%d\n", globalRecord.pc++, globalRecord.registerNumber++);
                                                                    
                                                                    //Call to Nest //Place the offset of procedure inside of symbol Table node
                                                                    fprintf(output, "%d: pc := %d \n", globalRecord.pc++, procNodeInTree->procStart);

                                                                } // end of else if (procNodeInTree->kind == procedure)

                                                                    

                                                              }
                        | loop_part
                        | if_statement
                        | RAISE ID
                        ;

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
if_statement            : IF initial THEN sequence_of_statements else_if else ENDIF
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

initial                 : condition
                                        {
                                            fprintf(output, "%d: pc := ? if not r%d\n", globalRecord.pc, $1->registerNumber);
                                            
                                            pushList(stackOfLL);
                                            putInToList(stackOfLL, globalRecord.pc++);   // Remembers which pc line to patch
                                        }
                        ;

condition               : expression 
                                        {
                                            $$ = $1;  //Pass up the ptr to the record  
                                        }
                        ;
                        

else_if                 : ELSEIF condition THEN sequence_of_statements else_if
                        | %empty
                                        {
                                           //pushList(stackOfLL);
                                            
                                           //$$ = globalRecord.pc; //Skips to the end of the else statement in case the if codition does nothing
                                        }
                        ;


else                    : ELSE sequence_of_statements
                        | %empty
                        ;




//Expressions in Ada
//TODO: EMIT instructions
expression_list         : expression ',' expression_list                       { } 
                        | expression                                           { $$ = $1; }
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
                                                                             else                  fprintf(output, "contents b, %d\n", $3->offset);                       //Local Variable
                                                                         }
                                                                         else {
                                                                             if ($3->isRegister)    fprintf(output, "r%d\n", $3->registerNumber); // Literals (boolean or ints etc.)
                                                                             else                   fprintf(output, "ERROR in ada.y, term : term multiplying_operation factor\n");
                                                                         }
                            
                                                                         $$ = resultInfo;
                                                                      }
                        ;

factor                  : primary                    { $$ = $1;   //printf("register number:%d, register offset:%d\n", $1->registerNumber, $1->offset);
                                                     }
                        | primary  EXP  primary      {
                                                       //TODO: Emit several Argument Arithmetic instructions
                                                       //This records register number will continously update in a loop
							                           /*
							                           printf("r%d  r%d\n", $1->registerNumber, $3->registerNumber);

                                                       //If $1  or $3 is a variale then move contents into a register
                                                       if (!$1->isRegister)
                                                         ;

                                                         if (!$3->isRegister)
                                                         ;

                                                       recordptr currentRecord = createRecord();
                                                       currentRecord->registerNumber = globalRecord.registerNumber++;
                                                       */
                                                       //fprintf(output, "%d: r%d := ", globalRecord.offset++, currentRecord->registerNumber, );
                                                       
                                                       
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

                                                       // NOTE: IF YOU WANT TO DISTINGUISH BETWEEN integer, boolean THEN PLACE A ENUMERATION TYPE IN YOUR RECORDS
                                                       //Handles true and false literals
                                                       if (nodeInTree->kind == value) { //value is an enum 5
                                                           //TODO:
                                                           //true and false do not have offset
                                                           variableInfo->registerNumber = globalRecord.registerNumber++; //ONLY KEEP THIS IF YOU WANT TO PUT TRUE INTO A REGISTER
                                                           variableInfo->isRegister = true;
                                                           variableInfo->isMemAddress = false;

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
                                                           variableInfo->offset = nodeInTree->offset;
                                                           
                                                           //****** Maybe do this instead of the line below it ****/
                                                           //variableInfo->registerNumber = globalRecord.registerNumber++;
                                                           
                                                           //Causes problems if a := 5; b := a; a = b; //NEW to account for exp and rel operations
                                                           //variableInfo->registerNumber = nodeInTree->registerNumber;  
                                                           variableInfo->isRegister = false;         // local variables are NOT stored in a register
                                                           variableInfo->isMemAddress = true;        // MUST DISPLAY contents b, 4 etc. for local variables
                                                           // variableInfo->offset = nodeInTree->parent_type->memSize;
                                                       }
                                                       //TODO: DOUBLE CHECK Handles GLOBAL variables in the right hand side of an assignment
                                                       else {
                                                              variableInfo->offset = nodeInTree->offset;
                                                              variableInfo->registerNumber = globalRecord.registerNumber;
                                                              variableInfo->isRegister = true;      // Want to walk back using a register  r2 := b then r2 := contents r2, 2
                                                              variableInfo->isMemAddress = true;    // THIS WILL BE STORED IN A REGISTER BECAUSE OF REQUIRED WALK BACK
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

    
    //stackOfTrees is initialized and declared at the top
    push(stackOfTrees, "O-C");
    add(stackOfTrees, 1, "integer");       //predefined
    add(stackOfTrees, 2, "boolean");       //predefined
    add(stackOfTrees, 3, "true");          //constant
    add(stackOfTrees, 4, "false");         //constant
    add(stackOfTrees, 5, "maxint");        //constant
    add(stackOfTrees, 6, "read");  //predefined (standard)
    add(stackOfTrees, 7, "write"); //predefined (standard)
    //add(stackOfTrees, 8, "array_type");    //????

    Node* intNode = localSearch(stackOfTrees[top].rootPointer, "integer");
    Node* boolNode = localSearch(stackOfTrees[top].rootPointer, "boolean");
    Node* trueNode = localSearch(stackOfTrees[top].rootPointer, "true");
    Node* falseNode = localSearch(stackOfTrees[top].rootPointer, "false");
    Node* maxintNode = localSearch(stackOfTrees[top].rootPointer, "maxint");
    Node* readRoutineNode = localSearch(stackOfTrees[top].rootPointer, "read");
    Node* writeRoutineNode = localSearch(stackOfTrees[top].rootPointer, "write");
    //Node* arrayTypeNode = localSearch(stackOfTrees[top].rootPointer, "array_type");


    intNode->kind =   type;   //enum 4
    boolNode->kind =  type;   //enum 4
    trueNode->kind =  value;  //enum 5 
    falseNode->kind = value;  //enum 5
    maxintNode->kind = value; //enum 5
    readRoutineNode->kind =  read_routine;    // enum 
    writeRoutineNode->kind = write_routine;   //enum 
    //arrayTypeNode->kind = 
    

    intNode->offset = 1;     //int takes up 1 piece of memory
    boolNode->offset = 1;    //bool takes up 1 piece of memory
    trueNode->offset = 1;    //default
    falseNode->offset = 1;   //default
    maxintNode->offset = 1;  //default
    readRoutineNode->offset = 1;  //Amount of memory it takes up ???
    writeRoutineNode->offset = 1; //Amount of memory it takes up ???
    
    

    printf("Outer Context\nboolean - %s\n", returnKind(boolNode));
    printf("integer - %s\n", returnKind(intNode));
    printf("false - %s\n", returnKind(falseNode));
    printf("maxint - %s\n", returnKind(maxintNode));
    printf("true - %s\n", returnKind(trueNode));
    printf("read - %s\n", returnKind(readRoutineNode));
    printf("write - %s\n", returnKind(writeRoutineNode));


    //Record to keep track of all the counters, offsets
    globalRecord.pc = 0;      //start at r1
    globalRecord.registerNumber = 1;


    
    yyparse();

    //Ready to Close File
    fclose(output);
}























//All printing done in expression list







//NOTE: Can Erase anytime you want
//Expressions in Ada
//TODO: EMIT instructions
/*
expression_list         : expression ',' expression_list 
                        | expression
                        ;

expression              : relation expression_prime
                        ;

expression_prime        : boolean_operation relation expression_prime
                        | %empty
                        ;

relation                : simple_expression relation_prime
;

relation_prime          : relational_operation simple_expression relation_prime
                        : %empty
                        ;

simple_expression       : simple_minus term simple_expression_prime
                        ;

simple_minus            : '-'
                        | %empty
                        ;

simple_expression_prime : adding_operation term simple_expression_prime
                        | %empty
                        ;

term                    : factor term_prime
                        ;

term_prime              : multiplying_operation factor term_prime
                        | %empty
                        ;

factor                  : primary factor_prime
                        | NOT primary
                        ;

factor_prime            : EXP primary factor_prime
                        | %empty
                        ;

primary                 : NUMBER
                        | ID
                        | '(' expression ')'
                        ;
*/






                                                                         /*CAN ERASE ANYTIME  //Stores value of operation into current record s_e -> s_e a_o term
                                                                         if (strcmp($2, "+") == 0)      resultInfo->value = $1->value + $3->value;
                                                                         else if (strcmp($2, "-") == 0) resultInfo->value = $1->value - $3->value;
                                                                         else                           printf("Error. Check your simple_expression production.");
                                                                         */

                                                                         /* ERASE ANYTIME   term -> term m_o factor
                                                                         if (strcmp($2, "*") == 0)       resultInfo->value = $1->value * $3->value;
                                                                         else if (strcmp($2, "/") == 0) resultInfo->value = $1->value / $3->value;
                                                                         else                            printf("Error. Check your term production.");
                                                                         */

                                                                                /* CAN ERASE ANYTIME   relation -> relation r_o s_e
                                                                                 if (!strcmp($2, "="))
                                                                                     resultInfo->value = ($1->value == $3->value);
                                                                                 else if (!strcmp($2, "/="))
                                                                                     resultInfo->value = ($1->value != $3->value);
                                                                                 else if(!strcmp($2, "<"))
                                                                                     resultInfo->value = ($1->value < $3->value);                                                                          
                                                                                 else if(!strcmp($2, "<="))
                                                                                     resultInfo->value = ($1->value <= $3->value);
                                                                                 else if(!strcmp($2, ">"))
                                                                                     resultInfo->value = ($1->value > $3->value);
                                                                                 else if(!strcmp($2, ">="))
                                                                                     resultInfo->value = ($1->value >= $3->value);
                                                                                 else
                                                                                     printf("Error. Check your relation production.");
                                                                                 */


                                                   /* ID ASSIGN expression

                                                                struct node* variableInTree = globalSearch(stackOfTrees, $1);
                                                                // variableInTree->val = $3->value;


                                                                //printf("FIRST**name: %s    offset: %d *****register: %d  ****\n", variableInTree->symbol, variableInTree->offset, variableInTree->registerNumber);

                                                                // If it is a register then its the first time your seeing this assignment. Ex. a := 3
                                                                // so you want to insert this value into the symbol table node
                                                                
                                                                if ($3->offset != 0) {
                                                                    variableInTree->offset = $3->offset;
                                                                }
                                                                
                                                                variableInTree->registerNumber = $3->registerNumber;    //NEW: to account for EXP and rel_op
                                                                //printf("SECOND**name: %s    offset: %d *****register: %d  ****\n", variableInTree->symbol, variableInTree->offset, variableInTree->registerNumber);


                                                                //If it is not a register then you've seen this and you dont want to insert so dont change variableInTree->offset
                                                                //EMIT a Store instruction
                                                                fprintf(output, "%d: contents b, %d := r%d\n", globalRecord.pc++, variableInTree->offset, $3->registerNumber);
                                                                */
