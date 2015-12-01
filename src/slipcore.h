/* 
* @Author: sxf
* @Date:   2015-11-29 09:30:04
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-01 20:14:35
*/



#ifndef SLIPCORE_H
#define SLIPCORE_H

#include "vm.h"
#include "stack.h"
#include "value.h"

typedef struct slip_Context slip_Context;
typedef struct slip_Core slip_Core;
typedef struct STable STable;

/**
 * @brief slip全局上下文, 一般是进程唯一对象
 */
struct slip_Context
{
	// 全局Table
	STable* env;
	
	// GC 堆
	slip_Obj* gc_heap;

};


/**
 * @brief slip内核, 包含一个栈和全局的引用
 */
struct slip_Core
{
	slip_Obj 		base;
	slip_Stack		stack;
	slip_Context* 	context;

	// 局部环境栈
	slip_Stack		env_stack; // 放置环境table
};


extern slip_Core* 		slipC_createCore();
extern slip_Context* 	slipC_createContext();
extern int 				slipC_close(slip_Core* vm);
extern int 				slipC_loadFile(const char* path);
extern int 				slipC_loadStr(const char* str);

/**
 * @brief 立即执行一次小GC
 */
extern void				slipC_gc(slip_Core* vm);

/**
 * @brief 执行完整的GC流程
 */
extern void				slipC_fullgc(slip_Core* vm);


#endif // SLIPCORE_H
