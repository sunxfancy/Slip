/* 
* @Author: sxf
* @Date:   2015-11-29 22:10:37
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-02 16:19:03
*/


#ifndef VALUE_H
#define VALUE_H

#include "object.h"
#include "libapi.h"

typedef union SValue {
	slip_Obj* 			o;    /* collectable objects */
	void*				p;    /* light userdata */
	slip_CFunction 		f;    /* light C functions */
	int 				i;    /* integer numbers */
	double 				n;    /* float numbers */
} SValue;

typedef enum slip_ValueType {
	slipV_int_t = 1, 
	slipV_double_t = 2,
	slipV_light_data_t = 3,  
	slipV_light_cfunc_t = 4, 
	slipV_light_cmacro_t = 5,
	slipV_table_t = 6,
	slipV_string_t = 7,
	slipV_thread_t = 8,
	slipV_chunk_t = 9,
} slip_ValueType;

typedef struct slip_Value {
	SValue 			v;
	slip_ValueType 	t;
} slip_Value;


extern int slipV_setValueString(slip_Value* v, slip_Obj* s);
extern int slipV_setValueChunk(slip_Value* v, slip_Obj* c);
extern int slipV_setValueTable(slip_Value* v, slip_Obj* t);
extern int slipV_setValueCPtr(slip_Value* v, void* ptr);
extern int slipV_setValueCFunc(slip_Value* v, slip_CFunction f);
extern int slipV_setValueCMacro(slip_Value* v, slip_CMacro f);
extern int slipV_setValueInt(slip_Value* v, int i);
extern int slipV_setValueDouble(slip_Value* v, double d);



#endif // VALUE_H
