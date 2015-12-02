/* 
* @Author: sxf
* @Date:   2015-12-01 16:42:01
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-02 12:35:03
*/

#include "schunk.h"
#include "vm.h"
#include "slipcore.h"
#include <malloc.h>
#include "sliplist.h"

SChunk*  
slipC_createChunk(slip_Node* node) {
	SChunk* s = (SChunk*) calloc(1, sizeof(SChunk));
	s->head = node;
	return s;
}


int
slipC_callNode(slip_Core* vm, slip_Node* node) {
	printf("call\n");
	if (node->b.stype == slipL_list_t) {
		node = node->l.child;
		if (node->b.stype != slipL_id_t) {
			printf("异常的首节点类型，必须为id\n");
			slipL_printList(node, 0);
		}
		slip_Value v = slipC_findID(vm, node->id.data);
		if (v.v.i == 0) {
			printf("异常，符号未找到：%s\n", node->id.data);
			return -1;
		}
		if (v.t == slipV_light_cfunc_t) { // 这里针对的是函数调用， 会依次解析下面的内容
			list_node* p = (list_node*)(node->link.prev);
			list_node* head = (list_node*) node;
			int num = 0;
			for (; p != head; p = p->prev, ++num) {
				slip_Node* n = (slip_Node*) p;
				switch(n->b.stype) {
					case slipL_int_t : slipV_pushInt(vm, n->i.value); break;
					case slipL_float_t : slipV_pushDouble(vm, n->f.value); break;
					case slipL_id_t : slipV_pushStr(vm, n->id.data); break;
					case slipL_string_t: slipV_pushStr(vm, n->s.data); break;
					case slipL_list_t: slipC_callNode(vm, n->l.child); break;
					default: printf("异常的节点类型\n"); return -1; // TODO 异常时需要抛弃已插入的元素
				}
			}
			slipV_pushValue(vm, v);
			slipV_call(vm, num);
			printf("call done\n");
			return 0;
		}
	}
	return -2;
}


int
slipC_callChunk(slip_Core* vm, SChunk* c, int num) {
	if (num == 0) 
	return slipC_callNode(vm, c->head);
}


