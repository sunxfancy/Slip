/* 
* @Author: sxf
* @Date:   2015-11-30 08:35:04
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-03 20:23:00
*/

#include "stack.h"
#include <malloc.h>
#include <assert.h>

slip_StackBlock* 
slipS_createBlock() {
	slip_StackBlock* block = (slip_StackBlock*) calloc(1, sizeof(slip_StackBlock));
	return block;	
}

#define GET_LIST_NODE(block) (&(block->link))

void 		
slipS_extend(slip_Stack* stack){
	slip_StackBlock* block = slipS_createBlock();
	assert(block != NULL);
	if (stack->block_head == NULL) {
		stack->block_head = block;
		stack->stack_size += BLOCK_SIZE;
		return;		
	} 
	list_add(GET_LIST_NODE(stack->block_head), 
			 GET_LIST_NODE(block));
	stack->stack_size += BLOCK_SIZE;
}    /* 扩展整个栈, 新增一个Block */


void 		
slipS_collapse(slip_Stack* stack){
	void* p = list_remove_last(GET_LIST_NODE(stack->block_head));
	free(p);
	stack->stack_size -= BLOCK_SIZE;
}  /* 塌缩栈, 减少一个Block, 建议在空余空间大于BLOCK_SIZE*2的时候塌缩 */


/**
 * @brief 这个是不安全的内部方法, 仅支持正数索引, 也不校验范围
 */
static inline slip_Value
stack_get_z(slip_Stack* stack, int n)
{
	int cs = n / BLOCK_SIZE;
	int hs = n % BLOCK_SIZE;
	list_node* block = (list_node*)(stack->block_head);
	for (int i = 0; i < cs; ++i) block = block->next;
	slip_StackBlock* b = (slip_StackBlock*) block;
	return b->vlist[hs];
}

static inline void
stack_push_z(slip_Stack* stack, int n, slip_Value value)
{
	int cs = n / BLOCK_SIZE;
	int hs = n % BLOCK_SIZE;
	list_node* block = (list_node*)(stack->block_head);
	for (int i = 0; i < cs; ++i) block = block->next;
	slip_StackBlock* b = (slip_StackBlock*) block;
	b->vlist[hs] = value;
}


slip_Value 	
slipS_get(slip_Stack* stack, int index){
	if (0 < index && index <= stack->stack_nuse) {
		return stack_get_z(stack, index);
	}
	if (-(stack->stack_nuse) <= index && index < 0) {
		return stack_get_z(stack, stack->stack_nuse + index + 1);
	}
	slip_Value ans = {0};
	return ans;
}


slip_Value 	
slipS_pop(slip_Stack* stack){
	if ( stack->stack_nuse > 0 ) {
		return stack_get_z(stack, stack->stack_nuse--); // 由于是用不安去的方法,可以直接写--
	}
	slip_Value ans = {0};
	return ans;
} /* 这里并不会主动调用collapse, 必须手动减小栈 */


int 			
slipS_push(slip_Stack* stack, slip_Value value){
	if ( stack->stack_nuse < stack->stack_size ) {
		stack_push_z(stack, ++(stack->stack_nuse), value);
		return 0;
	} 
	return -1;
} /* 压入新元素, 返回此时栈的大小, 即该元素的索引位置, 注意栈中元素是从1开始标号的 */


int
slipS_popNum(slip_Stack* stack, int num) {
	int p;
	if ( stack->stack_nuse >= num ) p = num;
	else p = stack->stack_nuse;
	for (int i = 0; i < p; ++i) {
		slipS_pop(stack);
	}
	return p;
} /* 弹出栈顶的指定个元素, 返回实际弹出的元素个数, 负数为异常 */


void
slipS_printStack(slip_Stack* stack) {
	printf("stack: ");
	for (int i = 1; i <= stack->stack_nuse; ++i) {
		slip_Value v = slipS_get(stack, i);
		slipV_printValue(&v);
		printf("  ");
	}
	printf("\n");
}