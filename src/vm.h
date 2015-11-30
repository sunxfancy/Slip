/* 
* @Author: sxf
* @Date:   2015-11-29 20:09:30
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-30 11:52:13
* 
* slip的栈式虚拟机
*/


#ifndef VM_H
#define VM_H

#include "stack.h"


typedef struct slip_VM {
	
	slip_Stack    stack;
} slip_VM;


extern int 			slipV_call (slip_VM* vm);
extern int 			slipV_pushValue (slip_VM* vm, slip_Value value);
extern slip_Value 	slipV_popValue (slip_VM* vm);
extern slip_Value 	slipV_getValue (slip_VM* vm, int index);


#endif // VM_H
