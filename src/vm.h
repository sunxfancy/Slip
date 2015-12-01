/* 
* @Author: sxf
* @Date:   2015-11-29 20:09:30
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-01 16:59:06
* 
* slip的栈式虚拟机
*/


#ifndef VM_H
#define VM_H

#include "value.h"
#include "libapi.h"

typedef struct slip_Core slip_Core;
typedef struct STable STable;

extern int 			slipV_call (slip_Core* vm);
extern int 			slipV_pushValue (slip_Core* vm, slip_Value value);
extern slip_Value 	slipV_popValue (slip_Core* vm);
extern slip_Value 	slipV_getValue (slip_Core* vm, int index);

extern int 			slipV_pushInt (slip_Core* vm, int value);
extern int 			slipV_pushDouble (slip_Core* vm, double value);
extern int 			slipV_pushNil (slip_Core* vm);
extern int 			slipV_pushTable (slip_Core* vm, STable* table);
extern int 			slipV_pushCFunc (slip_Core* vm, slip_CFunction func_pointer);



#endif // VM_H
