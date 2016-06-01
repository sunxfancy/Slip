/*
* @Author: sxf
* @Date:   2015-11-30 08:35:13
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-03 13:11:14
*/

#include "value.h"
#include "schunk.h"
#include "sstring.h"
#include "stdio.h"

int
slipV_setValueString(slip_Value* v, slip_Obj* s) {
	v->v.o = s;
	v->t = slipV_string_t;
	return 0;
}


int
slipV_setValueChunk(slip_Value* v, slip_Obj* c) {
	v->v.o = c;
	v->t = slipV_chunk_t;
	return 0;
}


int
slipV_setValueTable(slip_Value* v, slip_Obj* t) {
	v->v.o = t;
	v->t = slipV_table_t;
	return 0;
}




int
slipV_setValueCPtr(slip_Value* v, void* ptr) {
	v->v.p = ptr;
	v->t = slipV_light_data_t;
	return 0;
}


int
slipV_setValueCFunc(slip_Value* v, slip_CFunction f) {
	v->v.f = f;
	v->t = slipV_light_cfunc_t;
	return 0;
}

int
slipV_setValueCMacro(slip_Value* v, slip_CMacro m) {
	v->v.m = m;
	v->t = slipV_light_cmacro_t;
	return 0;
}



int
slipV_setValueInt(slip_Value* v, int i) {
	v->v.i = i;
	v->t = slipV_int_t;
	return 0;
}


int
slipV_setValueDouble(slip_Value* v, double d) {
	v->v.n = d;
	v->t = slipV_double_t;
	return 0;
}

int
slipV_setValueRef(slip_Value* v, slip_Value* ref) {
	v->v.r = ref;
	v->t = slipV_ref_t;
	return 0;
}

int
slipV_printValue(slip_Value* v) {
	switch(v->t) {
		case slipV_int_t : printf("%d", v->v.i); break;
		case slipV_string_t : {
			SString* s = (SString*)(v->v.o);
			printf("%s", s->data);
			break;
		}
		case slipV_double_t : printf("%.4f", v->v.n); break;
		case slipV_table_t : printf("Table"); break;
		case slipV_chunk_t : {
			printf("Chunk:\n");
			SChunk* c = (SChunk*)(v->v.o);
			slipL_printList(c->head, 1);
			printf("\n");
			break;
		}
		case slipV_light_cfunc_t : printf("C_Function"); break;
		case slipV_light_cmacro_t : printf("C_Macro"); break;
		case slipV_light_data_t : printf("C_Pointer"); break;
		default : printf("Unknown"); return -1;
	}
	return 0;
}
