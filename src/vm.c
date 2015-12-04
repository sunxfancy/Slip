/* 
* @Author: sxf
* @Date:   2015-11-30 08:35:18
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-04 17:13:20
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
		case slipV_light_cmacro_t: {
			slip_Value macro = slipV_popValue(vm);
			if (macro.v.i == 0 || macro.t != slipV_chunk_t) {
				printf("宏调用异常\n"); return -1;
			}
			SChunk* c = (SChunk*)(macro.v.o);
			return slipL_callCMacro(vm, v.v.m, c->head, num);
		}
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
slipV_pushCLightData (slip_Core* vm, void* data) {
	slip_Value v;
	slipV_setValueCPtr(&v, data);
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


int 		 	
slipV_toInt (slip_Core* vm, int index) {
	slip_Value v = slipV_getValue(vm, index);
	return v.v.i;
}

double 		
slipV_toDouble (slip_Core* vm, int index) {
	slip_Value v = slipV_getValue(vm, index);
	return v.v.n;
}

slip_Obj* 	
slipV_toSTable (slip_Core* vm, int index) {
	slip_Value v = slipV_getValue(vm, index);
	return v.v.o;
}

slip_Obj* 	
slipV_toSString (slip_Core* vm, int index) {
	slip_Value v = slipV_getValue(vm, index);
	return v.v.o;
}

const char* 	
slipV_toCStr (slip_Core* vm, int index) {
	slip_Value v = slipV_getValue(vm, index);
	SString* s = (SString*) (v.v.o);
	return s->data;
}

slip_Obj*	
slipV_toSChunk (slip_Core* vm, int index) {
	slip_Value v = slipV_getValue(vm, index);
	return v.v.o;
}

slip_Node*	
slipV_toListNode (slip_Core* vm, int index) {
	slip_Value v = slipV_getValue(vm, index);
	SChunk* sc = (SChunk*) (v.v.o);
	return sc->head;
}

