/*
* @Author: sxf
* @Date:   2015-12-02 21:14:37
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-04 17:34:59
*/


#include "slipcore.h"
#include "libapi.h"
#include "sliplist.h"
#include "schunk.h"
#include "stable.h"
#include "sstring.h"
#include <stdio.h>
#include <assert.h>


static int _print (slip_Core* vm, int num) {
	for (int i = -num; i < 0; ++i)
	{
		slip_Value v = slipV_getValue(vm, i);
		slipV_printValue(&v); printf("\t");
	}
	slipV_popValueNum(vm, num);
	printf("\n");
	return 0;
}

static int _dot (slip_Core* vm, int num) {

	return 0;
}

static int _add (slip_Core* vm, int num) {

	return 0;
}

static int _sub (slip_Core* vm, int num) {

	return 0;
}

static int _mul (slip_Core* vm, int num) {

	return 0;
}

static int _div (slip_Core* vm, int num) {

	return 0;
}

static int _set (slip_Core* vm, slip_Node* node, int num) {

	return 0;
}


static int _quote (slip_Core* vm, slip_Node* node, int num) {
	slip_Obj* obj = slipC_createChunk(node);
	slipV_pushSChunk(vm, obj);
	return 1;
}


/**
 * @brief 从当前栈中获取真实压栈个数的值, 存入到前x个元素中, 不足的设置为nil, 这些元素会加入新的局部符号表中
 *
 * @param vm [description]
 * @param node [description]
 *
 * @return [description]
 */
static int _let (slip_Core* vm, slip_Node* node, int num) {
	slip_Node* head = node; // 记录一下头
	// 获取到下一个参数, 这是参数定义表
	node = (slip_Node*)(node->link.next);
	// 初始化一个新的局部符号表
	slip_Obj* table = slipT_createTable();
	slipT_initHash(table, 16);
	// 初始化参数表
	int k = -num;
	list_for_each(slip_Node*, p, node->l.child)
		const char* var = p->id.data;
		slip_Obj* key = slipS_createFromStr(var);
		if (k < 0) { // 前n个参数, 从栈中取num个值为其设初值
			slip_Value v = slipV_getValue(vm, k);
			slipT_insertHash(table, key, v);
			++k;
		} else { // 后面初值设置为nil
			slip_Value v;
			slipV_setValueInt(&v, 0);
			slipT_insertHash(table, key, v);
		}
	list_for_each_end
	slipV_popValueNum(vm, num); // 获取参数后将其出栈

	slipC_pushEnvStack(vm, table);

	// 获取到下一个参数, 是程序块的开头
	list_node* p = node->link.next;

	int ret_size = 0;
	for (; p != (list_node*)head; p = p->next)
	{
		slip_Node* n = (slip_Node*) p;
		ret_size = slipC_callNode(vm, n, 0);
	}

	slipC_popEnvStack(vm);
	return ret_size;
}


static int _defun (slip_Core* vm, slip_Node* node, int num) {
	node->id.data = "let"; // 将defun替换成let
	list_node* prev = (list_node*)node;
	node = (slip_Node*)(node->link.next);
	const char* func_name = node->id.data;
	printf("%s\n", func_name);
	_list_remove(prev, node->link.next); // 删除函数名
	slip_Node* newlist = (slip_Node*)slipL_create_ListNode((slip_Node*)prev);
	slip_Obj* chunk = slipC_createChunk(newlist);
	slip_Value v;
	slipV_setValueChunk(&v, chunk);
	slipC_setID(vm, func_name, v);  // 记录这个代码段
	return 0;
}

static int _defmacro (slip_Core* vm, slip_Node* node, int num) {

	return 0;
}




const slip_Reg stdlib[] = {
	{ "print", _print },
	{ ".", _dot },
	{ "+", _add },
	{ "-", _sub },
	{ "*", _mul },
	{ "/", _div },
	{ NULL, NULL }
};


const slip_RegM stdmacro[] = {
	{ "set", _set },
	{ "quote", _quote },
	{ "let", _let },
	{ "defun", _defun },
	{ "defmacro", _defmacro },
	{ NULL, NULL }
};
