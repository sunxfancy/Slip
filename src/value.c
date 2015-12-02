/* 
* @Author: sxf
* @Date:   2015-11-30 08:35:13
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-02 16:18:42
*/

#include "value.h"

int 
slipV_setValueString(slip_Value* v, slip_Obj* s) {
	v->v.o = s;
	v->t = slipV_string_t;
}


int 
slipV_setValueChunk(slip_Value* v, slip_Obj* c) {
	v->v.o = c;
	v->t = slipV_chunk_t;
}


int 
slipV_setValueTable(slip_Value* v, slip_Obj* t) {
	v->v.o = t;
	v->t = slipV_table_t;
}




int 
slipV_setValueCPtr(slip_Value* v, void* ptr) {
	v->v.p = ptr;
	v->t = slipV_light_data_t;
}


int 
slipV_setValueCFunc(slip_Value* v, slip_CFunction f) {
	v->v.f = f;
	v->t = slipV_light_cfunc_t;
}

int 
slipV_setValueCMacro(slip_Value* v, slip_CMacro f) {
	v->v.f = f;
	v->t = slipV_light_cmacro_t;
}



int 
slipV_setValueInt(slip_Value* v, int i) {
	v->v.i = i;
	v->t = slipV_int_t;
}


int 
slipV_setValueDouble(slip_Value* v, double d) {
	v->v.n = d;
	v->t = slipV_double_t;
}


