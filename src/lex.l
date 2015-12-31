%{

#include "parser.h"
#include <malloc.h>

#define SAVE_TOKEN     yylval.str = maketoken(yytext, yyleng)
#define SAVE_STRING    yylval.str = makestring(yytext, yyleng, 2)
#define SAVE_STRING_NC yylval.str = makestring(yytext, yyleng, 3)

char* maketoken(const char* data, int len);
char* makestring(const char* data, int len, int s);

%}

%option yylineno
%option noyywrap
%%

"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/" ; /* 就是这种注释 */ 

;[^\n]*\n               ; /* 分号注释 */ 
"//"[^\n]*\n            ; /* 双线注释 */ 

[ \t\v\f]             ; /* 过滤空白字符 */

\n+|;                   return SEP;

    /* 界符 */
[()\[\]{}.:`']          return *yytext;
    /* 运算符 */
[+\-*/&|^~!%=,]         return *yytext;

"if"                    SAVE_TOKEN; return IF;
"else"                  SAVE_TOKEN; return ELSE;
"defun"                 SAVE_TOKEN; return DEFUN;
"defmacro"              SAVE_TOKEN; return DEFMACRO;
"return"                SAVE_TOKEN; return RETURN;
"while"                 SAVE_TOKEN; return WHILE;

[a-zA-Z_][a-zA-Z0-9_]*  SAVE_TOKEN; return ID; /* 标识符 */

-?[0-9]*\.[0-9]*        SAVE_TOKEN; return DOUBLE;
-?[0-9]+                SAVE_TOKEN; return INTEGER;
0x[0-9A-Fa-f]+          SAVE_TOKEN; return INTEGER;

\"(\\.|[^\\"])*\"       SAVE_STRING; return STRING; /* 字符串 */
@\"(\\.|[^\\"])*\"      SAVE_STRING_NC; return STRING; /* 无转义字符串 */
\'(\\.|.)\'             SAVE_STRING; return CHAR;   /* 字符 */

.                       printf("Unknown Token!\n"); yyterminate();

%%


char* maketoken(const char* data, int len) {
    char* str = (char*) malloc(len+1);
    strncpy(str, data, len);
    str[len] = 0;
    return str;
}

char* makestring(const char* data, int len, int s) {
    char* str = (char*) malloc(len-s+1);
    strncpy(str, data+s-1, len-s);
    str[len-s] = 0;
    if (s == 3) return str;
    return str; 
}

void slip_reset_file(FILE* f) {
    yyrestart(f);
}

void slip_scan_string(const char* str)
{
    yy_switch_to_buffer(yy_scan_string(str));
}