/* 
* @Author: sxf
* @Date:   2015-12-01 20:27:42
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-02 10:10:42
*/

#include "slipcore.h"
#include "libapi.h"
#include <stdio.h>

static int _hello (slip_Core* vm, int num) {
	printf("Hello World~\n");
	return 0;
}


const slip_Reg testlib[] = {
	{ "hello", _hello },
	{ NULL, NULL }
};




