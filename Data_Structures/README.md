I wrote approximately 1,165 lines of original C source code in the following eight files combined
# Files and Descriptions
**FileNames:** *stack.c*, *stack.h*, *binaryTree.c*, and *binaryTree.h*  
**Description:**  
- These two files together make up a stack of binary trees used in the *ada.y* file. Simply think of this as a list with additions and removals of elements (i.e. binary trees) at one end, but with searching of nodes available throughout every Binary Tree in the list. Nodes can be added only to the Binary Tree at the top of the "stack". However, the search for a node begins at the Binary Tree on top of the "stack" and continues down the "stack" of Binary Trees until the node is found or there are no more trees to search for.  
<p>&nbsp;</p>

**FileNames:** *listOfStructs.c*, and *listOfStructs.h*   
**Description:**  
- A linked list data structure used in the *ada.y* file. Data Structure is used in order to "carry up" information from one production to another production regarding the declared Ada variables. Ada Variables can be of type integer, boolean, array or record  
<p>&nbsp;</p>

**FileName:** *record.c*  
**Description:**  
- Contains the SPECIFICATION and IMPLEMENTATION of FOUR Data Structures used in the *ada.y* file. The four data structures are two linked lists and two structs. The Data Structures are needed in order to display the abstract machine instructions output that result from the productions of the Ada grammar  
<p>&nbsp;</p>

**FileName:**  *patchDataStructures.c*  
**Description:**  
- Contains the SPECIFICATION and IMPLEMENTATION of FIVE Data Structures used in the ada.y file. The five data structures are two linked lists, two stacks of linked lists and one stack of integers. The Data Structures are used in order to patch the program counter line numbers resulting from the Abstract Machine Instruction output of Ada Loops, Ada Case statements, Ada if, else if, else statements, and  Ada Exceptions

# Author:  
### **Daniel Mendez** 




# Acknowledgments:

 1. Data Structures and Program Design in C++, by Robert Kruse and Alexander Ryba, Prentice Hall, 1999.
	- General guideline and reference to help me build the stack of binary trees

<p>&nbsp;</p>

2. GeeksforGeeks
   - https://www.geeksforgeeks.org/iterative-searching-binary-search-tree/
      - General Guideline to create an iterative search function

   - https://www.geeksforgeeks.org/remove-duplicates-from-a-sorted-linked-list/
        - FileName:  binaryTree.c
        - Modified Function:
         	1. void detachDuplicates(Node *firstNode)

   - https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/
    	- FileName:  patchDataStructures.c  
    	- Modified Functions:
        	1. void bubbleSort(ListNodePtr start)
        	2. void swap(ListNodePtr a, ListNodePtr b) 

<p>&nbsp;</p>

 3.  https://www.learn-c.org/en/Binary_trees
       - FileName: binaryTree.c
       - Modified Functions:
           1. void printDFS(Node * current)
           2. void printBTNodesNextDFS(Node* current)
