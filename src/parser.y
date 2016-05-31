%{

#include <stdio.h>
#include "sliplist.h"

#define YYERROR_VERBOSE 1

union slip_Node *programBlock; /* the top level root node of our final AST */

extern int yylex();
extern int yylineno;
extern char* yytext;
extern int yyleng;
extern int oldSep;

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
%token <str> IF ELSE DEFUN DEFMACRO RETURN WHILE
/*
   Define the type of node our nonterminal symbols represent.
   The types refer to the %union declaration above. Ex: when
   we call an ident (defined by union type ident) we are really
   calling an (NIdentifier*). It makes the compiler happy.
 */

%type <node> program value list_node list src_list list_token
%type <node> expr exprs exprss block statement statements defargs
%type <node> defmacro_state defun_state if_state while_state ret_state select_state call_state

/* Operator precedence for mathematical operators */


%left  '+'  '-'
%left  '*'  '/'
%left  '('  '['
%left  '.'


%start program

%%

program : statements { programBlock = $1; }
        ;

value : ID { $$ = (slip_Node*)slipL_create_IDNode($1); }
      | STRING { $$ = (slip_Node*)slipL_create_StringNode($1); }
      | DOUBLE { $$ = (slip_Node*)slipL_create_FloatNodeFromStr($1); }
      | CHAR { $$ = (slip_Node*)slipL_create_IntNodeFromStr($1); }
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
          | list_node value { $$ = $1; slipL_addBrother($1, $2); }
          | list_node list { $$ = $1; slipL_addBrother($1, $2); }
          | list_node list_token { $$ = $1; slipL_addBrother($1, $2); }
          ;

list : '(' list_node ')' { $$ = (slip_Node*)slipL_create_ListNode($2); }
     ;

src_list : '`' list { $$ = $2; }
         ;

block : '{' statements '}' { $$ = $2; }
      ;

exprs : expr
      | exprs ',' expr { $$ = $1; slipL_addBrother($1, $3); }
      ;

exprss : expr ',' expr { $$ = $1; slipL_addBrother($1, $3); }
       | exprss ',' expr { $$ = $1; slipL_addBrother($1, $3); }
       ;

expr : expr '=' expr { $$ = slipL_makeList(3, slipL_create_IDNode("="), $1, $3); }
     | expr '+' expr { $$ = slipL_makeList(3, slipL_create_IDNode("+"), $1, $3); }
     | expr '-' expr { $$ = slipL_makeList(3, slipL_create_IDNode("-"), $1, $3); }
     | expr '*' expr { $$ = slipL_makeList(3, slipL_create_IDNode("*"), $1, $3); }
     | expr '/' expr { $$ = slipL_makeList(3, slipL_create_IDNode("/"), $1, $3); }
     | '(' expr ')' { $$ = $2; }
     | value
     | call_state
     | select_state
     ;

statements : statement
           | statements statement { $$ = $1; slipL_addBrother($1, $2); }
           ;

statement : if_state { $$ = (slip_Node*)slipL_create_ListNode($1); }
          | while_state { $$ = (slip_Node*)slipL_create_ListNode($1); }
          | ret_state  { $$ = (slip_Node*)slipL_create_ListNode($1); }
          | defun_state { $$ = (slip_Node*)slipL_create_ListNode($1); }
          | defmacro_state { $$ = (slip_Node*)slipL_create_ListNode($1); }
          | src_list
          | expr ';' { $$ = (slip_Node*)slipL_create_ListNode($1); }
          | exprss '=' exprss ';' { $$ = (slip_Node*)slipL_create_ListNode(slipL_makeList(3, slipL_create_IDNode("=s"), $1, $3)); }
          ;

call_state : expr '(' exprs ')' { $$ = $1; slipL_concat($$, $3); }
           ;

select_state : expr '[' exprs ']' { $$ = slipL_makeList(3, slipL_create_IDNode("select"), $1, $3); }
             | expr '.' ID { $$ = slipL_makeList(3, slipL_create_IDNode("call"), $1, slipL_create_IDNode($3)); }
             ;

if_state : IF expr block { $$ = slipL_makeList(3, slipL_create_IDNode("if"), $2, $3); }
         | IF expr block ELSE block { $$ = slipL_makeList(4, slipL_create_IDNode("if"), $2, $3, $5); }
         ;

while_state : WHILE expr block { $$ = slipL_makeList(3, slipL_create_IDNode("while"), $2, $3); }
            ;

defargs : ID { $$ = (slip_Node*)slipL_create_IDNode($1); }
        | defargs ',' ID { $$ = $1; slipL_addBrother($1, (slip_Node*)slipL_create_IDNode($3)); }
        ;

defun_state : DEFUN ID '(' defargs ')' block { $$ = slipL_makeList(3, slipL_create_IDNode("defun"), slipL_create_IDNode($2), slipL_create_ListNode($4)); slipL_concat($$, $6); }
            | DEFUN '(' defargs ')' block { $$ = slipL_makeList(3, slipL_create_IDNode("defun"), 0, slipL_create_ListNode($3)); slipL_concat($$, $5); }
            ;

defmacro_state : DEFMACRO ID '(' defargs ')' block {$$ = slipL_makeList(3, slipL_create_IDNode("defmacro"), slipL_create_IDNode($2), slipL_create_ListNode($4)); slipL_concat($$, $6);}
               | DEFMACRO '(' defargs ')' block { $$ = slipL_makeList(3, slipL_create_IDNode("defun"), 0, slipL_create_ListNode($3)); slipL_concat($$, $5); }
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
