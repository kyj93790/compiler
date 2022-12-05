/****************************************************/
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
  { case IF: fprintf(listing, "IF\t\t\t%s\n", tokenString); break;
    case ELSE: fprintf(listing, "ELSE\t\t\t%s\n", tokenString); break;
    case INT: fprintf(listing, "INT\t\t\t%s\n", tokenString); break;
    case RETURN: fprintf(listing, "RETURN\t\t\t%s\n", tokenString); break;
    case VOID: fprintf(listing, "VOID\t\t\t%s\n", tokenString); break;
    case WHILE: fprintf(listing, "WHILE\t\t\t%s\n", tokenString); break;
    case PLUS: fprintf(listing, "+\t\t\t%s\n", tokenString); break;
    case MINUS: fprintf(listing, "-\t\t\t%s\n", tokenString); break;
    case TIMES: fprintf(listing, "*\t\t\t%s\n", tokenString); break;
    case OVER: fprintf(listing, "/\t\t\t%s\n", tokenString); break;
    case LT: fprintf(listing,"<\t\t\t%s\n", tokenString); break;
    case LE: fprintf(listing, "<=\t\t\t%s\n", tokenString); break;
    case GT: fprintf(listing, ">\t\t\t%s\n", tokenString); break;
    case GE: fprintf(listing, ">=\t\t\t%s\n", tokenString); break;
    case EQ: fprintf(listing, "==\t\t\t%s\n", tokenString); break;
    case NEQ: fprintf(listing, "!=\t\t\t%s\n", tokenString); break;
    case ASSIGN: fprintf(listing, "=\t\t\t%s\n", tokenString); break;
    case SEMI: fprintf(listing, ";\t\t\t%s\n", tokenString); break;
    case COMMA: fprintf(listing, ",\t\t\t%s\n", tokenString); break;
    case LPAREN: fprintf(listing, "(\t\t\t%s\n", tokenString); break;
    case RPAREN: fprintf(listing, ")\t\t\t%s\n", tokenString); break;
    case LCURLY: fprintf(listing, "{\t\t\t%s\n", tokenString); break;
    case RCURLY: fprintf(listing, "}\t\t\t%s\n", tokenString); break;
    case LSQUARE: fprintf(listing, "[\t\t\t%s\n", tokenString); break;
    case RSQUARE: fprintf(listing, "]\t\t\t%s\n", tokenString); break;
    case ENDFILE: fprintf(listing,"EOF\n"); break;
    case NUM:
      fprintf(listing,
          "NUM\t\t\t%s\n",tokenString);
      break;
    case ID:
      fprintf(listing,
          "ID\t\t\t%s\n",tokenString);
      break;
    case ERROR:
      fprintf(listing,
          "ERROR\t\t\t%s\n",tokenString);
      break;
    case COMMENT_ERROR:
      fprintf(listing,
          "ERROR\t\t\tComment Error\n");
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

TreeNode * newDeclNode(DeclKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = DeclK;
    t->kind.decl = kind;
    t->lineno = lineno;
  }
  return t;
}

TreeNode * newParamNode(ParamKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = ParamK;
    t->kind.param = kind;
    t->lineno = lineno;
  }
  return t;
}

TreeNode * newTypeNode(TypeKind kind)
{ TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else {
    for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
    t->sibling = NULL;
    t->nodekind = TypeK;
    t->kind.type = kind;
    t->lineno = lineno;
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
    if (tree->nodekind == StmtK)
    {
      switch (tree->kind.stmt) {
        case IfK:
          fprintf(listing,"If\n");
          break;
        case CompK:
          fprintf(listing, "Compound Statement\n");
          break;
        case IterK:
          fprintf(listing, "Iteration Statement\n");
          break;
        case RetK:
          fprintf(listing, "Return Statement\n");
          break;
      }
    }
    else if (tree->nodekind == ExpK)
    {
      switch (tree->kind.exp) {
        case AssignK:
          fprintf(listing,"Assign : =\n");
          break;
        case SimpK:
          fprintf(listing,"Simple Expression\n");
          break;
        case AddK:
          fprintf(listing,"Additive Expression\n");
          break;
        case MulK:
          fprintf(listing,"Multiplicative Expression\n");
          break;
        case OpK:
          fprintf(listing,"Operator : ");
          printToken(tree->attr.op,"\0");
          break;
        case NumK:
          fprintf(listing,"Const: %d\n",tree->attr.val);
          break;
        case ExpVarK:
          fprintf(listing,"Variable : %s\n", tree->attr.name);
          break;
        case ExpArrK:
          fprintf(listing,"Array Variable (Name, index): (%s, %d)\n", tree->attr.arr.id, tree->attr.arr.size);
          break;
        case CallK:
          fprintf(listing, "Call\n");
          break;
        default:
          fprintf(listing,"Unknown ExpNode kind\n");
          break;
      }
    }
    else if (tree->nodekind == DeclK)
    {
      switch (tree->kind.decl)
      {
        case VarK:
          fprintf(listing, "Variable Declare : %s\n", tree->attr.name);
          break;
        case ArrayK:
          fprintf(listing, "Array Variable Declare (Name, size): (%s, %d)\n", tree->attr.name, tree->attr.arr.size);
          break;
        case FuncK:
          fprintf(listing, "Function Declare : %s\n", tree->attr.name);
          break;
        default:
          fprintf(listing,"Unknown DeclNode kind\n");
          break;
      }
    }
    else if (tree->nodekind == ParamK)
    {
      switch (tree->kind.param)
      {
        case VarParamK:
          fprintf(listing,"Parameter : %s\n", tree->attr.name);
          
          break;
        case ArrParamK:
          fprintf(listing,"Parameter (Array) : %s\n", tree->attr.name);
          break;
        default:
          fprintf(listing,"Unknown ParamNode kind\n");
          break;
      }
    }
    else if (tree->nodekind == TypeK)
    {
      fprintf(listing,"Type : ");
      if (tree->attr.type == INT) fprintf(listing,"int\n");
      else if (tree->attr.type == VOID) fprintf(listing, "void\n");
      else fprintf(listing,"Unknown type\n");
    }
    else fprintf(listing,"Unknown node kind\n");
    for (i=0;i<MAXCHILDREN;i++)
         printTree(tree->child[i]);
    tree = tree->sibling;
  }
  UNINDENT;
}