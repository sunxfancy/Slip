/* 
* @Author: sxf
* @Date:   2015-11-29 20:09:30
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-30 13:05:42
* 
* slip的栈式虚拟机
*/


#ifndef VM_H
#define VM_H

#include "value.h"

typedef struct slip_Core slip_Core;

extern int 			slipV_call (slip_Core* vm);
extern int 			slipV_pushValue (slip_Core* vm, slip_Value value);
extern slip_Value 	slipV_popValue (slip_Core* vm);
extern slip_Value 	slipV_getValue (slip_Core* vm, int index);


#endif // VM_H
