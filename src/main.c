/* 
* @Author: sxf
* @Date:   2015-11-29 09:05:24
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-30 12:14:46
*/

#include <stdio.h>
#include "sliplist.h"

const char help_message[] = "welcome for using Slip v0.1!\nusage: red [options] src-files\n";


extern FILE* yyin;
extern slip_Node* programBlock;

slip_Node* parseFile(const char* path) {
	FILE* file_in;
	if ((file_in = fopen(path, "r")) == NULL) {
		printf("找不到程序源文件: %s\n", path);
		return 0;
	}
	
	yyin = file_in;
	yyparse();
	fclose(file_in);

	// 打印语法树
	printf("源文件 - %s\n", path);
	slipL_printList(programBlock, 0);
	return programBlock;
}



int main(int argc,const char *argv[]) {
	if (argc <= 1) printf(help_message);
	else {
		const char *file_in_name = argv[1];
		slip_Node* ans = parseFile(file_in_name);
	}
	return 0;
}