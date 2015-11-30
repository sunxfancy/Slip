/* 
* @Author: sxf
* @Date:   2015-11-30 08:34:58
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-30 12:25:50
*/

#include "sliplist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


/**
 * @brief 用在链表数据类型的构造函数中的初始化宏
 */
#define NODE_LIST_CREATE_INIT(this_addr) LIST_INIT(&(this_addr->base.link))

#define STYPE_INIT(type) n->base.stype = type

#define mallocNode(type, ele) type* ele = (type*) malloc(sizeof(type))

slip_IntNode* 		
slipL_create_IntNode(int num) {
	mallocNode(slip_IntNode, n);
	NODE_LIST_CREATE_INIT(n);
	STYPE_INIT(int_t);
	n->value = num;
	return n;
}

slip_FloatNode* 		
slipL_create_FloatNode(double num) {
	mallocNode(slip_IntNode, n);
	NODE_LIST_CREATE_INIT(n);
	STYPE_INIT(float_t);
	n->value = num;
	return n;
}

slip_StringNode* 	
slipL_create_StringNode(const char* str) {
	mallocNode(slip_StringNode, n);
	NODE_LIST_CREATE_INIT(n);
	STYPE_INIT(string_t);
	int len = strlen(str);
	char* buf = (char*) malloc (len+1);
	n->data = strcpy(buf, str);
	return n;
}

slip_IDNode* 		
slipL_create_IDNode(const char* str) {
	mallocNode(slip_IDNode, n);
	NODE_LIST_CREATE_INIT(n);
	STYPE_INIT(id_t);
	int len = strlen(str);
	char* buf = (char*) malloc (len+1);
	n->data = strcpy(buf, str);
	return n;
}

slip_ListNode* 		
slipL_create_ListNode(slip_Node* node) {
	mallocNode(slip_ListNode, n);
	NODE_LIST_CREATE_INIT(n);
	STYPE_INIT(list_t);
	n->child = node;
	return n;
}

slip_IntNode* 		
slipL_create_IntNodeFromStr(const char* str) {
	int value = atoi(str);
	return slipL_create_IntNode(value);
}

slip_FloatNode* 		
slipL_create_FloatNodeFromStr(const char* str) {
	double value = atof(str);
	return slipL_create_FloatNode(value);
}

slip_Node* 		
slipL_makeList(int num, ...) {
	va_list argp; slip_Node* para = NULL;  
	slip_Node* ans = NULL;  
	va_start( argp, num );    
    for (int i = 0; i < num; ++i) {    
        para = va_arg( argp, slip_Node* );  
        if ( ans == NULL )    
        	ans = para;
        else slipL_addBrother(ans, para);
    }    
    va_end( argp );
    return ans;
}

slip_NodeType		
slipL_getType(slip_Node* node) {
	return node->b.stype;
}

void		 			
slipL_addBrother(slip_Node* node, slip_Node* add_node) {
	list_add(&(node->b.link), &(add_node->b.link));
}

static void
printList_Node(slip_Node* node) {
	switch(node->b.stype) {
		case int_t: printf("int %d", node->i.value); break;
		case float_t: printf("float %f", node->f.value); break;
		case string_t: printf("string %s", node->s.data); break;
		case id_t: printf("id %s", node->id.data); break;
		case list_t: printf("list"); break;
	}
	printf("\n");
}

void					
slipL_printList(slip_Node* node, int d) {
	for (int i = 0; i < d; ++i) {
		printf("    ");
	}
	printList_Node(node);
	if (node->b.stype == list_t) {
		slip_Node* child = node->l.child;
		list_for_each(slip_Node*, p, child)
			slipL_printList(p, d+1);
		list_for_each_end
	}
}