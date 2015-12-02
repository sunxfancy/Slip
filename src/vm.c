/* 
* @Author: sxf
* @Date:   2015-11-30 08:35:18
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-02 14:25:01
*/

#include "vm.h"
#include "slipcore.h"
#include "value.h"
#include "sstring.h"
#include "stable.h"
#include "schunk.h"


int
slipV_call (slip_Core* vm, int num) {
	slip_Value v = slipV_popValue(vm);
	switch (v.t) {
		case slipV_chunk_t:  return slipC_callChunk(vm, v.v.o, num); 
		case slipV_light_cfunc_t: return slipL_callCFunction(vm, v.v.f, num);
	}
}


int
slipV_pushValue (slip_Core* vm, slip_Value value) {
	if (vm->stack.stack_size > vm->stack.stack_nuse) {
		return slipS_push(&(vm->stack), value);
	} else {
		slipS_extend(&(vm->stack));
		return slipS_push(&(vm->stack), value);
	}
}

slip_Value
slipV_popValue (slip_Core* vm) {
	if (vm->stack.stack_size - vm->stack.stack_nuse > BLOCK_SIZE * 2) {
		slipS_collapse(&(vm->stack));
	}
	return slipS_pop(&(vm->stack));
}


int
slipV_popValueNum (slip_Core* vm, int num) {
	int right_num = slipS_popNum(&(vm->stack), num);
	if (vm->stack.stack_size - vm->stack.stack_nuse > BLOCK_SIZE * 2) {
		slipS_collapse(&(vm->stack));
	}
	return right_num;
}


slip_Value
slipV_getValue (slip_Core* vm, int index) {
	return slipS_get(&(vm->stack), index);
}


int
slipV_pushInt (slip_Core* vm, int value) {
	slip_Value v;
	slipV_setValueInt(&v, value);
	return slipV_pushValue(vm, v);
}


int
slipV_pushDouble (slip_Core* vm, double value) {
	slip_Value v;
	slipV_setValueDouble(&v, value);
	return slipV_pushValue(vm, v);
}


int
slipV_pushNil (slip_Core* vm) {
	slip_Value v;
	slipV_setValueInt(&v, 0);
	return slipV_pushValue(vm, v);
}


int
slipV_pushTable (slip_Core* vm, slip_Obj* table) {
	slip_Value v;
	slipV_setValueTable(&v, table);
	return slipV_pushValue(vm, v);
}


int
slipV_pushCFunc (slip_Core* vm, slip_CFunction func_pointer) {
	slip_Value v;
	slipV_setValueCFunc(&v, func_pointer);
	return slipV_pushValue(vm, v);
}


int
slipV_pushSString (slip_Core* vm, slip_Obj* str) {
	slip_Value v;
	slipV_setValueString(&v, str);
	return slipV_pushValue(vm, v);
}


int
slipV_pushStr (slip_Core* vm, const char* str) {
	slip_Value v;
	slip_Obj* s = slipS_createFromStr(str);
	slipV_setValueString(&v, s);
	return slipV_pushValue(vm, v);
}


int
slipV_pushSChunk (slip_Core* vm, slip_Obj* chunk) {
	slip_Value v;
	slipV_setValueChunk(&v, chunk);
	return slipV_pushValue(vm, v);
}


int
slipV_pushListNode (slip_Core* vm, slip_Node* node) {
	slip_Value v;
	slip_Obj* chunk = slipC_createChunk(node);
	slipV_setValueChunk(&v, chunk);
	return slipV_pushValue(vm, v);
}


