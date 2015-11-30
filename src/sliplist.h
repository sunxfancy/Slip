/* 
* @Author: sxf
* @Date:   2015-11-29 15:15:02
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-30 12:24:03
*/


#ifndef SLIPLIST_H
#define SLIPLIST_H

#include "list.h"


/**
 * 五种链表中的基本类型
 */
typedef enum slip_NodeType
{
	int_t,
	float_t,
	string_t,
	id_t,
	list_t,	
} slip_NodeType;

typedef union slip_Node slip_Node; 


typedef struct slip_NodeBase {
	list_node link;
	slip_NodeType stype;
} slip_NodeBase;


typedef struct slip_IntNode
{
	slip_NodeBase base;
	int value;
} slip_IntNode;

typedef struct slip_FloatNode
{
	slip_NodeBase base;
	double value;
} slip_FloatNode;


typedef struct slip_StringNode
{
	slip_NodeBase base;
	char* data;
} slip_StringNode;


typedef struct slip_IDNode
{
	slip_NodeBase base;
	char* data;
} slip_IDNode;


typedef struct slip_ListNode
{
	slip_NodeBase base;
	slip_Node* child;
} slip_ListNode;


/**
 * 基本的表节点的聚合
 */
union slip_Node {
	struct slip_NodeBase	b;
	struct slip_IntNode 	i;
	struct slip_FloatNode   f;
	struct slip_StringNode  s;
	struct slip_IDNode  	id;
	struct slip_ListNode    l;
};



extern slip_IntNode* 		slipL_create_IntNode(int num);
extern slip_FloatNode* 		slipL_create_FloatNode(double num);
extern slip_StringNode* 	slipL_create_StringNode(const char* str);
extern slip_IDNode* 		slipL_create_IDNode(const char* str);
extern slip_ListNode* 		slipL_create_ListNode(slip_Node* node);
extern slip_IntNode* 		slipL_create_IntNodeFromStr(const char* str);
extern slip_FloatNode* 		slipL_create_FloatNodeFromStr(const char* str);


extern slip_Node* 			slipL_makeList(int num, ...);
extern slip_NodeType		slipL_getType(slip_Node* node);
extern void		 			slipL_addBrother(slip_Node* node, slip_Node* add_node);
extern void					slipL_printList(slip_Node* node, int d);

#endif // SLIPLIST_H