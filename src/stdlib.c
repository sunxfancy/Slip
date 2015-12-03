/* 
* @Author: sxf
* @Date:   2015-12-02 21:14:37
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-03 16:16:50
*/


#include "slipcore.h"
#include "libapi.h"
#include <stdio.h>


static int _print (slip_Core* vm, int num) {
	for (int i = 0; i < num; ++i)
	{
		slip_Value v = slipV_popValue(vm);
		slipV_printValue(&v);
	}
	return 0;
}

static int _set (slip_Core* vm, int num) {

	return 0;
}


static int _quote (slip_Core* vm, slip_Node* node, int num) {
	printf("quote\n");
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
	printf("let\n");
	slip_Node* head = node; // 记录一下头
	// 获取到下一个参数, 这是参数定义表
	node = (slip_Node*)(node->link.next);
	// 初始化一个新的局部符号表
	slip_Obj* table = slipT_createTable();
	slipT_initHash(table, num*2);
	// 初始化参数表
	int k = -num;
	list_for_each(slip_Node*, p, node->l.child)
		const char* var = p->id.data;
		slip_Obj* key = slipS_createFromStr(var);
		if (k < 0) { // 前n个参数, 从栈中取num个值为其设初值
			slip_Value v = slipV_getValue(vm, k);
			slipT_insertHash(table, var, v);
			++k;
		} else { // 后面初值设置为nil
			slip_Value v;
			slipV_setValueInt(&v, 0);
			slipT_insertHash(table, var, v);
		}
	list_for_each_end
	slipC_pushEnvStack(vm, table);

	// 获取到下一个参数, 是程序块的开头
	node = (slip_Node*)(node->link.next);

	int ret_size = 0;
	for (list_node* p = node; p != head; p = p->next) 
	{
		slip_Node* n = (slip_Node*) p;
		ret_size = slipC_callNode(vm, n);
	}

	slipC_popEnvStack(vm);
	return ret_size;
}


static int _defun (slip_Core* vm, slip_Node* node, int num) {
	printf("defun\n");
	
	return 0;
}

static int _defmacro (slip_Core* vm, slip_Node* node, int num) {
	printf("defmacro\n");
	
	return 0;
}




const slip_Reg stdlib[] = {
	{ "print", _print },
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