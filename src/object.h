/* 
* @Author: sxf
* @Date:   2015-11-29 10:14:08
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-30 10:16:45
*/

#ifndef OBJECT_H
#define OBJECT_H


typedef struct slip_Obj slip_Obj;
typedef char byte_st;

struct slip_Obj {
	slip_Obj* next;
	byte_st mark; 
};







#endif // OBJECT_H
