/* 
* @Author: sxf
* @Date:   2015-12-03 16:36:48
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-03 16:41:30
*/

#include "gtest/gtest.h"

extern "C" {
#include "slipcore.h"
#include "stable.h"
#include "sstring.h"
#include "libapi.h"
}



TEST (libtest_slipL_openStdLib, slipL_openStdLib)
{
	slip_Core* vm = slipC_createCore();
	slipL_openStdLib(vm);
	slipC_loadStr(vm, "(print \"hello\")");
	slip_Value v = slipC_findID(vm, "print");
	EXPECT_NE(v.v.i, 0);
	v = slipC_findID(vm, "set");
	EXPECT_NE(v.v.i, 0);
	v = slipC_findID(vm, "let");
	EXPECT_NE(v.v.i, 0);
	v = slipC_findID(vm, "defun");
	EXPECT_NE(v.v.i, 0);
}