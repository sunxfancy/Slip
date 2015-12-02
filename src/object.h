/* 
* @Author: sxf
* @Date:   2015-11-29 10:14:08
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-02 13:45:25
*/

#ifndef OBJECT_H
#define OBJECT_H


typedef struct slip_Obj slip_Obj;
typedef unsigned char byte_st;


struct slip_Obj {
	slip_Obj* next;
	byte_st mark; 
	byte_st type;
};

#define slipO_string_t 	1
#define slipO_table_t 	2
#define slipO_chunk_t 	3

#define slipO_checkType(obj, ty) (obj->type == ty)
#define slipO_castString(obj) (SString*)(obj)
#define slipO_castTable(obj) (STable*)(obj)
#define slipO_castChunk(obj) (SChunk*)(obj)



#endif // OBJECT_H
