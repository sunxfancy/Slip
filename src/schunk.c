/* 
* @Author: sxf
* @Date:   2015-12-01 16:42:01
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-03 20:32:49
*/

#include "schunk.h"
#include "vm.h"
#include "slipcore.h"
#include "stack.h"
#include <malloc.h>
#include <assert.h>
#include "sliplist.h"

slip_Obj*  
slipC_createChunk(slip_Node* node) {
	SChunk* s = (SChunk*) calloc(1, sizeof(SChunk));
	s->head = node;
	return (slip_Obj*)s;
}


static int
slip_callNodeList(slip_Core* vm, slip_Node* node, int num) {
	if (node->b.stype != slipL_id_t) {
		printf("异常的首节点类型，必须为id\n");
		slipL_printList(node, 0);
		return -1;
	}
	slip_Value v = slipC_findID(vm, node->id.data);
	if (v.v.i == 0 && v.t == 0) {
		printf("异常，符号未找到：%s\n", node->id.data);
		return -1;
	}
	if (v.t == slipV_light_cfunc_t || v.t == slipV_chunk_t) { // 这里针对的是函数调用， 会依次解析下面的内容
		list_node* p = (list_node*)(node->link.next);
		list_node* head = (list_node*) node;
		int num = 0;
		for (; p != head; p = p->next) {
			slip_Node* n = (slip_Node*) p;
			int ret_sum = slipC_callNode(vm, n, num);
			if (ret_sum < 0) return -1;
			num += ret_sum;
		}
		slipV_pushValue(vm, v);
		int ret_size = slipV_call(vm, num);
		return ret_size;
	}

	if (v.t == slipV_light_cmacro_t) {
		slip_Obj* c = slipC_createChunk((slip_Node*)node);
		slip_Value chunk;
		slipV_setValueChunk(&chunk, c);
		slipV_pushValue(vm, chunk);
		slipV_pushValue(vm, v);
		int ret_size = slipV_call(vm, num);
		return ret_size;
	}
}


int
slipC_callNode(slip_Core* vm, slip_Node* node, int num) {
	switch (node->b.stype) {
		case slipL_id_t : {
			slip_Value v = slipC_findID(vm, node->id.data);
			if (v.v.i == 0 && v.t == 0) {
				printf("异常，符号未找到：%s\n", node->id.data);
				return -1;
			}
			slipV_pushValue(vm, v); return 1;
		}
		case slipL_int_t : slipV_pushInt(vm, node->i.value); return 1;
		case slipL_float_t : slipV_pushDouble(vm, node->f.value); return 1;
		case slipL_string_t: slipV_pushStr(vm, node->s.data); return 1;
		case slipL_list_t: return slip_callNodeList(vm, node->l.child, num); 
	}
	printf("该Chunk无法调用\n");
	return -1;
}


int
slipC_callChunk(slip_Core* vm, slip_Obj* c, int num) {
	slipS_printStack(&(vm->stack));
	SChunk* sc = slipO_castChunk(c);
	int ret_size = 0;
	list_for_each(slip_Node*, p, sc->head)
		ret_size = slipC_callNode(vm, p, num);
		if (ret_size < 0) return ret_size;
	list_for_each_end
	return ret_size;
}


