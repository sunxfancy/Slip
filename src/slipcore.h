/* 
* @Author: sxf
* @Date:   2015-11-29 09:30:04
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-30 09:53:57
*/



#ifndef SLIPCORE_H
#define SLIPCORE_H

#include "vm.h"

typedef struct slip_Context slip_Context;
typedef struct slip_Core slip_Core;


/**
 * @brief slip全局上下文, 一般是进程唯一对象
 */
struct slip_Context
{
};


/**
 * @brief slip内核, 包含一个栈和全局的引用
 */
struct slip_Core
{
	slip_Context* 	context;
	slip_VM* 		main_vm;
	// slip_VM**		threads;
};



#endif // SLIPCORE_H
