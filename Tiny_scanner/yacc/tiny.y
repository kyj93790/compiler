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

type_spcf   : INT   { savedType = Integer; }
            | VOID  { savedType = Void; }
            ;

func_decl   : type_spcf term_ID
                  {
                    $$ = newDeclNode(FuncK);
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

comp_stmt    : LCURLY local_decl stmt_lst RCURLY
                  {
                    $$ = newStmtNode(CompK);
                    $$->child[0] = $2;
                    $$->child[1] = $3;
                  }
              ;

local_decl    : local_decl var_decl
                  {
                    YYSTYPE t = $1;
                    if (t != NULL) {
                      while (t->sibling) {
                        t = t->sibling;
                      }
                      t->sibling = $2;
                      $$ = $1;
                    }
                    else {
                      $$ = $2;
                    }
                  }
              | { $$ = NULL; }
              ;


stmt_lst      : stmt_lst stmt
                    {
                      YYSTYPE t = $1;
                      if (t != NULL) {
                        while (t->sibling) {
                          t = t->sibling;
                        }
                        t->sibling = $2;
                        $$ = $1;
                      }
                      else {
                        $$ = $2;
                      }
                    }
              | { $$ = NULL; }
              ;

stmt          : exp_stmt
                      { $$ = $1; }
              | comp_stmt
                      { $$ = $1; }
              | sel_stmt
                      { $$ = $1; }
              | iter_stmt
                      { $$ = $1; }
              | ret_stmt
                      { $$ = $1; }
              ;

exp_stmt      : exp SEMI
                      { $$ = $1; }
              | SEMI
                      { $$ = NULL; }
              ;

sel_stmt      : IF LPAREN exp RPAREN stmt
                      {
                        $$ = newStmtNode(IfK);
                        $$->child[0] = $3;
                        $$->child[1] = $5;
                      }
              | IF LPAREN exp RPAREN stmt ELSE stmt
                      {
                        $$ = newStmtNode(IfK);
                        $$->child[0] = $3;
                        $$->child[1] = $5;
                        $$->child[2] = $7;
                      }
              ;

iter_stmt     : WHILE LPAREN exp RPAREN stmt
                      {
                        $$ = newStmtNode(IterK);
                        $$->child[0] = $3;
                        $$->child[1] = $5;
                      }
              ;

ret_stmt      : RETURN SEMI
                      { $$ = newStmtNode(RetK); }
              | RETURN exp SEMI
                      {
                        $$ = newStmtNode(RetK);
                        $$->child[0] = $2;
                      }
              ;

exp           : var ASSIGN exp
                      {
                        $$ = newExpNode(AssignK);
                        $$->child[0] = $1;
                        $$->child[1] = $2;
                      }
              | simp_exp
                      { $$ = $1; }
              ;

var           : term_ID
                      {
                        $$ = newExpNode(ExpVarK);
                        $$->attr.name = savedName;
                      }
              | term_ID LSQUARE exp RSQUARE
                      {
                        $$ = newExpNode(ExpArrK);
                        $$->attr.name = savedName;
                        $$->child[0] = $4;
                      }
              ;

simp_exp      : add_exp relop add_exp
                      {
                        $$ = newExpNode(SimpK);
                        $$->child[0] = $1;
                        $$->child[1] = $2;
                        $$->child[2] = $3;
                      }
              | add_exp
                      { $$ = $1; }
              ;

relop         : LE
                      {
                        $$ = newExpNode(OpK);
                        $$->attr.op = LE;
                      }
              | LT 
                      {
                        $$ = newExpNode(OpK);
                        $$->attr.op = LT;
                      }
              | GT
                      {
                        $$ = newExpNode(OpK);
                        $$->attr.op = GT;
                      }
              | GE
                      {
                        $$ = newExpNode(OpK);
                        $$->attr.op = GE;
                      }
              | EQ
                      {
                        $$ = newExpNode(OpK);
                        $$->attr.op = EQ;
                      }
              | NEQ
                      {
                        $$ = newExpNode(OpK);
                        $$->attr.op = NEQ;
                      }
              ;

add_exp       : add_exp addop term
                        {
                          $$ = newExpNode(AddK);
                          $$->child[0] = $1;
                          $$->child[1] = $2;
                          $$->child[2] = $3;
                        }
              | term
                        { $$ = $1; }
              ;

addop         : PLUS
                        {
                          $$ = newExpNode(OpK);
                          $$->attr.op = PLUS;
                        }
              | MINUS
                        {
                          $$ = newExpNode(OpK);
                          $$->attr.op = MINUS;
                        }
              ;

term          : term mulop factor
                        {
                          $$ = newExpNode(MulK);
                          $$->child[0] = $1;
                          $$->child[1] = $2;
                          $$->child[2] = $3;
                        }
              | factor
                        { $$ = $1; }
              ;

mulop         : TIMES
                        {
                          $$ = newExpNode(OpK);
                          $$->attr.op = TIMES;
                        }
              | OVER
                        {
                          $$ = newExpNode(OpK);
                          $$->attr.op = OVER;
                        }
              ;

factor        : LPAREN exp RPAREN
                      { $$ = $2; }
              | var
                      { $$ = $1; }
              | call
                      { $$ = $1; }
              | term_NUM
                      {
                        $$ = newExpNode(NumK);
                        $$->attr.val = savedNum;
                      }
              ;

call          : term_ID LPAREN args RPAREN
                      {
                        $$ = newExpNode(CallK);
                        $$->attr.name = savedName;
                        $$->child[0] = $3;
                      }
              ;

args          : arg_lst
                      { $$ = $1; }
              | { $$ = NULL; }
              ;

arg_lst       : arg_lst COMMA exp
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
              | exp
                      { $$ = $1; }
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

