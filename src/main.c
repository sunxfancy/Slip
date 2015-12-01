/* 
* @Author: sxf
* @Date:   2015-11-29 09:05:24
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-01 21:12:52
*/

#include <stdio.h>
#include "slipcore.h"

const char help_message[] = "welcome for using Slip v0.1!\nusage: slip [options] src-files\n";

int main(int argc,const char *argv[]) {
	if (argc <= 1) printf(help_message);
	else {
		const char *file_in_name = argv[1];
		slip_Core* vm = slipC_createCore();
		slipC_loadFile(vm, file_in_name);
	}
	return 0;
}