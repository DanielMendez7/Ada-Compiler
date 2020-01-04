/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IS = 258,
     BEG = 259,
     END = 260,
     PROCEDURE = 261,
     ID = 262,
     NUMBER = 263,
     TYPE = 264,
     ARRAY = 265,
     RAISE = 266,
     OTHERS = 267,
     RECORD = 268,
     IN = 269,
     OUT = 270,
     RANGE = 271,
     CONSTANT = 272,
     ASSIGN = 273,
     EXCEPTION = 274,
     NULLWORD = 275,
     LOOP = 276,
     IF = 277,
     THEN = 278,
     ELSEIF = 279,
     ELSE = 280,
     EXIT = 281,
     WHEN = 282,
     AND = 283,
     OR = 284,
     EQ = 285,
     NEQ = 286,
     LT = 287,
     GT = 288,
     GTE = 289,
     LTE = 290,
     TICK = 291,
     NOT = 292,
     EXP = 293,
     ARROW = 294,
     OF = 295,
     DOTDOT = 296,
     ENDIF = 297,
     ENDREC = 298,
     ENDLOOP = 299,
     EXITWHEN = 300,
     CASE = 301,
     ENDCASE = 302
   };
#endif
/* Tokens.  */
#define IS 258
#define BEG 259
#define END 260
#define PROCEDURE 261
#define ID 262
#define NUMBER 263
#define TYPE 264
#define ARRAY 265
#define RAISE 266
#define OTHERS 267
#define RECORD 268
#define IN 269
#define OUT 270
#define RANGE 271
#define CONSTANT 272
#define ASSIGN 273
#define EXCEPTION 274
#define NULLWORD 275
#define LOOP 276
#define IF 277
#define THEN 278
#define ELSEIF 279
#define ELSE 280
#define EXIT 281
#define WHEN 282
#define AND 283
#define OR 284
#define EQ 285
#define NEQ 286
#define LT 287
#define GT 288
#define GTE 289
#define LTE 290
#define TICK 291
#define NOT 292
#define EXP 293
#define ARROW 294
#define OF 295
#define DOTDOT 296
#define ENDIF 297
#define ENDREC 298
#define ENDLOOP 299
#define EXITWHEN 300
#define CASE 301
#define ENDCASE 302




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 57 "ada.y"
{
    int integer;
    char *var;
    struct idnode* listPointer; //pointer for the list of Ids
    struct node* nodePtr;
    struct Record* ptrToRecord;
    struct RecordNode* ptrToRecordNode; //Used to handle read and write with multiple expression lists
    struct RecordList* adaRecordsInfo;  //Used to handle Ada record types
    struct  numListNode* ptrToNumNode;
}
/* Line 1529 of yacc.c.  */
#line 154 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

