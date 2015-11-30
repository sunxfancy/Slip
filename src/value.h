/* 
* @Author: sxf
* @Date:   2015-11-29 22:10:37
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-30 18:40:19
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
	slipV_list_t = 5,
	slipV_table_t = 6,
	slipV_string_t = 7,
	slipV_thread_t = 8
} slip_ValueType;

typedef struct slip_Value {
	SValue 			v;
	slip_ValueType 	t;
} slip_Value;

#endif // VALUE_H
