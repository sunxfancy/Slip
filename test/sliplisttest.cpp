/*
* @Author: sxf
* @Date:   2015-11-29 19:51:58
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-05 15:47:45
*/

#include "gtest/gtest.h"

extern "C" {
#include "sliplist.h"
}

TEST(sliplisttest_slipL_create_IntNode, slipL_create_IntNode)
{
	slip_IntNode* int_node = slipL_create_IntNode(15);
	EXPECT_EQ(int_node->value, 15);
}

TEST(sliplisttest_slipL_create_IntNodeFromStr, slipL_create_IntNodeFromStr)
{
	slip_IntNode* int_node = slipL_create_IntNodeFromStr("32");
	EXPECT_EQ(int_node->value, 32);
	slip_IntNode* int_node2 = slipL_create_IntNodeFromStr("0xFF");
	EXPECT_EQ(int_node2->value, 0xFF);
	slip_IntNode* int_node3 = slipL_create_IntNodeFromStr("hello");
	EXPECT_EQ(int_node3->value, 0);
}

TEST(sliplisttest_slipL_create_FloatNode, slipL_create_FloatNode)
{
	slip_FloatNode* f_node = slipL_create_FloatNode(19.6);
	EXPECT_EQ(f_node->value, 19.6);
}

TEST(sliplisttest_slipL_create_FloatNodeFromStr, slipL_create_FloatNodeFromStr)
{
	slip_FloatNode* f_node = slipL_create_FloatNodeFromStr("19.6");
	EXPECT_EQ(f_node->value, 19.6);
	slip_FloatNode* f_node2 = slipL_create_FloatNodeFromStr("fwaef");
	EXPECT_EQ(f_node2->value, 0.0);
}


TEST(sliplisttest_slipL_parseString, slipL_parseString)
{
	slip_Node* node = slipL_parseString("`(int 3)");
	ASSERT_NE(node, (void*)0);
	slip_Node* child = node->l.child;
	ASSERT_NE(child, (void*)0);
	EXPECT_EQ(child->b.stype, slipL_id_t);
	slip_Node* child2 = (slip_Node*) (child->link.next);
	EXPECT_EQ(child2->b.stype, slipL_int_t);
}

TEST(sliplisttest_slipL_addBrother, slipL_addBrother)
{
	slip_Node* node = slipL_parseString("`(defun hello (x y) ((print x) (print y)))");
	ASSERT_NE(node, (void*)0);
	slip_Node* child = node->l.child;
	ASSERT_NE(child, (void*)0);
	EXPECT_EQ(child->b.stype, slipL_id_t);

	slip_Node* child2 = (slip_Node*) (child->link.next);
	EXPECT_EQ(child2->b.stype, slipL_id_t);
}
