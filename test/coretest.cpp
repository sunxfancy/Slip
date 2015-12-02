/* 
* @Author: sxf
* @Date:   2015-12-01 20:04:39
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-01 20:18:20
*/

#include "gtest/gtest.h"

extern "C" {
#include "slipcore.h"
}

TEST (coretest_slipC_createCore, slipC_createCore)
{
	slip_Core* vm = slipC_createCore();
	ASSERT_NE(vm, (void*)0);
	EXPECT_EQ(vm->env_stack.stack_nuse, 1);

	slip_Value v = slipS_get(&(vm->env_stack), 1);
	EXPECT_EQ(v.t, slipV_table_t);
}