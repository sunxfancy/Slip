%{

#include <stdio.h>
#include "sliplist.h"

#define YYERROR_VERBOSE 1

union slip_Node *programBlock; /* the top level root node of our final AST */

extern int yylex();
extern int yylineno;
extern char* yytext;
extern int yyleng;

void yyerror(const char *s);

%}

 

/* Represents the many different ways we can access our data */

%union {
    union slip_Node *node;
    char *str;
}

 

/* Define our terminal symbols (tokens). This should

   match our tokens.l lex file. We also define the node type

   they represent.

 */

%token <str> ID INTEGER DOUBLE CHAR STRING

/* 
   Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */

%type <node> program value list_node list


//%type <token> operator 这个设计容易引起规约冲突，舍弃
/* Operator precedence for mathematical operators */


%start program

%%

program : list_node { programBlock = $1; }
        ;

value : ID { $$ = slipL_create_IDNode($1); }
      | STRING { $$ = slipL_create_StringNode($1); }
      | DOUBLE { $$ = slipL_create_FloatNodeFromStr($1); }
      | INTEGER { $$ = slipL_create_IntNodeFromStr($1); }
      | list
      ;

list_node : value 
          | list_node value { $$ = $1; slipL_addBrother($1, $2); }
          ;

list : '(' list_node ')' { $$ = slipL_create_ListNode($2); }
     ;


%%

void yyerror(const char* s){
    fprintf(stderr, "%s \n", s);    
    fprintf(stderr, "line %d: ", yylineno);
    fprintf(stderr, "text %s \n", yytext);
    exit(1);
}