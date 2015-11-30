/* 
* @Author: sxf
* @Date:   2015-11-29 22:10:37
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-30 10:29:59
*/


#ifndef VALUE_H
#define VALUE_H

#include "object.h"
#include "libapi.h"

typedef union SValue {
	slip_Obj* 			o;    /* collectable objects */
	void*				p;    /* light userdata */
	int 				b;    /* booleans */
	slip_CFunction 		f;    /* light C functions */
	int 				i;    /* integer numbers */
	double 				n;    /* float numbers */
} SValue;

typedef enum slip_ValueType {
	obj_t, light_t, bool_t, light_cf_t, int_t, double_t
} slip_ValueType;

typedef struct slip_Value {
	SValue 			v;
	slip_ValueType 	t;
} slip_Value;

#endif // VALUE_H
