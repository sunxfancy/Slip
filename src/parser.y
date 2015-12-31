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

%token <str> ID INTEGER DOUBLE CHAR STRING SEP
%token <str> IF ELSE DEFUN DEFMACRO RETURN WHILE
/* 
   Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */

%type <node> program value list_node list src_list list_token
%type <node> inner_expr expr inner_exprs exprs block statement
%type <node> defmacro_state defun_state if_state while_state ret_state select_state call_state

/* Operator precedence for mathematical operators */

%right '='
%left  ','
%left  '+'  '-'
%left  '*'  '/'
%left  '.'

%start program

%%

program : inner_exprs { programBlock = $1; }
        ;

value : ID { $$ = (slip_Node*)slipL_create_IDNode($1); }
      | STRING { $$ = (slip_Node*)slipL_create_StringNode($1); }
      | DOUBLE { $$ = (slip_Node*)slipL_create_FloatNodeFromStr($1); }
      | INTEGER { $$ = (slip_Node*)slipL_create_IntNodeFromStr($1); }
      ;

list_token : IF { $$ = (slip_Node*)slipL_create_IDNode($1); }
           | ELSE { $$ = (slip_Node*)slipL_create_IDNode($1); }
           | DEFUN { $$ = (slip_Node*)slipL_create_IDNode($1); }
           | DEFMACRO { $$ = (slip_Node*)slipL_create_IDNode($1); }
           | RETURN { $$ = (slip_Node*)slipL_create_IDNode($1); }
           | WHILE { $$ = (slip_Node*)slipL_create_IDNode($1); }
           | '+' { $$ = (slip_Node*)slipL_create_IDNode("+"); }
           | '-' { $$ = (slip_Node*)slipL_create_IDNode("-"); }
           | '*' { $$ = (slip_Node*)slipL_create_IDNode("*"); }
           | '/' { $$ = (slip_Node*)slipL_create_IDNode("/"); }
           | '=' { $$ = (slip_Node*)slipL_create_IDNode("="); }
           ;

list_node : value 
          | list
          | list_token
          | list_node sep_null value { $$ = $1; slipL_addBrother($1, $3); }
          | list_node sep_null list { $$ = $1; slipL_addBrother($1, $3); }
          | list_node sep_null list_token { $$ = $1; slipL_addBrother($1, $3); }
          ;

list : '(' sep_null list_node sep_null ')' { $$ = (slip_Node*)slipL_create_ListNode($3); }
     ;

src_list : '`' '(' sep_null list_node sep_null ')' { $$ = $4; }

sep_null : %empty
         | SEP
         ;

block : '{' inner_exprs '}' { $$ = (slip_Node*)slipL_create_ListNode($2); }
      ;

inner_exprs : sep_null exprs sep_null { $$ = (slip_Node*)slipL_create_ListNode($2); }
            ;

exprs : expr
      | exprs SEP expr { $$ = $1; slipL_addBrother($1, $3); }
      ;

inner_expr : sep_null expr sep_null { $$ = $2; }
           ;

expr : expr '=' inner_expr { $$ = slipL_makeList(3, slipL_create_IDNode("="), $1, $3); }
     | expr ',' inner_expr { $$ = $1; slipL_addBrother($1, $3); }
     | expr '+' inner_expr { $$ = slipL_makeList(3, slipL_create_IDNode("+"), $1, $3); }
     | expr '-' inner_expr { $$ = slipL_makeList(3, slipL_create_IDNode("-"), $1, $3); }
     | expr '*' inner_expr { $$ = slipL_makeList(3, slipL_create_IDNode("*"), $1, $3); }
     | expr '/' inner_expr { $$ = slipL_makeList(3, slipL_create_IDNode("/"), $1, $3); }
     | '(' inner_expr ')' { $$ = $2; }
     | value
     | statement
     ;

statement : call_state 
          | select_state
          | if_state
          | while_state
          | ret_state
          | defun_state
          | defmacro_state
          | src_list
          ;

call_state : expr '(' inner_expr ')' { $$ = slipL_makeList(3, slipL_create_IDNode("call"), $1, $3); }
           ;

select_state : expr '[' inner_expr ']' { $$ = slipL_makeList(3, slipL_create_IDNode("select"), $1, $3); }
             | expr '.' inner_expr { $$ = slipL_makeList(3, slipL_create_IDNode("call"), $1, $3); }
             ;

if_state : IF '(' inner_expr ')' block { $$ = slipL_makeList(3, slipL_create_IDNode("if"), $3, $5); }
         | IF '(' inner_expr ')' block ELSE block { $$ = slipL_makeList(4, slipL_create_IDNode("if"), $3, $5, $7); }
         ;

while_state : WHILE '(' inner_expr ')' block { $$ = slipL_makeList(3, slipL_create_IDNode("while"), $3, $5); }
            ;

defun_state : DEFUN expr '(' inner_expr ')' block { $$ = slipL_makeList(4, slipL_create_IDNode("defun"), $2, $4, $6); }
            | DEFUN '(' inner_expr ')' block { $$ = slipL_makeList(4, slipL_create_IDNode("defun"), 0, $3, $5); }
            ;

defmacro_state : DEFMACRO expr '(' inner_expr ')' block { $$ = slipL_makeList(4, slipL_create_IDNode("defmacro"), $2, $4, $6); }
               | DEFMACRO '(' inner_expr ')' block { $$ = slipL_makeList(4, slipL_create_IDNode("defun"), 0, $3, $5); }
               ;

ret_state : RETURN expr { $$ = slipL_makeList(2, slipL_create_IDNode("return"), $2); }
          ;

%%

void yyerror(const char* s){
    fprintf(stderr, "%s \n", s);    
    fprintf(stderr, "line %d: ", yylineno);
    fprintf(stderr, "text %s \n", yytext);
    exit(1);
}

