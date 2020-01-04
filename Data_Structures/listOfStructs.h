/**** listOfStructs.h ***********************************************
 * Author: Daniel Mendez
 * Date Created: 10/09/2019
 * Last Modified:
 * Purpose: Contains the SPECIFICATION of a linked list data structure 
 *          used in the ada.y file. Data Structure is used in order to 
 *          "carry up" information from one production to another 
 *          production regarding the declared Ada variables. Ada Variables 
 *          can be of type integer, boolean, array or record
*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#ifndef LISTOFSTRUCTS
#define LISTOFSTRUCTS

typedef struct idnode {
    char *name;
    struct idnode *next;
} *idnodeptr;

idnodeptr initialize(char* nameData);
void printRoutine(idnodeptr list);
idnodeptr addToList(idnodeptr listHead, char* nodeName);

#endif
