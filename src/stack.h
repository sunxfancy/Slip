/* 
* @Author: sxf
* @Date:   2015-11-29 10:36:57
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-03 20:21:14
* 
* slip虚拟机栈的实现, 基于内核双链表实现的块状数组
* 整个栈的索引可以是1到栈顶, -1到栈底, 0为无效值
*/



#ifndef STACK_H
#define STACK_H

#include "list.h"
#include "value.h"

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 128
#endif

typedef struct slip_StackBlock {
	list_node 			link;
	slip_Value			vlist[BLOCK_SIZE]; /* all stack ref of slip value */
} slip_StackBlock;


typedef struct slip_Stack {
	slip_StackBlock* 	block_head; /* first block of the stack node */
	int 				stack_size; /* size of the sum stack */
	int 				stack_nuse; /* number of element */
} slip_Stack;


extern slip_StackBlock* slipS_createBlock();
extern void 			slipS_extend(slip_Stack* stack);    /* 扩展整个栈, 新增一个Block */
extern void 			slipS_collapse(slip_Stack* stack);  /* 塌缩栈, 减少一个Block, 建议在空余空间大于BLOCK_SIZE*2的时候塌缩 */
extern slip_Value 		slipS_get(slip_Stack* stack, int index);
extern slip_Value 		slipS_pop(slip_Stack* stack); /* 这里并不会主动调用collapse, 必须手动减小栈 */
extern int 				slipS_push(slip_Stack* stack, slip_Value value); /* 压入新元素, 返回此时栈的大小, 即该元素的索引位置, 注意栈中元素是从1开始标号的 */
extern int 		 		slipS_popNum(slip_Stack* stack, int num); /* 弹出栈顶的指定个元素, 返回实际弹出的元素个数, 负数为异常 */
extern void				slipS_printStack(slip_Stack* stack);

#endif // STACK_H
