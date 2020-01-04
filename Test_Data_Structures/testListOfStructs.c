/**** testListOfStructs.c **************************************
 * Author: Daniel Mendez
 * Date Created: 10/09/2019
 * Last Modified: ---
 * Purpose: Test the Linked List data structure found in the
 *          listOfStructs.h file for memory safety issues
 * 
 * Compile Command: gcc  -Wall  testListOfStructs.c  ../Data_Structures/listOfStructs.c  -o  testListOfStructs
 * Run Command:     ./testListOfStructs
******************************************************/
#include "../Data_Structures/listOfStructs.h"


int main() {

    idnodeptr head;
    head = initialize("25");
    head = addToList(head, "42");
    head = addToList(head, "81");
    head = addToList(head, "93");
    head = addToList(head, "52");

    printf("Print the linked list:");
    printRoutine(head);
    printf("\n\n");

    return EXIT_SUCCESS;

    //Another method for testing the linked list data structure
    /*
    idnodeptr theList;

    
    while (1) {
        printf ("_________________________________________________________________________\n");
        printf ("Please enter one of the following list commands:\n");
        printf ("(P)rint:         Prints out all the name fields of each struct\n");
        printf ("(A)dd:           Add a symbol to the front of the list\n");
        
        char userInput;
        scanf ("%c", &userInput);
        getchar(); //Eats the trailing newline character from scanf

        
        switch (userInput)
        {
        case 'P':
            printRoutine(theList);
            break;
            
        case 'A':
            //Ask for user input
            printf ("Please name the new node with a string: ");
            char nameOfNode[10];
            scanf ("%s", nameOfNode);
            getchar(); //Eats the trailing newline character from scanf

            
            addToList(&theList, nameOfNode);
            break;
        }
    }
    */
} //end of main function
