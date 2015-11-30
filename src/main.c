/* 
* @Author: sxf
* @Date:   2015-11-29 09:05:24
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-30 20:13:22
*/

#include <stdio.h>
#include "sliplist.h"

const char help_message[] = "welcome for using Slip v0.1!\nusage: slip [options] src-files\n";

int main(int argc,const char *argv[]) {
	if (argc <= 1) printf(help_message);
	else {
		const char *file_in_name = argv[1];
		slip_Node* ans = slipL_parseFile(file_in_name);
	}
	return 0;
}