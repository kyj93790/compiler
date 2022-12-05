/****************************************************/
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
static int savedNum;
static int savedType;
static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */
static int yylex(void);

%}

%token IF THEN ELSE INT RETURN VOID WHILE END REPEAT UNTIL READ WRITE COMMENT
%token ID NUM 
%token ASSIGN EQ NEQ LT LE GT GE PLUS MINUS TIMES OVER LPAREN RPAREN LCURLY RCURLY LSQUARE RSQUARE SEMI COMMA
%token ERROR COMMENT_ERROR

%% /* Grammar for TINY */

program     : decl_lst
                 { savedTree = $1;} 
            ;

decl_lst    : decl_lst decl
                  {
                    /* Preprocessor symbol that defines the value type of the parsing stack */
                    /* recursive */
                    YYSTYPE t = $1;
                    if (t != NULL)
                    { while (t->sibling != NULL)
                        t = t->sibling;
                      t->sibling = $2; // decl
                    }
                    $$ = $1;
                  }
            | decl
                  { $$ = $1; }
            ;

decl        : var_decl
                  { $$ = $1; }
            | func_decl
                  { $$ = $1; }
            ;


term_ID     : ID
                  {
                    /* embedded action */
                    /* have to be done before recognition for another token happens */
                    savedName = copyString(tokenString); 
                  }
            ;

term_NUM    : NUM
                  { savedNum = atoi(tokenString); }
            ;

var_decl    : type_spcf term_ID SEMI
                  {
                    /* should make new node for decl */
                    $$ = newDeclNode(VarK);
                    $$->lineno = lineno;
                    $$->type = savedType;
                    $$->attr.name = savedName;
                  }
            | type_spcf term_ID LSQUARE term_NUM RSQUARE SEMI
                  {
                    $$ = newDeclNode(ArrayK);
                    $$->lineno = lineno;
                    $$->type = savedType;
                    $$->attr.arr.id = savedName;
                    $$->attr.arr.size = savedNum;
                  }
            ;

type_spcf   : INT
                  { savedType = Integer; }
            | VOID
                  { savedType = Void; }
            ;

func_decl   : type_spcf term_ID
                  {
                    $$ = newDeclNoode(FuncK);
                    $$->lineno = lineno;
                    $$->type = savedType;
                    $$->attr.name = savedName;
                  }
              LPAREN params RPAREN comp_stmt
                  {
                    $$ = $3;
                    $$->child[0] = $5; // params
                    $$->child[1] = $7; // comp_stmt
                  }
            ;

params      : param_lst
                  { $$ = $1; }
            | VOID
                  { $$ = NULL; }
            ;

param_lst   : param_lst COMMA param_lst
                  {
                    YYSTYPE t = $1;
                    if (t != NULL) {
                      while (t->sibling) {
                        t = t->sibling;
                      }
                      t->sibling = $3;
                      $$ = $1;
                    }
                    else {
                      $$ = $3;
                    }
                  }
            | param
                  { $$ = $1; }

param       : type_spcf term_ID
                  {
                    $$ = newParamNode(VarParamK);
                    $$->type = savedType;
                    $$->attr.name = savedName;
                  }
            | type_spcf term_ID LSQUARE RSQUARE
                  {
                    $$ = newParamNode(ArrParamK);
                    $$->type = savedType;
                    $$->attr.name = savedName;
                  }

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

