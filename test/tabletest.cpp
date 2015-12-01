/* 
* @Author: sxf
* @Date:   2015-12-01 14:07:21
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-01 14:28:05
*/

#include "gtest/gtest.h"

extern "C" {
#include "stable.h"
#include "sstring.h"
}

TEST (tabletest_slipT_create, slipT_create)
{
	STable* t = slipT_create();
	ASSERT_NE(t, (void*)0);
}

TEST (tabletest_slipT_initHash, slipT_initHash)
{
	STable* t = slipT_create();
	slipT_initHash(t, 8);
	EXPECT_EQ(t->map_size, 8);
	EXPECT_EQ(t->map_nuse, 0);
}


TEST (tabletest_slipT_reHash, slipT_reHash)
{
	STable* t = slipT_create();
	slipT_initHash(t, 8);
	EXPECT_EQ(t->map_size, 8);
	slipT_reHash(t, 16);
	EXPECT_EQ(t->map_size, 16);
}


TEST (tabletest_slipT_insertHash, slipT_insertHash)
{
	STable* t = slipT_create();
	slipT_initHash(t, 8);
	slip_Value save;
	save.v.i = 1;
	save.t = slipV_int_t;
	slip_Value save2;
	save2.v.i = 2;
	save2.t = slipV_int_t;
	slipT_insertHash(t, slipS_createFromStr("one"), save);
	slipT_insertHash(t, slipS_createFromStr("two"), save2);
	slip_Value v = slipT_getHash(t, slipS_createFromStr("one"));
	EXPECT_EQ(v.v.i, 1);
	EXPECT_EQ(v.t, slipV_int_t);
	slip_Value v2 = slipT_getHash(t, slipS_createFromStr("two"));
	EXPECT_EQ(v2.v.i, 2);
	EXPECT_EQ(v2.t, slipV_int_t);
}