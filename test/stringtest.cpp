/* 
* @Author: sxf
* @Date:   2015-12-01 10:21:31
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-02 14:10:03
*/

#include "gtest/gtest.h"

extern "C" {
#include "sstring.h"
}


TEST(stringtest_slipS_createFromStr, slipS_createFromStr) 
{
	slip_Obj* str = slipS_createFromStr("hello world");
	ASSERT_NE(str, (void*)0);
	EXPECT_EQ(slipS_equalcstr(str, "hello world"), 1);
}

TEST(stringtest_slipS_equal, slipS_equal)
{
	slip_Obj* str = slipS_createFromStr("Great!");
	slip_Obj* str2 = slipS_createFromStr("From");
	EXPECT_EQ(slipS_equal(str, str2), 0);
}


TEST(stringtest_slipS_copy, slipS_copy)
{
	slip_Obj* str = slipS_createFromStr("Great!");
	slip_Obj* str2 = slipS_copy(str);
	EXPECT_EQ(slipS_equal(str, str2), 1);
}



