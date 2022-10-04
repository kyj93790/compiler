example_code_2.c                                                                                    0000644 0002260 0002114 00000000107 14317021021 013353  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /* comment /* asdf *****/

/* com**

    /


    ment*/

/* comerrorb *                                                                                                                                                                                                                                                                                                                                                                                                                                                         example_results_1.txt                                                                               0000644 0002260 0002114 00000003454 14317021021 014546  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  
TINY COMPILATION: test1.tny
    line number			token			lexeme
================================================================================
	2			INT			int
	2			ID			arr
	2			[			[
	2			NUM			11111
	2			]			]
	2			;			;
	3			INT			int
	3			ID			binarySearch
	3			(			(
	3			INT			int
	3			ID			x
	3			)			)
	3			{			{
	4			INT			int
	4			ID			left
	4			=			=
	4			NUM			0
	4			,			,
	4			ID			right
	4			=			=
	4			NUM			11111
	4			,			,
	4			ID			mid
	4			;			;
	5			WHILE			while
	5			(			(
	5			ID			left
	5			<=			<=
	5			ID			right
	5			)			)
	5			{			{
	6			ID			mid
	6			=			=
	6			(			(
	6			ID			left
	6			<=			<=
	6			ID			right
	6			)			)
	6			/			/
	6			NUM			2
	6			;			;
	7			IF			if
	7			(			(
	7			ID			mid
	7			==			==
	7			ID			x
	7			)			)
	7			RETURN			return
	7			ID			mid
	7			;			;
	8			ELSE			else
	8			IF			if
	8			(			(
	8			ID			mid
	8			<			<
	8			ID			x
	8			)			)
	8			ID			left
	8			=			=
	8			ID			mid
	8			+			+
	8			NUM			1
	8			;			;
	9			ELSE			else
	9			ID			right
	9			=			=
	9			ID			mid
	9			-			-
	9			NUM			1
	9			;			;
	10			}			}
	11			RETURN			return
	11			-			-
	11			NUM			1
	11			;			;
	12			}			}
	14			INT			int
	14			ID			main
	14			(			(
	14			)			)
	14			{			{
	15			INT			int
	15			ID			i
	15			,			,
	15			ID			goal
	15			,			,
	15			ID			res
	15			;			;
	16			ID			for
	16			(			(
	16			ID			i
	16			=			=
	16			NUM			0
	16			;			;
	16			ID			i
	16			<			<
	16			NUM			11111
	16			;			;
	16			ID			i
	16			+			+
	16			+			+
	16			)			)
	16			{			{
	17			ID			arr
	17			[			[
	17			ID			i
	17			]			]
	17			=			=
	17			ID			i
	17			;			;
	18			}			}
	19			ID			goal
	19			=			=
	19			NUM			100
	19			;			;
	20			ID			res
	20			=			=
	20			ID			binarySearch
	20			(			(
	20			ID			goal
	20			)			)
	20			;			;
	21			RETURN			return
	21			NUM			0
	21			;			;
	22			}			}
	22			EOF
                                                                                                                                                                                                                    example_results_2.txt                                                                               0000644 0002260 0002114 00000000263 14317021021 014542  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  
TINY COMPILATION: test2.c
    line number			token			lexeme
================================================================================
	10			ERROR			Comment Error
	10			EOF
                                                                                                                                                                                                                                                                                                                                             Tiny_scanner/                                                                                       0000755 0002260 0002114 00000000000 14317021022 013000  5                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  Tiny_scanner/ANALYZE.C                                                                              0000644 0002260 0002114 00000010544 14317021021 014212  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: analyze.c                                  */
/* Semantic analyzer implementation                 */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "analyze.h"

/* counter for variable memory locations */
static int location = 0;

/* Procedure traverse is a generic recursive 
 * syntax tree traversal routine:
 * it applies preProc in preorder and postProc 
 * in postorder to tree pointed to by t
 */
static void traverse( TreeNode * t,
               void (* preProc) (TreeNode *),
               void (* postProc) (TreeNode *) )
{ if (t != NULL)
  { preProc(t);
    { int i;
      for (i=0; i < MAXCHILDREN; i++)
        traverse(t->child[i],preProc,postProc);
    }
    postProc(t);
    traverse(t->sibling,preProc,postProc);
  }
}

/* nullProc is a do-nothing procedure to 
 * generate preorder-only or postorder-only
 * traversals from traverse
 */
static void nullProc(TreeNode * t)
{ if (t==NULL) return;
  else return;
}

/* Procedure insertNode inserts 
 * identifiers stored in t into 
 * the symbol table 
 */
static void insertNode( TreeNode * t)
{ switch (t->nodekind)
  { case StmtK:
      switch (t->kind.stmt)
      { case AssignK:
        case ReadK:
          if (st_lookup(t->attr.name) == -1)
          /* not yet in table, so treat as new definition */
            st_insert(t->attr.name,t->lineno,location++);
          else
          /* already in table, so ignore location, 
             add line number of use only */ 
            st_insert(t->attr.name,t->lineno,0);
          break;
        default:
          break;
      }
      break;
    case ExpK:
      switch (t->kind.exp)
      { case IdK:
          if (st_lookup(t->attr.name) == -1)
          /* not yet in table, so treat as new definition */
            st_insert(t->attr.name,t->lineno,location++);
          else
          /* already in table, so ignore location, 
             add line number of use only */ 
            st_insert(t->attr.name,t->lineno,0);
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode * syntaxTree)
{ traverse(syntaxTree,insertNode,nullProc);
  if (TraceAnalyze)
  { fprintf(listing,"\nSymbol table:\n\n");
    printSymTab(listing);
  }
}

static void typeError(TreeNode * t, char * message)
{ fprintf(listing,"Type error at line %d: %s\n",t->lineno,message);
  Error = TRUE;
}

/* Procedure checkNode performs
 * type checking at a single tree node
 */
static void checkNode(TreeNode * t)
{ switch (t->nodekind)
  { case ExpK:
      switch (t->kind.exp)
      { case OpK:
          if ((t->child[0]->type != Integer) ||
              (t->child[1]->type != Integer))
            typeError(t,"Op applied to non-integer");
          if ((t->attr.op == EQ) || (t->attr.op == LT))
            t->type = Boolean;
          else
            t->type = Integer;
          break;
        case ConstK:
        case IdK:
          t->type = Integer;
          break;
        default:
          break;
      }
      break;
    case StmtK:
      switch (t->kind.stmt)
      { case IfK:
          if (t->child[0]->type == Integer)
            typeError(t->child[0],"if test is not Boolean");
          break;
        case AssignK:
          if (t->child[0]->type != Integer)
            typeError(t->child[0],"assignment of non-integer value");
          break;
        case WriteK:
          if (t->child[0]->type != Integer)
            typeError(t->child[0],"write of non-integer value");
          break;
        case RepeatK:
          if (t->child[1]->type == Integer)
            typeError(t->child[1],"repeat test is not Boolean");
          break;
        default:
          break;
      }
      break;
    default:
      break;

  }
}

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode * syntaxTree)
{ traverse(syntaxTree,nullProc,checkNode);
}
                                                                                                                                                            Tiny_scanner/ANALYZE.H                                                                              0000644 0002260 0002114 00000001214 14317021021 014211  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: analyze.h                                  */
/* Semantic analyzer interface for TINY compiler    */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _ANALYZE_H_
#define _ANALYZE_H_

/* Function buildSymtab constructs the symbol 
 * table by preorder traversal of the syntax tree
 */
void buildSymtab(TreeNode *);

/* Procedure typeCheck performs type checking 
 * by a postorder syntax tree traversal
 */
void typeCheck(TreeNode *);

#endif
                                                                                                                                                                                                                                                                                                                                                                                    Tiny_scanner/CGEN.C                                                                                 0000644 0002260 0002114 00000015473 14317021021 013631  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: cgen.c                                     */
/* The code generator implementation                */
/* for the TINY compiler                            */
/* (generates code for the TM machine)              */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"

/* tmpOffset is the memory offset for temps
   It is decremented each time a temp is
   stored, and incremeted when loaded again
*/
static int tmpOffset = 0;

/* prototype for internal recursive code generator */
static void cGen (TreeNode * tree);

/* Procedure genStmt generates code at a statement node */
static void genStmt( TreeNode * tree)
{ TreeNode * p1, * p2, * p3;
  int savedLoc1,savedLoc2,currentLoc;
  int loc;
  switch (tree->kind.stmt) {

      case IfK :
         if (TraceCode) emitComment("-> if") ;
         p1 = tree->child[0] ;
         p2 = tree->child[1] ;
         p3 = tree->child[2] ;
         /* generate code for test expression */
         cGen(p1);
         savedLoc1 = emitSkip(1) ;
         emitComment("if: jump to else belongs here");
         /* recurse on then part */
         cGen(p2);
         savedLoc2 = emitSkip(1) ;
         emitComment("if: jump to end belongs here");
         currentLoc = emitSkip(0) ;
         emitBackup(savedLoc1) ;
         emitRM_Abs("JEQ",ac,currentLoc,"if: jmp to else");
         emitRestore() ;
         /* recurse on else part */
         cGen(p3);
         currentLoc = emitSkip(0) ;
         emitBackup(savedLoc2) ;
         emitRM_Abs("LDA",pc,currentLoc,"jmp to end") ;
         emitRestore() ;
         if (TraceCode)  emitComment("<- if") ;
         break; /* if_k */

      case RepeatK:
         if (TraceCode) emitComment("-> repeat") ;
         p1 = tree->child[0] ;
         p2 = tree->child[1] ;
         savedLoc1 = emitSkip(0);
         emitComment("repeat: jump after body comes back here");
         /* generate code for body */
         cGen(p1);
         /* generate code for test */
         cGen(p2);
         emitRM_Abs("JEQ",ac,savedLoc1,"repeat: jmp back to body");
         if (TraceCode)  emitComment("<- repeat") ;
         break; /* repeat */

      case AssignK:
         if (TraceCode) emitComment("-> assign") ;
         /* generate code for rhs */
         cGen(tree->child[0]);
         /* now store value */
         loc = st_lookup(tree->attr.name);
         emitRM("ST",ac,loc,gp,"assign: store value");
         if (TraceCode)  emitComment("<- assign") ;
         break; /* assign_k */

      case ReadK:
         emitRO("IN",ac,0,0,"read integer value");
         loc = st_lookup(tree->attr.name);
         emitRM("ST",ac,loc,gp,"read: store value");
         break;
      case WriteK:
         /* generate code for expression to write */
         cGen(tree->child[0]);
         /* now output it */
         emitRO("OUT",ac,0,0,"write ac");
         break;
      default:
         break;
    }
} /* genStmt */

/* Procedure genExp generates code at an expression node */
static void genExp( TreeNode * tree)
{ int loc;
  TreeNode * p1, * p2;
  switch (tree->kind.exp) {

    case ConstK :
      if (TraceCode) emitComment("-> Const") ;
      /* gen code to load integer constant using LDC */
      emitRM("LDC",ac,tree->attr.val,0,"load const");
      if (TraceCode)  emitComment("<- Const") ;
      break; /* ConstK */
    
    case IdK :
      if (TraceCode) emitComment("-> Id") ;
      loc = st_lookup(tree->attr.name);
      emitRM("LD",ac,loc,gp,"load id value");
      if (TraceCode)  emitComment("<- Id") ;
      break; /* IdK */

    case OpK :
         if (TraceCode) emitComment("-> Op") ;
         p1 = tree->child[0];
         p2 = tree->child[1];
         /* gen code for ac = left arg */
         cGen(p1);
         /* gen code to push left operand */
         emitRM("ST",ac,tmpOffset--,mp,"op: push left");
         /* gen code for ac = right operand */
         cGen(p2);
         /* now load left operand */
         emitRM("LD",ac1,++tmpOffset,mp,"op: load left");
         switch (tree->attr.op) {
            case PLUS :
               emitRO("ADD",ac,ac1,ac,"op +");
               break;
            case MINUS :
               emitRO("SUB",ac,ac1,ac,"op -");
               break;
            case TIMES :
               emitRO("MUL",ac,ac1,ac,"op *");
               break;
            case OVER :
               emitRO("DIV",ac,ac1,ac,"op /");
               break;
            case LT :
               emitRO("SUB",ac,ac1,ac,"op <") ;
               emitRM("JLT",ac,2,pc,"br if true") ;
               emitRM("LDC",ac,0,ac,"false case") ;
               emitRM("LDA",pc,1,pc,"unconditional jmp") ;
               emitRM("LDC",ac,1,ac,"true case") ;
               break;
            case EQ :
               emitRO("SUB",ac,ac1,ac,"op ==") ;
               emitRM("JEQ",ac,2,pc,"br if true");
               emitRM("LDC",ac,0,ac,"false case") ;
               emitRM("LDA",pc,1,pc,"unconditional jmp") ;
               emitRM("LDC",ac,1,ac,"true case") ;
               break;
            default:
               emitComment("BUG: Unknown operator");
               break;
         } /* case op */
         if (TraceCode)  emitComment("<- Op") ;
         break; /* OpK */

    default:
      break;
  }
} /* genExp */

/* Procedure cGen recursively generates code by
 * tree traversal
 */
static void cGen( TreeNode * tree)
{ if (tree != NULL)
  { switch (tree->nodekind) {
      case StmtK:
        genStmt(tree);
        break;
      case ExpK:
        genExp(tree);
        break;
      default:
        break;
    }
    cGen(tree->sibling);
  }
}

/**********************************************/
/* the primary function of the code generator */
/**********************************************/
/* Procedure codeGen generates code to a code
 * file by traversal of the syntax tree. The
 * second parameter (codefile) is the file name
 * of the code file, and is used to print the
 * file name as a comment in the code file
 */
void codeGen(TreeNode * syntaxTree, char * codefile)
{  char * s = malloc(strlen(codefile)+7);
   strcpy(s,"File: ");
   strcat(s,codefile);
   emitComment("TINY Compilation to TM Code");
   emitComment(s);
   /* generate standard prelude */
   emitComment("Standard prelude:");
   emitRM("LD",mp,0,ac,"load maxaddress from location 0");
   emitRM("ST",ac,0,ac,"clear location 0");
   emitComment("End of standard prelude.");
   /* generate code for TINY program */
   cGen(syntaxTree);
   /* finish */
   emitComment("End of execution.");
   emitRO("HALT",0,0,0,"");
}
                                                                                                                                                                                                     Tiny_scanner/CGEN.H                                                                                 0000644 0002260 0002114 00000001247 14317021021 013630  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: cgen.h                                     */
/* The code generator interface to the TINY compiler*/
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _CGEN_H_
#define _CGEN_H_

/* Procedure codeGen generates code to a code
 * file by traversal of the syntax tree. The
 * second parameter (codefile) is the file name
 * of the code file, and is used to print the
 * file name as a comment in the code file
 */
void codeGen(TreeNode * syntaxTree, char * codefile);

#endif
                                                                                                                                                                                                                                                                                                                                                         Tiny_scanner/CODE.C                                                                                 0000644 0002260 0002114 00000005737 14317021021 013631  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: code.c                                     */
/* TM Code emitting utilities                       */
/* implementation for the TINY compiler             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "code.h"

/* TM location number for current instruction emission */
static int emitLoc = 0 ;

/* Highest TM location emitted so far
   For use in conjunction with emitSkip,
   emitBackup, and emitRestore */
static int highEmitLoc = 0;

/* Procedure emitComment prints a comment line 
 * with comment c in the code file
 */
void emitComment( char * c )
{ if (TraceCode) fprintf(code,"* %s\n",c);}

/* Procedure emitRO emits a register-only
 * TM instruction
 * op = the opcode
 * r = target register
 * s = 1st source register
 * t = 2nd source register
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRO( char *op, int r, int s, int t, char *c)
{ fprintf(code,"%3d:  %5s  %d,%d,%d ",emitLoc++,op,r,s,t);
  if (TraceCode) fprintf(code,"\t%s",c) ;
  fprintf(code,"\n") ;
  if (highEmitLoc < emitLoc) highEmitLoc = emitLoc ;
} /* emitRO */

/* Procedure emitRM emits a register-to-memory
 * TM instruction
 * op = the opcode
 * r = target register
 * d = the offset
 * s = the base register
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRM( char * op, int r, int d, int s, char *c)
{ fprintf(code,"%3d:  %5s  %d,%d(%d) ",emitLoc++,op,r,d,s);
  if (TraceCode) fprintf(code,"\t%s",c) ;
  fprintf(code,"\n") ;
  if (highEmitLoc < emitLoc)  highEmitLoc = emitLoc ;
} /* emitRM */

/* Function emitSkip skips "howMany" code
 * locations for later backpatch. It also
 * returns the current code position
 */
int emitSkip( int howMany)
{  int i = emitLoc;
   emitLoc += howMany ;
   if (highEmitLoc < emitLoc)  highEmitLoc = emitLoc ;
   return i;
} /* emitSkip */

/* Procedure emitBackup backs up to 
 * loc = a previously skipped location
 */
void emitBackup( int loc)
{ if (loc > highEmitLoc) emitComment("BUG in emitBackup");
  emitLoc = loc ;
} /* emitBackup */

/* Procedure emitRestore restores the current 
 * code position to the highest previously
 * unemitted position
 */
void emitRestore(void)
{ emitLoc = highEmitLoc;}

/* Procedure emitRM_Abs converts an absolute reference 
 * to a pc-relative reference when emitting a
 * register-to-memory TM instruction
 * op = the opcode
 * r = target register
 * a = the absolute location in memory
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRM_Abs( char *op, int r, int a, char * c)
{ fprintf(code,"%3d:  %5s  %d,%d(%d) ",
               emitLoc,op,r,a-(emitLoc+1),pc);
  ++emitLoc ;
  if (TraceCode) fprintf(code,"\t%s",c) ;
  fprintf(code,"\n") ;
  if (highEmitLoc < emitLoc) highEmitLoc = emitLoc ;
} /* emitRM_Abs */
                                 Tiny_scanner/CODE.H                                                                                 0000644 0002260 0002114 00000004272 14317021021 013627  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: code.h                                     */
/* Code emitting utilities for the TINY compiler    */
/* and interface to the TM machine                  */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _CODE_H_
#define _CODE_H_

/* pc = program counter  */
#define  pc 7

/* mp = "memory pointer" points
 * to top of memory (for temp storage)
 */
#define  mp 6

/* gp = "global pointer" points
 * to bottom of memory for (global)
 * variable storage
 */
#define gp 5

/* accumulator */
#define  ac 0

/* 2nd accumulator */
#define  ac1 1

/* code emitting utilities */

/* Procedure emitComment prints a comment line 
 * with comment c in the code file
 */
void emitComment( char * c );

/* Procedure emitRO emits a register-only
 * TM instruction
 * op = the opcode
 * r = target register
 * s = 1st source register
 * t = 2nd source register
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRO( char *op, int r, int s, int t, char *c);

/* Procedure emitRM emits a register-to-memory
 * TM instruction
 * op = the opcode
 * r = target register
 * d = the offset
 * s = the base register
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRM( char * op, int r, int d, int s, char *c);

/* Function emitSkip skips "howMany" code
 * locations for later backpatch. It also
 * returns the current code position
 */
int emitSkip( int howMany);

/* Procedure emitBackup backs up to 
 * loc = a previously skipped location
 */
void emitBackup( int loc);

/* Procedure emitRestore restores the current 
 * code position to the highest previously
 * unemitted position
 */
void emitRestore(void);

/* Procedure emitRM_Abs converts an absolute reference 
 * to a pc-relative reference when emitting a
 * register-to-memory TM instruction
 * op = the opcode
 * r = target register
 * a = the absolute location in memory
 * c = a comment to be printed if TraceCode is TRUE
 */
void emitRM_Abs( char *op, int r, int a, char * c);

#endif
                                                                                                                                                                                                                                                                                                                                      Tiny_scanner/GLOBALS.H                                                                              0000644 0002260 0002114 00000005613 14317021021 014200  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: globals.h                                  */
/* Global types and vars for TINY compiler          */
/* must come before other include files             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 8

typedef enum 
    /* book-keeping tokens */
   {ENDFILE,ERROR,
    /* reserved words */
    IF,THEN,ELSE,END,REPEAT,UNTIL,READ,WRITE,
    /* multicharacter tokens */
    ID,NUM,
    /* special symbols */
    ASSIGN,EQ,LT,PLUS,MINUS,TIMES,OVER,LPAREN,RPAREN,SEMI
   } TokenType;

extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* code; /* code text file for TM simulator */

extern int lineno; /* source line number for listing */

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

typedef enum {StmtK,ExpK} NodeKind;
typedef enum {IfK,RepeatK,AssignK,ReadK,WriteK} StmtKind;
typedef enum {OpK,ConstK,IdK} ExpKind;

/* ExpType is used for type checking */
typedef enum {Void,Integer,Boolean} ExpType;

#define MAXCHILDREN 3

typedef struct treeNode
   { struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int lineno;
     NodeKind nodekind;
     union { StmtKind stmt; ExpKind exp;} kind;
     union { TokenType op;
             int val;
             char * name; } attr;
     ExpType type; /* for type checking of exps */
   } TreeNode;

/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/

/* EchoSource = TRUE causes the source program to
 * be echoed to the listing file with line numbers
 * during parsing
 */
extern int EchoSource;

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 */
extern int TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 */
extern int TraceParse;

/* TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be reported to the listing file
 */
extern int TraceAnalyze;

/* TraceCode = TRUE causes comments to be written
 * to the TM code file as code is generated
 */
extern int TraceCode;

/* Error = TRUE prevents further passes if an error occurs */
extern int Error; 
#endif
                                                                                                                     Tiny_scanner/MAIN.C                                                                                 0000644 0002260 0002114 00000004747 14317021021 013643  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: main.c                                     */
/* Main program for TINY compiler                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"

/* set NO_PARSE to TRUE to get a scanner-only compiler */
#define NO_PARSE FALSE
/* set NO_ANALYZE to TRUE to get a parser-only compiler */
#define NO_ANALYZE FALSE

/* set NO_CODE to TRUE to get a compiler that does not
 * generate code
 */
#define NO_CODE FALSE

#include "util.h"
#if NO_PARSE
#include "scan.h"
#else
#include "parse.h"
#if !NO_ANALYZE
#include "analyze.h"
#if !NO_CODE
#include "cgen.h"
#endif
#endif
#endif

/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = FALSE;
int TraceScan = FALSE;
int TraceParse = FALSE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;

main( int argc, char * argv[] )
{ TreeNode * syntaxTree;
  char pgm[120]; /* source code file name */
  if (argc != 2)
    { fprintf(stderr,"usage: %s <filename>\n",argv[0]);
      exit(1);
    }
  strcpy(pgm,argv[1]) ;
  if (strchr (pgm, '.') == NULL)
     strcat(pgm,".tny");
  source = fopen(pgm,"r");
  if (source==NULL)
  { fprintf(stderr,"File %s not found\n",pgm);
    exit(1);
  }
  listing = stdout; /* send listing to screen */
  fprintf(listing,"\nTINY COMPILATION: %s\n",pgm);
#if NO_PARSE
  while (getToken()!=ENDFILE);
#else
  syntaxTree = parse();
  if (TraceParse) {
    fprintf(listing,"\nSyntax tree:\n");
    printTree(syntaxTree);
  }
#if !NO_ANALYZE
  if (! Error)
  { if (TraceAnalyze) fprintf(listing,"\nBuilding Symbol Table...\n");
    buildSymtab(syntaxTree);
    if (TraceAnalyze) fprintf(listing,"\nChecking Types...\n");
    typeCheck(syntaxTree);
    if (TraceAnalyze) fprintf(listing,"\nType Checking Finished\n");
  }
#if !NO_CODE
  if (! Error)
  { char * codefile;
    int fnlen = strcspn(pgm,".");
    codefile = (char *) calloc(fnlen+4, sizeof(char));
    strncpy(codefile,pgm,fnlen);
    strcat(codefile,".tm");
    code = fopen(codefile,"w");
    if (code == NULL)
    { printf("Unable to open %s\n",codefile);
      exit(1);
    }
    codeGen(syntaxTree,codefile);
    fclose(code);
  }
#endif
#endif
#endif
  fclose(source);
  return 0;
}

                         Tiny_scanner/MAKEFILE                                                                               0000644 0002260 0002114 00000002151 14317021021 014076  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  #
# makefile for TINY
# Borland C Version
# K. Louden 2/3/98
#

CC = bcc

CFLAGS = 

OBJS = main.obj util.obj scan.obj parse.obj symtab.obj analyze.obj code.obj cgen.obj

tiny.exe: $(OBJS)
	$(CC) $(CFLAGS) -etiny $(OBJS)

main.obj: main.c globals.h util.h scan.h parse.h analyze.h cgen.h
	$(CC) $(CFLAGS) -c main.c

util.obj: util.c util.h globals.h
	$(CC) $(CFLAGS) -c util.c

scan.obj: scan.c scan.h util.h globals.h
	$(CC) $(CFLAGS) -c scan.c

parse.obj: parse.c parse.h scan.h globals.h util.h
	$(CC) $(CFLAGS) -c parse.c

symtab.obj: symtab.c symtab.h
	$(CC) $(CFLAGS) -c symtab.c

analyze.obj: analyze.c globals.h symtab.h analyze.h
	$(CC) $(CFLAGS) -c analyze.c

code.obj: code.c code.h globals.h
	$(CC) $(CFLAGS) -c code.c

cgen.obj: cgen.c globals.h symtab.h code.h cgen.h
	$(CC) $(CFLAGS) -c cgen.c

clean:
	-del tiny.exe
	-del tm.exe
	-del main.obj
	-del util.obj
	-del scan.obj
	-del parse.obj
	-del symtab.obj
	-del analyze.obj
	-del code.obj
	-del cgen.obj
	-del tm.obj

tm.exe: tm.c
	$(CC) $(CFLAGS) -etm tm.c

tiny: tiny.exe

tm: tm.exe

all: tiny tm

                                                                                                                                                                                                                                                                                                                                                                                                                       Tiny_scanner/PARSE.C                                                                                0000644 0002260 0002114 00000012065 14317021021 013761  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: parse.c                                    */
/* The parser implementation for the TINY compiler  */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

static TokenType token; /* holds current token */

/* function prototypes for recursive calls */
static TreeNode * stmt_sequence(void);
static TreeNode * statement(void);
static TreeNode * if_stmt(void);
static TreeNode * repeat_stmt(void);
static TreeNode * assign_stmt(void);
static TreeNode * read_stmt(void);
static TreeNode * write_stmt(void);
static TreeNode * exp(void);
static TreeNode * simple_exp(void);
static TreeNode * term(void);
static TreeNode * factor(void);

static void syntaxError(char * message)
{ fprintf(listing,"\n>>> ");
  fprintf(listing,"Syntax error at line %d: %s",lineno,message);
  Error = TRUE;
}

static void match(TokenType expected)
{ if (token == expected) token = getToken();
  else {
    syntaxError("unexpected token -> ");
    printToken(token,tokenString);
    fprintf(listing,"      ");
  }
}

TreeNode * stmt_sequence(void)
{ TreeNode * t = statement();
  TreeNode * p = t;
  while ((token!=ENDFILE) && (token!=END) &&
         (token!=ELSE) && (token!=UNTIL))
  { TreeNode * q;
    match(SEMI);
    q = statement();
    if (q!=NULL) {
      if (t==NULL) t = p = q;
      else /* now p cannot be NULL either */
      { p->sibling = q;
        p = q;
      }
    }
  }
  return t;
}

TreeNode * statement(void)
{ TreeNode * t = NULL;
  switch (token) {
    case IF : t = if_stmt(); break;
    case REPEAT : t = repeat_stmt(); break;
    case ID : t = assign_stmt(); break;
    case READ : t = read_stmt(); break;
    case WRITE : t = write_stmt(); break;
    default : syntaxError("unexpected token -> ");
              printToken(token,tokenString);
              token = getToken();
              break;
  } /* end case */
  return t;
}

TreeNode * if_stmt(void)
{ TreeNode * t = newStmtNode(IfK);
  match(IF);
  if (t!=NULL) t->child[0] = exp();
  match(THEN);
  if (t!=NULL) t->child[1] = stmt_sequence();
  if (token==ELSE) {
    match(ELSE);
    if (t!=NULL) t->child[2] = stmt_sequence();
  }
  match(END);
  return t;
}

TreeNode * repeat_stmt(void)
{ TreeNode * t = newStmtNode(RepeatK);
  match(REPEAT);
  if (t!=NULL) t->child[0] = stmt_sequence();
  match(UNTIL);
  if (t!=NULL) t->child[1] = exp();
  return t;
}

TreeNode * assign_stmt(void)
{ TreeNode * t = newStmtNode(AssignK);
  if ((t!=NULL) && (token==ID))
    t->attr.name = copyString(tokenString);
  match(ID);
  match(ASSIGN);
  if (t!=NULL) t->child[0] = exp();
  return t;
}

TreeNode * read_stmt(void)
{ TreeNode * t = newStmtNode(ReadK);
  match(READ);
  if ((t!=NULL) && (token==ID))
    t->attr.name = copyString(tokenString);
  match(ID);
  return t;
}

TreeNode * write_stmt(void)
{ TreeNode * t = newStmtNode(WriteK);
  match(WRITE);
  if (t!=NULL) t->child[0] = exp();
  return t;
}

TreeNode * exp(void)
{ TreeNode * t = simple_exp();
  if ((token==LT)||(token==EQ)) {
    TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
    }
    match(token);
    if (t!=NULL)
      t->child[1] = simple_exp();
  }
  return t;
}

TreeNode * simple_exp(void)
{ TreeNode * t = term();
  while ((token==PLUS)||(token==MINUS))
  { TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      t->child[1] = term();
    }
  }
  return t;
}

TreeNode * term(void)
{ TreeNode * t = factor();
  while ((token==TIMES)||(token==OVER))
  { TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      p->child[1] = factor();
    }
  }
  return t;
}

TreeNode * factor(void)
{ TreeNode * t = NULL;
  switch (token) {
    case NUM :
      t = newExpNode(ConstK);
      if ((t!=NULL) && (token==NUM))
        t->attr.val = atoi(tokenString);
      match(NUM);
      break;
    case ID :
      t = newExpNode(IdK);
      if ((t!=NULL) && (token==ID))
        t->attr.name = copyString(tokenString);
      match(ID);
      break;
    case LPAREN :
      match(LPAREN);
      t = exp();
      match(RPAREN);
      break;
    default:
      syntaxError("unexpected token -> ");
      printToken(token,tokenString);
      token = getToken();
      break;
    }
  return t;
}

/****************************************/
/* the primary function of the parser   */
/****************************************/
/* Function parse returns the newly 
 * constructed syntax tree
 */
TreeNode * parse(void)
{ TreeNode * t;
  token = getToken();
  t = stmt_sequence();
  if (token!=ENDFILE)
    syntaxError("Code ends before file\n");
  return t;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                           Tiny_scanner/PARSE.H                                                                                0000644 0002260 0002114 00000000744 14317021021 013767  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: parse.h                                    */
/* The parser interface for the TINY compiler       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _PARSE_H_
#define _PARSE_H_

/* Function parse returns the newly 
 * constructed syntax tree
 */
TreeNode * parse(void);

#endif
                            Tiny_scanner/README.DOS                                                                             0000644 0002260 0002114 00000003652 14317021021 014311  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  This is the README.DOS file included in the loucomp.zip file.
The other files in the distribution are the source code files 
in standard C for the TINY compiler and Tiny Machine simulator
as described in the text:

	Compiler Construction - Principles and Practice, by Kenneth C. Louden,
	PWS Publishing Co., 1997.

They are (with very minor variations) all the files as listed in Appendices
B and C of the text.

At the top level are:

     The file you are now reading (README.DOS):

     The sixteen files as listed on page 23 of the text (which are
     used to make the TINY compiler)

     The tm.c source code file for the TM machine interpreter

     The TINY program of Figure 1.4, page 23 (called sample.tny)

     Two DOS executables tiny.exe and tm.exe for your convenience.

     A Makefile for the TINY compiler and TM simulator for Borland's
     MAKE utility (with minor edits this should work for other MAKEs).

There are also two subdirectories: lex and yacc (assuming you have
unzipped with the -d option).

The lex subdirectory contains the single file tiny.l
as described in the text on pages 90-91, which can be used to build
a lex/flex version of the scanner.

The yacc subdirectory contains the two files tiny.y and globals.h 
as described on pages 243-245 of the text, which can be used 
to build a Yacc/Bison version of the parser. Note that, due to
the considerable variation among Yacc/Bison versions, these files
will probably need some minor editing in order to get them to
work correctly.

All source code has been tested with the Borland 3.0 and 4.0 compilers,
as well as with the Gnu C compiler and the Sun Ansi C compiler (version 2.0).
Any Ansi C compiler should be usable to compile this code, but there is
no guarantee that your favorite compiler will work. Nevertheless, if you
have a problem, I would appreciate hearing about it, and I will respond if I
can find a solution.

                                                                                      Tiny_scanner/SAMPLE.TM                                                                              0000644 0002260 0002114 00000001630 14317021022 014223  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                    0:     LD  6,0(0) 
  1:     ST  0,0(0) 
  2:     IN  0,0,0 
  3:     ST  0,0(5) 
  4:    LDC  0,0(0) 
  5:     ST  0,0(6) 
  6:     LD  0,0(5) 
  7:     LD  1,0(6) 
  8:    SUB  0,1,0 
  9:    JLT  0,2(7) 
 10:    LDC  0,0(0) 
 11:    LDA  7,1(7) 
 12:    LDC  0,1(0) 
 14:    LDC  0,1(0) 
 15:     ST  0,1(5) 
 16:     LD  0,1(5) 
 17:     ST  0,0(6) 
 18:     LD  0,0(5) 
 19:     LD  1,0(6) 
 20:    MUL  0,1,0 
 21:     ST  0,1(5) 
 22:     LD  0,0(5) 
 23:     ST  0,0(6) 
 24:    LDC  0,1(0) 
 25:     LD  1,0(6) 
 26:    SUB  0,1,0 
 27:     ST  0,0(5) 
 28:     LD  0,0(5) 
 29:     ST  0,0(6) 
 30:    LDC  0,0(0) 
 31:     LD  1,0(6) 
 32:    SUB  0,1,0 
 33:    JEQ  0,2(7) 
 34:    LDC  0,0(0) 
 35:    LDA  7,1(7) 
 36:    LDC  0,1(0) 
 37:    JEQ  0,-22(7) 
 38:     LD  0,1(5) 
 39:    OUT  0,0,0 
 13:    JEQ  0,27(7) 
 40:    LDA  7,0(7) 
 41:   HALT  0,0,0 
                                                                                                        Tiny_scanner/SAMPLE.TNY                                                                             0000644 0002260 0002114 00000000407 14317021022 014356  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  { Sample program
  in TINY language -
  computes factorial
}
read x; { input an integer }
if 0 < x then { don't compute if x <= 0 }
  fact := 1;
  repeat
    fact := fact * x;
    x := x - 1
  until x = 0;
  write fact  { output factorial of x }
end
                                                                                                                                                                                                                                                         Tiny_scanner/SCAN.C                                                                                 0000644 0002260 0002114 00000013145 14317021022 013634  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: scan.c                                     */
/* The scanner implementation for the TINY compiler */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"

/* states in scanner DFA */
typedef enum
   { START,INASSIGN,INCOMMENT,INNUM,INID,DONE }
   StateType;

/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];

/* BUFLEN = length of the input buffer for
   source code lines */
#define BUFLEN 256

static char lineBuf[BUFLEN]; /* holds the current line */
static int linepos = 0; /* current position in LineBuf */
static int bufsize = 0; /* current size of buffer string */
static int EOF_flag = FALSE; /* corrects ungetNextChar behavior on EOF */

/* getNextChar fetches the next non-blank character
   from lineBuf, reading in a new line if lineBuf is
   exhausted */
static int getNextChar(void)
{ if (!(linepos < bufsize))
  { lineno++;
    if (fgets(lineBuf,BUFLEN-1,source))
    { if (EchoSource) fprintf(listing,"%4d: %s",lineno,lineBuf);
      bufsize = strlen(lineBuf);
      linepos = 0;
      return lineBuf[linepos++];
    }
    else
    { EOF_flag = TRUE;
      return EOF;
    }
  }
  else return lineBuf[linepos++];
}

/* ungetNextChar backtracks one character
   in lineBuf */
static void ungetNextChar(void)
{ if (!EOF_flag) linepos-- ;}

/* lookup table of reserved words */
static struct
    { char* str;
      TokenType tok;
    } reservedWords[MAXRESERVED]
   = {{"if",IF},{"then",THEN},{"else",ELSE},{"end",END},
      {"repeat",REPEAT},{"until",UNTIL},{"read",READ},
      {"write",WRITE}};

/* lookup an identifier to see if it is a reserved word */
/* uses linear search */
static TokenType reservedLookup (char * s)
{ int i;
  for (i=0;i<MAXRESERVED;i++)
    if (!strcmp(s,reservedWords[i].str))
      return reservedWords[i].tok;
  return ID;
}

/****************************************/
/* the primary function of the scanner  */
/****************************************/
/* function getToken returns the 
 * next token in source file
 */
TokenType getToken(void)
{  /* index for storing into tokenString */
   int tokenStringIndex = 0;
   /* holds current token to be returned */
   TokenType currentToken;
   /* current state - always begins at START */
   StateType state = START;
   /* flag to indicate save to tokenString */
   int save;
   while (state != DONE)
   { int c = getNextChar();
     save = TRUE;
     switch (state)
     { case START:
         if (isdigit(c))
           state = INNUM;
         else if (isalpha(c))
           state = INID;
         else if (c == ':')
           state = INASSIGN;
         else if ((c == ' ') || (c == '\t') || (c == '\n'))
           save = FALSE;
         else if (c == '{')
         { save = FALSE;
           state = INCOMMENT;
         }
         else
         { state = DONE;
           switch (c)
           { case EOF:
               save = FALSE;
               currentToken = ENDFILE;
               break;
             case '=':
               currentToken = EQ;
               break;
             case '<':
               currentToken = LT;
               break;
             case '+':
               currentToken = PLUS;
               break;
             case '-':
               currentToken = MINUS;
               break;
             case '*':
               currentToken = TIMES;
               break;
             case '/':
               currentToken = OVER;
               break;
             case '(':
               currentToken = LPAREN;
               break;
             case ')':
               currentToken = RPAREN;
               break;
             case ';':
               currentToken = SEMI;
               break;
             default:
               currentToken = ERROR;
               break;
           }
         }
         break;
       case INCOMMENT:
         save = FALSE;
         if (c == EOF)
         { state = DONE;
           currentToken = ENDFILE;
         }
         else if (c == '}') state = START;
         break;
       case INASSIGN:
         state = DONE;
         if (c == '=')
           currentToken = ASSIGN;
         else
         { /* backup in the input */
           ungetNextChar();
           save = FALSE;
           currentToken = ERROR;
         }
         break;
       case INNUM:
         if (!isdigit(c))
         { /* backup in the input */
           ungetNextChar();
           save = FALSE;
           state = DONE;
           currentToken = NUM;
         }
         break;
       case INID:
         if (!isalpha(c))
         { /* backup in the input */
           ungetNextChar();
           save = FALSE;
           state = DONE;
           currentToken = ID;
         }
         break;
       case DONE:
       default: /* should never happen */
         fprintf(listing,"Scanner Bug: state= %d\n",state);
         state = DONE;
         currentToken = ERROR;
         break;
     }
     if ((save) && (tokenStringIndex <= MAXTOKENLEN))
       tokenString[tokenStringIndex++] = (char) c;
     if (state == DONE)
     { tokenString[tokenStringIndex] = '\0';
       if (currentToken == ID)
         currentToken = reservedLookup(tokenString);
     }
   }
   if (TraceScan) {
     fprintf(listing,"\t%d: ",lineno);
     printToken(currentToken,tokenString);
   }
   return currentToken;
} /* end getToken */

                                                                                                                                                                                                                                                                                                                                                                                                                           Tiny_scanner/SCAN.H                                                                                 0000644 0002260 0002114 00000001223 14317021022 013633  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: scan.h                                     */
/* The scanner interface for the TINY compiler      */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _SCAN_H_
#define _SCAN_H_

/* MAXTOKENLEN is the maximum size of a token */
#define MAXTOKENLEN 40

/* tokenString array stores the lexeme of each token */
extern char tokenString[MAXTOKENLEN+1];

/* function getToken returns the 
 * next token in source file
 */
TokenType getToken(void);

#endif
                                                                                                                                                                                                                                                                                                                                                                             Tiny_scanner/SYMTAB.C                                                                               0000644 0002260 0002114 00000006754 14317021022 014117  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: symtab.c                                   */
/* Symbol table implementation for the TINY compiler*/
/* (allows only one symbol table)                   */
/* Symbol table is implemented as a chained         */
/* hash table                                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

/* SIZE is the size of the hash table */
#define SIZE 211

/* SHIFT is the power of two used as multiplier
   in hash function  */
#define SHIFT 4

/* the hash function */
static int hash ( char * key )
{ int temp = 0;
  int i = 0;
  while (key[i] != '\0')
  { temp = ((temp << SHIFT) + key[i]) % SIZE;
    ++i;
  }
  return temp;
}

/* the list of line numbers of the source 
 * code in which a variable is referenced
 */
typedef struct LineListRec
   { int lineno;
     struct LineListRec * next;
   } * LineList;

/* The record in the bucket lists for
 * each variable, including name, 
 * assigned memory location, and
 * the list of line numbers in which
 * it appears in the source code
 */
typedef struct BucketListRec
   { char * name;
     LineList lines;
     int memloc ; /* memory location for variable */
     struct BucketListRec * next;
   } * BucketList;

/* the hash table */
static BucketList hashTable[SIZE];

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert( char * name, int lineno, int loc )
{ int h = hash(name);
  BucketList l =  hashTable[h];
  while ((l != NULL) && (strcmp(name,l->name) != 0))
    l = l->next;
  if (l == NULL) /* variable not yet in table */
  { l = (BucketList) malloc(sizeof(struct BucketListRec));
    l->name = name;
    l->lines = (LineList) malloc(sizeof(struct LineListRec));
    l->lines->lineno = lineno;
    l->memloc = loc;
    l->lines->next = NULL;
    l->next = hashTable[h];
    hashTable[h] = l; }
  else /* found in table, so just add line number */
  { LineList t = l->lines;
    while (t->next != NULL) t = t->next;
    t->next = (LineList) malloc(sizeof(struct LineListRec));
    t->next->lineno = lineno;
    t->next->next = NULL;
  }
} /* st_insert */

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
int st_lookup ( char * name )
{ int h = hash(name);
  BucketList l =  hashTable[h];
  while ((l != NULL) && (strcmp(name,l->name) != 0))
    l = l->next;
  if (l == NULL) return -1;
  else return l->memloc;
}

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE * listing)
{ int i;
  fprintf(listing,"Variable Name  Location   Line Numbers\n");
  fprintf(listing,"-------------  --------   ------------\n");
  for (i=0;i<SIZE;++i)
  { if (hashTable[i] != NULL)
    { BucketList l = hashTable[i];
      while (l != NULL)
      { LineList t = l->lines;
        fprintf(listing,"%-14s ",l->name);
        fprintf(listing,"%-8d  ",l->memloc);
        while (t != NULL)
        { fprintf(listing,"%4d ",t->lineno);
          t = t->next;
        }
        fprintf(listing,"\n");
        l = l->next;
      }
    }
  }
} /* printSymTab */
                    Tiny_scanner/SYMTAB.H                                                                               0000644 0002260 0002114 00000001677 14317021022 014123  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: symtab.h                                   */
/* Symbol table interface for the TINY compiler     */
/* (allows only one symbol table)                   */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _SYMTAB_H_
#define _SYMTAB_H_

/* Procedure st_insert inserts line numbers and
 * memory locations into the symbol table
 * loc = memory location is inserted only the
 * first time, otherwise ignored
 */
void st_insert( char * name, int lineno, int loc );

/* Function st_lookup returns the memory 
 * location of a variable or -1 if not found
 */
int st_lookup ( char * name );

/* Procedure printSymTab prints a formatted 
 * listing of the symbol table contents 
 * to the listing file
 */
void printSymTab(FILE * listing);

#endif
                                                                 Tiny_scanner/TINY.EXE                                                                               0000644 0002260 0002114 00000117440 14317021022 014135  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  MZ P s @ ] ��
�       >    �Pjr                               �  4  $  �  j  G  C  =  r  c  @  a%  R%  ����I  �H  �H  H  �G  �G  �G  �G  qL  FL  &L  �K  hK  -K   K  K  cJ  8J  �I  �I  �W  �W  �W  vY  ,a  a  �l  �l  �l  w  �v  �|  s|  �|    �~  �~  8~  +~  #~  y�  e�  -�  ��  y�  G�  +�  �  k  N  @  8  4  ��  v�  n�  j�  *�  �  �  �  у  Ã  ��  ��  O�  "�  �  ��  ��  �  ��  ^�  I�  ;�  1�  )�  ́  ��  ��  }�  m�  ;�  �  �  ݆  Ն  ц  ��  ��  K�  >�  6�  2�  �  م  �  �  �                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        ��.���0�!�. �, �ڣ� �� �� �.� �r�� ��3��؋������aC&8u��̀�ى� � �������� ��+�>Z
�� s� �>Z
�Ǩr(>�	r"���G;�r�>Z
 t�>�	 u� ;�w������ډ� �� �� +؎��JW�!_����ҋ��3�.���`��+���>�	vG�>� r@w�>� r7�X� �!r*�g��	�!r �H� �!r@�� H���I�!r
�X�  �!s�<3�U��%X.���B�Z�� �6� �6� �6~ �P�.��VW�Z�`�� _^�VW.��3��� &�� F��-�t�E R��Z_^Ë�L�F�!�_ R��Z� P�Y� 5�!�n �p �5�!�r �t �5�!�v �x �5�!�z �| � %�ʎں��!�� %�n �!�%�r �!�%�v �!�%�z �!ø �׋�;�t&�?�t&�O2�;�s���Ӄ���;�t��&�? &��t&�_��&�W�ô �׋�;�t&�?�t&8gr&�g�Ӄ���;�t��&�? &��t&�_��&�W���   U��VW�~3�3��������P����X»� �����A�ـ9 u���� _^]��  VW�v��Y�F��^�ۋ�`��t�t�4�v�EB���u��uCj��+Y���F�j��+Y�D�\�F��F�D�\�G  �^�ۋ�`�D�^�ۉ�`�'�|��}�} u�j�+Y�E�]�F��]�G  _^���  VW�~W��Y�F��^�ۋ�`��t�t�4W�A���u��u������D� _^���  VW�~h� W�L5��h� W�B5���F�  �j�^�ۃ�` t[�^�ۋ�`�L�D�F��4h� W�5���th� W�5����^��7h W��4���^��G�F��~� u�hW��4���t�u��F��~�� |�_^��U��VW�~�v�߃�w`�.���Vh
�Wh�0h!�+h$�&h'�!h*�h-�h0�h3�h6�h9�h<�64�h4��� VhA�VhO�
Vh]�Whh�64�F4��_^]Ú�bbbbbbbb��hrm����w|�U��VWj��)Y���u�6�h{�64��3���(3��	����   G��|��D  �D
  �F�D���D��� _^]�U��VWj�)Y���u�6�h��64�3���-3��	����   G��|��D  �D
 �F�D���D�D  ��� _^]��  VW�v�u3��5V�@Y@�F��v��)Y���u�6�h��64�13���VW�?����� _^��U��V3��h��64�
3��F;6|�^]�U��VW�v��� ����|
 ug�\��wN�.��h��64��2���Gh��64�2���8�th���th��64�2���h�64�2���h	�64�2��� �i�|
uV�D�t= t"= t%�5h�64�Z2��h$�t�����&�th&��th1�64�42���h9�64�%2���hO�64�2��3������0�
�YG��|��t�t�	��._^]�7FU]oU��b;d|U���62h� h/�;/���t1�>� th/�6�h��64�1��h/�X>Y�d�b  ���
�f ��]���b�b��/]�]�U��>f u�b]�U��V3��"������h�v�w=���u������j�F��|ٸ
 � ^]��  VW�F�  3���5��F��F� �߃�v�:�.���	�F������]
t� � �F������]
t� � �~�:u� � �~� t�~�	t�~�
u�F�  �n�~�{u
�F�  � �^� �F���F��
 ��	.�;F�t�����:.�g�F�  3��2� �-� �(� �#� �� �� �� �� �
� �� � � �F�  �~��u� 3���~�}u3��q� �~�=u� ����F�  � �V�F���؊�]
� �u���F�  � � �6�F���؊�]
� �u�g��F�  � �
 �Wh��64��/��� � � �~� t�~�(�^��F����F���u�^�Ƈ ��
u	h�#�Y����t�_��>� t�6�h��64�e/��hV������� _^����( ) * + - / ; < = ������������ 	 	@	U��VW�v�t5V�VY3���v�v����0�����G��|�V�VY�v�v�t�����_^]�U��~ u]��]�]�U��V�v�D
�t= t;�m�D= t= t�&�t���Y=��u
����P�j �t�t�>����� �6�D= t�&�t���Y=��u
����P�j �t�t�
����� �� ^]�U��h5
hF
�v�����>� th��64�.���64��Y]�U��V�v�v�th��64��-���� ^]�U��V�v�D
�t[= t� �D�t= t<= t7�<��u	�\�t
hV�����|t�|u�D ��D �	�D �� �k�\��w]�.�����uh �4�U����C��th7�4�@����.��thW�4�+�����\�uhr�t������ �� ^]Ø����U��h h5
�v�����]��  ���F��F���;�}�����F�����U��V�v;6�~h�� Y�6�^]�U�졐��]�U��>� t�vh��66�,��]�U���v
�v�v�v����Ph��66�m,���>� t�vh��66�V,��h��66�I,����;�}����]�U���v
�v�v�v����Ph��66�,���>� t�vh��66��+��h��66��+����;�}����]�U��j��@�V+�R�v�v�6�h��66�+�����>� t�v
h��66�+��h��66�+����;�}����]��  VW�v�D�؃�v��.��7�>� th ��Y�<�D�F��D�F�W�Yj�C�Y�F�h��Y�v��nYj�,�Y�F�h$�o�Yj ��Y�F��v��9�YhE�v�j hA�����?��v��3Yj ���Y�F��v���YhY�v�jhU��������>� thd��Y�� �>� thj��Y�<�D�F�j ��Y�F�ht���YW��Y�v���Yh��v�j h������>� th���Y� �>� th���Y�4�Y�t��Y�F�h�j�v�j h�����
�>� th��|�Y�Jh�j j j h�����
�t�k�Y�F�hj�v�j h�����
��4�2Yhj j j h�O���� _^�ìT���  V�v�D�t{= t= t5���>� th&���Yh3j �tj h/�\���
�>� th>���Y��>� thG���Y�t���Y�F�hPj�v�j hM� ���
�>� th^��Y�w�>� thd��Y��F��D�F��v��gYhmj����Pj hj�����
�v��HYh~j����Pjh{����
�D- �؃�v�� �.��Eh�j jj h��(h�j jj h��h�j jj h��h�j jj h���� h�j jj h������
h�jjj h��A���
h�j j j h��/���
h�jjjh�����
h�j jj h��Th�j jj h�����
h	jjj h�����
hj j j h�����
h'jjjh#�����
h=j jj h9����
�	hG�5�Y� �>� th]�%�Y�� ^���u9GUcU��V�v�t$�D
�t= t�V�!��V���Y�� �t���Y^]�U��VW�~W�74Y P�FY��hcV��3��WV�3��hj��YV��Yh���Yh�j j jh��	���
h�j j j h������
h��y�Y�v�a�Yh��k�Yh�j j j h��w���
_^]�U��h �64��&���v�6�h�64��&���� ]�U��0;Fu���0�!h"��Yh�60����h7�64�&��]��  VW�R �����(j��Y�C �F��~� t�u	�F������	�F��E�~��>0 t�>0t�>0t�>0u���� _^��U��V3��0����w"�.��"�M �� ��� ��� ��+���h>�	�Yh�60�9������0� ��� ^]����������U��Vj ��Y��j���Y�t�� �j���Y�t���D�>0uj���Y�t����Dj��Y��� ^]�U��Vj�m�Y��j��Y�t����j��Y�t� �D��� ^]�U��Vj�;�Y���t�>0
u
h���Y�Dj
�_�Yj�Y�Y�t�_ ���� ^]�U��Vj���Y��j�7�Y�t�>0
u
h��Y�Dj
��Y��� ^]�U��Vj���Y��j	��Y�t�	 ���� ^]�U��VW�@ ���>0t�>0u(j ���Y���t
�5�0�E���60��Y�t� �D��� _^]�U��VW�> ���$j ��Y���t�<�0�D���60��Y� �E�>0tՃ>0t΋�� _^]�U��VW�> ���$j �f�Y���t�<�0�D���60�;�Y� �D�>0tՃ>0t΋�� _^]�U��V3��0=
 t-= t= tD�Uj��Y���t�>0u
h�Y�Dj�.j���Y���t�>0
u
h�6�Y�Dj
�j��Y�����j��Y�hS�}�Yh�60����?�0� ��� ^]��  �,�0���F��>0 thh�C�Y�F������|  VW�~�~t�5h�h��#��j��Y�u�F�P�g/��j.�F�P��.���uh��F�P�.��h��F�P�"���2�>2 u�F�Ph�h���"��j�Y�4��F�Ph��64�"���G��F��>� th��64�"���v���Y�>� uJ�>� th��64�o"���v��'�Y�>� th��64�T"���v��@�Y�>� th�64�9"���>� uoh,�F�P�.���F�j�F� P������v��F�PV��.��h.V�-��h2V��!���6�>6 uVh4�(��j�YV�v��B����66�Y�62�Y3�� _^��VW�HP�� P�YY_^�U���VW�v�G.Y�F�@P�v�v�%���FF�_^��]�VW� P��Y��_^�U��VW�>h u� ��hۋF��8�h3�_^]�U��VW�v�.Y_^]�U��VW�v���Y_^]�U��VW��9Fu	�v�Y��v�v�YY_^]�U��VW�v�v���YY_^]�U��VW�C2��V�!r	�^�3��P�v_^]�U��VW�C��V�N�!r3��P�W_^]�U��VW�v�N-YP�v� P�.��_^]�VW_^�U��VW�~ u��h�h���8�>h u����j�!���~ u�~ u�l�n�v��Y_^]� U��VW3�PP�v��_^]�U��VW� P3�P�v��_^]�VW3�P� P3�P�x�_^�VW� PP3�P�h�_^�U��VW�5�F�!���_^]�U��VW�%�F�V�!_^]�YQ3��YQ� �YQ� �YQ� UVW����F
�V�^�N�u�ti�te�� u�y
���؃� ���y
���ۃ� ����  W3�3���������;�rw;�r+��@��[�� t�Ƌ����� t���؃� _^]� ���� t�3���[S��s�������ـ����ˀ��3�����}���у��� �/�s�� ���������Њ�% ��}���у��� ��+�s�� �����2�+ӊ���Њ�% �U��VW�V�|��X~�W ��	�ڊ��	������;l���	���� ���_^]� U��VW�v���F_^]� U��VW� D�^�!�%� _^]�U���"VW�~
�^��$wX��rS�F�N�}�~ t�-G���؃� �v���+�����F�	��+���F�u��N�����N�,
s:�F��� ��F
_^��]� U��VW3�P�v�v�
 P� P�aP�h�_^]� U��VW�^ہ��	���B�F
�^�N�V�!r�P����_^]�U��VW�V�~ u�Fx�v�u�<
���P�v��YYP���@
P�v��(YY�F_^]� U���VW�v3�P�^�?�u� �� �^�P���F�F�P�v� �YY�t̋F_^��]�    ��          ��     >U��� VW�  �L�43�PPPP�  P�P3�PP�F
P�F�P��-YY�H
�F�6� 6�  �F�P�P�>��_^��]�U���VW�J
�F��F�J
�F�_^��]�U���VW�~ t�F�� �F��J
�v��Y�F��u�>J
 u�F�_^��]�U��VW�v�v�@-YY�^�G�^�G6� 6�  �F_^]�    F
��   ��          ��     ;U���VW�  �S�-�F� 3�P�L
P�F�P��aYY�F�P�F
P��)� P�F�P�&d��
�F�6� _^��]�VW6�. 6�  3�P�F
P�-YY_^�  & �� . 2               Á    6 string                & �� . :               F    > xalloc                   U��VW�~ t(6�. 6�  3�P�v�n,YY�Ft	�v�a�Y��3�_^]�  & �� , 0               �J    4 xmsg              V����t�����������^�Q����ЊŊ���Yˊ�% ��;�u;��U��VW�^����	t� P��?�^�N�V�!r�P�g�_^]�VW� �%���Ǉ�	  �ڱ��Ƈt�����p���㉇~B;�	rՠt�P�{�Y�u�&r��� P�st� �3�P3�P�pP�a$�����P�H�Y�u�&���� P��t� �3�P3�P��P�.$��_^�U��VW�A�V�!r3��P��_^]Ê�� ������ ���'@'��U��� VW�F�  �F�P �F�  �FW���2����I_�6�G�N�u/SQR��j�+���j�PW�v�V
�u�F� �F�P ~j�ZY[����j��~��~��v�
�t<%t6�G�N���������v�<%t�~�3ɉN�N��N��F����F�����2�Ћ؀� ��`s��e��v��.��o$��� w��N��Ѐ� w�N��ŀ� w�~�+t�V�뵃f����N� �맀� wM�F� u)�N����8�~6��F��s�y�؃N��F���o���u׉F����b���sʵ�F��U��,0���w��F��|����������F��3���u��F��t����������F����N��e��N� �f���Y���
�
������F� �V�3҈V��~6���
�F��V��~6��GG�v�F� t6�GG�~�~��u�u�~� u6� ����N�RPW�ǘP�F�PS����V��}�� �� �V��v�~��^6�7CC�^�F�  t6�CC�^���:�Z��6� �F� �f���N�+��ϋV�;���� �v�V��~6��F�~�2�6�� �� �v�V��~�F�  u6�=�F��6�=�F���u�^�P�;N�v�N�� �v�V��~�N��}� WQ�^�SR� #F�P�F�� t	� �F
��F� P��Y�~��F� t�V��~���&�=-uI+�~�V�&�=-t�F�
�tO&��~� ~
�N��}�N�������~��^�� #F�= u�f���ou�~� �F� ���xt��Xu�N�@KK�n�}�F�  N��F� u�� �y�K;���F�@ t�0�h��F��b��V��~'+�+�&�<-t< t<+u&��C�IK����0�8������+�&�6�G�N��+����~	�˰ �����U��v�~�F�  u6�=�F�6�=�F�P *F�F�&��F� tGG&�  ���v��~��%����
�u��~�P}����~� t�����F�_^��]� � � !� 5!B!�!�!�!� �!�!�!�!"�"d"�"$?$?$?$� � ���Ӌ�&�_�6�W6�G��@@6�G6�_6�w6�Gi6�G
  6�G  6� 6�G6� 6�G6� 6�6� �VW��_^�U���VW6� &�G
�F��F6� &�O&�G
6� &�_�F�_^��]�    �%                    ��   0%     U���VW�  �F%�6��6� &� u	6� &�_6� &�G�F��^��F� 6� &�_
�F�  ��<���F�6� _^��]�VW��_^�U���VW6� &�G�F��F6� &�O&�G6� &�_�F�_^��]�U���VW6� &� u	6� &�_6� &�G�F��^�6� &�_�k�_^��]�U���VW�FFt��3�;Fu	;Vu3��:�^^&��^��F��^��V��F�&+G��V��F��^�&�W�&�G��V��F��^�&�G_^��]�U���VW�FFt��3�;Fu	;Vu3��>�^^&�W&��V��F��^��V��F�&+G��V��F��^�&�W�&�G��V��F��^�&�G_^��]�VW6�   6�   6� 6� ��أ���6� &�G
6� ��_^�U��VW�F�ԁ� ;�s�� 3��	��  ���_^]�U��VW�F�V� �� ���u�� r
;�s�� �	��  ���_^]�U��VW�v��Y_^]�U��VW�F�RP��YY_^]�U���VW�^3ɋF3�����V��F��~� rw�~��v3���v���Y�F��~� t� P�v��v������F�_^��]Ü[��#�P��X% �= ���  tB�� �S��X% ��� t/f�ԃ��f�fXf��f5   fPf�f�fXf3��� f��t�� �            .;i(t7�ڎ �>  t.�k(�8��.;i(t� .�k(3�P� .�o(�#.�i(.�i(  .�k(  .�m(  .�o(R3�P�=��Î�� �   � .;i(t.&�>  u&�  [&  ��Ў�&�>  u&� �
&� ��Q ��&  �؃>  tá  &  ����  ��&� ��; t� � � &� .�m(���.�m(  �.�m(�t!�Ӝ���6� 6� � �ӝ&� � �.�m(� � �U��VW.�o(�V�t.;k(u�����.�o(_^]�P.�o(3�PP�u��% t� +�3�.�o(PR�\��XP3ۊܱ����.�o(SP�C��[=��t.�i(.�k(�ډ  � � �3���P3ۊܱ����.�o(SP�	��[=��t8% u.�k(.�k(�ډ  � � �SR�� 3�SP����Z[=��tB��3��Ë�)    �ڣ  � ��  �ۉ � �U��V�F���VW.�o(t^ �� rA����u;�����
�.�i(�t .�m(�t�ڎ�9  s� ;�u��0���������3���w��-�� � � .�o(_^]�S.�6q(V.�6s(V�s����u[���S�  �J� ��� ��t7��@����@��3����ʁ� v� �������� v�� ���� ����.�o(����Z� �.;k(tD����ǋ�+�&�6  &� P��&�  ��ю�&�>  t&�> �&�> �������ָ �S��&�  �S3�P���Z� �U��V
�F�^VW.�o(.�q(.�s(�t:���t> �� r>����u8�����
��&�  ;�rw�Ӹ ��J������RP�G����SP�3���3��.�o(_^]�U���VW�F@�F��� )F��F�? ���F�;�t:��f��� �F�� ;�v	��+� �F��v��6� �-QYY�Ѓ��u�F������V�F�� �� � ��� £� ��   3�_^��]� U��VW�� �� �V�F��r �� �� �V�F��w�v�v�@��u����3�_^]�U���VW�� 3ұ��� �� FV��|U=��wP�� �� �N�^��V��F��� �� �.�r-�� �� �V��F���w�� �� �V��F��v��v����u��������V��F�_^��]�U��VW�V�D�F�^�N
�!r�~ u����P�x�_^]�VW��\��r;�t�B �� _^�9�t#�w�t�6�� ;6�t���T �G�����3�������S���[��;�t�w��u��?��u����2 �?���t�����\�ߋ;�t�>��w�u�|���  Ë6��t�|�\�]��wÉ��_�_�VW��D�tR r6%��= s� �>� t���t��9s�_;�u��f �!� �� �3������97s��k���� _^�P3�PP��[[% t	3�RP��[[XP3�SP��[[=��t�؉���X@������[3��P3�SP���[[=��t�ء��G��X@������X3��)��7���@��\�u����Ë�SPQP��[���t����v����V�����F��$�[�^���Ë�;�w5��;�u���SP�+�[[�����]+�)���|B��ˋ��7��ك��VWU��^�F
�t7�t-���I�Ѓ������s� ;�rw�������O����P�e��S��3�[]_^�PSQRVWU.�.��݋���^&�?bt����7���F�= t,�~� t�~��u� P�+�Y��  �F P�
 P� P�V�����]_^ZY[X�PSQRVWU.�.��݋�����F�= t,�~� t�~��u� P���Y��  �F P� P� P�V�����]_^ZY[X�PSQRVWU.�.��݋�����F�= t,�~� t�~��u� P�{�Y��  �F P� P� P�V�����]_^ZY[X�PSQRVWU.�.��݋�����F�= t,�~� t�~��u� P�#�Y��  �F P�~ P� P�V�����]_^ZY[X�PSQRVWU.�.��݋�����F�= t3�~� t�~��u� P���Y��  �6��6��# P� � P�V�����]_^ZY[X�U��VW3ҋڊ��� ;Fu���	B��|���_^]�U���VW�>� u��y2���v��Y��=��u��  ���� ��ۋ���F���ۋF����~u5�>� u�# P�T�Y�������~ u
�6��6����1P�# �^�~u�E1P3�P�/����1P� �@�~u,�>� u:� P���Y������0P� P��������~u��0P� P�����F�_^��]�U���VW�v���Y��=��u� �V��ۋ���F�= tD�~� u#�F= t= u��3��#�L�!� P�6�Y����Ǉ�  �ڊ�� P�v�V�YY3�_^��]�U��VWU�v�+���
 � �]
�F�u��  ��+t��-uE�F��9w.��0r)����t�����
 �ᗇ��⒗�ъF��9w��0s�M|���؃� ]_^]�U��VW�v��Y_^]�U��VW�N�C�F�V�!r��P��_^]�U��VW�V;�	r	� P�������Ǉ�	  R� Y_^]�U��VW�>�^�!r�Ǉ�	  3��P��_^]�U��VW�v���Y_^]�U���VW�F;�	r� P�]�^����	t� �O� D�^�!rA�u8�B3ɋ��!r1RP�B3ɋ��!�F��V�ZYr� B�!r;V�rw;F�r� �3��P�-�_^��]�U���VW�F����~ ty�^�G;Fun�^� t�? }	S�e Y�uW�^�Gt�w�o�Y�^� |�G�P���Y�F��^�G  �G  �  �G�� t3�PP�w���P���Y�^�G  �F�_^��]�U���VW�~ u�� �v�^�G;Fuf�^�? |+�Gu�F 9G
uR�^�  �F 9G
u@�G�G
�8�^�G@�F�)P�G�G
P�G�P���;F�t�^�Gu	�O����3�_^��]�U���VW3ҋF�F���^���F���
t&�N~!�^�|�w
�G
�� ��v��Y��=��u̓��u�F�;Fu3���^�� �^�Gt3���F_^��]�U���VW�F�  ��	�F��F�p��^��GtS���Y�F��F��F��N��u�F�_^��]�U���VW�F�  �^�F���<ru
� �F� �"��wu����au�	�F�� �F� �3��x�^��F��+t�^�?+u$��tt��bu��+u�^�������F���F� ��tu�� @���bu�� ����	% �Ћ��Āt�N�@�l-I�^��^�F���F�_^��]� U���VW�v�F�P�F�P�#��^
�G�t#� }+�v��F�FP�v�n���^
�G
�}�^
�G��G  �D�^
�G�P�|�Y�t�^
�O � P�^
�Gt� �3�P3�P�v
�_���t�v
���Y3���^
�G  �F
_^��]� U���VW�F�p�^�� |��	���p�V��F�;�w�^�� |3���F�_^��]�U��VW�����u3��R�v�v3�P���_^]�U��VW�iAP�v�v�FP���_^]�U���VW�~ t�v�Y�F��u3�� �v�v��v��t�^^��G�� ����_^��]�U���VW�^�? }
�WB����^��3�+ЉF��^�G@u3�^�O
�? }!�I�ـ?
u�F���J�u����A�?
u�F���J�u�F�_^��]� U��VW�v�	�Y�t����P�~
u�^�? ~S�i��)FV�^�g_��  �G�G
�v
�v�v�G�P�Z�����u
=��u����3�_^]�U���VW� P3�PP�^�G�P�'���V��F����u=��u� �^�? }{�G�������	t]� P3�PP�^�G�P������V��F����u=��u�W3�P�v��v��^�G�P�������u=��u�������.�V��F��V��F��v�|��F�V���v�m��)F�V��V��F�_^��]�U���VW�F� �F�p��^��G% = uS��Y�F��F��N��u�_^��]�U��VW�^�Gt���^�w�G�G
P�G�P����^��~�g�3��$�^�? u�G%�  �G��^�  �O���_^]� U��VW�F���S� Y_^]�U��VW�~ u� �^�? ~��9�^�? |�Gu�Gu	�^�O�w�^�O� � tS�=��ua�^��^�w
�G
��n�^�Gt���� P��P�^�G�P�����u.�^�G�P��Y= t	�^�O��^�G%�  �G�����>�u	�^�G@t��^�gߠ�� _^]�VW�pP�#�Y_^�U��VW�~�v�N����s��F_^]�U��VW�~�N�F����� t�	�I���s�_^]�U��VW�v�v�v������F_^]�U��VW�F;Fs�� ��3��v�~�N�t�N�O�� t��I+�+����s����_^]�U��VW�v�v�v�����F_^]�U��VW�N�<�V�!r�P���_^]� U��VW�^+�+Ҵ@�!_^]� U���VW�F�u	��	% �	F�� �F�3�P�v��YY�F��F��� �Fu�}��	!F�F��u� P�܃~��u6�>�	t�6�	�3�F�t3��� �F��F�t,�v3�P�M��F��}�� �Ft&�P P�K��� �v���Y��v�v��!��F��}t� �v�v� YY�F��|_3�P�v��r�YY�F���t!�N  �F�t"%�   P� P�v��M����Ft�v�����F�t�Ft�F�t� PP�v�����~� |0�Ft� �3��V�����P�F�t3��� ZЋ^�ۉ��	�F�_^��]�U���VW��N�� u
��� u� �V��"N
��=�!r�F��F%�� ��^�ۉ��	�F��P�1�_^��]�U��VW�v�v��YY_^]�U���VW�V�� ;l}�>�  |�� ۋ��F���F�i�t�ڀ? t��PS�y���P�wP�n�����P�v��a���P�zP�V���_^��]�U��VW�iAP��P�v�FP���_^]�U��VW�F���S�F�P� YY_^]�U��VW�F���^�?�}5��w
�G
��Gu��>�
t
�>�t��v��Y�u�� �� �^�G�u�Gu
�^�O�� �^�O � tP�? tS�i�Y�t� �^�G�؉�w
�G
����Gu� �>�
t
�>�t� �v�,�Y�u� �x�^�G�������	t� P3�PP�^�G�P�ڃ��>�
u!�^�G@u� P�|P�G�P���= u� P��P�^�G�P���= t�^�Gu	�O������� _^]�U��VW��P�v��YY_^]�U���VW�F�F��^�Gt)��v�^�F��P�}�YY=��u�q�F�N�u��h�^�G@u�� � u� �G;FsX�? tS�!�Y�t�6�^�G�������	t� P3�PP�^�G�P�ك��v�v�^�G�P�#��;Fu�� �� �^�F|�? u
���+G���v��Y�t�� �v�v�^�w
�S����^�F��FG
� �^�G�������	t� P3�PP�^�G�P��؃��v�v�^�G�P���;Ftf�`�^� t>�0�^�}�w
�G
�^�F��� ��v�^�F�7��YY=��t%�F�N�u���v�v�^�G�P�	��;Ft3���F�_^��]� U���VW�F;�	r
� P�N�� �F@= r�^����	t3�� �v�v�v�ۃ��F�@= r�^����	@u�F��b�N��v������<t-<t������S� P�F�P�v�Hۃ�[��F��;�u�� S� P���PQ�v�׃��^ہ��	 [+��_^��]�U��VW�^�G;Ft� �~~� �~
�v� �>� u�~�u�� ��>~ u�~pu�~ �^�? t� P3�PPS�����^�Gt�w��Y�^�g��G  �F �G�G
�~tJ�~
 vD�jeI�~ u�v
�N�Y�F�t	�^�O������^�F�G
�G�F
�G�~u�O3�_^]�U��VW��~��2�����u��~������+����� t�I���s��_^]�U��VW��v�^�� t	�:�t"�t�:�t"�t:�t"�u�3��F�D�_^]�U��VW�؎��3��؋~��2������ы��v�D��]�+�_^]�U��VW��~��2������ы~�F_^]�U���VW�N�F�  ��V��ي��:tB�ڀ? u�A�F��ـ? uދF�_^��]�U��VW�؎��~3��������H_^]�U��VW�؎���~��2��^���+ً~�����F_^]�U��� VW�F;�	r
� P�[���F@= s3��� �^����	t� P3�PP�v�5Ճ��^����	@u�v�v�v�� ��� �^ہ��	���F�F��F�F��Y�N��^��F���F�<
u���A�يF��A��v���+Ё�� |/��+ЉV�RP�v�j ����;F�t���u����K�F+F��>��v��~� u���v���+ЉV����v*R��v�P�v�' ����;F�t���u�����F�+F���F_^��]�U��VW�^����	t� P��@�^�N�V�!rP�^ہ��	 X�P��_^]�U��VW�v�v�v����_^]�U��VW�~ u� P�5�Y�F�t�v�v�YY�^�F�G6� 6�  �F_^]�zH      zH   ��      �G  ��     �GU���"VW�  ��G��3�PPPP�  P�KHP3�PP�F�F�P�F�P�;YY�^ދG�F�6� 6�  �F�P�zHP���_^��]�U��VW�v�v�YY�^�G�^�G6� 6�  �F_^]�  & �� . :               �H    > xalloc  �H                 U��VW�~ t(6�. 6�  3�P�v��YY�Ft	�v���Y��3�_^]�  & �� , 0               �J    4 xmsg              U���VW�F�  �F�p��^��GtS��Y�F��F��F�;�	r�_^��]�U���VW�F� �F�p��^��GtS�j�Y�N��F��~� u�_^��]�>L   ��          ��     ��    �IU���VW�  ��I��ڃ~ u� P���Y�F�t6� P���Y�F��t�F� �vP�04YY6�. 6�  �F� �F��^�6� 6�  �F�6� �F_^��]�>L   ��          ��     ��    6JU���VW�  �DJ�4ڃ~ u� P�W�Y�F�t8� P�H�Y�F��t!�F� �^�7P�3YY6�. 6�  �F� �F��^�6� 6�  �F�6� �F_^��]�U��VW6�. 6�  �~ t'6� 6�  � P�^�7��6YY�Ft�v���Y_^]�L      K  ��U���VW�  �K�j�3�PPPP�ZJP3�PP�v�F�P��YY�F�P�LP�e��_^��]�>L   ��          ��     ��    fKU���VW�  �tK�ًF;FtR6� 6�  � P�^�7�6YY� P��Y�F��t!�F� �^�7P�U2YY6�. 6�  �F� �F��^��F�V�6� _^��]�  & �� , 0               �J    4 xmsg               
 QL  string *   & �� . 2               Á    6 string              VW�܉�RP�_^�U��VW�~ t��F���F���F
���F���F��_^]�U���VW�FFu���=�^�V�F&G�V��F������u��� ��^�&��ڈB�^��F�&�? uܸ�_^��]�U���
VW�V�F;V
u;Ftj�^&�G�^&;GuR�^&��^&;uD�^�V�F&G�V��F��^�V
�F&G�V��F��^�&�����F��^�&���F��F�;V�t3���uڸ _^��]�U���
VW�^�V�F&G�V��F��^�&�W&��V��F��F�F�t{�^�&�Guj�~ t�^�&�G% = u� �3��F��v��v��v
�v�
����t	�~� t�� �^�&�Gt"�v��v�v�v
�v�v��v��c����t� �F��m��^�V�F&G
�V��F��^�&�W&��V��F��F�F�tp�~ t�^�&�G% = u� �3��F��v��v��v
�v�n����t�~� u)�^�&�Gt$�v��v�v�v
�v�v��v�������t� �	�F��x�3�_^��]�U���VW�N�V�F;V
u;Fu��^&�G�F��^&�G�F��F�#F��tr�f� 3�f� 3�F�;F�u� �t��F�% �V��� ;�t%�F�% ��#F���t�� �N� �N� �F�;F�tf�F� 0�V��� 0;�t�� �F�u�� � �F�#F���tc�^&�W&�G
�^&;Wu&;G
t!�t� �^&�W&�G
�^&G
&W�uw� �^&�W&�G�V�F�^&�W&�G�V
�F����v
�v�v�v������t� �6�F�t.�F�t(�^&�Gt� P�v�v�v
�v�v�v�I����3�_^��]�U��VW.�����v�]�Y���u-�~� w6� &�Gt� �6� &�O6� &�G�������_^]�U��VW.����6� &�G;Fu6� &�g���v�$�Y_^]�U��VW�v
�v3�P�v�v�v�v������uA�^&�W�^&�_�� t#�v
�v� P�^&�w&�w�v�v�����>��t7�Ft� �.��t'�� t�� t��@t��% �Ӂ� ;�u� �3��3�_^]�U���VW6� &�G�F��^��F% �F��Ft�N��Ft�N��Fu�N� �F t�N��F�t�N��Fu��^���v��.���T�v3�P�v�V���g�v3�P�v�^���U�v
�v3�P�v�v�V��v
�v3�P�v�v�^��
�)3�P�v�v�V�3�P�v�v�^�3�P�v
�v�v�v�V�3�P�v
�v�v�v�^���V�^3�S[�V���V�^3�S[�^���v
�v�v�v3��V��v
�v�v�v3��^��v�v3�P�V��v�v3�P�^YY�|�v�v
�v3�P�V���e�v�v
�v3�P�^���N�v3�P�v�V��v3�P�v�^�1�v3�P�v
�v�V��v3�P�v
�v�^�	��^���v�� �.��zT�v�v�V�g��v�v�[��v
�v�v�v�V��v
�v�v�v�^��� �v�v�k��v�v�p��F�^S[�V� �F�^����v
�v�v�v����v
�v�v�v����v�v�VY�f�v�v�^Y�Z�v�v
�v�VYY�H�v�v
�v�^YY�6�v�v�V�+�v�v�^� �v�v
�v�V��v�v
�v�^� _^��]�S�S�S�S�S�S�S�S�S�S�S�SsTsTsTsTTTT+T=THTSTcT�QRR2RJRYRhR|R�R�R�R�RjSjSjSjS�R�R�RS%S3SBSVSU���VW�~ t� �3��F�6� &�G�F��>� t�v
�v��YY�^��F% �F��Ft�N��Ft�N��Fu�N� �F t�N��F�t�N��^���v��.��uV�v��v�VYY�� �v��v�^YY�� �v��v�v�V���� �v��v�v�^���� �v��v�V�[�v��v�P�v��v�v�V��v��v�v�^� �^�F�S[�V� �^�F�S[�^� �v�v�F��V��v�v�F��^�d�v�v��VY�X�v�v��^Y�L�v�v��VY�>�v�v��^Y�0�v�v��V�%�v�v��^��v�v��V��v�v��^� _^��]�bUpU~U�U�U�U�U�U�U�U�U�UnVnVnVnV
VV"V0V>VIVTVaVU���VW6� &�G�F��^��F% �F��Ft�N��Ft�N��F t�N��^���wk�.��^W�v�VY�[�v�^Y�R�v�v�V�	�v�v�^YY�:�v�V��v�^�*�^S[�V� �^S[�^��v�v�V�	�v�v�^� _^��]��V�VWWW%WAWLW-W7WAWLW    Z                    fZ                    ��   vW        �W     U���BVW�  ��W��̋V�F�V�F��>� t�~  u�v�v�^&�GFP����6� &�_6� &�G��^��V�F�&G�VЉF�6� &�W�6� &�G ;�v�^�&��ڈB�F��^�&�? uً�� 6� �F&�G6� �F&�G�V�F��VމF��^�&��F��^�&�G�F��F�t	�^�&�G�3��F��F�0t�^�&�W&�G�VމF܋F�6 P��Y�VԉF�6� &�W&��^�&�W&�6� �VԋF�&�W&��^ҋV�F�&�W&�G�^ҋF&�G�^ҋF�&�G�^ҋF�&�G�^ҋF�&�G�^ҋVދF�&�W&�G�^ҋV�F&�W
&�G�^�&�G"  �^�&�G&  &�G$  �^�&�G  &�G�P�^ҋF&�G*�^ҋF&�G,�^ҋV�F&�W&�G�^ҋF&�G �^�&�G5 �^�&�G4�v��v
�v�F�6 �v�P�N1��
�F�tO6� 6� �V̉F��F� �v�v�v�v
�v�F�6 �v�P�����F�  ��>���V̋F�6� 6� �~  u:�F�t4�F� � P�^�&�w"�^�&�w &�w�v
�v�~����F�  ������6� &�G�^��F��V�F�VĉFVԋF҉VȉF��F�P3�� PR3�� PR�����PR�����F�6� _^��]�U���VW�n��^��G�N��F�3�P�v��v��v�v�v�v�v�v�v�v�v
�v�v�v����_^��]�U���
VW�n��^��G�N��F�6� &�W&��V��F��F�F�u�ʸ P�v��v��v�v�^�&�w�^�&�w �^�&�w&�w�^�&�w
&�w�^�&�4 t�V��F�6 �	�^�&�G2��RP�^�&�w&�w����_^��]�U���VW�F�  �^6�Gt�F�6� �>�F��F�3�PP�v�v�v��v�^�6�W�����u���4�~� t�F�6� �^�6��F��~��t�F�;F
u��~� t�F�6� � _^��]�U���LVW�V�u�F�  �F�& �F�  �F� �F�  �V���6�O�v3�PPR�>���_^��]�VW_^�PQRSTUVW�����z�P���Y�X�F��>�s� f`�f��  P�v���z�P�b.��
fa��|���z���L���J�������~���P���N�����������T���R�����������X���V�����������\���Z�����������`���^�����������d���b�f�fXf����p��F��E3�3҉�d���b���`���^���\���Z���X���V���T���R���P���N���L���J��F�ǆp�  ��n���d���b� �� ��t���r��~�u�~��u�^$&�W&�G�V���n��^��G�N��F��F�ǆh�  ��f��F�ǆl�  ��j�� PU����P�&-��
����ǆH�  ��F�����ǆD�  ��B�ǆ@�  ��>�ǆ<�  ��:�ǆx�  ��v�������^�������R�������Z�������V�������N�������J�������b��V�F����V��F��V�F�V��F��V��F��V��F��F�  �F$F&u
�F"  �F   �~" rw�~ v
�F"  �F  �F �F��F�  �)�^����F�؋F�����v$�&�T&�6�W6��F��F�3�;V"r�u;F rƸ��P����P�F�P�����u2�FtK�F� ��F�% �V�F�V��F��F�  �F�  �F�  �F�  붃N����P����P�F�P�C����t�s�>�s�� ��r���0��v��ً�:�&���>�&�G��B�&�G��F�&�G��L���J�&�W
&�G��P���N�&�W&�G��d���b�&�W&�G��t���r�&�W&�G��T���R�&�W&�G��X���V�&�W&�G��\���Z�&�W"&�G ��`���^�&�W&&�G$��p���n�&�W*&�G(��f�&�G,��j�&�G.��v�����faf��� ��r�����v��ً�B�&���F�&�G��J�&�G��N�&�G��b�&�G��r�&�G
��R�&�G��V�&�G��Z�&�G��^�&�G��n�&�G��f�&�G��j�&�G��v���a�ˎ�>���:���jċ�_^][[ZYX�    Ya                    ��   �`     U���VW�  �a�k��F� � P�v�v
�v�v�v����F�  ������ �F�6� _^��]�U���VW�^&�4 t\�^&�GtJ6� 6� �V��F��^&�_�F��^�&�w"�^�&�w &�w�F6 �vP�c���
�V��F�6� 6� �^&�G4 �^&�5 tM�^&�W0&�G.�V��F��^�&�Gt*�^�&�Gt �^�&�w"�^�&�w &�w�^&�w2�����
�^&�G5 _^��]�U���VW6� &�W&��V��F��^�&�W&�6� &�W&��^�&�W"��6�G��6G
��&���6�G
�v��v����YY�v��v��^�&�_YY_^��]�U���VW�^&�W&��V��F��F�F�u3�� �^6�W6��^&G�V��F��~ t�^�&��V��V��F��v�v
�v��v�����uB�^�&�GtM�^��V��F�&G
�V��F�F�F�t2�F�P�v�v
3�P�v��v��^����t�^�V��F�6�W6�� ��F�C�_^��]�U���VW�FFta�^�V
�F&G
�V��F��FP�v�v3�P�v��v�������u1�^�V
�F&G�V��F��FP�v�v� P�v��v�������t�V�F�3�3�_^��]�U���VW�^&�W&�G�V��F��^
&�W0&�G.�F�F�u�j�^&�G�t�]�^&�G% ���@�F�V�F
6 �V�F��^
&�G5�^&�F�^
&�G2�V��F��V��F��^�&��F��^�&�O����0t�^�&�W&�G�V��F��^�&�W��t"�^
&�Gt�v�3�P�^
&�w2�&���'��u� ��0u� �� t�#�^�&�W&��V�F��^
&�Gt�F�^�F��F� � �v��v��^
&�w&�w�����uD�V�F�V�F��v��v��^
&�w&�w�v��v��$����V�F�V�F�;V�u;F�t�F� �v��F��� �^
&�Gtz�v��v��^
&�w&�w����u(�v��v��^
&�w&�w�v��v������V�F��F� �^�&�Gts�^&�w�^&�w
&�w�v��v��^
&�w2����F� �^�� t�v��F�P�^
&�w2�%��
����t#�^
&�G;F�t�^�&��^��F� P�F�P�	�v��v��v��^
&�w2��$��
�~� u0�^�&�Gt�^�&�w"�^�&�w &�w�v��v�����
�^
&�G4 _^��]�U���VW6� �v6�D&�G�F�6� �v6�D&�G�^6�W6�G�V��F��^��F&+G�F��^6�G
�3�F��F��^�^�&��F��F��^�^�&��F�F��^�F�6�G
�^��v�� �.��2h�^�^�&�G���^6�G �^�U�n�&��]�^6�G  � 6� 6� � �^�&�G";Fu�^�&�G(;F�u� �V�F�V�F��^�&�W&��V�F��u��^�&�W&��^�&�W&��v��v���YY�v��v��^�&�_YY�E�^�^�&��F�F��^�^�&��^�F�F��V�F�V��v��v�F�RP�v��v��
��� �F��F��~� t�F�;Ft��_^��]�'ghhh[g�gU���VW6� �F��v�v��<�YY_^��]�U���VW6� �F�3�P�v���YY�^�6�6� _^��]�U���VW�V�F �V��F��U�^�&�W&�G�V��F��F�F�t03�P�^&�w�v��v��^&�w
&�w�^&�w&�w����t�V��F���F��^�&�? u�3�3�_^��]�**BCCxh1U���6VW�F�F��F�F��V�F
�V��F��^�6�W6�G�V��F�^�6�W6�G�V�F��^��F�&+G�F�^�6�G�F�6� �v�6�D&�G�F�6� �v�6�D&�G�F�^�6�Gu� 3�P�v����YY�^�6��t��6�?��t��^�&�W&��V�F��F�F�u��<� P�^�&�w�^�&�w&�7�^�&�w
&�w�^�&�w&�w�����t�a�F��^�&�&Gu�6� �Fދ^�6�6� 迻�F�6� �3�^�6�G
��F�F��^�^�&��F�F��^�^�&��F�F��^��v���.��l�^�6��t��6�?��t���^�^�&�W&��VډF؃F��v��v��v��v�������VމF܋F�F�u��^�F�&�G"�^�VދF�&�W&&�G$�^�F�&�G(�F�FҋF��F��^�&��F��v��v���YY�v��v��m�YY�^��F�6�G
�~�u�v��v��v��v��v��v��v��v������>� t
�v���YY�ʋF֋v�^�^�N����� �^�6��u
6�?��u�� �F��F̋V��F��VЉF΋^�6�W6��^�6�W6�G�F̋^�6�G�^�^�&����؎�V�v��^�U�n�&��]^�F��5�^�6��u	6�?��u�f�^�6�W6��^�6�W6�G�^�^�&��Fʃ~� }�^�6�Gt
�^��F�6�G
3��9�~� u��^�6�G  �F��F�FԉF��^�^����F�F�~� t���� _^��]�gl}k�k�jglgl    m                    %m                    ��   �l       �l    U���VW�  ��l蹷�F� �F� �v�^&�w"�^&�w &�w�v�v�����F� ��=����F�  ��0����F�6� _^��]�U���VW�N�`�^�V�F&G�V��F��~ t�^�&��V��V��F��^&�W&��V��F��^�&�Gt�v3�P3�PQ�v��v��v��v�� ��3Ƀn�F;Fs�_^��]�U���*VW�~ t	�^&�G��^&�G�F�  �F�FFt�V�F;V�ru;F�r�v�v
�v�v�v�����
�c�V�F�V�F��^�V
�F&G�V�F��V��F�~ tm�^�&�W&��V�F��F�F�tU�^�&�GtE�^�&�_3�;F�r0u;^�r)�v� P�v��v��v�F� �v�P�v�v������)^�^� �F���^�V
�F&G
�V��F��V��F��^�&�W&��V�F��F�F�t]�^�&�GtM�^�&�_3�;F�r8u;^�r1�v3�P�v��v��v��F� �v�P�v�v�����~ u�M�*)^�^� �F���^�V
�F&G$�V�F�V�F��^�&�W&��V��F��F� �^�&�Gt�^�&�G
�F��^�&�W&�G�V��F��^�&�G�n��3�;F�wr;^�s
)^�^� � �^�V�F&G�V܉F��^�&�W&��V؉Fփ~�v!�v�v��v��^�&�w&�7�v��v�� ����v� P�v��v��v��v��v��v������F�  �F�  �n��F�;F�s��v3�P3�P�v��v��v��v��v�v������~ t �v� P3�P�v��v��v��v�� ��F����_^��]�U���VW�V
�F�V��F��^�&�G
�F��^�&�W&�G�V��F��^�&�G�F�  �F��FFu�^�3ɋV��F��뭉V�F�v��v��v�v�y��V�F�N�^�V��F����)FV�^�&�3ɋV�F�読�VF�V�F�FFt@�v� P�v�v��^��V�F&+�V�F�v� P�v��v��v��v��v�v�Y����F�V�n��^� �u�_^��]�U���VW�N��6�W6��V��F��^�&�G%P =P u|�^�&��tr�^��V�F&G�V��F��^�&�G	t�^�&�W&��V��	�^�&��^��F��^��V�F&+G��V�F�^��V��F�&+G��V��F��^�&�W�&�G���6�W6��V�F_^��]�U��� VW�F�  �~�u���^6�W6�G�V��F�6� 6� +F�V��V��F��V
�F)F�V��^&�G t�^&�&�_&�G�F�  �F��~� ,u�~� w$�^&�G% = t�h�V�F�V��F��F��d�V�F�V��F��^�&�&Gu�n�
�E�^�&�W&��V�F�V��F��F� �^�&�Gu�� �^�&�W&�G�V�F�V��F��^�&�Gu� �^�&�G u� �^�&�Gu� �^�&�Gt�^�&�GF�V���^�&�W&�G�V�F�V�F�V�F��^�&�G�t�^�&�W&��V��	�^�&��^�F��^�&�G@t�F��F�P�v��v������V�F�V��F�V�F��^�&�Gt�^�&�G
�F��^�&�W&�G�V�F��^�&�G�n�F�F�3�;V�ru;F�s�F�)F��^� �F�
���^�&�W&��V��F��^�&�G�F��F�t�^�&�GF�V���^�&�W&�G�V�F��F�u� �^�&�W&�G�V��F�V�F�V�F��F�t�^�&�W&��V��	�^�&��^�F�V�F�V�F��F�%H =@ u�F��^�&�Gt&�^�&�G t�F�t�F�P�v��v������V�F�~� uF�^�&�Gt�v�v��v��v��v��v��v��V�����v� P�v��v��v��v��v��v��t����F�% = t� �F�%H =H u�n��^�&�GtM�^�&�W&�G�V��F��^�&�G&Gt�^�&�w�^�&�w&�w�:�F�t�v��v��k�YY�O�v��-��F�^�&�G&Gt �^�&�w�^�&�w&�w�v��v������
��F�t�v��v����YY��v��աY�F�  �F�  �F�n�
;Fv��_^��]�U���VW�F�F��~��t*�^�6�G���N��F�� P��P�v��v����
�t�����^�6�G
_^��]�VW6� &�G_^�VW6� &�G_^�VW6� &�G_^�U���VW�~ u� P� �Y�F�t5�^�G  ��|3�P3�P3�P3�P3�PP3�PP�F�  �F�P�k|P�����F_^��]�U��VW�F_^]�U��VW�F�V�t���G  ��|��tP豠Y_^]�U��VW�F�^�w�w���w�w��Ճ�_^]�U��VW�F�vP���YY���@_^]�U��VW�V�N�ڋGGu3��E�ًGGu� �6�ًG���t&D�wP�ڋG���t&D�wP�����}� �3�_^]�U��VW�F���w�w���YY_^]�U���VW�F�F��FFu$3�P3�P3�P3�P3�PP3�PP��P�U|P�����3�;Fu);Vu$3�P3�P3�P3�P3�PP3�PP��P�U|P�x���^�V
�F&+G��V
�F�^&�W�&�G��V��F��^��V��F��W�G�F���_^��]�U��� VW�F�  �F�  �F�  �F�  �FFt�v
�v�v�v�`ԃ��u
�^&�Gu3�3����F�  �^�V
�F&G�V��F��^�&�W&��V�F�F�F�u��^�&�Gt�t�~ t�^�&�G% = u� �3��F��^��V�F&G�V�F�V"�F �V�F��^�&�Gt�^�&��V�V�F�V�F�V�F��v��v��v�v�Ӄ��uk�^�&�Gu�� �v��v��v��v�v�v�v�v�v�v�v�v�v��v��v��v����� �V�F��F�F�u� �V�F��V�F�^6��F��]�FFt�V�F;V�u};F�ux�V�F�� �FFt43�PP3�P�v3�PP3�PP�v�v�v�v�v��v��v��v��;��� �t3�~� t�V�F�;V�u;F�u�F�	F���F�V�F�V��F�F��F��F��]��~� u�F��^�V
�F&G
�>��^�F�6��~�t
�F�  �F�  �V��F�_^��]�U���VW�V�F�V��F��V�F�V��F��FFu���3�;Fu;Vu��^�V�F&+G��V�F��^�V
�F&+G��V
�F�^&�W�&�G��V��F�FFt�v��v��v��v���у��t	�V�F��� �v��v��v��v��у��uB3�PP� P�F�P�v��v��v�v�v��v�3�PP�v��v��v��v������ �V�F�F�F�uD3�PP� P�F�P3�PP3�PP�v��v�3�PP�v��v��v��v����� �V�F�F�F�t�~� t�V�F��.�~ t$3�P3�P3�P3�P3�PP3�PP��P�A|P�ރ�3�3�_^��]�  
 ��  Bad_cast    
 ��  Bad_typeid   
 �|  Type_info * �|      w  &   s0 4               w    8 Type_info             ������ �@� �!�' ���@�!鷚�&:  ������.��|�6��>���� �� 2�&�@�Ň֓�6� FF� �>� r�� ���2���r��P���@%����+�r`��QI�2���݇�ًË�C� wrD<t� w�< t<t<	u�2����tB�
�uC��2����I,"t"<\u�<"u�I����Y�.��|��Cۋ��+�r��.���v ��6�
���t�3��F .��|�6��>��6��6����~ ���� �&�U��VW�J�^�F�!r����SP�f�X_^]�~      !~  ��U���VW�  �)~�_��~ u� P肞Y�F�t�^��^���6� 6�  �F�6� �F_^��]�  & �� . :               �~    > xalloc  �~                 U��VW�~ t(6�. 6�  3�P�v���YY�Ft	�v��Y��3�_^]�  & �� , 0               �J    4 xmsg              Y�  �      �   ��      2  ��     ��    >U���VW�  �L�,��~ u� P�O�Y�F�tP�
 P�@�Y�F��t9�F� 3�PPP�~ t	�v��Y�3�P�v�v����6�. 6�  �F� �F��^�6� 6�  �F�6� �F_^��]� �
 E�  TStringRef *   & �� : F               ��    J string::lengtherror �                   & �� . :               Ԁ    > xalloc  �                 U��VW�~ t(6�. 6�  3�P�v��YY�Ft	�v��Y��3�_^]�U��VW�~ t(6�. 6�  3�P�v���YY�Ft	�v�ӖY��3�_^]�  & �� , 0               �J    4 xmsg              
  & �� 2 >               !�    B TStringRef  ��                    �� & *             TReference              ��  ��U���VW�  ����ˢ6�. 6�  �~ t4�^����u6� 6�  � P�^�7�YY�Ft�v輕Y�F�6� _^��]�ɉ      ��   ��  ɉ   ��      '�  ��     /�U���"VW�  �G��9��F�Fދ^��G;F�v� �3��uZ3�PPPP�  P�܈P3�PP�F� ��P�F�P��YY�F�P�F�P�
�YY� P�F�P��YY6� 6�  �F�P�ɉP��׃��F�6� _^��]�ɉ      ��   ��  ɉ   ��      �  ��     �U���"VW�  ���u��F�Fދ^��G;F�r� �3��uZ3�PPPP�  P�܈P3�PP�F� ��P�F�P���YY�F�P�F�P�F�YY� P�F�P�>�YY6� 6�  �F�P�ɉP�#׃��F�6� _^��]�ɉ      ��   ��  ɉ   ��      ��  ��     ��U���"VW�  �σ豠�F�Fދ^�G;F�v� �3��uZ3�PPPP�  P�܈P3�PP�F� �P�F�P�5�YY�F�P�F�P��YY� P�F�P�|�YY6� 6�  �F�P�ɉP�aփ��F�6� _^��]�U��VW�~ u�
 P�L�Y�F�ty�^� �G  �FF�G�GFP��Y�^�G�G@P�$�Y�^�G� u�F
P� �Y�v�v�^�w�ʷ�v�v
�^�GFP跷���FF�^G��� 6� 6�  �F_^]�    �  ��U���VW�  ���m�6�. 6�  �~ t�^�w���Y�Ft�v�{�Y�F�6� _^��]�M�  ɉ      h�  ��U���VW�  �t����^�O�F@P�� Y�F�^�G+F�;�v�F�@P�w�|�YY�^�G�F�G�F�6� _^��]�    Ӆ  ��U���VW�  �ׅ豞�^�w� Y�F�^�G+F�;�v�F�@P�w��YY�^�G�F�G�F�6� _^��]�M�  ��      0�  ��U���VW�  �<��L��^�F�G�G@P�w�ͩYY�^�G� u�F
P�q�Y�F�6� _^��]�    ��  ��U���VW�  ���������F���F+F��H3�����F�V�6� _^��]�M�  ��      φ  ��U���"VW�  �ۆ譝�^�GF+F�F�P��Y�Fދ^�G;F�s�v�S�'�YY�U�^�G+F�;�vF�Gu@�F�@P衧Y�F�^� u�F
P��Y�~ t�v�^�w�v��A����^�FމG�	�^�G�F�^�G;F�u�F;Ft'�^�G+F+FP�GFFP�F�FFP螵���~ t,�~
 t�v�v
�F�FP����v�  P�F�FP�����^�F��G�_^�� �^�G;F�tP��Y�^�F�G�F�6� _^��]�U���VW���F��F���F�_^��]�U���VW���F��F���F�_^��]�U���VW���F��F���F�_^��]�U���VW���F��F���F�_^��]�U���VW���F��F���>� u�� �F�_^��]�U���VW���F��F���F�_^��]�U��VW�v�v�p�YY6� 6�  �F_^]�  & �� : F               �    J string::lengtherror                    & �� . :               P�    > xalloc                     & �� . 2               Á    6 string                & �� : F               ��    J string::outofrange                   U��VW�~ t(6�. 6�  3�P�v��YY�Ft	�v萍Y��3�_^]�U��VW�~ t(6�. 6�  3�P�v�d�YY�Ft	�v�W�Y��3�_^]�U��VW�~ t(6�. 6�  3�P�v�+�YY�Ft	�v��Y��3�_^]�  & �� , 0               �J    4 xmsg              U��VW�F����v�~
��D�2�&�M�2�+�_^]�U��VW���~�v
�N����s��ڋV�F_^]�U��VW�~�N
�F����� t�	�I���s�_^]�U��VW�v
�v�v�v������V�F_^]�U��VW���3����~
��2������ы��v�D�&�]�+Î�_^]�      NULL CHECK            Borland C++ - Copyright 1993 Borland Intl. Null pointer assignment
 Divide error
                                   ����            Variable Name  Location   Line Numbers
 -------------  --------   ------------
 %-14s  %-8d   %4d  
    reserved word: %s
 :=
 <
 =
 (
 )
 ;
 +
 -
 *
 /
 EOF
 NUM, val= %s
 ID, name= %s
 ERROR: %s
 Unknown token: %d
 Out of memory error at line %d
 Out of memory error at line %d
 Out of memory error at line %d
   If
 Repeat
 Assign to: %s
 Read: %s
 Write
 Unknown ExpNode kind
 Op:    Const: %d
 Id: %s
 Unknown ExpNode kind
 Unknown node kind
       � � � � � � � �	 %4d: %s if then else end repeat until read write Scanner Bug: state= %d
 	%d:     
Symbol table:

 Type error at line %d: %s
 Op applied to non-integer if test is not Boolean assignment of non-integer value write of non-integer value repeat test is not Boolean      BUG in emitBackup * %s
 %3d:  %5s  %d,%d,%d  	%s 
 %3d:  %5s  %d,%d(%d)  	%s 
 %3d:  %5s  %d,%d(%d)  	%s 
    -> if if: jump to else belongs here if: jump to end belongs here JEQ if: jmp to else LDA jmp to end <- if -> repeat repeat: jump after body comes back here JEQ repeat: jmp back to body <- repeat -> assign ST assign: store value <- assign IN read integer value ST read: store value OUT write ac -> Const LDC load const <- Const -> Id LD load id value <- Id -> Op ST op: push left LD op: load left ADD op + SUB op - MUL op * DIV op / SUB op < JLT br if true LDC false case LDA unconditional jmp LDC true case SUB op == JEQ br if true LDC false case LDA unconditional jmp LDC true case BUG: Unknown operator <- Op File:  TINY Compilation to TM Code Standard prelude: LD load maxaddress from location 0 ST clear location 0 End of standard prelude. End of execution. HALT  
>>>  Syntax error at line %d: %s unexpected token ->         unexpected token ->  unexpected token ->  Code ends before file
               usage: %s <filename>
 .tny r File %s not found
 
TINY COMPILATION: %s
 
Syntax tree:
 
Building Symbol Table...
 
Checking Types...
 
Type Checking Finished
 . .tm w Unable to open %s
  Abnormal program termination
    ���  	          p  
         �           �  C         �  B         �                                                                                                                                                                                                                                                 ```��                               @��     ),(((((),(((),#,*((((**#(#%( TMP .$$$      ZOut of memory            !!!!!                  �@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                                                                                                                  (null)   	

           �$  �%                                          �   nv������1EThuv�������'8L^_`abcdefgh0 Error 0 Invalid function number No such file or directory Path not found Too many open files Permission denied Bad file number Memory arena trashed Not enough memory Invalid memory block address Invalid environment Invalid format Invalid access code Invalid data  No such device Attempted to remove current directory Not same device No more files Invalid argument Arg list too big Exec format error Cross-device link           Math argument Result too large File already exists Possible deadlock            Unknown error :  
      <notype> **BCCxh1 print scanf : floating point formats not linked
                   ? @ ? String reference out of range String reference out of range String reference out of range �|�|�|�|  a      (   �|    �                                                                                                                                                                                                                                  Tiny_scanner/TM.C                                                                                   0000644 0002260 0002114 00000040561 14317021022 013432  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: tm.c                                       */
/* The TM ("Tiny Machine") computer                 */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/******* const *******/
#define   IADDR_SIZE  1024 /* increase for large programs */
#define   DADDR_SIZE  1024 /* increase for large programs */
#define   NO_REGS 8
#define   PC_REG  7

#define   LINESIZE  121
#define   WORDSIZE  20

/******* type  *******/

typedef enum {
   opclRR,     /* reg operands r,s,t */
   opclRM,     /* reg r, mem d+s */
   opclRA      /* reg r, int d+s */
   } OPCLASS;

typedef enum {
   /* RR instructions */
   opHALT,    /* RR     halt, operands are ignored */
   opIN,      /* RR     read into reg(r); s and t are ignored */
   opOUT,     /* RR     write from reg(r), s and t are ignored */
   opADD,    /* RR     reg(r) = reg(s)+reg(t) */
   opSUB,    /* RR     reg(r) = reg(s)-reg(t) */
   opMUL,    /* RR     reg(r) = reg(s)*reg(t) */
   opDIV,    /* RR     reg(r) = reg(s)/reg(t) */
   opRRLim,   /* limit of RR opcodes */

   /* RM instructions */
   opLD,      /* RM     reg(r) = mem(d+reg(s)) */
   opST,      /* RM     mem(d+reg(s)) = reg(r) */
   opRMLim,   /* Limit of RM opcodes */

   /* RA instructions */
   opLDA,     /* RA     reg(r) = d+reg(s) */
   opLDC,     /* RA     reg(r) = d ; reg(s) is ignored */
   opJLT,     /* RA     if reg(r)<0 then reg(7) = d+reg(s) */
   opJLE,     /* RA     if reg(r)<=0 then reg(7) = d+reg(s) */
   opJGT,     /* RA     if reg(r)>0 then reg(7) = d+reg(s) */
   opJGE,     /* RA     if reg(r)>=0 then reg(7) = d+reg(s) */
   opJEQ,     /* RA     if reg(r)==0 then reg(7) = d+reg(s) */
   opJNE,     /* RA     if reg(r)!=0 then reg(7) = d+reg(s) */
   opRALim    /* Limit of RA opcodes */
   } OPCODE;

typedef enum {
   srOKAY,
   srHALT,
   srIMEM_ERR,
   srDMEM_ERR,
   srZERODIVIDE
   } STEPRESULT;

typedef struct {
      int iop  ;
      int iarg1  ;
      int iarg2  ;
      int iarg3  ;
   } INSTRUCTION;

/******** vars ********/
int iloc = 0 ;
int dloc = 0 ;
int traceflag = FALSE;
int icountflag = FALSE;

INSTRUCTION iMem [IADDR_SIZE];
int dMem [DADDR_SIZE];
int reg [NO_REGS];

char * opCodeTab[]
        = {"HALT","IN","OUT","ADD","SUB","MUL","DIV","????",
            /* RR opcodes */
           "LD","ST","????", /* RM opcodes */
           "LDA","LDC","JLT","JLE","JGT","JGE","JEQ","JNE","????"
           /* RA opcodes */
          };

char * stepResultTab[]
        = {"OK","Halted","Instruction Memory Fault",
           "Data Memory Fault","Division by 0"
          };

char pgmName[20];
FILE *pgm  ;

char in_Line[LINESIZE] ;
int lineLen ;
int inCol  ;
int num  ;
char word[WORDSIZE] ;
char ch  ;
int done  ;

/********************************************/
int opClass( int c )
{ if      ( c <= opRRLim) return ( opclRR );
  else if ( c <= opRMLim) return ( opclRM );
  else                    return ( opclRA );
} /* opClass */

/********************************************/
void writeInstruction ( int loc )
{ printf( "%5d: ", loc) ;
  if ( (loc >= 0) && (loc < IADDR_SIZE) )
  { printf("%6s%3d,", opCodeTab[iMem[loc].iop], iMem[loc].iarg1);
    switch ( opClass(iMem[loc].iop) )
    { case opclRR: printf("%1d,%1d", iMem[loc].iarg2, iMem[loc].iarg3);
                   break;
      case opclRM:
      case opclRA: printf("%3d(%1d)", iMem[loc].iarg2, iMem[loc].iarg3);
                   break;
    }
    printf ("\n") ;
  }
} /* writeInstruction */

/********************************************/
void getCh (void)
{ if (++inCol < lineLen)
  ch = in_Line[inCol] ;
  else ch = ' ' ;
} /* getCh */

/********************************************/
int nonBlank (void)
{ while ((inCol < lineLen)
         && (in_Line[inCol] == ' ') )
    inCol++ ;
  if (inCol < lineLen)
  { ch = in_Line[inCol] ;
    return TRUE ; }
  else
  { ch = ' ' ;
    return FALSE ; }
} /* nonBlank */

/********************************************/
int getNum (void)
{ int sign;
  int term;
  int temp = FALSE;
  num = 0 ;
  do
  { sign = 1;
    while ( nonBlank() && ((ch == '+') || (ch == '-')) )
    { temp = FALSE ;
      if (ch == '-')  sign = - sign ;
      getCh();
    }
    term = 0 ;
    nonBlank();
    while (isdigit(ch))
    { temp = TRUE ;
      term = term * 10 + ( ch - '0' ) ;
      getCh();
    }
    num = num + (term * sign) ;
  } while ( (nonBlank()) && ((ch == '+') || (ch == '-')) ) ;
  return temp;
} /* getNum */

/********************************************/
int getWord (void)
{ int temp = FALSE;
  int length = 0;
  if (nonBlank ())
  { while (isalnum(ch))
    { if (length < WORDSIZE-1) word [length++] =  ch ;
      getCh() ;
    }
    word[length] = '\0';
    temp = (length != 0);
  }
  return temp;
} /* getWord */

/********************************************/
int skipCh ( char c  )
{ int temp = FALSE;
  if ( nonBlank() && (ch == c) )
  { getCh();
    temp = TRUE;
  }
  return temp;
} /* skipCh */

/********************************************/
int atEOL(void)
{ return ( ! nonBlank ());
} /* atEOL */

/********************************************/
int error( char * msg, int lineNo, int instNo)
{ printf("Line %d",lineNo);
  if (instNo >= 0) printf(" (Instruction %d)",instNo);
  printf("   %s\n",msg);
  return FALSE;
} /* error */

/********************************************/
int readInstructions (void)
{ OPCODE op;
  int arg1, arg2, arg3;
  int loc, regNo, lineNo;
  for (regNo = 0 ; regNo < NO_REGS ; regNo++)
      reg[regNo] = 0 ;
  dMem[0] = DADDR_SIZE - 1 ;
  for (loc = 1 ; loc < DADDR_SIZE ; loc++)
      dMem[loc] = 0 ;
  for (loc = 0 ; loc < IADDR_SIZE ; loc++)
  { iMem[loc].iop = opHALT ;
    iMem[loc].iarg1 = 0 ;
    iMem[loc].iarg2 = 0 ;
    iMem[loc].iarg3 = 0 ;
  }
  lineNo = 0 ;
  while (! feof(pgm))
  { fgets( in_Line, LINESIZE-2, pgm  ) ;
    inCol = 0 ; 
    lineNo++;
    lineLen = strlen(in_Line)-1 ;
    if (in_Line[lineLen]=='\n') in_Line[lineLen] = '\0' ;
    else in_Line[++lineLen] = '\0';
    if ( (nonBlank()) && (in_Line[inCol] != '*') )
    { if (! getNum())
        return error("Bad location", lineNo,-1);
      loc = num;
      if (loc > IADDR_SIZE)
        return error("Location too large",lineNo,loc);
      if (! skipCh(':'))
        return error("Missing colon", lineNo,loc);
      if (! getWord ())
        return error("Missing opcode", lineNo,loc);
      op = opHALT ;
      while ((op < opRALim)
             && (strncmp(opCodeTab[op], word, 4) != 0) )
          op++ ;
      if (strncmp(opCodeTab[op], word, 4) != 0)
          return error("Illegal opcode", lineNo,loc);
      switch ( opClass(op) )
      { case opclRR :
        /***********************************/
        if ( (! getNum ()) || (num < 0) || (num >= NO_REGS) )
            return error("Bad first register", lineNo,loc);
        arg1 = num;
        if ( ! skipCh(','))
            return error("Missing comma", lineNo, loc);
        if ( (! getNum ()) || (num < 0) || (num >= NO_REGS) )
            return error("Bad second register", lineNo, loc);
        arg2 = num;
        if ( ! skipCh(',')) 
            return error("Missing comma", lineNo,loc);
        if ( (! getNum ()) || (num < 0) || (num >= NO_REGS) )
            return error("Bad third register", lineNo,loc);
        arg3 = num;
        break;

        case opclRM :
        case opclRA :
        /***********************************/
        if ( (! getNum ()) || (num < 0) || (num >= NO_REGS) )
            return error("Bad first register", lineNo,loc);
        arg1 = num;
        if ( ! skipCh(','))
            return error("Missing comma", lineNo,loc);
        if (! getNum ())
            return error("Bad displacement", lineNo,loc);
        arg2 = num;
        if ( ! skipCh('(') && ! skipCh(',') )
            return error("Missing LParen", lineNo,loc);
        if ( (! getNum ()) || (num < 0) || (num >= NO_REGS))
            return error("Bad second register", lineNo,loc);
        arg3 = num;
        break;
        }
      iMem[loc].iop = op;
      iMem[loc].iarg1 = arg1;
      iMem[loc].iarg2 = arg2;
      iMem[loc].iarg3 = arg3;
    }
  }
  return TRUE;
} /* readInstructions */


/********************************************/
STEPRESULT stepTM (void)
{ INSTRUCTION currentinstruction  ;
  int pc  ;
  int r,s,t,m  ;
  int ok ;

  pc = reg[PC_REG] ;
  if ( (pc < 0) || (pc > IADDR_SIZE)  )
      return srIMEM_ERR ;
  reg[PC_REG] = pc + 1 ;
  currentinstruction = iMem[ pc ] ;
  switch (opClass(currentinstruction.iop) )
  { case opclRR :
    /***********************************/
      r = currentinstruction.iarg1 ;
      s = currentinstruction.iarg2 ;
      t = currentinstruction.iarg3 ;
      break;

    case opclRM :
    /***********************************/
      r = currentinstruction.iarg1 ;
      s = currentinstruction.iarg3 ;
      m = currentinstruction.iarg2 + reg[s] ;
      if ( (m < 0) || (m > DADDR_SIZE))
         return srDMEM_ERR ;
      break;

    case opclRA :
    /***********************************/
      r = currentinstruction.iarg1 ;
      s = currentinstruction.iarg3 ;
      m = currentinstruction.iarg2 + reg[s] ;
      break;
  } /* case */

  switch ( currentinstruction.iop)
  { /* RR instructions */
    case opHALT :
    /***********************************/
      printf("HALT: %1d,%1d,%1d\n",r,s,t);
      return srHALT ;
      /* break; */

    case opIN :
    /***********************************/
      do
      { printf("Enter value for IN instruction: ") ;
        fflush (stdin);
        fflush (stdout);
        gets(in_Line);
        lineLen = strlen(in_Line) ;
        inCol = 0;
        ok = getNum();
        if ( ! ok ) printf ("Illegal value\n");
        else reg[r] = num;
      }
      while (! ok);
      break;

    case opOUT :  
      printf ("OUT instruction prints: %d\n", reg[r] ) ;
      break;
    case opADD :  reg[r] = reg[s] + reg[t] ;  break;
    case opSUB :  reg[r] = reg[s] - reg[t] ;  break;
    case opMUL :  reg[r] = reg[s] * reg[t] ;  break;

    case opDIV :
    /***********************************/
      if ( reg[t] != 0 ) reg[r] = reg[s] / reg[t];
      else return srZERODIVIDE ;
      break;

    /*************** RM instructions ********************/
    case opLD :    reg[r] = dMem[m] ;  break;
    case opST :    dMem[m] = reg[r] ;  break;

    /*************** RA instructions ********************/
    case opLDA :    reg[r] = m ; break;
    case opLDC :    reg[r] = currentinstruction.iarg2 ;   break;
    case opJLT :    if ( reg[r] <  0 ) reg[PC_REG] = m ; break;
    case opJLE :    if ( reg[r] <=  0 ) reg[PC_REG] = m ; break;
    case opJGT :    if ( reg[r] >  0 ) reg[PC_REG] = m ; break;
    case opJGE :    if ( reg[r] >=  0 ) reg[PC_REG] = m ; break;
    case opJEQ :    if ( reg[r] == 0 ) reg[PC_REG] = m ; break;
    case opJNE :    if ( reg[r] != 0 ) reg[PC_REG] = m ; break;

    /* end of legal instructions */
  } /* case */
  return srOKAY ;
} /* stepTM */

/********************************************/
int doCommand (void)
{ char cmd;
  int stepcnt=0, i;
  int printcnt;
  int stepResult;
  int regNo, loc;
  do
  { printf ("Enter command: ");
    fflush (stdin);
    fflush (stdout);
    gets(in_Line);
    lineLen = strlen(in_Line);
    inCol = 0;
  }
  while (! getWord ());

  cmd = word[0] ;
  switch ( cmd )
  { case 't' :
    /***********************************/
      traceflag = ! traceflag ;
      printf("Tracing now ");
      if ( traceflag ) printf("on.\n"); else printf("off.\n");
      break;

    case 'h' :
    /***********************************/
      printf("Commands are:\n");
      printf("   s(tep <n>      "\
             "Execute n (default 1) TM instructions\n");
      printf("   g(o            "\
             "Execute TM instructions until HALT\n");
      printf("   r(egs          "\
             "Print the contents of the registers\n");
      printf("   i(Mem <b <n>>  "\
             "Print n iMem locations starting at b\n");
      printf("   d(Mem <b <n>>  "\
             "Print n dMem locations starting at b\n");
      printf("   t(race         "\
             "Toggle instruction trace\n");
      printf("   p(rint         "\
             "Toggle print of total instructions executed"\
             " ('go' only)\n");
      printf("   c(lear         "\
             "Reset simulator for new execution of program\n");
      printf("   h(elp          "\
             "Cause this list of commands to be printed\n");
      printf("   q(uit          "\
             "Terminate the simulation\n");
      break;

    case 'p' :
    /***********************************/
      icountflag = ! icountflag ;
      printf("Printing instruction count now ");
      if ( icountflag ) printf("on.\n"); else printf("off.\n");
      break;

    case 's' :
    /***********************************/
      if ( atEOL ())  stepcnt = 1;
      else if ( getNum ())  stepcnt = abs(num);
      else   printf("Step count?\n");
      break;

    case 'g' :   stepcnt = 1 ;     break;

    case 'r' :
    /***********************************/
      for (i = 0; i < NO_REGS; i++)
      { printf("%1d: %4d    ", i,reg[i]);
        if ( (i % 4) == 3 ) printf ("\n");
      }
      break;

    case 'i' :
    /***********************************/
      printcnt = 1 ;
      if ( getNum ())
      { iloc = num ;
        if ( getNum ()) printcnt = num ;
      }
      if ( ! atEOL ())
        printf ("Instruction locations?\n");
      else
      { while ((iloc >= 0) && (iloc < IADDR_SIZE)
                && (printcnt > 0) )
        { writeInstruction(iloc);
          iloc++ ;
          printcnt-- ;
        }
      }
      break;

    case 'd' :
    /***********************************/
      printcnt = 1 ;
      if ( getNum  ())
      { dloc = num ;
        if ( getNum ()) printcnt = num ;
      }
      if ( ! atEOL ())
        printf("Data locations?\n");
      else
      { while ((dloc >= 0) && (dloc < DADDR_SIZE)
                  && (printcnt > 0))
        { printf("%5d: %5d\n",dloc,dMem[dloc]);
          dloc++;
          printcnt--;
        }
      }
      break;

    case 'c' :
    /***********************************/
      iloc = 0;
      dloc = 0;
      stepcnt = 0;
      for (regNo = 0;  regNo < NO_REGS ; regNo++)
            reg[regNo] = 0 ;
      dMem[0] = DADDR_SIZE - 1 ;
      for (loc = 1 ; loc < DADDR_SIZE ; loc++)
            dMem[loc] = 0 ;
      break;

    case 'q' : return FALSE;  /* break; */

    default : printf("Command %c unknown.\n", cmd); break;
  }  /* case */
  stepResult = srOKAY;
  if ( stepcnt > 0 )
  { if ( cmd == 'g' )
    { stepcnt = 0;
      while (stepResult == srOKAY)
      { iloc = reg[PC_REG] ;
        if ( traceflag ) writeInstruction( iloc ) ;
        stepResult = stepTM ();
        stepcnt++;
      }
      if ( icountflag )
        printf("Number of instructions executed = %d\n",stepcnt);
    }
    else
    { while ((stepcnt > 0) && (stepResult == srOKAY))
      { iloc = reg[PC_REG] ;
        if ( traceflag ) writeInstruction( iloc ) ;
        stepResult = stepTM ();
        stepcnt-- ;
      }
    }
    printf( "%s\n",stepResultTab[stepResult] );
  }
  return TRUE;
} /* doCommand */


/********************************************/
/* E X E C U T I O N   B E G I N S   H E R E */
/********************************************/

main( int argc, char * argv[] )
{ if (argc != 2)
  { printf("usage: %s <filename>\n",argv[0]);
    exit(1);
  }
  strcpy(pgmName,argv[1]) ;
  if (strchr (pgmName, '.') == NULL)
     strcat(pgmName,".tm");
  pgm = fopen(pgmName,"r");
  if (pgm == NULL)
  { printf("file '%s' not found\n",pgmName);
    exit(1);
  }

  /* read the program */
  if ( ! readInstructions ())
         exit(1) ;
  /* switch input file to terminal */
  /* reset( input ); */
  /* read-eval-print */
  printf("TM  simulation (enter h for help)...\n");
  do
     done = ! doCommand ();
  while (! done );
  printf("Simulation done.\n");
  return 0;
}
                                                                                                                                               Tiny_scanner/TM.EXE                                                                                 0000644 0002260 0002114 00000033430 14317021022 013666  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  MZ    �����       >    �Pjr                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             ��.���0�!�. �, �ڣ� �� �� �.� ��>� �ǋع����aC&8u��̀�ى� � �������� ��+�>�	�� s� �>�	��X3r(>	r"���G;�r�>�	 t�>	 u� ;�w�������ډ� �� �� +؎��JW�!_����ҋ��3�.���J
�X3+���>�vG�>� r@w�>� r7�X� �!r*�g���!r �H� �!r@�� H���I�!r
�X�  �!s�[� ��� �� 
�t�@ ���p &�3�.���>
�J
�� �6� �6� �6� �P��.��VW�J
�J
� _^�VW.��3���/ &�� F��-\t	� �/ �� _^Ë�L�F�!� �H �� � 5�!�t �v �5�!�x �z �5�!�| �~ �5�!�� �� � %�ʎں��!�� %�t �!�%�x �!�%�| �!�%�� �!Á�>
t2�����׋�;�t#&�?�t��>
t&:g�&8gw&�g�Ӄ���;�t��&�? &��t&�_�&�W�ô@� �!ù �V .������ P��   U��V��3�����
� ���� ��]�U��V�vV�xP�!YY�}� �� |� �����������������㋟����� �~P�� ��������������Y�t= t+= t&�A��������������������
��P� �����������������������
���ڸ�P�t Y^]�U���c
�c
;e
}�c
��g
�L
��L
 ]�U����c
�c
;e
}�c
��g
 t�c
;e
}�c
��g
�L
� ��	�L
 3���]�U���VW�F�  �a
  � ��F�  �>L
-u���؋��l����t�>L
+t݀>L
-t�3��v���F� �L
�P�Ǻ
 ��ZЃ�Ћ��4��L
��؊���� uԋ���a
Љa
�7��t�>L
+t��>L
-u�x��F�� _^��]�U��VW3�3����t4���}�L
��M
F����L
��؊���� u�ƄM
 �t� �3������ _^]�U��V3�����t�L
:Fu��� ��� ^]�U�������@� ]�U��V�v�v��P��YY�|
V��P��YY�v��P�YY3�� ^]�U���
VW�F�  ��^���Ǉ�
  �F��~�|���� �����Ǉ  F�� |�3��9��������Ǉ  ��������Ǉ  ��������Ǉ
  ��������Ǉ  F�� |�3��d�6�
�w P�g
P�g���c
  G�g
P�##YH�e
�e
��g

u��e
�e
Ƈg
 ���u��c
��g
*u�����u���PW��P�������6a
�� ~VW����:P��Y�uVW�����2��uVW�����F�  ��F��~�}� P�M
P�^������ �"���uܸ P�M
P�^������ �}"���tVW���w��v����Y�t= u� = u� ����t�>a
 |�>a
|VW��<��a
�F��,P���Y�uVW��#�����t�>a
 |�>a
|VW�'���a
�F��,P��Y�uVW�;������t�>a
 |�>a
|VW�I����a
�F�� ���t�>a
 |�>a
|VW�\���a
�F��,P�L�Y�uVW�o���J��uVW�}���a
�F��(P�$�Y�u�,P��Y�uVW���^����t�>a
 |�>a
|VW���A��n���������F�����������F�����������F���
��������F�����
�G  u��� ���_^��]�U���VW��F��~� |�~� ~� �2�F�@��F�P�F�������P� ��v���Y�t= t= t;�R�v��F��F�F��F��A�v��F��F�^���F���
���|�� ~� ���v��F��F�^���F���
��� �^���v���.���
�v��v�V��P����� �K���P��Y��P�Y��P�Y�g
P�Y�g
P��Y�e
�c
  ���F��~� u
��P�Y�����a
���
�~� t�� �������
��P�pYY��^��㋇�
�^�����
����� �^��㋇�
�^���+��
��^��㋇�
�^������
�ы^��ヿ�
 t�^��㋇�
�^������
���㉇�
�� �l�� ���㋇땋��㋇�
���㉇�}���㉿�
�s����F����
�f���ヿ�
 }�>�U���ヿ�
 �>�D���ヿ�
 ~�>�3���ヿ�
 |�>�"���ヿ�
 u�>����ヿ�
 t�>� 3����_^��]�� 	[	o	�	�	�	{
�	�	{
�	

&
7
H
Y
j
U���
VW3��P�Y��P��Y��P��Y�g
P��Y�g
P�Y�e
�c
  ���tȠM
�F��F��-c �؃�v�(��.����� ���@�� � P�Y�>�  t�-��2P�Y��8P�Y�GP�Y��P�Y��P�Y��P�}Y�%P�uY�]P�mY��P�eY��P�]Y�P�UY�QP�MY��� ���@�� �}P�7Y�>�  t�����P�#Y��'��t� ����t�a
�3�+����P��Y�X� �R�F�  �/�^������
�v���P�����F�� �����u��P�Y�F��~�|��� ���t�a
�� ���t�>a
���u
��P�Y�"��6� �V�Y�� O�>�  |�>�  }���� � �P��t�a
�� �C��t�>a
�L��u
��P�6Y�2��� �����6� ��P����� O�>�  |�>�  }���b��   ��   3��F�  ��^���Ǉ�
  �F��~�|����F� ��^���Ǉ  �F��~� |��3�� �F��P��P�YY� �F�  �~y�~�gu93����� �>�  t�6� �Q�Y����F�F�~� tރ>�  t
V�P�YYY�(���� �>�  t�6� ��Y���F�N�~�~� tڋ^������ �2P�YY� �e�_^��]��{--�6*------�(��U��V�v�~t�4�6P��YY� P�9Y�t��
P�YY�. P��
P�tYY�u�LP��
P�*YY�PP��
P��YY��
�>�
 u��
P�RP�YY� P�� Y����u� P�� Y�gP�_Y�-����@�J
�>J
 tP�EY3�� ^]�U��>� u� �����F��3��3�]�U��C2��V�!r	�^�3��P�� ]�U��C��V�N�!r3��P�� ]��U��V�v�u���������3�>� u��=�������F�~ u�u�����v�V�Y^]� U��3�PP�v��]�U�� P3�P�v��]�3�P� P3�P��ø PP3�P�y��U��V�v�|��X~�W �6	��	�����ރ�#��	���6� ���^]� U��V�vV����^]� U�� D�^�!�%� ]�U���"VW�~
�^��$wX��rS�F�N�}�~ t�-G���؃� �v���+�����F�	��+���F�u��N�����N�,
s:�F��� ��F
_^��]� U��3�P�v�v�
 P� P�aP�j�]� U��^�で����B�F
�^�N�V�!r�P����]�U��V�v�V�u�F3�v�u�v	���PV�0YYP���z	PV�YY��^]� U���VW�v�~V3�P�=�u� �� �P�����F�PV��YY�t׋�_^��]� U��VW�v�~������_^]� U��^����� t� P��?�^�N�V�!r�P��]ú ;�s+����Ǉ�  �ڱ��Ƈ����������㉇�B;�rՠ��P�+�Y�u�&���� P�� t� �3�P3�P��P�������P���Y�u�&���� P�� t� �3�P3�P��P����U�� P3�PP�v�d���]�U��A�V�!r3��P�U�]Ê�� ������ ���'@'��U��� VW�F�  �F�P �F�  �FW���2����I_�6�G�N�u/SQR��j�+���j�PW�v�V
�u�F� �F�P ~j�ZY[����j��~��~��v�
�t<%t6�G�N���������v�<%t�~�3ɉN�N��N��F����F�����2�Ћ؀� ��`s���	��v���.����~�� w��N��Ѐ� w�N��ŀ� w�~�+t�V�뵃f����N� �맀� wM�F� u)�N����3�~6��F��s�y�؃N��F���o���u׉F����b���sʵ�F��U��,0���w��F��|����������F��3���u��F��t����������F����N��e��N� �f���Y���
�
�
�����F� �V�3҈V��~6���
�F��V��~6��GG�v�F� t6�GG�~�~��u�u	�~� u�h��N�RPW�ǘP�F�PS���V��}�� �� �V��v�~��^6�7CC�^�F�  t6�CC�^���:�Z��6� �F� �f���N�+��ϋV�;���� �v�V��~6��F�~�2�6�� �� �v�V��~�F�  u6�=�F��6�=�F���u��	�U�;N�v�N�� �v�V��~�N��}� WQ�^�SR� #F�P�F�� t	� �F
��F� P���~��F� t�V��~���&�=-uI+�~�V�&�=-t�F�
�tO&��~� ~
�N��}�N�������~��^�� #F�= u�f���ou�~� �F� ���xt��Xu�N�@KK�n�}�F�  N��F� u�� �~�K;���F�@ t�0�m��F��g��V��~'+�+�&�<-t< t<+u&��H�IK����0�=������+�&�6�G�N��0����~	�˰ �����Z��v�~�F�  u6�=�F�6�=�F�P *F�F�&��F� tGG&�  ���v��~��%����
�u��~�P}����~� t�����F�_^��]� -b"�����K���j��Y���=CU��VW�~�v��Y��@P�vW��
�����_^]�U��F�ԁ� ;�s�� 3��	��  ���]�U��F�V� �� ���u�� r
;�s�� �	��  ���]�U���v��Y]�U��F�RP��YY]ú�	���	� �@� �!�' ��	�@�!���U��V�D�F�^�N
�!r�~ u����P��]�VW��\��r;
t�B �� _^�9
t#�w�t�6
� ;6
t���T �G�
���3��
�
� 
S���[��;
t�w��u��?��u����2 �?���t�����\�ߋ;�t�> 
�w�u�|�� 
  Ë6 
�t�|�\�]��wÉ 
�_�_�VW��D�tR r6%��= s� �>
 t� 
�t��9s�_;�u��f �!� �� �3������97s��k���� _^�P3�PP�6�[[% t	3�RP�(�[[XP3�SP��[[=��t�؉
�
X@������[3��P3�SP���[[=��t�ء
�G�
X@������X3��)��7���@��\�u����Ë�SPQP��[���t����v����V�����F��$�[�^���Ë�;�w5��;
u���SP�K�[[�����]+�)���|B��ˋ��7��ك��VWU��^�F
�t7�t-���I�Ѓ������s� ;�rw�������O����P�e��S��3�[]_^��&6
  �&
�(
�*
.�J�6,
�>.
��� �� 2�&�@�Ň֓�6� FF� �>� r�� ���2���n��P���@%����+�r\��QI�2���݇�ًË�C� wr@� w�< t<t<	u�2����tB�
�uC��2����I,"t"<\u�<"u�I���r�Y�.�J�"
Cۋ��+�r��.$
��v ��6�
���t�3��F .�J�6,
�>.
�6*
�6(
�"
�� �$
�� �&&
U��N�C�F�V�!r��P��]�U��V;�r	� P��������Ǉ�  R� Y]�U��>�^�!r��Ǉ�  3��P���]�U����F;�r� P�[�^����� t� �L� D�^�!r>�u5�B3ɋ��!r.RP�B3ɋ��!�F��V�ZYr� B�!r;V�r	w;F�r�3��P�S��]�U��VW�~���9}u_�} t�= }	W�V Y�uK�E t�u�k�Y�} |�E�P��Y���E  �E  �  �E��} t3�PP�u�	�P�}�Y�E  ��_^]�U��VW�~�u�� �f9}t����^�= |)�E u
�� 9E
uF�  �� 9E
u8�E�E
�0�.�E@��)5P�E�E
P�E�P�8��;�t�E u�M�3�_^]�U��VW3ҋ~��G��
t&�N~!�^�|�w
�G
�� ��v�Y��=��u҃��u	;~u3��� �^�G t3���F_^]�U���VW�F�  �>�����D tV��Y�F�����O�u�F�_^��]�U���VW�v�F�  ��F���<ru� � � ��wu����au�	�F�� � �3��i�F��+t�<+u��tt��bu��+u�������F��� ��tu�� @���bu�� ���	% �Ћ© �t��@���*�^��^�F����_^��]� U���V�v
�v�F�P�F�P�4��D�t �| }'�v��F�FP�v����D
�}�D��D  3��A�D�P��Y�t�L � P�D t� �3�P3�PV����tV�?�Y���D  ��^��]� V���| |�������փ�;�w�| |3����^�U��������u3��R�v�v3�P�$�]�U��VW�v�< }
�TB�����3�+Ћ��D@ u,�L
�< }�	I�ـ?
uG��J�u����A�?
uG��J�u���_^]� U��VW�v�~
V���Y�t����G��u�< ~V�|��)FV�d_��  �D�D
W�v�v�D�P�������u
=��u����3�_^]�U���V�v�D�P���Y�V��F����u=��t�< }V���F�V��V���)F�V��V��F�^��]�VW� ����D% = uV�4�Y����O�u�_^�U��V�v�D t����t�D�D
P�D�P�*����~�d�3���< u�D%�  �D��  �L���^]� U��V�v�V� Y^]�U��V�v�u���� �< ~��\
�D
�� �< |T�DuM�D tF�L� �| tV�S��t������D t��� P�T3P�D�P�~���u#�D�P�\�Y= t�L뉋D%�  �D�z��>T3u�D@ t��dߠT3� ^]ø�P�N�Y�U��VW�~����F��|������ ���P��Y��=��t��
uՃ��u;�u3��� �� t3����_^]�U��VW�~�v�N����s��F_^]�U��N�<�V�!r�P�W�]� U��^+�+Ҵ@�!]� U���VW�v�~�� �u�	% ��3�P�v���YY�F��� tx#>	�ǩ�u� P���~��u#�>	t
�6	����� �ǀ t3��� �F���� t7�P P����� t�v3�P�O����}� W���Y��v�v��6����}l� V�v� YY���|Z3�PW��YY�F��� t��  �� �t%�   P� PW����
�� tW����F� t�� t��� t� PP�v�����|/�� t� �3��ց����R�F� t3��� ZЋ��㉗���_^��]�U�����N�� u
��� u� �V��"N
��=�!r�F��F%�� ��^��㉇��F��P���]�U��>%P��P�v�FP�X�]�U��V�v�V�F�P� YY^]�U��VW�~�F�V3�=�}:��]
�E
��E u�� �>V3
t
�>V3t�� W�d�Y�u�� ����� �� �E� u�E u�M��M �} tE�= t	W�+�Y�uʋE�؉�]
�E
�V3��E u� �>V3
t�>V3uxW���Y�to��k�E�������� t� P3�PP�E�P����>V3
u�E@ u� P�0
P�E�P�M��= u� P�V3P�E�P�5��= t
�E u�?��V3� _^]�U�츺P�v���YY]�U���VW�~�F�F��E t)�W�^�F��P��YY=��u3��U�F�N�u��E�E@ u�� �} u� �E;FsO�= t	W��Y�uŊE�������� t� P3�PP�E�P����v�v�E�P�n��;Fr�� ��� �F|�= u
���+E��W��Y�t�b��v�v�u
������F��FE
� �E�������� t� P3�PP�E�P�.���v�v�E�P����;Fsa���\�} t=�/�}�]
�E
�v�F��� �W�^�F�P�\�YY=��u����F�N�u���v�v�E�P���;Fs���F�_^��]� U���VW�F;�r
� P��� �F@= r�^����� t3�� �v�v�v�(���F�@= r�^����� @u�F��b�N��v������<t-<t������S� P�F�P�v����[��F��;�u�� S� P���PQ�v�����^�く� [+��_^��]�U��VW�v�~
9tu�~���v���� �>4
 u���u�4
 ��>2
 u���u�2
 �< t� P3�PPV�����D t�t���Y�d��D  �� �D�D
�~t>�v:���*�~ uW�m�Y�F�u�w��L��n��F�D
�D�|�~u�L3�_^]�U��VW��~��2�����u��~������+����� t�I���s��_^]�U��V��v�^�� t	�:�t"�t�:�t"�t:�t"�u�3��F�D�^]�U��VW��~��2������ы~�F_^]�U��W�؎��~3��������H_]�U��VW�؎���~���F�����2��+ًˋ��v�D��]�2��+�_^]�U��� VW�~�v;>�r
� P�#��� �F@= s3��� ������� t� P3�PPW����������� @u�vVW� ��� ���で����v��F�F��M�N��^��F���F�<
u�F�F��F��x���+Ё�� |'+�VPW�[ ����;�t���u����=�F+F��1��x��~� u���x�+����v!V��x�PW�  ����;�t���tŋF�+���F_^��]�U��^����� t� P��@�^�N�V�!rP�^�く� X�P��]�VW3���;>�s�D tV��Y��G;>�r�_^�VW� ����D tV���YO���u�_^�            Borland C++ - Copyright 1991 Borland Intl. Null pointer assignment
Divide error
Abnormal program termination
                                      X3X3                    � � � � � � �   $(,058?XjHALT IN OUT ADD SUB MUL DIV ???? LD ST ???? LDA LDC JLT JLE JGT JGE JEQ JNE ???? OK Halted Instruction Memory Fault Data Memory Fault Division by 0 %5d:  %6s%3d, %1d,%1d %3d(%1d) 
 Line %d  (Instruction %d)    %s
 Bad location Location too large Missing colon Missing opcode Illegal opcode Bad first register Missing comma Bad second register Missing comma Bad third register Bad first register Missing comma Bad displacement Missing LParen Bad second register HALT: %1d,%1d,%1d
 Enter value for IN instruction:  Illegal value
 OUT instruction prints: %d
 Enter command:  Tracing now  on.
 off.
 Commands are:
    s(tep <n>      Execute n (default 1) TM instructions
    g(o            Execute TM instructions until HALT
    r(egs          Print the contents of the registers
    i(Mem <b <n>>  Print n iMem locations starting at b
    d(Mem <b <n>>  Print n dMem locations starting at b
    t(race         Toggle instruction trace
    p(rint         Toggle print of total instructions executed ('go' only)
    c(lear         Reset simulator for new execution of program
    h(elp          Cause this list of commands to be printed
    q(uit          Terminate the simulation
 Printing instruction count now  on.
 off.
 Step count?
 %1d: %4d     
 Instruction locations?
 Data locations?
 %5d: %5d
 Command %c unknown.
 Number of instructions executed = %d
 %s
 usage: %s <filename>
 .tm r file '%s' not found
 TM  simulation (enter h for help)...
 Simulation done.
              !!!!!                  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                                                                                                                  ���  	          �  
         �           �  C         �  B         �                                                                                                                                                                                                                                                 ```��                               @��     �������������������������������#������������������#����#�� TMP .$$$   (null)   	

 print scanf : floating point formats not linked
                          ���� f   L                                                                                                                                                                                                                                        Tiny_scanner/UTIL.C                                                                                 0000644 0002260 0002114 00000011360 14317021022 013662  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType token, const char* tokenString )
{ switch (token)
  { case IF:
    case THEN:
    case ELSE:
    case END:
    case REPEAT:
    case UNTIL:
    case READ:
    case WRITE:
      fprintf(listing,
         "reserved word: %s\n",tokenString);
      break;
    case ASSIGN: fprintf(listing,":=\n"); break;
    case LT: fprintf(listing,"<\n"); break;
    case EQ: fprintf(listing,"=\n"); break;
    case LPAREN: fprintf(listing,"(\n"); break;
    case RPAREN: fprintf(listing,")\n"); break;
    case SEMI: fprintf(listing,";\n"); break;
    case PLUS: fprintf(listing,"+\n"); break;
    case MINUS: fprintf(listing,"-\n"); break;
    case TIMES: fprintf(listing,"*\n"); break;
    case OVER: fprintf(listing,"/\n"); break;
    case ENDFILE: fprintf(listing,"EOF\n"); break;
    case NUM:
      fprintf(listing,
          "NUM, val= %s\n",tokenString);
      break;
    case ID:
      fprintf(listing,
          "ID, name= %s\n",tokenString);
      break;
    case ERROR:
      fprintf(listing,
          "ERROR: %s\n",tokenString);
      break;
    default: /* should never happen */
      fprintf(listing,"Unknown token: %d\n",token);
  }
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = StmtK;
    t->kind.stmt = kind;
    t->lineno = lineno;
  }
  return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ExpK;
    t->kind.exp = kind;
    t->lineno = lineno;
    t->type = Void;
  }
  return t;
}

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString(char * s)
{ int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else strcpy(t,s);
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static indentno = 0;

/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{ int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * tree )
{ int i;
  INDENT;
  while (tree != NULL) {
    printSpaces();
    if (tree->nodekind==StmtK)
    { switch (tree->kind.stmt) {
        case IfK:
          fprintf(listing,"If\n");
          break;
        case RepeatK:
          fprintf(listing,"Repeat\n");
          break;
        case AssignK:
          fprintf(listing,"Assign to: %s\n",tree->attr.name);
          break;
        case ReadK:
          fprintf(listing,"Read: %s\n",tree->attr.name);
          break;
        case WriteK:
          fprintf(listing,"Write\n");
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else if (tree->nodekind==ExpK)
    { switch (tree->kind.exp) {
        case OpK:
          fprintf(listing,"Op: ");
          printToken(tree->attr.op,"\0");
          break;
        case ConstK:
          fprintf(listing,"Const: %d\n",tree->attr.val);
          break;
        case IdK:
          fprintf(listing,"Id: %s\n",tree->attr.name);
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else fprintf(listing,"Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}
                                                                                                                                                                                                                                                                                Tiny_scanner/UTIL.H                                                                                 0000644 0002260 0002114 00000002015 14317021022 013664  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: util.h                                     */
/* Utility functions for the TINY compiler          */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _UTIL_H_
#define _UTIL_H_

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType, const char* );

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind);

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind);

/* Function copyString allocates and makes a new
 * copy of an existing string
 */
char * copyString( char * );

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
void printTree( TreeNode * );

#endif
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   Tiny_scanner/LEX/                                                                                   0000755 0002260 0002114 00000000000 14317021022 013430  5                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  Tiny_scanner/LEX/TINY.L                                                                             0000644 0002260 0002114 00000003713 14317021022 014334  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: tiny.l                                     */
/* Lex specification for TINY                       */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

%{
#include "globals.h"
#include "util.h"
#include "scan.h"
/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];
%}

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}+
newline     \n
whitespace  [ \t]+

%%

"if"            {return IF;}
"then"          {return THEN;}
"else"          {return ELSE;}
"end"           {return END;}
"repeat"        {return REPEAT;}
"until"         {return UNTIL;}
"read"          {return READ;}
"write"         {return WRITE;}
":="            {return ASSIGN;}
"="             {return EQ;}
"<"             {return LT;}
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}
"("             {return LPAREN;}
")"             {return RPAREN;}
";"             {return SEMI;}
{number}        {return NUM;}
{identifier}    {return ID;}
{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}
"{"             { char c;
                  do
                  { c = input();
                    if (c == EOF) break;
                    if (c == '\n') lineno++;
                  } while (c != '}');
                }
.               {return ERROR;}

%%

TokenType getToken(void)
{ static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = listing;
  }
  currentToken = yylex();
  strncpy(tokenString,yytext,MAXTOKENLEN);
  if (TraceScan) {
    fprintf(listing,"\t%d: ",lineno);
    printToken(currentToken,tokenString);
  }
  return currentToken;
}

                                                     Tiny_scanner/YACC/                                                                                  0000755 0002260 0002114 00000000000 14317021022 013517  5                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  Tiny_scanner/YACC/GLOBALS.H                                                                         0000644 0002260 0002114 00000006412 14317021022 014716  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: globals.h                                  */
/* Yacc/Bison Version                               */
/* Global types and vars for TINY compiler          */
/* must come before other include files             */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Yacc/Bison generates internally its own values
 * for the tokens. Other files can access these values
 * by including the tab.h file generated using the
 * Yacc/Bison option -d ("generate header")
 *
 * The YYPARSER flag prevents inclusion of the tab.h
 * into the Yacc/Bison output itself
 */

#ifndef YYPARSER

/* the name of the following file may change */
#include "y.tab.h"

/* ENDFILE is implicitly defined by Yacc/Bison,
 * and not included in the tab.h file
 */
#define ENDFILE 0

#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 8

/* Yacc/Bison generates its own integer values
 * for tokens
 */
typedef int TokenType; 

extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* code; /* code text file for TM simulator */

extern int lineno; /* source line number for listing */

/**************************************************/
/***********   Syntax tree for parsing ************/
/**************************************************/

typedef enum {StmtK,ExpK} NodeKind;
typedef enum {IfK,RepeatK,AssignK,ReadK,WriteK} StmtKind;
typedef enum {OpK,ConstK,IdK} ExpKind;

/* ExpType is used for type checking */
typedef enum {Void,Integer,Boolean} ExpType;

#define MAXCHILDREN 3

typedef struct treeNode
   { struct treeNode * child[MAXCHILDREN];
     struct treeNode * sibling;
     int lineno;
     NodeKind nodekind;
     union { StmtKind stmt; ExpKind exp;} kind;
     union { TokenType op;
             int val;
             char * name; } attr;
     ExpType type; /* for type checking of exps */
   } TreeNode;

/**************************************************/
/***********   Flags for tracing       ************/
/**************************************************/

/* EchoSource = TRUE causes the source program to
 * be echoed to the listing file with line numbers
 * during parsing
 */
extern int EchoSource;

/* TraceScan = TRUE causes token information to be
 * printed to the listing file as each token is
 * recognized by the scanner
 */
extern int TraceScan;

/* TraceParse = TRUE causes the syntax tree to be
 * printed to the listing file in linearized form
 * (using indents for children)
 */
extern int TraceParse;

/* TraceAnalyze = TRUE causes symbol table inserts
 * and lookups to be reported to the listing file
 */
extern int TraceAnalyze;

/* TraceCode = TRUE causes comments to be written
 * to the TM code file as code is generated
 */
extern int TraceCode;

/* Error = TRUE prevents further passes if an error occurs */
extern int Error; 
#endif
                                                                                                                                                                                                                                                      Tiny_scanner/YACC/TINY.Y                                                                            0000644 0002260 0002114 00000012051 14317021022 014433  0                                                                                                    ustar   cse20191574                     under                                                                                                                                                                                                                  /****************************************************/
/* File: tiny.y                                     */
/* The TINY Yacc/Bison specification file           */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/
%{
#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode *
static char * savedName; /* for use in assignments */
static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */

%}

%token IF THEN ELSE END REPEAT UNTIL READ WRITE
%token ID NUM 
%token ASSIGN EQ LT PLUS MINUS TIMES OVER LPAREN RPAREN SEMI
%token ERROR 

%% /* Grammar for TINY */

program     : stmt_seq
                 { savedTree = $1;} 
            ;
stmt_seq    : stmt_seq SEMI stmt
                 { YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->sibling != NULL)
                        t = t->sibling;
                     t->sibling = $3;
                     $$ = $1; }
                     else $$ = $3;
                 }
            | stmt  { $$ = $1; }
            ;
stmt        : if_stmt { $$ = $1; }
            | repeat_stmt { $$ = $1; }
            | assign_stmt { $$ = $1; }
            | read_stmt { $$ = $1; }
            | write_stmt { $$ = $1; }
            | error  { $$ = NULL; }
            ;
if_stmt     : IF exp THEN stmt_seq END
                 { $$ = newStmtNode(IfK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                 }
            | IF exp THEN stmt_seq ELSE stmt_seq END
                 { $$ = newStmtNode(IfK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                   $$->child[2] = $6;
                 }
            ;
repeat_stmt : REPEAT stmt_seq UNTIL exp
                 { $$ = newStmtNode(RepeatK);
                   $$->child[0] = $2;
                   $$->child[1] = $4;
                 }
            ;
assign_stmt : ID { savedName = copyString(tokenString);
                   savedLineNo = lineno; }
              ASSIGN exp
                 { $$ = newStmtNode(AssignK);
                   $$->child[0] = $4;
                   $$->attr.name = savedName;
                   $$->lineno = savedLineNo;
                 }
            ;
read_stmt   : READ ID
                 { $$ = newStmtNode(ReadK);
                   $$->attr.name =
                     copyString(tokenString);
                 }
            ;
write_stmt  : WRITE exp
                 { $$ = newStmtNode(WriteK);
                   $$->child[0] = $2;
                 }
            ;
exp         : simple_exp LT simple_exp 
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = LT;
                 }
            | simple_exp EQ simple_exp
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = EQ;
                 }
            | simple_exp { $$ = $1; }
            ;
simple_exp  : simple_exp PLUS term 
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = PLUS;
                 }
            | simple_exp MINUS term
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = MINUS;
                 } 
            | term { $$ = $1; }
            ;
term        : term TIMES factor 
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = TIMES;
                 }
            | term OVER factor
                 { $$ = newExpNode(OpK);
                   $$->child[0] = $1;
                   $$->child[1] = $3;
                   $$->attr.op = OVER;
                 }
            | factor { $$ = $1; }
            ;
factor      : LPAREN exp RPAREN
                 { $$ = $2; }
            | NUM
                 { $$ = newExpNode(ConstK);
                   $$->attr.val = atoi(tokenString);
                 }
            | ID { $$ = newExpNode(IdK);
                   $$->attr.name =
                         copyString(tokenString);
                 }
            | error { $$ = NULL; }
            ;

%%

int yyerror(char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: ");
  printToken(yychar,tokenString);
  Error = TRUE;
  return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
static int yylex(void)
{ return getToken(); }

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       