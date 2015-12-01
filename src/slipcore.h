/* 
* @Author: sxf
* @Date:   2015-11-29 09:30:04
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-01 09:56:32
*/



#ifndef SLIPCORE_H
#define SLIPCORE_H

#include "vm.h"
#include "stack.h"

typedef struct slip_Context slip_Context;
typedef struct slip_Core slip_Core;


/**
 * @brief slip全局上下文, 一般是进程唯一对象
 */
struct slip_Context
{
	// 全局Table
};


/**
 * @brief slip内核, 包含一个栈和全局的引用
 */
struct slip_Core
{

	slip_Stack		stack;
	slip_Context* 	context;

	// 局部环境栈
};



#endif // SLIPCORE_H
