/* 
* @Author: sxf
* @Date:   2015-12-01 10:21:31
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-01 10:46:58
*/

#include "gtest/gtest.h"

extern "C" {
#include "sstring.h"
}


TEST(stringtest_slipS_createFromStr, slipS_createFromStr) 
{
	SString* str = slipS_createFromStr("hello world");
	ASSERT_NE(str, (void*)0);
	printf("%s\n", str->data);
	EXPECT_EQ(slipS_equalcstr(str, "hello world"), 1);
}

TEST(stringtest_slipS_equal, slipS_equal)
{
	SString* str = slipS_createFromStr("Great!");
	SString* str2 = slipS_createFromStr("From");
	EXPECT_EQ(slipS_equal(str, str2), 0);
}


TEST(stringtest_slipS_copy, slipS_copy)
{
	SString* str = slipS_createFromStr("Great!");
	SString* str2 = slipS_copy(str);
	EXPECT_EQ(slipS_equal(str, str2), 1);
}



