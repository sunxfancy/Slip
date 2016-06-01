%{

#include "parser.h"
#include <stdlib.h>

#define SAVE_TOKEN     yylval.str = maketoken(yytext, yyleng)
#define SAVE_STRING    yylval.str = makestring(yytext, yyleng, 2)
#define SAVE_STRING_NC yylval.str = makestring(yytext, yyleng, 3)

char* maketoken(const char* data, int len);
char* makestring(const char* data, int len, int s);

int haveSep;
int oldSep;
#define CLR oldSep=haveSep;haveSep=0

#ifdef _WIN32

/*windows compatibility case*/  
#define YY_NO_UNISTD_H
#include <io.h>  
#define isatty _isatty  
#define fileno _fileno  

#endif

%}

%option yylineno
%option noyywrap

%%

"/*"([^\*]|(\*)*[^\*/])*(\*)*"*/" ; /* 就是这种注释 */
"//"[^\n]*\n            haveSep=1; /* 双线注释 */

[ \t\v\f]               ; /* 过滤空白字符 */

\n+                     haveSep=1;

    /* 界符 */
[()\[\]{}.:`';]         CLR; return *yytext;
    /* 运算符 */
[+\-*/&|^~!%=,]         CLR; return *yytext;

"if"                    CLR; SAVE_TOKEN; return IF;
"else"                  CLR; SAVE_TOKEN; return ELSE;
"defun"                 CLR; SAVE_TOKEN; return DEFUN;
"defmacro"              CLR; SAVE_TOKEN; return DEFMACRO;
"return"                CLR; SAVE_TOKEN; return RETURN;
"while"                 CLR; SAVE_TOKEN; return WHILE;

[a-zA-Z_][a-zA-Z0-9_]*  CLR; SAVE_TOKEN; return ID; /* 标识符 */

[0-9]*\.[0-9]*          CLR; SAVE_TOKEN; return DOUBLE;
[0-9]+                  CLR; SAVE_TOKEN; return INTEGER;
0x[0-9A-Fa-f]+          CLR; SAVE_TOKEN; return INTEGER;

\"(\\.|[^\\"])*\"       CLR; SAVE_STRING; return STRING; /* 字符串 */
@\"(\\.|[^\\"])*\"      CLR; SAVE_STRING_NC; return STRING; /* 无转义字符串 */
\'(\\.|.)\'             CLR; SAVE_STRING; return CHAR;   /* 字符 */

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
