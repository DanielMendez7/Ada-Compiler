/**** listOfStructs.c ***********************************************
 * Author: Daniel Mendez
 * Date Created: 10/09/2019
 * Last Modified:
 * Purpose: Contains the IMPLEMENTATION of a linked list data structure 
 *          used in the ada.y file. Data Structure is used in order to 
 *          "carry up" information from one production to another 
 *          production regarding the declared Ada variables. Ada Variables 
 *          can be of type integer, boolean, array or record
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listOfStructs.h"


idnodeptr initialize(char* nameData)
/***********************************************
Return a pointer to the newly allocated node
************************************************/
{
    idnodeptr new_node;
    new_node = (idnodeptr) malloc(sizeof(idnodeptr));
    new_node->name = (char*) malloc(sizeof(nameData) + 1);
    strcpy(new_node->name, nameData);
    new_node->next = NULL;
    return new_node;
    
}

void printRoutine(idnodeptr list)
/***********************************************
Prints the name field of each struct in the List 
************************************************/
{
    idnodeptr current = list;
    if (current == NULL)
        printf("Your list is currently empty\n\n");
    
    else 
        while (current != NULL) {
            printf("%s ", current -> name);
            current = current -> next;
        }
    

    
}


idnodeptr addToList(idnodeptr listHead, char* nodeName) 
/***********************************************
Adds a new node to the front of the list and 
returns a pointer to the front node of the 
resulting single list
************************************************/
{


    //Create a new node 
    idnodeptr newHead = (idnodeptr) malloc(sizeof(idnodeptr));
    newHead -> name = (char*) (malloc(sizeof(nodeName)+1));
    strcpy(newHead -> name, nodeName);
    newHead->next = listHead;
    return newHead;

} //end of addToList



