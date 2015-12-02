/* 
* @Author: sxf
* @Date:   2015-11-29 20:09:30
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-02 10:15:56
* 
* slip的栈式虚拟机
*/


#ifndef VM_H
#define VM_H

#include "value.h"
#include "libapi.h"

typedef struct slip_Core slip_Core;
typedef struct STable STable;
typedef struct SString SString;
typedef struct SChunk SChunk;
typedef union slip_Node slip_Node;


/**
 * @brief 核心的函数调用方法 弹出栈顶的元素, 按照对应的类型, 将其进行解析调用
 * 
 * @param vm 内核
 * @return 异常码
 */
extern int 			slipV_call (slip_Core* vm, int num);

extern int 			slipV_pushValue (slip_Core* vm, slip_Value value);
extern slip_Value 	slipV_popValue (slip_Core* vm);
extern int 		 	slipV_popValueNum (slip_Core* vm, int num);
extern slip_Value 	slipV_getValue (slip_Core* vm, int index);

extern int 			slipV_pushInt (slip_Core* vm, int value);
extern int 			slipV_pushDouble (slip_Core* vm, double value);
extern int 			slipV_pushNil (slip_Core* vm);
extern int 			slipV_pushTable (slip_Core* vm, STable* table);
extern int 			slipV_pushCFunc (slip_Core* vm, slip_CFunction func_pointer);
extern int 			slipV_pushSString (slip_Core* vm, SString* str);
extern int 			slipV_pushStr (slip_Core* vm, const char* str);
extern int 			slipV_pushSChunk (slip_Core* vm, SChunk* chunk);
extern int 			slipV_pushListNode (slip_Core* vm, slip_Node* node);


#endif // VM_H
