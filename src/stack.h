/* 
* @Author: sxf
* @Date:   2015-11-29 10:36:57
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-30 10:12:02
* 
* slip虚拟机栈的实现, 基于内核双链表实现的块状数组
* 整个栈的索引可以是0到栈顶-1, -1到栈底
*/



#ifndef STACK_H
#define STACK_H

#include "list.h"
#include "value.h"

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 510
#endif

typedef struct slip_StackBlock {
	list_node 			link;
	slip_Value*			vlist[BLOCK_SIZE]; /* all stack ref of slip value */
} slip_StackBlock;


typedef struct slip_Stack {
	slip_StackBlock* 	block_head; /* first block of the stack node */
	int 				stack_size; /* size of the sum stack */
	int 				stack_nuse; /* number of element */
} slip_Stack;




#endif // STACK_H
