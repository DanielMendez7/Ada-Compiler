# Ada Compiler

This project consists of a synthesized (passed up the parse tree) attribute grammar. This compiler takes source code written in the Ada programming language and produces compiled code (code generation process). The Ada source code can be thought of as a "single long string". The compiler separates this "single long string" into tokens (lexical units),parses the tokens and then builds intermediate code trees. It checks for syntax and some semantic errors. I wrote approximately 2,413 lines of original C source code (including the Ada grammar) in the *ada.y* and *ada.l* files combined. 


### **This Ada compiler generates complete compiled code for the following:**
1.  Assignment statements
    - Supports local variables, non-local variables, literals and expressions in arithmetic operations
2.  Procedure calls and returns for procedures with scalar parameters.  
    - Supports in, in out and out parameters
3.   Input/Output calls
4.   Array types
5.   Record types
6.   Loops
7.   Full If then Elsifs Else statements
8.   Case statements
9.   Exceptions
     - Supports declaring, raising, handling and propagating exceptions throughout an Ada program
1.   Epilogue
2.   Prologue

<p>&nbsp;</p>

Note:
- Local variables, non-local variables, literals and expressions 
are supported as parameters in the following: **3, 4, 5, 6, 7, 8, 9, 10**  
- Local variable and non-local variable types are supported 
for the following: **integer, boolean, arrays, records**




# Prerequisites: 
1) Lex Flex Yacc Bison Extension by Faustino Aguilar helps with reading the syntax in the *ada.y* file




# Running The Tests:
### **To compile an ada file and see the resulting compiled code please follow these steps.**
- **Step 1)** Choose an ada file from the *TESTS* directory that you want to test OR make your own ada file that you want to test and place it in the *TESTS* directory! 
- **Step 2)** Go to the script file found in the AdaSubset_Grammar directory and go to this line:  *input="./TESTS/final.ada"* At this line please substitute, *final.ada*, with the file you want to test. 
- **Step 3)** To execute please enter the following on the terminal:   *./script*
- **Step 4)** In order to see the resulting compiled code there are two options. Option 1 is more straightforward and less work.
	- **Option 1)** The resulting compiled code is located in the *AMI_Output_Patched.out* file
	- **Option 2)** Alternatively, the compiled code will be located at the very bottom of the terminal right after the printed patch list. Please note that for the question marks in the resulting compiled code should be replaced with the jumpNumber found in the printed patch list at the terminal. Here is an example from the code generated from *final.ada*, **0: b := ?** has a **PatchLine** of **0** and the question mark should be replaced with the **JumpNumber** of **117**. **PatchLine** and **JumpNumber** are found in the printed patch list near the bottom of the terminal.


### **To understand the compiled code you will need to look at these three files.**
- **File 1)** The ada source code file you are testing is in the *TESTS* directory
- **File 2)** *AMI_Output_Patched.out* is located in the *AdaSubset_Grammar* directory 
- **File 3)** *Abstract_Machine_Instructions_Sheet.pdf* is located in the *AdaSubset_Grammar* directory
- **Note:** In simple terms, my compiler receives some input ada file and "spits out" some compiled code (*AMI_Output_Patched.out*). To understand the compiled code in the *AMI_Output_Patched.out* file, please refer to this pdf, *Abstract_Machine_Instructions_Sheet.pdf*.



# Sample Test Example:

### **Example 1:**  
`Ada Source Code:

	procedure main is		--SimpElseif.ada
			x,y:integer;
	begin
			if x = y then
			x := 5;
			elsif y = x then
			y := 6;
			elsif y < x then
			y := x;
			else
			y := 7;
			end if;
	end;
`Compiled Code generated by my Ada compiler ( *AMI_Output_Patched.out* ):

	0: b := 31
	1: contents b, 0 := 37
	2: contents b, 1 := 5
	3: r1 := 0
	4: pc := 6
	5: halt
	6: r2 := contents b, 4 
	7: r3 := contents b, 5 
	8: r4 := r2 = r3
	9: pc := 13 if not r4
	10: r5 := 5
	11: contents b, 4 := r5
	12: pc := 28
	13: r6 := contents b, 5 
	14: r7 := contents b, 4 
	15: r8 := r6 = r7
	16: pc := 20 if not r8
	17: r9 := 6
	18: contents b, 5 := r9
	19: pc := 28
	20: r10 := contents b, 5 
	21: r11 := contents b, 4 
	22: r12 := r10 < r11
	23: pc := 26 if not r12
	24: contents b, 5 := contents b, 4
	25: pc := 28
	26: r13 := 7
	27: contents b, 5 := r13
	28: r14 := contents b, 1
	29: b := contents b, 3
	30: pc := r14

### **Example 2:**  
- Please refer to the file called, *AMI_Output_Patched.out*,  which contains the compiled code from when I ran the, *final.ada* file.



# Author:  
### **Daniel Mendez**


# Acknowledgments:  
1) My Compiler Construction Course Professor: Laurie Smith King

2) Mason. Lex and Yacc, O'Reilly & Associates
