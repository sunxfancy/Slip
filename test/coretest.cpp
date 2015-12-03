/* 
* @Author: sxf
* @Date:   2015-12-01 20:04:39
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-03 16:36:43
*/

#include "gtest/gtest.h"

extern "C" {
#include "slipcore.h"
#include "stable.h"
#include "sstring.h"
}

TEST (coretest_slipC_createCore, slipC_createCore)
{
	slip_Core* vm = slipC_createCore();
	ASSERT_NE(vm, (void*)0);
	EXPECT_EQ(vm->env_stack.stack_nuse, 1);

	slip_Value v = slipS_get(&(vm->env_stack), 1);
	EXPECT_EQ(v.t, slipV_table_t);
}

TEST (coretest_slipC_pushEnvStack, slipC_pushEnvStack)
{
	slip_Core* vm = slipC_createCore();
	slip_Obj* map = slipT_createTable();
	ASSERT_NE(map, (void*)0);
	slipT_initHash(map, 16);
	slipC_pushEnvStack(vm, map);
	EXPECT_EQ(vm->env_stack.stack_nuse, 2);
	slip_Obj* t = slipC_popEnvStack(vm);
	EXPECT_EQ(map, t);
}

TEST (coretest_slipC_findID, slipC_findID)
{
	slip_Core* vm = slipC_createCore();
	slip_Obj* map = slipT_createTable();
	slipT_initHash(map, 16);
	slip_Value v;
	slipV_setValueInt(&v, 12);
	slipT_insertHash(map, slipS_createFromStr("x"), v);

	slipC_pushEnvStack(vm, map);
	slip_Value p = slipC_findID(vm, "x");
	EXPECT_EQ(v.v.i, p.v.i);
}
