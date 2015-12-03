/* 
* @Author: sxf
* @Date:   2015-12-01 16:13:25
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-03 20:28:19
*/

#ifndef CHUNK_H
#define CHUNK_H

#include "object.h"
#include "sliplist.h"

typedef struct slip_Core slip_Core;

typedef struct SChunk {
	slip_Obj 	base;
	slip_Node*  head;
} SChunk;


extern slip_Obj*  	slipC_createChunk(slip_Node* node);


/**
 * @brief 将一个list当做代码执行
 * 
 * @param vm 内核
 * @param node list的头节点
 * 
 * @return 0 为正常执行，-1 符号未找到异常， -2 调用类型不符
 */
extern int 			slipC_callNode(slip_Core* vm, slip_Node* node, int num);


extern int 			slipC_callChunk(slip_Core* vm, slip_Obj* c, int num);


#endif // CHUNK_H
