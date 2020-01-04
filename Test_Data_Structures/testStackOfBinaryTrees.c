/**** testStackOfBinaryTrees.c ***********************************************
 * Author: Daniel Mendez
 * Date Created: 09/10/2019
 * Last Modified: 01/01/2020
 * Purpose:  Test the Stack of Binary Trees data structure found in the
 *           stack.c, stack.h , binaryTree.c and binaryTree.h files for
 *           any memory safety issues. 
 * 
 * Compile Command: gcc  -Wall  testStackOfBinaryTrees.c  ../Data_Structures/stack.c  ../Data_Structures/binaryTree.c  -o  testStackOfBinaryTrees
 * Run Command:     ./testStackOfBinaryTrees
 * 
 * Example Input for Add option: 5 hello
 * 
****************************************************************/

#include "../Data_Structures/stack.h"

int MAXSIZE = 20;
int top = -1;


int main()
{
    char nodeName[10];
    int symbolInteger = 0;
    char symbolString[10];
    TreeELEM stackOfTrees[MAXSIZE];


    //Immediately include the base of the stack
    char nameOfTree[8];
    printf("Pushing empty Binary Tree onto Stack... \nGive the tree a string name: ");
    scanf ("%s", nameOfTree);
    getchar(); //Eats the trailing newline character from scanf
    push(stackOfTrees, nameOfTree);                              //Name of binary tree is "O"

    
    printf ("Please enter an integer and a string: ");
    scanf ("%d %s", &symbolInteger, symbolString);
    getchar();                                       //Eats the trailing newline character from scanf
    add(stackOfTrees, symbolInteger, symbolString);  //string field is "maxint", int field is 8

    //Accept user input
    while (1) {
        printf ("_________________________________________________________________________\n");
        printf ("Please enter one of the following stack commands:\n");
        printf ("p(U)sh:         Push a new empty tree onto the stack. Max of 7 characters.\n");
        printf ("p(O)p:          Pop the top tree off the stack.\n");
        printf ("(A)dd:          Add a symbol to the binary tree on the top of the stack. Max of 9 characters.\n");
        printf ("(L)ocal Search: Search for a symbol in the topmost binary tree on the stack.\n");
        printf ("(S)earch:       Search for a symbol in all binary trees on the stack.\n");
        printf ("(Q)uit:         Quit this program.\n\n\n");

        char userInput;
        scanf ("%c", &userInput);
        getchar(); //Eats the trailing newline character from scanf

        switch (userInput)
        {
        case 'U':
            printf("Pushing empty Binary Tree onto Stack... \nGive the tree a string name: ");
            scanf ("%s", nameOfTree);
            getchar(); //Eats the trailing newline character from scanf
            
            push(stackOfTrees, nameOfTree);
            break;
            
        case 'O':
            pop(stackOfTrees);
            break;
            
        case 'A':
            //User input
            printf ("Please enter an integer and a string: ");
            scanf ("%d %s", &symbolInteger, symbolString);
            getchar(); //Eats the trailing newline character from scanf

            add(stackOfTrees, symbolInteger, symbolString);
            break;

        case 'L':
            //User input
            printf ("Please input the string you are searching for: ");
            scanf ("%s", nodeName);
            getchar(); //Eats the trailing newline character from scanf

            
            //Search for symbol on the topmost binary tree on the stack
            Node* wantedNode = NULL;
            wantedNode = localSearch(stackOfTrees[top].rootPointer, nodeName);
            if (wantedNode != NULL){
                printf("String \"%s\" FOUND!\nFound in Binary Tree with Name: \"%s\"\n\n\n",
                       wantedNode->symbol, stackOfTrees[top].name);
            }
            else
                printf("The string \"%s\" is NOT found on the topmost Binary Tree.\n\n\n", nodeName);

            break;

        case 'S':
            //User input
            printf ("Please input the string you are searching for: ");
            scanf ("%s", nodeName);
            getchar(); //Eats the trailing newline character from scanf
      

            //Searches for symbol in each tree on the stack
            Node* targetNode = NULL;
            int searchCount = 0;
            for (int i=top; i>=0; i--) {
                targetNode = localSearch(stackOfTrees[i].rootPointer, nodeName);
                if (targetNode != NULL){
                    printf("String \"%s\" FOUND!\nNumber of searched trees: %d\nFound in Binary Tree with Name: \"%s\"\n\n\n",
                           targetNode->symbol, searchCount, stackOfTrees[i].name);
                    break;
                }
                searchCount++;
            }

            
            //Symbol is not found so display eror message to user
            if (targetNode == NULL)
                printf("The string \"%s\" is NOT found on any tree in the stack.\n\n\n", nodeName);

            break;

        case 'Q':
            quit();
            break;

        default:
            printf("Please input one of these valid character commands: \nU\nO\nA\nS\nQ\n");
            break;
        }
    } //end of while loop

} /* end of main */
