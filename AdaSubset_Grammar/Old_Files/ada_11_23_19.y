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
 
//GLOBAL VARIABLES 
TreeELEM stackOfTrees[20];
struct GlobalRecord globalRecord;


 
FILE *output;      //Write to file so you can test output code with AMI
extern int lineno; //Line number here is the instruction for part 3
%}

%token IS BEG END PROCEDURE ID NUMBER TYPE ARRAY RAISE OTHERS
%token RECORD IN OUT RANGE CONSTANT ASSIGN EXCEPTION NULLWORD LOOP IF
%token THEN ELSEIF ELSE EXIT WHEN AND OR EQ NEQ LT GT GTE LTE TICK
%token NOT EXP ARROW OF DOTDOT ENDIF ENDREC ENDLOOP EXITWHEN

%type <integer>         NUMBER   constant    declarative_part    declarative_part_prime   begin
%type <var>             ID   type_name   mode   IN   OUT    adding_operation   multiplying_operation   relational_operation  boolean_operation  name 
%type <listPointer>     identifier_list 
%type <nodePtr>         parameters   formal_parameter_part   procedure_specification    procedure_body_prime
%type <argumentRecord>  primary  factor  term  simple_expression  relation  expression

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
                          declarative_part BEG
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
                                                                           
                                                                           //POP: Procedure is finished so don't need this offset anymore
                                                                           popOffSet(stackOffSet);

                                                                          } //Want to pop here because we're at the end of a statement 
                        ;

main_specification      : PROCEDURE ID                                    {
                                                                           push(stackOfTrees, $2);  //PUSH new binaryTree onto stack
                                                                           pushOffSet(stackOffSet); //PUSH new offset onto stack because of new procedure

                                                                           //Record the current instruction counter

                                                                           //ABSTRACT MACHINE INSTRUCTIONS
                                                                           fprintf(output, "%d: b := ?\n", globalRecord.pc++);
                                                                           fprintf(output, "%d: contents b, 0 := ?\n", globalRecord.pc++);
                                                                           fprintf(output, "%d: contents b, 1 := ?\n", globalRecord.pc++);
                                                                           fprintf(output, "%d: pc := ?\n", globalRecord.pc++);
                                                                           fprintf(output, "%d: halt\n", globalRecord.pc++);
                                                                           

                                                                           
                                                                          }
                        ;

procedure_body          : procedure_body_prime IS                         
                          declarative_part begin
                          sequence_of_statements
                          exception_part END ';'                          {
                                                                           struct node* ptrToProcedureNode = $1; //REPLACED
                                                                           //struct node* procNodeInTree = globalSearch(stackOfTrees, $1);  //NEW
                                                                           //procNodeInTree->procStart = $4;                                //NEW

                                                                           //Only new line added aside from the begin production, to get correct pc count
                                                                           ptrToProcedureNode->procStart = $4;

                                                                           
                                                                           //POP: Procedure is finished so don't need this Binary Tree anymore
                                                                           printf("\nPopping scope for %s, so print tree\n", ptrToProcedureNode->symbol);  //REPLACED
                                                                           //printf("\nPopping scope for %s, so print tree\n", procNodeInTree->symbol);        //NEW
                                                                           printDFS(stackOfTrees[top].rootPointer);
                                                                           pop(stackOfTrees);  

                                                                           //NEED For AMI to calculate size of procedure //i.e. $3 is 4 bookeeping plus any other variables
                                                                           ptrToProcedureNode->offset = $3;  //REPLACED
                                                                           //procNodeInTree->offset = $3;        //NEW
                                                                           
                                                                           //EPLIOGUE for procedures in main 
                                                                           //1)get return adress 2)get dynamic link and 3)update pc count
                                                                           fprintf(output, "%d: r%d := contents b, 1\n", globalRecord.pc++, globalRecord.registerNumber);
                                                                           fprintf(output, "%d: b := contents b, 3\n", globalRecord.pc++);
                                                                           fprintf(output, "%d: pc := r%d\n", globalRecord.pc++, globalRecord.registerNumber++);

                                                                           fprintf(output, "******** START OF AMI for PROCEDURE *******\n");//: %s *****************\n", ptrToProcedureNode->symbol);
                                                                           
                                                                           //POP: Procedure is finished so don't need this offset anymore
                                                                           popOffSet(stackOffSet);
                                                                          }
                        ;

begin                   : BEG   { $$ = globalRecord.pc; }

procedure_body_prime    : procedure_specification formal_parameter_part   {

                                                                           //Updated version accounts for duplicates and connects precedure node to the formal parameters in the next binary tree
                                                                            struct node* treeNodeList = $2;          // treeNodeList is not in the binary tree, its a copy    
                                                                            struct node* ptrToProcedureNode = $1;
                                                                            ptrToProcedureNode->next = treeNodeList; //connect Y1's next pointer to first formal parameter of the copy list//
                                                                            ptrToProcedureNode->kind = 2;            //kind is a procedure so enum value is 2
                                                                                
                                                                            struct node* currentNode;
                                                                            while (treeNodeList != NULL){
                                                                               
                                                                                //Duplicate Found so don't add to topmost stack
                                                                                if (localSearch(stackOfTrees[top].rootPointer, treeNodeList->symbol) != NULL) { //A
                                                                                    printf("ERROR: Duplicate IDs name: %s with parent_type: %s, component_type: %s was not inserted into the symbol table\n", treeNodeList->symbol, treeNodeList->parent_type->symbol, treeNodeList->component_type->symbol);

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

procedure_specification : PROCEDURE ID                                    { 
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
                                                                           currentNode->kind = 3;                                     //kind is variable, so enum is 3

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
                                                                               currentNode->kind = 3;                                     //kind is variable, so enum is 3
                                                                               
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
                                                                           currentNode->kind = 3;                                     //kind is variable, so enum is 3

                                                                           listToPassUp = currentNode;                                //Now I can have currentNode point to something else
                                                                           linkedList = linkedList->next;                             //if Null then currentNode->next = NULL
                                                                           
                                                                           while (linkedList != NULL){
                                                                               //Have the next of the previous node point to the newly created node
                                                                               currentNode->next = createNode(0, linkedList->name);       
                                                                               currentNode = currentNode->next;                           //update pointer of currentNode
                                                                               currentNode->mode = (char*) malloc(sizeof($3) + 1);
                                                                               strcpy(currentNode->mode, $3);
                                                                               currentNode->parent_type = globalSearch(stackOfTrees, $4); //w is the parent_type
                                                                               currentNode->kind = 3;                                     //kind is variable, so enum is 3 
                                                                               
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
                                                                                                    first->kind = 4;  //enum is type
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
                                                                 first->kind = 4;  // kind is type so enum is 4
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
                                                                             first->kind = 3;                   //kind is variable so enum is 3
                                                                             
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

                                                                             first->kind = 6;         //kind is exception so enum is 6
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

                                                                
                                                                //Handles LOCAL variables in the left hand side of an assignment
                                                                if (walkBackCount == 0) {
                                                                    variableInTree->registerNumber = $3->registerNumber;    //NEW: to account for EXP and rel_op
                                                                    
                                                                    //OLD (WORKING)
                                                                    //fprintf(output, "%d: contents b, %d := r%d\n", globalRecord.pc++, variableInTree->offset, $3->registerNumber); 

                                                                    //NEW (????)
                                                                    // For literals (true && false) and variables (false && true) on the right hand side  
                                                                    if (($3->registerNumber && !$3->isMemAddress) || (!$3->registerNumber && $3->isMemAddress)) {
                                                                        // NEW (?????)enum is 5, handles true and false
                                                                        if ($3->value == 2)
                                                                            fprintf(output, "%d: contents b, %d := true\n", globalRecord.pc++, variableInTree->offset);
                                                                        else if ($3->value == 1)
                                                                            fprintf(output, "%d: contents b, %d := false\n", globalRecord.pc++, variableInTree->offset);
                                                                        //OLD (Working) For literal numbers and variables 
                                                                        else
                                                                            fprintf(output, "%d: contents b, %d := r%d\n", globalRecord.pc++, variableInTree->offset, $3->registerNumber);
                                                                        
                                                                    }
                                                                    // For Non-Local variables (true && true) on the right hand side
                                                                    else if ($3->registerNumber && $3->isMemAddress)
                                                                        fprintf(output, "%d: contents b, %d := contents r%d, %d\n", globalRecord.pc++, variableInTree->offset, $3->registerNumber, $3->offset);
                                                                    
                                                                }
                                                                //Handles NON-LOCAL variables in the left hand side of the assignment
                                                                else {
                                                                    struct node* nodeInTree = globalSearch(stackOfTrees, $1);
                                                                    if (nodeInTree != NULL){

                                                                        //r2 := b
                                                                        fprintf(output, "%d: r%d := b\n", globalRecord.pc++, globalRecord.registerNumber);
                                                                        
                                                                        //Loop updates the register and static link  Ex. r2 := contents r2, 2
                                                                        while (walkBackCount != 0){
                                                                            fprintf(output, "%d: r%d := contents r%d, 2\n", globalRecord.pc++, globalRecord.registerNumber, globalRecord.registerNumber);
                                                                            walkBackCount--;
                                                                        }

                                                                        //Ex. contents r2, 5 := contents b, 4  or contents r3, 5 := contents r2, 6
                                                                        fprintf(output, "%d: contents r%d, %d := ", globalRecord.pc++, globalRecord.registerNumber++, nodeInTree->offset);
                                                                        
                                                                        //OLD (WORKING)
                                                                        /* if ($3->isRegister)
                                                                            fprintf(output, "contents r%d, %d\n", $3->registerNumber, $3->offset); // For global variables on right hand side
                                                                        else
                                                                            fprintf(output, "contents b, %d\n", $3->offset);   //For local variables on right hand side
                                                                        */


                                                                        
                                                                        //NEW (????????)
                                                                        // For global variables (true && true) on right hand side
                                                                        if ($3->isRegister && $3->isMemAddress)
                                                                            fprintf(output, "contents r%d, %d\n", $3->registerNumber, $3->offset);
                                                                        // For local variables (false && true) on right hand side
                                                                        else if (!$3->isRegister && $3->isMemAddress)
                                                                            fprintf(output, "contents b, %d\n", $3->offset);
                                                                        // For number and boolean literals (true && false) on the right hand side
                                                                        else if ($3->isRegister && !$3->isMemAddress){
                                                                            if      ($3->value == 2)  fprintf(output, "true\n");
                                                                            else if ($3->value == 1)  fprintf(output, "false\n");
                                                                            else                      fprintf(output, "r%d\n", $3->registerNumber);
                                                                           
                                                                        }
                                                                        
                                                                        
                                                                    }
                                                                    else
                                                                        printf("Error: Check your statement_sequence_prime -> ID ASSIGN expression production");
                                                                }
                                                              
                                                               
                                                              }
                        | name                                {
                                                                    struct node* procNodeInTree = globalSearch(stackOfTrees, $1);
                                                                    //fprintf(output, "************* %d ***************\n", procNodeInTree->offset);
                            
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
                                                                    fprintf(output, "%d: r%d := %d**********\n", globalRecord.pc++, globalRecord.registerNumber, procNodeInTree->offset);//returnOffSet(stackOffSet)
                                                                    fprintf(output, "%d: contents b, 0 := b + r%d\n", globalRecord.pc++, globalRecord.registerNumber++);                                                                    
                                                                    //Return Address //Jump to pc count
                                                                    fprintf(output, "%d: r%d := %d\n", globalRecord.pc++, globalRecord.registerNumber, globalRecord.pc + 3);
                                                                    fprintf(output, "%d: contents b, 1 := r%d\n", globalRecord.pc++, globalRecord.registerNumber++);
                                                                    
                                                                    //Call to Nest //Place the offset of procedure inside of symbol Table node
                                                                    fprintf(output, "%d: pc := %d \n", globalRecord.pc++, procNodeInTree->procStart);

                                                              }
                        | loop_part
                        | if_statement
                        | RAISE ID
                        ;

name                    : ID                                  { $$ = $1; }
                        | ID '(' expression_list ')'          { $$ = $1 ;}
                        ;


//Accounts for where the loop begins and ends in the program
loop_part               : loop_start loop_stmt_list ENDLOOP
                        ;
loop_start              : LOOP
                        ;
loop_stmt_list          : loop_stmt ';' loop_stmt_list
                        | loop_stmt ';'
                        ;
loop_stmt               : statement_sequence_prime 
                        | when_condition
                        ;
when_condition          : EXITWHEN condition
                        | EXIT
                        ;


//Accounts for where the if statement begins and ends in the program
if_statement            : IF condition then_cond sequence_of_statements else_if else ENDIF
                        ;
else_if                 : ELSEIF condition THEN sequence_of_statements else_if
                        | %empty
                        ;
then_cond               : THEN
                        ;
else                    : ELSE sequence_of_statements
                        | %empty
                        ;
condition               : expression  
                        ;



//Expressions in Ada
//TODO: EMIT instructions
expression_list         : expression ',' expression_list 
                        | expression
                        ;

expression              : relation                                             { $$ = $1; } 
                        | expression  boolean_operation  relation              {
                                                                                 /*
                                                                                  recordptr resultInfo = createRecord();
                                                                                  resultInfo->registerNumber = globalRecord.registerNumber++;
                                                                                  resultInfo->isRegister = true;

                                                                                  //Prints Pc counter
                                                                                  fprintf(output, "%d: r%d := ", globalRecord.pc++, resultInfo->registerNumber);

                                                                                  //Handles left hand side of operation
                                                                                  if ($1->isRegister) fprintf(output, "r%d ", $1->registerNumber);
                                                                                  else                fprintf(output, "contents b, %d ", $1->offset);
                                                                         
                                                                                  //Prints a AND or OR
                                                                                  fprintf(output, "%s ", $2);
                                                                         
                                                                                  //Handles righthand side of operation
                                                                                  if ($3->isRegister) fprintf(output, "r%d\n", $3->registerNumber);
                                                                                  else                fprintf(output, "contents b, %d \n", $3->offset);
                                                                                 */
                            
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

                                                                               }             //TODO: Emit an argument arithmetic instruction
                        ;

relation                : simple_expression                                    { $$ = $1; }
                        | relation  relational_operation  simple_expression    {            //TODO: Emit an ALU arithmetic instruction

                                                                                 recordptr resultInfo = createRecord();
                                                                                 resultInfo->registerNumber = globalRecord.registerNumber++;
                                                                                 resultInfo->isRegister = true;

                                                                                 
                                                                                 //Left Hand Side of AMI 
                                                                                 fprintf(output, "%d: r%d := ",  globalRecord.pc++, resultInfo->registerNumber);
                                                                                 
                                                                                 //Handles which symbol to use
                                                                                 //Right Hand side of AMI
                                                                                 if (strcmp($2, ">") == 0) {
                                                                                     //fprintf(output, "r%d < r%d\n", $3->registerNumber, $1->registerNumber);
                                                                                     //Handles left hand side of operation
                                                                                     if ($3->isRegister) fprintf(output, "r%d ", $3->registerNumber);
                                                                                     else                fprintf(output, "contents b, %d ", $3->offset);
                                                                         
                                                                                     //Prints a "<"
                                                                                     fprintf(output, "< ");
                                                                         
                                                                                     //Handles righthand side of operation
                                                                                     if ($1->isRegister) fprintf(output, "r%d\n", $1->registerNumber);
                                                                                     else                fprintf(output, "contents b, %d \n", $1->offset);
 
                                                                                 }
                                                                                 else if (strcmp($2, ">=") == 0) {
                                                                                     //fprintf(output, "r%d <= r%d\n", $3->registerNumber, $1->registerNumber);
                                                                                     //Handles left hand side of operation
                                                                                     if ($3->isRegister) fprintf(output, "r%d ", $3->registerNumber);
                                                                                     else                fprintf(output, "contents b, %d ", $3->offset);
                                                                         
                                                                                     //Prints a "<"
                                                                                     fprintf(output, "<= ");
                                                                         
                                                                                     //Handles righthand side of operation
                                                                                     if ($1->isRegister) fprintf(output, "r%d\n", $1->registerNumber);
                                                                                     else                fprintf(output, "contents b, %d \n", $1->offset);
                                                                                 }




                                                                                 
                                                                                 else {
                                                                                     //fprintf(output, "r%d %s r%d\n", $1->registerNumber, $2, $3->registerNumber);
                                                                                     //Handles left hand side of operation
                                                                                     if ($1->isRegister) fprintf(output, "r%d ", $1->registerNumber);
                                                                                     else                fprintf(output, "contents b, %d ", $1->offset);
                                                                         
                                                                                     //Prints a "<"
                                                                                     fprintf(output, "%s ", $2);
                                                                         
                                                                                     //Handles righthand side of operation
                                                                                     if ($3->isRegister) fprintf(output, "r%d\n", $3->registerNumber);
                                                                                     else                fprintf(output, "contents b, %d \n", $3->offset);
                                                                                 }



                                                                                     
                                                                                 

                                                                                 $$ = resultInfo;
                                                                               }
                        ;

simple_expression       : term                                        { $$ = $1; }
                        | '-' term                                    {
                                                                        //TODO: Emit an argument arithmetic instruction
                                                                        /*
                                                                        recordptr resultInfo = createRecord();
                                                                        resultInfo->registerNumber = globalRecord.registerNumber++;
                                                                        resultInfo->isRegister = true;

                                                                        fprintf(output, "%d: r%d := - ", globalRecord.pc++, resultInfo->registerNumber);
                                                                        
                                                                        //Right Hand side of AMI, either a variable (register) or literal (memAddress)
                                                                         if ($2->isRegister) fprintf(output, "r%d\n", $2->registerNumber);
                                                                         else                fprintf(output, "contents b, %d \n", $2->offset);
                                                                        */
                            
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
                                                                             if ($2->isRegister)    fprintf(output, "r%d\n", $2->registerNumber); // Literals (boolean or ints etc.)
                                                                             else                  fprintf(output, "ERROR in ada.y, s_e : - term\n");
                                                                         }

                                                                         
                                                                        $$ = resultInfo;
                                                                      }
                        | simple_expression  adding_operation  term   {
                                                                         /*
                                                                         recordptr resultInfo = createRecord();
                                                                         resultInfo->registerNumber = globalRecord.registerNumber++;
                                                                         resultInfo->isRegister = true;
                                                                         
                                                                         //Prints Pc counter
                                                                         fprintf(output, "%d: r%d := ", globalRecord.pc++, resultInfo->registerNumber);

                                                                         //Handles left hand side of operation
                                                                         if ($1->isRegister) fprintf(output, "r%d ", $1->registerNumber);
                                                                         else                fprintf(output, "contents b, %d ", $1->offset);
                                                                         
                                                                         //Prints a + or -
                                                                         fprintf(output, "%s ", $2);
                                                                         
                                                                         //Handles righthand side of operation
                                                                         if ($3->isRegister) fprintf(output, "r%d\n", $3->registerNumber);
                                                                         else                fprintf(output, "contents b, %d \n", $3->offset);
                                                                         */

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
                                                                       
                                                                        /*recordptr resultInfo = createRecord();
                                                                              
                                                                         resultInfo->registerNumber = globalRecord.registerNumber++;
                                                                         resultInfo->isRegister = true;
                                                                         fprintf(output, "%d: r%d := ", globalRecord.pc++, resultInfo->registerNumber);

                                                                         //Handles left hand side of operation
                                                                         if ($1->isRegister)  fprintf(output, "r%d ", $1->registerNumber);
                                                                         else                 fprintf(output, "contents b, %d ", $1->offset);
                                                                         
                                                                         //Prints out a * or a /
                                                                         fprintf(output, "%s ", $2);
                                                                         
                                                                         //Handles righthand side of operation
                                                                         if ($3->isRegister)  fprintf(output, "r%d\n", $3->registerNumber);
                                                                         else                 fprintf(output, "contents b, %d \n", $3->offset);
                                                                        */
                            
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
                                                      /* (OLD WORKING)
                                                      recordptr resultInfo = createRecord();
                                                      resultInfo->registerNumber = globalRecord.registerNumber++;
                                                      resultInfo->isRegister = true;

                                                      fprintf(output, "%d: r%d := not ", globalRecord.pc++, resultInfo->registerNumber);
                                                     
                                                      //Right Hand side of AMI, either a variable (register) or literal (memAddress)
                                                      if ($2->isRegister) fprintf(output, "r%d\n", $2->registerNumber);
                                                      else                fprintf(output, "contents b, %d \n", $2->offset);
                                                      */

                                                      //(NEW ?????????)
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
                                                       //if (strcmp($1, "true"))
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

                                                       //NEW NEW NEW (?????????)
                                                       //Handles true and false literals
                                                       if (nodeInTree->kind == value) { //value is an enum so actually a number
                                                           //TODO:
                                                           fprintf(output, "LOOOOOOOOOOOOOOOOOOOOOOOOK\n");
                                                           //true and false do not have offset
                                                           variableInfo->registerNumber = globalRecord.registerNumber++;
                                                           variableInfo->isRegister = true;
                                                           variableInfo->isMemAddress = false;
                                                           // accounts for true and false if statements in tree; enum 5
                                                           if (strcmp(nodeInTree->symbol, "true") == 0)
                                                               variableInfo->value = 2;
                                                           else if (strcmp(nodeInTree->symbol, "false") == 0)
                                                               variableInfo->value = 1; 
                                                       }                                                      
                                                       
                                                       //Handles LOCAL variables in the right hand side of an assignment
                                                       else if (walkBackCount == 0) {
                                                           variableInfo->offset = nodeInTree->offset;
                                                           variableInfo->registerNumber = nodeInTree->registerNumber;   //NEW
                                                           variableInfo->isRegister = false;         // local variables are NOT stored in a register
                                                           variableInfo->isMemAddress = true;        // MUST DISPLAY contents b, 4 etc. for local variables
                                                           // variableInfo->offset = nodeInTree->parent_type->memSize;
                                                       }
                                                       //TODO: DOUBLE CHECK Handles GLOBAL variables in the right hand side of an assignment
                                                       else {
                                                              //May not need this part
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
    add(stackOfTrees, 1, "integer"); //predefined
    add(stackOfTrees, 2, "boolean"); //predefined
    add(stackOfTrees, 3, "true");    //constant
    add(stackOfTrees, 4, "false");   //constant
    add(stackOfTrees, 5, "maxint");  //constant

    Node* intNode = localSearch(stackOfTrees[top].rootPointer, "integer");
    Node* boolNode = localSearch(stackOfTrees[top].rootPointer, "boolean");
    Node* trueNode = localSearch(stackOfTrees[top].rootPointer, "true");
    Node* falseNode = localSearch(stackOfTrees[top].rootPointer, "false");
    Node* maxintNode = localSearch(stackOfTrees[top].rootPointer, "maxint");

    intNode->kind = type;     //enum 4
    boolNode->kind = type;    //enum 4
    trueNode->kind = value;   //enum 5 
    falseNode->kind = value;  //enum 5
    maxintNode->kind = value; //enum 5

    intNode->offset = 1;     //int takes up 1 piece of memory
    boolNode->offset = 1;    //bool takes up 1 piece of memory
    trueNode->offset = 1;    //deafault
    falseNode->offset = 1;   //default
    maxintNode->offset = 1;  //default
    

    printf("Outer Context\nboolean - %s\n", returnKind(boolNode));
    printf("integer - %s\n", returnKind(intNode));
    printf("false - %s\n", returnKind(falseNode));
    printf("maxint - %s\n", returnKind(maxintNode));
    printf("true - %s\n", returnKind(trueNode));




    //Record to keep track of all the counters, offsets
    globalRecord.pc = 0;      //start at r1
    //globalRecord.offset = 4;  // 
    globalRecord.registerNumber = 1;
    //globalRecord.variableAddress = 0;
    
    yyparse();

    //Ready to Close File
    fclose(output);
}































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
