/* 
* @Author: sxf
* @Date:   2015-11-30 17:51:42
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-30 18:09:28
*/

#ifndef STABLE_H
#define STABLE_H

#include "object.h"


typedef struct STablePair {
	SString* key;
	slip_Value value;
} STablePair;


typedef struct STable {
	slip_Obj 	base;

	// 分成两部分, 一部分是用作数组的, 一部分则作为hash表
	slip_Value* array; // 默认情况是未分配
	int 		array_size;	
	int 		array_nuse;

	// 用作hash表的部分
	STablePair* hash_map;
	int 		map_size;
	int 		map_nuse;

} STable;





#endif // STABLE_H
